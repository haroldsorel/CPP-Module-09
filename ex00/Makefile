NAME = btc
SRC =  main.cpp BitcoinExchange.cpp input_parsing.cpp
OBJ = ${SRC:.cpp=.o}
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98
CXX = $(CC) $(CFLAGS)

all : ${NAME}

${NAME} : ${OBJ}
	${CC} ${CFLAGS} ${OBJ} -o ${NAME}

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY : all clean fclean re
