#

# Executable name
NAME			:= npuzzle

# Project directories
DIRS			:= srcs include modules/ft/public modules/ftlua/public modules/ftui/public modules/liblua/public modules/tiles/include modules/gl modules/ft_xml/include/public

# Git submodule to init
MODULES			:=
# Makefiles to call
LIBS			:= modules

# Base flags
BASE_FLAGS		= -Wall -Wextra
HEAD_FLAGS		= $(addprefix -I,$(DIRS))

# Compilation flags (per language)
C_FLAGS			= $(HEAD_FLAGS) $(BASE_FLAGS)
CPP_FLAGS		= $(HEAD_FLAGS) $(BASE_FLAGS) -std=c++14

LINK_FLAGS		= $(BASE_FLAGS) -Lmodules -lmodules -Lmodules/liblua -llua -lfreetype

ifeq ($(DEBUG_MODE),1)
	# Extra flags used in debug mode
	BASE_FLAGS	+= -g
	C_FLAGS		+=
	CPP_FLAGS	+=
else
	# Extra flags used when not in debug mode
	BASE_FLAGS	+= -O2
	C_FLAGS		+=
	CPP_FLAGS	+=
endif

DEBUG_MODE		?= 0
export DEBUG_MODE

# Ocaml flags
OCAML_WHERE		:= $(shell ocamlc -where)
HEAD_FLAGS		+= -I$(OCAML_WHERE)
LINK_FLAGS		+= -L$(OCAML_WHERE) -lunix -lasmrun -lthreadsnat -lncurses

OCAML_SOLVER	= $(O_DIR)/ocaml_solver.o

OCAML_LINKS		= -thread unix.cmxa threads/threads.cmxa
OCAML_FLAGS		=

# Extra libs
ifeq ($(shell uname),Darwin)
	BASE_FLAGS	+= -DMAC_OS_MODE=1
	LINK_FLAGS	+= -lglfw3 -framework OpenGL
else
	LINK_FLAGS	+= -lglfw -lGL -lGLEW -ldl
endif

# Jobs
JOBS			:= 8

# Column output
COLUMN_OUTPUT	:= 1

ifeq ($(COLUMN_OUTPUT),0)
	PRINT_OK	= printf '\033[32m$<\033[0m\n'
	PRINT_LINK	= printf '\033[32m$(NAME)\033[0m\n'
else
	PRINT_OK	= echo $(patsubst $(firstword $(DIRS))/%,%,$<) >> $(PRINT_FILE)
	PRINT_LINK	= printf '\n\033[32m$(NAME)\033[0m\n'
endif

# Objects directory
O_DIR		:= o

# Depend file name
DEPEND		:= depend.mk
ML_DEPEND	:= ml_depend.mk

# tmp
MODULE_RULES	:= $(addsuffix /.git,$(MODULES))
PRINT_FILE		:= .tmp_print
SHELL			:= /bin/bash

MAX_SOURCE_LEN	= 20

# Default rule (need to be before any include)
all: $(MODULE_RULES) libs
ifeq ($(COLUMN_OUTPUT),0)
	make -j$(JOBS) $(NAME)
else
	PER_LINE=$$((`tput cols` / $$(($(MAX_SOURCE_LEN) + 2))));			\
	CURR=0;																\
	rm -f $(PRINT_FILE);												\
	touch $(PRINT_FILE);												\
	tail -n0 -f $(PRINT_FILE) | while read l;							\
	do																	\
		if [[ $$CURR -ge $$PER_LINE ]];									\
		then															\
			CURR=0;														\
			echo;														\
		fi;																\
		CURR=$$(($$CURR + 1));											\
		printf '\033[32m%-*s\033[0m  ' "$(MAX_SOURCE_LEN)" "$$l";		\
	done &																\
	make -j$(JOBS) $(NAME);												\
	STATUS=$$?;															\
	kill -9 `jobs -p`;													\
	rm -f $(PRINT_FILE);												\
	exit $$STATUS
endif

# Include $(O_FILES) and dependencies
include $(DEPEND)
include $(ML_DEPEND)

MAX_SOURCE_LEN	:= $(shell if [[ $(MAX_SOURCE_LEN) -gt $(ML_MAX_LEN) ]]; then echo $(MAX_SOURCE_LEN); else echo $(ML_MAX_LEN); fi)

# Linking
$(NAME): $(LIBS_DEPEND) $(O_FILES) $(OCAML_SOLVER)
	clang++ -o $(NAME) $(O_FILES) $(OCAML_SOLVER) $(LINK_FLAGS) && $(PRINT_LINK)

# C
$(O_DIR)/%.o: %.c
	clang $(C_FLAGS) -c $< -o $@ && $(PRINT_OK)
# Cpp
$(O_DIR)/%.o: %.cpp
	clang++ $(CPP_FLAGS) -c $< -o $@ && $(PRINT_OK)
# Ocaml
%.cmi: %.mli
	ocamlopt.opt $(OCAML_LINKS) $(OCAML_FLAGS) -c $< && $(PRINT_OK)
%.cmx: %.ml
	ocamlopt.opt $(OCAML_LINKS) $(OCAML_FLAGS) -c $< && $(PRINT_OK)
$(OCAML_SOLVER): $(ML_OBJS)
	ocamlopt.opt $(OCAML_LINKS) -output-obj -o $@ $(filter %.cmx,$^)

ocamldep:
	bash ocaml_depend.sh > $(ML_DEPEND)
.PHONY: ocamldep

# Init submodules
$(MODULE_RULES):
	git submodule init $(@:.git=)
	git submodule update $(@:.git=)

# Create obj directories
$(O_DIR)/%/:
	mkdir -p $@

# Set debug mode and make
debug: _debug all

# Clean, set debug mode and make
rebug: fclean debug

# Clean obj files
clean:
	rm -f $(PRINT_FILE)
	rm -f $(O_FILES)
	rm -f $(ML_OBJS) $(SOLVER)

# Clean everything
fclean: clean
	rm -f $(NAME)

# Clean and make
re: fclean all

# Set debug flags
_debug:
	$(eval DEBUG_MODE = 1)

.SILENT:
.PHONY: all clean fclean re debug rebug _debug
