// @(#)root/core/utils:$Id: ClassSelectionRule.h 28529 2009-05-11 16:43:35Z pcanal $
// Author: Velislava Spasova September 2010

/*************************************************************************
 * Copyright (C) 1995-2011, Rene Brun, Fons Rademakers and al.           *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef R__CLASSSELECTIONRULE_H
#define R__CLASSSELECTIONRULE_H

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// ClassSelection                                                       //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "BaseSelectionRule.h"
#include "VariableSelectionRule.h"

#include <list>

class ClassSelectionRule: public BaseSelectionRule
{
private:
   std::list<VariableSelectionRule> fFieldSelectionRules;
   std::list<FunctionSelectionRule> fMethodSelectionRules;
   bool fIsInheritable;

   bool fPlus;        // for linkdef.h: true if we had '+' at the end of a class name
   bool fMinus;       // for linkdef.h: true if we had '-' or "-!" at the end of a class name
   bool fExclamation; // for linkdef.h: true if we had '!' at the end of a class name
   bool fRequestOnlyTClass;  // True if the user want the TClass intiliazer but *not* the interpreter meta data
   bool fRequestProtected; // Explicit request to be able to access protected member from the interpreter.
   bool fRequestPrivate;   // Explicit request to be able to access private member from the interpreter.
   
public:
   ClassSelectionRule(long index):
      BaseSelectionRule(index), fIsInheritable(false), fPlus(false), fMinus(false), fExclamation(false), fRequestOnlyTClass(false), fRequestProtected(false), fRequestPrivate(false) {}
   ClassSelectionRule(long index, bool inherit, ESelect sel, std::string attributeName, std::string attributeValue):
      BaseSelectionRule(index, sel, attributeName, attributeValue), fIsInheritable(inherit), fPlus(false), fMinus(false), fExclamation(false), fRequestOnlyTClass(false), fRequestProtected(false), fRequestPrivate(false) {}
   

   void AddFieldSelectionRule(VariableSelectionRule field); //adds entry to the filed selections list
   bool HasFieldSelectionRules() const;
   //const std::list<VariableSelectionRule>& getFieldSelectionRules(); //gets the field selections list
   const std::list<VariableSelectionRule>& GetFieldSelectionRules() const; //gets the field selections list
   
   void AddMethodSelectionRule(FunctionSelectionRule method); //adds entry to the method selections list
   bool HasMethodSelectionRules() const;
   //const std::list<FunctionSelectionRule>& getMethodSelectionRules(); //gets the method selections list
   const std::list<FunctionSelectionRule>& GetMethodSelectionRules() const; //gets the method selections list
   
   bool IsInheritable() const; //checks if the class selection rule is inheritable
   void SetInheritable(bool inherit); //sets the inheritance rule for the class

   bool HasPlus() const;
   void SetPlus(bool pl);

   bool HasMinus() const;
   void SetMinus(bool mn);

   bool HasExclamation() const;
   void SetExclamation(bool excl);
   
   void SetRequestOnlyTClass(bool val);
   void SetRequestProtected(bool val);
   void SetRequestPrivate(bool val);

   /* virtual */ bool RequestOnlyTClass() const;      // True if the user want the TClass intiliazer but *not* the interpreter meta data
   /* virtual */ bool RequestNoStreamer() const;      // Request no Streamer function in the dictionary
   /* virtual */ bool RequestNoInputOperator() const; // Request no generation on a default input operator by rootcint or the compiler.
   /* virtual */ bool RequestStreamerInfo() const;    // Request the ROOT 4+ I/O streamer
                 bool RequestProtected() const;
                 bool RequestPrivate() const;
};

#endif

