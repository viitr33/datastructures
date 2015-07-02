#include <iostream>
#include <stdlib.h>

/*
    Using classes just for the sake of saving some lines
    in initialization and cleanup while creating nodes
*/

class Node
{
    public:
        Node *lnode;
        Node *rnode;
        int key;

        Node(int num):key(num), lnode(NULL), rnode(NULL) {}
};

//for a singly linked-list of 'Nodes'
class NodeList
{
    public:
        Node *nodeptr;
        NodeList *nextnode;

        NodeList(Node *ptr) : nodeptr(ptr), nextnode(NULL) {}
        ~NodeList() { nodeptr = NULL; nextnode = NULL; }
};

//search a key (non-recursive)
Node* findNodeNR(Node *root, int skey)
{
    while(root)
    {
        if(skey < root->key)
        {
            root = root->lnode;
            continue;
        }

        if(skey > root->key)
        {
            root = root->rnode;
            continue;
        }
        return root;
    }
    return NULL;
}

//search a key (recursive)
Node* findNodeR(Node *root, int skey)
{
    if(root)
    {
        if(skey == root->key)
            return root;
        else if(skey < root->key)
            return findNodeR(root->lnode, skey);
        else
            return findNodeR(root->rnode, skey);
    }
    return NULL;
}

//find the minimum key (non-recursive)
Node* findMinNR(Node *root)
{
    if(root)
    {
        while(root->lnode)
            root = root->lnode;
    }
    return root;
}

//find the maximum key (non-recursive)
Node* findMaxNR(Node *root)
{
    if(root)
    {
        while(root->rnode)
            root = root->rnode;
    }
    return root;
}

//add a node to the tree (recursive)
Node* addNodeR(Node **root, int key)
{
    if(*root)
    {
        if(key <= (*root)->key)
            addNodeR(&((*root)->lnode), key);
        else
            addNodeR(&((*root)->rnode), key);
    }
    else
    {
        *root = new Node(key);
        return *root;
    }
    return NULL;
}

//delete a node from the tree (recursive)
Node* deleteNodeR(Node** root, int skey)
{
    // base case
    if (*root == NULL)
        return *root;
 
    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if (skey < (*root)->key)
        return deleteNodeR(&((*root)->lnode), skey);
 
    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if (skey > (*root)->key)
        return deleteNodeR(&((*root)->rnode), skey);
 
    // else, this is the node to be deleted
    else
    {
        // node with only one child or no children
        if ((*root)->lnode == NULL)
        {
            Node *temp = (*root)->rnode;
            Node *dtmp = *root;
            *root = temp;
            return dtmp;
        }
        else if ((*root)->rnode == NULL)
        {
            Node *temp = (*root)->lnode;
            Node *dtmp = *root;
            *root = temp;
            return dtmp;
        }
 
        // node with two children: Get the inorder successor 
        // OR we can also work with the inorder predecessor
        Node* temp = findMin((*root)->rnode);
 
        // Copy the inorder successor's key to this node
        (*root)->key = temp->key;
 
        // Delete the inorder successor
        return deleteNodeR(&((*root)->rnode), temp->key);
    }
}

//level order traversal (non-recursive)
void levelOrderNR(Node *root)
{
    if(!root)
        return;

    NodeList *nhead = new NodeList(root);
    NodeList *ntail = nhead;

    while(nhead)
    {   
        if(nhead->nodeptr->lnode)
        {   
            ntail->nextnode = new NodeList(nhead->nodeptr->lnode);
            ntail = ntail->nextnode;
        }   
        if(nhead->nodeptr->rnode)
        {   
            ntail->nextnode = new NodeList(nhead->nodeptr->rnode);
            ntail = ntail->nextnode; 
        }   
        NodeList *tmp = nhead;
        std::cout<<" "<<tmp->nodeptr->key;
        nhead = nhead->nextnode;
        delete(tmp);
    }   
}

//preorder traversal (recursive)
void traversePreorderR(Node *root)
{
    if(root)
    {
        std::cout<<" "<<root->key;
        traversePreorderR(root->lnode);
        traversePreorderR(root->rnode);
    }
}

//postorder traversal (recursive)
void traversePostorderR(Node *root)
{
    if(root)
    {
        traversePostorderR(root->lnode);
        traversePostorderR(root->rnode);
        std::cout<<" "<<root->key;
    }
}

//inorder traversal (recursive)
void traverseInorderR(Node *root)
{
    if(root)
    {
        traverseInorderR(root->lnode);
        std::cout<<" "<<root->key;
        traverseInorderR(root->rnode);
    }
}

//function to transform a Binary Search Tree
//into a Circular Doubly Linked List (recursive)
void transformInorderR(Node *root, Node **head, Node **lv)
{
    if(root)
    {
        transformInorderR(root->lnode, head, lv);

        if(*head == NULL)
            *head = *lv = root;
        else
        {
            (*lv)->rnode = root;
            root->lnode = *lv;
            *lv = root;
        }

        transformInorderR(root->rnode, head, lv);
    }
}

//wrapper to transfor a Binary Search Tree
//into a Circular Doubly Linked List
Node* btreeToCircularDLL(Node *root)
{
    Node *lv = NULL;
    Node *head = NULL;

    transformInorderR(root, &head, &lv);
    if(head)
    {
        head->lnode = lv;
        lv->rnode = head;
    }
    return head;
}

//mirror a BST using preorder traversal (recursive)
void mirrorTreePreorderR(Node *root)
{
    if(root)
    {
        Node *tmp = root->rnode;
        root->rnode = root->lnode;
        root->lnode = tmp;
        
        mirrorTreePreorderR(root->lnode);
        mirrorTreePreorderR(root->rnode);
    }
}

//mirror a BST using postorder traversal (recursive)
void mirrorTreePostorderR(Node *root)
{
    if(root)
    {
        mirrorTreePostorderR(root->lnode);
        mirrorTreePostorderR(root->rnode);

        Node *tmp = root->rnode;
        root->rnode = root->lnode;
        root->lnode = tmp;
    }
}

//mirror a BST using inorder traversal (recursive)
void mirrorTreeInorderR(Node *root)
{
    if(root)
    {
        mirrorTreeInorderR(root->lnode);

        Node *tmp = root->rnode;
        root->rnode = root->lnode;
        root->lnode = tmp;

        mirrorTreeInorderR(root->lnode);
    }
}
