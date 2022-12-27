#ifndef AOC_2022_TREE_H
#define AOC_2022_TREE_H

#include <stdlib.h>
#include "list.h"

typedef struct TreeNode {
    void *data;
    struct TreeNode *parent;
    List *children;
} TreeNode;

TreeNode *new_treenode(TreeNode *parent);

List *map_dfs(TreeNode *root, void *(*map_fn)(TreeNode *));
void append_treenode(TreeNode *parent, TreeNode *child);
void destroy_tree(TreeNode *root);

#endif //AOC_2022_TREE_H
