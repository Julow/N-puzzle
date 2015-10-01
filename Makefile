#

# Executable name
NAME := npuzzle

# Project directories
DIRS := srcs include libftui/include

# Git submodule to init
MODULES := 
# Makefiles to call
LIBS := libftui(BINDINGS=glfw make -C ?name?)

# Compilation and linking flags
FLAGS := -std=c++14 -Wall -Wextra -O2
# Same but used in debug mode
DEBUG_FLAGS := -Wall -Wextra -g
# Compilation flags
HEADS := $(addprefix -I,$(DIRS))
# Linking flags
ifeq ($(shell uname),Darwin)
	FLAGS += -DMAC_OS_MODE=1
	DEBUG_FLAGS += -DMAC_OS_MODE=1
	LINKS := -lglfw3 -framework OpenGL
else
	LINKS := -lglfw -lGL -lGLEW
endif
LINKS += -Llibftui -lftui

# Jobs
JOBS := 4

# Column output
COLUMN_OUTPUT := 1

ifeq ($(COLUMN_OUTPUT),0)
	PRINT_OK = printf '\033[32m$<\033[0m\n'
	PRINT_LINK = printf '\033[32m$@\033[0m\n'
else
	PRINT_OK = echo $(patsubst $(firstword $(DIRS))/%,%,$<) >> $(PRINT_FILE)
	PRINT_LINK = printf '\n\033[32m$@\033[0m\n'
endif

# Objects directory
O_DIR := o

# Depend file name
DEPEND := depend.mk

# tmp
MODULE_RULES := $(addsuffix /.git,$(MODULES))
PRINT_FILE := .tmp_print
SHELL := /bin/bash

# Default rule (need to be before any include)
all: $(MODULE_RULES) libs
ifeq ($(COLUMN_OUTPUT),0)
	make -j$(JOBS) $(NAME)
else
	MAX_LEN=1;															\
	for o in $(patsubst $(O_DIR)/$(firstword $(DIRS))/%,%,$(O_FILES));	\
	do																	\
		if [[ $${#o} -gt $$MAX_LEN ]];									\
		then															\
			MAX_LEN=$${#o};												\
		fi;																\
	done;																\
	PER_LINE=$$((`tput cols` / $$(($$MAX_LEN + 2))));					\
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
		printf '\033[32m%-*s\033[0m  ' $$MAX_LEN "$$l";					\
	done &																\
	make -j$(JOBS) $(NAME);												\
	STATUS=$$?															\
	kill -9 `jobs -p`;													\
	rm -f $(PRINT_FILE)													\
	exit $$STATUS
endif

# Include $(O_FILES) and dependencies
-include $(DEPEND)

# Linking
$(NAME): $(LIBS_DEPEND) $(O_FILES)
	clang++ $(FLAGS) -o $@ $(O_FILES) $(LINKS) && $(PRINT_LINK)

# Compiling
$(O_DIR)/%.o:
	clang++ $(FLAGS) $(HEADS) -c $< -o $@ && $(PRINT_OK)

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

# Clean everything
fclean: clean
	rm -f $(NAME)

# Clean and make
re: fclean all

# Set debug flags
_debug:
	$(eval FLAGS := $(DEBUG_FLAGS))

.SILENT:
.PHONY: all clean fclean re debug rebug _debug
