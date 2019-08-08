
namespace ns {

typedef class {
public:
	void noNameMember(const int& iRef);
} NoName;

class CppTest {
public:
	static int s_fun();

	CppTest();

	CppTest(const CppTest&);

	explicit CppTest(int i, double j = 3.14);

	~CppTest();

	operator NoName() const;

	int iPub = 42;

	virtual int foo(const CppTest*);
	virtual int foo(const CppTest*) const;
//	int foo(const CppTest*);

    static int counter;

    static NoName compStaticField;
    NoName compField;

    static int getCount() { return counter; }
	template <class X> void fooTmplMember() const;

	struct {
		int inner_FieldOfNonameStruct;
	};

	struct Inner{
		int inner_FieldOfInnerStruct;
	} inner;
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

