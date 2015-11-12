LIBS_RULES += liblua
LINK_FLAGS += -lfreetype -Lliblua/lua-5.3.1/src -llua
O_FILES += $(O_DIR)/ft/assert.o $(O_DIR)/ft/padformat.o \
	$(O_DIR)/ftlua/cpp_utils.o $(O_DIR)/ftlua/push_utils.o \
	$(O_DIR)/ftui/ALayout.o $(O_DIR)/ftui/ALayout_luaHandler.o \
	$(O_DIR)/ftui/ASolidView.o $(O_DIR)/ftui/AView.o \
	$(O_DIR)/ftui/AView_luaHandler.o $(O_DIR)/ftui/AView_statics.o \
	$(O_DIR)/ftui/Activity.o $(O_DIR)/ftui/Activity_RootViewHolder.o \
	$(O_DIR)/ftui/Button.o $(O_DIR)/ftui/Canvas.o \
	$(O_DIR)/ftui/HorizontalLayout.o \
	$(O_DIR)/ftui/HorizontalLayout_ViewHolder.o $(O_DIR)/ftui/SolidView.o \
	$(O_DIR)/ftui/TextView.o $(O_DIR)/ftui/VerticalLayout.o \
	$(O_DIR)/ftui/VerticalLayout_ViewHolder.o $(O_DIR)/ftui/XmlParser.o \
	$(O_DIR)/ftui/XmlTokenizer.o $(O_DIR)/tiles/Tiles.o
PUBLIC_DIRS += ft/public ftlua/public ftui/public gl liblua/public \
	tiles/include

# module ft
$(O_DIR)/ft/assert.o $(O_DIR)/ft/padformat.o: INCLUDE_FLAGS += -Ift/public
$(O_DIR)/ft/assert.o: ft/assert.cpp ft/public/ft/Rect.hpp ft/public/ft/Vec.hpp \
	ft/public/ft/assert.hpp ft/public/ft/templates/Rect.tpp \
	ft/public/ft/templates/Vec2.tpp ft/public/ft/templates/Vec3.tpp \
	ft/public/ft/templates/Vec4.tpp ft/public/ft/utils.hpp | $(O_DIR)/ft/
$(O_DIR)/ft/padformat.o: ft/padformat.cpp ft/public/ft/Rect.hpp \
	ft/public/ft/Vec.hpp ft/public/ft/assert.hpp \
	ft/public/ft/templates/Rect.tpp ft/public/ft/templates/Vec2.tpp \
	ft/public/ft/templates/Vec3.tpp ft/public/ft/templates/Vec4.tpp \
	ft/public/ft/utils.hpp | $(O_DIR)/ft/

# module ftlua
$(O_DIR)/ftlua/cpp_utils.o $(O_DIR)/ftlua/push_utils.o: BASE_FLAGS += -DRES_PATH='"$(abspath ftlua/res/)"'
$(O_DIR)/ftlua/cpp_utils.o $(O_DIR)/ftlua/push_utils.o: INCLUDE_FLAGS += \
	-Iftlua/public -Ift/public -Iliblua/public
$(O_DIR)/ftlua/cpp_utils.o: ftlua/cpp_utils.cpp ft/public/ft/Rect.hpp \
	ft/public/ft/Vec.hpp ft/public/ft/assert.hpp \
	ft/public/ft/templates/Rect.tpp ft/public/ft/templates/Vec2.tpp \
	ft/public/ft/templates/Vec3.tpp ft/public/ft/templates/Vec4.tpp \
	ft/public/ft/utils.hpp ftlua/public/ftlua/ftlua.hpp \
	ftlua/public/ftlua/templates/ftlua_caller.tpp \
	ftlua/public/ftlua/templates/ftlua_handler.tpp liblua/public/liblua.hpp \
	| $(O_DIR)/ftlua/
$(O_DIR)/ftlua/push_utils.o: ftlua/push_utils.cpp ft/public/ft/Rect.hpp \
	ft/public/ft/Vec.hpp ft/public/ft/assert.hpp ft/public/ft/assert.hpp \
	ft/public/ft/templates/Rect.tpp ft/public/ft/templates/Vec2.tpp \
	ft/public/ft/templates/Vec3.tpp ft/public/ft/templates/Vec4.tpp \
	ft/public/ft/utils.hpp ftlua/public/ftlua/ftlua.hpp \
	ftlua/public/ftlua/templates/ftlua_caller.tpp \
	ftlua/public/ftlua/templates/ftlua_handler.tpp liblua/public/liblua.hpp \
	| $(O_DIR)/ftlua/

# module ftui
$(O_DIR)/ftui/ALayout.o $(O_DIR)/ftui/ALayout_luaHandler.o \
$(O_DIR)/ftui/ASolidView.o $(O_DIR)/ftui/AView.o \
$(O_DIR)/ftui/AView_luaHandler.o $(O_DIR)/ftui/AView_statics.o \
$(O_DIR)/ftui/Activity.o $(O_DIR)/ftui/Activity_RootViewHolder.o \
$(O_DIR)/ftui/Button.o $(O_DIR)/ftui/Canvas.o $(O_DIR)/ftui/HorizontalLayout.o \
$(O_DIR)/ftui/HorizontalLayout_ViewHolder.o $(O_DIR)/ftui/SolidView.o \
$(O_DIR)/ftui/TextView.o $(O_DIR)/ftui/VerticalLayout.o \
$(O_DIR)/ftui/VerticalLayout_ViewHolder.o $(O_DIR)/ftui/XmlParser.o \
$(O_DIR)/ftui/XmlTokenizer.o: BASE_FLAGS += -DRES_PATH='"$(abspath ftui/res/)"'
$(O_DIR)/ftui/ALayout.o $(O_DIR)/ftui/ALayout_luaHandler.o \
$(O_DIR)/ftui/ASolidView.o $(O_DIR)/ftui/AView.o \
$(O_DIR)/ftui/AView_luaHandler.o $(O_DIR)/ftui/AView_statics.o \
$(O_DIR)/ftui/Activity.o $(O_DIR)/ftui/Activity_RootViewHolder.o \
$(O_DIR)/ftui/Button.o $(O_DIR)/ftui/Canvas.o $(O_DIR)/ftui/HorizontalLayout.o \
$(O_DIR)/ftui/HorizontalLayout_ViewHolder.o $(O_DIR)/ftui/SolidView.o \
$(O_DIR)/ftui/TextView.o $(O_DIR)/ftui/VerticalLayout.o \
$(O_DIR)/ftui/VerticalLayout_ViewHolder.o $(O_DIR)/ftui/XmlParser.o \
$(O_DIR)/ftui/XmlTokenizer.o: INCLUDE_FLAGS += -Iftlua/public -Ift/public \
	-Iliblua/public -Iftui/public
$(O_DIR)/ftui/ALayout.o: ftui/ALayout.cpp ft/public/ft/Color.hpp \
	ft/public/ft/Rect.hpp ft/public/ft/Vec.hpp ft/public/ft/assert.hpp \
	ft/public/ft/templates/Rect.tpp ft/public/ft/templates/Vec2.tpp \
	ft/public/ft/templates/Vec3.tpp ft/public/ft/templates/Vec4.tpp \
	ft/public/ft/utils.hpp ft/public/ft/utils.hpp ftlua/public/ftlua/ftlua.hpp \
	ftlua/public/ftlua/templates/ftlua_caller.tpp \
	ftlua/public/ftlua/templates/ftlua_handler.tpp \
	ftui/public/ftui/ALayout.hpp ftui/public/ftui/ASolidView.hpp \
	ftui/public/ftui/AView.hpp ftui/public/ftui/Canvas.hpp \
	ftui/public/ftui/IViewHolder.hpp ftui/public/ftui/XmlParser.hpp \
	ftui/public/ftui/XmlTokenizer.hpp ftui/public/ftui/libftui.hpp \
	liblua/public/liblua.hpp | $(O_DIR)/ftui/
$(O_DIR)/ftui/ALayout_luaHandler.o: ftui/ALayout_luaHandler.cpp \
	ft/public/ft/Color.hpp ft/public/ft/Rect.hpp ft/public/ft/Vec.hpp \
	ft/public/ft/assert.hpp ft/public/ft/templates/Rect.tpp \
	ft/public/ft/templates/Vec2.tpp ft/public/ft/templates/Vec3.tpp \
	ft/public/ft/templates/Vec4.tpp ft/public/ft/utils.hpp \
	ftlua/public/ftlua/ftlua.hpp ftlua/public/ftlua/ftlua.hpp \
	ftlua/public/ftlua/templates/ftlua_caller.tpp \
	ftlua/public/ftlua/templates/ftlua_handler.tpp \
	ftui/public/ftui/ALayout.hpp ftui/public/ftui/ASolidView.hpp \
	ftui/public/ftui/AView.hpp ftui/public/ftui/Canvas.hpp \
	ftui/public/ftui/libftui.hpp liblua/public/liblua.hpp | $(O_DIR)/ftui/
$(O_DIR)/ftui/ASolidView.o: ftui/ASolidView.cpp ft/public/ft/Color.hpp \
	ft/public/ft/Rect.hpp ft/public/ft/Vec.hpp ft/public/ft/assert.hpp \
	ft/public/ft/templates/Rect.tpp ft/public/ft/templates/Vec2.tpp \
	ft/public/ft/templates/Vec3.tpp ft/public/ft/templates/Vec4.tpp \
	ft/public/ft/utils.hpp ft/public/ft/utils.hpp ftlua/public/ftlua/ftlua.hpp \
	ftlua/public/ftlua/templates/ftlua_caller.tpp \
	ftlua/public/ftlua/templates/ftlua_handler.tpp \
	ftui/public/ftui/ASolidView.hpp ftui/public/ftui/AView.hpp \
	ftui/public/ftui/Canvas.hpp ftui/public/ftui/IViewHolder.hpp \
	ftui/public/ftui/XmlParser.hpp ftui/public/ftui/XmlTokenizer.hpp \
	ftui/public/ftui/libftui.hpp liblua/public/liblua.hpp | $(O_DIR)/ftui/
$(O_DIR)/ftui/AView.o: ftui/AView.cpp ft/public/ft/Color.hpp \
	ft/public/ft/Rect.hpp ft/public/ft/Vec.hpp ft/public/ft/assert.hpp \
	ft/public/ft/templates/Rect.tpp ft/public/ft/templates/Vec2.tpp \
	ft/public/ft/templates/Vec3.tpp ft/public/ft/templates/Vec4.tpp \
	ft/public/ft/utils.hpp ftlua/public/ftlua/ftlua.hpp \
	ftlua/public/ftlua/templates/ftlua_caller.tpp \
	ftlua/public/ftlua/templates/ftlua_handler.tpp \
	ftui/public/ftui/ALayout.hpp ftui/public/ftui/ASolidView.hpp \
	ftui/public/ftui/AView.hpp ftui/public/ftui/Activity.hpp \
	ftui/public/ftui/Canvas.hpp ftui/public/ftui/DefaultEventBox.hpp \
	ftui/public/ftui/EventBox.hpp ftui/public/ftui/EventParams.hpp \
	ftui/public/ftui/EventParams.hpp ftui/public/ftui/IEventBox.hpp \
	ftui/public/ftui/IEventParams.hpp ftui/public/ftui/IViewHolder.hpp \
	ftui/public/ftui/IViewHolder.hpp ftui/public/ftui/VerticalLayout.hpp \
	ftui/public/ftui/XmlParser.hpp ftui/public/ftui/XmlTokenizer.hpp \
	ftui/public/ftui/libftui.hpp \
	ftui/public/ftui/templates/AView_callLuaCallback.tpp \
	ftui/public/ftui/templates/Activity.tpp \
	ftui/public/ftui/templates/DefaultEventBox.tpp \
	ftui/public/ftui/templates/EventBox.tpp liblua/public/liblua.hpp \
	| $(O_DIR)/ftui/
$(O_DIR)/ftui/AView_luaHandler.o: ftui/AView_luaHandler.cpp \
	ft/public/ft/Color.hpp ft/public/ft/Rect.hpp ft/public/ft/Vec.hpp \
	ft/public/ft/assert.hpp ft/public/ft/templates/Rect.tpp \
	ft/public/ft/templates/Vec2.tpp ft/public/ft/templates/Vec3.tpp \
	ft/public/ft/templates/Vec4.tpp ft/public/ft/utils.hpp \
	ftlua/public/ftlua/ftlua.hpp ftlua/public/ftlua/ftlua.hpp \
	ftlua/public/ftlua/templates/ftlua_caller.tpp \
	ftlua/public/ftlua/templates/ftlua_handler.tpp \
	ftui/public/ftui/ASolidView.hpp ftui/public/ftui/AView.hpp \
	ftui/public/ftui/Canvas.hpp ftui/public/ftui/IViewHolder.hpp \
	ftui/public/ftui/TextView.hpp ftui/public/ftui/libftui.hpp \
	liblua/public/liblua.hpp | $(O_DIR)/ftui/
$(O_DIR)/ftui/AView_statics.o: ftui/AView_statics.cpp ft/public/ft/Color.hpp \
	ft/public/ft/Rect.hpp ft/public/ft/Vec.hpp ft/public/ft/assert.hpp \
	ft/public/ft/templates/Rect.tpp ft/public/ft/templates/Vec2.tpp \
	ft/public/ft/templates/Vec3.tpp ft/public/ft/templates/Vec4.tpp \
	ft/public/ft/utils.hpp ftlua/public/ftlua/ftlua.hpp \
	ftlua/public/ftlua/ftlua.hpp ftlua/public/ftlua/templates/ftlua_caller.tpp \
	ftlua/public/ftlua/templates/ftlua_handler.tpp \
	ftui/public/ftui/ALayout.hpp ftui/public/ftui/ASolidView.hpp \
	ftui/public/ftui/ASolidView.hpp ftui/public/ftui/AView.hpp \
	ftui/public/ftui/Button.hpp ftui/public/ftui/Canvas.hpp \
	ftui/public/ftui/HorizontalLayout.hpp ftui/public/ftui/IViewHolder.hpp \
	ftui/public/ftui/SolidView.hpp ftui/public/ftui/TextView.hpp \
	ftui/public/ftui/VerticalLayout.hpp ftui/public/ftui/libftui.hpp \
	liblua/public/liblua.hpp | $(O_DIR)/ftui/
$(O_DIR)/ftui/Activity.o: ftui/Activity.cpp ft/public/ft/Color.hpp \
	ft/public/ft/Rect.hpp ft/public/ft/Vec.hpp ft/public/ft/assert.hpp \
	ft/public/ft/templates/Rect.tpp ft/public/ft/templates/Vec2.tpp \
	ft/public/ft/templates/Vec3.tpp ft/public/ft/templates/Vec4.tpp \
	ft/public/ft/utils.hpp ftlua/public/ftlua/ftlua.hpp \
	ftlua/public/ftlua/templates/ftlua_caller.tpp \
	ftlua/public/ftlua/templates/ftlua_handler.tpp ftui/public/ftui/AView.hpp \
	ftui/public/ftui/Activity.hpp ftui/public/ftui/Canvas.hpp \
	ftui/public/ftui/DefaultEventBox.hpp ftui/public/ftui/EventBox.hpp \
	ftui/public/ftui/EventParams.hpp ftui/public/ftui/IEventBox.hpp \
	ftui/public/ftui/IEventParams.hpp ftui/public/ftui/IViewHolder.hpp \
	ftui/public/ftui/XmlParser.hpp ftui/public/ftui/XmlTokenizer.hpp \
	ftui/public/ftui/libftui.hpp ftui/public/ftui/templates/Activity.tpp \
	ftui/public/ftui/templates/DefaultEventBox.tpp \
	ftui/public/ftui/templates/EventBox.tpp liblua/public/liblua.hpp \
	| $(O_DIR)/ftui/
$(O_DIR)/ftui/Activity_RootViewHolder.o: ftui/Activity_RootViewHolder.cpp \
	ft/public/ft/Rect.hpp ft/public/ft/Vec.hpp ft/public/ft/assert.hpp \
	ft/public/ft/templates/Rect.tpp ft/public/ft/templates/Vec2.tpp \
	ft/public/ft/templates/Vec3.tpp ft/public/ft/templates/Vec4.tpp \
	ft/public/ft/utils.hpp ftlua/public/ftlua/ftlua.hpp \
	ftlua/public/ftlua/templates/ftlua_caller.tpp \
	ftlua/public/ftlua/templates/ftlua_handler.tpp ftui/public/ftui/AView.hpp \
	ftui/public/ftui/Activity.hpp ftui/public/ftui/DefaultEventBox.hpp \
	ftui/public/ftui/EventBox.hpp ftui/public/ftui/EventParams.hpp \
	ftui/public/ftui/IEventBox.hpp ftui/public/ftui/IEventParams.hpp \
	ftui/public/ftui/IViewHolder.hpp ftui/public/ftui/XmlParser.hpp \
	ftui/public/ftui/XmlTokenizer.hpp ftui/public/ftui/libftui.hpp \
	ftui/public/ftui/templates/Activity.tpp \
	ftui/public/ftui/templates/DefaultEventBox.tpp \
	ftui/public/ftui/templates/EventBox.tpp liblua/public/liblua.hpp \
	| $(O_DIR)/ftui/
$(O_DIR)/ftui/Button.o: ftui/Button.cpp ft/public/ft/Color.hpp \
	ft/public/ft/Rect.hpp ft/public/ft/Vec.hpp ft/public/ft/assert.hpp \
	ft/public/ft/templates/Rect.tpp ft/public/ft/templates/Vec2.tpp \
	ft/public/ft/templates/Vec3.tpp ft/public/ft/templates/Vec4.tpp \
	ft/public/ft/utils.hpp ftlua/public/ftlua/ftlua.hpp \
	ftlua/public/ftlua/templates/ftlua_caller.tpp \
	ftlua/public/ftlua/templates/ftlua_handler.tpp ftui/public/ftui/AView.hpp \
	ftui/public/ftui/Activity.hpp ftui/public/ftui/Button.hpp \
	ftui/public/ftui/Canvas.hpp ftui/public/ftui/DefaultEventBox.hpp \
	ftui/public/ftui/EventBox.hpp ftui/public/ftui/EventParams.hpp \
	ftui/public/ftui/IEventBox.hpp ftui/public/ftui/IEventParams.hpp \
	ftui/public/ftui/IViewHolder.hpp ftui/public/ftui/IViewHolder.hpp \
	ftui/public/ftui/libftui.hpp ftui/public/ftui/templates/Activity.tpp \
	ftui/public/ftui/templates/DefaultEventBox.tpp \
	ftui/public/ftui/templates/EventBox.tpp liblua/public/liblua.hpp \
	| $(O_DIR)/ftui/
$(O_DIR)/ftui/Canvas.o: ftui/Canvas.cpp ft/public/ft/Color.hpp \
	ft/public/ft/Rect.hpp ft/public/ft/Vec.hpp ft/public/ft/assert.hpp \
	ft/public/ft/templates/Rect.tpp ft/public/ft/templates/Vec2.tpp \
	ft/public/ft/templates/Vec3.tpp ft/public/ft/templates/Vec4.tpp \
	ft/public/ft/utils.hpp ft/public/ft/utils.hpp ftlua/public/ftlua/ftlua.hpp \
	ftlua/public/ftlua/ftlua.hpp ftlua/public/ftlua/templates/ftlua_caller.tpp \
	ftlua/public/ftlua/templates/ftlua_handler.tpp ftui/public/ftui/Canvas.hpp \
	ftui/public/ftui/libftui.hpp liblua/public/liblua.hpp | $(O_DIR)/ftui/
$(O_DIR)/ftui/HorizontalLayout.o: ftui/HorizontalLayout.cpp \
	ft/public/ft/Color.hpp ft/public/ft/Rect.hpp ft/public/ft/Vec.hpp \
	ft/public/ft/assert.hpp ft/public/ft/templates/Rect.tpp \
	ft/public/ft/templates/Vec2.tpp ft/public/ft/templates/Vec3.tpp \
	ft/public/ft/templates/Vec4.tpp ft/public/ft/utils.hpp \
	ft/public/ft/utils.hpp ftlua/public/ftlua/ftlua.hpp \
	ftlua/public/ftlua/templates/ftlua_caller.tpp \
	ftlua/public/ftlua/templates/ftlua_handler.tpp \
	ftui/public/ftui/ALayout.hpp ftui/public/ftui/ASolidView.hpp \
	ftui/public/ftui/AView.hpp ftui/public/ftui/Canvas.hpp \
	ftui/public/ftui/Canvas.hpp ftui/public/ftui/HorizontalLayout.hpp \
	ftui/public/ftui/IViewHolder.hpp ftui/public/ftui/XmlParser.hpp \
	ftui/public/ftui/XmlTokenizer.hpp ftui/public/ftui/libftui.hpp \
	liblua/public/liblua.hpp | $(O_DIR)/ftui/
$(O_DIR)/ftui/HorizontalLayout_ViewHolder.o: \
	ftui/HorizontalLayout_ViewHolder.cpp ft/public/ft/Color.hpp \
	ft/public/ft/Rect.hpp ft/public/ft/Vec.hpp ft/public/ft/assert.hpp \
	ft/public/ft/templates/Rect.tpp ft/public/ft/templates/Vec2.tpp \
	ft/public/ft/templates/Vec3.tpp ft/public/ft/templates/Vec4.tpp \
	ft/public/ft/utils.hpp ftlua/public/ftlua/ftlua.hpp \
	ftlua/public/ftlua/templates/ftlua_caller.tpp \
	ftlua/public/ftlua/templates/ftlua_handler.tpp \
	ftui/public/ftui/ALayout.hpp ftui/public/ftui/ASolidView.hpp \
	ftui/public/ftui/AView.hpp ftui/public/ftui/Activity.hpp \
	ftui/public/ftui/Canvas.hpp ftui/public/ftui/DefaultEventBox.hpp \
	ftui/public/ftui/EventBox.hpp ftui/public/ftui/EventParams.hpp \
	ftui/public/ftui/HorizontalLayout.hpp ftui/public/ftui/IEventBox.hpp \
	ftui/public/ftui/IEventParams.hpp ftui/public/ftui/IViewHolder.hpp \
	ftui/public/ftui/XmlParser.hpp ftui/public/ftui/XmlTokenizer.hpp \
	ftui/public/ftui/libftui.hpp ftui/public/ftui/templates/Activity.tpp \
	ftui/public/ftui/templates/DefaultEventBox.tpp \
	ftui/public/ftui/templates/EventBox.tpp liblua/public/liblua.hpp \
	| $(O_DIR)/ftui/
$(O_DIR)/ftui/SolidView.o: ftui/SolidView.cpp ft/public/ft/Color.hpp \
	ft/public/ft/Rect.hpp ft/public/ft/Vec.hpp ft/public/ft/assert.hpp \
	ft/public/ft/templates/Rect.tpp ft/public/ft/templates/Vec2.tpp \
	ft/public/ft/templates/Vec3.tpp ft/public/ft/templates/Vec4.tpp \
	ft/public/ft/utils.hpp ftlua/public/ftlua/ftlua.hpp \
	ftlua/public/ftlua/templates/ftlua_caller.tpp \
	ftlua/public/ftlua/templates/ftlua_handler.tpp \
	ftui/public/ftui/ASolidView.hpp ftui/public/ftui/AView.hpp \
	ftui/public/ftui/Canvas.hpp ftui/public/ftui/SolidView.hpp \
	ftui/public/ftui/libftui.hpp liblua/public/liblua.hpp | $(O_DIR)/ftui/
$(O_DIR)/ftui/TextView.o: ftui/TextView.cpp ft/public/ft/Color.hpp \
	ft/public/ft/Rect.hpp ft/public/ft/Vec.hpp ft/public/ft/assert.hpp \
	ft/public/ft/templates/Rect.tpp ft/public/ft/templates/Vec2.tpp \
	ft/public/ft/templates/Vec3.tpp ft/public/ft/templates/Vec4.tpp \
	ft/public/ft/utils.hpp ftlua/public/ftlua/ftlua.hpp \
	ftlua/public/ftlua/templates/ftlua_caller.tpp \
	ftlua/public/ftlua/templates/ftlua_handler.tpp \
	ftui/public/ftui/ASolidView.hpp ftui/public/ftui/AView.hpp \
	ftui/public/ftui/Canvas.hpp ftui/public/ftui/IViewHolder.hpp \
	ftui/public/ftui/TextView.hpp ftui/public/ftui/libftui.hpp \
	liblua/public/liblua.hpp | $(O_DIR)/ftui/
$(O_DIR)/ftui/VerticalLayout.o: ftui/VerticalLayout.cpp ft/public/ft/Color.hpp \
	ft/public/ft/Rect.hpp ft/public/ft/Vec.hpp ft/public/ft/assert.hpp \
	ft/public/ft/templates/Rect.tpp ft/public/ft/templates/Vec2.tpp \
	ft/public/ft/templates/Vec3.tpp ft/public/ft/templates/Vec4.tpp \
	ft/public/ft/utils.hpp ft/public/ft/utils.hpp ftlua/public/ftlua/ftlua.hpp \
	ftlua/public/ftlua/templates/ftlua_caller.tpp \
	ftlua/public/ftlua/templates/ftlua_handler.tpp \
	ftui/public/ftui/ALayout.hpp ftui/public/ftui/ASolidView.hpp \
	ftui/public/ftui/AView.hpp ftui/public/ftui/Canvas.hpp \
	ftui/public/ftui/Canvas.hpp ftui/public/ftui/IViewHolder.hpp \
	ftui/public/ftui/VerticalLayout.hpp ftui/public/ftui/XmlParser.hpp \
	ftui/public/ftui/XmlTokenizer.hpp ftui/public/ftui/libftui.hpp \
	liblua/public/liblua.hpp | $(O_DIR)/ftui/
$(O_DIR)/ftui/VerticalLayout_ViewHolder.o: ftui/VerticalLayout_ViewHolder.cpp \
	ft/public/ft/Color.hpp ft/public/ft/Rect.hpp ft/public/ft/Vec.hpp \
	ft/public/ft/assert.hpp ft/public/ft/templates/Rect.tpp \
	ft/public/ft/templates/Vec2.tpp ft/public/ft/templates/Vec3.tpp \
	ft/public/ft/templates/Vec4.tpp ft/public/ft/utils.hpp \
	ftlua/public/ftlua/ftlua.hpp ftlua/public/ftlua/templates/ftlua_caller.tpp \
	ftlua/public/ftlua/templates/ftlua_handler.tpp \
	ftui/public/ftui/ALayout.hpp ftui/public/ftui/ASolidView.hpp \
	ftui/public/ftui/AView.hpp ftui/public/ftui/Activity.hpp \
	ftui/public/ftui/Canvas.hpp ftui/public/ftui/DefaultEventBox.hpp \
	ftui/public/ftui/EventBox.hpp ftui/public/ftui/EventParams.hpp \
	ftui/public/ftui/IEventBox.hpp ftui/public/ftui/IEventParams.hpp \
	ftui/public/ftui/IViewHolder.hpp ftui/public/ftui/VerticalLayout.hpp \
	ftui/public/ftui/XmlParser.hpp ftui/public/ftui/XmlTokenizer.hpp \
	ftui/public/ftui/libftui.hpp ftui/public/ftui/templates/Activity.tpp \
	ftui/public/ftui/templates/DefaultEventBox.tpp \
	ftui/public/ftui/templates/EventBox.tpp liblua/public/liblua.hpp \
	| $(O_DIR)/ftui/
$(O_DIR)/ftui/XmlParser.o: ftui/XmlParser.cpp ft/public/ft/Rect.hpp \
	ft/public/ft/Vec.hpp ft/public/ft/assert.hpp \
	ft/public/ft/templates/Rect.tpp ft/public/ft/templates/Vec2.tpp \
	ft/public/ft/templates/Vec3.tpp ft/public/ft/templates/Vec4.tpp \
	ft/public/ft/utils.hpp ftui/public/ftui/XmlParser.hpp \
	ftui/public/ftui/XmlTokenizer.hpp ftui/public/ftui/libftui.hpp \
	| $(O_DIR)/ftui/
$(O_DIR)/ftui/XmlTokenizer.o: ftui/XmlTokenizer.cpp ft/public/ft/Rect.hpp \
	ft/public/ft/Vec.hpp ft/public/ft/assert.hpp \
	ft/public/ft/templates/Rect.tpp ft/public/ft/templates/Vec2.tpp \
	ft/public/ft/templates/Vec3.tpp ft/public/ft/templates/Vec4.tpp \
	ft/public/ft/utils.hpp ftui/public/ftui/XmlTokenizer.hpp \
	ftui/public/ftui/libftui.hpp | $(O_DIR)/ftui/

# module gl
ifeq ($(shell uname),Darwin)
  BASE_FLAGS += -DMAC_OS_MODE=1
  LINK_FLAGS += -lglfw3 -framework OpenGL
else
  LINK_FLAGS += -lglfw -lGL -lGLEW
endif

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

# module tiles
$(O_DIR)/tiles/Tiles.o: INCLUDE_FLAGS += -Ift/public -Igl -Itiles/include
$(O_DIR)/tiles/Tiles.o: tiles/Tiles.cpp ft/public/ft/Vec.hpp \
	ft/public/ft/templates/Vec2.tpp ft/public/ft/templates/Vec3.tpp \
	ft/public/ft/templates/Vec4.tpp gl/gl.h gl/gl.hpp \
	tiles/include/tiles/Tiles.hpp | $(O_DIR)/tiles/
