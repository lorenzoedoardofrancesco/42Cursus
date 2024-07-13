NAME		=	push_swap
CC			=	c++
CFLAGS		=	-Wall -Wextra -Werror -std=c++20
RM			=	rm -rf
SRCS		=	srcs/algorithm.cpp \
				srcs/main.cpp \
				srcs/operations.cpp \
				srcs/parsing.cpp \
				srcs/sort.cpp

HEADDIR		=	./includes/
OBJDIR		=	objs
DEPDIR		=	.deps
OBJS		=	$(SRCS:srcs/%.cpp=$(OBJDIR)/%.o)
DEPS		=	$(SRCS:srcs/%.cpp=$(DEPDIR)/%.d)

$(OBJDIR)/%.o:	srcs/%.cpp
			@mkdir -p $(OBJDIR) $(DEPDIR)
			$(CC) $(CFLAGS) -I$(HEADDIR) -MMD -MF $(DEPDIR)/$*.d -c $< -o $@

-include $(DEPS)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) -I$(HEADDIR) -o $(NAME) $(OBJS)

all:		$(NAME)

clean:
			$(RM) $(OBJDIR) $(DEPDIR)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all bonus clean fclean re
