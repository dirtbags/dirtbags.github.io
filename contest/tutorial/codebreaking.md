---
title: "Contest Tutorial: Codebreaking"
---

Early cryptography (before WWI) is fun to play with, and can often be
worked out with pencil and paper.  This tutorial will focus on the
Monoalphabetic Substitution Cipher, which is a fancy name for the
[cryptograms](http://en.wikipedia.org/wiki/Cryptogram) present in many
Sunday newspapers in the US.

Begin with the following ciphertex:

    GUVF VF GUR FHOFGVGHGVBA PVCURE.  TERNG WBO OERNXVAT VG.

This tutorial will use the `tr` program in Unix and MacOS to apply
transformations.  First, assign the text to a variable, and perform a
pass-through translation:

    $ ctxt="GUVF VF GUR FHOFGVGHGVBA PVCURE.  TERNG WBO OERNXVAT VG."
    $ echo $ctxt | tr '' ''
    GUVF VF GUR FHOFGVGHGVBA PVCURE. TERNG WBO OERNXVAT VG.

To approach cracking a substitution cipher, it helps to know a few facts
about the English language:

* The most frequent letters in English are "ETAOIN SHRDLU" from most to
  less frequent.
* The most frequent two-letter combinations in English are "th", "er",
  "on", "an", "re", and "he".
* The most frequent three-letter combinations in English are "the", "and",
  "tha", and "ent".

A cursory glance at the ciphertext shows two "GU"s, one of which is a
three-letter word beginning with "GU".  Since "th" and "the" are the
most frequent bi- and tri-grams, we will guess that "GUR" corresponds to
"the":

    $ echo $ctxt | tr 'GUR' 'the'
    thVF VF the FHOFtVtHtVBA PVCheE. TEeNt WBO OEeNXVAT Vt.

Next we will guess that "thVF" should be "this", and "VF" should be "is":

    $ echo $ctxt | tr 'GURVF' 'theis'
    this is the sHOstitHtiBA PiCheE. TEeNt WBO OEeNXiAT it.

The longest word is now over half decoded.  Use the `grep` program to
search the dictionary for words which fit this pattern:

    $ grep '^s..stit.ti..$' /usr/share/dict/words
    substituting
    substitution
    substitutive

We'll be conservative and guess at just a few letters:

    $ echo $ctxt | tr 'GURVFHO' 'theisub'
    this is the substitutiBA PiCheE. TEeNt WBb bEeNXiAT it.

Now we have to start making more wild guesses.  Could the first sentence
say "this is the substitution cipher"?  Let's try that and see what
happens to the rest of the text:

    $ echo $ctxt | tr 'GURVFHOBAPCE' 'theisuboncpr'
    this is the substitution cipher. TreNt Wob breNXinT it.

Now let's try `grep` on `breNXinT`:

    $ grep '^bre..in.$' /usr/share/dict/words
    breading
    breaking
    breaming
    breeding
    breezing

We're already guessing the plaintext has something to do with ciphers,
and "breaking" seems like the most appropriate word in that context, so
let's guess that:

    $ echo $ctxt | tr 'GURVFHOBAPCENXT' 'theisuboncprakg'
    this is the substitution cipher. great Wob breaking it.

It's a good sign that the word `great` appeared in a location we weren't
working on.  We only have one letter left, and at this point it's almost
irrelevant what letter that is.  You can use `grep` to see
possibilities, if you like:

    $ grep '^.ob$' /usr/share/dict/words



Question
========

SZG AHDS TOG BHD STT GHDI.  MHO ITQ QDG YVGPQGOMI HOHAIDND HOU BTVU ANDS FHSMZNOC ST UNDMTEGV SZHS SZG HODBGV ND LHDFNOG?

<p id="a">Enable JavaScript if you'd like to check your answer.</p>
<script type="application/javascript" src="tutorial.js"></script>
<script type="application/javascript">ans("a", 48844);</script>
