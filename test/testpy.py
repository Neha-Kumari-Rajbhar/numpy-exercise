import mynumpy 

a = mynumpy.Array([1, 2, 3])
b = mynumpy.Array([4, 5, 6])
print(a.add(b))  # [5, 7, 9]

c = mynumpy.Array([10])
print(a.add(c))  # [11, 12, 13]

d = mynumpy.Array([10, 2])
print(a.add(d))  # raises ValueError
