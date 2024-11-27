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
ARCH = $(shell uname -m)
PWD = $(shell pwd)

#------Header-------#
HEADER = -I ./header/ -I $(READLINE_INC_DIR)

#----Directories-----#
SRC_DIR = ./source/
OBJ_DIR = ./obj/
LIBFT_DIR = ./libft/
BUILTIN_DIR = $(SRC_DIR)builtin/
EXECUTE_DIR = $(SRC_DIR)execution/
ENVIRONMENT_DIR = $(SRC_DIR)env/
SIGNAL_DIR = $(SRC_DIR)signal/
PARSING_DIR = $(SRC_DIR)parsing/
EXPANDER_DIR = $(SRC_DIR)expander/
HEREDOC_DIR = $(SRC_DIR)heredoc/
ERROR_DIR = $(SRC_DIR)error/

#-----Path-------#
LIBFT_PATH = ./libft/libft.a
MINISHELL_PATH = $(OBJ_DIR)libft.a

#----Readline----#
READLINE_URL = https://ftp.gnu.org/gnu/readline/readline-8.2.tar.gz
READLINE_TAR_FILE = readline-8.2.tar.gz
READLINE_SRC_DIR = readline-8.2/
READLINE_DIR = readline/$(ARCH)/
READLINE_LIB_DIR = $(READLINE_DIR)/lib
READLINE_LIB = $(READLINE_LIB_DIR)/libreadline.a
READLINE_INC_DIR = $(READLINE_DIR)/include
RLLIB = -L $(READLINE_LIB_DIR)

#------Command-------#
CC = gcc
CFLAGS = -Werror -Wextra -Wall
RLFLAGS = -lreadline -lncurses
FSAN = -fsanitize=address -g3
LEAKS = Leaks --atExit --
RM = rm -rf
AR = ar rcs

#-----Files-----#
SRC_FILES	=	main.c \
				start_shell.c \
				prep_shell.c \

ERROR_FILES	=	error.c\
				clean.c \
				quote_error.c \
				print.c \


BUILTIN_FILES	=	builtin_cd.c \
					builtin_echo.c \
					builtin_env.c \
					builtin_exit.c \
					builtin_pwd.c \
					builtin_unset.c\
					builtin_export.c\


EXECUTE_FILES	=	builtin.c\
					execution_setup.c \
					handle_cmd.c\
					handle_cmd_utils.c\
					pipe.c \
					pipe_utils.c \

ENVIRONMENT_FILES	=	env.c\
						env_tools.c\
						get_env.c\
						shell_level.c\
						sort_env.c\
						env_utils.c \
						

SIGNAL_FILES	=	signal.c\

PARSING_FILES	=	read_token.c \
					parser.c \
					parser_utils.c \
					parse_redirections.c \
					lexer.c \
					lexer_utils.c \
					cmds_utils.c \
					cmds.c \
					single_token.c \
					read_token_utils.c \
				

EXPANDER_FILES	=	expander.c \
					expander_utils.c \
					expander_utils2.c \

HEREDOC_FILES	=	heredoc.c \
					redirection.c \
					heredoc_utils.c \

OBJ_FILES	=	$(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o)) \
				$(addprefix $(OBJ_DIR), $(ERROR_FILES:.c=.o)) \
				$(addprefix $(OBJ_DIR), $(BUILTIN_FILES:.c=.o))\
				$(addprefix $(OBJ_DIR), $(EXECUTE_FILES:.c=.o))\
				$(addprefix $(OBJ_DIR), $(ENVIRONMENT_FILES:.c=.o))\
				$(addprefix $(OBJ_DIR), $(SIGNAL_FILES:.c=.o)) \
				$(addprefix $(OBJ_DIR), $(PARSING_FILES:.c=.o)) \
				$(addprefix $(OBJ_DIR), $(EXPANDER_FILES:.c=.o)) \
				$(addprefix $(OBJ_DIR), $(HEREDOC_FILES:.c=.o)) \

#----Rules & Dependencies-----#
all : execlib execrd  $(NAME)

$(NAME) :$(OBJ_DIR) $(OBJ_FILES)
	@echo $(GREEN)"--------- 🗃 Compiling Files 🗄 ----------\n"$(RESET)
	@cp $(LIBFT_PATH) $(OBJ_DIR)
	@$(AR) $(MINISHELL_PATH) $(OBJ_FILES)
	@$(CC) $(CFLAGS) $(HEADER) $(MINISHELL_PATH) $(RLLIB) $(RLFLAGS) -o $(NAME)
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

execrd :
	@if [ ! -d $(READLINE_DIR) ]; then \
		echo $(GREEN)"----- 👵🏻 Grandma is fetching readline ------\n"$(RESET); \
		curl -O "$(READLINE_URL)"; \
		echo $(GREEN)"------ 💤 Be patient yea, Grandma is compiling readline ------\n"$(RESET); \
		tar -xzf $(READLINE_TAR_FILE); \
		rm -rf $(READLINE_TAR_FILE); \
		cd $(READLINE_SRC_DIR) && ./configure "--prefix=$(PWD)/$(READLINE_DIR)" \
		&& make && make install && cd ..; \
		rm -rf $(READLINE_SRC_DIR); \
		echo "#include <stdio.h>\n" > .tmp; \
		cat $(READLINE_INC_DIR)/readline/readline.h >> .tmp; \
		mv .tmp $(READLINE_INC_DIR)/readline/readline.h; \
		echo "#include <stdio.h>\n" > .tmp; \
		cat $(READLINE_INC_DIR)/readline/rltypedefs.h >> .tmp; \
		mv .tmp $(READLINE_INC_DIR)/readline/rltypedefs.h; \
	else \
		echo $(GREEN)"----- 🧵 Readline had been installed 🧵 -----\n"$(RESET); \
	fi

clean_readline:
	@echo $(RED)"----- 🧻 Removing readline library -----\n"$(RESET)
	@rm -rf readline/
	@echo $(RED)"------ 🧼 Removing readline sources -----\n"$(RESET)
	@rm -rf $(READLINE_SRC_DIR)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

$(OBJ_DIR)%.o : $(ERROR_DIR)%.c
	@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

$(OBJ_DIR)%.o : $(BUILTIN_DIR)%.c
	@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

$(OBJ_DIR)%.o : $(EXECUTE_DIR)%.c
	@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@
	
$(OBJ_DIR)%.o : $(ENVIRONMENT_DIR)%.c
	@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

$(OBJ_DIR)%.o : $(SIGNAL_DIR)%.c
	@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

$(OBJ_DIR)%.o : $(PARSING_DIR)%.c
	@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

$(OBJ_DIR)%.o : $(EXPANDER_DIR)%.c
	@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

$(OBJ_DIR)%.o : $(HEREDOC_DIR)%.c
	@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@


$(OBJ_DIR) :
	@mkdir -p $(OBJ_DIR)

norm :
	norminette ./header
	norminette ./libft
	norminette ./source

.PHONY : all bonus clean fclean re execlib execrd clean_readline