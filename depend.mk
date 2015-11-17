O_FILES :=	o/srcs/GlCanvasHolder.o o/srcs/Grid.o o/srcs/Main.o \
			o/srcs/OCamlBinding.o o/srcs/PickState.o o/srcs/ftlua_extend.o \
			o/srcs/libftui_extend/Bookmark.o

LIBS_DEPEND := modules/libmodules.a

libs:
	make -C modules
.PHONY: libs



MAX_SOURCE_LEN := 32
o/srcs/GlCanvasHolder.o: srcs/GlCanvasHolder.cpp include/GlCanvasHolder.hpp \
	| o/srcs/
o/srcs/Grid.o: srcs/Grid.cpp include/Grid.hpp | o/srcs/
o/srcs/Main.o: srcs/Main.cpp include/GlCanvasHolder.hpp include/Grid.hpp \
	include/IBundle.hpp include/ISolverListener.hpp include/IState.hpp \
	include/Main.hpp include/OCamlBinding.hpp include/config_window.hpp \
	include/ftce/math.hpp include/PickState.hpp include/ftlua_extend.hpp \
	include/libftui_extend/Bookmark.hpp | o/srcs/
o/srcs/OCamlBinding.o: srcs/OCamlBinding.cpp include/Grid.hpp \
	include/ISolverListener.hpp include/OCamlBinding.hpp | o/srcs/
o/srcs/PickState.o: srcs/PickState.cpp include/GlCanvasHolder.hpp \
	include/Grid.hpp include/IBundle.hpp include/ISolverListener.hpp \
	include/IState.hpp include/Main.hpp include/OCamlBinding.hpp \
	include/PickState.hpp include/config_window.hpp include/ftce/math.hpp \
	| o/srcs/
o/srcs/ftlua_extend.o: srcs/ftlua_extend.cpp include/Grid.hpp | o/srcs/
o/srcs/libftui_extend/Bookmark.o: srcs/libftui_extend/Bookmark.cpp \
	include/libftui_extend/Bookmark.hpp | o/srcs/libftui_extend/
