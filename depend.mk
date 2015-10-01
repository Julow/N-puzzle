O_FILES :=	o/srcs/main.o

LIBS_DEPEND := libftui/libftui.a

libs:
	BINDINGS=glfw make -C libftui
.PHONY: libs

o/srcs/main.o: srcs/main.cpp | o/srcs/
