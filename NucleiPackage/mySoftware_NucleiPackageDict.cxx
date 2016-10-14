// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME mySoftware_NucleiPackageDict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
#include "nucleon.h"
#include "nucleus.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *nucleus_Dictionary();
   static void nucleus_TClassManip(TClass*);
   static void *new_nucleus(void *p = 0);
   static void *newArray_nucleus(Long_t size, void *p);
   static void delete_nucleus(void *p);
   static void deleteArray_nucleus(void *p);
   static void destruct_nucleus(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::nucleus*)
   {
      ::nucleus *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::nucleus));
      static ::ROOT::TGenericClassInfo 
         instance("nucleus", "nucleus.h", 25,
                  typeid(::nucleus), DefineBehavior(ptr, ptr),
                  &nucleus_Dictionary, isa_proxy, 4,
                  sizeof(::nucleus) );
      instance.SetNew(&new_nucleus);
      instance.SetNewArray(&newArray_nucleus);
      instance.SetDelete(&delete_nucleus);
      instance.SetDeleteArray(&deleteArray_nucleus);
      instance.SetDestructor(&destruct_nucleus);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::nucleus*)
   {
      return GenerateInitInstanceLocal((::nucleus*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::nucleus*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *nucleus_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::nucleus*)0x0)->GetClass();
      nucleus_TClassManip(theClass);
   return theClass;
   }

   static void nucleus_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *nucleon_Dictionary();
   static void nucleon_TClassManip(TClass*);
   static void *new_nucleon(void *p = 0);
   static void *newArray_nucleon(Long_t size, void *p);
   static void delete_nucleon(void *p);
   static void deleteArray_nucleon(void *p);
   static void destruct_nucleon(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::nucleon*)
   {
      ::nucleon *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::nucleon));
      static ::ROOT::TGenericClassInfo 
         instance("nucleon", "nucleon.h", 26,
                  typeid(::nucleon), DefineBehavior(ptr, ptr),
                  &nucleon_Dictionary, isa_proxy, 4,
                  sizeof(::nucleon) );
      instance.SetNew(&new_nucleon);
      instance.SetNewArray(&newArray_nucleon);
      instance.SetDelete(&delete_nucleon);
      instance.SetDeleteArray(&deleteArray_nucleon);
      instance.SetDestructor(&destruct_nucleon);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::nucleon*)
   {
      return GenerateInitInstanceLocal((::nucleon*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::nucleon*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *nucleon_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::nucleon*)0x0)->GetClass();
      nucleon_TClassManip(theClass);
   return theClass;
   }

   static void nucleon_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_nucleus(void *p) {
      return  p ? new(p) ::nucleus : new ::nucleus;
   }
   static void *newArray_nucleus(Long_t nElements, void *p) {
      return p ? new(p) ::nucleus[nElements] : new ::nucleus[nElements];
   }
   // Wrapper around operator delete
   static void delete_nucleus(void *p) {
      delete ((::nucleus*)p);
   }
   static void deleteArray_nucleus(void *p) {
      delete [] ((::nucleus*)p);
   }
   static void destruct_nucleus(void *p) {
      typedef ::nucleus current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::nucleus

namespace ROOT {
   // Wrappers around operator new
   static void *new_nucleon(void *p) {
      return  p ? new(p) ::nucleon : new ::nucleon;
   }
   static void *newArray_nucleon(Long_t nElements, void *p) {
      return p ? new(p) ::nucleon[nElements] : new ::nucleon[nElements];
   }
   // Wrapper around operator delete
   static void delete_nucleon(void *p) {
      delete ((::nucleon*)p);
   }
   static void deleteArray_nucleon(void *p) {
      delete [] ((::nucleon*)p);
   }
   static void destruct_nucleon(void *p) {
      typedef ::nucleon current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::nucleon

namespace ROOT {
   static TClass *vectorlEnucleongR_Dictionary();
   static void vectorlEnucleongR_TClassManip(TClass*);
   static void *new_vectorlEnucleongR(void *p = 0);
   static void *newArray_vectorlEnucleongR(Long_t size, void *p);
   static void delete_vectorlEnucleongR(void *p);
   static void deleteArray_vectorlEnucleongR(void *p);
   static void destruct_vectorlEnucleongR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<nucleon>*)
   {
      vector<nucleon> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<nucleon>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<nucleon>", -2, "vector", 457,
                  typeid(vector<nucleon>), DefineBehavior(ptr, ptr),
                  &vectorlEnucleongR_Dictionary, isa_proxy, 0,
                  sizeof(vector<nucleon>) );
      instance.SetNew(&new_vectorlEnucleongR);
      instance.SetNewArray(&newArray_vectorlEnucleongR);
      instance.SetDelete(&delete_vectorlEnucleongR);
      instance.SetDeleteArray(&deleteArray_vectorlEnucleongR);
      instance.SetDestructor(&destruct_vectorlEnucleongR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<nucleon> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<nucleon>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEnucleongR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<nucleon>*)0x0)->GetClass();
      vectorlEnucleongR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEnucleongR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEnucleongR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<nucleon> : new vector<nucleon>;
   }
   static void *newArray_vectorlEnucleongR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<nucleon>[nElements] : new vector<nucleon>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEnucleongR(void *p) {
      delete ((vector<nucleon>*)p);
   }
   static void deleteArray_vectorlEnucleongR(void *p) {
      delete [] ((vector<nucleon>*)p);
   }
   static void destruct_vectorlEnucleongR(void *p) {
      typedef vector<nucleon> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<nucleon>

namespace ROOT {
   static TClass *vectorlETVector3gR_Dictionary();
   static void vectorlETVector3gR_TClassManip(TClass*);
   static void *new_vectorlETVector3gR(void *p = 0);
   static void *newArray_vectorlETVector3gR(Long_t size, void *p);
   static void delete_vectorlETVector3gR(void *p);
   static void deleteArray_vectorlETVector3gR(void *p);
   static void destruct_vectorlETVector3gR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TVector3>*)
   {
      vector<TVector3> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TVector3>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TVector3>", -2, "vector", 457,
                  typeid(vector<TVector3>), DefineBehavior(ptr, ptr),
                  &vectorlETVector3gR_Dictionary, isa_proxy, 4,
                  sizeof(vector<TVector3>) );
      instance.SetNew(&new_vectorlETVector3gR);
      instance.SetNewArray(&newArray_vectorlETVector3gR);
      instance.SetDelete(&delete_vectorlETVector3gR);
      instance.SetDeleteArray(&deleteArray_vectorlETVector3gR);
      instance.SetDestructor(&destruct_vectorlETVector3gR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TVector3> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<TVector3>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETVector3gR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<TVector3>*)0x0)->GetClass();
      vectorlETVector3gR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETVector3gR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETVector3gR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<TVector3> : new vector<TVector3>;
   }
   static void *newArray_vectorlETVector3gR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<TVector3>[nElements] : new vector<TVector3>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETVector3gR(void *p) {
      delete ((vector<TVector3>*)p);
   }
   static void deleteArray_vectorlETVector3gR(void *p) {
      delete [] ((vector<TVector3>*)p);
   }
   static void destruct_vectorlETVector3gR(void *p) {
      typedef vector<TVector3> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<TVector3>

namespace ROOT {
   static TClass *vectorlETLorentzVectorgR_Dictionary();
   static void vectorlETLorentzVectorgR_TClassManip(TClass*);
   static void *new_vectorlETLorentzVectorgR(void *p = 0);
   static void *newArray_vectorlETLorentzVectorgR(Long_t size, void *p);
   static void delete_vectorlETLorentzVectorgR(void *p);
   static void deleteArray_vectorlETLorentzVectorgR(void *p);
   static void destruct_vectorlETLorentzVectorgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TLorentzVector>*)
   {
      vector<TLorentzVector> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TLorentzVector>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TLorentzVector>", -2, "vector", 457,
                  typeid(vector<TLorentzVector>), DefineBehavior(ptr, ptr),
                  &vectorlETLorentzVectorgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<TLorentzVector>) );
      instance.SetNew(&new_vectorlETLorentzVectorgR);
      instance.SetNewArray(&newArray_vectorlETLorentzVectorgR);
      instance.SetDelete(&delete_vectorlETLorentzVectorgR);
      instance.SetDeleteArray(&deleteArray_vectorlETLorentzVectorgR);
      instance.SetDestructor(&destruct_vectorlETLorentzVectorgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TLorentzVector> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<TLorentzVector>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETLorentzVectorgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<TLorentzVector>*)0x0)->GetClass();
      vectorlETLorentzVectorgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETLorentzVectorgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETLorentzVectorgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<TLorentzVector> : new vector<TLorentzVector>;
   }
   static void *newArray_vectorlETLorentzVectorgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<TLorentzVector>[nElements] : new vector<TLorentzVector>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETLorentzVectorgR(void *p) {
      delete ((vector<TLorentzVector>*)p);
   }
   static void deleteArray_vectorlETLorentzVectorgR(void *p) {
      delete [] ((vector<TLorentzVector>*)p);
   }
   static void destruct_vectorlETLorentzVectorgR(void *p) {
      typedef vector<TLorentzVector> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<TLorentzVector>

namespace {
  void TriggerDictionaryInitialization_libmySoftware_NucleiPackage_Impl() {
    static const char* headers[] = {
"nucleon.h",
"nucleus.h",
0
    };
    static const char* includePaths[] = {
"/Users/erezcohen/larlite/UserDev/mySoftware/MySoftwarePackage",
"/Users/erezcohen/root6/root-6.04.10/include",
"/Users/erezcohen/larlite/UserDev/mySoftware/NucleiPackage/",
0
    };
    static const char* fwdDeclCode = 
R"DICTFWDDCLS(
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$nucleon.h")))  TVector3;
namespace std{inline namespace __1{template <class _Tp> class __attribute__((annotate("$clingAutoload$string")))  allocator;
}}
class __attribute__((annotate("$clingAutoload$nucleon.h")))  TLorentzVector;
class __attribute__((annotate("$clingAutoload$nucleus.h")))  nucleus;
class __attribute__((annotate("$clingAutoload$nucleon.h")))  nucleon;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "nucleon.h"
#include "nucleus.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"nucleon", payloadCode, "@",
"nucleus", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libmySoftware_NucleiPackage",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libmySoftware_NucleiPackage_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libmySoftware_NucleiPackage_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libmySoftware_NucleiPackage() {
  TriggerDictionaryInitialization_libmySoftware_NucleiPackage_Impl();
}
