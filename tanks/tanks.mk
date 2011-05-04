PLAIN += tanks
TARGETS += $(DESTDIR)/tanks/tanks.js

TANKS_GIT_DIR = $(HOME)/projects/tanks


.DELETE_ON_ERROR:

$(DESTDIR)/tanks/tanks.js: $(TANKS_GIT_DIR)/refs/heads/master
	git --git-dir=$(TANKS_GIT_DIR) show HEAD:$(@F) > $@
