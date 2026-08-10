#!/usr/bin/env python3
"""Translate missing nav labels in all website language files."""
import json, os, sys, time

from deep_translator import GoogleTranslator

DOCS_DIR = os.path.dirname(os.path.abspath(__file__))

# Map website lang codes to Google Translate codes
LANG_MAP = {
    'ca': 'ca', 'de': 'de', 'es': 'es', 'fr': 'fr', 'gl': 'gl',
    'hr': 'hr', 'id': 'id', 'it': 'it', 'ja': 'ja', 'ko': 'ko',
    'lv': 'lv', 'pt': 'pt', 'ru': 'ru', 'sv': 'sv', 'zh_CN': 'zh-CN',
}

# Labels to translate
LABELS = {
    'nav_docs': 'Docs',
    'nav_wiki': 'Wiki',
    'nav_tutorials': 'Tutorials',
    'nav_manifest': 'Manifest',
    'nav_hardware': 'Hardware',
    'nav_ondas': 'ONDAS',
    'nav_servos': 'Servos',
    'nav_features': 'Features',
    'manifest_title': 'Manifest',
    'features_title': 'Features',
    'hardware_title': 'Hardware',
    'ondas_title': 'ONDAS',
}

def load_json(path):
    with open(path, 'r', encoding='utf-8') as f:
        return json.load(f)

def save_json(path, data):
    with open(path, 'w', encoding='utf-8') as f:
        json.dump(data, f, ensure_ascii=False, indent=2)

def main():
    en_path = os.path.join(DOCS_DIR, '_lang', 'en.json')
    en = load_json(en_path)
    
    # 1. Add hardware_title to en.json if missing
    if 'hardware_title' not in en or not en['hardware_title']:
        en['hardware_title'] = 'Hardware'
        save_json(en_path, en)
        print("Added hardware_title to en.json")
    
    # 2. Translate for each language
    lang_dir = os.path.join(DOCS_DIR, '_lang')
    
    for code, gt_code in LANG_MAP.items():
        if code in ('en',):
            continue
        
        path = os.path.join(lang_dir, f'{code}.json')
        if not os.path.exists(path):
            print(f"  SKIP {code}: file not found")
            continue
        
        d = load_json(path)
        
        # Find labels that need translation
        to_translate = {}
        for key, en_val in LABELS.items():
            current = d.get(key, '')
            if current == '' or current == en_val:
                to_translate[key] = en_val
        
        if not to_translate:
            print(f"  {code}: all done, skipping")
            continue
        
        print(f"  {code}: translating {len(to_translate)} labels...", end=' ', flush=True)
        
        try:
            translator = GoogleTranslator(source='en', target=gt_code)
            for key, en_val in to_translate.items():
                try:
                    result = translator.translate(en_val)
                    d[key] = result
                    print(f"{key}={result}", end=' ', flush=True)
                    time.sleep(0.3)  # rate limit
                except Exception as e:
                    print(f"FAIL({key}:{e})", end=' ', flush=True)
                    time.sleep(2)
        except Exception as e:
            print(f"TRANSLATOR FAIL: {e}")
            continue
        
        save_json(path, d)
        print(" OK")
        time.sleep(1)  # between languages

if __name__ == '__main__':
    main()
