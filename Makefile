
SRCS		:=  main.cpp Map.cpp Vector2D.cpp Game.cpp TextureManager.cpp Collision.cpp\
				include/ECS/ECS.cpp


INC 		:= 	$(addprefix $(HEADDIR), $(HEAD))\
				$(addprefix $(ECSDIR), $(ECS))

HEAD		:=	Vector2D.hpp TextureManager.hpp Map.hpp Game.hpp Const.hpp Collision.hpp\

HEADDIR		:=	include/

ECS			:=	Animation.hpp ColliderComponent.hpp Components.hpp ECS.hpp SpriteComponent.hpp\
				TileComponent.hpp TransformComponent.hpp
ECSDIR		:= includes/ECS/

OBJS		:= $(SRCS:.cpp=.o)
NAME		:= EmeraldSense
CC			:= c++
CFLAGS		:= -Wall -Wextra -Werror -std=c++17
LIB  		:= -lSDL2main -lSDL2  -lSDL2_image  -lSDL2_ttf

%.o:		%.cpp $(INC)
				$(CC) $(CFLAGS) -Iinclude -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJS)
				$(CC) $(CFLAGS) $(OBJS) $(LIB)  -o $(NAME)

clean:
				$(RM) $(OBJS)
		
fclean:		clean
				$(RM) $(NAME)

re:			fclean all

.PHONY:     all clean fclean re