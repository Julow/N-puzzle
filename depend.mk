O_FILES :=	o/srcs/Grid.o o/srcs/GridParser.o o/srcs/Main.o \
			o/srcs/OCamlBinding.o o/srcs/PickState.o o/srcs/Tokenizer.o \
			o/srcs/libftui_extend/Bookmark.o

LIBS_DEPEND := modules/libmodules.a

libs:
	make -C modules
.PHONY: libs



MAX_SOURCE_LEN := 32
o/srcs/Grid.o: srcs/Grid.cpp include/Grid.hpp include/GridParser.hpp \
	include/Tokenizer.hpp | o/srcs/
o/srcs/GridParser.o: srcs/GridParser.cpp include/GridParser.hpp \
	include/Tokenizer.hpp | o/srcs/
o/srcs/Main.o: srcs/Main.cpp include/Grid.hpp include/IBundle.hpp \
	include/ISolverListener.hpp include/IState.hpp include/Main.hpp \
	include/OCamlBinding.hpp include/ftlua_extend.hpp \
	include/config_window.hpp include/PickState.hpp \
	include/libftui_extend/Bookmark.hpp | o/srcs/
o/srcs/OCamlBinding.o: srcs/OCamlBinding.cpp include/Grid.hpp \
	include/ISolverListener.hpp include/OCamlBinding.hpp | o/srcs/
o/srcs/PickState.o: srcs/PickState.cpp include/Grid.hpp include/IBundle.hpp \
	include/ISolverListener.hpp include/IState.hpp include/Main.hpp \
	include/OCamlBinding.hpp include/PickState.hpp include/ftlua_extend.hpp \
	include/config_window.hpp | o/srcs/
o/srcs/Tokenizer.o: srcs/Tokenizer.cpp include/Tokenizer.hpp | o/srcs/
o/srcs/libftui_extend/Bookmark.o: srcs/libftui_extend/Bookmark.cpp \
	include/libftui_extend/Bookmark.hpp | o/srcs/libftui_extend/
