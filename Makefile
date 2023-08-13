CC = gcc
FLAG = -L ./minilibx_mms_20210621 -lmlx -framework OpenGL -framework Appkit -lz
WFLAG = -Wall -Wextra -Werror
RMF = rm -f
SRC_NAME = fdf get_next_line get_next_line_utils \
	draw_info bresenham_line interpolate_3d \
	mini_libft1 mini_libft2 ft_split \
	key_event draw parse_map1 parse_map2

MAN_DIR = ./man_src/
MAN_SRC = $(addprefix $(MAN_DIR), $(addsuffix .c, $(SRC_NAME)))
MAN_OBJ = $(addprefix $(MAN_DIR), $(addsuffix .o, $(SRC_NAME)))
MAN_NAME = ./fdf

BON_DIR = ./bon_src/
BON_SRC = $(addprefix $(BON_DIR), $(addsuffix _bonus.c, $(SRC_NAME)))
BON_OBJ = $(addprefix $(BON_DIR), $(addsuffix _bonus.o, $(SRC_NAME)))
BON_NAME = ./fdf_bonus

all : $(MAN_NAME)

$(MAN_NAME) : $(MAN_OBJ)
	$(CC) $(WFLAG) $(FLAG) $^ -o $@

bonus : $(BON_OBJ)
	$(CC) $(WFLAG) $(FLAG) $^ -o $(BON_NAME)
	@touch bonus

%.o : %.c
	$(CC) $(WFLAG) -I $(dir $<) -c $< -o $@

clean :
	$(RMF) $(MAN_OBJ) $(BON_OBJ) bonus

fclean : clean
	$(RMF) $(MAN_NAME) $(BON_NAME)

re :
	make fclean
	make all

.PHONY : all clean fclean re