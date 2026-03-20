NAME = expander.a

CC = cc
AR = ar rcs
CFLAGS = -Wall -Werror -Wextra -g

SRCS = src/expand_pipeline.c \
		src/expand_redir.c \
		src/expand_segments.c \
		src/expander_utils.c \
		src/expand_token.c \
		src/expand_heredoc.c

OBJS = $(SRCS:.c=.o)

INCLUDES = -I include -I libft
LIBFT = ../libft/libft.a

#-----------------------------------------------------------
# Principal
#-----------------------------------------------------------
all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C ../libft > /dev/null
	@cp $(LIBFT) $(NAME)
	@$(AR) $(NAME) $(OBJS)
	@echo "📦 Librería $(NAME) creada correctamente."

#-----------------------------------------------------------
# Compilar archivos fuente
#-----------------------------------------------------------
%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "🔧 Compilado: $<"

#-----------------------------------------------------------
# Limpiar archivos
#-----------------------------------------------------------
clean:
	@rm -f $(OBJS)
	@$(MAKE) -C ../libft clean > /dev/null
	@echo "🧹 Archivos objeto eliminados."

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C ../libft fclean > /dev/null
	@echo "🧼 Todo limpio."

re: fclean all

.PHONY: all clean fclean re
