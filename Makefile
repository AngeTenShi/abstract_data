NAME		=	abstract_data
CXX			=	c++ -g
RED			=	\033[0;31m
CYAN		=	\033[0;36m
COLOR_OFF	=	\033[0m\0
YELLOW		=	\033[0;33m
FLAGS		=	-Wall -Werror -Wextra -std=c++98
INC			= 	-I./includes
SRCS_DIR	=	srcs
OBJS_DIR	=	objs
SRCS		=	vector.cpp
 
OBJS		=	$(SRCS:%.cpp=$(OBJS_DIR)/%.o)

all:	$(NAME)

$(NAME):	$(LFT) $(OBJS)
			$(CXX) $(FLAGS) -o  $@ $^ 

$(OBJS): $(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp
			@mkdir -p $(@D)
			@echo
			@echo "$(RED)[**] Compiling $< [**]"
			@echo "$(COLOR_OFF)"
			$(CXX) $(FLAGS) $(INC) -o $@ -c $<

clean:
			@rm -rf $(OBJS_DIR)
			@echo "$(YELLOW)Objects files have been removed."

fclean:		clean
			@rm -rf $(NAME)
			@echo "$(YELLOW)Binary file has been removed."

re:			fclean all

.PHONY:		all clean fclean re
