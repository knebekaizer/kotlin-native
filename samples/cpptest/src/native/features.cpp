#include "features.h"

#include <iostream>

using namespace std;

namespace ns {

void NoName::noNameMember() {
	cout << __PRETTY_FUNCTION__ << " invoked" << endl;
}

int CppTest::s_fun() {
	static int counter = 777;
	cout << __PRETTY_FUNCTION__ << " invoked" << endl;
	return counter++;
}

int CppTest::foo(const CppTest* x) {
	int res = x == this;
	cout << "This is CppTest::foo: result is iPub + (int)(param == this): " << iPub + res << endl;
	return iPub + res;
}

CppTest::CppTest() : iPub(99) {}

CppTest::CppTest(int i) : iPub(i) {}

/*
CppTest::~CppTest() {
	cout << "~CppTest dtor called" << endl;
}
*/

CppTest bar(CppTest* s) {
	if (s)
		return *s;
	else
		return * new CppTest();
}

CppTest* create() {
	return new CppTest();
}

} // ns

CppTest* create() {
	cout << __PRETTY_FUNCTION__ << " declared in global ns" << endl;
	return nullptr;
}

::CppTest* ns2::create() {
	cout << __PRETTY_FUNCTION__ << " declared in ns2" << endl;
	return nullptr;
}
