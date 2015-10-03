O_FILES :=	$(FTUI_PATH)/o/glfw/srcs/GlfwWindow.o

LIBS_DEPEND := 

libs:
.PHONY: libs



MAX_SOURCE_LEN := 19
$(FTUI_PATH)/o/glfw/srcs/GlfwWindow.o: srcs/GlfwWindow.cpp \
	| $(FTUI_PATH)/o/glfw/srcs/
