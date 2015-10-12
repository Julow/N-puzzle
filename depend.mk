O_FILES :=	o/include/tiles/Tiles.o o/srcs/GlCanvasHolder.o o/srcs/TextView.o \
			o/srcs/main.o

LIBS_DEPEND := libftui/libftui.a

libs:
	make -C libftui
.PHONY: libs



MAX_SOURCE_LEN := 23
o/include/tiles/Tiles.o: include/tiles/Tiles.cpp include/gl.hpp \
	| o/include/tiles/
o/srcs/GlCanvasHolder.o: srcs/GlCanvasHolder.cpp include/GlCanvasHolder.hpp \
	libftui/include/ft/Color.hpp libftui/include/ft/Rect.hpp \
	libftui/include/ft/Vec.hpp libftui/include/ft/assert.hpp \
	libftui/include/ft/templates/Vec2.tpp \
	libftui/include/ft/templates/Vec3.tpp \
	libftui/include/ft/templates/Vec4.tpp libftui/include/ftui/Canvas.hpp \
	libftui/include/ftui/libftui.hpp include/gl.hpp \
	libftui/include/ft/utils.hpp | o/srcs/
o/srcs/TextView.o: srcs/TextView.cpp include/TextView.hpp \
	libftui/include/ft/Color.hpp libftui/include/ft/Rect.hpp \
	libftui/include/ft/Vec.hpp libftui/include/ft/assert.hpp \
	libftui/include/ft/templates/Vec2.tpp \
	libftui/include/ft/templates/Vec3.tpp \
	libftui/include/ft/templates/Vec4.tpp libftui/include/ftui/ASolidView.hpp \
	libftui/include/ftui/AView.hpp libftui/include/ftui/Canvas.hpp \
	libftui/include/ftui/libftui.hpp libftui/include/ftui/IViewHolder.hpp \
	| o/srcs/
o/srcs/main.o: srcs/main.cpp libftui/include/ft/utils.hpp \
	include/config_window.hpp include/ftce/math.hpp libftui/include/ft/Vec.hpp \
	libftui/include/ft/assert.hpp libftui/include/ft/templates/Vec2.tpp \
	libftui/include/ft/templates/Vec3.tpp \
	libftui/include/ft/templates/Vec4.tpp libftui/include/ftui/libftui.hpp \
	include/TextView.hpp libftui/include/ft/Color.hpp \
	libftui/include/ft/Rect.hpp libftui/include/ftui/ASolidView.hpp \
	libftui/include/ftui/AView.hpp libftui/include/ftui/Canvas.hpp \
	libftui/include/ftui/Activity.hpp libftui/include/ftui/DefaultEventBox.hpp \
	libftui/include/ftui/EventBox.hpp libftui/include/ftui/EventParams.hpp \
	libftui/include/ftui/IEventBox.hpp libftui/include/ftui/IEventParams.hpp \
	libftui/include/ftui/IViewHolder.hpp \
	libftui/include/ftui/templates/Activity.tpp \
	libftui/include/ftui/ALayout.hpp \
	libftui/include/ftui/luaCFunctions_helpers.hpp \
	libftui/include/ftui/templates/luaCFunctions_helpers.tpp \
	include/tiles/Tiles.hpp include/GlCanvasHolder.hpp include/gl.hpp | o/srcs/
