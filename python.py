#!/usr/bin/env python3
import re
import pathlib

# Map alternative operators to normal symbols
OPS = {
    "and": "&&",
    "or": "||",
    "not": "!",
    "xor": "^",
    "bitand": "&",
    "bitor": "|",
    "compl": "~",
    "and_eq": "&=",
    "or_eq": "|=",
    "xor_eq": "^=",
    "not_eq": "!=",
}

# File extensions to process
EXTS = [".cpp", ".cc", ".cxx", ".hpp", ".hxx", ".h"]

# Build a regex pattern that matches any operator as a whole word
pattern = re.compile(r'\b(' + '|'.join(OPS.keys()) + r')\b')

def process_file(path):
    code = path.read_text(encoding="utf-8")
    # Remove #include <ciso646> lines
    code = re.sub(r'^[ \t]*#include[ \t]*<ciso646>.*$', '', code, flags=re.MULTILINE)

    result = []
    i = 0
    in_block_comment = False
    in_string = False
    string_char = ''

    while i < len(code):
        if in_string:
            result.append(code[i])
            if code[i] == string_char and code[i-1] != '\\':
                in_string = False
            i += 1
        elif in_block_comment:
            result.append(code[i])
            if code[i:i+2] == '*/':
                in_block_comment = False
                result.append(code[i+1])
                i += 2
            else:
                i += 1
        else:
            if code[i:i+2] == '//':
                # single-line comment, copy until newline
                end = code.find('\n', i)
                if end == -1:
                    result.append(code[i:])
                    break
                else:
                    result.append(code[i:end])
                    i = end
            elif code[i:i+2] == '/*':
                in_block_comment = True
                result.append('/*')
                i += 2
            elif code[i] in ('"', "'"):
                in_string = True
                string_char = code[i]
                result.append(code[i])
                i += 1
            else:
                # find the next operator as a whole word
                match = pattern.match(code, i)
                if match:
                    op = match.group(0)
                    result.append(OPS[op])
                    i += len(op)
                else:
                    result.append(code[i])
                    i += 1

    path.write_text(''.join(result), encoding="utf-8")


# Process recursively
for ext in EXTS:
    for file in pathlib.Path('.').rglob(f'*{ext}'):
        process_file(file)
