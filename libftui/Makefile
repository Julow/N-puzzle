#

# Executable name
NAME := libftui.a

# Project directories
DIRS := srcs include

# Bindings
BINDINGS ?=
BINDINGS_DIR := bindings

# Git submodule to init
MODULES := 
# Makefiles to call
LIBS :=

# Compilation and linking flags
FLAGS := -std=c++14 -Wall -Wextra -O2
# Same but used in debug mode
DEBUG_FLAGS := -Wall -Wextra -g
# Compilation flags
HEADS := $(addprefix -I,$(DIRS))
# Linking flags
LINKS :=

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
all: $(MODULE_RULES) libs bindings
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
$(NAME): $(LIBS_DEPEND) $(O_FILES) \
	$(addprefix $(BINDINGS_DIR)/,\
		$(join $(BINDINGS),$(BINDINGS:%=/libftui-%.a)))
	BINDINGS_FILES="";													\
	for b in $(BINDINGS);												\
	do																	\
		EXTRACT_DIR="$(O_DIR)/$$b";										\
		ARCH="`pwd`/$(BINDINGS_DIR)/$$b/libftui-$$b.a";					\
		for f in `ar t $$ARCH | grep '\.o$$'`;							\
		do																\
			BINDINGS_FILES="$$BINDINGS_FILES $$EXTRACT_DIR/$$f";		\
		done || exit 1;													\
		mkdir -p $$EXTRACT_DIR;											\
		(cd $$EXTRACT_DIR && ar x $$ARCH);								\
	done;																\
	ar rcs $@ $(O_FILES) $$BINDINGS_FILES && $(PRINT_LINK)

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

# Bindings
bindings:
	for b in $(BINDINGS);												\
	do																	\
		make -C $(BINDINGS_DIR)/$$b;									\
	done

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
.PHONY: all $(LIBS) clean fclean re debug rebug _debug bindings
