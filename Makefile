CC = gcc
FLAGS = -L ./minilibx_mms_20210621 -lmlx -framework OpenGL -framework Appkit -lz
CFLAGS = -Wall -Wextra -Werror
SRCS = main.c get_next_line.c get_next_line_utils.c parse_map.c 
SRCS = main.c get_next_line.c get_next_line_utils.c parse_map.c 
NAME = FDF
OBJECTS = $(SRCS:.c=.o)
OBJECTS2 = $(SRCS2:.c=.o)
ARRCS = ar rcus
INC = -I./
RMF = rm -f

all : $(NAME)

$(NAME) : $(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) libft.a -o $(NAME)

%.o : %.c
	$(CC) -c $(INC) $<

clean :
	$(RMF) $(OBJECTS) $(OBJECTS2) bonus

fclean : clean
	$(RMF) $(NAME)

re :
	make fclean
	make all

.PHONY : all clean fclean re