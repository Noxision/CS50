from __future__ import print_function
import cs50

height = 0

while height < 1 or height > 23:
    print("height: ")
    height = cs50.get_int()

for i in range(1, height+1):
    j = height - i
    k = i
    while j > 0:
        print(" ", end="")
        j = j-1

    while k > 0:
        print("#", end="")
        k = k-1

    print("#")
    