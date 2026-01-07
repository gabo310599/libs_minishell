# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/11 16:33:59 by gojeda            #+#    #+#              #
#    Updated: 2026/01/07 04:43:33 by gojeda           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
SRC = ft_atoi.c \
		ft_atol.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_itoa.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_split.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_strndup.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strjoin_char.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_printf.c \
		ft_printf_utils.c \
		ft_printf_utils_base.c \
		ft_printf_hex_parse.c \
		get_next_line_bonus.c \
		get_next_line_utils_bonus.c \
		ft_lstadd_back_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstiter_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstmap_bonus.c \
		ft_lstnew_bonus.c \
		ft_lstsize_bonus.c \
		ft_realloc.c
SRC_BONUS = ft_lstadd_back_bonus.c \
			ft_lstadd_front_bonus.c \
			ft_lstclear_bonus.c \
			ft_lstdelone_bonus.c \
			ft_lstiter_bonus.c \
			ft_lstlast_bonus.c \
			ft_lstmap_bonus.c \
			ft_lstnew_bonus.c \
			ft_lstsize_bonus.c
CFLAGS = -Wall -Werror -Wextra
OBJ = ${SRC:.c=.o}
B_OBJ = ${SRC_BONUS:.c=.o}
RM = rm -f
AR = @ar rcs

all: ${NAME}

$(NAME): ${OBJ}
	${AR} ${NAME} ${OBJ}

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@ 

bonus:	${OBJ} ${B_OBJ}
	${AR} ${NAME} ${OBJ} ${B_OBJ}

clean:
	@${RM} ${OBJ} ${B_OBJ}

fclean:	clean
	@${RM} ${NAME}

re:	fclean all

.PHONY: all clean fclean re bonus