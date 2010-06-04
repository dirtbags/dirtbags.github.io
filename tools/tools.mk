PLAIN += tools
COPY += tools/zar tools/zdec tools/zpex

$(DESTDIR)/tools/%: /home/neale/bin/%
	@mkdir -p $(@D)
	cp $< $@
