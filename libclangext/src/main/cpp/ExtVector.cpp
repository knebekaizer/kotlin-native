/*
 * Copyright 2010-2017 JetBrains s.r.o.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

//#include "ExtVector.h"

#include <cassert>

//#include <clang/AST/Attr.h>
//#include <clang/AST/DeclObjC.h>
//#include <clang/Frontend/ASTUnit.h>
#include "clang-c/ext.h"

//using namespace clang;

namespace clng {

/// These types are POD and bitwise compatible with corresponding clang:: types.

struct PointerIntPair {
	intptr_t Value = 0;
};

struct QualType {
	PointerIntPair Value; // llvm::PointerIntPair<llvm::PointerUnion<const Type *, const ExtQuals *>, Qualifiers::FastWidth> Value;
};

struct Type;
struct ExtQualsTypeCommonBase {
	Type * BaseType;
	QualType CanonicalType;
};

struct TypeBitfields {
	/// TypeClass bitfield - Enum that specifies what subclass this belongs to.
	enum { NumTypeBits = 18 };
	union {
		unsigned TC : 8;

		struct {
			unsigned : NumTypeBits;
			unsigned VecKind : 3;

			 /// The number of elements in the vector.
			unsigned NumElements : 29 - NumTypeBits;
		} VectorBits;
	};

 };

struct Type : public ExtQualsTypeCommonBase {
    union {
		TypeBitfields TypeBits;
	};
//	TypeClass getTypeClass() const { return static_cast<TypeClass>(TypeBits.TC); }
	int getTypeClass() const { return static_cast<int>(TypeBits.TC); }
	void setTypeClass(int tc) {
	//	auto offset = (intptr_t)&TypeBits - (intptr_t)this;
	//	((uint8_t*)this)[offset] = tc & 0xff;
		TypeBits.TC = tc & 0xff;
	}
};

bool tryCast2Vector(CXType type) {
	type = clang_getCanonicalType(type); // always safe

	clng::ExtQualsTypeCommonBase *base = reinterpret_cast<clng::Type *>( reinterpret_cast<intptr_t>(type.data[0]) & ~0xf );

	auto& typeClass_ = *reinterpret_cast<uint8_t *>(static_cast<ExtQualsTypeCommonBase*>(base->BaseType) + 1);
	if (typeClass_ == 15) { // ExtVector
		typeClass_ = 13;
		return true;
	}
	return false;
}

} // namesoace clng

extern "C" int tryCastToVector(CXType type);

int tryCastToVector(CXType type) {
	static_assert(CINDEX_VERSION >= 50, "Unexpected obsolete libclang version");
	static_assert(CINDEX_VERSION < 59, "Use CXType_ExtVector for this libclang version");

	type = clang_getCanonicalType(type); // always safe

	clng::ExtQualsTypeCommonBase* base = reinterpret_cast<clng::Type*>( reinterpret_cast<intptr_t>(type.data[0]) & ~0xf );
	clng::Type* baseType = base->BaseType; // = * reinterpret_cast<clang::Type**>( type.data[0]) & ~0xf )

	// extra <<
	auto canonType = reinterpret_cast<clng::Type*>(baseType->CanonicalType.Value.Value & ~0xf);
	auto canonTypeClass = canonType->BaseType->getTypeClass();
//	TraceX(canonTypeClass);
	if (canonTypeClass == 15 || canonTypeClass == 13) {
//		Trace2(canonType->BaseType->TypeBits.VectorBits.VecKind, canonType->BaseType->TypeBits.VectorBits.NumElements);
	}
	// << end

	if (baseType->getTypeClass() == 15) { // ExtVector
		baseType->setTypeClass(13);
		return true;
	}
	return false;
}
