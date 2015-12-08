INCLUDE_FLAGS += -I$(O_DIR)/_public
LIBS_RULES += liblua
LINK_FLAGS += -lfreetype -Lliblua/lua-5.3.1/src -llua
OBJ_DIR_TREE += $(O_DIR)/tiles/ $(O_DIR)/gl_canvas/ $(O_DIR)/ftui/ \
	$(O_DIR)/ftlua/ $(O_DIR)/ft_xml/srcs/ $(O_DIR)/ft_xml/ $(O_DIR)/ft/ \
	$(O_DIR)/_public/tiles/ $(O_DIR)/_public/liblua/ \
	$(O_DIR)/_public/gl_canvas/ $(O_DIR)/_public/gl/ \
	$(O_DIR)/_public/ftui/templates/ $(O_DIR)/_public/ftui/ \
	$(O_DIR)/_public/ftlua/templates/ $(O_DIR)/_public/ftlua/ \
	$(O_DIR)/_public/ftce/ $(O_DIR)/_public/ft_xml/ \
	$(O_DIR)/_public/ft/templates/ $(O_DIR)/_public/ft/ $(O_DIR)/_public/ \
	$(O_DIR)/
O_FILES += $(O_DIR)/ft/assert.o $(O_DIR)/ft/padformat.o \
	$(O_DIR)/ft_xml/srcs/XmlParser.o $(O_DIR)/ft_xml/srcs/XmlTokenizer.o \
	$(O_DIR)/ftlua/cpp_utils.o $(O_DIR)/ftlua/push_utils.o \
	$(O_DIR)/ftlua/stackError.o $(O_DIR)/ftui/ACanvas.o \
	$(O_DIR)/ftui/ALayout.o $(O_DIR)/ftui/ALayout_luaHandler.o \
	$(O_DIR)/ftui/ASolidView.o $(O_DIR)/ftui/AView.o \
	$(O_DIR)/ftui/AView_luaHandler.o $(O_DIR)/ftui/Activity.o \
	$(O_DIR)/ftui/Activity_RootViewHolder.o $(O_DIR)/ftui/Activity_luaDef.o \
	$(O_DIR)/ftui/Button.o $(O_DIR)/ftui/CheckBox.o \
	$(O_DIR)/ftui/EventTarget.o $(O_DIR)/ftui/LinearLayout.o \
	$(O_DIR)/ftui/LinearLayout_ViewHolder.o $(O_DIR)/ftui/ScrollableLayout.o \
	$(O_DIR)/ftui/SliderView.o $(O_DIR)/ftui/SolidView.o \
	$(O_DIR)/ftui/TextView.o $(O_DIR)/ftui/ViewTemplate.o \
	$(O_DIR)/gl_canvas/GlCanvas.o $(O_DIR)/gl_canvas/GlCanvasHolder.o \
	$(O_DIR)/tiles/Tiles.o
PUBLIC_LINKS += $(O_DIR)/_public/ft/assert.hpp $(O_DIR)/_public/ft/Color.hpp \
	$(O_DIR)/_public/ft/padformat.hpp $(O_DIR)/_public/ft/Rect.hpp \
	$(O_DIR)/_public/ft/TupleRef.hpp $(O_DIR)/_public/ft/type_traits.hpp \
	$(O_DIR)/_public/ft/utils.hpp $(O_DIR)/_public/ft/Vec.hpp \
	$(O_DIR)/_public/ft/templates/Rect.tpp \
	$(O_DIR)/_public/ft/templates/Vec2.tpp \
	$(O_DIR)/_public/ft/templates/Vec3.tpp \
	$(O_DIR)/_public/ft/templates/Vec4.tpp \
	$(O_DIR)/_public/ft_xml/XmlParser.hpp \
	$(O_DIR)/_public/ft_xml/XmlTokenizer.hpp $(O_DIR)/_public/ftce/Array.hpp \
	$(O_DIR)/_public/ftce/Array.tpp $(O_DIR)/_public/ftce/math.hpp \
	$(O_DIR)/_public/ftlua/call.hpp $(O_DIR)/_public/ftlua/conversions.hpp \
	$(O_DIR)/_public/ftlua/ftlua.hpp $(O_DIR)/_public/ftlua/KeysWrapper.hpp \
	$(O_DIR)/_public/ftlua/light.hpp $(O_DIR)/_public/ftlua/pop.hpp \
	$(O_DIR)/_public/ftlua/push.hpp $(O_DIR)/_public/ftlua/set.hpp \
	$(O_DIR)/_public/ftlua/size.hpp $(O_DIR)/_public/ftlua/stackassert.hpp \
	$(O_DIR)/_public/ftlua/types.hpp $(O_DIR)/_public/ftlua/utils.hpp \
	$(O_DIR)/_public/ftlua/templates/ftlua_handler.tpp \
	$(O_DIR)/_public/ftui/AbsoluteLayout.hpp $(O_DIR)/_public/ftui/ACanvas.hpp \
	$(O_DIR)/_public/ftui/Activity.hpp $(O_DIR)/_public/ftui/ALayout.hpp \
	$(O_DIR)/_public/ftui/ASolidView.hpp $(O_DIR)/_public/ftui/AView.hpp \
	$(O_DIR)/_public/ftui/Button.hpp $(O_DIR)/_public/ftui/CheckBox.hpp \
	$(O_DIR)/_public/ftui/EventTarget.hpp \
	$(O_DIR)/_public/ftui/EventTargetCpp.hpp \
	$(O_DIR)/_public/ftui/IViewHolder.hpp $(O_DIR)/_public/ftui/libftui.hpp \
	$(O_DIR)/_public/ftui/LinearLayout.hpp \
	$(O_DIR)/_public/ftui/RelativeLayout.hpp \
	$(O_DIR)/_public/ftui/ScrollableLayout.hpp \
	$(O_DIR)/_public/ftui/SliderView.hpp $(O_DIR)/_public/ftui/SolidView.hpp \
	$(O_DIR)/_public/ftui/TextView.hpp $(O_DIR)/_public/ftui/ViewTemplate.hpp \
	$(O_DIR)/_public/ftui/templates/Activity.tpp \
	$(O_DIR)/_public/ftui/templates/AView_callLuaCallback.tpp \
	$(O_DIR)/_public/gl/gl.h $(O_DIR)/_public/gl/gl.hpp \
	$(O_DIR)/_public/gl_canvas/GlCanvas.hpp \
	$(O_DIR)/_public/gl_canvas/GlCanvasHolder.hpp \
	$(O_DIR)/_public/liblua/lapi.c $(O_DIR)/_public/liblua/lapi.h \
	$(O_DIR)/_public/liblua/lauxlib.c $(O_DIR)/_public/liblua/lauxlib.h \
	$(O_DIR)/_public/liblua/lbaselib.c $(O_DIR)/_public/liblua/lbitlib.c \
	$(O_DIR)/_public/liblua/lcode.c $(O_DIR)/_public/liblua/lcode.h \
	$(O_DIR)/_public/liblua/lcorolib.c $(O_DIR)/_public/liblua/lctype.c \
	$(O_DIR)/_public/liblua/lctype.h $(O_DIR)/_public/liblua/ldblib.c \
	$(O_DIR)/_public/liblua/ldebug.c $(O_DIR)/_public/liblua/ldebug.h \
	$(O_DIR)/_public/liblua/ldo.c $(O_DIR)/_public/liblua/ldo.h \
	$(O_DIR)/_public/liblua/ldump.c $(O_DIR)/_public/liblua/lfunc.c \
	$(O_DIR)/_public/liblua/lfunc.h $(O_DIR)/_public/liblua/lgc.c \
	$(O_DIR)/_public/liblua/lgc.h $(O_DIR)/_public/liblua/linit.c \
	$(O_DIR)/_public/liblua/liolib.c $(O_DIR)/_public/liblua/llex.c \
	$(O_DIR)/_public/liblua/llex.h $(O_DIR)/_public/liblua/llimits.h \
	$(O_DIR)/_public/liblua/lmathlib.c $(O_DIR)/_public/liblua/lmem.c \
	$(O_DIR)/_public/liblua/lmem.h $(O_DIR)/_public/liblua/loadlib.c \
	$(O_DIR)/_public/liblua/lobject.c $(O_DIR)/_public/liblua/lobject.h \
	$(O_DIR)/_public/liblua/lopcodes.c $(O_DIR)/_public/liblua/lopcodes.h \
	$(O_DIR)/_public/liblua/loslib.c $(O_DIR)/_public/liblua/lparser.c \
	$(O_DIR)/_public/liblua/lparser.h $(O_DIR)/_public/liblua/lprefix.h \
	$(O_DIR)/_public/liblua/lstate.c $(O_DIR)/_public/liblua/lstate.h \
	$(O_DIR)/_public/liblua/lstring.c $(O_DIR)/_public/liblua/lstring.h \
	$(O_DIR)/_public/liblua/lstrlib.c $(O_DIR)/_public/liblua/ltable.c \
	$(O_DIR)/_public/liblua/ltable.h $(O_DIR)/_public/liblua/ltablib.c \
	$(O_DIR)/_public/liblua/ltm.c $(O_DIR)/_public/liblua/ltm.h \
	$(O_DIR)/_public/liblua/lua.c $(O_DIR)/_public/liblua/lua.h \
	$(O_DIR)/_public/liblua/lua.hpp $(O_DIR)/_public/liblua/luac.c \
	$(O_DIR)/_public/liblua/luaconf.h $(O_DIR)/_public/liblua/lualib.h \
	$(O_DIR)/_public/liblua/lundump.c $(O_DIR)/_public/liblua/lundump.h \
	$(O_DIR)/_public/liblua/lutf8lib.c $(O_DIR)/_public/liblua/lvm.c \
	$(O_DIR)/_public/liblua/lvm.h $(O_DIR)/_public/liblua/lzio.c \
	$(O_DIR)/_public/liblua/lzio.h $(O_DIR)/_public/tiles/Tiles.hpp

# module ft::ft
$(O_DIR)/ft/assert.o: ft/assert.cpp ft/public/Rect.hpp ft/public/Vec.hpp \
	ft/public/assert.hpp ft/public/templates/Rect.tpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp ft/public/type_traits.hpp ft/public/utils.hpp
$(O_DIR)/ft/padformat.o: ft/padformat.cpp ft/public/Rect.hpp ft/public/Vec.hpp \
	ft/public/assert.hpp ft/public/templates/Rect.tpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp ft/public/type_traits.hpp ft/public/utils.hpp

# module ft_xml::ft_xml
$(O_DIR)/ft_xml/srcs/XmlParser.o: ft_xml/srcs/XmlParser.cpp ft/public/Rect.hpp \
	ft/public/Vec.hpp ft/public/templates/Rect.tpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp ft/public/type_traits.hpp ft/public/utils.hpp \
	ft_xml/public/XmlParser.hpp ft_xml/public/XmlTokenizer.hpp
$(O_DIR)/ft_xml/srcs/XmlTokenizer.o: ft_xml/srcs/XmlTokenizer.cpp \
	ft/public/Rect.hpp ft/public/Vec.hpp ft/public/templates/Rect.tpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp ft/public/type_traits.hpp ft/public/utils.hpp \
	ft_xml/public/XmlTokenizer.hpp

# module ftce::ftce

# module ftlua::ftlua
$(O_DIR)/ftlua/cpp_utils.o: ftlua/cpp_utils.cpp ft/public/Rect.hpp \
	ft/public/Vec.hpp ft/public/templates/Rect.tpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp ft/public/type_traits.hpp \
	ftlua/public/KeysWrapper.hpp ftlua/public/call.hpp \
	ftlua/public/conversions.hpp ftlua/public/ftlua.hpp ftlua/public/light.hpp \
	ftlua/public/pop.hpp ftlua/public/push.hpp ftlua/public/set.hpp \
	ftlua/public/size.hpp ftlua/public/stackassert.hpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp liblua/lua-5.3.1/src/lauxlib.h \
	liblua/lua-5.3.1/src/lua.h liblua/lua-5.3.1/src/lua.hpp \
	liblua/lua-5.3.1/src/luaconf.h liblua/lua-5.3.1/src/lualib.h
$(O_DIR)/ftlua/push_utils.o: ftlua/push_utils.cpp ft/public/Rect.hpp \
	ft/public/Vec.hpp ft/public/assert.hpp ft/public/templates/Rect.tpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp ft/public/type_traits.hpp \
	ftlua/public/KeysWrapper.hpp ftlua/public/call.hpp \
	ftlua/public/conversions.hpp ftlua/public/ftlua.hpp ftlua/public/light.hpp \
	ftlua/public/pop.hpp ftlua/public/push.hpp ftlua/public/set.hpp \
	ftlua/public/size.hpp ftlua/public/stackassert.hpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp liblua/lua-5.3.1/src/lauxlib.h \
	liblua/lua-5.3.1/src/lua.h liblua/lua-5.3.1/src/lua.hpp \
	liblua/lua-5.3.1/src/luaconf.h liblua/lua-5.3.1/src/lualib.h
$(O_DIR)/ftlua/stackError.o: ftlua/stackError.cpp ftlua/public/stackassert.hpp \
	ftlua/public/utils.hpp liblua/lua-5.3.1/src/lauxlib.h \
	liblua/lua-5.3.1/src/lua.h liblua/lua-5.3.1/src/lua.hpp \
	liblua/lua-5.3.1/src/luaconf.h liblua/lua-5.3.1/src/lualib.h

$(O_DIR)/ftlua/cpp_utils.o $(O_DIR)/ftlua/push_utils.o \
$(O_DIR)/ftlua/stackError.o: BASE_FLAGS += -DRES_PATH='"$(abspath \
	ftlua/res/)"'

# module ftui::ftui
$(O_DIR)/ftui/ACanvas.o: ftui/ACanvas.cpp ft/public/Color.hpp \
	ft/public/Rect.hpp ft/public/Vec.hpp ft/public/assert.hpp \
	ft/public/templates/Rect.tpp ft/public/templates/Vec2.tpp \
	ft/public/templates/Vec3.tpp ft/public/templates/Vec4.tpp \
	ft/public/type_traits.hpp ft/public/utils.hpp ftlua/public/KeysWrapper.hpp \
	ftlua/public/call.hpp ftlua/public/conversions.hpp ftlua/public/ftlua.hpp \
	ftlua/public/light.hpp ftlua/public/pop.hpp ftlua/public/push.hpp \
	ftlua/public/set.hpp ftlua/public/size.hpp ftlua/public/stackassert.hpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/ACanvas.hpp \
	liblua/lua-5.3.1/src/lauxlib.h liblua/lua-5.3.1/src/lua.h \
	liblua/lua-5.3.1/src/lua.hpp liblua/lua-5.3.1/src/luaconf.h \
	liblua/lua-5.3.1/src/lualib.h
$(O_DIR)/ftui/ALayout.o: ftui/ALayout.cpp ft/public/Color.hpp \
	ft/public/Rect.hpp ft/public/TupleRef.hpp ft/public/Vec.hpp \
	ft/public/assert.hpp ft/public/templates/Rect.tpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp ft/public/type_traits.hpp ft/public/utils.hpp \
	ft_xml/public/XmlParser.hpp ft_xml/public/XmlTokenizer.hpp \
	ftlua/public/KeysWrapper.hpp ftlua/public/call.hpp \
	ftlua/public/conversions.hpp ftlua/public/ftlua.hpp ftlua/public/light.hpp \
	ftlua/public/pop.hpp ftlua/public/push.hpp ftlua/public/set.hpp \
	ftlua/public/size.hpp ftlua/public/stackassert.hpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/ACanvas.hpp ftui/public/ALayout.hpp \
	ftui/public/ASolidView.hpp ftui/public/AView.hpp ftui/public/Activity.hpp \
	ftui/public/EventTarget.hpp ftui/public/EventTargetCpp.hpp \
	ftui/public/IViewHolder.hpp ftui/public/ViewTemplate.hpp \
	ftui/public/templates/AView_callLuaCallback.tpp \
	ftui/public/templates/Activity.tpp liblua/lua-5.3.1/src/lauxlib.h \
	liblua/lua-5.3.1/src/lua.h liblua/lua-5.3.1/src/lua.hpp \
	liblua/lua-5.3.1/src/luaconf.h liblua/lua-5.3.1/src/lualib.h
$(O_DIR)/ftui/ALayout_luaHandler.o: ftui/ALayout_luaHandler.cpp \
	ft/public/Color.hpp ft/public/Rect.hpp ft/public/Vec.hpp \
	ft/public/assert.hpp ft/public/templates/Rect.tpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp ft/public/type_traits.hpp ft/public/utils.hpp \
	ft_xml/public/XmlParser.hpp ft_xml/public/XmlTokenizer.hpp \
	ftlua/public/KeysWrapper.hpp ftlua/public/call.hpp \
	ftlua/public/conversions.hpp ftlua/public/ftlua.hpp ftlua/public/light.hpp \
	ftlua/public/pop.hpp ftlua/public/push.hpp ftlua/public/set.hpp \
	ftlua/public/size.hpp ftlua/public/stackassert.hpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/ACanvas.hpp ftui/public/ALayout.hpp \
	ftui/public/ASolidView.hpp ftui/public/AView.hpp \
	ftui/public/IViewHolder.hpp ftui/public/ViewTemplate.hpp \
	ftui/public/templates/AView_callLuaCallback.tpp \
	liblua/lua-5.3.1/src/lauxlib.h liblua/lua-5.3.1/src/lua.h \
	liblua/lua-5.3.1/src/lua.hpp liblua/lua-5.3.1/src/luaconf.h \
	liblua/lua-5.3.1/src/lualib.h
$(O_DIR)/ftui/ASolidView.o: ftui/ASolidView.cpp ft/public/Color.hpp \
	ft/public/Rect.hpp ft/public/Vec.hpp ft/public/assert.hpp \
	ft/public/templates/Rect.tpp ft/public/templates/Vec2.tpp \
	ft/public/templates/Vec3.tpp ft/public/templates/Vec4.tpp \
	ft/public/type_traits.hpp ft/public/utils.hpp ft_xml/public/XmlParser.hpp \
	ft_xml/public/XmlTokenizer.hpp ftlua/public/KeysWrapper.hpp \
	ftlua/public/call.hpp ftlua/public/conversions.hpp ftlua/public/ftlua.hpp \
	ftlua/public/light.hpp ftlua/public/pop.hpp ftlua/public/push.hpp \
	ftlua/public/set.hpp ftlua/public/size.hpp ftlua/public/stackassert.hpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/ACanvas.hpp ftui/public/ASolidView.hpp \
	ftui/public/AView.hpp ftui/public/IViewHolder.hpp \
	ftui/public/ViewTemplate.hpp \
	ftui/public/templates/AView_callLuaCallback.tpp \
	liblua/lua-5.3.1/src/lauxlib.h liblua/lua-5.3.1/src/lua.h \
	liblua/lua-5.3.1/src/lua.hpp liblua/lua-5.3.1/src/luaconf.h \
	liblua/lua-5.3.1/src/lualib.h
$(O_DIR)/ftui/AView.o: ftui/AView.cpp ft/public/Color.hpp ft/public/Rect.hpp \
	ft/public/TupleRef.hpp ft/public/Vec.hpp ft/public/assert.hpp \
	ft/public/padformat.hpp ft/public/templates/Rect.tpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp ft/public/type_traits.hpp ft/public/utils.hpp \
	ft_xml/public/XmlParser.hpp ft_xml/public/XmlTokenizer.hpp \
	ftlua/public/KeysWrapper.hpp ftlua/public/call.hpp \
	ftlua/public/conversions.hpp ftlua/public/ftlua.hpp ftlua/public/light.hpp \
	ftlua/public/pop.hpp ftlua/public/push.hpp ftlua/public/set.hpp \
	ftlua/public/size.hpp ftlua/public/stackassert.hpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/ACanvas.hpp ftui/public/ALayout.hpp \
	ftui/public/ASolidView.hpp ftui/public/AView.hpp ftui/public/Activity.hpp \
	ftui/public/EventTarget.hpp ftui/public/EventTargetCpp.hpp \
	ftui/public/IViewHolder.hpp ftui/public/ViewTemplate.hpp \
	ftui/public/templates/AView_callLuaCallback.tpp \
	ftui/public/templates/Activity.tpp liblua/lua-5.3.1/src/lauxlib.h \
	liblua/lua-5.3.1/src/lua.h liblua/lua-5.3.1/src/lua.hpp \
	liblua/lua-5.3.1/src/luaconf.h liblua/lua-5.3.1/src/lualib.h
$(O_DIR)/ftui/AView_luaHandler.o: ftui/AView_luaHandler.cpp \
	ft/public/Color.hpp ft/public/Rect.hpp ft/public/Vec.hpp \
	ft/public/assert.hpp ft/public/templates/Rect.tpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp ft/public/type_traits.hpp ft/public/utils.hpp \
	ft_xml/public/XmlParser.hpp ft_xml/public/XmlTokenizer.hpp \
	ftlua/public/KeysWrapper.hpp ftlua/public/call.hpp \
	ftlua/public/conversions.hpp ftlua/public/ftlua.hpp ftlua/public/light.hpp \
	ftlua/public/pop.hpp ftlua/public/push.hpp ftlua/public/set.hpp \
	ftlua/public/size.hpp ftlua/public/stackassert.hpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/ACanvas.hpp ftui/public/ALayout.hpp \
	ftui/public/ASolidView.hpp ftui/public/AView.hpp \
	ftui/public/IViewHolder.hpp ftui/public/TextView.hpp \
	ftui/public/ViewTemplate.hpp \
	ftui/public/templates/AView_callLuaCallback.tpp \
	liblua/lua-5.3.1/src/lauxlib.h liblua/lua-5.3.1/src/lua.h \
	liblua/lua-5.3.1/src/lua.hpp liblua/lua-5.3.1/src/luaconf.h \
	liblua/lua-5.3.1/src/lualib.h
$(O_DIR)/ftui/Activity.o: ftui/Activity.cpp ft/public/Color.hpp \
	ft/public/Rect.hpp ft/public/TupleRef.hpp ft/public/Vec.hpp \
	ft/public/assert.hpp ft/public/templates/Rect.tpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp ft/public/type_traits.hpp ft/public/utils.hpp \
	ft_xml/public/XmlParser.hpp ft_xml/public/XmlTokenizer.hpp \
	ftlua/public/KeysWrapper.hpp ftlua/public/call.hpp \
	ftlua/public/conversions.hpp ftlua/public/ftlua.hpp ftlua/public/light.hpp \
	ftlua/public/pop.hpp ftlua/public/push.hpp ftlua/public/set.hpp \
	ftlua/public/size.hpp ftlua/public/stackassert.hpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/ACanvas.hpp ftui/public/AView.hpp \
	ftui/public/Activity.hpp ftui/public/EventTarget.hpp \
	ftui/public/EventTargetCpp.hpp ftui/public/IViewHolder.hpp \
	ftui/public/ViewTemplate.hpp \
	ftui/public/templates/AView_callLuaCallback.tpp \
	ftui/public/templates/Activity.tpp liblua/lua-5.3.1/src/lauxlib.h \
	liblua/lua-5.3.1/src/lua.h liblua/lua-5.3.1/src/lua.hpp \
	liblua/lua-5.3.1/src/luaconf.h liblua/lua-5.3.1/src/lualib.h
$(O_DIR)/ftui/Activity_RootViewHolder.o: ftui/Activity_RootViewHolder.cpp \
	ft/public/Color.hpp ft/public/Rect.hpp ft/public/TupleRef.hpp \
	ft/public/Vec.hpp ft/public/assert.hpp ft/public/templates/Rect.tpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp ft/public/type_traits.hpp ft/public/utils.hpp \
	ft_xml/public/XmlParser.hpp ft_xml/public/XmlTokenizer.hpp \
	ftlua/public/KeysWrapper.hpp ftlua/public/call.hpp \
	ftlua/public/conversions.hpp ftlua/public/ftlua.hpp ftlua/public/light.hpp \
	ftlua/public/pop.hpp ftlua/public/push.hpp ftlua/public/set.hpp \
	ftlua/public/size.hpp ftlua/public/stackassert.hpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/ACanvas.hpp ftui/public/AView.hpp \
	ftui/public/Activity.hpp ftui/public/EventTarget.hpp \
	ftui/public/EventTargetCpp.hpp ftui/public/IViewHolder.hpp \
	ftui/public/ViewTemplate.hpp \
	ftui/public/templates/AView_callLuaCallback.tpp \
	ftui/public/templates/Activity.tpp liblua/lua-5.3.1/src/lauxlib.h \
	liblua/lua-5.3.1/src/lua.h liblua/lua-5.3.1/src/lua.hpp \
	liblua/lua-5.3.1/src/luaconf.h liblua/lua-5.3.1/src/lualib.h
$(O_DIR)/ftui/Activity_luaDef.o: ftui/Activity_luaDef.cpp ft/public/Color.hpp \
	ft/public/Rect.hpp ft/public/TupleRef.hpp ft/public/Vec.hpp \
	ft/public/assert.hpp ft/public/templates/Rect.tpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp ft/public/type_traits.hpp ft/public/utils.hpp \
	ft_xml/public/XmlParser.hpp ft_xml/public/XmlTokenizer.hpp \
	ftlua/public/KeysWrapper.hpp ftlua/public/call.hpp \
	ftlua/public/conversions.hpp ftlua/public/ftlua.hpp ftlua/public/light.hpp \
	ftlua/public/pop.hpp ftlua/public/push.hpp ftlua/public/set.hpp \
	ftlua/public/size.hpp ftlua/public/stackassert.hpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/ACanvas.hpp ftui/public/ALayout.hpp \
	ftui/public/ASolidView.hpp ftui/public/AView.hpp ftui/public/Activity.hpp \
	ftui/public/Button.hpp ftui/public/CheckBox.hpp \
	ftui/public/EventTarget.hpp ftui/public/EventTargetCpp.hpp \
	ftui/public/IViewHolder.hpp ftui/public/LinearLayout.hpp \
	ftui/public/ScrollableLayout.hpp ftui/public/SliderView.hpp \
	ftui/public/SolidView.hpp ftui/public/TextView.hpp \
	ftui/public/ViewTemplate.hpp \
	ftui/public/templates/AView_callLuaCallback.tpp \
	ftui/public/templates/Activity.tpp liblua/lua-5.3.1/src/lauxlib.h \
	liblua/lua-5.3.1/src/lua.h liblua/lua-5.3.1/src/lua.hpp \
	liblua/lua-5.3.1/src/luaconf.h liblua/lua-5.3.1/src/lualib.h
$(O_DIR)/ftui/Button.o: ftui/Button.cpp ft/public/Color.hpp ft/public/Rect.hpp \
	ft/public/TupleRef.hpp ft/public/Vec.hpp ft/public/assert.hpp \
	ft/public/templates/Rect.tpp ft/public/templates/Vec2.tpp \
	ft/public/templates/Vec3.tpp ft/public/templates/Vec4.tpp \
	ft/public/type_traits.hpp ft/public/utils.hpp ft_xml/public/XmlParser.hpp \
	ft_xml/public/XmlTokenizer.hpp ftlua/public/KeysWrapper.hpp \
	ftlua/public/call.hpp ftlua/public/conversions.hpp ftlua/public/ftlua.hpp \
	ftlua/public/light.hpp ftlua/public/pop.hpp ftlua/public/push.hpp \
	ftlua/public/set.hpp ftlua/public/size.hpp ftlua/public/stackassert.hpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/ACanvas.hpp ftui/public/AView.hpp \
	ftui/public/Activity.hpp ftui/public/Button.hpp \
	ftui/public/EventTarget.hpp ftui/public/EventTargetCpp.hpp \
	ftui/public/IViewHolder.hpp ftui/public/ViewTemplate.hpp \
	ftui/public/templates/AView_callLuaCallback.tpp \
	ftui/public/templates/Activity.tpp liblua/lua-5.3.1/src/lauxlib.h \
	liblua/lua-5.3.1/src/lua.h liblua/lua-5.3.1/src/lua.hpp \
	liblua/lua-5.3.1/src/luaconf.h liblua/lua-5.3.1/src/lualib.h
$(O_DIR)/ftui/CheckBox.o: ftui/CheckBox.cpp ft/public/Color.hpp \
	ft/public/Rect.hpp ft/public/TupleRef.hpp ft/public/Vec.hpp \
	ft/public/assert.hpp ft/public/templates/Rect.tpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp ft/public/type_traits.hpp ft/public/utils.hpp \
	ft_xml/public/XmlParser.hpp ft_xml/public/XmlTokenizer.hpp \
	ftlua/public/KeysWrapper.hpp ftlua/public/call.hpp \
	ftlua/public/conversions.hpp ftlua/public/ftlua.hpp ftlua/public/light.hpp \
	ftlua/public/pop.hpp ftlua/public/push.hpp ftlua/public/set.hpp \
	ftlua/public/size.hpp ftlua/public/stackassert.hpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/ACanvas.hpp ftui/public/AView.hpp \
	ftui/public/Activity.hpp ftui/public/Button.hpp ftui/public/CheckBox.hpp \
	ftui/public/EventTarget.hpp ftui/public/EventTargetCpp.hpp \
	ftui/public/IViewHolder.hpp ftui/public/ViewTemplate.hpp \
	ftui/public/templates/AView_callLuaCallback.tpp \
	ftui/public/templates/Activity.tpp liblua/lua-5.3.1/src/lauxlib.h \
	liblua/lua-5.3.1/src/lua.h liblua/lua-5.3.1/src/lua.hpp \
	liblua/lua-5.3.1/src/luaconf.h liblua/lua-5.3.1/src/lualib.h
$(O_DIR)/ftui/EventTarget.o: ftui/EventTarget.cpp ft/public/Color.hpp \
	ft/public/Rect.hpp ft/public/TupleRef.hpp ft/public/Vec.hpp \
	ft/public/assert.hpp ft/public/templates/Rect.tpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp ft/public/type_traits.hpp ft/public/utils.hpp \
	ft_xml/public/XmlParser.hpp ft_xml/public/XmlTokenizer.hpp \
	ftlua/public/KeysWrapper.hpp ftlua/public/call.hpp \
	ftlua/public/conversions.hpp ftlua/public/ftlua.hpp ftlua/public/light.hpp \
	ftlua/public/pop.hpp ftlua/public/push.hpp ftlua/public/set.hpp \
	ftlua/public/size.hpp ftlua/public/stackassert.hpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/ACanvas.hpp ftui/public/AView.hpp \
	ftui/public/EventTarget.hpp ftui/public/IViewHolder.hpp \
	ftui/public/ViewTemplate.hpp \
	ftui/public/templates/AView_callLuaCallback.tpp \
	liblua/lua-5.3.1/src/lauxlib.h liblua/lua-5.3.1/src/lua.h \
	liblua/lua-5.3.1/src/lua.hpp liblua/lua-5.3.1/src/luaconf.h \
	liblua/lua-5.3.1/src/lualib.h
$(O_DIR)/ftui/LinearLayout.o: ftui/LinearLayout.cpp ft/public/Color.hpp \
	ft/public/Rect.hpp ft/public/TupleRef.hpp ft/public/Vec.hpp \
	ft/public/assert.hpp ft/public/templates/Rect.tpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp ft/public/type_traits.hpp ft/public/utils.hpp \
	ft_xml/public/XmlParser.hpp ft_xml/public/XmlTokenizer.hpp \
	ftlua/public/KeysWrapper.hpp ftlua/public/call.hpp \
	ftlua/public/conversions.hpp ftlua/public/ftlua.hpp ftlua/public/light.hpp \
	ftlua/public/pop.hpp ftlua/public/push.hpp ftlua/public/set.hpp \
	ftlua/public/size.hpp ftlua/public/stackassert.hpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/ACanvas.hpp ftui/public/ALayout.hpp \
	ftui/public/ASolidView.hpp ftui/public/AView.hpp ftui/public/Activity.hpp \
	ftui/public/EventTarget.hpp ftui/public/EventTargetCpp.hpp \
	ftui/public/IViewHolder.hpp ftui/public/LinearLayout.hpp \
	ftui/public/ViewTemplate.hpp \
	ftui/public/templates/AView_callLuaCallback.tpp \
	ftui/public/templates/Activity.tpp liblua/lua-5.3.1/src/lauxlib.h \
	liblua/lua-5.3.1/src/lua.h liblua/lua-5.3.1/src/lua.hpp \
	liblua/lua-5.3.1/src/luaconf.h liblua/lua-5.3.1/src/lualib.h
$(O_DIR)/ftui/LinearLayout_ViewHolder.o: ftui/LinearLayout_ViewHolder.cpp \
	ft/public/Color.hpp ft/public/Rect.hpp ft/public/TupleRef.hpp \
	ft/public/Vec.hpp ft/public/assert.hpp ft/public/templates/Rect.tpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp ft/public/type_traits.hpp ft/public/utils.hpp \
	ft_xml/public/XmlParser.hpp ft_xml/public/XmlTokenizer.hpp \
	ftlua/public/KeysWrapper.hpp ftlua/public/call.hpp \
	ftlua/public/conversions.hpp ftlua/public/ftlua.hpp ftlua/public/light.hpp \
	ftlua/public/pop.hpp ftlua/public/push.hpp ftlua/public/set.hpp \
	ftlua/public/size.hpp ftlua/public/stackassert.hpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/ACanvas.hpp ftui/public/ALayout.hpp \
	ftui/public/ASolidView.hpp ftui/public/AView.hpp ftui/public/Activity.hpp \
	ftui/public/EventTarget.hpp ftui/public/EventTargetCpp.hpp \
	ftui/public/IViewHolder.hpp ftui/public/LinearLayout.hpp \
	ftui/public/ViewTemplate.hpp \
	ftui/public/templates/AView_callLuaCallback.tpp \
	ftui/public/templates/Activity.tpp liblua/lua-5.3.1/src/lauxlib.h \
	liblua/lua-5.3.1/src/lua.h liblua/lua-5.3.1/src/lua.hpp \
	liblua/lua-5.3.1/src/luaconf.h liblua/lua-5.3.1/src/lualib.h
$(O_DIR)/ftui/ScrollableLayout.o: ftui/ScrollableLayout.cpp \
	ft/public/Color.hpp ft/public/Rect.hpp ft/public/TupleRef.hpp \
	ft/public/Vec.hpp ft/public/assert.hpp ft/public/templates/Rect.tpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp ft/public/type_traits.hpp ft/public/utils.hpp \
	ft_xml/public/XmlParser.hpp ft_xml/public/XmlTokenizer.hpp \
	ftlua/public/KeysWrapper.hpp ftlua/public/call.hpp \
	ftlua/public/conversions.hpp ftlua/public/ftlua.hpp ftlua/public/light.hpp \
	ftlua/public/pop.hpp ftlua/public/push.hpp ftlua/public/set.hpp \
	ftlua/public/size.hpp ftlua/public/stackassert.hpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/ACanvas.hpp ftui/public/ALayout.hpp \
	ftui/public/ASolidView.hpp ftui/public/AView.hpp ftui/public/Activity.hpp \
	ftui/public/EventTarget.hpp ftui/public/EventTargetCpp.hpp \
	ftui/public/IViewHolder.hpp ftui/public/LinearLayout.hpp \
	ftui/public/ScrollableLayout.hpp ftui/public/ViewTemplate.hpp \
	ftui/public/templates/AView_callLuaCallback.tpp \
	ftui/public/templates/Activity.tpp liblua/lua-5.3.1/src/lauxlib.h \
	liblua/lua-5.3.1/src/lua.h liblua/lua-5.3.1/src/lua.hpp \
	liblua/lua-5.3.1/src/luaconf.h liblua/lua-5.3.1/src/lualib.h
$(O_DIR)/ftui/SliderView.o: ftui/SliderView.cpp ft/public/Color.hpp \
	ft/public/Rect.hpp ft/public/TupleRef.hpp ft/public/Vec.hpp \
	ft/public/assert.hpp ft/public/templates/Rect.tpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp ft/public/type_traits.hpp ft/public/utils.hpp \
	ft_xml/public/XmlParser.hpp ft_xml/public/XmlTokenizer.hpp \
	ftlua/public/KeysWrapper.hpp ftlua/public/call.hpp \
	ftlua/public/conversions.hpp ftlua/public/ftlua.hpp ftlua/public/light.hpp \
	ftlua/public/pop.hpp ftlua/public/push.hpp ftlua/public/set.hpp \
	ftlua/public/size.hpp ftlua/public/stackassert.hpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/ACanvas.hpp ftui/public/ASolidView.hpp \
	ftui/public/AView.hpp ftui/public/Activity.hpp ftui/public/EventTarget.hpp \
	ftui/public/EventTargetCpp.hpp ftui/public/IViewHolder.hpp \
	ftui/public/SliderView.hpp ftui/public/ViewTemplate.hpp \
	ftui/public/templates/AView_callLuaCallback.tpp \
	ftui/public/templates/Activity.tpp liblua/lua-5.3.1/src/lauxlib.h \
	liblua/lua-5.3.1/src/lua.h liblua/lua-5.3.1/src/lua.hpp \
	liblua/lua-5.3.1/src/luaconf.h liblua/lua-5.3.1/src/lualib.h
$(O_DIR)/ftui/SolidView.o: ftui/SolidView.cpp ft/public/Color.hpp \
	ft/public/Rect.hpp ft/public/Vec.hpp ft/public/assert.hpp \
	ft/public/templates/Rect.tpp ft/public/templates/Vec2.tpp \
	ft/public/templates/Vec3.tpp ft/public/templates/Vec4.tpp \
	ft/public/type_traits.hpp ft/public/utils.hpp ft_xml/public/XmlParser.hpp \
	ft_xml/public/XmlTokenizer.hpp ftlua/public/KeysWrapper.hpp \
	ftlua/public/call.hpp ftlua/public/conversions.hpp ftlua/public/ftlua.hpp \
	ftlua/public/light.hpp ftlua/public/pop.hpp ftlua/public/push.hpp \
	ftlua/public/set.hpp ftlua/public/size.hpp ftlua/public/stackassert.hpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/ACanvas.hpp ftui/public/ASolidView.hpp \
	ftui/public/AView.hpp ftui/public/IViewHolder.hpp \
	ftui/public/SolidView.hpp ftui/public/ViewTemplate.hpp \
	ftui/public/templates/AView_callLuaCallback.tpp \
	liblua/lua-5.3.1/src/lauxlib.h liblua/lua-5.3.1/src/lua.h \
	liblua/lua-5.3.1/src/lua.hpp liblua/lua-5.3.1/src/luaconf.h \
	liblua/lua-5.3.1/src/lualib.h
$(O_DIR)/ftui/TextView.o: ftui/TextView.cpp ft/public/Color.hpp \
	ft/public/Rect.hpp ft/public/Vec.hpp ft/public/assert.hpp \
	ft/public/templates/Rect.tpp ft/public/templates/Vec2.tpp \
	ft/public/templates/Vec3.tpp ft/public/templates/Vec4.tpp \
	ft/public/type_traits.hpp ft/public/utils.hpp ft_xml/public/XmlParser.hpp \
	ft_xml/public/XmlTokenizer.hpp ftlua/public/KeysWrapper.hpp \
	ftlua/public/call.hpp ftlua/public/conversions.hpp ftlua/public/ftlua.hpp \
	ftlua/public/light.hpp ftlua/public/pop.hpp ftlua/public/push.hpp \
	ftlua/public/set.hpp ftlua/public/size.hpp ftlua/public/stackassert.hpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/ACanvas.hpp ftui/public/ASolidView.hpp \
	ftui/public/AView.hpp ftui/public/IViewHolder.hpp ftui/public/TextView.hpp \
	ftui/public/ViewTemplate.hpp \
	ftui/public/templates/AView_callLuaCallback.tpp \
	liblua/lua-5.3.1/src/lauxlib.h liblua/lua-5.3.1/src/lua.h \
	liblua/lua-5.3.1/src/lua.hpp liblua/lua-5.3.1/src/luaconf.h \
	liblua/lua-5.3.1/src/lualib.h
$(O_DIR)/ftui/ViewTemplate.o: ftui/ViewTemplate.cpp ft/public/Color.hpp \
	ft/public/Rect.hpp ft/public/TupleRef.hpp ft/public/Vec.hpp \
	ft/public/assert.hpp ft/public/templates/Rect.tpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp ft/public/type_traits.hpp ft/public/utils.hpp \
	ft_xml/public/XmlParser.hpp ft_xml/public/XmlTokenizer.hpp \
	ftlua/public/KeysWrapper.hpp ftlua/public/call.hpp \
	ftlua/public/conversions.hpp ftlua/public/ftlua.hpp ftlua/public/light.hpp \
	ftlua/public/pop.hpp ftlua/public/push.hpp ftlua/public/set.hpp \
	ftlua/public/size.hpp ftlua/public/stackassert.hpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/ACanvas.hpp ftui/public/AView.hpp \
	ftui/public/Activity.hpp ftui/public/EventTarget.hpp \
	ftui/public/EventTargetCpp.hpp ftui/public/IViewHolder.hpp \
	ftui/public/ViewTemplate.hpp \
	ftui/public/templates/AView_callLuaCallback.tpp \
	ftui/public/templates/Activity.tpp liblua/lua-5.3.1/src/lauxlib.h \
	liblua/lua-5.3.1/src/lua.h liblua/lua-5.3.1/src/lua.hpp \
	liblua/lua-5.3.1/src/luaconf.h liblua/lua-5.3.1/src/lualib.h

$(O_DIR)/ftui/ACanvas.o $(O_DIR)/ftui/ALayout.o \
$(O_DIR)/ftui/ALayout_luaHandler.o $(O_DIR)/ftui/ASolidView.o \
$(O_DIR)/ftui/AView.o $(O_DIR)/ftui/AView_luaHandler.o \
$(O_DIR)/ftui/Activity.o $(O_DIR)/ftui/Activity_RootViewHolder.o \
$(O_DIR)/ftui/Activity_luaDef.o $(O_DIR)/ftui/Button.o \
$(O_DIR)/ftui/CheckBox.o $(O_DIR)/ftui/EventTarget.o \
$(O_DIR)/ftui/LinearLayout.o $(O_DIR)/ftui/LinearLayout_ViewHolder.o \
$(O_DIR)/ftui/ScrollableLayout.o $(O_DIR)/ftui/SliderView.o \
$(O_DIR)/ftui/SolidView.o $(O_DIR)/ftui/TextView.o \
$(O_DIR)/ftui/ViewTemplate.o: BASE_FLAGS += -DRES_PATH='"$(abspath \
	ftui/res/)"'

# module gl::gl
ifeq ($(shell uname),Darwin)
  BASE_FLAGS += -DMAC_OS_MODE=1
  LINK_FLAGS += -lglfw3 -framework OpenGL
else
  LINK_FLAGS += -lglfw -lGL -lGLEW
endif

# module gl_canvas::gl_canvas
$(O_DIR)/gl_canvas/GlCanvas.o: gl_canvas/GlCanvas.cpp ft/public/Color.hpp \
	ft/public/Rect.hpp ft/public/Vec.hpp ft/public/assert.hpp \
	ft/public/templates/Rect.tpp ft/public/templates/Vec2.tpp \
	ft/public/templates/Vec3.tpp ft/public/templates/Vec4.tpp \
	ft/public/type_traits.hpp ft/public/utils.hpp ftlua/public/KeysWrapper.hpp \
	ftlua/public/conversions.hpp ftlua/public/light.hpp ftlua/public/push.hpp \
	ftlua/public/size.hpp ftlua/public/stackassert.hpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/ACanvas.hpp \
	gl_canvas/public/GlCanvas.hpp liblua/lua-5.3.1/src/lauxlib.h \
	liblua/lua-5.3.1/src/lua.h liblua/lua-5.3.1/src/lua.hpp \
	liblua/lua-5.3.1/src/luaconf.h liblua/lua-5.3.1/src/lualib.h
$(O_DIR)/gl_canvas/GlCanvasHolder.o: gl_canvas/GlCanvasHolder.cpp \
	ft/public/Color.hpp ft/public/Rect.hpp ft/public/Vec.hpp \
	ft/public/assert.hpp ft/public/templates/Rect.tpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp ft/public/type_traits.hpp ft/public/utils.hpp \
	ftlua/public/KeysWrapper.hpp ftlua/public/conversions.hpp \
	ftlua/public/light.hpp ftlua/public/push.hpp ftlua/public/size.hpp \
	ftlua/public/stackassert.hpp ftlua/public/types.hpp ftlua/public/utils.hpp \
	ftui/public/ACanvas.hpp gl/gl.h gl/gl.hpp gl_canvas/public/GlCanvas.hpp \
	gl_canvas/public/GlCanvasHolder.hpp liblua/lua-5.3.1/src/lauxlib.h \
	liblua/lua-5.3.1/src/lua.h liblua/lua-5.3.1/src/lua.hpp \
	liblua/lua-5.3.1/src/luaconf.h liblua/lua-5.3.1/src/lualib.h

# module liblua::liblua
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

liblua: $(LIBLUA_LIB)
.PHONY: liblua

$(LIBLUA_LIB):
	echo Extract lua
	tar -x -C liblua -f $(LIBLUA_ARCHIVE)
	echo "Make lua ($(LIBLUA_PLATFORM))"
	make -C $(LIBLUA_DIR) $(LIBLUA_PLATFORM)
	echo Done

# module tiles::tiles
$(O_DIR)/tiles/Tiles.o: tiles/Tiles.cpp ft/public/Vec.hpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp gl/gl.h gl/gl.hpp tiles/include/Tiles.hpp

# public links
$(O_DIR)/_public/ft/Color.hpp: ft/public/Color.hpp
$(O_DIR)/_public/ft/Rect.hpp: ft/public/Rect.hpp
$(O_DIR)/_public/ft/TupleRef.hpp: ft/public/TupleRef.hpp
$(O_DIR)/_public/ft/Vec.hpp: ft/public/Vec.hpp
$(O_DIR)/_public/ft/assert.hpp: ft/public/assert.hpp
$(O_DIR)/_public/ft/padformat.hpp: ft/public/padformat.hpp
$(O_DIR)/_public/ft/templates/Rect.tpp: ft/public/templates/Rect.tpp
$(O_DIR)/_public/ft/templates/Vec2.tpp: ft/public/templates/Vec2.tpp
$(O_DIR)/_public/ft/templates/Vec3.tpp: ft/public/templates/Vec3.tpp
$(O_DIR)/_public/ft/templates/Vec4.tpp: ft/public/templates/Vec4.tpp
$(O_DIR)/_public/ft/type_traits.hpp: ft/public/type_traits.hpp
$(O_DIR)/_public/ft/utils.hpp: ft/public/utils.hpp
$(O_DIR)/_public/ft_xml/XmlParser.hpp: ft_xml/public/XmlParser.hpp
$(O_DIR)/_public/ft_xml/XmlTokenizer.hpp: ft_xml/public/XmlTokenizer.hpp
$(O_DIR)/_public/ftce/Array.hpp: ftce/Array.hpp
$(O_DIR)/_public/ftce/Array.tpp: ftce/Array.tpp
$(O_DIR)/_public/ftce/math.hpp: ftce/math.hpp
$(O_DIR)/_public/ftlua/KeysWrapper.hpp: ftlua/public/KeysWrapper.hpp
$(O_DIR)/_public/ftlua/call.hpp: ftlua/public/call.hpp
$(O_DIR)/_public/ftlua/conversions.hpp: ftlua/public/conversions.hpp
$(O_DIR)/_public/ftlua/ftlua.hpp: ftlua/public/ftlua.hpp
$(O_DIR)/_public/ftlua/light.hpp: ftlua/public/light.hpp
$(O_DIR)/_public/ftlua/pop.hpp: ftlua/public/pop.hpp
$(O_DIR)/_public/ftlua/push.hpp: ftlua/public/push.hpp
$(O_DIR)/_public/ftlua/set.hpp: ftlua/public/set.hpp
$(O_DIR)/_public/ftlua/size.hpp: ftlua/public/size.hpp
$(O_DIR)/_public/ftlua/stackassert.hpp: ftlua/public/stackassert.hpp
$(O_DIR)/_public/ftlua/templates/ftlua_handler.tpp: \
ftlua/public/templates/ftlua_handler.tpp
$(O_DIR)/_public/ftlua/types.hpp: ftlua/public/types.hpp
$(O_DIR)/_public/ftlua/utils.hpp: ftlua/public/utils.hpp
$(O_DIR)/_public/ftui/ACanvas.hpp: ftui/public/ACanvas.hpp
$(O_DIR)/_public/ftui/ALayout.hpp: ftui/public/ALayout.hpp
$(O_DIR)/_public/ftui/ASolidView.hpp: ftui/public/ASolidView.hpp
$(O_DIR)/_public/ftui/AView.hpp: ftui/public/AView.hpp
$(O_DIR)/_public/ftui/AbsoluteLayout.hpp: ftui/public/AbsoluteLayout.hpp
$(O_DIR)/_public/ftui/Activity.hpp: ftui/public/Activity.hpp
$(O_DIR)/_public/ftui/Button.hpp: ftui/public/Button.hpp
$(O_DIR)/_public/ftui/CheckBox.hpp: ftui/public/CheckBox.hpp
$(O_DIR)/_public/ftui/EventTarget.hpp: ftui/public/EventTarget.hpp
$(O_DIR)/_public/ftui/EventTargetCpp.hpp: ftui/public/EventTargetCpp.hpp
$(O_DIR)/_public/ftui/IViewHolder.hpp: ftui/public/IViewHolder.hpp
$(O_DIR)/_public/ftui/LinearLayout.hpp: ftui/public/LinearLayout.hpp
$(O_DIR)/_public/ftui/RelativeLayout.hpp: ftui/public/RelativeLayout.hpp
$(O_DIR)/_public/ftui/ScrollableLayout.hpp: ftui/public/ScrollableLayout.hpp
$(O_DIR)/_public/ftui/SliderView.hpp: ftui/public/SliderView.hpp
$(O_DIR)/_public/ftui/SolidView.hpp: ftui/public/SolidView.hpp
$(O_DIR)/_public/ftui/TextView.hpp: ftui/public/TextView.hpp
$(O_DIR)/_public/ftui/ViewTemplate.hpp: ftui/public/ViewTemplate.hpp
$(O_DIR)/_public/ftui/libftui.hpp: ftui/public/libftui.hpp
$(O_DIR)/_public/ftui/templates/AView_callLuaCallback.tpp: \
ftui/public/templates/AView_callLuaCallback.tpp
$(O_DIR)/_public/ftui/templates/Activity.tpp: \
ftui/public/templates/Activity.tpp
$(O_DIR)/_public/gl/gl.h: gl/gl.h
$(O_DIR)/_public/gl/gl.hpp: gl/gl.hpp
$(O_DIR)/_public/gl_canvas/GlCanvas.hpp: gl_canvas/public/GlCanvas.hpp
$(O_DIR)/_public/gl_canvas/GlCanvasHolder.hpp: \
gl_canvas/public/GlCanvasHolder.hpp
$(O_DIR)/_public/liblua/lapi.c: liblua/lua-5.3.1/src/lapi.c
$(O_DIR)/_public/liblua/lapi.h: liblua/lua-5.3.1/src/lapi.h
$(O_DIR)/_public/liblua/lauxlib.c: liblua/lua-5.3.1/src/lauxlib.c
$(O_DIR)/_public/liblua/lauxlib.h: liblua/lua-5.3.1/src/lauxlib.h
$(O_DIR)/_public/liblua/lbaselib.c: liblua/lua-5.3.1/src/lbaselib.c
$(O_DIR)/_public/liblua/lbitlib.c: liblua/lua-5.3.1/src/lbitlib.c
$(O_DIR)/_public/liblua/lcode.c: liblua/lua-5.3.1/src/lcode.c
$(O_DIR)/_public/liblua/lcode.h: liblua/lua-5.3.1/src/lcode.h
$(O_DIR)/_public/liblua/lcorolib.c: liblua/lua-5.3.1/src/lcorolib.c
$(O_DIR)/_public/liblua/lctype.c: liblua/lua-5.3.1/src/lctype.c
$(O_DIR)/_public/liblua/lctype.h: liblua/lua-5.3.1/src/lctype.h
$(O_DIR)/_public/liblua/ldblib.c: liblua/lua-5.3.1/src/ldblib.c
$(O_DIR)/_public/liblua/ldebug.c: liblua/lua-5.3.1/src/ldebug.c
$(O_DIR)/_public/liblua/ldebug.h: liblua/lua-5.3.1/src/ldebug.h
$(O_DIR)/_public/liblua/ldo.c: liblua/lua-5.3.1/src/ldo.c
$(O_DIR)/_public/liblua/ldo.h: liblua/lua-5.3.1/src/ldo.h
$(O_DIR)/_public/liblua/ldump.c: liblua/lua-5.3.1/src/ldump.c
$(O_DIR)/_public/liblua/lfunc.c: liblua/lua-5.3.1/src/lfunc.c
$(O_DIR)/_public/liblua/lfunc.h: liblua/lua-5.3.1/src/lfunc.h
$(O_DIR)/_public/liblua/lgc.c: liblua/lua-5.3.1/src/lgc.c
$(O_DIR)/_public/liblua/lgc.h: liblua/lua-5.3.1/src/lgc.h
$(O_DIR)/_public/liblua/linit.c: liblua/lua-5.3.1/src/linit.c
$(O_DIR)/_public/liblua/liolib.c: liblua/lua-5.3.1/src/liolib.c
$(O_DIR)/_public/liblua/llex.c: liblua/lua-5.3.1/src/llex.c
$(O_DIR)/_public/liblua/llex.h: liblua/lua-5.3.1/src/llex.h
$(O_DIR)/_public/liblua/llimits.h: liblua/lua-5.3.1/src/llimits.h
$(O_DIR)/_public/liblua/lmathlib.c: liblua/lua-5.3.1/src/lmathlib.c
$(O_DIR)/_public/liblua/lmem.c: liblua/lua-5.3.1/src/lmem.c
$(O_DIR)/_public/liblua/lmem.h: liblua/lua-5.3.1/src/lmem.h
$(O_DIR)/_public/liblua/loadlib.c: liblua/lua-5.3.1/src/loadlib.c
$(O_DIR)/_public/liblua/lobject.c: liblua/lua-5.3.1/src/lobject.c
$(O_DIR)/_public/liblua/lobject.h: liblua/lua-5.3.1/src/lobject.h
$(O_DIR)/_public/liblua/lopcodes.c: liblua/lua-5.3.1/src/lopcodes.c
$(O_DIR)/_public/liblua/lopcodes.h: liblua/lua-5.3.1/src/lopcodes.h
$(O_DIR)/_public/liblua/loslib.c: liblua/lua-5.3.1/src/loslib.c
$(O_DIR)/_public/liblua/lparser.c: liblua/lua-5.3.1/src/lparser.c
$(O_DIR)/_public/liblua/lparser.h: liblua/lua-5.3.1/src/lparser.h
$(O_DIR)/_public/liblua/lprefix.h: liblua/lua-5.3.1/src/lprefix.h
$(O_DIR)/_public/liblua/lstate.c: liblua/lua-5.3.1/src/lstate.c
$(O_DIR)/_public/liblua/lstate.h: liblua/lua-5.3.1/src/lstate.h
$(O_DIR)/_public/liblua/lstring.c: liblua/lua-5.3.1/src/lstring.c
$(O_DIR)/_public/liblua/lstring.h: liblua/lua-5.3.1/src/lstring.h
$(O_DIR)/_public/liblua/lstrlib.c: liblua/lua-5.3.1/src/lstrlib.c
$(O_DIR)/_public/liblua/ltable.c: liblua/lua-5.3.1/src/ltable.c
$(O_DIR)/_public/liblua/ltable.h: liblua/lua-5.3.1/src/ltable.h
$(O_DIR)/_public/liblua/ltablib.c: liblua/lua-5.3.1/src/ltablib.c
$(O_DIR)/_public/liblua/ltm.c: liblua/lua-5.3.1/src/ltm.c
$(O_DIR)/_public/liblua/ltm.h: liblua/lua-5.3.1/src/ltm.h
$(O_DIR)/_public/liblua/lua.c: liblua/lua-5.3.1/src/lua.c
$(O_DIR)/_public/liblua/lua.h: liblua/lua-5.3.1/src/lua.h
$(O_DIR)/_public/liblua/lua.hpp: liblua/lua-5.3.1/src/lua.hpp
$(O_DIR)/_public/liblua/luac.c: liblua/lua-5.3.1/src/luac.c
$(O_DIR)/_public/liblua/luaconf.h: liblua/lua-5.3.1/src/luaconf.h
$(O_DIR)/_public/liblua/lualib.h: liblua/lua-5.3.1/src/lualib.h
$(O_DIR)/_public/liblua/lundump.c: liblua/lua-5.3.1/src/lundump.c
$(O_DIR)/_public/liblua/lundump.h: liblua/lua-5.3.1/src/lundump.h
$(O_DIR)/_public/liblua/lutf8lib.c: liblua/lua-5.3.1/src/lutf8lib.c
$(O_DIR)/_public/liblua/lvm.c: liblua/lua-5.3.1/src/lvm.c
$(O_DIR)/_public/liblua/lvm.h: liblua/lua-5.3.1/src/lvm.h
$(O_DIR)/_public/liblua/lzio.c: liblua/lua-5.3.1/src/lzio.c
$(O_DIR)/_public/liblua/lzio.h: liblua/lua-5.3.1/src/lzio.h
$(O_DIR)/_public/tiles/Tiles.hpp: tiles/include/Tiles.hpp
