Title: CTF Tutorial: File carving

Begin with the following image:

![carving image](carving-ex.jpg)

Since the browser is able to display this image, you know that it is a
valid JPEG file.  Further, there are no obvious encoding errors.  There
are a few immediate possibilities for analysis:

* Steganography, such as steghide
* Information in the headers
* Information after the JPEG end-of-file marker

Since the last two can be detected with a simple hex dump, we will start
with this.  In Windows, open the file in a binary editor.  Under Unix or
MacOS, run (at a terminal prompt, represented by `$` in our examples):

    $ xxd carving-ex.jpg | less

Look at the beginning and end of the file, initially for English text.
After the `JFIF` tag, there is some comment information about software
used to create the file, and some initialization strings which show up
as the alphabet.  There is no obvious hidden information at the
beginning of the file.  At the end, however, are some strings which
look like file names.

    00008e20: 3fff d950 4b03 0414 0000 0008 0088 6c0c  ?..PK.........l.
    00008e30: 3f18 f066 802d 0000 0032 0000 000a 001c  ?..f.-...2......
    00008e40: 0061 6e73 7765 722e 7478 7455 5409 0003  .answer.txtUT...
    00008e50: 9f72 454e 126d 454e 7578 0b00 0104 8813  .rEN.mENux......
    00008e60: 0000 0488 1300 000b c9c8 2c56 00a2 acd2  ..........,V....
    00008e70: e212 85c4 3c85 d48a c4dc 829c 546b 8592  ....<.......Tk..
    00008e80: 8cd4 a254 904c 5e3e 50bc b83c b548 0124  ...T.L^>P..<.H.$


Also notice the string `PK`.  This is the initials of [Phil
Katz](http://en.wikipedia.org/wiki/Phil_Katz), creator of the zip file
format.  Immediately preceding `PK` is the hex value `ffd9`, the
end-of-file marker for JPEG files.  

At this point, we have determined that the JPEG file has a zip file
appended to it.  Our task is now to strip the JPEG file off of the
beginning and uncompress the zip file.  There are many ways to
accomplish this task: this tutorial will focus on using the `dd` program
available in Unix or MacOS.

`dd` supports a `skip=` option, which will discard a number of
characters from the beginning of a file, but it only takes values in
decimal.  We want to skip everything up to the `PK`, which, according to
the hex dump output, is at offset 00008e23.  I like to use the `printf`
command in Unix to do quick base conversions:

    $ printf '%d\n' 0x00008e23
    36387

Now we know what offset to use.  We tell `dd` to use a block size of 1,
and skip 36387 blocks.

    $ dd if=carving-ex.jpg bs=1 skip=36387 of=foo.zip

We can now unzip `foo.zip`, and read the resulting `answer.txt`.

Question
========

Use the same technique on this image to obtain the answer for this page.

![carving image](carving.jpg)

<p id="a">Enable JavaScript if you'd like to check your answer.</p>
<script type="application/javascript" src="tutorial.js"></script>
<script type="application/javascript">ans("a", 48922);</script>
