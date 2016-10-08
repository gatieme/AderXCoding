ROOT=.
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)
include $(ROOT)/Make.readme


DIRS=language


all:
	for i in $(DIRS); do \
		(cd $$i && echo "making $$i" && $(MAKE) ) || exit 1; \
	done


clean:
	for i in $(DIRS); do \
		(cd $$i && echo "cleaning $$i" && $(MAKE) clean) || exit 1; \
	done


github:
	git add -A
	git commit -m $(COMMIT_FBTERM)
	git push origin master
