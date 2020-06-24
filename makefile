INC_DIR := ./include
SRC_DIR := ./source
OBJ_DIR := ./object
LIB_DIR := ./lib

CC       := g++
CPPFLAGS := -I$(INC_DIR) -L$(LIB_DIR) -MMD -MP -DGLEW_STATIC -g
CXXFLAGS := -w -Wl,-subsystem,windows
LDLIBS = -lmingw32 -lSDL2main -lSDL2 -lglew32 -lglu32 -lopengl32

SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
DEPS    := $(wildcard $(OBJ_DIR)/*.d)

.PHONY: clean

Game: $(OBJECTS)
	$(CC) -L$(LIB_DIR) $(LDFLAGS) $^ $(LDLIBS) -o $@
	
Debug: $(OBJECTS)
	$(CC) -L$(LIB_DIR) $(LDFLAGS) -g $^ $(LDLIBS) -o $@

$(OBJECTS): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(OUTPUT_OPTION) $<

clean: ; $(RM) $(DEPS) $(OBJECTS)

include $(DEPS)

$(MAKEFILE_LIST): ;
%:: %,v
%:: RCS/%,v
%:: RCS/%
%:: s.%
%:: SCCS/s.%
