// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIudIhomedItrottardIAnalysisdIhallc_replay_kaonltdIUTIL_KAONLTdIscripts_KaonYielddIKaonYield_C_ACLiC_dict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "/u/home/trottar/Analysis/hallc_replay_kaonlt/UTIL_KAONLT/scripts_KaonYield/./KaonYield.C"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_KaonYield(void *p = 0);
   static void *newArray_KaonYield(Long_t size, void *p);
   static void delete_KaonYield(void *p);
   static void deleteArray_KaonYield(void *p);
   static void destruct_KaonYield(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KaonYield*)
   {
      ::KaonYield *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KaonYield >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KaonYield", ::KaonYield::Class_Version(), "KaonYield.h", 28,
                  typeid(::KaonYield), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KaonYield::Dictionary, isa_proxy, 4,
                  sizeof(::KaonYield) );
      instance.SetNew(&new_KaonYield);
      instance.SetNewArray(&newArray_KaonYield);
      instance.SetDelete(&delete_KaonYield);
      instance.SetDeleteArray(&deleteArray_KaonYield);
      instance.SetDestructor(&destruct_KaonYield);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KaonYield*)
   {
      return GenerateInitInstanceLocal((::KaonYield*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::KaonYield*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr KaonYield::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KaonYield::Class_Name()
{
   return "KaonYield";
}

//______________________________________________________________________________
const char *KaonYield::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KaonYield*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KaonYield::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KaonYield*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KaonYield::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KaonYield*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KaonYield::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KaonYield*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void KaonYield::Streamer(TBuffer &R__b)
{
   // Stream an object of class KaonYield.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KaonYield::Class(),this);
   } else {
      R__b.WriteClassBuffer(KaonYield::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KaonYield(void *p) {
      return  p ? new(p) ::KaonYield : new ::KaonYield;
   }
   static void *newArray_KaonYield(Long_t nElements, void *p) {
      return p ? new(p) ::KaonYield[nElements] : new ::KaonYield[nElements];
   }
   // Wrapper around operator delete
   static void delete_KaonYield(void *p) {
      delete ((::KaonYield*)p);
   }
   static void deleteArray_KaonYield(void *p) {
      delete [] ((::KaonYield*)p);
   }
   static void destruct_KaonYield(void *p) {
      typedef ::KaonYield current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KaonYield

namespace {
  void TriggerDictionaryInitialization_KaonYield_C_ACLiC_dict_Impl() {
    static const char* headers[] = {
"./KaonYield.C",
0
    };
    static const char* includePaths[] = {
"/u/site/12gev_phys/2.0/Linux_CentOS7.2.1511-x86_64-gcc5.2.0/root/6.08.00/include",
"/u/site/12gev_phys/2.0/Linux_CentOS7.2.1511-x86_64-gcc5.2.0/root/6.08.00/etc",
"/u/site/12gev_phys/2.0/Linux_CentOS7.2.1511-x86_64-gcc5.2.0/root/6.08.00/etc/cling",
"/u/site/12gev_phys/2.0/Linux_CentOS7.2.1511-x86_64-gcc5.2.0/root/6.08.00/include",
"/u/apps/gcc/5.2.0/install/bin/../lib/gcc/x86_64-unknown-linux-gnu/5.2.0/../../../../include/c++/5.2.0",
"/u/apps/gcc/5.2.0/install/bin/../lib/gcc/x86_64-unknown-linux-gnu/5.2.0/../../../../include/c++/5.2.0/x86_64-unknown-linux-gnu",
"/u/apps/gcc/5.2.0/install/bin/../lib/gcc/x86_64-unknown-linux-gnu/5.2.0/../../../../include/c++/5.2.0/backward",
"/usr/include/freetype2",
"/u/site/12gev_phys/2.0/Linux_CentOS7.2.1511-x86_64-gcc5.2.0/root/6.08.00/include",
"/u/home/trottar/Analysis/hallc_replay_kaonlt/UTIL_KAONLT/scripts_KaonYield/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "KaonYield_C_ACLiC_dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate(R"ATTRDUMP(file_name@@@/u/home/trottar/Analysis/hallc_replay_kaonlt/UTIL_KAONLT/scripts_KaonYield/./KaonYield.h)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$./KaonYield.C")))  KaonYield;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "KaonYield_C_ACLiC_dict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif
#ifndef __ACLIC__
  #define __ACLIC__ 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "./KaonYield.C"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"", payloadCode, "@",
"KaonYield", payloadCode, "@",
"KaonYield::fgIsA", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("KaonYield_C_ACLiC_dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_KaonYield_C_ACLiC_dict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_KaonYield_C_ACLiC_dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_KaonYield_C_ACLiC_dict() {
  TriggerDictionaryInitialization_KaonYield_C_ACLiC_dict_Impl();
}
