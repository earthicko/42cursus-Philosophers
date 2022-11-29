NAME			= philo

INC_DIR			= -I./includes
################################# COMMANDS #####################################
RM				= rm -f
CC				= gcc
CFLAGS			= -Wall -Werror -Wextra -MMD -MP
################################ FILENAMES #####################################
SRCNAME			= \
				main \
				ft_asciitools \
				ft_atoi \
				timetools \
				msg_queue \
				parser \
				t_info_allocator \
				t_info_initializer \
				philo_actions \
				philosopher

SRC				= $(addprefix src/, $(addsuffix .c, $(SRCNAME)))
OBJ				= $(addprefix src/, $(addsuffix .o, $(SRCNAME)))
DEP				= $(addprefix src/, $(addsuffix .d, $(SRCNAME)))
################################# TARGETS ######################################
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INC_DIR) $(OBJ) -o $@ -lpthread

-include $(DEP)

%.o: %.c
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

clean:
	$(RM) $(OBJ) $(DEP)

fclean: clean
	$(RM) $(NAME)

re:
	@make fclean
	@make all

.PHONY: all clean fclean re
