##
## EPITECH PROJECT, 2021
## MyGKrellm
## File description:
## Makefile
##

NAME	=	mygkrellm

CC	=	g++

RM	=	rm -f

SRCS	=	src/main.cpp \
			src/modules/ModuleUser.cpp \
			src/modules/ModuleSystem.cpp \
			src/ncurses/DisplayNcurses.cpp \
			src/ncurses/ImplementGraphs.cpp \
			src/sfml/graph.cpp \
			src/sfml/module.cpp \
			src/sfml/moduleText.cpp\
			src/sfml/StartSFML.cpp \

OBJS	=	$(SRCS:.cpp=.o)

IDIR	=	./include/

CFLAGS	=	-Wall -Wextra -Werror -I$(IDIR)

LDFLAGS	=	-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lncurses

all:	$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
