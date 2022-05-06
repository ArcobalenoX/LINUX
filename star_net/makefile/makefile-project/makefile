#终极目标
all = server

#源文件
SRCS += $(shell find -name "*.c")
SRCS += $(shell find -name "*.cpp")

#目标文件
OBJ = ui.o db.o net.o

#查找路径
VPATH = ./app ./lib

#编译选项
CFLAG = -I./include -L./

#库文件
SLIB = libserver.a 

#编译器
ifeq ($(filter %.cpp, $(SRCS)),)
   CC = gcc
else
   CC = g++
endif

#all的规则
$(all):./app/server/server.c $(OBJ) $(SLIB) 
#	@echo 开始编译server
#	$(CC) $<  $(OBJ) -o  $@ $(CFLAG)
	@echo 开始静态库编译server...
	$(CC) $<  -o  $@ $(CFLAG) -lserver -static
	
$(SLIB):$(OBJ)
	@echo 生成静态库...
	ar rcs -o $@ $^
	
$(OBJ):$(SRCS)
	@echo 开始编译目标文件...
	$(CC) $(SRCS) -c $(CFLAG)	

#伪目标
.PHONY:clean install
#清理工程规则
clean:
	@echo 正在清除编译产生的文件...
	-rm $(all) *.o *.a
INSTDIR = ./bin
#安装工程规则	
install:server
	@echo 正在进行安装...
	-mkdir 	$(INSTDIR)
	cp server $(INSTDIR)
	

