NAME			= philo

INC_DIR			= -I./includes
################################# COMMANDS #####################################
RM				= rm -f
CC				= gcc
CFLAGS			= -Wall -Werror -Wextra -MMD -MP
################################ FILENAMES #####################################
SRCNAME			= \
				main \
				ft_asciitools2 \
				ft_atoi \
				error_handler \
				parser \
				allocator \
				initializer \
				msg_queue \
				msg_printer \
				philosopher \
				philo_strategy_0 \
				philo_strategy_1

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

.PHONY: all bonus clean fclean re
