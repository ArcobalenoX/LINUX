
#include <sys/epoll.h>


/*头文件和主要函数
epoll_create, epoll_ctl, epoll_wait和close
其中epoll_create用来创建一个epoll文件描述符，epoll_ctl用来添加/修改/删除需要侦听的文件描述符及其事件，epoll_wait/epoll_pwait接收发生在被侦听的描述符上的，用户感兴趣的IO事件。epoll文件描述符用完后，直接用close关闭即可
首先通过epoll_create(int maxfds)来创建一个epoll的句柄，其中maxfds为你epoll所支持的最大句柄数。这个函数会返回一个新的epoll句柄，之后的所有操作将通过这个句柄来进行操作。在用完之后，记得用close()来关闭这个创建出来的epoll句柄。
之后在你的网络主循环里面，每一帧的调用epoll_wait(int epfd, epoll_event *events, int max events, int timeout)来查询所有的网络接口，看哪一个可以读，哪一个可以写了。
其中kdpfd为用epoll_create创建之后的句柄，events是一个epoll_event*的指针，当epoll_wait这个函数操作成功之后，epoll_events里面将储存所有的读写事件。maxevents是最大事件数量。最后一个timeout是epoll_wait的超时，为0的时候表示马上返回，为-1的时候表示一直等下去，直到有事件发生，为任意正整数的时候表示等这么长的时间，如果一直没有事件，则返回。一般如果网络主循环是单独的线程的话，可以用-1来等，这样可以保证一些效率，如果是和主逻辑在同一个线程的话，则可以用0来保证主循环的效率。
*/

int epfd = epoll_create(POLL_SIZE);
struct epoll_event ev* = NULL;
struct epoll_event events;
nfds = epoll_wait(epfd, events, 20, 500);
{
    for (n = 0; n < nfds; ++n)
    {
        if (events[n].data.fd == listener)
        {
            //如果是主socket的事件的话，则表示
            //有新连接进入了，进行新连接的处理。
            client = accept(listener, (structsockaddr *)&local, &addrlen);
            if (client < 0)
            {
                perror("accept");
                continue;
            }
            setnonblocking(client);        //将新连接置于非阻塞模式
            ev.events = EPOLLIN | EPOLLET; //并且将新连接也加入EPOLL的监听队列。
            //注意，这里的参数EPOLLIN|EPOLLET并没有设置对写socket的监听，
            //如果有写操作的话，这个时候epoll是不会返回事件的，如果要对写操作
            //也监听的话，应该是EPOLLIN|EPOLLOUT|EPOLLET
            ev.data.fd = client;
            if (epoll_ctl(epfd, EPOLL_CTL_ADD, client, &ev) < 0)
            {
                //设置好event之后，将这个新的event通过epoll_ctl加入到epoll的监听队列里面，
                //这里用EPOLL_CTL_ADD来加一个新的epoll事件，通过EPOLL_CTL_DEL来减少一个
                //epoll事件，通过EPOLL_CTL_MOD来改变一个事件的监听方式。
                fprintf(stderr, "epollsetinsertionerror:fd=%d", client);
                return -1;
            }
        }
        else if(event[n].events & EPOLLIN)
        {
            //如果是已经连接的用户，并且收到数据，
            //那么进行读入
            int sockfd_r;
            if ((sockfd_r = event[n].data.fd) < 0)
                continue;
            read(sockfd_r, buffer, MAXSIZE);
            //修改sockfd_r上要处理的事件为EPOLLOUT
            ev.data.fd = sockfd_r;
            ev.events = EPOLLOUT | EPOLLET;
            epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd_r, &ev)
        }
        else if(event[n].events & EPOLLOUT)
        {
            //如果有数据发送
            int sockfd_w = events[n].data.fd;
            write(sockfd_w, buffer, sizeof(buffer));
            //修改sockfd_w上要处理的事件为EPOLLIN
            ev.data.fd = sockfd_w;
            ev.events = EPOLLIN | EPOLLET;
            epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd_w, &ev)
        }
        do_use_fd(events[n].data.fd);
    }
}