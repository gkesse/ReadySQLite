GSRC = ../code/GProject/src
GBIN = bin
GBUILD = build
GTARGET = $(GBIN)/gp_sqlite

GINCS = \
    -I$(GSRC)/include \
    -I/usr/include/opencv4 \
    
GLIBS = \
    -lsqlite3 \
    
GOBJS = \
    $(patsubst $(GSRC)/%.cpp, $(GBUILD)/%.o, $(wildcard $(GSRC)/*.cpp)) \
    $(patsubst $(GSRC)/manager/%.cpp, $(GBUILD)/%.o, $(wildcard $(GSRC)/manager/*.cpp)) \

GCFLAGS = \
    -std=gnu++11 \
    
all: compile run

compile: $(GOBJS)
	@if ! [ -d $(GBIN) ] ; then mkdir -p $(GBIN) ; fi
	g++ -o $(GTARGET) $(GOBJS) $(GLIBS) 
$(GBUILD)/%.o: $(GSRC)/%.cpp
	@if ! [ -d $(GBUILD) ] ; then mkdir -p $(GBUILD) ; fi
	g++ $(GCFLAGS) -c $< -o $@ $(GINCS)
$(GBUILD)/%.o: $(GSRC)/manager/%.cpp
	@if ! [ -d $(GBUILD) ] ; then mkdir -p $(GBUILD) ; fi
	g++ $(GCFLAGS) -c $< -o $@ $(GINCS)
run:
	@$(GTARGET) $(args)
clean: 
	rm -f $(GBUILD)/* $(GBIN)/*
