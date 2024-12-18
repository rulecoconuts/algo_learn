#pragma once
#include <optional>
#include "b_tree_node.h"

/// @brief This class is a composable way of defining node validation rules
/// @tparam T
template <typename T>
class BTreeNodeValidator
{
public:
    /// @brief Check if the number of keys in a node is valid
    /// @param maxKeys maximum number of keys allowed. The minimum number of keys allowed will likely be derived from this as well
    /// @param node
    /// @param isRoot
    /// @return
    std::optional<std::string> validateKeyCount(int maxKeys, const BTreeNode<T> &node, bool isRoot);

    /// @brief Check if the number of children in a node is valid
    /// @param maxKeys
    /// @param node
    /// @param isRoot
    /// @return
    std::optional<std::string> validateChildrenCount(int maxKeys, const BTreeNode<T> &node, bool isRoot);
};