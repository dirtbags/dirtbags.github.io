PLAIN += shs
COPY += shs/duck.png shs/stegduck.png shs/pnmsteg.py

$(DESTDIR)/shs/duck.png: shs/duck.pnm
	pnmtopng $< > $@

$(DESTDIR)/shs/stegduck.png: shs/duck.pnm shs/pnmsteg.py shs/declaration.txt
	shs/pnmsteg.py shs/declaration.txt < $< | pnmtopng > $@
