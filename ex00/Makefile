# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/15 11:21:29 by bvan-pae          #+#    #+#              #
#    Updated: 2024/04/22 10:11:36 by bvan-pae         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CPP 	:= c++
CFLAGS 	:= -Wall -Wextra -Werror -std=c++98

NAME 	:= btc

SRC	:= $(wildcard *.cpp)

OBJ 	:= $(SRC:%.cpp=%.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CPP) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	$(CPP) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean:
	rm -rf $(OBJ) $(NAME)

re:	fclean all
