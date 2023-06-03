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

LIBDIR = lib

OBJDIR = obj

INCDIR = include

OS := $(shell uname)

ifeq "$(OS)" "Linux"
MINILIB_DIR := minilibx-linux-master
else
MINILIB_DIR := minilibx_mms_20191025_beta
endif

MINILIB_INCDIR = $(patsubst %, $(LIBDIR)/%, $(MINILIB_DIR))

LIB_INCDIR = $(LIBDIR)/$(INCDIR)

_SRC = fract-ol_main.c
SRC = $(patsubst %, $(SRCDIR)/%, $(_SRC))

_OBJ = $(patsubst %.c, %.o, $(_SRC))
OBJ = $(patsubst %, $(OBJDIR)/%, $(_OBJ))

#_SRC_BONUS = 
#SRC_BONUS = $(patsubst %, $(SRCDIR)/%, $(_SRC_BONUS))

#_OBJ_BONUS = $(patsubst %.c, %.o, $(_SRC_BONUS))
#OBJ_BONUS = $(patsubst %, $(OBJDIR)/%, $(_OBJ_BONUS))

_LIB = libft.a
LIB = $(patsubst %, $(LIBDIR)/%, $(_LIB))
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
MINILIBX = $(patsubst %, $(LIBDIR)/$(MINILIB_DIR)/%, $(_MINILIBX))
else
_MINILIBX = libmlx.dylib
MINILIBX_NAME = $(patsubst lib%.dylib, %, $(_MINILIBX))
endif


.PHONY: all bonus test clean

all: $(NAME)

#bonus: $(OBJ_BONUS) $(INC_BONUS) $(LIB)
#	$(CC) $(CFLAGS) $(OBJ_BONUS) -L$(LIBDIR) -l$(LIB_NAME) -o $(NAME_BONUS)

sanitizer: $(OBJ)
	$(CC) $(CFLAGS) $(SFLAGS) $(OBJ) -L$(LIBDIR) -l$(LIB_NAME) -o $(NAME)

suppress: $(SRC) $(LIB) $(INC)
	$(CC) $(SRC) -I$(INCDIR) -I$(LIB_INCDIR) -L$(LIBDIR) -l$(LIB_NAME) -o $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(LIB):
	$(MAKE) -C $(LIBDIR)

ifeq "$(OS)" "Linux"
$(MINILIBX): 
	$(MAKE) -C $(LIBDIR)/$(MINILIB_DIR)
else
$(_MINILIBX):
	$(MAKE) -C $(LIBDIR)/$(MINILIB_DIR)
	cp $(LIBDIR)/$(MINILIB_DIR)/$(_MINILIBX) .
endif

ifeq "$(OS)" "Linux"
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INC) $(LIB_INC) | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -I$(INCDIR) -I$(LIB_INCDIR) -I/usr/include -I$(MINILIB_INCDIR) -o $@
else
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INC) $(LIB_INC) | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -I$(INCDIR) -I$(LIB_INCDIR) -I$(MINILIB_INCDIR) -o $@
endif

ifeq "$(OS)" "Linux"
$(NAME): $(OBJ) $(LIB) $(MINILIBX)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBDIR) -l$(LIB_NAME) -L/usr/lib -L$(LIBDIR)/$(MINILIB_DIR) -l$(MINILIBX_NAME) -lXext -lX11 -lm -o $@
else
$(NAME): $(OBJ) $(LIB) $(_MINILIBX)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBDIR) -l$(LIB_NAME) -l$(MINILIBX_NAME) -lm -o $@
endif

clean:
	rm -f $(OBJ)
	rm -f $(OBJ_BONUS)
	rmdir $(OBJDIR) 2> /dev/null || true
	$(MAKE) -C $(LIBDIR) clean
	rm -f $(LIB)
	rm -f $(patsubst %, %~, $(SRC) $(SRC_BONUS))
	rm -f $(patsubst %, %~, $(INC) $(INC_BONUS))

fclean: clean
	rm -f $(NAME)

re: fclean all