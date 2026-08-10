#!/usr/bin/env python3
"""Translate remaining English strings in all 15 non-EN languages."""
import json, sys, os
from translate import Translator

os.chdir(os.path.dirname(os.path.abspath(__file__)))

en = json.load(open('_lang/en.json', encoding='utf-8'))

# All long-text keys that may need translation
LONG_KEYS = [
    'manifest_body', 'manifest_highlight', 'manifest_lead',
    'feat_ondas_desc',
    'ondas_body', 'ondas_lead', 'ondas_highlight',
    'hw_lead'
]

# Language code → provider language code
LANG_MAP = {
    'ja': 'ja', 'fr': 'fr', 'es': 'es', 'ko': 'ko',
    'zh_CN': 'zh-CN', 'ru': 'ru', 'it': 'it', 'pt': 'pt',
    'ca': 'ca', 'gl': 'gl', 'hr': 'hr', 'id': 'id',
    'lv': 'lv', 'sv': 'sv', 'de': 'de'
}

for code, provider_code in LANG_MAP.items():
    if code == 'en' or code == 'de':
        continue  # DE is fully done, EN is source
    
    path = f'_lang/{code}.json'
    d = json.load(open(path, encoding='utf-8'))
    
    # Find keys that are still English
    to_translate = []
    for k in LONG_KEYS:
        if d.get(k, '') == en.get(k, ''):
            to_translate.append(k)
    
    if not to_translate:
        print(f'{code}: nothing to translate')
        continue
    
    print(f'{code}: translating {len(to_translate)} keys: {to_translate}')
    
    translator = Translator(from_lang='en', to_lang=provider_code)
    
    for k in to_translate:
        text = en[k]
        try:
            result = translator.translate(text)
            d[k] = result
            print(f'  {k}: OK ({len(result)} chars)')
        except Exception as e:
            print(f'  {k}: FAILED - {e}')
    
    json.dump(d, open(path, 'w', encoding='utf-8'), indent=2, ensure_ascii=False)
    print(f'  Saved {path}')

print('\nDone.')
