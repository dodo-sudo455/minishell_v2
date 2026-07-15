#--------------------------------------#
#- CONFIG -----------------------------#
#--------------------------------------#

# main source codes
APP				:= minishell
APP_DIR			:= app
APP_CODES		:= $(shell find $(APP_DIR) -name '*.c')
APP_OBJS		:= $(APP_CODES:.c=.o)

BIN_DIR			:= bin
INC_DIR			:= include

CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror 
CFLAGS			+= -I $(INC_DIR) -I libft
CFLAGS			+= $(DBG)	# make DBG="-g"
LDLIBS			:= -lreadline -Llibft -lft

SRC_DIR			:= src
SRC_CODES		:= $(shell find $(SRC_DIR) -name '*.c')
SRC_OBJS		:= $(SRC_CODES:.c=.o)

TEST_DIR		:= test
TEST_NAMES		:= $(shell find $(TEST_DIR) -mindepth 1 -maxdepth 1 -type d -printf '%f\n')
TEST_CODES		:= $(shell find $(TEST_DIR) -name '*.c')
TEST_INC_DIR	:= test_include		# shared headers for test
TEST_SRC_DIR	:= test_src			# shared srcs for test
TEST_SRC_CODES	:= $(shell find $(TEST_SRC_DIR) -name '*.c')
TEST_SRC_OBJS	:= $(TEST_SRC_CODES:.c=.o)
# objs including all test srcs and shared srcs
TEST_OBJS		:= $(TEST_CODES:.c=.o) $(TEST_SRC_OBJS)

#--------------------------------------#
#- CMD --------------------------------#
#--------------------------------------#

.PHONY: all
all: app

.PHONY: clean
clean:
	find . -name "*.o" -delete
	$(MAKE) -C libft clean

.PHONY: fclean
fclean: clean
	rm -f $(APP)
	rm -f $(BIN_DIR)/*
	$(MAKE) -C libft fclean

.PHONY: re
re: fclean all

#--------------------------------------#
#- APP --------------------------------#
#--------------------------------------#

.PHONY: app
app: $(APP)

libft/libft.a:
	$(MAKE) -C libft

$(APP): $(SRC_OBJS) $(APP_OBJS) libft/libft.a
	$(CC) $(CFLAGS) -o $@ $(SRC_OBJS) $(APP_OBJS) $(LDLIBS)

#--------------------------------------#
#- SRC --------------------------------#
#--------------------------------------#

.PHONY: src
src: $(SRC_OBJS)

#--------------------------------------#
#- TEST -------------------------------#
#--------------------------------------#

.PHONY: test
test: $(BIN_DIR) $(TEST_NAMES)

.SECONDEXPANSION:
%_test: \
	$(SRC_OBJS) \
	$(TEST_SRC_OBJS) \
	libft/libft.a \
	$$(shell find $(TEST_DIR)/$$*_test -type f -name '*.c' | sed 's/\.c/\.o/') | \
	$(BIN_DIR)	# order only prerequisite
	$(CC) $(CFLAGS) -I $(TEST_INC_DIR) -o $(BIN_DIR)/$@ $^ -L libft -lft -lreadline

#--------------------------------------#
#- COMMONS ----------------------------#
#--------------------------------------#

$(BIN_DIR):
	mkdir $(BIN_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# include test headers for test objs
$(TEST_OBJS): %.o: %.c
	$(CC) $(CFLAGS) -I $(TEST_INC_DIR) -c -o $@ $<