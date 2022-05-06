#终极目标
all = server
#源文件
#SRC += $(shell find -name "*.c")
#SRC += $(shell find -name "*.cpp")
#目标文件
OBJ = ui.o
SUBOBJ  = db.o net.o
VPATH = ./
#编译选项
CFLAG = -I./include

#工程使用的库文件
LIBS = -./lib
#编译器
CC = g++
#安装命令变量定义
INSTALL_FILE = install -m 644 -p

#all的规则
$(all):./app/server/server.c $(OBJ) $(SUBOBJ)
	@echo 开始编译server
	$(CC) $^ -o  $@ $(CFLAG)
	-rm $(all) *.o 
	
#	$(CC) -o $@ $<
$(OBJ):$(SUBOBJ) 
	@echo 开始编译ui
	$(CC) ./lib/ui/ui.c  -c $(CFLAG)
	
net.o:
	@echo 开始编译net
	$(CC) ./lib/net/net.c -c $(CFLAG)
db.o:	
	@echo 开始编译db 
	$(CC) ./lib/db/db.c -c $(CFLAG)

	
#%.so:%.o	
#	$(CC) -fPIC -shared -o  lib$($@) $<

	

#伪目标
.PHONY:clean install

#清理工程规则
clean:
	@echo 正在清除编译产生的文件...
	-rm $(all) *.o *.so *.a 

#安装工程规则	
install:
	-$(INSTALL_FILE) server