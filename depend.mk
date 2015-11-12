O_FILES :=	o/srcs/GlCanvasHolder.o o/srcs/Grid.o o/srcs/Main.o \
			o/srcs/OCamlBinding.o o/srcs/PickState.o o/srcs/Tiles.o \
			o/srcs/ftlua_extend.o

LIBS_DEPEND := libftui/libftui.a

libs:
	make -C libftui
.PHONY: libs



MAX_SOURCE_LEN := 23
o/srcs/GlCanvasHolder.o: srcs/GlCanvasHolder.cpp include/GlCanvasHolder.hpp \
	libftui/ft/public/ft/Color.hpp libftui/ft/public/ft/Rect.hpp \
	libftui/ft/public/ft/Vec.hpp libftui/ft/public/ft/assert.hpp \
	libftui/ft/public/ft/templates/Rect.tpp \
	libftui/ft/public/ft/templates/Vec2.tpp \
	libftui/ft/public/ft/templates/Vec3.tpp \
	libftui/ft/public/ft/templates/Vec4.tpp libftui/ft/public/ft/utils.hpp \
	libftui/ftlua/public/ftlua/ftlua.hpp \
	libftui/ftlua/public/ftlua/templates/ftlua_caller.tpp \
	libftui/ftlua/public/ftlua/templates/ftlua_handler.tpp \
	libftui/ftui/public/ftui/Canvas.hpp libftui/ftui/public/ftui/libftui.hpp \
	libftui/liblua/public/liblua.hpp include/gl.hpp | o/srcs/
o/srcs/Grid.o: srcs/Grid.cpp include/Grid.hpp libftui/ft/public/ft/Rect.hpp \
	libftui/ft/public/ft/Vec.hpp libftui/ft/public/ft/templates/Rect.tpp \
	libftui/ft/public/ft/templates/Vec2.tpp \
	libftui/ft/public/ft/templates/Vec3.tpp \
	libftui/ft/public/ft/templates/Vec4.tpp libftui/ft/public/ft/utils.hpp \
	| o/srcs/
o/srcs/Main.o: srcs/Main.cpp libftui/ft/public/ft/Rect.hpp \
	libftui/ft/public/ft/Vec.hpp libftui/ft/public/ft/templates/Rect.tpp \
	libftui/ft/public/ft/templates/Vec2.tpp \
	libftui/ft/public/ft/templates/Vec3.tpp \
	libftui/ft/public/ft/templates/Vec4.tpp libftui/ft/public/ft/utils.hpp \
	include/GlCanvasHolder.hpp include/Grid.hpp include/ISolverListener.hpp \
	include/IState.hpp include/Main.hpp include/OCamlBinding.hpp \
	include/gl.hpp libftui/ft/public/ft/Color.hpp \
	libftui/ft/public/ft/assert.hpp libftui/ftlua/public/ftlua/ftlua.hpp \
	libftui/ftlua/public/ftlua/templates/ftlua_caller.tpp \
	libftui/ftlua/public/ftlua/templates/ftlua_handler.tpp \
	libftui/ftui/public/ftui/Activity.hpp libftui/ftui/public/ftui/Canvas.hpp \
	libftui/ftui/public/ftui/DefaultEventBox.hpp \
	libftui/ftui/public/ftui/EventBox.hpp \
	libftui/ftui/public/ftui/EventParams.hpp \
	libftui/ftui/public/ftui/IEventBox.hpp \
	libftui/ftui/public/ftui/IEventParams.hpp \
	libftui/ftui/public/ftui/IViewHolder.hpp \
	libftui/ftui/public/ftui/libftui.hpp \
	libftui/ftui/public/ftui/templates/Activity.tpp \
	libftui/ftui/public/ftui/templates/DefaultEventBox.tpp \
	libftui/ftui/public/ftui/templates/EventBox.tpp \
	libftui/liblua/public/liblua.hpp include/config_window.hpp \
	include/ftce/math.hpp include/PickState.hpp include/tiles/Tiles.hpp \
	include/ftlua_extend.hpp | o/srcs/
o/srcs/OCamlBinding.o: srcs/OCamlBinding.cpp include/Grid.hpp \
	include/ISolverListener.hpp include/OCamlBinding.hpp \
	libftui/ft/public/ft/Rect.hpp libftui/ft/public/ft/Vec.hpp \
	libftui/ft/public/ft/templates/Rect.tpp \
	libftui/ft/public/ft/templates/Vec2.tpp \
	libftui/ft/public/ft/templates/Vec3.tpp \
	libftui/ft/public/ft/templates/Vec4.tpp libftui/ft/public/ft/utils.hpp \
	| o/srcs/
o/srcs/PickState.o: srcs/PickState.cpp include/GlCanvasHolder.hpp \
	include/Grid.hpp include/ISolverListener.hpp include/IState.hpp \
	include/Main.hpp include/OCamlBinding.hpp include/PickState.hpp \
	include/gl.hpp include/tiles/Tiles.hpp libftui/ft/public/ft/Color.hpp \
	libftui/ft/public/ft/Rect.hpp libftui/ft/public/ft/Vec.hpp \
	libftui/ft/public/ft/assert.hpp libftui/ft/public/ft/templates/Rect.tpp \
	libftui/ft/public/ft/templates/Vec2.tpp \
	libftui/ft/public/ft/templates/Vec3.tpp \
	libftui/ft/public/ft/templates/Vec4.tpp libftui/ft/public/ft/utils.hpp \
	libftui/ftlua/public/ftlua/ftlua.hpp \
	libftui/ftlua/public/ftlua/templates/ftlua_caller.tpp \
	libftui/ftlua/public/ftlua/templates/ftlua_handler.tpp \
	libftui/ftui/public/ftui/Activity.hpp libftui/ftui/public/ftui/Canvas.hpp \
	libftui/ftui/public/ftui/DefaultEventBox.hpp \
	libftui/ftui/public/ftui/EventBox.hpp \
	libftui/ftui/public/ftui/EventParams.hpp \
	libftui/ftui/public/ftui/IEventBox.hpp \
	libftui/ftui/public/ftui/IEventParams.hpp \
	libftui/ftui/public/ftui/IViewHolder.hpp \
	libftui/ftui/public/ftui/libftui.hpp \
	libftui/ftui/public/ftui/templates/Activity.tpp \
	libftui/ftui/public/ftui/templates/DefaultEventBox.tpp \
	libftui/ftui/public/ftui/templates/EventBox.tpp \
	libftui/liblua/public/liblua.hpp include/config_window.hpp \
	include/ftce/math.hpp | o/srcs/
o/srcs/Tiles.o: srcs/Tiles.cpp include/tiles/Tiles.hpp \
	libftui/ft/public/ft/Vec.hpp libftui/ft/public/ft/templates/Vec2.tpp \
	libftui/ft/public/ft/templates/Vec3.tpp \
	libftui/ft/public/ft/templates/Vec4.tpp include/gl.hpp | o/srcs/
o/srcs/ftlua_extend.o: srcs/ftlua_extend.cpp libftui/ft/public/ft/Rect.hpp \
	libftui/ft/public/ft/Vec.hpp libftui/ft/public/ft/assert.hpp \
	libftui/ft/public/ft/templates/Rect.tpp \
	libftui/ft/public/ft/templates/Vec2.tpp \
	libftui/ft/public/ft/templates/Vec3.tpp \
	libftui/ft/public/ft/templates/Vec4.tpp libftui/ft/public/ft/utils.hpp \
	libftui/ftlua/public/ftlua/ftlua.hpp \
	libftui/ftlua/public/ftlua/templates/ftlua_caller.tpp \
	libftui/ftlua/public/ftlua/templates/ftlua_handler.tpp \
	libftui/liblua/public/liblua.hpp include/Grid.hpp | o/srcs/
