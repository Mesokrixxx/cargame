NAME = cargame

CXX = clang++
CXXFLAGS = -Wall -Wextra -std=c++23 -Isrc -g3 -fno-rtti -fno-exceptions
LDFLAGS = -g3

LIBS = sdl3 glew

SRC = src/main.cpp
SRC += src/container/string.cpp
SRC += src/memory/allocator.cpp src/memory/mallocator.cpp
SRC += src/util/error.cpp src/util/assert.cpp src/util/format.cpp

CXXFLAGS += $(shell pkg-config -cflags $(LIBS))
LDFLAGS += $(shell pkg-config -libs $(LIBS))
OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(OBJ) $(CXXFLAGS) -o $(NAME) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
