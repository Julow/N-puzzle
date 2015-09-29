O_FILES :=	o/srcs/ACanvas.o o/srcs/ALayout.o o/srcs/AView.o \
			o/srcs/AbsoluteLayout.o o/srcs/Activity.o \
			o/srcs/Activity_RootViewHolder.o o/srcs/RelativeLayout.o \
			o/srcs/SliderView.o o/srcs/TextView.o o/srcs/VerticalLayout.o \
			o/srcs/VerticalLayout_ViewHolder.o o/srcs/XmlParser.o \
			o/srcs/XmlTokenizer.o o/srcs/ft/assert.o

LIBS_DEPEND := 

libs:
.PHONY: libs

o/srcs/ACanvas.o: srcs/ACanvas.cpp include/ACanvas.hpp include/libftui.h \
	| o/srcs/
o/srcs/ALayout.o: srcs/ALayout.cpp include/ALayout.hpp include/AView.hpp \
	include/libftui.h include/XmlParser.hpp include/XmlTokenizer.hpp \
	include/IViewHolder.hpp include/Vec.hpp | o/srcs/
o/srcs/AView.o: srcs/AView.cpp include/AView.hpp include/libftui.h \
	include/ALayout.hpp include/IViewHolder.hpp include/Vec.hpp \
	include/XmlParser.hpp include/XmlTokenizer.hpp include/VerticalLayout.hpp \
	| o/srcs/
o/srcs/AbsoluteLayout.o: srcs/AbsoluteLayout.cpp include/AbsoluteLayout.hpp \
	include/libftui.h | o/srcs/
o/srcs/Activity.o: srcs/Activity.cpp include/Activity.hpp \
	include/IViewHolder.hpp include/Vec.hpp include/libftui.h \
	include/AView.hpp include/XmlParser.hpp include/XmlTokenizer.hpp | o/srcs/
o/srcs/Activity_RootViewHolder.o: srcs/Activity_RootViewHolder.cpp \
	include/Activity.hpp include/IViewHolder.hpp include/Vec.hpp \
	include/libftui.h include/AView.hpp include/XmlParser.hpp \
	include/XmlTokenizer.hpp | o/srcs/
o/srcs/RelativeLayout.o: srcs/RelativeLayout.cpp include/RelativeLayout.hpp \
	include/libftui.h | o/srcs/
o/srcs/SliderView.o: srcs/SliderView.cpp include/SliderView.hpp \
	include/libftui.h | o/srcs/
o/srcs/TextView.o: srcs/TextView.cpp include/TextView.hpp include/libftui.h \
	| o/srcs/
o/srcs/VerticalLayout.o: srcs/VerticalLayout.cpp include/ALayout.hpp \
	include/AView.hpp include/IViewHolder.hpp include/Vec.hpp \
	include/VerticalLayout.hpp include/libftui.h include/XmlParser.hpp \
	include/XmlTokenizer.hpp | o/srcs/
o/srcs/VerticalLayout_ViewHolder.o: srcs/VerticalLayout_ViewHolder.cpp \
	include/ALayout.hpp include/AView.hpp include/IViewHolder.hpp \
	include/Vec.hpp include/VerticalLayout.hpp include/libftui.h \
	include/XmlParser.hpp include/XmlTokenizer.hpp include/Activity.hpp \
	| o/srcs/
o/srcs/XmlParser.o: srcs/XmlParser.cpp include/XmlParser.hpp \
	include/XmlTokenizer.hpp include/libftui.h include/ft/utils.hpp | o/srcs/
o/srcs/XmlTokenizer.o: srcs/XmlTokenizer.cpp include/XmlTokenizer.hpp \
	include/libftui.h include/ft/utils.hpp | o/srcs/
o/srcs/ft/assert.o: srcs/ft/assert.cpp include/ft/assert.hpp | o/srcs/ft/
