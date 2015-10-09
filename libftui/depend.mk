O_FILES :=	o/srcs/ALayout.o o/srcs/ALayout_luaCFunctions.o o/srcs/AView.o \
			o/srcs/AView_luaCFunctions.o o/srcs/AView_statics.o \
			o/srcs/AbsoluteLayout.o o/srcs/Activity.o \
			o/srcs/Activity_RootViewHolder.o o/srcs/Canvas.o \
			o/srcs/RelativeLayout.o o/srcs/SliderView.o o/srcs/TextView.o \
			o/srcs/VerticalLayout.o o/srcs/VerticalLayout_ViewHolder.o \
			o/srcs/XmlParser.o o/srcs/XmlTokenizer.o o/srcs/ft/assert.o \
			o/srcs/lua_debug.o

LIBS_DEPEND := 

libs:
.PHONY: libs



MAX_SOURCE_LEN := 34
o/srcs/ALayout.o: srcs/ALayout.cpp include/ft/assert.hpp \
	include/ftui/ALayout.hpp include/ftui/AView.hpp include/ftui/libftui.hpp \
	include/ftui/lua.hpp include/ftui/XmlParser.hpp \
	include/ftui/XmlTokenizer.hpp include/ft/Vec.hpp \
	include/ft/templates/Vec2.tpp include/ft/templates/Vec3.tpp \
	include/ft/templates/Vec4.tpp include/ftui/IViewHolder.hpp | o/srcs/
o/srcs/ALayout_luaCFunctions.o: srcs/ALayout_luaCFunctions.cpp \
	include/ft/assert.hpp include/ftui/ALayout.hpp include/ftui/AView.hpp \
	include/ftui/libftui.hpp include/ftui/lua.hpp include/ft/Vec.hpp \
	include/ft/templates/Vec2.tpp include/ft/templates/Vec3.tpp \
	include/ft/templates/Vec4.tpp include/ft/utils.hpp \
	include/ftui/luaCFunctions_helpers.hpp \
	include/ftui/templates/luaCFunctions_helpers.tpp | o/srcs/
o/srcs/AView.o: srcs/AView.cpp include/ft/utils.hpp include/ft/assert.hpp \
	include/ftui/AView.hpp include/ftui/libftui.hpp include/ftui/lua.hpp \
	include/ft/Vec.hpp include/ft/templates/Vec2.tpp \
	include/ft/templates/Vec3.tpp include/ft/templates/Vec4.tpp \
	include/ftui/Activity.hpp include/ftui/DefaultEventBox.hpp \
	include/ftui/EventBox.hpp include/ftui/EventParams.hpp \
	include/ftui/IEventBox.hpp include/ftui/IEventParams.hpp \
	include/ftui/IViewHolder.hpp include/ftui/templates/Activity.tpp \
	include/ftui/ALayout.hpp include/ftui/XmlParser.hpp \
	include/ftui/XmlTokenizer.hpp include/ftui/VerticalLayout.hpp | o/srcs/
o/srcs/AView_luaCFunctions.o: srcs/AView_luaCFunctions.cpp \
	include/ft/assert.hpp include/ftui/AView.hpp include/ftui/libftui.hpp \
	include/ftui/lua.hpp include/ft/Vec.hpp include/ft/templates/Vec2.tpp \
	include/ft/templates/Vec3.tpp include/ft/templates/Vec4.tpp \
	include/ft/utils.hpp include/ftui/luaCFunctions_helpers.hpp \
	include/ftui/templates/luaCFunctions_helpers.tpp | o/srcs/
o/srcs/AView_statics.o: srcs/AView_statics.cpp include/ft/utils.hpp \
	include/ft/assert.hpp include/ftui/AView.hpp include/ftui/libftui.hpp \
	include/ftui/lua.hpp include/ft/Vec.hpp include/ft/templates/Vec2.tpp \
	include/ft/templates/Vec3.tpp include/ft/templates/Vec4.tpp \
	include/ftui/ALayout.hpp include/ftui/IViewHolder.hpp \
	include/ftui/VerticalLayout.hpp | o/srcs/
o/srcs/AbsoluteLayout.o: srcs/AbsoluteLayout.cpp include/ft/assert.hpp \
	include/ftui/AbsoluteLayout.hpp include/ftui/libftui.hpp | o/srcs/
o/srcs/Activity.o: srcs/Activity.cpp include/ft/utils.hpp include/ft/Vec.hpp \
	include/ft/assert.hpp include/ft/templates/Vec2.tpp \
	include/ft/templates/Vec3.tpp include/ft/templates/Vec4.tpp \
	include/ftui/Activity.hpp include/ftui/DefaultEventBox.hpp \
	include/ftui/EventBox.hpp include/ftui/EventParams.hpp \
	include/ftui/IEventBox.hpp include/ftui/IEventParams.hpp \
	include/ftui/IViewHolder.hpp include/ftui/libftui.hpp include/ftui/lua.hpp \
	include/ftui/templates/Activity.tpp include/ftui/AView.hpp \
	include/ftui/XmlParser.hpp include/ftui/XmlTokenizer.hpp | o/srcs/
o/srcs/Activity_RootViewHolder.o: srcs/Activity_RootViewHolder.cpp \
	include/ft/Vec.hpp include/ft/assert.hpp include/ft/templates/Vec2.tpp \
	include/ft/templates/Vec3.tpp include/ft/templates/Vec4.tpp \
	include/ftui/Activity.hpp include/ftui/DefaultEventBox.hpp \
	include/ftui/EventBox.hpp include/ftui/EventParams.hpp \
	include/ftui/IEventBox.hpp include/ftui/IEventParams.hpp \
	include/ftui/IViewHolder.hpp include/ftui/libftui.hpp include/ftui/lua.hpp \
	include/ftui/templates/Activity.tpp include/ftui/AView.hpp \
	include/ftui/XmlParser.hpp include/ftui/XmlTokenizer.hpp | o/srcs/
o/srcs/Canvas.o: srcs/Canvas.cpp include/ft/Color.hpp include/ft/Rect.hpp \
	include/ft/Vec.hpp include/ft/assert.hpp include/ft/templates/Vec2.tpp \
	include/ft/templates/Vec3.tpp include/ft/templates/Vec4.tpp \
	include/ftui/Canvas.hpp include/ftui/libftui.hpp | o/srcs/
o/srcs/RelativeLayout.o: srcs/RelativeLayout.cpp include/ft/assert.hpp \
	include/ftui/RelativeLayout.hpp include/ftui/libftui.hpp | o/srcs/
o/srcs/SliderView.o: srcs/SliderView.cpp include/ft/assert.hpp \
	include/ftui/SliderView.hpp include/ftui/libftui.hpp | o/srcs/
o/srcs/TextView.o: srcs/TextView.cpp include/ft/assert.hpp \
	include/ftui/TextView.hpp include/ftui/libftui.hpp | o/srcs/
o/srcs/VerticalLayout.o: srcs/VerticalLayout.cpp include/ft/Vec.hpp \
	include/ft/assert.hpp include/ft/templates/Vec2.tpp \
	include/ft/templates/Vec3.tpp include/ft/templates/Vec4.tpp \
	include/ftui/ALayout.hpp include/ftui/AView.hpp \
	include/ftui/IViewHolder.hpp include/ftui/VerticalLayout.hpp \
	include/ftui/libftui.hpp include/ftui/lua.hpp include/ft/Color.hpp \
	include/ft/Rect.hpp include/ftui/Canvas.hpp include/ftui/XmlParser.hpp \
	include/ftui/XmlTokenizer.hpp include/ft/utils.hpp | o/srcs/
o/srcs/VerticalLayout_ViewHolder.o: srcs/VerticalLayout_ViewHolder.cpp \
	include/ft/utils.hpp include/ft/Vec.hpp include/ft/assert.hpp \
	include/ft/templates/Vec2.tpp include/ft/templates/Vec3.tpp \
	include/ft/templates/Vec4.tpp include/ftui/ALayout.hpp \
	include/ftui/AView.hpp include/ftui/IViewHolder.hpp \
	include/ftui/VerticalLayout.hpp include/ftui/libftui.hpp \
	include/ftui/lua.hpp include/ftui/XmlParser.hpp \
	include/ftui/XmlTokenizer.hpp include/ftui/Activity.hpp \
	include/ftui/DefaultEventBox.hpp include/ftui/EventBox.hpp \
	include/ftui/EventParams.hpp include/ftui/IEventBox.hpp \
	include/ftui/IEventParams.hpp include/ftui/templates/Activity.tpp | o/srcs/
o/srcs/XmlParser.o: srcs/XmlParser.cpp include/ft/assert.hpp \
	include/ftui/XmlParser.hpp include/ftui/XmlTokenizer.hpp \
	include/ftui/libftui.hpp include/ft/utils.hpp | o/srcs/
o/srcs/XmlTokenizer.o: srcs/XmlTokenizer.cpp include/ft/assert.hpp \
	include/ftui/XmlTokenizer.hpp include/ftui/libftui.hpp \
	include/ft/utils.hpp | o/srcs/
o/srcs/ft/assert.o: srcs/ft/assert.cpp include/ft/assert.hpp \
	include/ft/utils.hpp | o/srcs/ft/
o/srcs/lua_debug.o: srcs/lua_debug.cpp include/ft/assert.hpp \
	include/ftui/libftui.hpp include/ft/Vec.hpp include/ft/templates/Vec2.tpp \
	include/ft/templates/Vec3.tpp include/ft/templates/Vec4.tpp \
	include/ftui/Activity.hpp include/ftui/DefaultEventBox.hpp \
	include/ftui/EventBox.hpp include/ftui/EventParams.hpp \
	include/ftui/IEventBox.hpp include/ftui/IEventParams.hpp \
	include/ftui/IViewHolder.hpp include/ftui/lua.hpp \
	include/ftui/templates/Activity.tpp | o/srcs/
