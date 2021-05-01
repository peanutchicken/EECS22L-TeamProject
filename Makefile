# Root level makefile for chessgame project
# This allows make to be called from the top level project directory, and it will compile everything
# in ./src/

# subdirectories (obviously)
SUBDIRS = src

.PHONY: subdirs $(SUBDIRS)

subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@
