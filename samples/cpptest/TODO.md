- заменить memcpy на присваивание / copy ctor


* Improvements
	+ Language.CXX ?
	- Костыль в определнии языка (нужно ждя extern C) - надо использовать CursorLanguage)
	+ getMethod invokes getFunction with additional block (lambda) parameter


- Спорное решение про throw Error("Native interop types constructors must not be called directly")  

Conceptual
==========

0. Поля классов сейчас собираются через clang_Type_visitFields. Это нехорошо, потому что для методов и статических полей нет соответствующего API. Надо рефакторить и все делать однотипно - через visitChildren с разбором сразу всех возможных CXCursorKind. Пока оэто отложил, как следчтвие - не сделаны static fields (CXCursor_VarDecl)

0. Конструкторы-деструкторы надо переделать. Вопрос концептуальный, требует обсуждения. И это довольно большая работа. Моё предложение: надо различать 3 сущности: 
	- Аллоцированный объект: alloc + init (т.е. placement new) и парный к нему destroy (это this->~MyClass()), деаллокация автоматическая или ручная
	- Holder, владеющий указатель на объект, созданный в нативном хипе по new MyClass() и парный к нему delete. Это аналог std::unique_ptr. 
	- Non-owning holder без передачи ownership, т.е. невладеюший указатель. Освобождать не надо.
	- Можно замапить std::shared_ptr на котлин тип с acquire/release парой.
	
0. Надо замапить самые важные std типы: string, containers, smart pointers

0. Сейчас работа с C/C++ из котлина выглядит неестественно, многословная. Interop должен быть seamless. Без лишних interpretPointed, rawValue etc. Но это требует определенного пересмотра концепции (type matching)

0. Override С++ методов в котлине (callbacks) Можно сделать через обертки (генерим C++ класс-наследник у которого каждый метод перевызывает соответствующий котлинвский метод как plain C. Но хорошо бы генерить эти обертки только on demand, т.е. когда компилятор видит, что котлин хотел бы перегрузить соответствующий метод.

Design issues
-------------

0. В контейнере members может лежать IncompleteField. Это имело бы смысл, если Incomplrtr - такой lazy тип, который позже можно, например, зарезолвить. Но это не предусмотрено - так что зачем добавлять dummy, надо было просто пропустить

0. getArrayLength(type: ArrayType) сделана приватным методом StructStubBuilder'а. Должна быть или свободной функцией, или (лучше) extension: ArrayType.getArrayLength() 
	