O_FILES :=	o/srcs/main.o

LIBS_DEPEND := libftui/libftui.a

libs:
	make -C libftui
.PHONY: libs

o/srcs/main.o: srcs/main.c | o/srcs/
