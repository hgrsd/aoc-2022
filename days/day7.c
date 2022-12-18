#include <stddef.h>
#include <string.h>
#include "common.h"
#include "tree.h"

#define BUF_SIZE 64

typedef enum NodeType {
    DIRECTORY_NODE,
    FILE_NODE
} NodeType;

typedef struct FileSystemNode {
    NodeType type;
    long size;
    char name[BUF_SIZE];
} FileSystemNode;

TreeNode *fs_root(void) {
    TreeNode *root = new_treenode(NULL);
    FileSystemNode *root_fsnode = malloc(sizeof(*root_fsnode));

    strncpy(root_fsnode->name, "/\0", 2);
    root_fsnode->size = 0;
    root_fsnode->type = DIRECTORY_NODE;

    root->children = new_list();
    root->data = root_fsnode;
    root->parent = NULL;

    return root;
}

void move(TreeNode **current, char *to) {
    TreeNode *c = *current;
    if (strcmp("..", to) == 0) {
        *current = c->parent;
        return;
    }

    iter_list((*current)->children, child, TreeNode *) {
        FileSystemNode *fs = (FileSystemNode *) child->data;

        if (strcmp(fs->name, to) == 0 && fs->type == DIRECTORY_NODE) {
            *current = child;
            break;
        }
    }
    rewind_list(c->children);
}

void append_dir(TreeNode *current, char *dir) {
    TreeNode *new = new_treenode(current);

    FileSystemNode *data = malloc(sizeof(*data));
    strncpy(data->name, dir, BUF_SIZE);
    data->type = DIRECTORY_NODE;
    data->size = 0;
    new->data = data;
    append_treenode(current, new);
}

void bubble_up_size_increase(TreeNode *leaf, long size) {
    TreeNode *cur = leaf;
    while (cur) {
        FileSystemNode *fs = (FileSystemNode *) cur->data;
        if (fs->type == DIRECTORY_NODE) {
            fs->size = fs->size + size;
        }
        cur = cur->parent;
    }
}

void append_file(TreeNode *current, char *filename, long size) {
    TreeNode *new = new_treenode(current);

    FileSystemNode *data = malloc(sizeof(*data));
    strncpy(data->name, filename, BUF_SIZE);
    data->type = FILE_NODE;
    data->size = size;
    new->data = data;
    append_treenode(current, new);
    bubble_up_size_increase(current, size);
}

void apply(TreeNode **current, char *instruction) {
    printf("applying: %s\n", instruction);
    long size;
    char buf[BUF_SIZE];

    if (sscanf(instruction, "$ cd %s", buf) != 0) {
        if (strcmp("/", buf) != 0) {
            move(current, buf);
        }
        return;
    }

    if (sscanf(instruction, "dir %s", buf) != 0) {
        append_dir(*current, buf);
        return;
    }

    if (sscanf(instruction, "%ld %s", &size, buf) != 0) {
        append_file(*current, buf, size);
        return;
    }
}

TreeNode *build_file_system_tree(List *instructions) {
    TreeNode *root = fs_root();
    TreeNode *cur = root;
    iter_list(instructions, instruction, char *) {
        apply(&cur, instruction);
    }
    return root;
}

void *dirsize(TreeNode *node) {
    long *ds = malloc(sizeof(*ds));
    *ds = 0;

    FileSystemNode *fsnode = (FileSystemNode *)node->data;
    if (fsnode->type == DIRECTORY_NODE) {
       *ds = fsnode->size;
    }

    return ds;
}

int main(void) {
    char *buf;
    size_t sz;

    read_string("../inputs/day_7", &buf, &sz);
    List *instructions = split_by('\n', buf);
    free(buf);

    TreeNode *file_tree = build_file_system_tree(instructions);
    destroy(instructions);

    List *dirsizes = map_dfs(file_tree, dirsize);
    long part1 = 0;
    iter_list(dirsizes, s, long *) {
        if (*s <= 100000) part1 += *s;
    }


    printf("day 7, part 1: %ld\n", part1);

    destroy_tree(file_tree);
}