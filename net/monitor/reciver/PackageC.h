#ifndef __PACKAGE_H
#define __PACKAGE_H

/********std header**********/
#define  _PG_std
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdarg.h>
#include <setjmp.h>

/**********IO header*************/
#define  _PG_IO
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

/*******TCP/UDP/IP header**************/
#define  _PG_IP
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


/********* jpeglib header *************/
#include "jpeglib.h"

//jpeg_show.c -->functions
void  lcd_init(void);
void  lcd_release(void);
int jpeg_show_file(char * const path);
int jpeg_show_buf(const unsigned char * jpg_buf, const off_t size, \
			int x0, int y0, int half_flg);


/****** std Package functions ***/
#ifdef _PG_std

void * 
Malloc(size_t size);


void * 
Calloc(size_t nmemb, size_t size);

void *
Realloc(void *ptr, size_t size);


void 
Free(void *ptr);

FILE * 
Fopen(const char * path, const char *mode);

int 
Fclose(FILE *fp);

#endif //end of _PG_std





/***** IO package functions *****/

#ifdef _PG_IO

int 
Open(const char *pathname,...);

void 
Close(int fd);



ssize_t 
Read(int fd, void *buf, size_t count);


ssize_t 
Write(int fd, void *buf, size_t count);


off_t 
Lseek(int fd, off_t offset, int whence);


int 
Munmap(void *addr,size_t length);

DIR * 
Opendir(const char * name);

int
Closedir(DIR *dirp);

int 
Mkdir(char *pathname, mode_t mode);

#endif //end of _PG_IO



/********* PIC Package function ****/

#ifdef _PG_PIC

pid_t 
Fork(void);

pid_t 
Wait(int *status);

pid_t
Waitpid(pid_t pid, int *status, int options);

int
Kill (pid_t pid, int sig);

int 
Raise(int sig);

typedef void (*sighandler_t)(int);

sighandler_t 
Signal(int signum, sighandler_t handler);

int 
Pipe(int pipefd[2]);

int 
Mkfifo(const char *pathname, mode_t mode);

key_t
Ftok(const char *pathname, int proj_id);

int 
Msgget(key_t key, int msgflg);

int 
Msgsnd(int msgid, const void *msgp, size_t msgsz, int msgflg);

ssize_t 
Msgrcv(int msgid, void *msgp, size_t msgsz, long msgtyp, int msgflg);

int 
Msgctl(int msgid, int cmd, struct msqid_ds *buf);

int 
Shmget(key_t key, size_t size, int shmflg);

void *
Shmat ( int shmid, const void * shmaddr , int shmflg);

int 
Shmdt(const void * shmaddr);

int
Shmctl(int shmid, int cmd, struct shmid_ds *buf);

int 
Semget(key_t key, int nsems, int semflg);

int 
Semop(int semid, struct sembuf *sops, unsigned nsops);

#endif //end of _PG_PIC






/********************thread package function************/

#ifdef _PG_thread

int
Pthread_create(pthread_t *thread,const pthread_attr_t *attr,
		void *(*start_routine)(void *), void *arg);

int 
Pthread_cancel(pthread_t thread);

int 
Pthread_join(pthread_t thread , void **retval);

int 
Pthread_attr_init(pthread_attr_t *attr);

int 
Pthread_attr_destroy(pthread_attr_t *attr);

int 
Pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate);


int 
Pthread_setcancelstate(int state,int *oldstate);

int 
Pthread_setcanceltype(int type, int *oldtype);

#endif //end of _PG_thread







/****************system-V sem**************/

#ifdef _PG_thread

sem_t *
Sem_open(const char *name, ... );

int 
Sem_post(sem_t *sem);


int 
Sem_wait(sem_t *sem);

int 
Sem_unlink(char * sem);

int 
Sem_close(sem_t * sem);

int 
Sem_init(sem_t * sem, int pshared, unsigned int value);

int 
Sem_destroy(sem_t *sem);



#endif //end of _PG_thread





/************** IP/TCP/UDP package function ***********/

#ifdef _PG_IP

int 
Socket(int domain, int type, int protocol);

int
Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

int
Listen(int sockfd, int backlog);

int 
Connect(int sockfd, const struct sockaddr* addr, socklen_t addrlen);


int 
Accept(int sockfd, struct sockaddr *addr, socklen_t  *addrlen);

ssize_t 
Send(int sockfd, const void *buf, size_t len, int flags);

ssize_t 
Sendto(int sockfd, const void *buf, size_t len, int flags,
		const struct sockaddr *dest_addr, socklen_t addrlen);


ssize_t 
Recv(int sockfd, void *buf, size_t len, int flags);

ssize_t 
Recvfrom(int sockfd,  void *buf, size_t len, int flags,
	 	 struct sockaddr *src_addr, socklen_t *addrlen);

#endif //end of _PG_IP

#endif //end of __PACKAGE_H


