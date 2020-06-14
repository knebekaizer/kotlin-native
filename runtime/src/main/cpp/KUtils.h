//
// Created by Vladimir Ivanov on 14.06.2020.
//

#ifndef RUNTIME_KUTILS_H
#define RUNTIME_KUTILS_H

#include <string>
#include <iostream>

#include "Types.h"
#include "Natives.h"
//#include "utf8/unchecked.h"
#include "gsl/gsl"

#include <locale>
#include <codecvt>

using namespace gsl;
// namespace konan::std { // C++17
namespace konan {
namespace std {

using string = KStdString;

//string createCppString(KConstRef kref) {
//  // TODO: assert if not KString
//  if (kref) {
//    KString kstring = kref->array(); // not_null
//    const KChar *utf16 = CharArrayAddressOfElementAt(kstring, 0); // not_null
//    KStdString utf8;
//    utf8.reserve(kstring->count_);
//    utf8::unchecked::utf16to8(utf16, utf16 + kstring->count_, back_inserter(utf8));
//    return utf8;
//  }
//  return "";
//}

::std::string stdString(KConstRef kref) {
  // TODO: assert if not KString
  if (kref) {
    KString kstring = kref->array(); // not_null
    auto utf16 = reinterpret_cast<const char16_t*>(CharArrayAddressOfElementAt(kstring, 0)); // not_null
    ::std::wstring_convert<::std::codecvt_utf8_utf16<char16_t>,char16_t> convert;
    return convert.to_bytes(utf16, utf16 + kstring->count_);
  }
  return "";
}

// this of little use, as all ostreams are char-based
using ::std::u16string;  // TODO: use custom allocator

u16string toU16String(KConstRef kref) {
  // TODO: assert if not KString
  if (kref) {
    KString kstring = kref->array(); // not_null
    auto utf16 = reinterpret_cast<const char16_t*>(CharArrayAddressOfElementAt(kstring, 0)); // not_null
    return u16string(utf16, kstring->count_);
  }
  return u16string();
}


}} // namespace konan::std

/*
#include <string>
#include <locale>
#include <codecvt>

void convert_example() {
  //UTF-8 to UTF-16
  std::string source;
  //...
  std::wstring_convert<std::codecvt_utf8_utf16<char16_t>,char16_t> convert;
  std::u16string dest = convert.from_bytes(source);

  //UTF-16 to UTF-8
  std::u16string source;
  //...
  std::wstring_convert<std::codecvt_utf8_utf16<char16_t>,char16_t> convert;
  std::string dest = convert.to_bytes(source);
}
*/

#endif //RUNTIME_KUTILS_H
