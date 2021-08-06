#include "thread_pool.h"
#include"subcopy.h"

int main(int argc,char *argv[])
{
    if(argv[1]==NULL||argv[2]==NULL)
    {
        printf("请输入两个文件夹的路径，第一个为源文件的路径，第二个为目标文件夹的路径\n");
        exit(-1);
    }
    char* source_path=argv[1];
    char* destination_path=argv[2];
    DIR* source=opendir(source_path);
    DIR* destination=opendir(destination_path);

    printf("开始复制\n");
    

    src_dest path=malloc(sizeof(struct src_dest));
    strcpy(path->src,source_path);
    strcpy(path->dest,destination_path);


    sleep(1);

    // 1, initialize the pool
    thread_pool *pool = malloc(sizeof(thread_pool));
    init_pool(pool,5);

    // 2, throw tasks
    printf("throwing 3 tasks...\n");
	
	//copydir(path);
    add_task(pool, copydir,(void*)path);
    add_task(pool, copydir, (void*)path);
   // add_task(pool, copydir, (void*)path);

    // 3, check active threads number
    printf("current thread number: %d\n",
           remove_thread(pool, 0));
    sleep(1);


    // 4, throw tasks
    printf("throwing another 2 tasks...\n");
    add_task(pool, copydir,(void*)path);
    add_task(pool, copydir, (void*)path);
	add_task(pool, copydir, (void*)path);
	add_task(pool, copydir, (void*)path);

    // 5, add threads
    add_thread(pool, 2);
    printf("add 2 pthread...\n");
    sleep(1);




    // 6, remove threads
    printf("remove 3 threads from the pool, "
           "current thread number: %d\n",
           remove_thread(pool, 3));




    // 7, destroy the pool
    destroy_pool(pool);
    free(pool);
    free(path);
    printf("结束\n");
    return 0;
}


