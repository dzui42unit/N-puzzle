CXX = g++
CXXFLAGS = -std=c++14 -O3
CXXXFLAGS = -std=c++14 -O3
NAME = N-Puzzle

SRC = 	App/main.cpp \
\
 		Tools/Field.cpp \
		Tools/Parser.cpp \
\
		App/AStarNode.cpp \
		App/Heuristic.cpp \

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(CXXXFLAGS)

%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
