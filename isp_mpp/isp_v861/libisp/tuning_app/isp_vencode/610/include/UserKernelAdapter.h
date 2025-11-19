/* SPDX-License-Identifier: GPL-2.0-or-later */
/* Copyright(c) 2020 - 2023 Allwinner Technology Co.,Ltd. All rights reserved. */

#ifndef USERKERNELADAPTER_h
#define USERKERNELADAPTER_h

#ifdef CONFIG_AW_VIDEO_KERNEL_ENC
//#include "ve_interface.h"
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/mutex.h>
#include <linux/delay.h>
#include <linux/semaphore.h>
#include <linux/errno.h>
#include <linux/kthread.h>

// #include "sc_interface.h"
#include "cedar_ve.h"

int kernel_write_file(unsigned char *data0, int size0, unsigned char *data1, int size1, char *file_name);
int kernel_mutex_init(struct mutex *p_mutex);
int read_file_by_name(unsigned char *data0, int size0, char *file_name);
int check_device_exists(char *name);
#define PRINTF printk

#define MUTEX_STRUCT struct mutex
#define SEM_STRUCT struct semaphore
#define THREAD_STRUCT struct task_struct*
#define MALLOC(size) kmalloc(size, GFP_KERNEL | __GFP_ZERO)
#define MALLOC_BIG(size) vmalloc(size)
#define CALLOC(num, size)  kcalloc(num, size, GFP_KERNEL)
#if 1
#define FREE(poiter) do {\
	if (poiter) {\
		kfree(poiter);\
		poiter = NULL;\
	} \
} while (0)

#define FREE_BIG(poiter) do {\
	if (poiter) {\
		vfree(poiter);\
		poiter = NULL;\
	} \
} while (0)
#else
#define FREE(poiter) do {\
    if (poiter) {\
		logd("poiter 0x%px", poiter);\
		kfree(poiter);\
	poiter = NULL;\
    } \
} while (0)

#define FREE_BIG(poiter) do {\
    if (poiter) {\
		vfree(poiter);\
		poiter = NULL;\
    } \
} while (0)
#endif
#define THREAD_CREATE(p_thread, attr, func, arg, name) do { \
	p_thread = kthread_run(func, (void *)arg, name); \
} while (0)

#define THREAD_JOIN(thread, pp_ret) kthread_stop(thread)

#define DEF_STATIC_MUTEX(Mutex) DEFINE_MUTEX(Mutex)
#define MUTEX_INIT(p_mutex, p_mutex_attr)  kernel_mutex_init(p_mutex)
#define MUTEX_LOCK(p_mutex) mutex_lock(p_mutex)
#define MUTEX_UNLOCK(p_mutex) mutex_unlock(p_mutex)
#define MUTEX_DESTROY(p_mutex) mutex_destroy(p_mutex)

#define SEM_INIT(p_sem, shared, value) sema_init(p_sem, value)
#define SEM_POST(p_sem) up(p_sem)
#define SEM_WAIT(p_sem) down(p_sem)
#define SEM_TRYWAIT(p_sem) ({ \
    int __ret = down_trylock(p_sem); \
    if (__ret) { printk("err, ret %d\n", __ret); } \
    __ret; \
})
#define SEM_GETVALUME(p_sem, cnt) ((*cnt) = (p_sem)->count)
#define SEM_DESTROY(p_sem)

#define FILE_STRUCT struct file

static inline struct file* inline_filp_open(const char *path, int flags, umode_t mode)
{
    struct file *filp = filp_open(path, O_WRONLY | O_CREAT, 0644);
    if (IS_ERR(filp)) {
        pr_err("filp_open failed for %s: %ld\n", path, PTR_ERR(filp));
        return filp;
    }
    return filp;
}

#define FLOOR(x) ((x) >= 0 ? (int)(x) : (int)((x)-1))

#define FOPEN_W(name, arg) inline_filp_open(name, O_WRONLY | O_CREAT, 0644);
#define FOPEN_R(name, arg) inline_filp_open(name, O_RDONLY, 0644);
#define FOPEN_A(name, arg) inline_filp_open(name, O_WRONLY | O_APPEND | O_CREAT, 0644);
#define FWRITE(data, size, n, fd) if((fd)!=NULL){loff_t pos = 0;kernel_write(fd, data, size, &pos);}
#define FCLOSE(p) if((p)!=NULL){filp_close(p, NULL);p=NULL;}

#define WRITE_FILE(data0, size0, data1, size1, file_name) kernel_write_file(data0, size0, data1, size1, file_name)
#define WRITE_FILE_FD(data0, size0, data1, size1, fd)

#define READ_FILE(data0, size0, file_name) read_file_by_name(data0, size0, file_name)

#define POPCOUNT(p_addr) popcount(p_addr)
#define USLEEP(us) usleep_range(us, us + 10)

#define ATOI(str) simple_strtol(str, NULL, 10)

#ifndef VENC_SUPPORT_EXT_PARAM
#define VENC_SUPPORT_EXT_PARAM 0

typedef void *devfd_t;
typedef void *ionfd_t;

#define IOCTL(fd, cmd, arg) rt_cedardev_ioctl((devfd_t)fd, cmd, (unsigned long)arg)
#endif

#define ASSERT(cond) WARN_ON(!(cond))
#define GET_PID() task_tgid_vnr(current)
#define GET_TID() task_pid_vnr(current)
#define FILE_EXIST(name) check_device_exists(name)

#else//not CONFIG_AW_VIDEO_KERNEL_ENC
#include <pthread.h>
#include <stdio.h>

#define PRINTF printf
#define MUTEX_STRUCT pthread_mutex_t
#define SEM_STRUCT sem_t
#define THREAD_STRUCT pthread_t
#define MALLOC(size) malloc(size)
#define MALLOC_BIG(size) malloc(size)
#define CALLOC(num, size)  calloc(num, size)
#define FREE(poiter) do {\
    if (poiter) {\
		free(poiter);\
		poiter = NULL;\
    } \
} while (0)

#define FREE_BIG(poiter) do {\
    if (poiter) {\
		free(poiter);\
		poiter = NULL;\
    } \
} while (0)

#define THREAD_CREATE(thread, attr, func, arg, name) pthread_create(&thread, attr, func, (void *)arg)
#define THREAD_JOIN(thread, pp_ret) pthread_join(thread, pp_ret)

#define DEF_STATIC_MUTEX(Mutex) static MUTEX_STRUCT Mutex = PTHREAD_MUTEX_INITIALIZER
#define MUTEX_INIT(p_mutex, p_mutex_attr)  pthread_mutex_init(p_mutex, p_mutex_attr)
#define MUTEX_LOCK(p_mutex) pthread_mutex_lock(p_mutex)
#define MUTEX_UNLOCK(p_mutex) pthread_mutex_unlock(p_mutex)

#define MUTEX_DESTROY(p_mutex) pthread_mutex_destroy(p_mutex)

#define SEM_INIT(p_sem, shared, value) sem_init(p_sem, shared, value)
#define SEM_POST(p_sem) sem_post(p_sem)
#define SEM_WAIT(p_sem) sem_wait(p_sem)
#define SEM_TRYWAIT(p_sem) sem_trywait(p_sem)
#define SEM_GETVALUME(p_sem, cnt) sem_getvalue(p_sem, cnt)
#define SEM_DESTROY(p_sem) sem_destroy(p_sem)

#define FILE_STRUCT FILE

static inline FILE_STRUCT* safe_fopen(const char* filename, const char* mode) {
    FILE* fd = fopen(filename, mode);
    if (fd == NULL) {
		printf("open file err: %s\n", filename);
    }
    return fd;
}
#define FOPEN_W(name, arg) safe_fopen(name, "wb");
#define FOPEN_R(name, arg) safe_fopen(name, "rb");
#define FOPEN_A(name, arg) safe_fopen(name, "ab");
#define FWRITE(data, size, n, fd) fwrite(data, size, n, fd)
#define FCLOSE(p) if((p)!=NULL){fclose(p);p=NULL;}

#define WRITE_FILE(data0, size0, data1, size1, file_name) user_write_file(data0, size0, data1, size1, file_name)
#define WRITE_FILE_FD(data0, size0, data1, size1, fd) user_write_file_fd(data0, size0, data1, size1, fd)

#define READ_FILE(data0, size0, file_name) read_file_by_name(data0, size0, file_name)

#define POPCOUNT(p_addr) __builtin_popcount(p_addr)
#define USLEEP(us) usleep(us)

#define ATOI(str) atoi(str)

int user_write_file(unsigned char *data0, int size0, unsigned char *data1, int size1, char *file_name);
int user_write_file_fd(unsigned char *data0, int size0, unsigned char *data1, int size1, FILE_STRUCT *fp);
int read_file_by_name(unsigned char *data0, int size0, char *file_name);

typedef int devfd_t;
typedef int ionfd_t;

#define IOCTL(fd, cmd, arg) ioctl(fd, cmd, arg)
#define ASSERT(cond) assert(cond)
#define GET_PID() getpid()
#define GET_TID() gettid()
#define FLOOR(a) floor(a)
#define FILE_EXIST(name) (!access(name, F_OK))
#endif//CONFIG_AW_VIDEO_KERNEL_ENC

int get_random_number(void);

#endif//USERKERNELADAPTER_h
