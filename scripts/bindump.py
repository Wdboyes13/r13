import sys

input_file = sys.argv[1]
var_name = sys.argv[2]

with open(input_file, 'rb') as f:
    data = f.read()

print('#include <stddef.h>')
print('#include <stdint.h>')
print(f'uint8_t {var_name}[] = {{')
print(', '.join(f'0x{b:02x}' for b in data))
print(f'}};')
print(f'size_t {var_name}_len = {len(data)};')