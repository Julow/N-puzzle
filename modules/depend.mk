LIBS_RULES += liblua
LINK_FLAGS += -lfreetype -Lliblua/lua-5.3.1/src -llua
O_FILES += $(O_DIR)/ft/assert.o $(O_DIR)/ft/padformat.o \
	$(O_DIR)/ft_xml/srcs/XmlParser.o $(O_DIR)/ft_xml/srcs/XmlTokenizer.o \
	$(O_DIR)/ftlua/cpp_utils.o $(O_DIR)/ftlua/push_utils.o \
	$(O_DIR)/ftlua/stackError.o $(O_DIR)/ftui/ALayout.o \
	$(O_DIR)/ftui/ALayout_luaHandler.o $(O_DIR)/ftui/ASolidView.o \
	$(O_DIR)/ftui/AView.o $(O_DIR)/ftui/AView_luaHandler.o \
	$(O_DIR)/ftui/AView_statics.o $(O_DIR)/ftui/Activity.o \
	$(O_DIR)/ftui/Activity_RootViewHolder.o $(O_DIR)/ftui/Button.o \
	$(O_DIR)/ftui/Canvas.o $(O_DIR)/ftui/HorizontalLayout.o \
	$(O_DIR)/ftui/HorizontalLayout_ViewHolder.o $(O_DIR)/ftui/SolidView.o \
	$(O_DIR)/ftui/TextView.o $(O_DIR)/ftui/VerticalLayout.o \
	$(O_DIR)/ftui/VerticalLayout_ViewHolder.o $(O_DIR)/tiles/Tiles.o

# module ft
$(O_DIR)/ft/_public/ft: | $(O_DIR)/ft/_public/
$(O_DIR)/ft/_public/ft: ft/public

PUBLIC_LINKS += $(O_DIR)/ft/_public/ft

$(O_DIR)/ft/assert.o $(O_DIR)/ft/padformat.o: INCLUDE_FLAGS += \
	-I$(O_DIR)/ft/_public
$(O_DIR)/ft/assert.o $(O_DIR)/ft/padformat.o: | $(O_DIR)/ft/_public/ft

$(O_DIR)/ft/assert.o: ft/assert.cpp ft/public/Rect.hpp ft/public/Vec.hpp \
	ft/public/assert.hpp ft/public/templates/Rect.tpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp ft/public/utils.hpp | $(O_DIR)/ft/
$(O_DIR)/ft/padformat.o: ft/padformat.cpp ft/public/Rect.hpp ft/public/Vec.hpp \
	ft/public/assert.hpp ft/public/templates/Rect.tpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp ft/public/utils.hpp | $(O_DIR)/ft/

# module ft_xml
$(O_DIR)/ft_xml/_public/ft $(O_DIR)/ft_xml/_public/ft_xml: \
	| $(O_DIR)/ft_xml/_public/
$(O_DIR)/ft_xml/_public/ft: ft/public
$(O_DIR)/ft_xml/_public/ft_xml: ft_xml/public

PUBLIC_LINKS += $(O_DIR)/ft_xml/_public/ft $(O_DIR)/ft_xml/_public/ft_xml

$(O_DIR)/ft_xml/srcs/XmlParser.o $(O_DIR)/ft_xml/srcs/XmlTokenizer.o: \
	INCLUDE_FLAGS += -I$(O_DIR)/ft_xml/_public
$(O_DIR)/ft_xml/srcs/XmlParser.o $(O_DIR)/ft_xml/srcs/XmlTokenizer.o: | \
	$(O_DIR)/ft_xml/_public/ft $(O_DIR)/ft_xml/_public/ft_xml

$(O_DIR)/ft_xml/srcs/XmlParser.o: ft_xml/srcs/XmlParser.cpp ft/public/Rect.hpp \
	ft/public/Vec.hpp ft/public/templates/Rect.tpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp ft/public/utils.hpp \
	ft_xml/public/XmlParser.hpp ft_xml/public/XmlTokenizer.hpp \
	| $(O_DIR)/ft_xml/srcs/
$(O_DIR)/ft_xml/srcs/XmlTokenizer.o: ft_xml/srcs/XmlTokenizer.cpp \
	ft/public/Rect.hpp ft/public/Vec.hpp ft/public/templates/Rect.tpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp ft/public/utils.hpp \
	ft_xml/public/XmlTokenizer.hpp | $(O_DIR)/ft_xml/srcs/

# module ftlua
$(O_DIR)/ftlua/_public/ft $(O_DIR)/ftlua/_public/liblua \
$(O_DIR)/ftlua/_public/ftlua: | $(O_DIR)/ftlua/_public/
$(O_DIR)/ftlua/_public/ft: ft/public
$(O_DIR)/ftlua/_public/liblua: liblua/lua-5.3.1/src
$(O_DIR)/ftlua/_public/ftlua: ftlua/public

PUBLIC_LINKS += $(O_DIR)/ftlua/_public/ft $(O_DIR)/ftlua/_public/liblua \
	$(O_DIR)/ftlua/_public/ftlua

$(O_DIR)/ftlua/cpp_utils.o $(O_DIR)/ftlua/push_utils.o \
$(O_DIR)/ftlua/stackError.o: INCLUDE_FLAGS += -I$(O_DIR)/ftlua/_public
$(O_DIR)/ftlua/cpp_utils.o $(O_DIR)/ftlua/push_utils.o \
$(O_DIR)/ftlua/stackError.o: | $(O_DIR)/ftlua/_public/ft \
	$(O_DIR)/ftlua/_public/liblua $(O_DIR)/ftlua/_public/ftlua

$(O_DIR)/ftlua/cpp_utils.o $(O_DIR)/ftlua/push_utils.o \
$(O_DIR)/ftlua/stackError.o: BASE_FLAGS += -DRES_PATH='"$(abspath ftlua/res/)"'
$(O_DIR)/ftlua/cpp_utils.o: ftlua/cpp_utils.cpp ft/public/Rect.hpp \
	ft/public/Vec.hpp ft/public/assert.hpp ft/public/templates/Rect.tpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp ftlua/public/Converter.hpp \
	ftlua/public/KeysWrapper.hpp ftlua/public/call.hpp ftlua/public/ftlua.hpp \
	ftlua/public/light.hpp ftlua/public/pop.hpp ftlua/public/push.hpp \
	ftlua/public/set.hpp ftlua/public/stackassert.hpp \
	ftlua/public/templates/ftlua_caller.tpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp liblua/lua-5.3.1/src/lauxlib.h \
	liblua/lua-5.3.1/src/lua.h liblua/lua-5.3.1/src/lua.hpp \
	liblua/lua-5.3.1/src/luaconf.h liblua/lua-5.3.1/src/lualib.h \
	| $(O_DIR)/ftlua/
$(O_DIR)/ftlua/push_utils.o: ftlua/push_utils.cpp ft/public/Rect.hpp \
	ft/public/Vec.hpp ft/public/assert.hpp ft/public/templates/Rect.tpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp ftlua/public/Converter.hpp \
	ftlua/public/KeysWrapper.hpp ftlua/public/call.hpp ftlua/public/ftlua.hpp \
	ftlua/public/light.hpp ftlua/public/pop.hpp ftlua/public/push.hpp \
	ftlua/public/set.hpp ftlua/public/stackassert.hpp \
	ftlua/public/templates/ftlua_caller.tpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp liblua/lua-5.3.1/src/lauxlib.h \
	liblua/lua-5.3.1/src/lua.h liblua/lua-5.3.1/src/lua.hpp \
	liblua/lua-5.3.1/src/luaconf.h liblua/lua-5.3.1/src/lualib.h \
	| $(O_DIR)/ftlua/
$(O_DIR)/ftlua/stackError.o: ftlua/stackError.cpp ftlua/public/stackassert.hpp \
	ftlua/public/utils.hpp liblua/lua-5.3.1/src/lauxlib.h \
	liblua/lua-5.3.1/src/lua.h liblua/lua-5.3.1/src/lua.hpp \
	liblua/lua-5.3.1/src/luaconf.h liblua/lua-5.3.1/src/lualib.h \
	| $(O_DIR)/ftlua/

# module ftui
$(O_DIR)/ftui/_public/ft $(O_DIR)/ftui/_public/ft_xml \
$(O_DIR)/ftui/_public/ftlua $(O_DIR)/ftui/_public/liblua \
$(O_DIR)/ftui/_public/ftui: | $(O_DIR)/ftui/_public/
$(O_DIR)/ftui/_public/ft: ft/public
$(O_DIR)/ftui/_public/ft_xml: ft_xml/public
$(O_DIR)/ftui/_public/ftlua: ftlua/public
$(O_DIR)/ftui/_public/liblua: liblua/lua-5.3.1/src
$(O_DIR)/ftui/_public/ftui: ftui/public

PUBLIC_LINKS += $(O_DIR)/ftui/_public/ft $(O_DIR)/ftui/_public/ft_xml \
	$(O_DIR)/ftui/_public/ftlua $(O_DIR)/ftui/_public/liblua \
	$(O_DIR)/ftui/_public/ftui

$(O_DIR)/ftui/ALayout.o $(O_DIR)/ftui/ALayout_luaHandler.o \
$(O_DIR)/ftui/ASolidView.o $(O_DIR)/ftui/AView.o \
$(O_DIR)/ftui/AView_luaHandler.o $(O_DIR)/ftui/AView_statics.o \
$(O_DIR)/ftui/Activity.o $(O_DIR)/ftui/Activity_RootViewHolder.o \
$(O_DIR)/ftui/Button.o $(O_DIR)/ftui/Canvas.o $(O_DIR)/ftui/HorizontalLayout.o \
$(O_DIR)/ftui/HorizontalLayout_ViewHolder.o $(O_DIR)/ftui/SolidView.o \
$(O_DIR)/ftui/TextView.o $(O_DIR)/ftui/VerticalLayout.o \
$(O_DIR)/ftui/VerticalLayout_ViewHolder.o: INCLUDE_FLAGS += \
	-I$(O_DIR)/ftui/_public
$(O_DIR)/ftui/ALayout.o $(O_DIR)/ftui/ALayout_luaHandler.o \
$(O_DIR)/ftui/ASolidView.o $(O_DIR)/ftui/AView.o \
$(O_DIR)/ftui/AView_luaHandler.o $(O_DIR)/ftui/AView_statics.o \
$(O_DIR)/ftui/Activity.o $(O_DIR)/ftui/Activity_RootViewHolder.o \
$(O_DIR)/ftui/Button.o $(O_DIR)/ftui/Canvas.o $(O_DIR)/ftui/HorizontalLayout.o \
$(O_DIR)/ftui/HorizontalLayout_ViewHolder.o $(O_DIR)/ftui/SolidView.o \
$(O_DIR)/ftui/TextView.o $(O_DIR)/ftui/VerticalLayout.o \
$(O_DIR)/ftui/VerticalLayout_ViewHolder.o: | $(O_DIR)/ftui/_public/ft \
	$(O_DIR)/ftui/_public/ft_xml $(O_DIR)/ftui/_public/ftlua \
	$(O_DIR)/ftui/_public/liblua $(O_DIR)/ftui/_public/ftui

$(O_DIR)/ftui/ALayout.o $(O_DIR)/ftui/ALayout_luaHandler.o \
$(O_DIR)/ftui/ASolidView.o $(O_DIR)/ftui/AView.o \
$(O_DIR)/ftui/AView_luaHandler.o $(O_DIR)/ftui/AView_statics.o \
$(O_DIR)/ftui/Activity.o $(O_DIR)/ftui/Activity_RootViewHolder.o \
$(O_DIR)/ftui/Button.o $(O_DIR)/ftui/Canvas.o $(O_DIR)/ftui/HorizontalLayout.o \
$(O_DIR)/ftui/HorizontalLayout_ViewHolder.o $(O_DIR)/ftui/SolidView.o \
$(O_DIR)/ftui/TextView.o $(O_DIR)/ftui/VerticalLayout.o \
$(O_DIR)/ftui/VerticalLayout_ViewHolder.o: BASE_FLAGS += -DRES_PATH='"$(abspath ftui/res/)"'
$(O_DIR)/ftui/ALayout.o: ftui/ALayout.cpp ft/public/Color.hpp \
	ft/public/Rect.hpp ft/public/Vec.hpp ft/public/assert.hpp \
	ft/public/templates/Rect.tpp ft/public/templates/Vec2.tpp \
	ft/public/templates/Vec3.tpp ft/public/templates/Vec4.tpp \
	ft/public/utils.hpp ft_xml/public/XmlParser.hpp \
	ft_xml/public/XmlTokenizer.hpp ftlua/public/Converter.hpp \
	ftlua/public/KeysWrapper.hpp ftlua/public/call.hpp ftlua/public/ftlua.hpp \
	ftlua/public/light.hpp ftlua/public/pop.hpp ftlua/public/push.hpp \
	ftlua/public/set.hpp ftlua/public/stackassert.hpp \
	ftlua/public/templates/ftlua_caller.tpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/ALayout.hpp ftui/public/ASolidView.hpp \
	ftui/public/AView.hpp ftui/public/Canvas.hpp ftui/public/IViewHolder.hpp \
	ftui/public/ftlua_extend.hpp ftui/public/libftui.hpp \
	ftui/public/templates/AView_callLuaCallback.tpp \
	liblua/lua-5.3.1/src/lauxlib.h liblua/lua-5.3.1/src/lua.h \
	liblua/lua-5.3.1/src/lua.hpp liblua/lua-5.3.1/src/luaconf.h \
	liblua/lua-5.3.1/src/lualib.h | $(O_DIR)/ftui/
$(O_DIR)/ftui/ALayout_luaHandler.o: ftui/ALayout_luaHandler.cpp \
	ft/public/Color.hpp ft/public/Rect.hpp ft/public/Vec.hpp \
	ft/public/assert.hpp ft/public/templates/Rect.tpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp ft/public/utils.hpp \
	ft_xml/public/XmlParser.hpp ft_xml/public/XmlTokenizer.hpp \
	ftlua/public/Converter.hpp ftlua/public/KeysWrapper.hpp \
	ftlua/public/call.hpp ftlua/public/ftlua.hpp ftlua/public/light.hpp \
	ftlua/public/pop.hpp ftlua/public/push.hpp ftlua/public/set.hpp \
	ftlua/public/stackassert.hpp ftlua/public/templates/ftlua_caller.tpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/ALayout.hpp ftui/public/ASolidView.hpp \
	ftui/public/AView.hpp ftui/public/Canvas.hpp ftui/public/ftlua_extend.hpp \
	ftui/public/libftui.hpp ftui/public/templates/AView_callLuaCallback.tpp \
	liblua/lua-5.3.1/src/lauxlib.h liblua/lua-5.3.1/src/lua.h \
	liblua/lua-5.3.1/src/lua.hpp liblua/lua-5.3.1/src/luaconf.h \
	liblua/lua-5.3.1/src/lualib.h | $(O_DIR)/ftui/
$(O_DIR)/ftui/ASolidView.o: ftui/ASolidView.cpp ft/public/Color.hpp \
	ft/public/Rect.hpp ft/public/Vec.hpp ft/public/assert.hpp \
	ft/public/templates/Rect.tpp ft/public/templates/Vec2.tpp \
	ft/public/templates/Vec3.tpp ft/public/templates/Vec4.tpp \
	ft/public/utils.hpp ft_xml/public/XmlParser.hpp \
	ft_xml/public/XmlTokenizer.hpp ftlua/public/Converter.hpp \
	ftlua/public/KeysWrapper.hpp ftlua/public/call.hpp ftlua/public/ftlua.hpp \
	ftlua/public/light.hpp ftlua/public/pop.hpp ftlua/public/push.hpp \
	ftlua/public/set.hpp ftlua/public/stackassert.hpp \
	ftlua/public/templates/ftlua_caller.tpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/ASolidView.hpp ftui/public/AView.hpp \
	ftui/public/Canvas.hpp ftui/public/IViewHolder.hpp \
	ftui/public/ftlua_extend.hpp ftui/public/libftui.hpp \
	ftui/public/templates/AView_callLuaCallback.tpp \
	liblua/lua-5.3.1/src/lauxlib.h liblua/lua-5.3.1/src/lua.h \
	liblua/lua-5.3.1/src/lua.hpp liblua/lua-5.3.1/src/luaconf.h \
	liblua/lua-5.3.1/src/lualib.h | $(O_DIR)/ftui/
$(O_DIR)/ftui/AView.o: ftui/AView.cpp ft/public/Color.hpp ft/public/Rect.hpp \
	ft/public/Vec.hpp ft/public/assert.hpp ft/public/templates/Rect.tpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp ft/public/utils.hpp \
	ft_xml/public/XmlParser.hpp ft_xml/public/XmlTokenizer.hpp \
	ftlua/public/Converter.hpp ftlua/public/KeysWrapper.hpp \
	ftlua/public/call.hpp ftlua/public/ftlua.hpp ftlua/public/light.hpp \
	ftlua/public/pop.hpp ftlua/public/push.hpp ftlua/public/set.hpp \
	ftlua/public/stackassert.hpp ftlua/public/templates/ftlua_caller.tpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/ALayout.hpp ftui/public/ASolidView.hpp \
	ftui/public/AView.hpp ftui/public/Activity.hpp ftui/public/Canvas.hpp \
	ftui/public/DefaultEventBox.hpp ftui/public/EventBox.hpp \
	ftui/public/EventParams.hpp ftui/public/IEventBox.hpp \
	ftui/public/IEventParams.hpp ftui/public/IViewHolder.hpp \
	ftui/public/VerticalLayout.hpp ftui/public/ftlua_extend.hpp \
	ftui/public/libftui.hpp ftui/public/templates/AView_callLuaCallback.tpp \
	ftui/public/templates/Activity.tpp \
	ftui/public/templates/DefaultEventBox.tpp \
	ftui/public/templates/EventBox.tpp liblua/lua-5.3.1/src/lauxlib.h \
	liblua/lua-5.3.1/src/lua.h liblua/lua-5.3.1/src/lua.hpp \
	liblua/lua-5.3.1/src/luaconf.h liblua/lua-5.3.1/src/lualib.h \
	| $(O_DIR)/ftui/
$(O_DIR)/ftui/AView_luaHandler.o: ftui/AView_luaHandler.cpp \
	ft/public/Color.hpp ft/public/Rect.hpp ft/public/Vec.hpp \
	ft/public/assert.hpp ft/public/templates/Rect.tpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp ft/public/utils.hpp \
	ft_xml/public/XmlParser.hpp ft_xml/public/XmlTokenizer.hpp \
	ftlua/public/Converter.hpp ftlua/public/KeysWrapper.hpp \
	ftlua/public/call.hpp ftlua/public/ftlua.hpp ftlua/public/light.hpp \
	ftlua/public/pop.hpp ftlua/public/push.hpp ftlua/public/set.hpp \
	ftlua/public/stackassert.hpp ftlua/public/templates/ftlua_caller.tpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/ALayout.hpp ftui/public/ASolidView.hpp \
	ftui/public/AView.hpp ftui/public/Canvas.hpp ftui/public/IViewHolder.hpp \
	ftui/public/TextView.hpp ftui/public/ftlua_extend.hpp \
	ftui/public/libftui.hpp ftui/public/templates/AView_callLuaCallback.tpp \
	liblua/lua-5.3.1/src/lauxlib.h liblua/lua-5.3.1/src/lua.h \
	liblua/lua-5.3.1/src/lua.hpp liblua/lua-5.3.1/src/luaconf.h \
	liblua/lua-5.3.1/src/lualib.h | $(O_DIR)/ftui/
$(O_DIR)/ftui/AView_statics.o: ftui/AView_statics.cpp ft/public/Color.hpp \
	ft/public/Rect.hpp ft/public/Vec.hpp ft/public/assert.hpp \
	ft/public/templates/Rect.tpp ft/public/templates/Vec2.tpp \
	ft/public/templates/Vec3.tpp ft/public/templates/Vec4.tpp \
	ft/public/utils.hpp ft_xml/public/XmlParser.hpp \
	ft_xml/public/XmlTokenizer.hpp ftlua/public/Converter.hpp \
	ftlua/public/KeysWrapper.hpp ftlua/public/call.hpp ftlua/public/ftlua.hpp \
	ftlua/public/light.hpp ftlua/public/pop.hpp ftlua/public/push.hpp \
	ftlua/public/set.hpp ftlua/public/stackassert.hpp \
	ftlua/public/templates/ftlua_caller.tpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/ALayout.hpp ftui/public/ASolidView.hpp \
	ftui/public/AView.hpp ftui/public/Button.hpp ftui/public/Canvas.hpp \
	ftui/public/HorizontalLayout.hpp ftui/public/IViewHolder.hpp \
	ftui/public/SolidView.hpp ftui/public/TextView.hpp \
	ftui/public/VerticalLayout.hpp ftui/public/ftlua_extend.hpp \
	ftui/public/libftui.hpp ftui/public/templates/AView_callLuaCallback.tpp \
	liblua/lua-5.3.1/src/lauxlib.h liblua/lua-5.3.1/src/lua.h \
	liblua/lua-5.3.1/src/lua.hpp liblua/lua-5.3.1/src/luaconf.h \
	liblua/lua-5.3.1/src/lualib.h | $(O_DIR)/ftui/
$(O_DIR)/ftui/Activity.o: ftui/Activity.cpp ft/public/Color.hpp \
	ft/public/Rect.hpp ft/public/Vec.hpp ft/public/assert.hpp \
	ft/public/templates/Rect.tpp ft/public/templates/Vec2.tpp \
	ft/public/templates/Vec3.tpp ft/public/templates/Vec4.tpp \
	ft/public/utils.hpp ft_xml/public/XmlParser.hpp \
	ft_xml/public/XmlTokenizer.hpp ftlua/public/Converter.hpp \
	ftlua/public/KeysWrapper.hpp ftlua/public/call.hpp ftlua/public/ftlua.hpp \
	ftlua/public/light.hpp ftlua/public/pop.hpp ftlua/public/push.hpp \
	ftlua/public/set.hpp ftlua/public/stackassert.hpp \
	ftlua/public/templates/ftlua_caller.tpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/AView.hpp ftui/public/Activity.hpp \
	ftui/public/Canvas.hpp ftui/public/DefaultEventBox.hpp \
	ftui/public/EventBox.hpp ftui/public/EventParams.hpp \
	ftui/public/IEventBox.hpp ftui/public/IEventParams.hpp \
	ftui/public/IViewHolder.hpp ftui/public/ftlua_extend.hpp \
	ftui/public/libftui.hpp ftui/public/templates/AView_callLuaCallback.tpp \
	ftui/public/templates/Activity.tpp \
	ftui/public/templates/DefaultEventBox.tpp \
	ftui/public/templates/EventBox.tpp liblua/lua-5.3.1/src/lauxlib.h \
	liblua/lua-5.3.1/src/lua.h liblua/lua-5.3.1/src/lua.hpp \
	liblua/lua-5.3.1/src/luaconf.h liblua/lua-5.3.1/src/lualib.h \
	| $(O_DIR)/ftui/
$(O_DIR)/ftui/Activity_RootViewHolder.o: ftui/Activity_RootViewHolder.cpp \
	ft/public/Rect.hpp ft/public/Vec.hpp ft/public/assert.hpp \
	ft/public/templates/Rect.tpp ft/public/templates/Vec2.tpp \
	ft/public/templates/Vec3.tpp ft/public/templates/Vec4.tpp \
	ft_xml/public/XmlParser.hpp ft_xml/public/XmlTokenizer.hpp \
	ftlua/public/Converter.hpp ftlua/public/KeysWrapper.hpp \
	ftlua/public/call.hpp ftlua/public/ftlua.hpp ftlua/public/light.hpp \
	ftlua/public/pop.hpp ftlua/public/push.hpp ftlua/public/set.hpp \
	ftlua/public/stackassert.hpp ftlua/public/templates/ftlua_caller.tpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/AView.hpp ftui/public/Activity.hpp \
	ftui/public/DefaultEventBox.hpp ftui/public/EventBox.hpp \
	ftui/public/EventParams.hpp ftui/public/IEventBox.hpp \
	ftui/public/IEventParams.hpp ftui/public/IViewHolder.hpp \
	ftui/public/ftlua_extend.hpp ftui/public/libftui.hpp \
	ftui/public/templates/AView_callLuaCallback.tpp \
	ftui/public/templates/Activity.tpp \
	ftui/public/templates/DefaultEventBox.tpp \
	ftui/public/templates/EventBox.tpp liblua/lua-5.3.1/src/lauxlib.h \
	liblua/lua-5.3.1/src/lua.h liblua/lua-5.3.1/src/lua.hpp \
	liblua/lua-5.3.1/src/luaconf.h liblua/lua-5.3.1/src/lualib.h \
	| $(O_DIR)/ftui/
$(O_DIR)/ftui/Button.o: ftui/Button.cpp ft/public/Color.hpp ft/public/Rect.hpp \
	ft/public/Vec.hpp ft/public/assert.hpp ft/public/templates/Rect.tpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp ft/public/utils.hpp \
	ft_xml/public/XmlParser.hpp ft_xml/public/XmlTokenizer.hpp \
	ftlua/public/Converter.hpp ftlua/public/KeysWrapper.hpp \
	ftlua/public/call.hpp ftlua/public/ftlua.hpp ftlua/public/light.hpp \
	ftlua/public/pop.hpp ftlua/public/push.hpp ftlua/public/set.hpp \
	ftlua/public/stackassert.hpp ftlua/public/templates/ftlua_caller.tpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/AView.hpp ftui/public/Activity.hpp \
	ftui/public/Button.hpp ftui/public/Canvas.hpp \
	ftui/public/DefaultEventBox.hpp ftui/public/EventBox.hpp \
	ftui/public/EventParams.hpp ftui/public/IEventBox.hpp \
	ftui/public/IEventParams.hpp ftui/public/IViewHolder.hpp \
	ftui/public/ftlua_extend.hpp ftui/public/libftui.hpp \
	ftui/public/templates/AView_callLuaCallback.tpp \
	ftui/public/templates/Activity.tpp \
	ftui/public/templates/DefaultEventBox.tpp \
	ftui/public/templates/EventBox.tpp liblua/lua-5.3.1/src/lauxlib.h \
	liblua/lua-5.3.1/src/lua.h liblua/lua-5.3.1/src/lua.hpp \
	liblua/lua-5.3.1/src/luaconf.h liblua/lua-5.3.1/src/lualib.h \
	| $(O_DIR)/ftui/
$(O_DIR)/ftui/Canvas.o: ftui/Canvas.cpp ft/public/Color.hpp ft/public/Rect.hpp \
	ft/public/Vec.hpp ft/public/assert.hpp ft/public/templates/Rect.tpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp ft/public/utils.hpp \
	ftlua/public/Converter.hpp ftlua/public/KeysWrapper.hpp \
	ftlua/public/call.hpp ftlua/public/ftlua.hpp ftlua/public/light.hpp \
	ftlua/public/pop.hpp ftlua/public/push.hpp ftlua/public/set.hpp \
	ftlua/public/stackassert.hpp ftlua/public/templates/ftlua_caller.tpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/Canvas.hpp ftui/public/ftlua_extend.hpp \
	ftui/public/libftui.hpp liblua/lua-5.3.1/src/lauxlib.h \
	liblua/lua-5.3.1/src/lua.h liblua/lua-5.3.1/src/lua.hpp \
	liblua/lua-5.3.1/src/luaconf.h liblua/lua-5.3.1/src/lualib.h \
	| $(O_DIR)/ftui/
$(O_DIR)/ftui/HorizontalLayout.o: ftui/HorizontalLayout.cpp \
	ft/public/Color.hpp ft/public/Rect.hpp ft/public/Vec.hpp \
	ft/public/assert.hpp ft/public/templates/Rect.tpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp ft/public/utils.hpp \
	ft_xml/public/XmlParser.hpp ft_xml/public/XmlTokenizer.hpp \
	ftlua/public/Converter.hpp ftlua/public/KeysWrapper.hpp \
	ftlua/public/call.hpp ftlua/public/ftlua.hpp ftlua/public/light.hpp \
	ftlua/public/pop.hpp ftlua/public/push.hpp ftlua/public/set.hpp \
	ftlua/public/stackassert.hpp ftlua/public/templates/ftlua_caller.tpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/ALayout.hpp ftui/public/ASolidView.hpp \
	ftui/public/AView.hpp ftui/public/Canvas.hpp \
	ftui/public/HorizontalLayout.hpp ftui/public/IViewHolder.hpp \
	ftui/public/ftlua_extend.hpp ftui/public/libftui.hpp \
	ftui/public/templates/AView_callLuaCallback.tpp \
	liblua/lua-5.3.1/src/lauxlib.h liblua/lua-5.3.1/src/lua.h \
	liblua/lua-5.3.1/src/lua.hpp liblua/lua-5.3.1/src/luaconf.h \
	liblua/lua-5.3.1/src/lualib.h | $(O_DIR)/ftui/
$(O_DIR)/ftui/HorizontalLayout_ViewHolder.o: \
	ftui/HorizontalLayout_ViewHolder.cpp ft/public/Color.hpp \
	ft/public/Rect.hpp ft/public/Vec.hpp ft/public/assert.hpp \
	ft/public/templates/Rect.tpp ft/public/templates/Vec2.tpp \
	ft/public/templates/Vec3.tpp ft/public/templates/Vec4.tpp \
	ft/public/utils.hpp ft_xml/public/XmlParser.hpp \
	ft_xml/public/XmlTokenizer.hpp ftlua/public/Converter.hpp \
	ftlua/public/KeysWrapper.hpp ftlua/public/call.hpp ftlua/public/ftlua.hpp \
	ftlua/public/light.hpp ftlua/public/pop.hpp ftlua/public/push.hpp \
	ftlua/public/set.hpp ftlua/public/stackassert.hpp \
	ftlua/public/templates/ftlua_caller.tpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/ALayout.hpp ftui/public/ASolidView.hpp \
	ftui/public/AView.hpp ftui/public/Activity.hpp ftui/public/Canvas.hpp \
	ftui/public/DefaultEventBox.hpp ftui/public/EventBox.hpp \
	ftui/public/EventParams.hpp ftui/public/HorizontalLayout.hpp \
	ftui/public/IEventBox.hpp ftui/public/IEventParams.hpp \
	ftui/public/IViewHolder.hpp ftui/public/ftlua_extend.hpp \
	ftui/public/libftui.hpp ftui/public/templates/AView_callLuaCallback.tpp \
	ftui/public/templates/Activity.tpp \
	ftui/public/templates/DefaultEventBox.tpp \
	ftui/public/templates/EventBox.tpp liblua/lua-5.3.1/src/lauxlib.h \
	liblua/lua-5.3.1/src/lua.h liblua/lua-5.3.1/src/lua.hpp \
	liblua/lua-5.3.1/src/luaconf.h liblua/lua-5.3.1/src/lualib.h \
	| $(O_DIR)/ftui/
$(O_DIR)/ftui/SolidView.o: ftui/SolidView.cpp ft/public/Color.hpp \
	ft/public/Rect.hpp ft/public/Vec.hpp ft/public/assert.hpp \
	ft/public/templates/Rect.tpp ft/public/templates/Vec2.tpp \
	ft/public/templates/Vec3.tpp ft/public/templates/Vec4.tpp \
	ft/public/utils.hpp ft_xml/public/XmlParser.hpp \
	ft_xml/public/XmlTokenizer.hpp ftlua/public/Converter.hpp \
	ftlua/public/KeysWrapper.hpp ftlua/public/call.hpp ftlua/public/ftlua.hpp \
	ftlua/public/light.hpp ftlua/public/pop.hpp ftlua/public/push.hpp \
	ftlua/public/set.hpp ftlua/public/stackassert.hpp \
	ftlua/public/templates/ftlua_caller.tpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/ASolidView.hpp ftui/public/AView.hpp \
	ftui/public/Canvas.hpp ftui/public/SolidView.hpp \
	ftui/public/ftlua_extend.hpp ftui/public/libftui.hpp \
	ftui/public/templates/AView_callLuaCallback.tpp \
	liblua/lua-5.3.1/src/lauxlib.h liblua/lua-5.3.1/src/lua.h \
	liblua/lua-5.3.1/src/lua.hpp liblua/lua-5.3.1/src/luaconf.h \
	liblua/lua-5.3.1/src/lualib.h | $(O_DIR)/ftui/
$(O_DIR)/ftui/TextView.o: ftui/TextView.cpp ft/public/Color.hpp \
	ft/public/Rect.hpp ft/public/Vec.hpp ft/public/assert.hpp \
	ft/public/templates/Rect.tpp ft/public/templates/Vec2.tpp \
	ft/public/templates/Vec3.tpp ft/public/templates/Vec4.tpp \
	ft/public/utils.hpp ft_xml/public/XmlParser.hpp \
	ft_xml/public/XmlTokenizer.hpp ftlua/public/Converter.hpp \
	ftlua/public/KeysWrapper.hpp ftlua/public/call.hpp ftlua/public/ftlua.hpp \
	ftlua/public/light.hpp ftlua/public/pop.hpp ftlua/public/push.hpp \
	ftlua/public/set.hpp ftlua/public/stackassert.hpp \
	ftlua/public/templates/ftlua_caller.tpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/ASolidView.hpp ftui/public/AView.hpp \
	ftui/public/Canvas.hpp ftui/public/IViewHolder.hpp \
	ftui/public/TextView.hpp ftui/public/ftlua_extend.hpp \
	ftui/public/libftui.hpp ftui/public/templates/AView_callLuaCallback.tpp \
	liblua/lua-5.3.1/src/lauxlib.h liblua/lua-5.3.1/src/lua.h \
	liblua/lua-5.3.1/src/lua.hpp liblua/lua-5.3.1/src/luaconf.h \
	liblua/lua-5.3.1/src/lualib.h | $(O_DIR)/ftui/
$(O_DIR)/ftui/VerticalLayout.o: ftui/VerticalLayout.cpp ft/public/Color.hpp \
	ft/public/Rect.hpp ft/public/Vec.hpp ft/public/assert.hpp \
	ft/public/templates/Rect.tpp ft/public/templates/Vec2.tpp \
	ft/public/templates/Vec3.tpp ft/public/templates/Vec4.tpp \
	ft/public/utils.hpp ft_xml/public/XmlParser.hpp \
	ft_xml/public/XmlTokenizer.hpp ftlua/public/Converter.hpp \
	ftlua/public/KeysWrapper.hpp ftlua/public/call.hpp ftlua/public/ftlua.hpp \
	ftlua/public/light.hpp ftlua/public/pop.hpp ftlua/public/push.hpp \
	ftlua/public/set.hpp ftlua/public/stackassert.hpp \
	ftlua/public/templates/ftlua_caller.tpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/ALayout.hpp ftui/public/ASolidView.hpp \
	ftui/public/AView.hpp ftui/public/Canvas.hpp ftui/public/IViewHolder.hpp \
	ftui/public/VerticalLayout.hpp ftui/public/ftlua_extend.hpp \
	ftui/public/libftui.hpp ftui/public/templates/AView_callLuaCallback.tpp \
	liblua/lua-5.3.1/src/lauxlib.h liblua/lua-5.3.1/src/lua.h \
	liblua/lua-5.3.1/src/lua.hpp liblua/lua-5.3.1/src/luaconf.h \
	liblua/lua-5.3.1/src/lualib.h | $(O_DIR)/ftui/
$(O_DIR)/ftui/VerticalLayout_ViewHolder.o: ftui/VerticalLayout_ViewHolder.cpp \
	ft/public/Color.hpp ft/public/Rect.hpp ft/public/Vec.hpp \
	ft/public/assert.hpp ft/public/templates/Rect.tpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp ft/public/utils.hpp \
	ft_xml/public/XmlParser.hpp ft_xml/public/XmlTokenizer.hpp \
	ftlua/public/Converter.hpp ftlua/public/KeysWrapper.hpp \
	ftlua/public/call.hpp ftlua/public/ftlua.hpp ftlua/public/light.hpp \
	ftlua/public/pop.hpp ftlua/public/push.hpp ftlua/public/set.hpp \
	ftlua/public/stackassert.hpp ftlua/public/templates/ftlua_caller.tpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/ALayout.hpp ftui/public/ASolidView.hpp \
	ftui/public/AView.hpp ftui/public/Activity.hpp ftui/public/Canvas.hpp \
	ftui/public/DefaultEventBox.hpp ftui/public/EventBox.hpp \
	ftui/public/EventParams.hpp ftui/public/IEventBox.hpp \
	ftui/public/IEventParams.hpp ftui/public/IViewHolder.hpp \
	ftui/public/VerticalLayout.hpp ftui/public/ftlua_extend.hpp \
	ftui/public/libftui.hpp ftui/public/templates/AView_callLuaCallback.tpp \
	ftui/public/templates/Activity.tpp \
	ftui/public/templates/DefaultEventBox.tpp \
	ftui/public/templates/EventBox.tpp liblua/lua-5.3.1/src/lauxlib.h \
	liblua/lua-5.3.1/src/lua.h liblua/lua-5.3.1/src/lua.hpp \
	liblua/lua-5.3.1/src/luaconf.h liblua/lua-5.3.1/src/lualib.h \
	| $(O_DIR)/ftui/

# module gl
ifeq ($(shell uname),Darwin)
  BASE_FLAGS += -DMAC_OS_MODE=1
  LINK_FLAGS += -lglfw3 -framework OpenGL
else
  LINK_FLAGS += -lglfw -lGL -lGLEW
endif
$(O_DIR)/gl/_public/gl: | $(O_DIR)/gl/_public/
$(O_DIR)/gl/_public/gl: gl

PUBLIC_LINKS += $(O_DIR)/gl/_public/gl

:INCLUDE_FLAGS += -I$(O_DIR)/gl/_public
:|$(O_DIR)/gl/_public/gl


# module liblua
LIBLUA_DIR		:= liblua/lua-5.3.1
LIBLUA_PLATFORM	:= posix
LIBLUA_ARCHIVE	:= $(LIBLUA_DIR).tar.gz
LIBLUA_LIB		:= $(LIBLUA_DIR)/src/liblua.a
LIBLUA			:= liblua/liblua.a

_PLATFORM		:= $(shell uname)

ifeq ($(_PLATFORM),Linux)
  LIBLUA_PLATFORM = linux
else
  ifeq ($(_PLATFORM),Darwin)
    LIBLUA_PLATFORM = macosx
  endif
endif

liblua: $(LIBLUA)
.PHONY: liblua

$(LIBLUA):
	echo Extract lua
	tar -x -C liblua -f $(LIBLUA_ARCHIVE)
	echo "Make lua ($(LIBLUA_PLATFORM))"
	make -C $(LIBLUA_DIR) $(LIBLUA_PLATFORM)
	cp $(LIBLUA_LIB) $(LIBLUA)
	echo Done
$(O_DIR)/liblua/_public/liblua: | $(O_DIR)/liblua/_public/
$(O_DIR)/liblua/_public/liblua: liblua/lua-5.3.1/src

PUBLIC_LINKS += $(O_DIR)/liblua/_public/liblua

:INCLUDE_FLAGS += -I$(O_DIR)/liblua/_public
:|$(O_DIR)/liblua/_public/liblua


# module tiles
$(O_DIR)/tiles/_public/gl $(O_DIR)/tiles/_public/ft \
$(O_DIR)/tiles/_public/tiles: | $(O_DIR)/tiles/_public/
$(O_DIR)/tiles/_public/gl: gl
$(O_DIR)/tiles/_public/ft: ft/public
$(O_DIR)/tiles/_public/tiles: tiles/include

PUBLIC_LINKS += $(O_DIR)/tiles/_public/gl $(O_DIR)/tiles/_public/ft \
	$(O_DIR)/tiles/_public/tiles

$(O_DIR)/tiles/Tiles.o: INCLUDE_FLAGS += -I$(O_DIR)/tiles/_public
$(O_DIR)/tiles/Tiles.o: | $(O_DIR)/tiles/_public/gl $(O_DIR)/tiles/_public/ft \
	$(O_DIR)/tiles/_public/tiles

$(O_DIR)/tiles/Tiles.o: tiles/Tiles.cpp ft/public/Vec.hpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp gl/gl.h gl/gl.hpp tiles/include/Tiles.hpp \
	| $(O_DIR)/tiles/
