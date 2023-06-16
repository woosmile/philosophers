NAME = philo

CC = cc
CFLAGS = -Werror -Wall -Wextra -fsanitize=thread

MAKE = make
MFLAGS = -C

RM = rm
RMFLAGS = -rf

HEADER = \
philo.h

INCLUDES = -I.

MANDATORY_SRCS = \
philo.c \
philo_utils.c \
philo_atoi.c \
philo_split.c \
philo_share_init.c \
philo_share_init_utils.c \
philo_init.c \
philo_observer_init.c

MANDATORY_OBJS = $(MANDATORY_SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(MANDATORY_OBJS) $(HEADER)
	$(CC) $(CFLAGS) -o $@ $(MANDATORY_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

clean :
	$(RM) $(RMFLAGS) $(MANDATORY_OBJS)

fclean :
	$(MAKE) clean
	$(RM) $(RMFLAGS) $(NAME)

re :
	$(MAKE) fclean
	$(MAKE) all

.PHONY : all clean fclean re
