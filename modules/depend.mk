LIBS_RULES += liblua
LINK_FLAGS += -Lliblua/lua-5.3.1/src -llua -lfreetype
O_FILES += $(O_DIR)/ft/assert.o $(O_DIR)/ft/padformat.o \
	$(O_DIR)/ft_xml/srcs/XmlParser.o $(O_DIR)/ft_xml/srcs/XmlTokenizer.o \
	$(O_DIR)/ftlua/cpp_utils.o $(O_DIR)/ftlua/push_utils.o \
	$(O_DIR)/ftlua/stackError.o $(O_DIR)/ftui/ACanvas.o \
	$(O_DIR)/ftui/ALayout.o $(O_DIR)/ftui/ALayout_luaHandler.o \
	$(O_DIR)/ftui/ASolidView.o $(O_DIR)/ftui/AView.o \
	$(O_DIR)/ftui/AView_luaHandler.o $(O_DIR)/ftui/Activity.o \
	$(O_DIR)/ftui/Activity_RootViewHolder.o $(O_DIR)/ftui/Activity_luaDef.o \
	$(O_DIR)/ftui/Button.o $(O_DIR)/ftui/EventTarget.o \
	$(O_DIR)/ftui/LinearLayout.o $(O_DIR)/ftui/LinearLayout_ViewHolder.o \
	$(O_DIR)/ftui/SliderView.o $(O_DIR)/ftui/SolidView.o \
	$(O_DIR)/ftui/TextView.o $(O_DIR)/gl_canvas/GlCanvas.o \
	$(O_DIR)/gl_canvas/GlCanvasHolder.o $(O_DIR)/tiles/Tiles.o

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

# module ft_xml
$(O_DIR)/ft_xml/_public/ft $(O_DIR)/ft_xml/_public/ft_xml: | \
	$(O_DIR)/ft_xml/_public/
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
	ft/public/templates/Vec4.tpp ft/public/type_traits.hpp ft/public/utils.hpp \
	ft_xml/public/XmlParser.hpp ft_xml/public/XmlTokenizer.hpp \
	| $(O_DIR)/ft_xml/srcs/
$(O_DIR)/ft_xml/srcs/XmlTokenizer.o: ft_xml/srcs/XmlTokenizer.cpp \
	ft/public/Rect.hpp ft/public/Vec.hpp ft/public/templates/Rect.tpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp ft/public/type_traits.hpp ft/public/utils.hpp \
	ft_xml/public/XmlTokenizer.hpp | $(O_DIR)/ft_xml/srcs/

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
	ft/public/templates/Vec4.tpp ft/public/type_traits.hpp ft/public/utils.hpp \
	| $(O_DIR)/ft/
$(O_DIR)/ft/padformat.o: ft/padformat.cpp ft/public/Rect.hpp ft/public/Vec.hpp \
	ft/public/assert.hpp ft/public/templates/Rect.tpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp ft/public/type_traits.hpp ft/public/utils.hpp \
	| $(O_DIR)/ft/

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


# module gl_canvas
$(O_DIR)/gl_canvas/_public/gl $(O_DIR)/gl_canvas/_public/ft \
$(O_DIR)/gl_canvas/_public/ftui $(O_DIR)/gl_canvas/_public/ft_xml \
$(O_DIR)/gl_canvas/_public/ftlua $(O_DIR)/gl_canvas/_public/liblua \
$(O_DIR)/gl_canvas/_public/gl_canvas: | $(O_DIR)/gl_canvas/_public/
$(O_DIR)/gl_canvas/_public/gl: gl
$(O_DIR)/gl_canvas/_public/ft: ft/public
$(O_DIR)/gl_canvas/_public/ftui: ftui/public
$(O_DIR)/gl_canvas/_public/ft_xml: ft_xml/public
$(O_DIR)/gl_canvas/_public/ftlua: ftlua/public
$(O_DIR)/gl_canvas/_public/liblua: liblua/lua-5.3.1/src
$(O_DIR)/gl_canvas/_public/gl_canvas: gl_canvas/public

PUBLIC_LINKS += $(O_DIR)/gl_canvas/_public/gl $(O_DIR)/gl_canvas/_public/ft \
	$(O_DIR)/gl_canvas/_public/ftui $(O_DIR)/gl_canvas/_public/ft_xml \
	$(O_DIR)/gl_canvas/_public/ftlua $(O_DIR)/gl_canvas/_public/liblua \
	$(O_DIR)/gl_canvas/_public/gl_canvas

$(O_DIR)/gl_canvas/GlCanvas.o $(O_DIR)/gl_canvas/GlCanvasHolder.o: \
	INCLUDE_FLAGS += -I$(O_DIR)/gl_canvas/_public
$(O_DIR)/gl_canvas/GlCanvas.o $(O_DIR)/gl_canvas/GlCanvasHolder.o: | \
	$(O_DIR)/gl_canvas/_public/gl $(O_DIR)/gl_canvas/_public/ft \
	$(O_DIR)/gl_canvas/_public/ftui $(O_DIR)/gl_canvas/_public/ft_xml \
	$(O_DIR)/gl_canvas/_public/ftlua $(O_DIR)/gl_canvas/_public/liblua \
	$(O_DIR)/gl_canvas/_public/gl_canvas

$(O_DIR)/gl_canvas/GlCanvas.o: gl_canvas/GlCanvas.cpp ft/public/Color.hpp \
	ft/public/Rect.hpp ft/public/Vec.hpp ft/public/assert.hpp \
	ft/public/templates/Rect.tpp ft/public/templates/Vec2.tpp \
	ft/public/templates/Vec3.tpp ft/public/templates/Vec4.tpp \
	ftlua/public/Converter.hpp ftlua/public/KeysWrapper.hpp \
	ftlua/public/call.hpp ftlua/public/ftlua.hpp ftlua/public/light.hpp \
	ftlua/public/pop.hpp ftlua/public/push.hpp ftlua/public/set.hpp \
	ftlua/public/stackassert.hpp ftlua/public/templates/ftlua_caller.tpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/ACanvas.hpp \
	ftui/public/ftlua_extend.hpp ftui/public/libftui.hpp \
	gl_canvas/public/GlCanvas.hpp liblua/lua-5.3.1/src/lauxlib.h \
	liblua/lua-5.3.1/src/lua.h liblua/lua-5.3.1/src/lua.hpp \
	liblua/lua-5.3.1/src/luaconf.h liblua/lua-5.3.1/src/lualib.h \
	| $(O_DIR)/gl_canvas/
$(O_DIR)/gl_canvas/GlCanvasHolder.o: gl_canvas/GlCanvasHolder.cpp \
	ft/public/Color.hpp ft/public/Rect.hpp ft/public/Vec.hpp \
	ft/public/assert.hpp ft/public/templates/Rect.tpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp ft/public/type_traits.hpp ft/public/utils.hpp \
	ftlua/public/Converter.hpp ftlua/public/KeysWrapper.hpp \
	ftlua/public/call.hpp ftlua/public/ftlua.hpp ftlua/public/light.hpp \
	ftlua/public/pop.hpp ftlua/public/push.hpp ftlua/public/set.hpp \
	ftlua/public/stackassert.hpp ftlua/public/templates/ftlua_caller.tpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/ACanvas.hpp \
	ftui/public/ftlua_extend.hpp ftui/public/libftui.hpp gl/gl.h gl/gl.hpp \
	gl_canvas/public/GlCanvas.hpp gl_canvas/public/GlCanvasHolder.hpp \
	liblua/lua-5.3.1/src/lauxlib.h liblua/lua-5.3.1/src/lua.h \
	liblua/lua-5.3.1/src/lua.hpp liblua/lua-5.3.1/src/luaconf.h \
	liblua/lua-5.3.1/src/lualib.h | $(O_DIR)/gl_canvas/

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

# module ftce
$(O_DIR)/ftce/_public/ftce: | $(O_DIR)/ftce/_public/
$(O_DIR)/ftce/_public/ftce: ftce

PUBLIC_LINKS += $(O_DIR)/ftce/_public/ftce

:INCLUDE_FLAGS += -I$(O_DIR)/ftce/_public
:|$(O_DIR)/ftce/_public/ftce


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

$(O_DIR)/ftui/ACanvas.o $(O_DIR)/ftui/ALayout.o \
$(O_DIR)/ftui/ALayout_luaHandler.o $(O_DIR)/ftui/ASolidView.o \
$(O_DIR)/ftui/AView.o $(O_DIR)/ftui/AView_luaHandler.o \
$(O_DIR)/ftui/Activity.o $(O_DIR)/ftui/Activity_RootViewHolder.o \
$(O_DIR)/ftui/Activity_luaDef.o $(O_DIR)/ftui/Button.o \
$(O_DIR)/ftui/EventTarget.o $(O_DIR)/ftui/LinearLayout.o \
$(O_DIR)/ftui/LinearLayout_ViewHolder.o $(O_DIR)/ftui/SliderView.o \
$(O_DIR)/ftui/SolidView.o $(O_DIR)/ftui/TextView.o: INCLUDE_FLAGS += \
	-I$(O_DIR)/ftui/_public
$(O_DIR)/ftui/ACanvas.o $(O_DIR)/ftui/ALayout.o \
$(O_DIR)/ftui/ALayout_luaHandler.o $(O_DIR)/ftui/ASolidView.o \
$(O_DIR)/ftui/AView.o $(O_DIR)/ftui/AView_luaHandler.o \
$(O_DIR)/ftui/Activity.o $(O_DIR)/ftui/Activity_RootViewHolder.o \
$(O_DIR)/ftui/Activity_luaDef.o $(O_DIR)/ftui/Button.o \
$(O_DIR)/ftui/EventTarget.o $(O_DIR)/ftui/LinearLayout.o \
$(O_DIR)/ftui/LinearLayout_ViewHolder.o $(O_DIR)/ftui/SliderView.o \
$(O_DIR)/ftui/SolidView.o $(O_DIR)/ftui/TextView.o: | $(O_DIR)/ftui/_public/ft \
	$(O_DIR)/ftui/_public/ft_xml $(O_DIR)/ftui/_public/ftlua \
	$(O_DIR)/ftui/_public/liblua $(O_DIR)/ftui/_public/ftui

$(O_DIR)/ftui/ACanvas.o $(O_DIR)/ftui/ALayout.o \
$(O_DIR)/ftui/ALayout_luaHandler.o $(O_DIR)/ftui/ASolidView.o \
$(O_DIR)/ftui/AView.o $(O_DIR)/ftui/AView_luaHandler.o \
$(O_DIR)/ftui/Activity.o $(O_DIR)/ftui/Activity_RootViewHolder.o \
$(O_DIR)/ftui/Activity_luaDef.o $(O_DIR)/ftui/Button.o \
$(O_DIR)/ftui/EventTarget.o $(O_DIR)/ftui/LinearLayout.o \
$(O_DIR)/ftui/LinearLayout_ViewHolder.o $(O_DIR)/ftui/SliderView.o \
$(O_DIR)/ftui/SolidView.o $(O_DIR)/ftui/TextView.o: BASE_FLAGS += -DRES_PATH='"$(abspath ftui/res/)"'
$(O_DIR)/ftui/ACanvas.o: ftui/ACanvas.cpp ft/public/Color.hpp \
	ft/public/Rect.hpp ft/public/Vec.hpp ft/public/assert.hpp \
	ft/public/templates/Rect.tpp ft/public/templates/Vec2.tpp \
	ft/public/templates/Vec3.tpp ft/public/templates/Vec4.tpp \
	ft/public/type_traits.hpp ft/public/utils.hpp ftlua/public/Converter.hpp \
	ftlua/public/KeysWrapper.hpp ftlua/public/call.hpp ftlua/public/ftlua.hpp \
	ftlua/public/light.hpp ftlua/public/pop.hpp ftlua/public/push.hpp \
	ftlua/public/set.hpp ftlua/public/stackassert.hpp \
	ftlua/public/templates/ftlua_caller.tpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/ACanvas.hpp \
	ftui/public/ftlua_extend.hpp ftui/public/libftui.hpp \
	liblua/lua-5.3.1/src/lauxlib.h liblua/lua-5.3.1/src/lua.h \
	liblua/lua-5.3.1/src/lua.hpp liblua/lua-5.3.1/src/luaconf.h \
	liblua/lua-5.3.1/src/lualib.h | $(O_DIR)/ftui/
$(O_DIR)/ftui/ALayout.o: ftui/ALayout.cpp ft/public/Color.hpp \
	ft/public/Rect.hpp ft/public/TupleRef.hpp ft/public/Vec.hpp \
	ft/public/assert.hpp ft/public/templates/Rect.tpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp ft/public/type_traits.hpp ft/public/utils.hpp \
	ft_xml/public/XmlParser.hpp ft_xml/public/XmlTokenizer.hpp \
	ftlua/public/Converter.hpp ftlua/public/KeysWrapper.hpp \
	ftlua/public/call.hpp ftlua/public/ftlua.hpp ftlua/public/light.hpp \
	ftlua/public/pop.hpp ftlua/public/push.hpp ftlua/public/set.hpp \
	ftlua/public/stackassert.hpp ftlua/public/templates/ftlua_caller.tpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/ACanvas.hpp ftui/public/ALayout.hpp \
	ftui/public/ASolidView.hpp ftui/public/AView.hpp ftui/public/Activity.hpp \
	ftui/public/EventTarget.hpp ftui/public/EventTargetCpp.hpp \
	ftui/public/IViewHolder.hpp ftui/public/ftlua_extend.hpp \
	ftui/public/libftui.hpp ftui/public/templates/AView_callLuaCallback.tpp \
	ftui/public/templates/Activity.tpp liblua/lua-5.3.1/src/lauxlib.h \
	liblua/lua-5.3.1/src/lua.h liblua/lua-5.3.1/src/lua.hpp \
	liblua/lua-5.3.1/src/luaconf.h liblua/lua-5.3.1/src/lualib.h \
	| $(O_DIR)/ftui/
$(O_DIR)/ftui/ALayout_luaHandler.o: ftui/ALayout_luaHandler.cpp \
	ft/public/Color.hpp ft/public/Rect.hpp ft/public/Vec.hpp \
	ft/public/assert.hpp ft/public/templates/Rect.tpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp ft_xml/public/XmlParser.hpp \
	ft_xml/public/XmlTokenizer.hpp ftlua/public/Converter.hpp \
	ftlua/public/KeysWrapper.hpp ftlua/public/call.hpp ftlua/public/ftlua.hpp \
	ftlua/public/light.hpp ftlua/public/pop.hpp ftlua/public/push.hpp \
	ftlua/public/set.hpp ftlua/public/stackassert.hpp \
	ftlua/public/templates/ftlua_caller.tpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/ACanvas.hpp ftui/public/ALayout.hpp \
	ftui/public/ASolidView.hpp ftui/public/AView.hpp \
	ftui/public/ftlua_extend.hpp ftui/public/libftui.hpp \
	ftui/public/templates/AView_callLuaCallback.tpp \
	liblua/lua-5.3.1/src/lauxlib.h liblua/lua-5.3.1/src/lua.h \
	liblua/lua-5.3.1/src/lua.hpp liblua/lua-5.3.1/src/luaconf.h \
	liblua/lua-5.3.1/src/lualib.h | $(O_DIR)/ftui/
$(O_DIR)/ftui/ASolidView.o: ftui/ASolidView.cpp ft/public/Color.hpp \
	ft/public/Rect.hpp ft/public/Vec.hpp ft/public/assert.hpp \
	ft/public/templates/Rect.tpp ft/public/templates/Vec2.tpp \
	ft/public/templates/Vec3.tpp ft/public/templates/Vec4.tpp \
	ft/public/type_traits.hpp ft/public/utils.hpp ft_xml/public/XmlParser.hpp \
	ft_xml/public/XmlTokenizer.hpp ftlua/public/Converter.hpp \
	ftlua/public/KeysWrapper.hpp ftlua/public/call.hpp ftlua/public/ftlua.hpp \
	ftlua/public/light.hpp ftlua/public/pop.hpp ftlua/public/push.hpp \
	ftlua/public/set.hpp ftlua/public/stackassert.hpp \
	ftlua/public/templates/ftlua_caller.tpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/ACanvas.hpp ftui/public/ASolidView.hpp \
	ftui/public/AView.hpp ftui/public/IViewHolder.hpp \
	ftui/public/ftlua_extend.hpp ftui/public/libftui.hpp \
	ftui/public/templates/AView_callLuaCallback.tpp \
	liblua/lua-5.3.1/src/lauxlib.h liblua/lua-5.3.1/src/lua.h \
	liblua/lua-5.3.1/src/lua.hpp liblua/lua-5.3.1/src/luaconf.h \
	liblua/lua-5.3.1/src/lualib.h | $(O_DIR)/ftui/
$(O_DIR)/ftui/AView.o: ftui/AView.cpp ft/public/Color.hpp ft/public/Rect.hpp \
	ft/public/TupleRef.hpp ft/public/Vec.hpp ft/public/assert.hpp \
	ft/public/templates/Rect.tpp ft/public/templates/Vec2.tpp \
	ft/public/templates/Vec3.tpp ft/public/templates/Vec4.tpp \
	ft/public/type_traits.hpp ft/public/utils.hpp ft_xml/public/XmlParser.hpp \
	ft_xml/public/XmlTokenizer.hpp ftlua/public/Converter.hpp \
	ftlua/public/KeysWrapper.hpp ftlua/public/call.hpp ftlua/public/ftlua.hpp \
	ftlua/public/light.hpp ftlua/public/pop.hpp ftlua/public/push.hpp \
	ftlua/public/set.hpp ftlua/public/stackassert.hpp \
	ftlua/public/templates/ftlua_caller.tpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/ACanvas.hpp ftui/public/ALayout.hpp \
	ftui/public/ASolidView.hpp ftui/public/AView.hpp ftui/public/Activity.hpp \
	ftui/public/EventTarget.hpp ftui/public/EventTargetCpp.hpp \
	ftui/public/IViewHolder.hpp ftui/public/ftlua_extend.hpp \
	ftui/public/libftui.hpp ftui/public/templates/AView_callLuaCallback.tpp \
	ftui/public/templates/Activity.tpp liblua/lua-5.3.1/src/lauxlib.h \
	liblua/lua-5.3.1/src/lua.h liblua/lua-5.3.1/src/lua.hpp \
	liblua/lua-5.3.1/src/luaconf.h liblua/lua-5.3.1/src/lualib.h \
	| $(O_DIR)/ftui/
$(O_DIR)/ftui/AView_luaHandler.o: ftui/AView_luaHandler.cpp \
	ft/public/Color.hpp ft/public/Rect.hpp ft/public/Vec.hpp \
	ft/public/assert.hpp ft/public/templates/Rect.tpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp ft_xml/public/XmlParser.hpp \
	ft_xml/public/XmlTokenizer.hpp ftlua/public/Converter.hpp \
	ftlua/public/KeysWrapper.hpp ftlua/public/call.hpp ftlua/public/ftlua.hpp \
	ftlua/public/light.hpp ftlua/public/pop.hpp ftlua/public/push.hpp \
	ftlua/public/set.hpp ftlua/public/stackassert.hpp \
	ftlua/public/templates/ftlua_caller.tpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/ACanvas.hpp ftui/public/ALayout.hpp \
	ftui/public/ASolidView.hpp ftui/public/AView.hpp \
	ftui/public/IViewHolder.hpp ftui/public/TextView.hpp \
	ftui/public/ftlua_extend.hpp ftui/public/libftui.hpp \
	ftui/public/templates/AView_callLuaCallback.tpp \
	liblua/lua-5.3.1/src/lauxlib.h liblua/lua-5.3.1/src/lua.h \
	liblua/lua-5.3.1/src/lua.hpp liblua/lua-5.3.1/src/luaconf.h \
	liblua/lua-5.3.1/src/lualib.h | $(O_DIR)/ftui/
$(O_DIR)/ftui/Activity.o: ftui/Activity.cpp ft/public/Color.hpp \
	ft/public/Rect.hpp ft/public/TupleRef.hpp ft/public/Vec.hpp \
	ft/public/assert.hpp ft/public/templates/Rect.tpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp ft/public/type_traits.hpp ft/public/utils.hpp \
	ft_xml/public/XmlParser.hpp ft_xml/public/XmlTokenizer.hpp \
	ftlua/public/Converter.hpp ftlua/public/KeysWrapper.hpp \
	ftlua/public/call.hpp ftlua/public/ftlua.hpp ftlua/public/light.hpp \
	ftlua/public/pop.hpp ftlua/public/push.hpp ftlua/public/set.hpp \
	ftlua/public/stackassert.hpp ftlua/public/templates/ftlua_caller.tpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/ACanvas.hpp ftui/public/AView.hpp \
	ftui/public/Activity.hpp ftui/public/EventTarget.hpp \
	ftui/public/EventTargetCpp.hpp ftui/public/IViewHolder.hpp \
	ftui/public/ftlua_extend.hpp ftui/public/libftui.hpp \
	ftui/public/templates/AView_callLuaCallback.tpp \
	ftui/public/templates/Activity.tpp liblua/lua-5.3.1/src/lauxlib.h \
	liblua/lua-5.3.1/src/lua.h liblua/lua-5.3.1/src/lua.hpp \
	liblua/lua-5.3.1/src/luaconf.h liblua/lua-5.3.1/src/lualib.h \
	| $(O_DIR)/ftui/
$(O_DIR)/ftui/Activity_RootViewHolder.o: ftui/Activity_RootViewHolder.cpp \
	ft/public/Rect.hpp ft/public/TupleRef.hpp ft/public/Vec.hpp \
	ft/public/assert.hpp ft/public/templates/Rect.tpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp ft/public/type_traits.hpp ft/public/utils.hpp \
	ft_xml/public/XmlParser.hpp ft_xml/public/XmlTokenizer.hpp \
	ftlua/public/Converter.hpp ftlua/public/KeysWrapper.hpp \
	ftlua/public/call.hpp ftlua/public/ftlua.hpp ftlua/public/light.hpp \
	ftlua/public/pop.hpp ftlua/public/push.hpp ftlua/public/set.hpp \
	ftlua/public/stackassert.hpp ftlua/public/templates/ftlua_caller.tpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/AView.hpp ftui/public/Activity.hpp \
	ftui/public/EventTarget.hpp ftui/public/EventTargetCpp.hpp \
	ftui/public/IViewHolder.hpp ftui/public/ftlua_extend.hpp \
	ftui/public/libftui.hpp ftui/public/templates/AView_callLuaCallback.tpp \
	ftui/public/templates/Activity.tpp liblua/lua-5.3.1/src/lauxlib.h \
	liblua/lua-5.3.1/src/lua.h liblua/lua-5.3.1/src/lua.hpp \
	liblua/lua-5.3.1/src/luaconf.h liblua/lua-5.3.1/src/lualib.h \
	| $(O_DIR)/ftui/
$(O_DIR)/ftui/Activity_luaDef.o: ftui/Activity_luaDef.cpp ft/public/Color.hpp \
	ft/public/Rect.hpp ft/public/TupleRef.hpp ft/public/Vec.hpp \
	ft/public/assert.hpp ft/public/templates/Rect.tpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp ft/public/type_traits.hpp ft/public/utils.hpp \
	ft_xml/public/XmlParser.hpp ft_xml/public/XmlTokenizer.hpp \
	ftlua/public/Converter.hpp ftlua/public/KeysWrapper.hpp \
	ftlua/public/call.hpp ftlua/public/ftlua.hpp ftlua/public/light.hpp \
	ftlua/public/pop.hpp ftlua/public/push.hpp ftlua/public/set.hpp \
	ftlua/public/stackassert.hpp ftlua/public/templates/ftlua_caller.tpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/ACanvas.hpp ftui/public/ALayout.hpp \
	ftui/public/ASolidView.hpp ftui/public/AView.hpp ftui/public/Activity.hpp \
	ftui/public/Button.hpp ftui/public/EventTarget.hpp \
	ftui/public/EventTargetCpp.hpp ftui/public/IViewHolder.hpp \
	ftui/public/LinearLayout.hpp ftui/public/SliderView.hpp \
	ftui/public/SolidView.hpp ftui/public/TextView.hpp \
	ftui/public/ftlua_extend.hpp ftui/public/libftui.hpp \
	ftui/public/templates/AView_callLuaCallback.tpp \
	ftui/public/templates/Activity.tpp liblua/lua-5.3.1/src/lauxlib.h \
	liblua/lua-5.3.1/src/lua.h liblua/lua-5.3.1/src/lua.hpp \
	liblua/lua-5.3.1/src/luaconf.h liblua/lua-5.3.1/src/lualib.h \
	| $(O_DIR)/ftui/
$(O_DIR)/ftui/Button.o: ftui/Button.cpp ft/public/Color.hpp ft/public/Rect.hpp \
	ft/public/TupleRef.hpp ft/public/Vec.hpp ft/public/assert.hpp \
	ft/public/templates/Rect.tpp ft/public/templates/Vec2.tpp \
	ft/public/templates/Vec3.tpp ft/public/templates/Vec4.tpp \
	ft/public/type_traits.hpp ft/public/utils.hpp ft_xml/public/XmlParser.hpp \
	ft_xml/public/XmlTokenizer.hpp ftlua/public/Converter.hpp \
	ftlua/public/KeysWrapper.hpp ftlua/public/call.hpp ftlua/public/ftlua.hpp \
	ftlua/public/light.hpp ftlua/public/pop.hpp ftlua/public/push.hpp \
	ftlua/public/set.hpp ftlua/public/stackassert.hpp \
	ftlua/public/templates/ftlua_caller.tpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/ACanvas.hpp ftui/public/AView.hpp \
	ftui/public/Activity.hpp ftui/public/Button.hpp \
	ftui/public/EventTarget.hpp ftui/public/EventTargetCpp.hpp \
	ftui/public/IViewHolder.hpp ftui/public/ftlua_extend.hpp \
	ftui/public/libftui.hpp ftui/public/templates/AView_callLuaCallback.tpp \
	ftui/public/templates/Activity.tpp liblua/lua-5.3.1/src/lauxlib.h \
	liblua/lua-5.3.1/src/lua.h liblua/lua-5.3.1/src/lua.hpp \
	liblua/lua-5.3.1/src/luaconf.h liblua/lua-5.3.1/src/lualib.h \
	| $(O_DIR)/ftui/
$(O_DIR)/ftui/EventTarget.o: ftui/EventTarget.cpp ft/public/Rect.hpp \
	ft/public/TupleRef.hpp ft/public/Vec.hpp ft/public/assert.hpp \
	ft/public/templates/Rect.tpp ft/public/templates/Vec2.tpp \
	ft/public/templates/Vec3.tpp ft/public/templates/Vec4.tpp \
	ft/public/type_traits.hpp ft/public/utils.hpp ftui/public/EventTarget.hpp \
	ftui/public/libftui.hpp | $(O_DIR)/ftui/
$(O_DIR)/ftui/LinearLayout.o: ftui/LinearLayout.cpp ft/public/Color.hpp \
	ft/public/Rect.hpp ft/public/TupleRef.hpp ft/public/Vec.hpp \
	ft/public/assert.hpp ft/public/templates/Rect.tpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp ft/public/type_traits.hpp ft/public/utils.hpp \
	ft_xml/public/XmlParser.hpp ft_xml/public/XmlTokenizer.hpp \
	ftlua/public/Converter.hpp ftlua/public/KeysWrapper.hpp \
	ftlua/public/call.hpp ftlua/public/ftlua.hpp ftlua/public/light.hpp \
	ftlua/public/pop.hpp ftlua/public/push.hpp ftlua/public/set.hpp \
	ftlua/public/stackassert.hpp ftlua/public/templates/ftlua_caller.tpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/ACanvas.hpp ftui/public/ALayout.hpp \
	ftui/public/ASolidView.hpp ftui/public/AView.hpp ftui/public/Activity.hpp \
	ftui/public/EventTarget.hpp ftui/public/EventTargetCpp.hpp \
	ftui/public/IViewHolder.hpp ftui/public/LinearLayout.hpp \
	ftui/public/ftlua_extend.hpp ftui/public/libftui.hpp \
	ftui/public/templates/AView_callLuaCallback.tpp \
	ftui/public/templates/Activity.tpp liblua/lua-5.3.1/src/lauxlib.h \
	liblua/lua-5.3.1/src/lua.h liblua/lua-5.3.1/src/lua.hpp \
	liblua/lua-5.3.1/src/luaconf.h liblua/lua-5.3.1/src/lualib.h \
	| $(O_DIR)/ftui/
$(O_DIR)/ftui/LinearLayout_ViewHolder.o: ftui/LinearLayout_ViewHolder.cpp \
	ft/public/Color.hpp ft/public/Rect.hpp ft/public/TupleRef.hpp \
	ft/public/Vec.hpp ft/public/assert.hpp ft/public/templates/Rect.tpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp ft/public/type_traits.hpp ft/public/utils.hpp \
	ft_xml/public/XmlParser.hpp ft_xml/public/XmlTokenizer.hpp \
	ftlua/public/Converter.hpp ftlua/public/KeysWrapper.hpp \
	ftlua/public/call.hpp ftlua/public/ftlua.hpp ftlua/public/light.hpp \
	ftlua/public/pop.hpp ftlua/public/push.hpp ftlua/public/set.hpp \
	ftlua/public/stackassert.hpp ftlua/public/templates/ftlua_caller.tpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/ACanvas.hpp ftui/public/ALayout.hpp \
	ftui/public/ASolidView.hpp ftui/public/AView.hpp ftui/public/Activity.hpp \
	ftui/public/EventTarget.hpp ftui/public/EventTargetCpp.hpp \
	ftui/public/IViewHolder.hpp ftui/public/LinearLayout.hpp \
	ftui/public/ftlua_extend.hpp ftui/public/libftui.hpp \
	ftui/public/templates/AView_callLuaCallback.tpp \
	ftui/public/templates/Activity.tpp liblua/lua-5.3.1/src/lauxlib.h \
	liblua/lua-5.3.1/src/lua.h liblua/lua-5.3.1/src/lua.hpp \
	liblua/lua-5.3.1/src/luaconf.h liblua/lua-5.3.1/src/lualib.h \
	| $(O_DIR)/ftui/
$(O_DIR)/ftui/SliderView.o: ftui/SliderView.cpp ft/public/Color.hpp \
	ft/public/Rect.hpp ft/public/TupleRef.hpp ft/public/Vec.hpp \
	ft/public/assert.hpp ft/public/templates/Rect.tpp \
	ft/public/templates/Vec2.tpp ft/public/templates/Vec3.tpp \
	ft/public/templates/Vec4.tpp ft/public/type_traits.hpp ft/public/utils.hpp \
	ft_xml/public/XmlParser.hpp ft_xml/public/XmlTokenizer.hpp \
	ftlua/public/Converter.hpp ftlua/public/KeysWrapper.hpp \
	ftlua/public/call.hpp ftlua/public/ftlua.hpp ftlua/public/light.hpp \
	ftlua/public/pop.hpp ftlua/public/push.hpp ftlua/public/set.hpp \
	ftlua/public/stackassert.hpp ftlua/public/templates/ftlua_caller.tpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/ACanvas.hpp ftui/public/ASolidView.hpp \
	ftui/public/AView.hpp ftui/public/Activity.hpp ftui/public/EventTarget.hpp \
	ftui/public/EventTargetCpp.hpp ftui/public/IViewHolder.hpp \
	ftui/public/SliderView.hpp ftui/public/ftlua_extend.hpp \
	ftui/public/libftui.hpp ftui/public/templates/AView_callLuaCallback.tpp \
	ftui/public/templates/Activity.tpp liblua/lua-5.3.1/src/lauxlib.h \
	liblua/lua-5.3.1/src/lua.h liblua/lua-5.3.1/src/lua.hpp \
	liblua/lua-5.3.1/src/luaconf.h liblua/lua-5.3.1/src/lualib.h \
	| $(O_DIR)/ftui/
$(O_DIR)/ftui/SolidView.o: ftui/SolidView.cpp ft/public/Color.hpp \
	ft/public/Rect.hpp ft/public/Vec.hpp ft/public/assert.hpp \
	ft/public/templates/Rect.tpp ft/public/templates/Vec2.tpp \
	ft/public/templates/Vec3.tpp ft/public/templates/Vec4.tpp \
	ft_xml/public/XmlParser.hpp ft_xml/public/XmlTokenizer.hpp \
	ftlua/public/Converter.hpp ftlua/public/KeysWrapper.hpp \
	ftlua/public/call.hpp ftlua/public/ftlua.hpp ftlua/public/light.hpp \
	ftlua/public/pop.hpp ftlua/public/push.hpp ftlua/public/set.hpp \
	ftlua/public/stackassert.hpp ftlua/public/templates/ftlua_caller.tpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/ACanvas.hpp ftui/public/ASolidView.hpp \
	ftui/public/AView.hpp ftui/public/SolidView.hpp \
	ftui/public/ftlua_extend.hpp ftui/public/libftui.hpp \
	ftui/public/templates/AView_callLuaCallback.tpp \
	liblua/lua-5.3.1/src/lauxlib.h liblua/lua-5.3.1/src/lua.h \
	liblua/lua-5.3.1/src/lua.hpp liblua/lua-5.3.1/src/luaconf.h \
	liblua/lua-5.3.1/src/lualib.h | $(O_DIR)/ftui/
$(O_DIR)/ftui/TextView.o: ftui/TextView.cpp ft/public/Color.hpp \
	ft/public/Rect.hpp ft/public/Vec.hpp ft/public/assert.hpp \
	ft/public/templates/Rect.tpp ft/public/templates/Vec2.tpp \
	ft/public/templates/Vec3.tpp ft/public/templates/Vec4.tpp \
	ft_xml/public/XmlParser.hpp ft_xml/public/XmlTokenizer.hpp \
	ftlua/public/Converter.hpp ftlua/public/KeysWrapper.hpp \
	ftlua/public/call.hpp ftlua/public/ftlua.hpp ftlua/public/light.hpp \
	ftlua/public/pop.hpp ftlua/public/push.hpp ftlua/public/set.hpp \
	ftlua/public/stackassert.hpp ftlua/public/templates/ftlua_caller.tpp \
	ftlua/public/templates/ftlua_handler.tpp ftlua/public/types.hpp \
	ftlua/public/utils.hpp ftui/public/ACanvas.hpp ftui/public/ASolidView.hpp \
	ftui/public/AView.hpp ftui/public/IViewHolder.hpp ftui/public/TextView.hpp \
	ftui/public/ftlua_extend.hpp ftui/public/libftui.hpp \
	ftui/public/templates/AView_callLuaCallback.tpp \
	liblua/lua-5.3.1/src/lauxlib.h liblua/lua-5.3.1/src/lua.h \
	liblua/lua-5.3.1/src/lua.hpp liblua/lua-5.3.1/src/luaconf.h \
	liblua/lua-5.3.1/src/lualib.h | $(O_DIR)/ftui/
