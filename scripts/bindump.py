import sys

input_file = sys.argv[1]
var_name = sys.argv[2]
out_file = sys.argv[3]

with open(input_file, 'rb') as f:
    data = f.read()

with open(out_file, 'w') as f:
    print('#include <stddef.h>', file=f)
    print('#include <stdint.h>', file=f)
    print('#ifdef _WIN32', file=f)
    print('__declspec(dllexport)', file=f)
    print('#endif', file=f)
    print(f'uint8_t {var_name}[] = {{', file=f)
    print(', '.join(f'0x{b:02x}' for b in data), file=f)
    print(f'}};', file=f)
    print(f'size_t {var_name}_len = {len(data)};', file=f)