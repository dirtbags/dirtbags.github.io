PLAIN += tools
COPY += tools/zar tools/zdec tools/zpex tools/bubblebabble.c

$(DESTDIR)/tools/%: /home/neale/bin/%
	@mkdir -p $(@D)
	cp $< $@

$(DESTDIR)/tools/%: /home/neale/src/c/%
	@mkdir -p $(@D)
	cp $< $@
