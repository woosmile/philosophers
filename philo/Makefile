NAME = philo
CC = cc
CFLAGS = -Werror -Wall -Wextra

MAKE = make
MFLAGS = -C

RM = rm
RMFLAGS = -rf

HEADER = \
philo.h

INCLUDES = -I.

MANDATORY_SRCS = \
philo_utils.c \
philo.c

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
