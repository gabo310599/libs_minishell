NAME = executor.a

CC = cc
AR = ar rcs
CFLAGS = -Wall -Wextra -Werror -g

#-----------------------------------------------------------
# Archivos fuente
#-----------------------------------------------------------
SRCS =	src/aply_redirections.c \
		src/executor.c \
		src/helpers.c \
		src/execute_pipeline.c \
		src/execute_pipeline_utils.c \
		src/execute_pipeline_utils2.c \
		src/builtins/builtin.c \
		src/builtins/builtin_cd.c \
		src/builtins/builtin_echo.c \
		src/builtins/builtin_env.c \
		src/builtins/builtin_exit.c \
		src/builtins/builtin_export.c \
		src/builtins/builtin_pwd.c \
		src/builtins/builtin_unset.c \
		src/executor_utils.c

OBJS = $(SRCS:.c=.o)

#-----------------------------------------------------------
# Includes y dependencias
#-----------------------------------------------------------
INCLUDES = -I includes -I ../libft
LIBFT = ../libft/libft.a

#-----------------------------------------------------------
# Regla principal
#-----------------------------------------------------------
all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C ../libft > /dev/null
	@cp $(LIBFT) $(NAME)
	@$(AR) $(NAME) $(OBJS)
	@echo "📦 Librería $(NAME) creada correctamente."

#-----------------------------------------------------------
# Compilación
#-----------------------------------------------------------
%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "🔧 Compilado: $<"

#-----------------------------------------------------------
# Limpieza
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
