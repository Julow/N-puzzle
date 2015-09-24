#

# Executable name
NAME := npuzzle

# Project directories
DIRS := srcs include

# Git submodule to init
MODULES := 
# Makefiles to call
LIBS := libftui

# Compilation and linking flags
FLAGS := -std=c++14 -Wall -Wextra -O2
# Compilation flags
HEADS := $(addprefix -I,$(DIRS))
# Linking flags
LINKS :=

# Objects directory
O_DIR := o

# Depend file name
DEPEND := depend.mk

# tmp
MODULE_RULES := $(addsuffix /.git,$(MODULES))

# Default rule (need to be before any include)
all: $(MODULE_RULES) libs $(NAME)

# Include $(O_FILES) and dependencies
-include $(DEPEND)

# Linking
$(NAME): $(LIBS_DEPEND) $(O_FILES)
	clang $(FLAGS) -o $@ $(O_FILES) $(LINKS) && printf '\033[32m$@\033[0m\n'

# Compiling
$(O_DIR)/%.o:
	clang $(FLAGS) $(HEADS) -c $< -o $@ && printf '\033[32m$<\033[0m\n'

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
	rm -f $(O_FILES)

# Clean everything
fclean: clean
	rm -f $(NAME)

# Clean and make
re: fclean all

# Update $(DEPEND) file
$(DEPEND): Makefile
	makemake || printf "\033[31mCannot remake $(DEPEND)\033[0m\n"

# Set debug flags
_debug:
	$(eval FLAGS := $(DEBUG_FLAGS))

.SILENT:
.PHONY: all $(LIBS) clean fclean re debug rebug _debug
