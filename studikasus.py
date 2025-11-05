import numpy as np

celsius = np.array([22, 21, 20, 29, 32, 19, 15, 12, 19, 20])

fahrenheit = (celsius * 9/5) + 32

print("sebelum diubah ke fahrenheit: ", celsius)
print("setelah diubah ke farenheit: ", fahrenheit)

input_1 = int(input("Masukkan bilangan 1: "))
input_2 = int(input("Masukkan bilangan 2: "))
hasil = input_1 + input_2

print("Hasil pertambahannya adalah: ", hasil)