NAME = webserv


CC = c++ 

CPPFLAGS = -std=c++98  -Wall -Wextra -Werror -fsanitize=address -g

SRCS =	srcs/main.cpp \
		srcs/Client.cpp \
		srcs/Server.cpp \
		srcs/ContextManager.cpp \
		srcs/Location.cpp \
		srcs/fileSystemUtils.cpp \
		srcs/string.cpp \
		srcs/ConfigParser.cpp \
		srcs/autoindex.cpp \
		srcs/GET.cpp \
		srcs/POST.cpp \
		srcs/DELETE.cpp \
		srcs/requestParser.cpp \
		srcs/CGI.cpp \
		

OBJS:=$(SRCS:.cpp=.o)


all : $(NAME)

$(NAME) : $(OBJS)
	$(CC)   $(CPPFLAGS) $(OBJS)  -o $(NAME)


clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : clean all
