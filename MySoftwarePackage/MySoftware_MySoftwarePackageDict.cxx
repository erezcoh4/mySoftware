// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME MySoftware_MySoftwarePackageDict

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
#include "TAnalysis.h"
#include "TCalculations.h"
#include "TPlots.h"
#include "myIncludes.h"
#include "ppElastic.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *TPlots_Dictionary();
   static void TPlots_TClassManip(TClass*);
   static void *new_TPlots(void *p = 0);
   static void *newArray_TPlots(Long_t size, void *p);
   static void delete_TPlots(void *p);
   static void deleteArray_TPlots(void *p);
   static void destruct_TPlots(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TPlots*)
   {
      ::TPlots *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::TPlots));
      static ::ROOT::TGenericClassInfo 
         instance("TPlots", "TPlots.h", 8,
                  typeid(::TPlots), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &TPlots_Dictionary, isa_proxy, 4,
                  sizeof(::TPlots) );
      instance.SetNew(&new_TPlots);
      instance.SetNewArray(&newArray_TPlots);
      instance.SetDelete(&delete_TPlots);
      instance.SetDeleteArray(&deleteArray_TPlots);
      instance.SetDestructor(&destruct_TPlots);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TPlots*)
   {
      return GenerateInitInstanceLocal((::TPlots*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TPlots*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *TPlots_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::TPlots*)0x0)->GetClass();
      TPlots_TClassManip(theClass);
   return theClass;
   }

   static void TPlots_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *TAnalysis_Dictionary();
   static void TAnalysis_TClassManip(TClass*);
   static void *new_TAnalysis(void *p = 0);
   static void *newArray_TAnalysis(Long_t size, void *p);
   static void delete_TAnalysis(void *p);
   static void deleteArray_TAnalysis(void *p);
   static void destruct_TAnalysis(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TAnalysis*)
   {
      ::TAnalysis *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::TAnalysis));
      static ::ROOT::TGenericClassInfo 
         instance("TAnalysis", "TAnalysis.h", 17,
                  typeid(::TAnalysis), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &TAnalysis_Dictionary, isa_proxy, 4,
                  sizeof(::TAnalysis) );
      instance.SetNew(&new_TAnalysis);
      instance.SetNewArray(&newArray_TAnalysis);
      instance.SetDelete(&delete_TAnalysis);
      instance.SetDeleteArray(&deleteArray_TAnalysis);
      instance.SetDestructor(&destruct_TAnalysis);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TAnalysis*)
   {
      return GenerateInitInstanceLocal((::TAnalysis*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TAnalysis*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *TAnalysis_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::TAnalysis*)0x0)->GetClass();
      TAnalysis_TClassManip(theClass);
   return theClass;
   }

   static void TAnalysis_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *TCalculations_Dictionary();
   static void TCalculations_TClassManip(TClass*);
   static void *new_TCalculations(void *p = 0);
   static void *newArray_TCalculations(Long_t size, void *p);
   static void delete_TCalculations(void *p);
   static void deleteArray_TCalculations(void *p);
   static void destruct_TCalculations(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TCalculations*)
   {
      ::TCalculations *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::TCalculations));
      static ::ROOT::TGenericClassInfo 
         instance("TCalculations", "TCalculations.h", 55,
                  typeid(::TCalculations), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &TCalculations_Dictionary, isa_proxy, 4,
                  sizeof(::TCalculations) );
      instance.SetNew(&new_TCalculations);
      instance.SetNewArray(&newArray_TCalculations);
      instance.SetDelete(&delete_TCalculations);
      instance.SetDeleteArray(&deleteArray_TCalculations);
      instance.SetDestructor(&destruct_TCalculations);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TCalculations*)
   {
      return GenerateInitInstanceLocal((::TCalculations*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TCalculations*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *TCalculations_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::TCalculations*)0x0)->GetClass();
      TCalculations_TClassManip(theClass);
   return theClass;
   }

   static void TCalculations_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *ppElastic_Dictionary();
   static void ppElastic_TClassManip(TClass*);
   static void *new_ppElastic(void *p = 0);
   static void *newArray_ppElastic(Long_t size, void *p);
   static void delete_ppElastic(void *p);
   static void deleteArray_ppElastic(void *p);
   static void destruct_ppElastic(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::ppElastic*)
   {
      ::ppElastic *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::ppElastic));
      static ::ROOT::TGenericClassInfo 
         instance("ppElastic", "ppElastic.h", 27,
                  typeid(::ppElastic), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &ppElastic_Dictionary, isa_proxy, 4,
                  sizeof(::ppElastic) );
      instance.SetNew(&new_ppElastic);
      instance.SetNewArray(&newArray_ppElastic);
      instance.SetDelete(&delete_ppElastic);
      instance.SetDeleteArray(&deleteArray_ppElastic);
      instance.SetDestructor(&destruct_ppElastic);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::ppElastic*)
   {
      return GenerateInitInstanceLocal((::ppElastic*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::ppElastic*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *ppElastic_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::ppElastic*)0x0)->GetClass();
      ppElastic_TClassManip(theClass);
   return theClass;
   }

   static void ppElastic_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *myIncludes_Dictionary();
   static void myIncludes_TClassManip(TClass*);
   static void *new_myIncludes(void *p = 0);
   static void *newArray_myIncludes(Long_t size, void *p);
   static void delete_myIncludes(void *p);
   static void deleteArray_myIncludes(void *p);
   static void destruct_myIncludes(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::myIncludes*)
   {
      ::myIncludes *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::myIncludes));
      static ::ROOT::TGenericClassInfo 
         instance("myIncludes", "myIncludes.h", 124,
                  typeid(::myIncludes), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &myIncludes_Dictionary, isa_proxy, 4,
                  sizeof(::myIncludes) );
      instance.SetNew(&new_myIncludes);
      instance.SetNewArray(&newArray_myIncludes);
      instance.SetDelete(&delete_myIncludes);
      instance.SetDeleteArray(&deleteArray_myIncludes);
      instance.SetDestructor(&destruct_myIncludes);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::myIncludes*)
   {
      return GenerateInitInstanceLocal((::myIncludes*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::myIncludes*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *myIncludes_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::myIncludes*)0x0)->GetClass();
      myIncludes_TClassManip(theClass);
   return theClass;
   }

   static void myIncludes_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_TPlots(void *p) {
      return  p ? new(p) ::TPlots : new ::TPlots;
   }
   static void *newArray_TPlots(Long_t nElements, void *p) {
      return p ? new(p) ::TPlots[nElements] : new ::TPlots[nElements];
   }
   // Wrapper around operator delete
   static void delete_TPlots(void *p) {
      delete ((::TPlots*)p);
   }
   static void deleteArray_TPlots(void *p) {
      delete [] ((::TPlots*)p);
   }
   static void destruct_TPlots(void *p) {
      typedef ::TPlots current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TPlots

namespace ROOT {
   // Wrappers around operator new
   static void *new_TAnalysis(void *p) {
      return  p ? new(p) ::TAnalysis : new ::TAnalysis;
   }
   static void *newArray_TAnalysis(Long_t nElements, void *p) {
      return p ? new(p) ::TAnalysis[nElements] : new ::TAnalysis[nElements];
   }
   // Wrapper around operator delete
   static void delete_TAnalysis(void *p) {
      delete ((::TAnalysis*)p);
   }
   static void deleteArray_TAnalysis(void *p) {
      delete [] ((::TAnalysis*)p);
   }
   static void destruct_TAnalysis(void *p) {
      typedef ::TAnalysis current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TAnalysis

namespace ROOT {
   // Wrappers around operator new
   static void *new_TCalculations(void *p) {
      return  p ? new(p) ::TCalculations : new ::TCalculations;
   }
   static void *newArray_TCalculations(Long_t nElements, void *p) {
      return p ? new(p) ::TCalculations[nElements] : new ::TCalculations[nElements];
   }
   // Wrapper around operator delete
   static void delete_TCalculations(void *p) {
      delete ((::TCalculations*)p);
   }
   static void deleteArray_TCalculations(void *p) {
      delete [] ((::TCalculations*)p);
   }
   static void destruct_TCalculations(void *p) {
      typedef ::TCalculations current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TCalculations

namespace ROOT {
   // Wrappers around operator new
   static void *new_ppElastic(void *p) {
      return  p ? new(p) ::ppElastic : new ::ppElastic;
   }
   static void *newArray_ppElastic(Long_t nElements, void *p) {
      return p ? new(p) ::ppElastic[nElements] : new ::ppElastic[nElements];
   }
   // Wrapper around operator delete
   static void delete_ppElastic(void *p) {
      delete ((::ppElastic*)p);
   }
   static void deleteArray_ppElastic(void *p) {
      delete [] ((::ppElastic*)p);
   }
   static void destruct_ppElastic(void *p) {
      typedef ::ppElastic current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::ppElastic

namespace ROOT {
   // Wrappers around operator new
   static void *new_myIncludes(void *p) {
      return  p ? new(p) ::myIncludes : new ::myIncludes;
   }
   static void *newArray_myIncludes(Long_t nElements, void *p) {
      return p ? new(p) ::myIncludes[nElements] : new ::myIncludes[nElements];
   }
   // Wrapper around operator delete
   static void delete_myIncludes(void *p) {
      delete ((::myIncludes*)p);
   }
   static void deleteArray_myIncludes(void *p) {
      delete [] ((::myIncludes*)p);
   }
   static void destruct_myIncludes(void *p) {
      typedef ::myIncludes current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::myIncludes

namespace ROOT {
   static TClass *vectorlEdoublegR_Dictionary();
   static void vectorlEdoublegR_TClassManip(TClass*);
   static void *new_vectorlEdoublegR(void *p = 0);
   static void *newArray_vectorlEdoublegR(Long_t size, void *p);
   static void delete_vectorlEdoublegR(void *p);
   static void deleteArray_vectorlEdoublegR(void *p);
   static void destruct_vectorlEdoublegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<double>*)
   {
      vector<double> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<double>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<double>", -2, "vector", 477,
                  typeid(vector<double>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEdoublegR_Dictionary, isa_proxy, 0,
                  sizeof(vector<double>) );
      instance.SetNew(&new_vectorlEdoublegR);
      instance.SetNewArray(&newArray_vectorlEdoublegR);
      instance.SetDelete(&delete_vectorlEdoublegR);
      instance.SetDeleteArray(&deleteArray_vectorlEdoublegR);
      instance.SetDestructor(&destruct_vectorlEdoublegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<double> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<double>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEdoublegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<double>*)0x0)->GetClass();
      vectorlEdoublegR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEdoublegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEdoublegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<double> : new vector<double>;
   }
   static void *newArray_vectorlEdoublegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<double>[nElements] : new vector<double>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEdoublegR(void *p) {
      delete ((vector<double>*)p);
   }
   static void deleteArray_vectorlEdoublegR(void *p) {
      delete [] ((vector<double>*)p);
   }
   static void destruct_vectorlEdoublegR(void *p) {
      typedef vector<double> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<double>

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
         instance("vector<TVector3>", -2, "vector", 477,
                  typeid(vector<TVector3>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
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
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TVector3> : new vector<TVector3>;
   }
   static void *newArray_vectorlETVector3gR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TVector3>[nElements] : new vector<TVector3>[nElements];
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
         instance("vector<TLorentzVector>", -2, "vector", 477,
                  typeid(vector<TLorentzVector>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
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
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TLorentzVector> : new vector<TLorentzVector>;
   }
   static void *newArray_vectorlETLorentzVectorgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TLorentzVector>[nElements] : new vector<TLorentzVector>[nElements];
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
  void TriggerDictionaryInitialization_libMySoftware_MySoftwarePackage_Impl() {
    static const char* headers[] = {
"TAnalysis.h",
"TCalculations.h",
"TPlots.h",
"myIncludes.h",
"ppElastic.h",
0
    };
    static const char* includePaths[] = {
"/usr/local/Cellar/root6/6.06.02/include/root",
"/Users/erezcohen/larlite/UserDev/mySoftware/MySoftwarePackage/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "libMySoftware_MySoftwarePackage dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$TAnalysis.h")))  TVector3;
namespace std{inline namespace __1{template <class _Tp> class __attribute__((annotate("$clingAutoload$string")))  allocator;
}}
class __attribute__((annotate("$clingAutoload$TAnalysis.h")))  TLorentzVector;
class __attribute__((annotate("$clingAutoload$TAnalysis.h")))  TPlots;
class __attribute__((annotate("$clingAutoload$TAnalysis.h")))  TAnalysis;
class __attribute__((annotate("$clingAutoload$TCalculations.h")))  TCalculations;
class __attribute__((annotate("$clingAutoload$ppElastic.h")))  ppElastic;
class __attribute__((annotate("$clingAutoload$TAnalysis.h")))  myIncludes;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "libMySoftware_MySoftwarePackage dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "TAnalysis.h"
#include "TCalculations.h"
#include "TPlots.h"
#include "myIncludes.h"
#include "ppElastic.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"TAnalysis", payloadCode, "@",
"TCalculations", payloadCode, "@",
"TPlots", payloadCode, "@",
"myIncludes", payloadCode, "@",
"ppElastic", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libMySoftware_MySoftwarePackage",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libMySoftware_MySoftwarePackage_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libMySoftware_MySoftwarePackage_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libMySoftware_MySoftwarePackage() {
  TriggerDictionaryInitialization_libMySoftware_MySoftwarePackage_Impl();
}
