CC = gcc
CXX = g++

COMPILE_FLAGS = -Wall -ggdb -O3
LINK_FLAGS = -lglfw3 -lopengl32 -lglu32 -lgdi32

projectpath = D:\UnityProject\LearnOpenGL\Opengl
glfw = $(projectpath)/glfw-3.3.6.bin.WIN64
glfw_inc = $(glfw)/include
glfw_lib = $(glfw)/lib-mingw-w64

glad = $(projectpath)/glad
glad_inc = $(glad)/include
glad_src = $(glad)/src/glad.c

INCLUDES = -I$(glfw_inc) -I$(glad_inc) -I$(projectpath)/Include
LIBRARIES = -L$(glfw_lib)

cpp_files = main.cpp
objects = $(cpp_files:.cpp=.o)
headers = $(projectpath)/Include/MyWindow.h
abc: echo "sdfsd"
all: main.exe


main.exe: $(objects) glad.o
	$(CXX) $(LIBRARIES) -o main.exe $(objects) glad.o $(LINK_FLAGS)

$(objects): %.o: %.cpp $(headers) makefile
	$(CXX) $(COMPILE_FLAGS) $(INCLUDES) -c -o $@ $<
	
#glad.c is in glad/src, so we need full path
glad.o: $(glad_src)
	$(CC) $(COMPILE_FLAGS) $(INCLUDES) -c -o glad.o $(glad_src)
		
.PHONY : clean
clean:
	del *.o main.exe -rf
