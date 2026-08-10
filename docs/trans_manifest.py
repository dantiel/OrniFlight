#!/usr/bin/env python3
"""Translate manifest_body by splitting into sub-500-char chunks."""
import json, os, re
from translate import Translator

os.chdir(os.path.dirname(os.path.abspath(__file__)))

en = json.load(open('_lang/en.json', encoding='utf-8'))
text = en['manifest_body']

# Split into sentences
sentences = re.split(r'(?<=[.!?])\s+', text)

# Group into chunks under 480 chars
chunks = []
current = ''
for s in sentences:
    if len(current) + len(s) + 1 <= 480:
        current = (current + ' ' + s).strip()
    else:
        if current:
            chunks.append(current)
        current = s
if current:
    chunks.append(current)

print(f'Split into {len(chunks)} chunks:')
for i, c in enumerate(chunks):
    print(f'  Chunk {i+1}: {len(c)} chars')

LANG_MAP = {
    'ja': 'ja', 'fr': 'fr', 'es': 'es', 'ko': 'ko',
    'zh_CN': 'zh-CN', 'ru': 'ru', 'it': 'it', 'pt': 'pt',
    'ca': 'ca', 'gl': 'gl', 'hr': 'hr', 'id': 'id',
    'lv': 'lv', 'sv': 'sv'
}

for code, provider_code in LANG_MAP.items():
    path = f'_lang/{code}.json'
    d = json.load(open(path, encoding='utf-8'))
    
    if d.get('manifest_body', '') != en['manifest_body']:
        print(f'{code}: already translated, skip')
        continue
    
    print(f'{code}: translating manifest_body in {len(chunks)} chunks...')
    translator = Translator(from_lang='en', to_lang=provider_code)
    
    translated_chunks = []
    for i, chunk in enumerate(chunks):
        try:
            result = translator.translate(chunk)
            translated_chunks.append(result)
            print(f'  Chunk {i+1}/{len(chunks)}: OK ({len(result)} chars)')
        except Exception as e:
            print(f'  Chunk {i+1}/{len(chunks)}: FAILED - {e}')
            translated_chunks.append(chunk)  # fallback
    
    d['manifest_body'] = ' '.join(translated_chunks)
    json.dump(d, open(path, 'w', encoding='utf-8'), indent=2, ensure_ascii=False)
    print(f'  Saved {path} ({len(d["manifest_body"])} chars total)')

print('\nDone.')
