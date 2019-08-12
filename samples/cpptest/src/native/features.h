
int plainCFreeFunction();
static inline void plainCInternalFunction();  // [Conceptual] should be mapped as internal fun or not eligible for binding at all

int g_Var;

struct PlainCStruct {
	int plainCField;
	struct {
		int innerCField;
	};
};

typedef struct PlainCStruct PlainCStructT;

using PlainCStructAlias = PlainCStruct;

void wrappingFun() {
	class NestedInFunction {
		int varInLocalClass;
	} var;  // local types shall be ignored
}

struct UnknownT;
UnknownT* cFunUnknownParams(const UnknownT*);


struct ForwardT;  // declaratuin
ForwardT* cFunForwardParams(const ForwardT*);  // decl

struct ForwardT {}; // definition
ForwardT* cFunForwardParams(const ForwardT*) { // def
	return new ForwardT();
}

namespace ns0 {
class clDeclaredInNS;
extern int varWithDefinition;
int varWithDefFirst = 99;
}


namespace ns0_alias = ns0;
class ns0_alias::clDeclaredInNS{};
extern int ns0_alias::varWithDefFirst;

using clDeclaredInNSAlias = ns0_alias::clDeclaredInNS;

// int ns0_alias::varInNSAlias; // illegal declaration
int ns0_alias::varWithDefinition = 21;

namespace ns {

int g_varInNS;

namespace {
	void funInInnerAnonNS();
}

namespace NestedNS {
	int funInNestedNS();
	int g_varInNestedNS;
}

namespace {
	void funInInnerAnonNS();
}

typedef class {
public:
	int noNameMember(int& iRef);
//	int noNameMember(const int& iRef);  need mangling
	static int noNameStaticFun(); // won't work
	int fieldInAnonClass;
	// static int s_fieldInAnonClass; not legal C++
} NoName;

enum EnumInNS {one, two, three};

enum class EnumClass : char { one, two, three};

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
//  virtual int foo(const CppTest*) const;

    static int counter;

    static NoName compStaticField;
    NoName compField;

    static int getCount() { return counter; }
	template <class X> void fooTmplMember() const;

	class Nested {
	public:
		int nestedFoo();
	};

private:
	CppTest* funPrivate() const;
	static int s_funPrivate();

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
/*
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

