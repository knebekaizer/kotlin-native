package org.jetbrains.kotlin.native.interop.indexer

import clang.*
import kotlinx.cinterop.*
import clang.CXTypeKind
import clang.CXCursorKind



class Entity(cursor: CValue<CXCursor>) {
    val usr = clang_getCursorUSR(cursor).convertAndDispose()
    val name = cursor.spelling
    val kind = cursor.kind
    val typeName = cursor.type.name
    val typeKind = cursor.type.kind
}

private fun CValue<CXCursor>.data() = Entity(this)

abstract class Node(val data: Entity, val parent: Container?) {
    open val name: String get() = data.name
    // debug:
    open val kindSpelling: String  get() = clang_getCursorKindSpelling(data.kind).convertAndDispose()
    open val typeSpelling: String  get() = clang_getTypeKindSpelling(data.typeKind).convertAndDispose()

    open fun accept(r: Render) : Render { return r.renderNode(this) }

}

abstract class Container(data: Entity, parent: Container?) : Node(data, parent) {
    val children: MutableList<Node> = mutableListOf()

    fun add(node: Node) { children.add(node) }
    override fun accept(r: Render) : Render { return r.renderContainer(this) }

}

open class Function(data: Entity, parent: Container) : Node(data, parent) {
}

class CxxMethod(data: Entity, parent: Container) : Function(data, parent) {

}

class CxxClass(data: Entity, parent: Container) : Container(data, parent) {

}

class Namespace(data: Entity, parent: Container) : Container(data, parent) {

}


/*
struct Tree;
struct Namespace;
struct Struct;
struct Function;
struct CXXMethod;
struct Constructor;
struct Var;
struct Field;
struct Enum;
*/

interface Render {
//    fun render(x: Node): Render
    fun renderNode(x: Node): Render
    fun renderContainer(x: Container): Render
    fun flush(): List<String>
}

class RenderLog : Render {
    override fun renderNode(c: Node): Render {
        val prefix = (List(indent) {"    "}).joinToString("")
        lines.add( "$prefix.${c.name} : ${c.kindSpelling}" )
        return this
    }

    override fun renderContainer(c: Container): Render {
        renderNode(c); // prolog
        c.children.forEach {
            indent += 1
            it.accept(this)
            indent -= 1
        }
        // no epilog
        return this;
    }

    override fun flush() = lines

    private var indent: Int = 0
    private val lines: MutableList<String> = mutableListOf()
}

class TreeParser(root: CValue<CXCursor>) : Container(root.data(), null) {

    init {
        visitChildren(root) {c, _ -> typesVisitor(c, this)}
   }

    private fun typesVisitor(cursor: CValue<CXCursor>, parent: Container): CXChildVisitResult {

        val entity = cursor.data()

        when (cursor.kind) {
            CXCursorKind.CXCursor_Namespace -> {
                val x = Namespace(entity, parent)
                visitChildren(cursor) {c, _ -> typesVisitor(c, x)}
                parent.add(x)
            }

            CXCursorKind.CXCursor_ClassDecl, CXCursorKind.CXCursor_StructDecl -> {
                val x = CxxClass(entity, parent)
                visitChildren(cursor) {c, _ -> typesVisitor(c, x)}
                parent.add(x)
            }

            CXCursorKind.CXCursor_UnionDecl -> {
                // TODO container
            }

            CXCursorKind.CXCursor_ClassTemplate -> {
                // TODO container
            }

            CXCursorKind.CXCursor_FunctionDecl -> {
                val x = Function(entity, parent)
                parent.add(x)
            }

            CXCursorKind.CXCursor_FunctionTemplate -> {
                // TODO
            }

            CXCursorKind.CXCursor_CXXMethod -> {
                // TODO
            }

            CXCursorKind.CXCursor_Constructor -> {
                // TODO
            }

            CXCursorKind.CXCursor_Destructor -> {
                // TODO
            }

            CXCursorKind.CXCursor_VarDecl -> {
                // TODO
            }

            CXCursorKind.CXCursor_EnumDecl -> {
                // TODO
            }

            CXCursorKind.CXCursor_FieldDecl -> {
                // TODO
            }

            else -> {
                return CXChildVisitResult.CXChildVisit_Recurse
            }
        }
        return CXChildVisitResult.CXChildVisit_Continue
}
}

