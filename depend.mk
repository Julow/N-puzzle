O_FILES :=	o/srcs/main.o

LIBS_DEPEND := libftui/libftui.a

libs:
	BINDINGS=glfw make -C libftui
.PHONY: libs



MAX_SOURCE_LEN := 13
o/srcs/main.o: srcs/main.cpp libftui/include/ft/assert.hpp \
	libftui/include/ftui/glfw/GlfwWindow.hpp libftui/include/ftui/libftui.hpp \
	libftui/include/ftui/glfw/IGlfwEventListener.hpp \
	libftui/include/ft/utils.hpp libftui/include/ft/Vec.hpp \
	libftui/include/ftui/Activity.hpp libftui/include/ftui/DefaultEventBox.hpp \
	libftui/include/ftui/EventBox.hpp libftui/include/ftui/EventParams.hpp \
	libftui/include/ftui/IEventBox.hpp libftui/include/ftui/IEventParams.hpp \
	libftui/include/ftui/IViewHolder.hpp \
	libftui/include/ftui/templates/Activity.tpp | o/srcs/
