#pragma once

//https://stackoverflow.com/questions/37197445/how-to-generalize-a-tree-structure-with-variant-visitor

#include <string>
#include <variant>
#include <filesystem>
#include <unordered_map>

#include "ValueVisitor.h"

namespace fs = std::filesystem;

#pragma region BinaryTree

template <typename LeafData>
struct BinaryTree;

template <typename LeafData>
struct BinaryTreeBranch
{
   std::shared_ptr<BinaryTree<LeafData>> left;
   std::shared_ptr<BinaryTree<LeafData>> right;
};

template <typename LeafData>
struct BinaryTree
{
   using Value = std::variant<LeafData, BinaryTreeBranch<LeafData>>;
   Value value;
};

#pragma endregion

struct BaseValue
{
   using Value = std::variant<bool, signed, double, std::string, std::vector<BaseValue>>;
   Value value;
};


//using BaseValue = std::variant<
//   bool, signed, double, std::string, std::vector<BaseValue>
//>;



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

class Writer;

struct BaseParameter /*: public ParameterBase*/
{
   BaseParameter();
   ~BaseParameter();

   BaseValue getValue() const;
   void setValue(BaseValue value);

   void Serialize(Writer& writer) const;

private:
   ParameterImpl m;
};

using ParameterList = std::vector<BaseParameter>;

struct ListParameter /*: public ParameterBase*/
{
   ListParameter();
   ~ListParameter();

   BaseValue getValue() const;
   void setValue(BaseValue value);

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

Visitor GetCurrentVisitor{
	[](const BaseParameter& p) { return p.getValue(); },
	[](const ListParameter& p) { return p.getValue(); },
};


// Codepage: UTF-8 (ÜüÖöÄäẞß)

