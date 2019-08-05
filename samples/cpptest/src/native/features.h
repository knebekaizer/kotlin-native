
namespace ns {

typedef class {
public:
	void noNameMember(const int& iRef);
} NoName;

class CppTest {
public:
	static int s_fun();

	CppTest() = default;

	CppTest(const CppTest&) = default;

	explicit CppTest(int i, double j = 3.14);

	~CppTest() = default;


	int iPub = 42;

	virtual int foo(const CppTest*);
//	int foo(const CppTest*);

	template <class X> void fooTmplMember() const;
private:
//	CppTest* fct() const;

private:
	int iPriv;
};

CppTest bar(CppTest* s);

CppTest* create();

} // ns

namespace {
ns::CppTest* fooInAnonNamespace();

}

class CppTest;
CppTest* create();

namespace ns2 {
	::CppTest* create();

/*
template <typename T> struct TmplStruct {
public:
	void baz() const {}
};

template <typename T> class TmplClass {
public:
	void baz() const {}
};

typedef class TmplStruct<int> IntTmplStruct;
IntTmplStruct intTmplStruct;

struct Smth {
    IntTmplStruct intTmplStruct;
};
*/
} // ns2

