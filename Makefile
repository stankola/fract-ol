#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsankola <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/20 20:58:24 by tsankola          #+#    #+#              #
#    Updated: 2023/05/20 20:58:26 by tsankola         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = fractol

NAME_BONUS = fractol

CC = cc

CFLAGS = -Wall -Wextra -Werror

SFLAGS = -fsanitize=address -g3

SRCDIR = src

SRCDIR_BONUS = src_bonus

LIB_DIR = lib

OBJDIR = obj

OBJDIR_BONUS = obj

INCDIR = include

INCDIR_BONUS = include_bonus

OS := $(shell uname)

ifeq "$(OS)" "Linux"
MINILIB_SRC_DIR := minilibx-linux
#else ifeq "$(OS)" "Darwin"
#MINILIB_SRC_DIR := minilibx_mms_20191025_beta
#MINILIB_SRC_DIR := /usr/local/include
endif

ifeq "$(OS)" "Linux"
MINILIB_SRC := minilibx-linux.tgz
#else ifeq "$(OS)" "Darwin"
#MINILIB_SRC := minilibx_mms_beta.tgz
endif

ifeq "$(OS)" "Linux"
MINILIB_INCDIR = $(patsubst %, $(LIB_DIR)/%, $(MINILIB_SRC_DIR))
else ifeq "$(OS)" "Darwin"
MINILIB_INCDIR = /usr/local/include
endif

LIB_INCDIR = $(LIB_DIR)/$(INCDIR)

_SRC =	fractol_main.c fractol_helpers.c draw.c mandelbrot.c julia.c \
		hooks_n_things.c
SRC = $(patsubst %, $(SRCDIR)/%, $(_SRC))

_OBJ = $(patsubst %.c, %.o, $(_SRC))
OBJ = $(patsubst %, $(OBJDIR)/%, $(_OBJ))

_SRC_BONUS = $(patsubst %.c, %_bonus.c, $(_SRC))
SRC_BONUS = $(patsubst %, $(SRCDIR)/%, $(_SRC_BONUS))

_OBJ_BONUS = $(patsubst %.c, %.o, $(_SRC_BONUS))
OBJ_BONUS = $(patsubst %, $(OBJDIR)/%, $(_OBJ_BONUS))

_LIB = libft.a
LIB = $(patsubst %, $(LIB_DIR)/%, $(_LIB))
LIB_NAME = $(patsubst lib%.a, %, $(_LIB))

_INC = fractol.h
INC = $(patsubst %, $(INCDIR)/%, $(_INC))

_INC_BONUS = $(patsubst %.h, %_bonus.h, $(_INC))
INC_BONUS = $(patsubst %, $(INCDIR_BONUS)/%, $(_INC_BONUS))

_LIB_INC = libft.h
LIB_INC = $(patsubst %, $(LIB_INCDIR)/%, $(_LIB_INC))

_MINILIB_INC = mlx.h
MINILIB_INC = $(patsubst %, $(MINILIB_INCDIR)/%, $(_MINILIB_INC))

ifeq "$(OS)" "Linux"
_MINILIBX = libmlx.a
MINILIBX_NAME = $(patsubst lib%.a, %, $(_MINILIBX))
MINILIBX = $(patsubst %, $(LIB_DIR)/$(MINILIB_SRC_DIR)/%, $(_MINILIBX))
#else ifeq "$(OS)" "Darwin"
#_MINILIBX = libmlx.dylib
#MINILIBX_NAME = $(patsubst lib%.dylib, %, $(_MINILIBX))
endif

.PHONY: all bonus test clean

all: $(NAME)

bonus: .bonus

ifeq "$(OS)" "Linux"
.bonus: $(OBJ_BONUS) $(LIB) $(MINILIBX)
	$(CC) $(CFLAGS) $(OBJ_BONUS) -L$(LIB_DIR) -l$(LIB_NAME) -L/usr/lib -L$(LIB_DIR)/$(MINILIB_SRC_DIR) -l$(MINILIBX_NAME) -lXext -lX11 -lm -o $(NAME_BONUS)
else ifeq "$(OS)" "Darwin"
.bonus: $(OBJ_BONUS) $(LIB)
	$(CC) $(CFLAGS) $(OBJ_BONUS) -L$(LIB_DIR) -l$(LIB_NAME) -lm -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit -o $(NAME_BONUS)
endif
	@touch .bonus
	@rm -f .mandatory

sanitizer: $(OBJ)
	$(CC) $(CFLAGS) $(SFLAGS) $(OBJ) -L$(LIB_DIR) -l$(LIB_NAME) -o $(NAME)

suppress: $(SRC) $(LIB) $(INC)
	$(CC) $(SRC) -I$(INCDIR) -I$(LIB_INCDIR) -L$(LIB_DIR) -l$(LIB_NAME) -o $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(LIB):
	$(MAKE) -C $(LIB_DIR)

$(MINILIB_SRC_DIR):
	tar -xf $(LIB_DIR)/$(MINILIB_SRC) -C $(LIB_DIR)

# Minilib
ifeq "$(OS)" "Linux"
$(MINILIBX): $(MINILIB_SRC_DIR)
	$(MAKE) -C $(LIB_DIR)/$(MINILIB_SRC_DIR)
#else ifeq "$(OS)" "Darwin"
#$(_MINILIBX): $(MINILIB_SRC_DIR)
#	$(MAKE) -C $(LIB_DIR)/$(MINILIB_SRC_DIR)
#	cp $(LIB_DIR)/$(MINILIB_SRC_DIR)/$(_MINILIBX) .
endif

# Object
ifeq "$(OS)" "Linux"
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INC) $(LIB_INC) $(MINILIB_INC) | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -I$(INCDIR) -I$(LIB_INCDIR) -I/usr/include -I$(MINILIB_INCDIR) -o $@

$(OBJDIR_BONUS)/%.o: $(SRCDIR_BONUS)/%.c $(INC_BONUS) $(LIB_INC) $(MINILIB_INC) | $(OBJDIR_BONUS)
	$(CC) $(CFLAGS) -c $< -I$(INCDIR_BONUS) -I$(LIB_INCDIR) -I/usr/include -I$(MINILIB_INCDIR) -o $@
else ifeq "$(OS)" "Darwin"
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INC) $(LIB_INC) $(MINILIB_INC) | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -I$(INCDIR) -I$(LIB_INCDIR) -I$(MINILIB_INCDIR) -o $@

$(OBJDIR_BONUS)/%.o: $(SRCDIR_BONUS)/%.c $(INC_BONUS) $(LIB_INC) $(MINILIB_INC) | $(OBJDIR_BONUS)
	$(CC) $(CFLAGS) -c $< -I$(INCDIR_BONUS) -I$(LIB_INCDIR) -I$(MINILIB_INCDIR) -o $@
endif

# Build
$(NAME): .mandatory

ifeq "$(OS)" "Linux"
.mandatory: $(OBJ) $(LIB) $(MINILIBX)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIB_DIR) -l$(LIB_NAME) -L/usr/lib -L$(LIB_DIR)/$(MINILIB_SRC_DIR) -l$(MINILIBX_NAME) -lXext -lX11 -lm -o $(NAME)
else ifeq "$(OS)" "Darwin"
.mandatory: $(OBJ) $(LIB)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIB_DIR) -l$(LIB_NAME) -lm -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit -o $(NAME)
endif
	@touch .mandatory
	@rm -f .bonus

clean:
	rm -f $(OBJ)
	rm -f $(OBJ_BONUS)
	rmdir $(OBJDIR) 2> /dev/null || true
	$(MAKE) -C $(LIB_DIR) clean
	rm -f $(LIB)
	rm -f $(patsubst %, %~, $(SRC) $(SRC_BONUS))
	rm -f $(patsubst %, %~, $(INC) $(INC_BONUS))

fclean: clean
	rm -f $(NAME)
	@rm -f .bonus
	@rm -f .mandatory

re: fclean all