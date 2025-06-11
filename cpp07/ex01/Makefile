# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/20 12:55:30 by joaosilva         #+#    #+#              #
#    Updated: 2025/06/02 11:10:18 by joaosilva        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#######################  Variables ######################
NAME = iter
CC = c++
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -std=c++98 # -pthread -g -fsanitize=thread #-fsanitize=address
INCLUDE = -I include/

############  Source files - Sources to objects ###########
SRC_FILES = main.cpp
SRC_DIR = src/
SRC = ${addprefix ${SRC_DIR}, ${SRC_FILES}}

########### Object files ###########
OBJ_DIR = objects/
OBJS = ${addprefix ${OBJ_DIR}, ${SRC_FILES:.cpp=.o}}

############ Header files same folder ###########
HEADER_FILES = iter.hpp
HEADER_DIR = include/
HEADER = ${addprefix ${HEADER_DIR}, ${HEADER_FILES}}

#######################   Rules ######################

# Default rule to build the executable
all: $(NAME)

# Rule to link object files and generate the executable
${NAME}: ${OBJS} ${HEADER}
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "$(GREEN)$(NAME) created$(DEF_COLOR)"
	
# Rule to compile object files from source files
${OBJ_DIR}%.o: ${SRC_DIR}%.cpp ${HEADER} # I could also use $(OBJ_PATH)%.o: src/%.cpp $(DEPS) because accordingly with the Makefile rules, I only have to declare mannually the .cpp (like I did in the SRC_FILES). 
	@mkdir -p $(dir $@)
	@${CC} ${CFLAGS} ${INCLUDE} -c $< -o $@
	@echo "$(GRAY) Object $(basename $(notdir $@)) files created with success$(DEF_COLOR)"

# Rule to remove object files and obj/ directory
clean:
	@$(RM) $(OBJS)
	@$(RM) -r $(OBJ_DIR)
	@echo "$(RED)Object files and obj/ directory removed$(DEF_COLOR)"

# Rule to remove the executable, object files, and obj/ directory
fclean: clean
	$(RM) $(NAME)
	$(RM) *_shrubbery
	@echo "$(RED)Executable $(NAME) removed$(DEF_COLOR)"

# Rule to remove all generated files and recompile everything
re: fclean all

# Phony targets
### ensures that the names of these commands are not mistaken for actual files. That is, if there is a file with the same name, the compiler will ignore it and still run the rule.
.PHONY: all clean fclean re bonus

### causes the actions to be executed without being displayed in the terminal. Hence the name "silent" — the actions still happen, but they are hidden from the terminal output.
#.SILENT:

# Colors
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

git :
	@ clear && sleep 1 && echo "$(RED)\n\n\n\nStart cleanning...\n\n" && sleep 1
	@ make fclean
	@ echo "$(CYAN)\n\n\n\nEverything clean\n\n\n$(GREEN)Git status:\n\n$(DEF_COLOR)"
	@ git status && sleep 1 && echo "$(RED)Press Enter to confirm" && read enter
	@ echo "$(DEF_COLOR)\nGit add everything\n\n"
	@ git add . && git status
	@ echo "$(YELLOW)" && read -p "Enter commit message: " message && read -p "Enter commit comment: " comment && git commit -m "$message" -m "$comment"
	@ echo "$(GRAY)" && git push
	@ echo "$(GREEN)\n\nGit push done with sucess\n\n$(DEF_COLOR)"
