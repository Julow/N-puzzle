O_FILES :=	o/srcs/Grid.o o/srcs/GridParser.o o/srcs/Main.o \
			o/srcs/OCamlBinding.o o/srcs/PickState.o o/srcs/SolvingState.o \
			o/srcs/Tokenizer.o o/srcs/libftui_extend/Bookmark.o

LIBS_DEPEND := modules/libmodules.a

libs:
	make -C modules
.PHONY: libs



MAX_SOURCE_LEN := 32
o/srcs/Grid.o: srcs/Grid.cpp modules/_objs/_public/ft/assert.hpp \
	modules/_objs/_public/ft/Rect.hpp modules/_objs/_public/ft/Vec.hpp \
	modules/_objs/_public/ft/templates/Rect.tpp \
	modules/_objs/_public/ft/templates/Vec2.tpp \
	modules/_objs/_public/ft/templates/Vec3.tpp \
	modules/_objs/_public/ft/templates/Vec4.tpp \
	modules/_objs/_public/ft/type_traits.hpp \
	modules/_objs/_public/ft/utils.hpp include/Grid.hpp \
	modules/_objs/_public/ftlua/KeysWrapper.hpp \
	modules/_objs/_public/ftlua/conversions.hpp \
	modules/_objs/_public/ftlua/push.hpp modules/_objs/_public/ftlua/size.hpp \
	modules/_objs/_public/ftlua/stackassert.hpp \
	modules/_objs/_public/ftlua/types.hpp \
	modules/_objs/_public/ftlua/utils.hpp modules/_objs/_public/liblua/lua.hpp \
	include/GridParser.hpp include/Tokenizer.hpp | o/srcs/
o/srcs/GridParser.o: srcs/GridParser.cpp include/GridParser.hpp \
	include/Tokenizer.hpp modules/_objs/_public/ft/Rect.hpp \
	modules/_objs/_public/ft/Vec.hpp \
	modules/_objs/_public/ft/templates/Rect.tpp \
	modules/_objs/_public/ft/templates/Vec2.tpp \
	modules/_objs/_public/ft/templates/Vec3.tpp \
	modules/_objs/_public/ft/templates/Vec4.tpp \
	modules/_objs/_public/ft/type_traits.hpp \
	modules/_objs/_public/ft/utils.hpp modules/_objs/_public/ft/assert.hpp \
	| o/srcs/
o/srcs/Main.o: srcs/Main.cpp modules/_objs/_public/ft/Rect.hpp \
	modules/_objs/_public/ft/Vec.hpp \
	modules/_objs/_public/ft/templates/Rect.tpp \
	modules/_objs/_public/ft/templates/Vec2.tpp \
	modules/_objs/_public/ft/templates/Vec3.tpp \
	modules/_objs/_public/ft/templates/Vec4.tpp \
	modules/_objs/_public/ft/type_traits.hpp \
	modules/_objs/_public/ft/utils.hpp modules/_objs/_public/ft/assert.hpp \
	modules/_objs/_public/ft_xml/XmlParser.hpp \
	modules/_objs/_public/ft_xml/XmlTokenizer.hpp \
	modules/_objs/_public/ftlua/KeysWrapper.hpp \
	modules/_objs/_public/ftlua/call.hpp \
	modules/_objs/_public/ftlua/conversions.hpp \
	modules/_objs/_public/ftlua/ftlua.hpp \
	modules/_objs/_public/ftlua/light.hpp modules/_objs/_public/ftlua/pop.hpp \
	modules/_objs/_public/ftlua/push.hpp modules/_objs/_public/ftlua/set.hpp \
	modules/_objs/_public/ftlua/size.hpp \
	modules/_objs/_public/ftlua/stackassert.hpp \
	modules/_objs/_public/ftlua/templates/ftlua_caller.tpp \
	modules/_objs/_public/ftlua/templates/ftlua_handler.tpp \
	modules/_objs/_public/ftlua/types.hpp \
	modules/_objs/_public/ftlua/utils.hpp modules/_objs/_public/ftui/AView.hpp \
	modules/_objs/_public/ftui/ViewTemplate.hpp \
	modules/_objs/_public/ftui/libftui.hpp \
	modules/_objs/_public/ftui/templates/AView_callLuaCallback.tpp \
	modules/_objs/_public/liblua/lua.hpp include/libftui_extend/Bookmark.hpp \
	modules/_objs/_public/ft/Color.hpp modules/_objs/_public/ft/TupleRef.hpp \
	modules/_objs/_public/ftui/ACanvas.hpp \
	modules/_objs/_public/ftui/ALayout.hpp \
	modules/_objs/_public/ftui/ASolidView.hpp \
	modules/_objs/_public/ftui/Activity.hpp \
	modules/_objs/_public/ftui/EventTarget.hpp \
	modules/_objs/_public/ftui/EventTargetCpp.hpp \
	modules/_objs/_public/ftui/IViewHolder.hpp \
	modules/_objs/_public/ftui/templates/Activity.tpp include/Grid.hpp \
	include/IBundle.hpp include/ISolverListener.hpp include/IState.hpp \
	include/Main.hpp include/OCamlBinding.hpp modules/_objs/_public/gl/gl.hpp \
	modules/_objs/_public/gl_canvas/GlCanvasHolder.hpp \
	include/config_window.hpp modules/_objs/_public/ftce/math.hpp \
	include/PickState.hpp modules/_objs/_public/tiles/Tiles.hpp \
	include/SolvingState.hpp | o/srcs/
o/srcs/OCamlBinding.o: srcs/OCamlBinding.cpp include/Grid.hpp \
	include/ISolverListener.hpp include/OCamlBinding.hpp \
	modules/_objs/_public/ft/Rect.hpp modules/_objs/_public/ft/Vec.hpp \
	modules/_objs/_public/ft/templates/Rect.tpp \
	modules/_objs/_public/ft/templates/Vec2.tpp \
	modules/_objs/_public/ft/templates/Vec3.tpp \
	modules/_objs/_public/ft/templates/Vec4.tpp \
	modules/_objs/_public/ft/type_traits.hpp \
	modules/_objs/_public/ft/utils.hpp \
	modules/_objs/_public/ftlua/KeysWrapper.hpp \
	modules/_objs/_public/ftlua/conversions.hpp \
	modules/_objs/_public/ftlua/push.hpp modules/_objs/_public/ftlua/size.hpp \
	modules/_objs/_public/ftlua/stackassert.hpp \
	modules/_objs/_public/ftlua/types.hpp \
	modules/_objs/_public/ftlua/utils.hpp modules/_objs/_public/liblua/lua.hpp \
	| o/srcs/
o/srcs/PickState.o: srcs/PickState.cpp include/Grid.hpp include/IBundle.hpp \
	include/ISolverListener.hpp include/IState.hpp include/Main.hpp \
	include/OCamlBinding.hpp include/PickState.hpp \
	modules/_objs/_public/ft/Color.hpp modules/_objs/_public/ft/Rect.hpp \
	modules/_objs/_public/ft/TupleRef.hpp modules/_objs/_public/ft/Vec.hpp \
	modules/_objs/_public/ft/assert.hpp \
	modules/_objs/_public/ft/templates/Rect.tpp \
	modules/_objs/_public/ft/templates/Vec2.tpp \
	modules/_objs/_public/ft/templates/Vec3.tpp \
	modules/_objs/_public/ft/templates/Vec4.tpp \
	modules/_objs/_public/ft/type_traits.hpp \
	modules/_objs/_public/ft/utils.hpp \
	modules/_objs/_public/ft_xml/XmlParser.hpp \
	modules/_objs/_public/ft_xml/XmlTokenizer.hpp \
	modules/_objs/_public/ftlua/KeysWrapper.hpp \
	modules/_objs/_public/ftlua/call.hpp \
	modules/_objs/_public/ftlua/conversions.hpp \
	modules/_objs/_public/ftlua/ftlua.hpp \
	modules/_objs/_public/ftlua/light.hpp modules/_objs/_public/ftlua/pop.hpp \
	modules/_objs/_public/ftlua/push.hpp modules/_objs/_public/ftlua/set.hpp \
	modules/_objs/_public/ftlua/size.hpp \
	modules/_objs/_public/ftlua/stackassert.hpp \
	modules/_objs/_public/ftlua/templates/ftlua_caller.tpp \
	modules/_objs/_public/ftlua/templates/ftlua_handler.tpp \
	modules/_objs/_public/ftlua/types.hpp \
	modules/_objs/_public/ftlua/utils.hpp \
	modules/_objs/_public/ftui/ACanvas.hpp \
	modules/_objs/_public/ftui/AView.hpp \
	modules/_objs/_public/ftui/Activity.hpp \
	modules/_objs/_public/ftui/EventTarget.hpp \
	modules/_objs/_public/ftui/EventTargetCpp.hpp \
	modules/_objs/_public/ftui/IViewHolder.hpp \
	modules/_objs/_public/ftui/ViewTemplate.hpp \
	modules/_objs/_public/ftui/libftui.hpp \
	modules/_objs/_public/ftui/templates/AView_callLuaCallback.tpp \
	modules/_objs/_public/ftui/templates/Activity.tpp \
	modules/_objs/_public/gl/gl.hpp \
	modules/_objs/_public/gl_canvas/GlCanvasHolder.hpp \
	modules/_objs/_public/liblua/lua.hpp modules/_objs/_public/tiles/Tiles.hpp \
	include/SolvingState.hpp include/config_window.hpp \
	modules/_objs/_public/ftce/math.hpp | o/srcs/
o/srcs/SolvingState.o: srcs/SolvingState.cpp include/Grid.hpp \
	include/IBundle.hpp include/ISolverListener.hpp include/IState.hpp \
	include/Main.hpp include/OCamlBinding.hpp include/SolvingState.hpp \
	modules/_objs/_public/ft/Color.hpp modules/_objs/_public/ft/Rect.hpp \
	modules/_objs/_public/ft/TupleRef.hpp modules/_objs/_public/ft/Vec.hpp \
	modules/_objs/_public/ft/assert.hpp \
	modules/_objs/_public/ft/templates/Rect.tpp \
	modules/_objs/_public/ft/templates/Vec2.tpp \
	modules/_objs/_public/ft/templates/Vec3.tpp \
	modules/_objs/_public/ft/templates/Vec4.tpp \
	modules/_objs/_public/ft/type_traits.hpp \
	modules/_objs/_public/ft/utils.hpp \
	modules/_objs/_public/ft_xml/XmlParser.hpp \
	modules/_objs/_public/ft_xml/XmlTokenizer.hpp \
	modules/_objs/_public/ftlua/KeysWrapper.hpp \
	modules/_objs/_public/ftlua/call.hpp \
	modules/_objs/_public/ftlua/conversions.hpp \
	modules/_objs/_public/ftlua/ftlua.hpp \
	modules/_objs/_public/ftlua/light.hpp modules/_objs/_public/ftlua/pop.hpp \
	modules/_objs/_public/ftlua/push.hpp modules/_objs/_public/ftlua/set.hpp \
	modules/_objs/_public/ftlua/size.hpp \
	modules/_objs/_public/ftlua/stackassert.hpp \
	modules/_objs/_public/ftlua/templates/ftlua_caller.tpp \
	modules/_objs/_public/ftlua/templates/ftlua_handler.tpp \
	modules/_objs/_public/ftlua/types.hpp \
	modules/_objs/_public/ftlua/utils.hpp \
	modules/_objs/_public/ftui/ACanvas.hpp \
	modules/_objs/_public/ftui/AView.hpp \
	modules/_objs/_public/ftui/Activity.hpp \
	modules/_objs/_public/ftui/EventTarget.hpp \
	modules/_objs/_public/ftui/EventTargetCpp.hpp \
	modules/_objs/_public/ftui/IViewHolder.hpp \
	modules/_objs/_public/ftui/ViewTemplate.hpp \
	modules/_objs/_public/ftui/libftui.hpp \
	modules/_objs/_public/ftui/templates/AView_callLuaCallback.tpp \
	modules/_objs/_public/ftui/templates/Activity.tpp \
	modules/_objs/_public/gl/gl.hpp \
	modules/_objs/_public/gl_canvas/GlCanvasHolder.hpp \
	modules/_objs/_public/liblua/lua.hpp modules/_objs/_public/tiles/Tiles.hpp \
	include/config_window.hpp modules/_objs/_public/ftce/math.hpp | o/srcs/
o/srcs/Tokenizer.o: srcs/Tokenizer.cpp include/Tokenizer.hpp \
	modules/_objs/_public/ft/Rect.hpp modules/_objs/_public/ft/Vec.hpp \
	modules/_objs/_public/ft/templates/Rect.tpp \
	modules/_objs/_public/ft/templates/Vec2.tpp \
	modules/_objs/_public/ft/templates/Vec3.tpp \
	modules/_objs/_public/ft/templates/Vec4.tpp \
	modules/_objs/_public/ft/type_traits.hpp \
	modules/_objs/_public/ft/utils.hpp | o/srcs/
o/srcs/libftui_extend/Bookmark.o: srcs/libftui_extend/Bookmark.cpp \
	include/libftui_extend/Bookmark.hpp modules/_objs/_public/ft/Color.hpp \
	modules/_objs/_public/ft/Rect.hpp modules/_objs/_public/ft/TupleRef.hpp \
	modules/_objs/_public/ft/Vec.hpp modules/_objs/_public/ft/assert.hpp \
	modules/_objs/_public/ft/templates/Rect.tpp \
	modules/_objs/_public/ft/templates/Vec2.tpp \
	modules/_objs/_public/ft/templates/Vec3.tpp \
	modules/_objs/_public/ft/templates/Vec4.tpp \
	modules/_objs/_public/ft/type_traits.hpp \
	modules/_objs/_public/ft/utils.hpp \
	modules/_objs/_public/ft_xml/XmlParser.hpp \
	modules/_objs/_public/ft_xml/XmlTokenizer.hpp \
	modules/_objs/_public/ftlua/KeysWrapper.hpp \
	modules/_objs/_public/ftlua/call.hpp \
	modules/_objs/_public/ftlua/conversions.hpp \
	modules/_objs/_public/ftlua/ftlua.hpp \
	modules/_objs/_public/ftlua/light.hpp modules/_objs/_public/ftlua/pop.hpp \
	modules/_objs/_public/ftlua/push.hpp modules/_objs/_public/ftlua/set.hpp \
	modules/_objs/_public/ftlua/size.hpp \
	modules/_objs/_public/ftlua/stackassert.hpp \
	modules/_objs/_public/ftlua/templates/ftlua_caller.tpp \
	modules/_objs/_public/ftlua/templates/ftlua_handler.tpp \
	modules/_objs/_public/ftlua/types.hpp \
	modules/_objs/_public/ftlua/utils.hpp \
	modules/_objs/_public/ftui/ACanvas.hpp \
	modules/_objs/_public/ftui/ALayout.hpp \
	modules/_objs/_public/ftui/ASolidView.hpp \
	modules/_objs/_public/ftui/AView.hpp \
	modules/_objs/_public/ftui/Activity.hpp \
	modules/_objs/_public/ftui/EventTarget.hpp \
	modules/_objs/_public/ftui/EventTargetCpp.hpp \
	modules/_objs/_public/ftui/IViewHolder.hpp \
	modules/_objs/_public/ftui/ViewTemplate.hpp \
	modules/_objs/_public/ftui/libftui.hpp \
	modules/_objs/_public/ftui/templates/AView_callLuaCallback.tpp \
	modules/_objs/_public/ftui/templates/Activity.tpp \
	modules/_objs/_public/liblua/lua.hpp modules/_objs/_public/ftui/Button.hpp \
	| o/srcs/libftui_extend/
