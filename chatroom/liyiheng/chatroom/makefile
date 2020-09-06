CC = gcc
target1 = Server
target2 = Client
object1 = Server.c ServerFunction.c Linklist.c mysql.c
object2 = Client.c ClientFunction.c	Linklist.c

all : $(target1) $(target2)

$(target1) : $(object1)
	$(CC) -g $(object1) -o $(target1) -lpthread -Wall -L/usr/lib64/mysql -lmysqlclient
$(target2) : $(object2)
	$(CC) -g $(object2) -o $(target2) -lpthread -Wall -L/usr/lib64/mysql -lmysqlclient

.PHONY : clean
clean :
	rm -rf $(target1)
	rm -rf $(target2)
