#include "eh.h"

#include <iostream>
#include <exception>

#include "trace.h"

int exc_wrapper(exc_fun foo) {
	try {
		auto rc = foo();
		log_info << "Exception missed; rc = " << rc;

	} catch (std::exception& e) {
		log_info << "Exception handled: "  << e.what();
		return 0;
	}
	return -1;
}


int exc_throw(void) {
	TraceF;
	throw std::runtime_error("exc_throw");
	return 42;
}


#ifdef MAIN

int main() {
	TraceF;
	auto rc = exc_wrapper(exc_throw);
	TraceX(rc);
	return 0;
}

#endif