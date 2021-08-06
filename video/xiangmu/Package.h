#ifndef __PACKAGE_H
#define __PACKAGE_H


/****** std Package functions ***/
#ifndef _PG_std
#define _PG_std

void * 
Malloc(size_t size){

	if(size <=0 ){
		fprintf(stderr,"malloc -->arg(size) must be above 0\n");
		exit(-1);
	}

	void * ptr = malloc(size);
	if(ptr == NULL){
		fprintf(stderr,"malloc nbyts[%lu] err\n",size);
		exit(-1);
	}	
	return ptr;
}


void * 
Calloc(size_t nmemb, size_t size){

	if((size <=0) || (nmemb <=0)){
		fprintf(stderr,"calloc -->arg(nmemb/size)\
					 must be above 0\n");
		exit(-1);
	}

	void * ptr = calloc(nmemb,size);
	if(ptr == NULL){
		fprintf(stderr,"calloc nbyts[%lu*%lu] err\n",nmemb,size);
		exit(-1);
	}	
	return ptr;
}

void *
Realloc(void *ptr, size_t size){

	if( size <= 0 ){
		fprintf(stderr,"realloc -->arg(size)\
					 must be above 0\n");
		exit(-1);
	}

	void * prt = realloc(ptr,size);
	if(prt == NULL){
		fprintf(stderr,"realloc nbyts[%lu] err\n",size);
		exit(-1);
	}	
	return prt;

	

}


void 
Free(void *ptr){
	free(ptr);	
}

FILE * 
Fopen(const char * path, const char *mode){
	FILE *fp = fopen(path, mode);
	
	if(fp == NULL){
		fprintf(stderr,"fopen %s err\n",path);
		perror("fopen err");
		exit(-1);
	}
	
	return fp;
}

int 
Fclose(FILE *fp){

	int ret = fclose(fp);
	if(ret == EOF){
		perror("fclose");
		exit(-1);
	}
	return ret;
}

#endif //end of _PG_std





/***** IO package functions *****/

#ifndef _PG_IO
#define _PG_IO

int 
Open(const char *pathname,...){
	
	int fd;
	
	va_list ap;
	va_start(ap,pathname);
	
	int flags = va_arg(ap,int);
	
	if((flags & O_CREAT)==O_CREAT){
		mode_t mode= va_arg(ap,mode_t);
		fd = open(pathname,flags,mode);
		
	}else{
		fd = open(pathname,flags);
	}

	
	if(fd == -1){
		fprintf(stderr,"open %s err\n",pathname);
		perror("open error");
		exit(-1);
	}
}

void 
Close(int fd){
	int ret = close(fd);

	if(ret == -1){
		fprintf(stderr,"close fd[%d]\n",fd);
		perror("");
		exit(-1);
	}

	return;
}



ssize_t 
Read(int fd, void *buf, size_t count){

	ssize_t nbyte = read(fd,buf,count);
	if(nbyte == -1){
		fprintf(stderr,"read fd[%d] err\n",fd);
		perror("read error");
		exit(-1);
	}
	return nbyte;
}


ssize_t 
Write(int fd, void *buf, size_t count){

	ssize_t nbyte = write(fd,buf,count);
	if(nbyte == -1){
		fprintf(stderr,"write fd[%d] err\n",fd);
		perror("write error");
		exit(-1);
	}
	return nbyte;
}


off_t 
Lseek(int fd, off_t offset, int whence){

	int tbyte = lseek(fd, offset, whence);
	if(tbyte == -1){
		fprintf(stderr,"lseek fd[%d] err\n",fd);
		perror("lseek error");
		exit(-1);
	}
	
	return tbyte;
}


int 
Munmap(void *addr,size_t length){
	
	int ret = munmap(addr,length);

	if(ret == -1){
		perror("munmap error");
		exit(-1);
	}
	
	return ret;
}


DIR * 
Opendir(const char * name){
	DIR * dirp = opendir(name);

	if(dirp == NULL){
		fprintf(stderr,"opendir %s err\n",name);
		perror("open dir err");
		exit(-1);
	}
	return dirp;
}

int
Closedir(DIR *dirp){
	int ret = closedir(dirp);
	
	if(ret == -1){
		perror("closedir");
		exit(-1);
	}
	
	return ret;
}

int 
Mkdir(char *pathname, mode_t mode){
	int ret = mkdir(pathname,mode);

	if(ret == -1){
		perror("mkdir");
		exit(-1);
	}
	
	return ret;
}


#endif //end of _PG_IO



#endif //end of __PACKAGE_H


