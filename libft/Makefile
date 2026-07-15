#--------------------------------------#
#- CONFIG -----------------------------#
#--------------------------------------#

BIN_DIR			:= bin
INC_DIR			:= .

CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror
CFLAGS			+= -I $(INC_DIR)
CFLAGS			+= $(DBG)	# make DBG="-g"

NAME			:= libft.a
LIB				:= $(NAME)
LIB_DIR			:= .
LIB_CODES		:= \
	ft_isascii.c \
	ft_isalnum.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_strlen.c \
	ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_isalpha.c \
	ft_memmove.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_strchr.c \
	ft_strcmp.c \
	ft_strrchr.c \
	ft_strncmp.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strnstr.c \
	ft_atoi.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_strndup.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_split.c \
	ft_itoa.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_lst.c \
	ft_lst2.c \
	ft_lst_mut.c \
	ft_lst_mut2.c \
	get_next_line.c \
	get_next_line_utils.c \
	ft_printf_read.c \
	ft_printf_write_c.c \
	ft_printf_write_di.c \
	ft_printf_write_h.c \
	ft_printf_write_p.c \
	ft_printf_write_pc.c \
	ft_printf_write_s.c \
	ft_printf_write_u.c \
	ft_printf_write.c \
	ft_printf.c \
	ft_vec.c
LIB_OBJS		:= $(LIB_CODES:.c=.o)
LIB_MARK_NAME	:= mark_lib

#--------------------------------------#
#- CMD --------------------------------#
#--------------------------------------#

.PHONY: all
all: lib

.PHONY: clean
clean:
	find . -name "*.o" -delete

.PHONY: fclean
fclean: clean
	rm -f $(LIB) $(BIN_DIR)/*

.PHONY: re
re: fclean all

#--------------------------------------#
#- LIB --------------------------------#
#--------------------------------------#

.PHONY: lib
lib: $(NAME)

$(NAME): $(LIB_MARK_NAME)

$(LIB_MARK_NAME): $(LIB_OBJS)
	ar crs $(NAME) $^

#--------------------------------------#
#- COMMONS ----------------------------#
#--------------------------------------#

$(BIN_DIR):
	@mkdir $(BIN_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
