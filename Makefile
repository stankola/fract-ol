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

NAME = fract-ol

NAME_BONUS = fract-ol

CC = cc

CFLAGS = -Wall -Wextra -Werror

SFLAGS = -fsanitize=address -g3

SRCDIR = src

LIB_DIR = lib

OBJDIR = obj

INCDIR = include

OS := $(shell uname)

ifeq "$(OS)" "Linux"
MINILIB_DIR := minilibx-linux
else
MINILIB_DIR := minilibx_mms_20191025_beta
endif

ifeq "$(OS)" "Linux"
MINILIB_SRC := minilibx-linux.tgz
else
MINILIB_SRC := minilibx_mms_beta.tgz
endif

MINILIB_INCDIR = $(patsubst %, $(LIB_DIR)/%, $(MINILIB_DIR))

LIB_INCDIR = $(LIB_DIR)/$(INCDIR)

_SRC = fract-ol_main.c fract-ol_helpers.c draw.c shapes.c
SRC = $(patsubst %, $(SRCDIR)/%, $(_SRC))

_OBJ = $(patsubst %.c, %.o, $(_SRC))
OBJ = $(patsubst %, $(OBJDIR)/%, $(_OBJ))

#_SRC_BONUS = 
#SRC_BONUS = $(patsubst %, $(SRCDIR)/%, $(_SRC_BONUS))

#_OBJ_BONUS = $(patsubst %.c, %.o, $(_SRC_BONUS))
#OBJ_BONUS = $(patsubst %, $(OBJDIR)/%, $(_OBJ_BONUS))

_LIB = libft.a
LIB = $(patsubst %, $(LIB_DIR)/%, $(_LIB))
LIB_NAME = $(patsubst lib%.a, %, $(_LIB))

_INC = fract-ol.h
INC = $(patsubst %, $(INCDIR)/%, $(_INC))

#_INC_BONUS = 
#INC_BONUS = $(patsubst %, $(INCDIR)/%, $(_INC_BONUS))

_LIB_INC = libft.h
LIB_INC = $(patsubst %, $(LIB_INCDIR)/%, $(_LIB_INC))

_MINILIB_LIB_INC = mlx.h
MINILIB_LIB_INC = $(patsubst %, $(MINILIB_INCDIR)/%, $(_MINILIB_LIB_INC))

ifeq "$(OS)" "Linux"
_MINILIBX = libmlx.a
MINILIBX_NAME = $(patsubst lib%.a, %, $(_MINILIBX))
MINILIBX = $(patsubst %, $(LIB_DIR)/$(MINILIB_DIR)/%, $(_MINILIBX))
else
_MINILIBX = libmlx.dylib
MINILIBX_NAME = $(patsubst lib%.dylib, %, $(_MINILIBX))
endif


.PHONY: all bonus test clean

all: $(NAME)

#bonus: $(OBJ_BONUS) $(INC_BONUS) $(LIB)
#	$(CC) $(CFLAGS) $(OBJ_BONUS) -L$(LIB_DIR) -l$(LIB_NAME) -o $(NAME_BONUS)

sanitizer: $(OBJ)
	$(CC) $(CFLAGS) $(SFLAGS) $(OBJ) -L$(LIB_DIR) -l$(LIB_NAME) -o $(NAME)

suppress: $(SRC) $(LIB) $(INC)
	$(CC) $(SRC) -I$(INCDIR) -I$(LIB_INCDIR) -L$(LIB_DIR) -l$(LIB_NAME) -o $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(LIB):
	$(MAKE) -C $(LIB_DIR)

$(MINILIB_DIR):
	tar -xf $(LIB_DIR)/$(MINILIB_SRC) -C $(LIB_DIR)

# Minilib
# TODO: Should I include Makefile to requirements?
ifeq "$(OS)" "Linux"
$(MINILIBX): $(MINILIB_DIR)
	$(MAKE) -C $(LIB_DIR)/$(MINILIB_DIR)
else
$(_MINILIBX): $(MINILIB_DIR)
	$(MAKE) -C $(LIB_DIR)/$(MINILIB_DIR)
	cp $(LIB_DIR)/$(MINILIB_DIR)/$(_MINILIBX) .
endif

# Object
ifeq "$(OS)" "Linux"
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INC) $(LIB_INC) | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -I$(INCDIR) -I$(LIB_INCDIR) -I/usr/include -I$(MINILIB_INCDIR) -o $@
else
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INC) $(LIB_INC) | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -I$(INCDIR) -I$(LIB_INCDIR) -I$(MINILIB_INCDIR) -o $@
endif

# Build
ifeq "$(OS)" "Linux"
$(NAME): $(OBJ) $(LIB) $(MINILIBX)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIB_DIR) -l$(LIB_NAME) -L/usr/lib -L$(LIB_DIR)/$(MINILIB_DIR) -l$(MINILIBX_NAME) -lXext -lX11 -lm -o $@
else
$(NAME): $(OBJ) $(LIB) $(_MINILIBX)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIB_DIR) -l$(LIB_NAME) -l$(MINILIBX_NAME) -lm -o $@
endif

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

re: fclean all