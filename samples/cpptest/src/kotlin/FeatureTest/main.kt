//package sample.spdlog
//package test

import kotlinx.cinterop.*
import platform.posix.*
import platform.posix.memcpy
import test.*

fun main() {
    val name = "You"
    println("Hey $name")
    val theStruct = interpretPointed<ns__CppTest>(ns__create().rawValue)
    theStruct.iPub = 21
    theStruct.foo(theStruct.ptr)

    testStatic()

    test0()
    testCtor()
    testCtor1()

    testCtor2()
//    testCtor3()
    test2()
}

fun testStatic() {
    println("ns__CppTest.s_fun() returns ${ns__CppTest.s_fun()}")
    println("ns__CppTest.s_fun() returns ${ns__CppTest.s_fun()}")
    println("ns__CppTest.s_fun() returns ${ns__CppTest.s_fun()}")
}

fun testCtor() {
    println("testCtor")
    val cxx = nativeHeap.alloc<ns__CppTest>() {
        memcpy(ptr, ns__create(), typeOf<ns__CppTest>().size.convert()) // use placement new here
    }
//    memcpy(cxx.ptr, ns__create(), typeOf<CppTest>().size.convert()) // use placement new here
    cxx.foo(null)
    nativeHeap.free(cxx)
}

fun testCtor1() {
    println("testCtor1: interpretPointed<ns__CppTest>(ns__CppTest.__create__().rawValue)")
    val theStruct = interpretPointed<ns__CppTest>(ns__CppTest.__create__().rawValue)
    theStruct.iPub = 33
    theStruct.foo(theStruct.ptr)

    println("testCtor1: ns__CppTest(ns__CppTest.__create__().rawValue)")
    val xs = ns__CppTest(ns__CppTest.__create__().rawValue)
    xs.foo(null)
    xs.foo(xs.ptr)

    println("testCtor1: ns__CppTest(ns__CppTest.__create__(1001).rawValue)")
    val x2 = ns__CppTest(ns__CppTest.__create__(1001).rawValue)
    x2.foo(null)
    x2.foo(x2.ptr)

}

fun testCtor2() {
    println("testCtor2: ns__CppTest(ns__create().rawValue)")
    val xs = ns__CppTest(ns__create().rawValue)
    xs.foo(null)
    xs.foo(xs.ptr)
}
/*
fun testCtor3() {
    println("testCtor3: MyStruct()")
    val xs = MyStruct()
    xs.foo()
}
*/
fun test0() {
    memScoped {
        val aStruct = alloc<ns__NoName>()
        aStruct.noNameMember()
    }
}

fun test2() {
    println("test2")
	val x = ns__bar(null)
//    val theS = interpretPointed<ns__CppTest>(ns__bar(null).rawValue)
//    theS.foo(null)

	println("x.useContents {iPub} = ${x.useContents {iPub}}" )
}
