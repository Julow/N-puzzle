LIBLUA_DIR		:= ?path?/lua-5.3.1
LIBLUA_PLATFORM	:= posix
LIBLUA_ARCHIVE	:= $(LIBLUA_DIR).tar.gz
LIBLUA_LIB		:= $(LIBLUA_DIR)/src/liblua.a
LIBLUA			:= ?path?/liblua.a

_PLATFORM		:= $(shell uname)

ifeq ($(_PLATFORM),Linux)
  LIBLUA_PLATFORM = linux
else
  ifeq ($(_PLATFORM),Darwin)
    LIBLUA_PLATFORM = macosx
  endif
endif

liblua: $(LIBLUA_LIB)
.PHONY: liblua

$(LIBLUA_LIB):
	echo Extract lua
	tar -x -C ?path? -f $(LIBLUA_ARCHIVE)
	echo "Make lua ($(LIBLUA_PLATFORM))"
	make -C $(LIBLUA_DIR) $(LIBLUA_PLATFORM)
	echo Done
