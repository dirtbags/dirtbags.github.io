---
title: "Contest Tutorial: Scripting"
---

So, you've run into a problem with a task you've been asked to complete. Your boss wants you to gather information from a database. Sounds easy enough. Unfortunately, you only have 3 seconds to gather all the information before it disappears forever. How on earth are you going to be able to manually gather millions upon millions of data in a matter of 3 seconds?

The answer to your dilemma: write a simple shell script program.

What is a scripting language you ask?
===================================== 

Well, a scripting language is a programming language designed to be easy to use for everyday or administrative tasks. There are a lot of popular scripting languages out there such as PHP, Perl, and Python, but for the purposes of this tutorial, we will concentrate primarily on a scripting language known as Bourne shell.

Why did we pick Bourne as our tutorial language? 
================================================

The most notable benefit of Bourne is that it is available everywhere. Another added benefit is that while you are learning the shell, you are subsequently introduced to a lot of very useful and common command-line programs. This will help you later on when you begin to program on a much more frequent basis.

So, what's a shell?
===================

To put it simply, a shell is a command interpreter. In other words, it accepts command-line arguments given to it by the user and executes said commands. With that in mind, another interesting and useful aspect of shell is that you have the ability to put commands in a file and execute them all at once. This is known as a script. Here's a simple one: 

	#!/bin/sh
	# Simple Script

	message='Hello World'
	echo $message		# This prints 'Hello World' to the terminal

There are several things to take notice of in this very simple script. First and foremost, the first line of any script must begin with #!, followed by the name of the interpreter. In our case, our interpreter is /bin/sh. Secondly, comments begin with a hash (#) and continue to the end of the line.

The script itself is just a series of commands. You could easily have typed these commands into the terminal, however, scripts come in handy when you need to perform multiple commands that would otherwise take up a lot of time if done by hand.
Variables are first created by setting them equal to a value. Once your variable has been declared, you are then able to use the variable by including a $ in front of the variable name.

Quotes are another thing to keep in mind. There are multiple uses for quotes, and different quotes are used for different reasons. In our script, we use single quotes ('). Single quotes are used to quote whatever is inside them. Double quotes (") are used to preserve spaces and most special characters. Back-quotes, or back-ticks (\`), are used to evaluate the expression inside as a command; for instance:

    `x + y`

This can also be achieved the same way by doing, $(x + y).

Flow Control
============

sh supports several flow-control constructs, which can add power and flexibility to your scripts. We will go over a few of the more commonly used ones here.

<dl>
<dt>if</dt>
<dd>The if statement is a simple conditional. Keep in mind that spaces in sh are very important.
<pre>
if [ condition ]; then
    commands
elif [ condition ]; then
    commands
else
    commands
fi 
</pre>
</dd>
<dt>while</dt>
<dd>while loops allow the user to proceed through a set of commands until a condition is met. Much like a for loop.
<pre>
while [ condition ]; do
    commands
done
</pre>
</dd>
<dt>for</dt>
<dd>for loops iterate through a set of values until the list is exhausted.
<pre>
for var in list; do
    commands
done
</pre>
</dd>
</dl>

Example
=======

So, let's walk through an example. On the server there is a random number generator. We need to first be able to connect to that server. How do we do that? 

First we will enter the following commands into the terminal:
	tcpsvd 0 4444 ./server &
This lines will allow you to connect to the server and start the random number generator so you can start performing opeartions.

Now that we've connected, let's try to write a simple script that will add 1 to the number. We notice at first, that if we try to do it by hand, we may not succeed. The server appears to timeout at a certain amount of time. This is where a script comes in handy.

Open up a new file in your favorite editor such as Vim, gedit, emacs, etc.

Let's start off our script as such:

	#!/bin/sh

	# read the number given by the server and save it in a variable:
	read rand

	# take the value of rand and add 1 to it, then save the new value into answer
	answer=$(expr $rand + 1) 

	# to echo back the value of answer to the server
	echo $answer

	# Read the server's answer and display it on the screen
	read stuff
	echo $stuff 1>&2

Now, save your file and run this line:

	socat TCP:localhost:4444 EXEC:./client (or whatever you named your file)

If you did everything right, then you will get a response of 'Good Job!'. If you did something incorrectly, then you will get the response, 'OH NO!! Wrong answer!', and you will have to try again.

Question
========

Connect to the server using TCP, and then write a script that squares the number given to you. Once you have completed this, and done it corectly, you will receive your token to put into the answer box below.

<p id="debug"></p>
<p id="a">Enable JavaScript if you'd like to check your answer.</p>
<script type="application/javascript" src="tutorial.js"></script>
<script type="application/javascript">ans("a", 54533);</script>
