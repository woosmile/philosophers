NAME = philo_bonus

CC = cc

#CFLAGS = -Werror -Wall -Wextra -fsanitize=thread -g
CFLAGS = -Werror -Wall -Wextra

MAKE = make
MFLAGS = -C

RM = rm
RMFLAGS = -rf

HEADER = \
philo_bonus.h

INCLUDES = -I.

BONUS_SRCS = \
philo_atoi_bonus.c \
philo_bonus.c \
philo_share_init_bonus.c \
philo_share_init_utils_bonus.c \
philo_split_bonus.c \
philo_utils_bonus.c \
philo_init_bonus.c \
philo_behavior_bonus.c \
philo_behavior_utils_bonus.c

BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(BONUS_OBJS) $(HEADER)
	$(CC) $(CFLAGS) -o $@ $(BONUS_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

clean :
	$(RM) $(RMFLAGS) $(BONUS_OBJS)

fclean :
	$(MAKE) clean
	$(RM) $(RMFLAGS) $(NAME)

re :
	$(MAKE) fclean
	$(MAKE) all

.PHONY : all clean fclean re
