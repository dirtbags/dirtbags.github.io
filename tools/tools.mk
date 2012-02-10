PLAIN += tools
COPY += tools/zar tools/zdec tools/zpex tools/bubblebabble.c
COPY += tools/xor.c tools/hd.c tools/unhex.c tools/pyesc.c

$(DESTDIR)/tools/%: /home/neale/bin/%
	@mkdir -p $(@D)
	cp $< $@

$(DESTDIR)/tools/%: /home/neale/src/c/%
	@mkdir -p $(@D)
	cp $< $@
