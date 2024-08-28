#------Colours------#
DEF_COLOR='\033[0;39m'
RESET = '\033[0;0m'
BLACK='\033[0;30m'
RED='\033[1;91m'
GREEN='\033[1;92m'
YELLOW='\033[0;93m'
BLUE='\033[0;94m'
MAGENTA='\033[0;95m'
CYAN='\033[0;96m'
GRAY='\033[0;90m'
WHITE='\033[0;97m'

#------Program Name-----#
NAME = minishell

#------Header-------#
HEADER = -I ./header/

#----Directories-----#
SRC_DIR = ./source/
OBJ_DIR = ./obj/
LIBFT_DIR = ./libft/

#-----Path-------#
LIBFT_PATH = ./libft/libft.a
MINISHELL_PATH = $(OBJ_DIR)libft.a

#------Command-------#
CC = gcc
CFLAGS = -Werror -Wextra -Wall
RLFLAGS = -L./readline -lreadline -lncurses
FSAN = -fsanitize=address -g3
LEAKS = Leaks --atExit --
RM = rm -rf
AR = ar rcs

#-----Files-----#
SRC_FILES	=	main.c \


OBJ_FILES = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

#----Rules & Dependencies-----#
all : execlib $(NAME)

$(NAME) :$(OBJ_DIR) $(OBJ_FILES)
	@echo $(GREEN)"--------- 🗃 Compiling Files 🗄 ----------\n"$(RESET)
	@cp $(LIBFT_PATH) $(OBJ_DIR)
	@$(AR) $(MINISHELL_PATH) $(OBJ_FILES)
	@$(CC) $(CFLAGS) $(HEADER) $(MINISHELL_PATH) $(RLFLAGS) -o $(NAME)
	@echo $(GREEN)"------- 🎉 Files had been compiled 🎉 --------\n"$(RESET)
	@echo $(GREEN)"-------- 📁 Your File Name is :"$(RESET)${RED}" $(NAME) "${END}${GREEN}"📂 --------\n"$(RESET)

clean :
	@echo $(YELLOW)"----- 🧼 Grandma is trying to clean your files 🧹 ------\n"$(RESET)
	@make -s fclean -C $(LIBFT_DIR)
	@$(RM) $(MINISHELL_PATH)
	@$(RM) $(OBJ_DIR)
	@echo $(YELLOW)"------ ✅ All Object Files Had Been Cleaned ✅ -------\n"$(RESET)


fclean :clean
	@$(RM) $(NAME)
	@$(RM) $(MINISHELL_PATH)
	@$(RM) $(OBJ_DIR)
	@$(RM) $(NAME)
	@echo $(YELLOW)"-------- ✅ All Object Files and Program Had Been Removed ✅ --------\n"$(RESET)

re :fclean all

execlib :
	@make -s -C $(LIBFT_DIR)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

$(OBJ_DIR) :
	@mkdir -p $(OBJ_DIR)

norm :
	norminette ./header
	norminette ./libft
	norminette ./source

.PHONY : all bonus clean fclean re execlib
