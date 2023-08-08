CC = gcc
FLAGS = -L ./minilibx_mms_20210621 -lmlx -framework OpenGL -framework Appkit -lz
CFLAGS = -Wall -Wextra -Werror
SRCS = fdf.c get_next_line.c get_next_line_utils.c draw_info.c bresenham_line.c \
	interpolate_3d.c mini_libft1.c mini_libft2.c ft_split.c key_event.c draw.c \
	parse_map1.c parse_map2.c
NAME = FDF
OBJECTS = $(SRCS:.c=.o)
OBJECTS2 = $(SRCS2:.c=.o)
INC = -I./
RMF = rm -f

all : $(NAME)

$(NAME) : $(OBJECTS)
	$(CC) $(CFLAGS) $(FLAGS) $(OBJECTS) -o $(NAME)

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