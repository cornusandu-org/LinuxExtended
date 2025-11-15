# C++ Project Template
A general-purpose base for new C++ projects (mainly intended for Linux development). This base already adds **signal handling**, as well as **custom exit codes** not just for debugging purposes, but also to inform your users of what went wrong and produce an output easy to copy & paste into an Issue / bug report.


| Exit Code Name | Exit Code | Purpose | Associated Signals |  |
|:---:|:---:|---|:---:|---|
| EXIT_SEG_FAULT | 139 | Anything that could be associated with segfaults | SIGSEGV, SIGBUS, SIGPIPE |  |
| EXIT_NO_SO | 15 | Failed to load a .so (or dynamically linked library) | N/A |  |
| EXIT_DEBUG0 - EXITDEBUG3 | 16-19 | Debug-purposes exit codes | N/A |  |
| EXIT_PANIC | 20 | Emergency exits | N/A |  |
| EXIT_FORCED | 21 | When something is trying to kill the program | SIGTERM, SIGILL |  |
| EXIT_REQUESTED | 22 | When the user is attempting to close the program | SIGINT, SIGQUIT, SIGTSTP |  |
| EXIT_TERMINATED_BY_KERNEL | 23 | When the kernel wishes to terminate the program | SIGXCPU, SIGXFSZ, SIGSYS |  |

## Getting Started

Include the header and call `setup()` early in `main()`:

```cpp
#include "stopping.hpp"

int main() {
    setup(); // install signal handlers

    // your code...

    return 0;
}
```

DEBUG exit codes are disabled by default, but you can enable them by building with the following compiler flag: `-DDEBUG_BUILD=true`