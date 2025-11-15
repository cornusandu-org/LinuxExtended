#pragma once

#include "headers.hpp"
#include <iostream>
#include <csignal>
#include <atomic>

static std::atomic<uint8_t> errcode{EXIT_SUCCESS};  // Should be async-safe (is not), but UB is purely theoretical
													// (it's atomic, so no race conditions) and this should work in practice
static std::atomic<bool> signal_gotten{false};

inline void cf_exit() {
	if (errcode == EXIT_DEBUG0 || errcode == EXIT_DEBUG1 || errcode == EXIT_DEBUG2 || errcode == EXIT_DEBUG3) {
		if (!DEBUG_BUILD) {return;}

		std::cerr << "[DEXIT] DEBUG EXIT TRIGGERED (ID=" << errcode - EXIT_DEBUG0 << ")" << std::endl;
		goto _finish;
	}
	switch (errcode) {
		case EXIT_SUCCESS: {
			goto _finish;
		}
		case EXIT_FAILURE: {
			std::cerr << "[UEXIT] An unknown error occured. Stopping the program. (EXIT CODE " << errcode << ")" << std::endl;
			goto _finish;
		}
		case EXIT_NO_SO: {
			std::cerr << "[EXIT] We failed to load a dynamic library. (EXIT CODE " << errcode << ")" << std::endl;
			goto _finish;
		}
		case EXIT_SEG_FAULT: {
			std::cerr << "[EXIT] Oops! Looks like a segfault (program memory was corrupted, or the program attempted to access invalid memory) (EXIT CODE " << errcode << ")" << std::endl;
			goto _finish;
		}
		case EXIT_PANIC: {
			std::cerr << "[UEXIT] Oops! Looks like something went wrong, and the program had to halt. (EXIT CODE " << errcode << ")" << std::endl;
			goto _finish;
		}
		case EXIT_FORCED: {
			std::cerr << "[EEXIT] Oops! Looks like you killed me. (EXIT_FORCED by SIGTERM / SIGILL)" << std::endl;
			goto _finish;
		}
		case EXIT_REQUESTED: {
			std::cerr << "[EEXIT] Oops! Looks like you killed me. (EXIT_REQUESTED)" << std::endl;
			goto _finish;
		}
		case EXIT_TERMINATED_BY_KERNEL: {
			std::cerr << "[KEXIT] Looks like the Linux kernel is attempting to kill me. (Error code: " << errcode << "/EXIT_TERMINATED_BY_KERNEL)" << std::endl;
			goto _finish;
		}
		default: {
			std::cerr << "[UEXIT] An unknown error occured, and no pre-defined exit code was found. (EXIT CODE " << errcode << ")" << std::endl;
			goto _finish;
		}
	}
	_finish:
		std::exit(errcode);
}

inline void cf_exit(int errorcode) {
	errcode = errorcode;
	cf_exit();
}

// This is a POSIX-based (Linux) function
// You may need to patch this for windows by adding #include <windows.h>
inline void signal_handler(int signal) {
	if (signal_gotten == true) return;
	signal_gotten = true;

	switch (signal) {
		case SIGSEGV:
		case SIGBUS:
		case SIGPIPE: {
			errcode = EXIT_SEG_FAULT;
			cf_exit();
			break;
		}
		case SIGTERM:
		case SIGILL: {
			errcode = EXIT_FORCED;
			cf_exit();
			break;
		}
		case SIGINT:
		case SIGQUIT:
		case SIGTSTP: {
			errcode = EXIT_REQUESTED;
			cf_exit();
			break;
		}
		case SIGXCPU:
		case SIGXFSZ:
		case SIGSYS: {
			errcode = EXIT_TERMINATED_BY_KERNEL;
			cf_exit();
			break;
		}
	}
}

/* Setup signal handling with signal_handler()                         */
/* Also intended for Linux, you may need to patch this for <windows.h> */
static void setup() {
	std::signal(SIGSEGV, signal_handler);
	std::signal(SIGBUS, signal_handler);
	std::signal(SIGPIPE, signal_handler);
	std::signal(SIGTERM, signal_handler);
	std::signal(SIGILL, signal_handler);
	std::signal(SIGINT, signal_handler);
	std::signal(SIGQUIT, signal_handler);
	std::signal(SIGTSTP, signal_handler);
	std::signal(SIGXCPU, signal_handler);
	std::signal(SIGXFSZ, signal_handler);
	std::signal(SIGSYS, signal_handler);
}
