export DISPLAY=:0

# Configuration variables
CC = g++
CFLAGS = `sdl2-config --cflags` -Wall -g -std=c++17
LFLAGS = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -lm

# This slightly modified INCLUDE lets you use #include<SDL.h> instead of #include<SDL/SDL.h>, etc.
INCLUDE = -I ./include -I `sdl2-config --prefix`/include

# This function fills the role of **, the globstar in GNUMake, which is not inherently supported.
# Credit to user larskholte on https://stackoverflow.com/questions/2483182/recursive-wildcards-in-gnu-make
GLOB = $(foreach d, $(wildcard $(1:=/*)), $(call rwildcard, $d, $2) $(filter $(subst *,%,$2),$d))

# This modified version will not only get all the .cpp files, but get the .cpp files
# out of any directories in src/ as well
SRCS = $(call GLOB, src, *.cpp) 

# Generate object Files
OBJS = $(patsubst %.cpp, bin/%.o, $(SRCS))

# Executable Name
TARGET = prog.out

# Builds Object Files
bin/%.o: %.cpp
	@mkdir -p $(dir $@) 
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

# Builds Final Executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) -o $@ $(LFLAGS)

# Runs the executable created from the build
run: $(TARGET)
	./$(TARGET) 

# Removes the executable from the directory
clean: 
	rm -rf bin
	rm -rf prog.out

# Tars the entire directory
tar:
	tar -czvf assn4_nejman.tar.gz * 