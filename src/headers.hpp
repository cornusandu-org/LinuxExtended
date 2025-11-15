#pragma once

#define LINUX_HEADERS_IMPORTED

#include <iostream>         // C++ standard I/O
#include <fstream>          // C++ file streams
#include <string>           // C++ string handling
#include <vector>           // C++ dynamic arrays

// C standard headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>         // POSIX API (fork, pipe, etc.)
#include <fcntl.h>          // File control options
#include <dirent.h>         // Directory operations
#include <signal.h>         // Signal handling
#include <time.h>           // Time functions
#include <pthread.h>        // POSIX threads

// -------------------------- LINUX HEADERS --------------------------

#include <sys/types.h>      // Data types
#include <sys/stat.h>       // File status
#include <sys/mman.h>       // Memory mapping
#include <sys/socket.h>     // Sockets
#include <sys/un.h>         // Unix domain sockets
#include <sys/wait.h>       // Process waiting
#include <sys/ipc.h>        // IPC
#include <sys/shm.h>        // Shared memory
#include <sys/sem.h>        // Semaphores
#include <sys/time.h>       // Time structures
#include <sys/resource.h>   // Resource usage
#include <sys/ioctl.h>      // Device control
#include <sys/select.h>     // Select for I/O multiplexing
#include <sys/utsname.h>    // System information
#include <sys/ptrace.h>
#include <sys/user.h>
// Networking
#include <netinet/in.h>     // Internet address family
#include <netinet/tcp.h>    // TCP protocol
#include <arpa/inet.h>      // IP address conversion
#include <netdb.h>          // Network database operations

#include <linux/limits.h>   // Linux path limits
#include <linux/unistd.h>   // Linux syscall numbers
#include <sys/syscall.h>
#include <dlfcn.h>




// -------------------------- EXIT CODES --------------------------
#define EXIT_SEG_FAULT 139  // SIGSEGV / SIGBUS / SIGPIPE
#define EXIT_NO_SO 15
#define EXIT_DEBUG0 16
#define EXIT_DEBUG1 17
#define EXIT_DEBUG2 18
#define EXIT_DEBUG3 19
#define EXIT_PANIC 20
#define EXIT_FORCED 21  // SIGTERM / SIGILL
#define EXIT_REQUESTED 22  // SIGINT / SIGQUIT / SIGTSTP
#define EXIT_TERMINATED_BY_KERNEL 23  // SIGXCPU / SIGXFSZ / SIGSYS

#define DEBUG_BUILD false