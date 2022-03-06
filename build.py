#!/usr/bin/env python3

import subprocess
import sys

buck_path = "build/buck/bin/buck"
main_project = "cg"

def main():
    project = main_project
    output = subprocess.run([buck_path, "build", "--show-output", f":{project}"], capture_output=True)
    print(f"{output}")
    print(f"-------")
    print(f"-------")
    print(f"running...\n")
    build = output.stdout.decode("utf8").strip().split()[-1]
    output = subprocess.run([build], capture_output=True)
    print(f"{output}")
    print(f"-------")
    print(f"opening...\n")
    bmp = output.stdout.decode("utf8").strip().split()[-1]
    subprocess.run(["open", bmp])
    return 0

if __name__ == "__main__":
    main()
