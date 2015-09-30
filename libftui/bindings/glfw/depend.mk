O_FILES :=	o/srcs/GlfwWindow.o

LIBS_DEPEND := 

libs:
.PHONY: libs

o/srcs/GlfwWindow.o: srcs/GlfwWindow.cpp \
	../../include/ftui/glfw/GlfwWindow.hpp | o/srcs/
