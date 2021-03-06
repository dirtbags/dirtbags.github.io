---
title: Being Sneaky
---

Encryption
----------

We started out talking about how encryption is used on DVDs, and what
DRM is.  That led into a discussion about DeCSS, DVD Jon, and the DMCA
(these are all terms you can look up in a search engine for more
informaiton).


Authentication
--------------

Moving on to authentication, we discussed Mary, Queen of Scots, and how
encryption is sometimes not enough if you don't also have
authentication.  It got her killed!  The "Babington Plot" which brought
her down was an example of a Man-In-The-Middle attack.


Anonymity
---------

The opposite of authentication is anonymity, which might be useful if
you don't want anyone to know you're the author of a message: like if
you're a whistleblower, exposing misconduct of your boss.  You can,
however, encrypt your authentication, and then send it anonymously.
This would be a way to have a secure authenticated communication,
without anyone in the middle knowing who sent the message.


Steganography
-------------

<table class="figure">
<tr><td>
<img src="duck.png">
<img src="stegduck.png">
</td></tr>
<caption>
One of these ducks has the Declaration of Independence
hidden in it.  Can you tell which one?
</caption>
</table>

Steganography is all about hiding information.  We used the examples of
invisible ink, or the more modern technique of hiding information in the
low-order bits of image pixel components.  That's a fancy way to say
that you change whether a red, green, or blue value is even or odd to
encode your message.  Steganography could be used in situations where
you don't want anyone to know you're even sending messages, and any or
all of the previous three techniques can be used here too.


Social Implications
-------------------

We touched on the social implications of this.  We spent a good deal of
time throughout the class talking about freedom, politics, and even the
US Constitution!  I ended things by asking everyone to think about the
downsides to having such strong techniques available for everyone to
use: child pornographers, organized crime, or seditious groups trying to
overthrow the government, can all use these powerful tools too.  Some
within law enforcement argue that these tools are too powerful for
ordinary people and should be made illegal.  What do you think?


Class Textbook
--------------

Finally, I managed to get everybody excited about the book *Little
Brother* by Cory Doctorow.  You can buy it at the bookstore, check it
out from the library, or download it [for free in many
formats](http://craphound.com/littlebrother/download/), including for
iPods, many mobile phones, and computers (PDF, HTML, plain text).  One
of the reasons that the author makes it available for free is because he
wants teenagers to read it, so please check it out.  It covers
everything we're talking about in these classes.


Interesting Links
-----------------

* [Gallery of CSS Descramblers](http://www.cs.cmu.edu/~dst/DeCSS/Gallery/)
* [Little Brother](http://craphound.com/littlebrother/)
* [Electronic Frontier Foundation](http://www.eff.org/)
* [pnmsteg](pnmsteg.py), a simple program to hide data in images