TF4_PHOTOS = $(wildcard ctf/2012-02-TF4/photos/IMGP*.jpg)
TF4_IMAGES += $(patsubst %.jpg, %-800.jpg, $(TF4_PHOTOS))
TF4_IMAGES += $(patsubst %.jpg, %-100.jpg, $(TF4_PHOTOS))

IMAGES += $(TF4_IMAGES) $(TF4_PHOTOS)
HTML += ctf/2012-02-TF4/photos/index.html

$(DESTDIR)/ctf/2012-02-TF4/photos/index.html: images album.sh
	./album.sh ctf/2012-02-TF4/photos "Tracer Fire 4" > $@
