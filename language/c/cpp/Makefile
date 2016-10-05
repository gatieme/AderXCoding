ROOT=../../..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)


# director config
DIRS=	add    sample apple cpp_link_c c_link_cpp		\
		c_link_cpp_func c_link_cpp_overload_func   		\
		c_link_cpp_mem_func c_link_cpp_class

ECHO_add="first和second的add函数测试程序"
ECHO_sample="简单的测试程序"
ECHO_apple="C语言链接C++库的完整测试程序(wrapper方法和handle方法)"
ECHO_cpp_link_c="C++链接C的函数"
ECHO_c_link_cpp="C语言链接C++的函数"
ECHO_c_link_cpp_func="C语言链接C++的基本函数"
ECHO_c_link_cpp_overload_func="C语言链接C++的重载函数"
ECHO_c_link_cpp_mem_func="C语言链接C++的类成员函数"
ECHO_c_link_cpp_class="C语言链接C++的完整类接口"


MAKE_DIR=make -C

SUBDIRS=$(DIRS)

.PHONY:all $(SUBDIRS)

#all: $(SUBDIRS)

#$(SUBDIRS):
		$(MAKE_DIR) $@

all	:
	for i in $(DIRS); do \
		(cd $$i && echo "making $$i" && echo $(ECHO_$(i)) && $(MAKE) ) || exit 1; \
	done

clean:
	for i in $(DIRS); do \
		(cd $$i && echo "cleaning $$i" && $(MAKE) clean) || exit 1; \
	done

install :
#	for i in $(DIRS); do \
#		(cd $$i && echo "install $$i" && $(MAKE) install) || exit 1; \
#	done
	cp $(INJECTOR)/memInjector $(BIN)/memInjector
	cp $(ENGINE)/memoryEngine.ko $(BIN)/memoryEngine.ko

github:
	make clean
	cd $(ROOT)/..
	git add -A
	git commit -m $(GITHUB_COMMIT)
	git push origin master

insmod:
	cd $(ENGINE)&& make insmod

reinsmod:
	cd $(ENGINE)&& make reinsmod
