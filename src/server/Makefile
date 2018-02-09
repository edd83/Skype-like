
CC		=	g++

RM		=	rm -f

NAME		= 	server

SRCS		=							\
			../abstraction/LinuxTCPRemoteClient.cpp		\
			../abstraction/myTCPRemoteClient.cpp		\
			../abstraction/LinuxTCPClient.cpp		\
			../abstraction/LinuxTCPServer.cpp		\
			../abstraction/LinuxTCPSocket.cpp		\
			../abstraction/LinuxSelect.cpp			\
			../common/ReceiveException.cpp			\
			../common/FileSerializer.cpp			\
			../common/StandardInput.cpp			\
			../common/PacketHelper.cpp			\
			../common/RequestMaker.cpp			\
			../common/Debug.cpp				\
			./BabelServer.cpp				\
			./Database.cpp					\
			./UserData.cpp					\
			./main.cpp

INCLUDE		=	-I. -I../common -I../abstraction

OBJS		=	$(SRCS:.cpp=.o)

CXXFLAGS	=	-Wall -Wextra $(INCLUDE)


$(NAME):	$(OBJS)
		$(CC) $(OBJS) -o $(NAME)

all:		$(NAME)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY: all clean fclean re
