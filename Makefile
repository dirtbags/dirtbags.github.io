DESTDIR = /srv/www/dirtbags.net

TEMPLATE = template.m4
MDWNTOHTML = ./mdwntohtml $(TEMPLATE)

# HTML to be generated
HTML = index.html

# Things to copy
COPY += grunge.png icon.png
COPY += dirtbags.css
#COPY += gitweb.cgi gitweb.css gitweb.conf gitweb.header.xml git-logo.png
COPY += g.cgi cgit.css cgitrc

# Images to scale
IMAGES += science-200.jpg

# Directories in which %.mdwn generates %.html
PLAIN = .

# Other targets for "make all"
TARGETS = html copy images $(DESTDIR)/projects $(DESTDIR)/footer.html

all: default

-include */*.mk

.DELETE_ON_ERROR:

$(DESTDIR)/%.html: %.mdwn $(TEMPLATE)
	@mkdir -p $(dir $@)
	$(MDWNTOHTML) < $< > $@

$(DESTDIR)/projects: /home/neale/projects
	ln -sf $< $@

$(DESTDIR)/%: %
	@mkdir -p $(dir $@)
	cp $< $@

$(DESTDIR)/%-200.jpg: %.jpg
	@mkdir -p $(dir $@)
	jpegtopnm $< | pnmscale -xysize 200 200 | pnmtojpeg > $@

$(DESTDIR)/%-800.jpg: %.jpg
	@mkdir -p $(dir $@)
	jpegtopnm $< | pnmscale -xysize 800 800 | pnmtojpeg > $@

$(DESTDIR)/%-100.jpg: %.jpg
	@mkdir -p $(dir $@)
	jpegtopnm $< | pnmscale -xysize 100 100 | pnmtojpeg > $@

$(DESTDIR)/tmp:
	mkdir -p $@

$(DESTDIR)/footer.html: $(TEMPLATE)
	awk '(/FOOT/) { a += 1; next; } (a == 1) { print; }' $< > $@

$(DESTDIR)/g.cgi: g.cgi.c
	$(CC) -o $@ $<

default: $(TARGETS)

MDWN = $(wildcard $(addsuffix /*.mdwn, $(PLAIN)))
HTML += $(patsubst %.mdwn, %.html, $(MDWN))

html: $(addprefix $(DESTDIR)/, $(HTML))
copy: $(addprefix $(DESTDIR)/, $(COPY))
images: $(addprefix $(DESTDIR)/, $(IMAGES))
projects: $(addprefix $(DESTDIR)/projects/, $(PROJECTS))

clean:
	rm -rf $(wildcard $(DESTDIR)/*)
