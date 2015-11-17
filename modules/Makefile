
#

# Executable name
NAME			:= libmodules.a

# Git submodule to init
SUBMODULES		:=

# Base flags
BASE_FLAGS		= -Wall -Wextra
INCLUDE_FLAGS	=

# Compilation flags (per language)
C_FLAGS			= $(INCLUDE_FLAGS) $(BASE_FLAGS)
CPP_FLAGS		= $(INCLUDE_FLAGS) $(BASE_FLAGS) -std=c++14

LINK_FLAGS		= $(BASE_FLAGS)

DEBUG_MODE		?= 0
ifeq ($(DEBUG_MODE),1)
	# Extra flags used in debug mode
	BASE_FLAGS	+= -g
else
	# Extra flags used when not in debug mode
	BASE_FLAGS	+= -O2
endif
export DEBUG_MODE

# Objects directory
O_DIR			:= _objs

# Jobs
JOBS			:= 8

# Column output
COLUMN_OUTPUT	:= 0

ifeq ($(COLUMN_OUTPUT),0)
	PRINT_DBUG	= printf '\033[33m$@\033[0m\n'
	PRINT_OK	= printf '\033[32m$<\033[0m\n'
	PRINT_LINK	= printf '\033[32m$@\033[0m\n'
else
	PRINT_OK	= echo $< >> $(PRINT_FILE)
	PRINT_LINK	= printf '\n\033[32m$@\033[0m\n'
endif

# Depend file name
DEPEND			:= depend.mk

# tmp
SUBMODULE_RULES	:= $(addsuffix /.git,$(SUBMODULES))
PRINT_FILE		:= .tmp_print
SHELL			:= /bin/bash

# Default rule (need to be before any include)
all: $(SUBMODULE_RULES) libs_rules
ifeq ($(COLUMN_OUTPUT),0)
	make -j$(JOBS) $(NAME)
else
	MAX_LEN=0;														\
	for f in $(patsubst $(O_DIR)/%,%,$(O_FILES)); do				\
		if [[ $${#f} -gt $$MAX_LEN ]]; then MAX_LEN=$${#f}; fi;		\
	done;															\
	PER_LINE=$$((`tput cols` / $$(($$MAX_LEN + 2))));				\
	CURR=0;															\
	touch $(PRINT_FILE);											\
	tail -n0 -f $(PRINT_FILE) | while read l;						\
	do																\
		if [[ $$CURR -ge $$PER_LINE ]]; then CURR=0; echo; fi;		\
		CURR=$$(($$CURR + 1));										\
		printf "\033[32m%-*s\033[0m  " "$$MAX_LEN" "$$l";			\
	done &															\
	make -j$(JOBS) $(NAME);											\
	STATUS=$$?;														\
	kill -9 `jobs -p`;												\
	rm -f $(PRINT_FILE);											\
	exit $$STATUS
endif

# Include $(O_FILES) and dependencies
include $(DEPEND)

libs_rules: $(LIBS_RULES)

# Linking
$(NAME): $(LINK_DEPENDS) $(O_FILES)
	ar rcs $@ $(O_FILES) && $(PRINT_LINK)

# Compiling
$(O_DIR)/%.o: %.c
	clang $(C_FLAGS) -c $< -o $@ && $(PRINT_OK)
$(O_DIR)/%.o: %.cpp
	clang++ $(CPP_FLAGS) -c $< -o $@ && $(PRINT_OK)

# Init submodules
$(SUBMODULE_RULES):
	git submodule init $(@:.git=)
	git submodule update $(@:.git=)

# Create include links
$(PUBLIC_LINKS):
	ln -s $(abspath $<) $@ && $(PRINT_DBUG)
# Create obj directories
$(O_DIR)/%/:
	mkdir -p $@ && $(PRINT_DBUG)

# Set debug mode and make
debug: _debug all

# Clean, set debug mode and make
rebug: fclean debug

# Clean obj files
clean:
	rm -f $(PRINT_FILE)
	rm -f $(O_FILES) $(PUBLIC_LINKS)

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
