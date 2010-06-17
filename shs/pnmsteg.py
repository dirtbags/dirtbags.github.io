#! /usr/bin/python

import sys

plaintext = open(sys.argv[1])

# Copy first three lines verbatim
sys.stdout.write(sys.stdin.readline())
sys.stdout.write(sys.stdin.readline())
sys.stdout.write(sys.stdin.readline())

while True:
    medium = sys.stdin.read(8)
    if len(medium) < 8:
        sys.stdout.write(medium)
        break

    message = plaintext.read(1)
    if not message:
        sys.stdout.write(medium)
        continue

    for i in range(8):
        j = 8 - i
        bit = (ord(message) & (1 << j)) >> j
        mask = 0xfe | bit
        out = chr(ord(medium[i]) & mask)
        sys.stdout.write(out)
