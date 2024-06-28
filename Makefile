# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/19 09:20:47 by dzuiev            #+#    #+#              #
#    Updated: 2024/03/19 09:20:47 by dzuiev           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                                                              #
#                        Makefile for philosophers                             #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                        Philosophers                                          #
#  Project structure:                                                          #
#  philo/                                                                      #
#  ├── src/                    # Source files for philosophers core funct-lity #
#  │   ├── mandatory/          # Source files from mandatory sources           #
#  │   ├── bonus/              # Source files from bonus sources               #
#  │   └── main.c              # Main file for the philosophers project        #
#  ├── includes/               # Header files for all philosophers parts       #
#  │   ├── philo.h             # Main headers for the project                  #
#  │   └── philo_bonus.h       # Bonus headers for the project                 #
#  ├── obj/                    # Object files for all philosophers parts       #
#  │   ├── mandatory/          # Object files from mandatory sources           #
#  │   ├── bonus/              # Object files from bonus sources               #
#  ├── Makefile                # Makefile to build the philosophers project    #
#  └── README.md               # Documentation of the project                  #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# Colors for messages
GREEN=\033[0;32m
YELLOW=\033[0;33m
RED=\033[0;31m
BLUE=\033[0;34m
RESET=\033[0m
# **************************************************************************** #

# **************************************************************************** #
# Basic Configurations
NAME = philo # Name of the executable file
# BONUS_NAME = philo_bonus # Name of the executable file for bonus part
CC = cc # Compiler
CFLAGS = -Wall -Wextra -Werror -g -pthread # Flags
# LIBFT = $(LIBFT_DIR)/libft.a # Libft library
# **************************************************************************** #

# **************************************************************************** #
# Directories with source files and libraries
# LIBFT_DIR = libft
INCLUDES = -I./includes #-I$(LIBFT_DIR)
# LFLAGS = -L$(LIBFT_DIR) -lft
SRC_DIR = src
OBJ_DIR = obj
SRC_MANDATORY_DIR = $(SRC_DIR)/mandatory
OBJ_MANDATORY_DIR = $(OBJ_DIR)/mandatory
# SRC_BONUS_DIR = $(SRC_DIR)/bonus
# OBJ_BONUS_DIR = $(OBJ_DIR)/bonus
# **************************************************************************** #

# **************************************************************************** #
# Source and Object files mapping for mandatory and bonus parts
SRC = $(SRC_DIR)/main.c
# Source and Object files mapping for mandatory and bonus parts
# SRC = $(wildcard $(SRC_DIR)/*.c) # All source files in current directory (main.c)
# SRC_MANDATORY = $(wildcard $(SRC_MANDATORY_DIR)/*.c)
# SRC_BONUS = $(wildcard $(SRC_BONUS_DIR)/*.c)
# SRC += src/bonus/wildcard.c src/bonus/wildcard_dir.c
SRC_MANDATORY = $(addprefix $(SRC_MANDATORY_DIR)/, \
				init.c					libft_utils1.c			libft_utils2.c \
				monitor_philosophers.c	philo_actions.c			simulation.c \
				utils.c					validation_arguments.c	validation_utils.c \
				print_actions.c )
# SRC_BONUS = $(addprefix $(SRC_BONUS_DIR)/,main_with_bonus.c)
# SRC += src/bonus/wildcard.c src/bonus/wildcard_dir.c

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o) # All object files in current directory
OBJ_MANDATORY = $(SRC_MANDATORY:$(SRC_MANDATORY_DIR)/%.c=$(OBJ_MANDATORY_DIR)/%.o)
# OBJ_BONUS = $(SRC_BONUS:$(SRC_BONUS_DIR)/%.c=$(OBJ_BONUS_DIR)/%.o)
# **************************************************************************** #

# **************************************************************************** #
# Main target
# ifeq ($(MAKECMDGOALS), bonus)
# OBJ_MANDATORY += $(OBJ_BONUS)
# else
# OBJ_MANDATORY += $(OBJ)
# endif

all: $(NAME)

# Linking the executable
$(NAME):$(OBJ) $(OBJ_MANDATORY) 
	@$(CC) -o $@ $(OBJ) $(OBJ_MANDATORY)
	@echo "$(GREEN)$(NAME) compiled$(RESET)"

# -o $@ - output file name $(NAME), $@ = $(NAME)
# **************************************************************************** #

# Compile libft library
# $(LIBFT):
# 	@$(MAKE) -C $(LIBFT_DIR)
# 	@echo "$(GREEN)Libft compiled$(RESET)"
# **************************************************************************** #

# **************************************************************************** #
# Rules for compiling source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_MANDATORY_DIR)/%.o: $(SRC_MANDATORY_DIR)/%.c
	@mkdir -p $(OBJ_MANDATORY_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# $(OBJ_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c
# 	@mkdir -p $(OBJ_BONUS_DIR)
# 	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# -c $< -o $@ - compile source file $< into object file $@,
# $< = source file, $@ = object file
# **************************************************************************** #

# Bonus part compilation
# bonus: $(BONUS_NAME)

# bonus:  # Add a flag to the compiler
# $(BONUS_NAME): $(OBJ) $(OBJ_MANDATORY) $(OBJ_BONUS)
# 	@$(CC) -o $@ $(OBJ_MANDATORY) $(OBJ_BONUS)
# 	@echo "$(GREEN)$(BONUS_NAME) compiled with bonus part$(RESET)"
# **************************************************************************** #
# Cleaning up
clean:
	@ if [ -d $(OBJ_DIR) ]; then \
		rm -rf $(OBJ_DIR); \
		echo "$(YELLOW)Minishell object files removed$(RESET)"; \
	fi

# Full cleaning
fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)$(NAME) removed$(RESET)"
# rm -rf - remove the directory with all its content
# -r - remove directories and their contents recursively
# -f - ignore nonexistent files and arguments, never prompt

# Rebuild everything
re: fclean all

# **************************************************************************** #
# Phony targets
.PHONY: all clean fclean re
# **************************************************************************** #

# В контексте Makefile, команда -c $< -o $@ используется для указания компилятору ($(CC))
# как компилировать исходные файлы в объектные файлы. Вот детальное объяснение каждого компонента этой команды:

# -c
# Этот флаг говорит компилятору генерировать объектный файл (*.o) из исходного файла (*.c).
# Он останавливает процесс после этапа компиляции, не переходя к этапу линковки,
# который обычно следует за компиляцией при создании исполняемого файла.

# $<
# Это одна из автоматических переменных в Makefile, которая представляет имя первой зависимости текущего правила.
# В контексте правил компиляции, где правило выглядит как $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c,
# $< будет подставлено значением исходного файла .c, который нужно скомпилировать.

# -o
# Этот флаг используется для указания выходного файла компиляции. Следом за этим флагом должно идти имя файла,
# в который будет записан результат компиляции (в данном случае, объектный файл).

# $@
# Это также автоматическая переменная в Makefile, которая представляет имя цели текущего правила.
# В контексте правила, например, $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c, $@ будет заменено на имя объектного файла,
# который должен быть сгенерирован. Это позволяет обеспечить, что каждый исходный файл будет компилироваться
# в соответствующий объектный файл в указанной директории.

# В итоге, -c $< -o $@ означает, что компилятор должен взять исходный файл, указанный в $<,
# скомпилировать его и записать результат в файл, указанный в $@. Это позволяет компилятору
# создавать объектные файлы из исходных файлов в соответствии с указанными правилами.
