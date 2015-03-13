SDL_CFLAGS=$(shell pkg-config --cflags sdl2 SDL2_image SDL2_net SDL2_ttf)
SDL_LIBS=$(shell pkg-config --libs sdl2 SDL2_image SDL2_net SDL2_ttf)
PROTOBUF_CFLAGS=$(shell pkg-config --cflags protobuf)
PROTOBUF_LIBS=$(shell pkg-config --libs protobuf)

CFLAGS := -std=c++11 -O0 -ggdb $(SDL_CFLAGS) $(PROTOBUF_CFLAGS) $(OPT_CFLAGS)
LDLIBS := -lm -lstdc++ $(SDL_LIBS) $(PROTOBUF_LIBS)

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
        LDLIBS += -lboost_system -lboost_thread -lboost_filesystem -lboost_log -lboost_log_setup
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
        LDLIBS += -lboost_system-mt -lboost_thread-mt -lboost_filesystem-mt -lboost_log-mt -lboost_log_setup-mt
    endif
endif

CXXFLAGS = $(CFLAGS)

.PHONY: clean all

OBJS = main.o Logger.o System.o Window.o Surface.o Font.o Control.o PartModel.o PartView.o Event.o Scrollbar.o Viewport.o DummyControl.o Button.o
TARGETS = main

all: $(TARGETS)

main: main.o Logger.o System.o Window.o Surface.o Font.o Control.o PartModel.o PartView.o Event.o Scrollbar.o Viewport.o DummyControl.o Button.o
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

