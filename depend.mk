O_FILES :=	o/srcs/GlCanvasHolder.o o/srcs/Tiles.o o/srcs/main.o \
			o/srcs/solver/Grid.o o/srcs/solver/OCamlBinding.o

LIBS_DEPEND := libftui/libftui.a

libs:
	make -C libftui
.PHONY: libs



MAX_SOURCE_LEN := 28
o/srcs/GlCanvasHolder.o: srcs/GlCanvasHolder.cpp include/GlCanvasHolder.hpp \
	libftui/include/ft/Color.hpp libftui/include/ft/Rect.hpp \
	libftui/include/ft/Vec.hpp libftui/include/ft/assert.hpp \
	libftui/include/ft/templates/Vec2.tpp \
	libftui/include/ft/templates/Vec3.tpp \
	libftui/include/ft/templates/Vec4.tpp libftui/include/ftui/Canvas.hpp \
	libftui/include/ftui/libftui.hpp include/gl.hpp \
	libftui/include/ft/utils.hpp | o/srcs/
o/srcs/Tiles.o: srcs/Tiles.cpp include/tiles/Tiles.hpp \
	libftui/include/ft/Vec.hpp libftui/include/ft/templates/Vec2.tpp \
	libftui/include/ft/templates/Vec3.tpp \
	libftui/include/ft/templates/Vec4.tpp include/gl.hpp | o/srcs/
o/srcs/main.o: srcs/main.cpp libftui/include/ft/utils.hpp \
	include/config_window.hpp include/ftce/math.hpp libftui/include/ft/Vec.hpp \
	libftui/include/ft/templates/Vec2.tpp \
	libftui/include/ft/templates/Vec3.tpp \
	libftui/include/ft/templates/Vec4.tpp libftui/include/ft/assert.hpp \
	libftui/include/ftui/Activity.hpp libftui/include/ftui/DefaultEventBox.hpp \
	libftui/include/ftui/EventBox.hpp libftui/include/ftui/EventParams.hpp \
	libftui/include/ftui/IEventBox.hpp libftui/include/ftui/IEventParams.hpp \
	libftui/include/ftui/IViewHolder.hpp libftui/include/ftui/libftui.hpp \
	libftui/include/ftui/templates/Activity.tpp \
	libftui/include/ftui/templates/EventBox.tpp libftui/include/ftui/AView.hpp \
	libftui/include/ft/Color.hpp libftui/include/ft/Rect.hpp \
	libftui/include/ftui/ALayout.hpp libftui/include/ftui/ASolidView.hpp \
	libftui/include/ftui/Canvas.hpp libftui/include/ftlua/ftlua.hpp \
	libftui/include/ftlua/templates/ftlua_caller.tpp \
	libftui/include/ftlua/templates/ftlua_handler.tpp include/tiles/Tiles.hpp \
	include/GlCanvasHolder.hpp include/gl.hpp include/Grid.hpp \
	include/ISolverListener.hpp include/OCamlBinding.hpp | o/srcs/
o/srcs/solver/Grid.o: srcs/solver/Grid.cpp include/Grid.hpp | o/srcs/solver/
o/srcs/solver/OCamlBinding.o: srcs/solver/OCamlBinding.cpp include/Grid.hpp \
	include/ISolverListener.hpp include/OCamlBinding.hpp \
	libftui/include/ft/Vec.hpp libftui/include/ft/templates/Vec2.tpp \
	libftui/include/ft/templates/Vec3.tpp \
	libftui/include/ft/templates/Vec4.tpp | o/srcs/solver/
