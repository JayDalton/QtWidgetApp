#pragma once

//https://stackoverflow.com/questions/37197445/how-to-generalize-a-tree-structure-with-variant-visitor

#include <string>
#include <variant>
#include <filesystem>
#include <unordered_map>

namespace fs = std::filesystem;

class Writer;

using BaseValue = std::variant<
   bool, signed, double, std::string
>;

struct ParameterBase
{
   std::string m_ident;
   std::string m_label;
   BaseValue m_current;
   BaseValue m_maximum;
   BaseValue m_minimum;
   BaseValue m_default;
   BaseValue m_precise;
};

using ParameterImpl = std::unique_ptr<ParameterBase>;

struct BaseParameter /*: public ParameterBase*/
{
   BaseParameter();
   ~BaseParameter();

   void setValue(BaseValue value);
   BaseValue getValue() const;

   void Serialize(Writer& writer) const;

private:
   ParameterImpl m;
};

using ParameterList = std::vector<BaseParameter>;

struct ListParameter /*: public ParameterBase*/
{
   ListParameter();
   ~ListParameter();

   void Serialize(Writer& writer) const;

private:
   struct Impl;
   std::unique_ptr<Impl> m;
};

struct ConfigParameter
{
   std::string m_ident;
   std::string m_label;

   //void Serialize(Writer& writer) const;
};

using ParameterVariant = std::variant<BaseParameter, ListParameter>;
using ParameterMapping = std::unordered_map<std::string, ParameterVariant>;


// Codepage: UTF-8 (ÜüÖöÄäẞß)

