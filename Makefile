CC = g++

RMV = rm -f src/*.o

DLIBS = $(DIR_PREFIX)/lib/
GLFLAGS = -lpthread -lGLU -lglut -lGL -lGLEW -lX11 -lXrandr -lXi -ldl
CFLAGS = $(GLFLAGS) -I$(GL_INCLUDE_DIR) -Wall -O0

EXEC_NAME = DoodleJumpGL

.PHONY : all clean # Target that arent a file

all : $(EXEC_NAME)

SRC = $(wildcard src/*.cpp) # WATCH OUT FOR THIS LINE!!!!!!! IT'S UNRECOGNIZED BY MAKE, SO BE SURE IT IS CORRECT!!!
OBJ = $(SRC:.cpp=.o) # Considera i file .cpp ma che che hanno come suffisso .o

$(EXEC_NAME) : $(OBJ)
	@echo "** Building main executable, aka $(EXEC_NAME) ..."
	$(CC) -L$(DLIBS) -o $@ $(OBJ) $(CFLAGS)

%.o: %.cpp
	@echo "** Building obj files..."
	$(CC) -c $< -o $@

clean :
	@echo "** Removing object files..."
	$(RMV)