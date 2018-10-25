CXX = g++
CXXFLAGS = -std=c++1z -Wall -Wextra -Werror  -Ofast
CXXXFLAGS = -std=c++1z -Wall -Wextra -Werror -Ofast
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
