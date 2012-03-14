TF4 = ctf/2012-02-TF4

TF4_PHOTOS = $(wildcard $(TF4)/photos/IMGP*.jpg)
TF4_IMAGES += $(patsubst %.jpg, %-800.jpg, $(TF4_PHOTOS))
TF4_IMAGES += $(patsubst %.jpg, %-100.jpg, $(TF4_PHOTOS))

IMAGES += $(TF4_IMAGES) $(TF4_PHOTOS)
HTML += $(TF4)/photos/index.html

COPY += $(TF4)/scoreboard.html $(TF4)/scoreboard.js $(TF4)/ctf.css $(TF4)/smoke.jpg

$(DESTDIR)/$(TF4)/index.html: images album.sh
	./album.sh $(TF4)/photos "Tracer Fire 4" > $@
