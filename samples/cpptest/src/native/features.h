
namespace ns {

typedef class {
public:
	void noNameMember();
} NoName;

class CppTest {
public:
	static int s_fun();

	CppTest();

	CppTest(int i);

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

template <typename T> struct TmplStruct {
public:
	void baz() const {}
};

template <typename T> class TmplClass {
public:
	void baz() const {}
};

} // ns2
