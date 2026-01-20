# =========================================================
# Nombre del binario final
# =========================================================
NAME = minishell

# =========================================================
# Compilador y flags
# =========================================================
CC = cc
CFLAGS = -Wall -Werror -Wextra -g

# =========================================================
# Módulos
# =========================================================
LIBFT_DIR     = libft
ENV_DIR       = env
LEXER_DIR     = lexer
PARSER_DIR    = parser
EXPANDER_DIR  = expander
EXECUTOR_DIR  = executor

LIBFT     = $(LIBFT_DIR)/libft.a
ENV       = $(ENV_DIR)/env.a
LEXER     = $(LEXER_DIR)/lexer.a
PARSER    = $(PARSER_DIR)/parser.a
EXPANDER  = $(EXPANDER_DIR)/expander.a
EXECUTOR  = $(EXECUTOR_DIR)/executor.a

LIBS = \
	$(EXECUTOR) \
	$(EXPANDER) \
	$(PARSER) \
	$(LEXER) \
	$(ENV) \
	$(LIBFT)

# =========================================================
# Includes
# =========================================================
INCLUDES = \
	-I . \
	-I $(LIBFT_DIR) \
	-I $(ENV_DIR)/includes \
	-I $(LEXER_DIR)/includes \
	-I $(PARSER_DIR)/includes \
	-I $(EXPANDER_DIR)/includes \
	-I $(EXECUTOR_DIR)/includes

# =========================================================
# Sources del programa principal
# =========================================================
SRCS = \
	src/main.c \
	src/signals/signals.c \
	src/cleanup.c \
	src/signals/signals_exec.c

OBJS = $(SRCS:.c=.o)

# =========================================================
# Reglas
# =========================================================
all: $(NAME)

# ---------------------------------------------------------
# Binario final
# ---------------------------------------------------------
$(NAME): $(LIBS) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -lreadline -o $(NAME)
	@echo "🚀 Minishell compilado correctamente."

# ---------------------------------------------------------
# Compilar módulos
# ---------------------------------------------------------
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(ENV):
	@$(MAKE) -C $(ENV_DIR)

$(LEXER):
	@$(MAKE) -C $(LEXER_DIR)

$(PARSER):
	@$(MAKE) -C $(PARSER_DIR)

$(EXPANDER):
	@$(MAKE) -C $(EXPANDER_DIR)

$(EXECUTOR):
	@$(MAKE) -C $(EXECUTOR_DIR)

# ---------------------------------------------------------
# Compilar objetos
# ---------------------------------------------------------
%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "🔧 Compilado: $<"

# ---------------------------------------------------------
# Limpieza
# ---------------------------------------------------------
clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(ENV_DIR) clean
	@$(MAKE) -C $(LEXER_DIR) clean
	@$(MAKE) -C $(PARSER_DIR) clean
	@$(MAKE) -C $(EXPANDER_DIR) clean
	@$(MAKE) -C $(EXECUTOR_DIR) clean
	@echo "🧹 Clean completo."

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(ENV_DIR) fclean
	@$(MAKE) -C $(LEXER_DIR) fclean
	@$(MAKE) -C $(PARSER_DIR) fclean
	@$(MAKE) -C $(EXPANDER_DIR) fclean
	@$(MAKE) -C $(EXECUTOR_DIR) fclean
	@echo "🧼 Fclean completo."

re: fclean all

.PHONY: all clean fclean re
