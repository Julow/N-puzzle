O_FILES :=	o/srcs/ALayout.o o/srcs/ALayout_luaHandler.o o/srcs/ASolidView.o \
			o/srcs/AView.o o/srcs/AView_luaHandler.o o/srcs/AView_statics.o \
			o/srcs/Activity.o o/srcs/Activity_RootViewHolder.o o/srcs/Button.o \
			o/srcs/Canvas.o o/srcs/SolidView.o o/srcs/TextView.o \
			o/srcs/VerticalLayout.o o/srcs/VerticalLayout_ViewHolder.o \
			o/srcs/XmlParser.o o/srcs/XmlTokenizer.o o/srcs/ft/assert.o \
			o/srcs/ft/padformat.o o/srcs/ftlua/cpp_utils.o \
			o/srcs/ftlua/push_utils.o

LIBS_DEPEND := 

libs:
.PHONY: libs



MAX_SOURCE_LEN := 34
o/srcs/ALayout.o: srcs/ALayout.cpp include/ft/Color.hpp include/ft/Rect.hpp \
	include/ft/Vec.hpp include/ft/assert.hpp include/ft/templates/Vec2.tpp \
	include/ft/templates/Vec3.tpp include/ft/templates/Vec4.tpp \
	include/ftui/ALayout.hpp include/ftui/ASolidView.hpp \
	include/ftui/AView.hpp include/ftui/Canvas.hpp include/ftui/libftui.hpp \
	include/ftui/XmlParser.hpp include/ftui/XmlTokenizer.hpp \
	include/ftui/IViewHolder.hpp include/ft/utils.hpp | o/srcs/
o/srcs/ALayout_luaHandler.o: srcs/ALayout_luaHandler.cpp include/ft/Color.hpp \
	include/ft/Rect.hpp include/ft/Vec.hpp include/ft/assert.hpp \
	include/ft/templates/Vec2.tpp include/ft/templates/Vec3.tpp \
	include/ft/templates/Vec4.tpp include/ftui/ALayout.hpp \
	include/ftui/ASolidView.hpp include/ftui/AView.hpp include/ftui/Canvas.hpp \
	include/ftui/libftui.hpp include/ft/utils.hpp include/ftlua/ftlua.hpp \
	include/ftlua/templates/ftlua_caller.tpp \
	include/ftlua/templates/ftlua_handler.tpp | o/srcs/
o/srcs/ASolidView.o: srcs/ASolidView.cpp include/ft/Color.hpp \
	include/ft/Rect.hpp include/ft/Vec.hpp include/ft/assert.hpp \
	include/ft/templates/Vec2.tpp include/ft/templates/Vec3.tpp \
	include/ft/templates/Vec4.tpp include/ftui/ASolidView.hpp \
	include/ftui/AView.hpp include/ftui/Canvas.hpp include/ftui/libftui.hpp \
	include/ftui/IViewHolder.hpp include/ftui/XmlParser.hpp \
	include/ftui/XmlTokenizer.hpp | o/srcs/
o/srcs/AView.o: srcs/AView.cpp include/ft/utils.hpp include/ft/Vec.hpp \
	include/ft/assert.hpp include/ft/templates/Vec2.tpp \
	include/ft/templates/Vec3.tpp include/ft/templates/Vec4.tpp \
	include/ftlua/ftlua.hpp include/ftlua/templates/ftlua_caller.tpp \
	include/ftlua/templates/ftlua_handler.tpp include/ftui/AView.hpp \
	include/ftui/libftui.hpp include/ftui/Activity.hpp \
	include/ftui/DefaultEventBox.hpp include/ftui/EventBox.hpp \
	include/ftui/EventParams.hpp include/ftui/IEventBox.hpp \
	include/ftui/IEventParams.hpp include/ftui/IViewHolder.hpp \
	include/ftui/templates/Activity.tpp include/ftui/templates/EventBox.tpp \
	include/ft/Color.hpp include/ft/Rect.hpp include/ftui/ALayout.hpp \
	include/ftui/ASolidView.hpp include/ftui/Canvas.hpp \
	include/ftui/XmlParser.hpp include/ftui/XmlTokenizer.hpp \
	include/ftui/VerticalLayout.hpp \
	include/ftui/templates/AView_callLuaCallback.tpp | o/srcs/
o/srcs/AView_luaHandler.o: srcs/AView_luaHandler.cpp include/ft/assert.hpp \
	include/ftui/AView.hpp include/ftui/libftui.hpp include/ft/Vec.hpp \
	include/ft/templates/Vec2.tpp include/ft/templates/Vec3.tpp \
	include/ft/templates/Vec4.tpp include/ftui/IViewHolder.hpp \
	include/ft/Color.hpp include/ft/Rect.hpp include/ftui/ASolidView.hpp \
	include/ftui/Canvas.hpp include/ftui/TextView.hpp include/ft/utils.hpp \
	include/ftlua/ftlua.hpp include/ftlua/templates/ftlua_caller.tpp \
	include/ftlua/templates/ftlua_handler.tpp | o/srcs/
o/srcs/AView_statics.o: srcs/AView_statics.cpp include/ft/utils.hpp \
	include/ft/assert.hpp include/ftui/AView.hpp include/ftui/libftui.hpp \
	include/ft/Color.hpp include/ft/Rect.hpp include/ft/Vec.hpp \
	include/ft/templates/Vec2.tpp include/ft/templates/Vec3.tpp \
	include/ft/templates/Vec4.tpp include/ftui/ALayout.hpp \
	include/ftui/ASolidView.hpp include/ftui/Canvas.hpp \
	include/ftui/IViewHolder.hpp include/ftui/VerticalLayout.hpp \
	include/ftui/SolidView.hpp include/ftui/TextView.hpp \
	include/ftui/Button.hpp include/ftlua/ftlua.hpp \
	include/ftlua/templates/ftlua_caller.tpp \
	include/ftlua/templates/ftlua_handler.tpp | o/srcs/
o/srcs/Activity.o: srcs/Activity.cpp include/ft/utils.hpp include/ft/Vec.hpp \
	include/ft/assert.hpp include/ft/templates/Vec2.tpp \
	include/ft/templates/Vec3.tpp include/ft/templates/Vec4.tpp \
	include/ftlua/ftlua.hpp include/ftlua/templates/ftlua_caller.tpp \
	include/ftlua/templates/ftlua_handler.tpp include/ftui/Activity.hpp \
	include/ftui/DefaultEventBox.hpp include/ftui/EventBox.hpp \
	include/ftui/EventParams.hpp include/ftui/IEventBox.hpp \
	include/ftui/IEventParams.hpp include/ftui/IViewHolder.hpp \
	include/ftui/libftui.hpp include/ftui/templates/Activity.tpp \
	include/ftui/templates/EventBox.tpp include/ftui/AView.hpp \
	include/ft/Color.hpp include/ft/Rect.hpp include/ftui/Canvas.hpp \
	include/ftui/XmlParser.hpp include/ftui/XmlTokenizer.hpp | o/srcs/
o/srcs/Activity_RootViewHolder.o: srcs/Activity_RootViewHolder.cpp \
	include/ft/Vec.hpp include/ft/assert.hpp include/ft/templates/Vec2.tpp \
	include/ft/templates/Vec3.tpp include/ft/templates/Vec4.tpp \
	include/ftui/Activity.hpp include/ftui/DefaultEventBox.hpp \
	include/ftui/EventBox.hpp include/ftui/EventParams.hpp \
	include/ftui/IEventBox.hpp include/ftui/IEventParams.hpp \
	include/ftui/IViewHolder.hpp include/ftui/libftui.hpp \
	include/ftui/templates/Activity.tpp include/ftui/templates/EventBox.tpp \
	include/ftui/AView.hpp include/ftui/XmlParser.hpp \
	include/ftui/XmlTokenizer.hpp | o/srcs/
o/srcs/Button.o: srcs/Button.cpp include/ft/Color.hpp include/ft/Rect.hpp \
	include/ft/Vec.hpp include/ft/assert.hpp include/ft/templates/Vec2.tpp \
	include/ft/templates/Vec3.tpp include/ft/templates/Vec4.tpp \
	include/ftui/AView.hpp include/ftui/Button.hpp include/ftui/Canvas.hpp \
	include/ftui/libftui.hpp include/ftui/Activity.hpp \
	include/ftui/DefaultEventBox.hpp include/ftui/EventBox.hpp \
	include/ftui/EventParams.hpp include/ftui/IEventBox.hpp \
	include/ftui/IEventParams.hpp include/ftui/IViewHolder.hpp \
	include/ftui/templates/Activity.tpp include/ftui/templates/EventBox.tpp \
	| o/srcs/
o/srcs/Canvas.o: srcs/Canvas.cpp include/ft/Color.hpp include/ft/Rect.hpp \
	include/ft/Vec.hpp include/ft/assert.hpp include/ft/templates/Vec2.tpp \
	include/ft/templates/Vec3.tpp include/ft/templates/Vec4.tpp \
	include/ftui/Canvas.hpp include/ftui/libftui.hpp include/ft/utils.hpp \
	include/ftlua/ftlua.hpp include/ftlua/templates/ftlua_caller.tpp \
	include/ftlua/templates/ftlua_handler.tpp | o/srcs/
o/srcs/SolidView.o: srcs/SolidView.cpp include/ft/Color.hpp \
	include/ft/Rect.hpp include/ft/Vec.hpp include/ft/assert.hpp \
	include/ft/templates/Vec2.tpp include/ft/templates/Vec3.tpp \
	include/ft/templates/Vec4.tpp include/ftui/ASolidView.hpp \
	include/ftui/AView.hpp include/ftui/Canvas.hpp include/ftui/SolidView.hpp \
	include/ftui/libftui.hpp | o/srcs/
o/srcs/TextView.o: srcs/TextView.cpp include/ft/Color.hpp include/ft/Rect.hpp \
	include/ft/Vec.hpp include/ft/assert.hpp include/ft/templates/Vec2.tpp \
	include/ft/templates/Vec3.tpp include/ft/templates/Vec4.tpp \
	include/ftui/ASolidView.hpp include/ftui/AView.hpp include/ftui/Canvas.hpp \
	include/ftui/TextView.hpp include/ftui/libftui.hpp \
	include/ftui/IViewHolder.hpp | o/srcs/
o/srcs/VerticalLayout.o: srcs/VerticalLayout.cpp include/ft/Color.hpp \
	include/ft/Rect.hpp include/ft/Vec.hpp include/ft/assert.hpp \
	include/ft/templates/Vec2.tpp include/ft/templates/Vec3.tpp \
	include/ft/templates/Vec4.tpp include/ftui/ALayout.hpp \
	include/ftui/ASolidView.hpp include/ftui/AView.hpp include/ftui/Canvas.hpp \
	include/ftui/IViewHolder.hpp include/ftui/VerticalLayout.hpp \
	include/ftui/libftui.hpp include/ftui/XmlParser.hpp \
	include/ftui/XmlTokenizer.hpp include/ft/utils.hpp | o/srcs/
o/srcs/VerticalLayout_ViewHolder.o: srcs/VerticalLayout_ViewHolder.cpp \
	include/ft/utils.hpp include/ft/Color.hpp include/ft/Rect.hpp \
	include/ft/Vec.hpp include/ft/assert.hpp include/ft/templates/Vec2.tpp \
	include/ft/templates/Vec3.tpp include/ft/templates/Vec4.tpp \
	include/ftui/ALayout.hpp include/ftui/ASolidView.hpp \
	include/ftui/AView.hpp include/ftui/Canvas.hpp \
	include/ftui/IViewHolder.hpp include/ftui/VerticalLayout.hpp \
	include/ftui/libftui.hpp include/ftui/XmlParser.hpp \
	include/ftui/XmlTokenizer.hpp include/ftui/Activity.hpp \
	include/ftui/DefaultEventBox.hpp include/ftui/EventBox.hpp \
	include/ftui/EventParams.hpp include/ftui/IEventBox.hpp \
	include/ftui/IEventParams.hpp include/ftui/templates/Activity.tpp \
	include/ftui/templates/EventBox.tpp | o/srcs/
o/srcs/XmlParser.o: srcs/XmlParser.cpp include/ft/assert.hpp \
	include/ftui/XmlParser.hpp include/ftui/XmlTokenizer.hpp \
	include/ftui/libftui.hpp include/ft/utils.hpp | o/srcs/
o/srcs/XmlTokenizer.o: srcs/XmlTokenizer.cpp include/ft/assert.hpp \
	include/ftui/XmlTokenizer.hpp include/ftui/libftui.hpp \
	include/ft/utils.hpp | o/srcs/
o/srcs/ft/assert.o: srcs/ft/assert.cpp include/ft/assert.hpp \
	include/ft/utils.hpp | o/srcs/ft/
o/srcs/ft/padformat.o: srcs/ft/padformat.cpp include/ft/assert.hpp \
	include/ft/utils.hpp | o/srcs/ft/
o/srcs/ftlua/cpp_utils.o: srcs/ftlua/cpp_utils.cpp include/ft/Vec.hpp \
	include/ft/assert.hpp include/ft/templates/Vec2.tpp \
	include/ft/templates/Vec3.tpp include/ft/templates/Vec4.tpp \
	include/ft/utils.hpp include/ftlua/ftlua.hpp \
	include/ftlua/templates/ftlua_caller.tpp \
	include/ftlua/templates/ftlua_handler.tpp | o/srcs/ftlua/
o/srcs/ftlua/push_utils.o: srcs/ftlua/push_utils.cpp include/ft/assert.hpp \
	| o/srcs/ftlua/
