O_FILES :=	o/srcs/ACanvas.o o/srcs/ALayout.o o/srcs/AView.o \
			o/srcs/AbsoluteLayout.o o/srcs/Activity.o o/srcs/RelativeLayout.o \
			o/srcs/SliderView.o o/srcs/TextView.o o/srcs/VerticalLayout.o \
			o/srcs/ViewFactory.o o/srcs/XmlParser.o

LIBS_DEPEND := 

libs:
.PHONY: libs

o/srcs/ACanvas.o: srcs/ACanvas.cpp include/ACanvas.hpp | o/srcs/
o/srcs/ALayout.o: srcs/ALayout.cpp include/ALayout.hpp | o/srcs/
o/srcs/AView.o: srcs/AView.cpp include/AView.hpp include/IViewHolder.hpp \
	| o/srcs/
o/srcs/AbsoluteLayout.o: srcs/AbsoluteLayout.cpp include/AbsoluteLayout.hpp \
	| o/srcs/
o/srcs/Activity.o: srcs/Activity.cpp include/Activity.hpp include/ACanvas.hpp \
	| o/srcs/
o/srcs/RelativeLayout.o: srcs/RelativeLayout.cpp include/RelativeLayout.hpp \
	| o/srcs/
o/srcs/SliderView.o: srcs/SliderView.cpp include/SliderView.hpp | o/srcs/
o/srcs/TextView.o: srcs/TextView.cpp include/TextView.hpp | o/srcs/
o/srcs/VerticalLayout.o: srcs/VerticalLayout.cpp include/VerticalLayout.hpp \
	| o/srcs/
o/srcs/ViewFactory.o: srcs/ViewFactory.cpp include/ViewFactory.hpp | o/srcs/
o/srcs/XmlParser.o: srcs/XmlParser.cpp include/XmlParser.hpp | o/srcs/
