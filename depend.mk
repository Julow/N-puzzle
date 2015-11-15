O_FILES :=	o/srcs/GlCanvasHolder.o o/srcs/Grid.o o/srcs/Main.o \
			o/srcs/OCamlBinding.o o/srcs/PickState.o o/srcs/ftlua_extend.o \
			o/srcs/libftui_extend/Bookmark.o

LIBS_DEPEND := modules/libmodules.a

libs:
	make -C modules
.PHONY: libs



MAX_SOURCE_LEN := 32
o/srcs/GlCanvasHolder.o: srcs/GlCanvasHolder.cpp include/GlCanvasHolder.hpp \
	modules/ft/public/ft/Color.hpp modules/ft/public/ft/Rect.hpp \
	modules/ft/public/ft/Vec.hpp modules/ft/public/ft/assert.hpp \
	modules/ft/public/ft/templates/Rect.tpp \
	modules/ft/public/ft/templates/Vec2.tpp \
	modules/ft/public/ft/templates/Vec3.tpp \
	modules/ft/public/ft/templates/Vec4.tpp modules/ft/public/ft/utils.hpp \
	modules/ftlua/public/ftlua/ftlua.hpp \
	modules/ftlua/public/ftlua/templates/ftlua_caller.tpp \
	modules/ftlua/public/ftlua/templates/ftlua_handler.tpp \
	modules/ftui/public/ftui/Canvas.hpp modules/ftui/public/ftui/libftui.hpp \
	modules/liblua/public/liblua.hpp modules/gl/gl.h modules/gl/gl.hpp | o/srcs/
o/srcs/Grid.o: srcs/Grid.cpp include/Grid.hpp modules/ft/public/ft/Rect.hpp \
	modules/ft/public/ft/Vec.hpp modules/ft/public/ft/templates/Rect.tpp \
	modules/ft/public/ft/templates/Vec2.tpp \
	modules/ft/public/ft/templates/Vec3.tpp \
	modules/ft/public/ft/templates/Vec4.tpp modules/ft/public/ft/utils.hpp \
	| o/srcs/
o/srcs/Main.o: srcs/Main.cpp modules/ft/public/ft/Rect.hpp \
	modules/ft/public/ft/Vec.hpp modules/ft/public/ft/templates/Rect.tpp \
	modules/ft/public/ft/templates/Vec2.tpp \
	modules/ft/public/ft/templates/Vec3.tpp \
	modules/ft/public/ft/templates/Vec4.tpp modules/ft/public/ft/utils.hpp \
	include/GlCanvasHolder.hpp include/Grid.hpp include/ISolverListener.hpp \
	include/IState.hpp include/Main.hpp include/OCamlBinding.hpp \
	modules/ft/public/ft/Color.hpp modules/ft/public/ft/assert.hpp \
	modules/ftlua/public/ftlua/ftlua.hpp \
	modules/ftlua/public/ftlua/templates/ftlua_caller.tpp \
	modules/ftlua/public/ftlua/templates/ftlua_handler.tpp \
	modules/ftui/public/ftui/Activity.hpp modules/ftui/public/ftui/Canvas.hpp \
	modules/ftui/public/ftui/DefaultEventBox.hpp \
	modules/ftui/public/ftui/EventBox.hpp \
	modules/ftui/public/ftui/EventParams.hpp \
	modules/ftui/public/ftui/IEventBox.hpp \
	modules/ftui/public/ftui/IEventParams.hpp \
	modules/ftui/public/ftui/IViewHolder.hpp \
	modules/ftui/public/ftui/libftui.hpp \
	modules/ftui/public/ftui/templates/Activity.tpp \
	modules/ftui/public/ftui/templates/DefaultEventBox.tpp \
	modules/ftui/public/ftui/templates/EventBox.tpp modules/gl/gl.h \
	modules/gl/gl.hpp modules/liblua/public/liblua.hpp \
	include/config_window.hpp include/ftce/math.hpp include/PickState.hpp \
	modules/tiles/include/tiles/Tiles.hpp include/ftlua_extend.hpp \
	include/libftui_extend/Bookmark.hpp | o/srcs/
o/srcs/OCamlBinding.o: srcs/OCamlBinding.cpp include/Grid.hpp \
	include/ISolverListener.hpp include/OCamlBinding.hpp \
	modules/ft/public/ft/Rect.hpp modules/ft/public/ft/Vec.hpp \
	modules/ft/public/ft/templates/Rect.tpp \
	modules/ft/public/ft/templates/Vec2.tpp \
	modules/ft/public/ft/templates/Vec3.tpp \
	modules/ft/public/ft/templates/Vec4.tpp modules/ft/public/ft/utils.hpp \
	| o/srcs/
o/srcs/PickState.o: srcs/PickState.cpp include/GlCanvasHolder.hpp \
	include/Grid.hpp include/ISolverListener.hpp include/IState.hpp \
	include/Main.hpp include/OCamlBinding.hpp include/PickState.hpp \
	modules/ft/public/ft/Color.hpp modules/ft/public/ft/Rect.hpp \
	modules/ft/public/ft/Vec.hpp modules/ft/public/ft/assert.hpp \
	modules/ft/public/ft/templates/Rect.tpp \
	modules/ft/public/ft/templates/Vec2.tpp \
	modules/ft/public/ft/templates/Vec3.tpp \
	modules/ft/public/ft/templates/Vec4.tpp modules/ft/public/ft/utils.hpp \
	modules/ftlua/public/ftlua/ftlua.hpp \
	modules/ftlua/public/ftlua/templates/ftlua_caller.tpp \
	modules/ftlua/public/ftlua/templates/ftlua_handler.tpp \
	modules/ftui/public/ftui/Activity.hpp modules/ftui/public/ftui/Canvas.hpp \
	modules/ftui/public/ftui/DefaultEventBox.hpp \
	modules/ftui/public/ftui/EventBox.hpp \
	modules/ftui/public/ftui/EventParams.hpp \
	modules/ftui/public/ftui/IEventBox.hpp \
	modules/ftui/public/ftui/IEventParams.hpp \
	modules/ftui/public/ftui/IViewHolder.hpp \
	modules/ftui/public/ftui/libftui.hpp \
	modules/ftui/public/ftui/templates/Activity.tpp \
	modules/ftui/public/ftui/templates/DefaultEventBox.tpp \
	modules/ftui/public/ftui/templates/EventBox.tpp modules/gl/gl.h \
	modules/gl/gl.hpp modules/liblua/public/liblua.hpp \
	modules/tiles/include/tiles/Tiles.hpp include/config_window.hpp \
	include/ftce/math.hpp | o/srcs/
o/srcs/ftlua_extend.o: srcs/ftlua_extend.cpp modules/ft/public/ft/Rect.hpp \
	modules/ft/public/ft/Vec.hpp modules/ft/public/ft/assert.hpp \
	modules/ft/public/ft/templates/Rect.tpp \
	modules/ft/public/ft/templates/Vec2.tpp \
	modules/ft/public/ft/templates/Vec3.tpp \
	modules/ft/public/ft/templates/Vec4.tpp modules/ft/public/ft/utils.hpp \
	modules/ftlua/public/ftlua/ftlua.hpp \
	modules/ftlua/public/ftlua/templates/ftlua_caller.tpp \
	modules/ftlua/public/ftlua/templates/ftlua_handler.tpp \
	modules/liblua/public/liblua.hpp include/Grid.hpp | o/srcs/
o/srcs/libftui_extend/Bookmark.o: srcs/libftui_extend/Bookmark.cpp \
	include/libftui_extend/Bookmark.hpp | o/srcs/libftui_extend/
