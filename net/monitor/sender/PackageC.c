#include "PackageC.h"


/****** std Package functions ***/
#ifdef _PG_std

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

#ifdef _PG_IO

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



/********* PIC Package function ****/

#ifdef _PG_PIC

pid_t 
Fork(void){
	int ret = fork();

	if(ret == -1){

		perror("fork err");
		exit(-1);
	}
}

pid_t 
Wait(int *status){
	int ret = wait(status);
	
	if(ret == -1){
		perror("wait err");
		exit(-1);
	}
	
	return ret;
}

pid_t
Waitpid(pid_t pid, int *status, int options){

	int ret = waitpid(pid,status,options);
	
	if(ret == -1){
		fprintf(stderr,"waitpid[%d] err\n",pid);
		perror("waitpid err");
		exit(-1);
	}
	return ret;
}

int
Kill (pid_t pid, int sig){
	int ret = kill(pid,sig);
	if(ret == -1){
		perror("kill err");
		exit(-1);
	}
	return ret;
}

int 
Raise(int sig){
	int ret = raise(sig);
	if(ret != 0){
		perror("raise err");
		exit(-1);
	}

	return ret;
}

typedef void (*sighandler_t)(int);

sighandler_t 
Signal(int signum, sighandler_t handler){

	sighandler_t ret = signal(signum,handler);

	if(ret == SIG_ERR){
		fprintf(stderr,"signal [%d] err\n",signum);
		exit(-1);
	}
	return ret;
}

int 
Pipe(int pipefd[2]){

	int ret = pipe(pipefd);
	if(ret == -1){
		perror("pipe err");
		exit(-1);
	}
	return ret;
}

int 
Mkfifo(const char *pathname, mode_t mode){
	
	int ret = mkfifo(pathname,mode);
	if(ret == -1){
		fptintf(stderr,"mkfifo %s err\n",pathname);
		perror("mkfifo err");
		exit(-1);
	}

	return ret;
}

key_t
Ftok(const char *pathname, int proj_id){

	key_t key = ftok(pathname,proj_id);

	if(key == -1){
		fprintf(stderr,"ftok [%s][%d] err\n",pathname,proj_id);
		perror("ftok err");
		exit(-1);
	}

	return key;
}	

int 
Msgget(key_t key, int msgflg){

	int msgid = msgget(key,msgflg);
	if(msgid == -1){
		perror("msgget err");
		exit(-1);
	}
	return msgid;
}

int 
Msgsnd(int msgid, const void *msgp, size_t msgsz, int msgflg){
	int ret = msgsnd(msgid,msgp,msgsz,msgflg);

	if(ret == -1){
	
		fprintf(stderr,"msgsnd [id:%d] err\n",msgid);
		perror("msgsnd");
		exit(-1);
	}

	return ret;
}

ssize_t 
Msgrcv(int msgid, void *msgp, size_t msgsz, long msgtyp, int msgflg){

	int nbyte = msgrcv(msgid,msgp, msgsz, msgtyp, msgflg);
	if(nbyte == -1){
		
		fprintf(stderr,"msgrcv [id:%d] err\n",msgid);
		perror("msgrcv");
		exit(-1);
	}

	return nbyte;
}

int 
Msgctl(int msgid, int cmd, struct msqid_ds *buf){

	int ret = msgctl(msgid, cmd, buf);

	if(ret == -1){
		
		fprintf(stderr,"msgctl [id:%d] err\n",msgid);
		perror("msgctl");
		exit(-1);
	}
	return ret;
}

int 
Shmget(key_t key, size_t size, int shmflg){

	int shmid  = shmget(key,size,shmflg);

	if(shmid == -1){
		
		fprintf(stderr,"msg [id:%d] err\n",msgid);
		perror("msgsnd");
		exit(-1);
	
	}
}

void *
Shmat ( int shmid, const void * shmaddr , int shmflg){
	void * shmp = shmat(shmid,shmaddr, shmflg);

	if(shmp == (void *)-1){
		fprintf(stderr,"shmat [%d] err\n",shmid);
		perror("shmat");
		exit(-1);
	}
	
	return shmp;
}

int 
Shmdt(const void * shmaddr){
	int ret = shmdt(shmaddr);	
	if(ret == -1){
		perror("shmdt");
		exit(-1);
	}
	return ret;
}

int
Shmctl(int shmid, int cmd, struct shmid_ds *buf){
	int ret = shmctl(shmid,cmd,buf);
	if(ret == -1){
		fprintf(stderr,"shmctl [id:%d] err\n",shmid);
		perror("shmctl");	
		exit(-1);
	}

	return ret;
}

int 
Semget(key_t key, int nsems, int semflg){
	int semid  = semget(key,nsems,semflg);

	if(semid == -1){
	
		fprintf(stderr,"semget [id:%d] err\n",semid);
		perror("semget");	
		exit(-1);
	}

	return semid;
}

int 
Semop(int semid, struct sembuf *sops, unsigned nsops){

	int ret = semop(semid, sops, nsops);

	if(ret == -1){
		fprintf(stderr,"semp [id:%d] err\n",semid);
		perror("semop err");
		exit(-1);
	}

	return ret;
}

#endif //end of _PG_PIC






/********************thread package function************/

#ifdef _PG_thread

int
Pthread_create(pthread_t *thread,const pthread_attr_t *attr,
		void *(*start_routine)(void *), void *arg){

	int ret = pthread_create(thread,attr,start_routine,arg);

	if(ret != 0){
		perror("pthread_create err");
		exit(-1);
	}
	
	return ret;
}

int 
Pthread_cancel(pthread_t thread){
	int ret = pthread_cancel(thread);
	if(ret !=0 ){
		perror("pthread cancel");
		exit(-1);
	}
	return ret;
}

int 
Pthread_join(pthread_t thread , void **retval){
	int ret = pthread_join(thread, retval);

	if(ret !=0 ){
		perror("pthread join");
		exit(-1);
	}
	return ret;
}

int 
Pthread_attr_init(pthread_attr_t *attr){
	int ret = pthread_attr_init(attr);
	
	if(ret !=0 ){
		perror("pthread_attr_init");
		exit(-1);
	}
	return ret;
}

int 
Pthread_attr_destroy(pthread_attr_t *attr){

	int ret = pthread_attr_destroy(attr);

	if(ret !=0 ){
		perror("pthread destroy");
		exit(-1);
	}
	return ret;
}

int 
Pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate){

	int ret = pthread_attr_setdetachstate(attr,detachstate);

	if(ret !=0 ){
		perror("pthread attr_setdetach state err");
		exit(-1);
	}
	return ret;
}


int 
Pthread_setcancelstate(int state,int *oldstate){
	int ret = pthread_setcancelstate(state,oldstate);

	if(ret !=0 ){
		perror("pthread setcancelstate err");
		exit(-1);
	}
	return ret;
}

int 
Pthread_setcanceltype(int type, int *oldtype){

	int ret = pthread_setcanceltype(type, oldtype);

	if(ret !=0 ){
		perror("pthread setcanceltype err");
		exit(-1);
	}
	return ret;


}

#endif //end of _PG_thread







/****************system-V sem**************/

#ifdef _PG_thread

sem_t *
Sem_open(const char *name, ... ){

	va_list ap;
	sem_t * ret;

	va_start(ap,name);

	int oflag = va_arg(ap,int);

	if( (oflag & O_CREAT) == O_CREAT){
		mode_t mode = va_arg(ap,mode_t);
		unsigned int value = va_arg(ap,unsigned int);

		ret = sem_open(name, oflag, mode , value);
	}else{
	
		ret = sem_open(name,oflag);
	}


	if(ret == SEM_FAILED){
	
		perror("sem_open err");
		exit(-1);
	}

	return ret;
	
}

int 
Sem_post(sem_t *sem){
	int ret = sem_post(sem);


	if(ret !=0 ){
		perror("sem_post err");
		exit(-1);
	}
	return ret;
}


int 
Sem_wait(sem_t *sem){

	int ret = sem_wait(sem);

	if(ret !=0 ){
		perror("sem_wait err");
		exit(-1);
	}
	return ret;

}

int 
Sem_unlink(char * sem){

	int ret = sem_unlink(sem);

	if(ret !=0 ){
		perror("sem unlink err");
		exit(-1);
	}
	return ret;
}

int 
Sem_close(sem_t * sem){
	int ret = sem_close(sem);

	if(ret !=0 ){
		perror("sem close err");
		exit(-1);
	}
	return ret;

}


int 
Sem_init(sem_t * sem, int pshared, unsigned int value){

	int ret = sem_init(sem,pshared, value);

	if(ret !=0 ){
		perror("sem_init err");
		exit(-1);
	}
	return ret;
}

int 
Sem_destroy(sem_t *sem){
	int ret = sem_destroy(sem);

	if(ret !=0 ){
		perror("sem_destroy err");
		exit(-1);
	}
	return ret;
}



#endif //end of _PG_thread





/************** IP/TCP/UDP package function ***********/

#ifdef _PG_IP

int 
Socket(int domain, int type, int protocol){

	int sockfd = socket(domain, type, protocol);

	if(sockfd == -1){
 
		perror("socket");
		exit(-1);
	}

	return sockfd;
}

int
Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen){
	int ret = bind(sockfd,addr,addrlen);

	if(ret == -1){
		perror("bind");
		exit(-1);
	}

	return ret;
}

int
Listen(int sockfd, int backlog){

	int ret = listen(sockfd, backlog);

	if(ret == -1){
		perror("listen");
		exit(-1);
	}
	return ret;
}

int 
Connect(int sockfd, const struct sockaddr* addr, socklen_t addrlen){

	int ret = connect(sockfd,addr, addrlen);
	
	if(ret == -1){

		perror("connect");
		exit(-1);
	}

	return ret;
}


int 
Accept(int sockfd, struct sockaddr *addr, socklen_t  *addrlen){

	int ret = accept(sockfd, addr, addrlen);

	if(ret == -1){

		perror("accept");
		exit(-1);
	}
	return ret;
}

ssize_t 
Send(int sockfd, const void *buf, size_t len, int flags){

	ssize_t ret = send(sockfd, buf, len, flags);

	if(ret == -1){
		perror("send");
		exit(-1);
	}
	
	return ret;
}

ssize_t 
Sendto(int sockfd, const void *buf, size_t len, int flags,
		const struct sockaddr *dest_addr, socklen_t addrlen){

	int ret = sendto(sockfd, buf, len, flags, dest_addr, addrlen);
	
	if(ret == -1){
		perror("sendto");
		exit(-1);
	}
	return ret;
}


ssize_t 
Recv(int sockfd, void *buf, size_t len, int flags){

	ssize_t ret = recv(sockfd, buf, len, flags);

	if(ret == -1){
		perror("send");
		exit(-1);
	}
	
	return ret;
}

ssize_t 
Recvfrom(int sockfd,  void *buf, size_t len, int flags,
	 	 struct sockaddr *src_addr, socklen_t *addrlen){

	int ret = recvfrom(sockfd, buf, len, flags, src_addr, addrlen);
	
	if(ret == -1){
		perror("recvfrom");
		exit(-1);
	}
	return ret;
}

#endif //end of _PG_IP




