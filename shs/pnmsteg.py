#! /usr/bin/python

import sys

plaintext = open(sys.argv[1], 'rb')

# Copy first three lines verbatim
sys.stdout.buffer.write(sys.stdin.buffer.readline())
sys.stdout.buffer.write(sys.stdin.buffer.readline())
sys.stdout.buffer.write(sys.stdin.buffer.readline())

while True:
    medium = sys.stdin.buffer.read(8)
    if len(medium) < 8:
        sys.stdout.buffer.write(medium)
        break

    message = plaintext.read(1)
    if not message:
        sys.stdout.buffer.write(medium)
        continue

    for i in range(8):
        j = 8 - i
        bit = (ord(message) & (1 << j)) >> j
        mask = 0xfe | bit
        out = bytes(medium[i] & mask)
        sys.stdout.buffer.write(out)
