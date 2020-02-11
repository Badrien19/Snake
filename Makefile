# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: badrien <badrien@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/07 10:38:07 by badrien           #+#    #+#              #
#    Updated: 2020/02/11 17:29:27 by badrien          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



all:
			gcc  -I minitruc -L minitruc -lmlx -framework OpenGL -framework AppKit snake.c ../libft/libft.a -o "snake"

play:		all
			./snake
clean:
			rm snake

re: clean all
