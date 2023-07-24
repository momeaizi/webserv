import sys
import time

print("Cntent-Type: text/plain\r\n", end='')
print("\r\n", end='')


while True:
    try:
        data = input()
    except :
        break
    print(data)


print("DONE!\n", end='')