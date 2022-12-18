#include "tree.h"

TreeNode *new_treenode(TreeNode *parent) {
    TreeNode *node = malloc(sizeof(*node));
    node->data = NULL;
    node->children = new_list();
    node->parent = parent;
    return node;
}

void append_treenode(TreeNode *parent, TreeNode *child) {
    push_back(parent->children, child);
}

void map_dfs_inner(TreeNode *root, void *(*map_fn)(TreeNode *), List *accumulator) {
    if (!root) return;
    void *mapped = map_fn(root);
    push(accumulator, mapped);
    iter_list(root->children, child, TreeNode *) {
        map_dfs_inner(child, map_fn, accumulator);
    }
}

List *map_dfs(TreeNode *root, void *(*map_fn)(TreeNode *)) {
    List *mapped = new_list();
    map_dfs_inner(root, map_fn, mapped);
    rewind_list(root->children);
    return mapped;
}

void destroy_tree(TreeNode *root) {
    iter_list(root->children, child, TreeNode *) {
        destroy_tree(child);
    }

    destroy(root->children);
    free(root->data);
    free(root);
}