SDL_CFLAGS=$(shell pkg-config --cflags sdl2 SDL2_image SDL2_net SDL2_ttf)
SDL_LIBS=$(shell pkg-config --libs sdl2 SDL2_image SDL2_net SDL2_ttf)
PROTOBUF_CFLAGS=$(shell pkg-config --cflags protobuf)
PROTOBUF_LIBS=$(shell pkg-config --libs protobuf)
BOOST_CFLAGS=-DBOOST_LOG_DYN_LINK -I/opt/local/include
BOOST_LIBS0=-lboost_system -lboost_thread -lboost_filesystem -lboost_log

ifeq ($(OS),Windows_NT)
    CFLAGS += -DWIN32
    ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
        CFLAGS += -DAMD64
    endif
    ifeq ($(PROCESSOR_ARCHITECTURE),x86)
        CFLAGS += -DIA32
    endif
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        CFLAGS += -DLINUX
		UNAME_P := $(shell uname -p)
		ifeq ($(UNAME_P),x86_64)
			CFLAGS += -DAMD64
		endif
		ifneq ($(filter %86,$(UNAME_P)),)
			CFLAGS += -DIA32
		endif
		ifneq ($(filter arm%,$(UNAME_P)),)
			CFLAGS += -DARM
		endif
    endif
    ifeq ($(UNAME_S),Darwin)
        CFLAGS += -DOSX
		UNAME_M := $(shell uname -m)
		ifeq ($(UNAME_M),x86_64)
			CFLAGS += -DAMD64
		endif
		ifneq ($(filter %86,$(UNAME_M)),)
			CFLAGS += -DIA32
		endif
		BOOST_LIBS=$(addsuffix -mt,$(BOOST_LIBS0))
    endif
endif
ifndef BOOST_LIBS
	BOOST_LIBS=$(BOOST_LIBS0)
endif

CFLAGS := -std=c++11 -O0 -ggdb $(BOOST_CFLAGS) $(SDL_CFLAGS) $(PROTOBUF_CFLAGS) $(OPT_CFLAGS)
CXXFLAGS = $(CFLAGS)
LDLIBS := -lm -lstdc++ $(BOOST_LIBS) $(SDL_LIBS) $(PROTOBUF_LIBS)

.PHONY: clean all

OBJS = main.o Logger.o Application.o Timer.o Window.o Surface.o Cursor.o Font.o Control.o PartModel.o PartView.o Event.o Scrollbar.o Scrollbar2.o Viewport.o DummyControl.o Button.o
TARGETS = main

all: $(TARGETS)

main: main.o Logger.o Application.o Timer.o Window.o Surface.o Cursor.o Font.o Control.o PartModel.o PartView.o Event.o Scrollbar.o Scrollbar2.o Viewport.o DummyControl.o Button.o
	$(CC) $^ $(LDLIBS) -o $@

-include $(OBJS:.o=.d)

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $*.cpp -o $*.o
	$(CXX) -MM $(CXXFLAGS) $*.cpp > $*.d
	@cp -f $*.d $*.d.tmp
	@sed -e 's/.*://' -e 's/\\$$//' < $*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> $*.d
	@rm -f $*.d.tmp

clean:
	@rm -vf $(OBJS) $(OBJS:.o=.d) $(TARGETS)
	@sh -c 'if ls *.o > /dev/null 2>&1; then echo "error: some *.o files have not been cleaned: $$(ls *.o)"; false; fi'

