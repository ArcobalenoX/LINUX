IMAGE = recv.out  
SRC = main.c jpeg_show.c PackageC.c
OBJ = $(SRC:%.c=%.o)

VPATH = .
CFLAGS = -I /home/gec/jpeglib/include -L /home/gec/jpeglib/lib -ljpeg 

CC = arm-linux-gcc

$(IMAGE) : $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

%.o : %.c
	$(CC) -c $< $(CFLAGS)


.PHONY:clean

clean:
	rm $(OBJ) $(IMAGE)



