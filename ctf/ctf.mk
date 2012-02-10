PLAIN += ctf
COPY += ctf/register.cgi
COPY += $(wildcard ctf/*/*.pdf)

PLAIN += ctf/*/

-include ctf/*/*.mk
