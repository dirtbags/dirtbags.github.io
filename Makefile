DESTDIR = /srv/www/dirtbags.net

TEMPLATE = template.html.m4
MDWNTOHTML = ./mdwntohtml $(TEMPLATE)

# HTML to be generated
HTML = index.html

# Things to copy
COPY += grunge.png icon.png
COPY += dirtbags.css
COPY += gitweb.cgi gitweb.css gitweb.conf gitweb.header.xml git-logo.png

# Images to scale
IMAGES += science-sm.jpg

# Directories in which %.mdwn generates %.html
PLAIN = .

# Git projects to link in
PROJECTS = tanks pytanks py-pcap

# Other targets for "make all"
TARGETS = html copy images projects $(DESTDIR)/tmp $(DESTDIR)/footer.xml

all: default

-include */*.mk

.DELETE_ON_ERROR:

$(DESTDIR)/%.html: %.mdwn $(TEMPLATE)
	@mkdir -p $(dir $@)
	$(MDWNTOHTML) < $< > $@

$(DESTDIR)/projects/%: /home/neale/projects/%
	@mkdir -p $(@D)
	ln -sf $< $@

$(DESTDIR)/%: %
	@mkdir -p $(dir $@)
	cp $< $@

$(DESTDIR)/%-sm.jpg: %.jpg
	jpegtopnm $< | pnmscale -xysize 200 200 | pnmtojpeg > $@

$(DESTDIR)/tmp:
	mkdir -p $@

$(DESTDIR)/footer.xml: $(TEMPLATE)
	awk '(/FOOT/) { a += 1; next; } (a == 1) { print; }' $< > $@


default: $(TARGETS)

MDWN = $(wildcard $(addsuffix /*.mdwn, $(PLAIN)))
HTML += $(patsubst %.mdwn, %.html, $(MDWN))

html: $(addprefix $(DESTDIR)/, $(HTML))
copy: $(addprefix $(DESTDIR)/, $(COPY))
images: $(addprefix $(DESTDIR)/, $(IMAGES))
projects: $(addprefix $(DESTDIR)/projects/, $(PROJECTS))

clean:
	rm -rf $(wildcard $(DESTDIR)/*)
