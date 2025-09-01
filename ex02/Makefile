NAME = PmergeMe
SRC =  main.cpp PmergeMe.cpp sortVec_utils.cpp sortDeq_utils.cpp
OBJ = ${SRC:.cpp=.o}
CC = c++
CXX = $(CC) $(CFLAGS)
CFLAGS = -Wall -Wextra -Werror -std=c++98 -fsanitize=address

all : ${NAME}

${NAME} : ${OBJ}
	${CC} ${CFLAGS} ${OBJ} -o ${NAME}

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY : all clean fclean re