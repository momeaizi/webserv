import sys
import time

print("Cntent-Type: text/plain\r\n", end='')
print("\r\n", end='')


time.sleep(2.4)
while True:
    try:
        data = input()
    except :
        break
    print(data)


print("DONE!\n", end='')