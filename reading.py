import sys

while True:
    line = sys.stdin.readline()
    if not line:
        break  # End-of-file signal received

    # Process the input line here
    print("Input:", line.strip())
print("FINISHED!")