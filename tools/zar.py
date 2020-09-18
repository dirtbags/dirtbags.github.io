#! /usr/bin/python3
"""zar -- Python Archiver, to get around SMTP filtering
Public Domain - 2020 September - Neale Pickett - https://dirtbags.net/

If you're reading this text in an email, someone was trying to send you a file,
and was repeatedly blocked by some filter between you and them.
They resorted to this non-standard encoding in order to get the file sent.

Save the text of this email to a file called "archive.py", and then run

    python archive.py

It will decompress the contents for you.

Please be aware that, because all sorts of filters are being circumvented,
it's highly likely there is bad stuff in here. 
You should be  very careful with the contents.
"""

import base64
import io
import os
import sys
import zipfile

### Program:

mgc = b'FNORD!'

def frob(buf):
    return bytes(b^42 for b in buf)

p = globals().get("p")
if p:
    b = frob(p)
    assert(b.startswith(mgc))
    b = b[len(mgc):]
    zf = zipfile.ZipFile(io.BytesIO(b))
    print("Extracting:")
    for m in zf.namelist():
        print("  - %s" % m)
        zf.extract(m)
else:
    for l in open(sys.argv[0]):
        if l.startswith("### Program"):
            f = io.BytesIO()
            zf = zipfile.ZipFile(f, "w", zipfile.ZIP_LZMA)
            print("### Archive contents:")
            for fn in sys.argv[1:]:
                print("# - %s" % fn)
                zf.write(fn)
            zf.close()
            b = frob(mgc + f.getvalue())
            print("p=base64.b85decode(%r)" % base64.b85encode(b))
        print(l, end='')
