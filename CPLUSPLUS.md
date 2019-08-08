Current status
==============

Limited C++ interop provided via plain C wrappers and cinterop mechanism.

Usage: add `compilerOpts = -x c++`' to .def file or as a command line option.

C++ features
------------

* C++ class:
  + Virtual and non-virtual methods
  * Static methods mapped as companion ones
  * Fields
  * Static fields as companion ones
  * Constructors are mapped to `__init__(args)` companion methods
  * Destructor is mapped to `__destroy__(this)` companion method
* LValueReference parameters and return value internally handled as pointers
* Namespaces provided as simple mangled class name. It works but awfully ugly. Shall be fixed by mapping to packages.
* Nested C++ classes: same as namespaces, simple mangling. Shall be fixed.
* Access modifiers: only public members exposed to Kotlin. Anonymous namespaces and entities with internal linkage are silently ignored.

Limitations
-----------
* Operators are not supported yet (silently ignored)
* LVReference mapper to CPointer<T>? which is incorrect (should be notNull). This may cause segmentation fault in case of null is sent as a parameter. TBD
* const overload not supported and cause compilation error. That is, two class methods with the same signature (`const` and `non-const`) can't be compiled. The same for function parameters: if two functions differ only in `const*` modifier of parameter, this will cause "conflicting overloads" error. TBD.
* C++ lambda type is not supported yet.
* Member pointer, member referencem, rvalue reference and other types are not wupported.
* Inheritance is not implemented yet. C++-style callbacks (overriding virtual method in Kotlin) may be implemented via plain C bridge (this can be done by hand as a workariund). TBD.

Known issues
------------

* Templates cause Kotlin compilation error. Fix requires severe refactoring of existing cinterop. TBD.
	+ template member functions are silently ignored, no errors.