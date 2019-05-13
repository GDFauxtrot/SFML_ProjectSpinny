CXX=g++
NAME=spinny
# Add folders to makefile by adding a space between them in INC
INC=SceneGraph
INCPARAMS=$(foreach d,$(INC),-I ./$d *.cpp $d/*.cpp)
LDFLAGS=
LDLIBS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio


main:
	$(CXX) $(LDFLAGS) -o $(NAME) $(INCPARAMS) $(LDLIBS)
 
