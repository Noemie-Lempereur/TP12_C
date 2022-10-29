#include "tree.h"
#include "nodeTreeList.h"
#include "nodeTreeQueueList.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


struct NodeTree* createEmptyTree(){
    return NULL;
}

struct NodeTree* bin(struct NodeTree* l, int val, struct NodeTree* r){
    struct NodeTree *tree=malloc(sizeof(struct NodeTree));
    if(tree!=NULL) {
        tree->value = val;
        tree->left = l;
        tree->right = r;
    }
    return tree;
}

bool isTreeEmpty(struct NodeTree* tree){
    if(tree==NULL){
        return true;
    }
    return false;
}

struct NodeTree* left(struct NodeTree* tree){
    return tree->left;
}

struct NodeTree* right(struct NodeTree* tree){
    return tree->right;
}

int root(struct NodeTree* tree){
    return tree->value;
}

bool isLeaf(struct NodeTree* tree){
    if(isTreeEmpty(tree)==false){
        if (isTreeEmpty(left(tree))&&isTreeEmpty(right(tree))){
            return true;
        }
    }
    return false;
}


void deleteLeaf(struct NodeTree* tree){
    if(!isTreeEmpty(tree)) {
        if(isLeaf(tree)){
            free(tree);
            return;
        }
        else {
            if (isTreeEmpty(tree->left)) {
                if (isLeaf(tree->left)) {
                    free(tree->left);
                    tree->left = NULL;
                } else {
                    deleteLeaf(tree->left);
                }
            } else {
                if (isLeaf(tree->right)) {
                    free(tree->right);
                    tree->right = NULL;
                } else {
                    deleteLeaf(tree->right);
                }
            }
        }
    }
}

void deleteTree(struct NodeTree* tree){
    while(!isTreeEmpty(tree)){
        deleteLeaf(tree);
    }
    free(tree);
}

int numberNodes(struct NodeTree* tree){
    if(isTreeEmpty(tree)){
        return 0;
    } else{
        return 1+numberNodes(left(tree))+numberNodes(right(tree));
    }
}

int numberLeaves(struct NodeTree* tree){
    if(isTreeEmpty(tree)){
        return 0;
    }else{
        if(isLeaf(tree)){
            return 1;
        }else{
            return numberLeaves(left(tree))+numberLeaves(right(tree));
        }
    }
}

int numberInternalNodes(struct NodeTree* tree){
    return numberNodes(tree)-numberLeaves(tree);
}

int sumValues(struct NodeTree* tree){
    if(isTreeEmpty(tree)){
        return 0;
    }else{
        return root(tree)+sumValues(left(tree))+sumValues(right(tree));
    }
}

int height(struct NodeTree* tree){
    if(isTreeEmpty(tree)){
        return 0;
    }else{
        if(height(left(tree))<height(right(tree))){
            return 1+height(right(tree));
        } else{
            return 1+height(left(tree));
        }
    }
}

bool belongs(struct NodeTree* tree, int x){
    if(numberRepetitions(tree,x)!=0){
        return true;
    }
    return false;
}

int lastFullLevel(struct NodeTree* tree){
    if(isTreeEmpty(tree)){
        return 0;
    }
    else{
        if(lastFullLevel(right(tree))<lastFullLevel(left(tree))){
            return 1+lastFullLevel(right(tree));
        }else{
            return 1+lastFullLevel(left(tree));
        }
    }
}

void descendants(struct NodeTree* tree, int x){
    if(isTreeEmpty(tree)==false){
        if(root(tree)==x){
            printf("%d  ",root(tree));
            if(!isTreeEmpty(left(tree))){
                descendants(left(tree), root(left(tree)));
            }
            if(!isTreeEmpty(right(tree))){
                descendants(right(tree), root(right(tree)));
            }

        }else{
            descendants(left(tree),x);
            descendants(right(tree),x);
        }
    }
}

struct NodeTree* mirror(struct NodeTree* tree){
    if(isTreeEmpty(tree)==false){
        return bin(mirror(right(tree)),root(tree),mirror(left(tree)));
    }else{
        return createEmptyTree();
    }
}

bool equals(struct NodeTree* tree1,struct NodeTree* tree2){
    if(isTreeEmpty(tree1)==false&&isTreeEmpty(tree2)==false){
        if(root(tree1)!=root(tree2)){
            return false;
        } else{
            return equals(left(tree1),left(tree2))&&equals(right(tree1),right(tree2));
        }
    } else{
        return true;
    }
}

int numberRepetitions(struct NodeTree* tree, int x){
    if(isTreeEmpty(tree)){
        return 0;
    }else{
        if(root(tree)==x){
            return 1+numberRepetitions(left(tree),x)+numberRepetitions(right(tree),x);
        }
        else{
            return numberRepetitions(left(tree),x)+numberRepetitions(right(tree),x);
        }
    }
}

void pathTo(struct NodeTree* tree, int x){
    if(belongs(tree,x)){
        printf("%d  ",root(tree));
    }
    if(belongs(left(tree),x)){
        pathTo(left(tree),x);
    }else {
        if(belongs(right(tree),x)){
            pathTo(right(tree),x);
        }
    }
}

void preorder(struct NodeTree* tree){
    if(isTreeEmpty(tree)==false){
        printf("%d  ",root(tree));
        preorder(left(tree));
        preorder(right(tree));
    }
}

void postorder(struct NodeTree* tree){
    if(isTreeEmpty(tree)==false){
        postorder(left(tree));
        postorder(right(tree));
        printf("%d  ",root(tree));
    }
}

void inorder(struct NodeTree* tree){
    if(isTreeEmpty(tree)==false) {
        inorder(left(tree));
        printf("%d  ", root(tree));
        inorder(right(tree));
    }
}
/*
void BFS(struct NodeTree* tree){
    bool val;
    struct Queue *Q=createEmptyQueue();
    enqueue(Q,root(tree),&val);
    struct NodeTree *B = createEmptyTree();
    while(isQueueEmpty(Q)==false){
        B->value=dequeue(Q,&val);
        if(isTreeEmpty(B)==false){
            printf("%d", root(B));
            enqueue(Q,root(left(B)),&val);
            enqueue(Q,root(right(B)),&val);
        }
    }
    deleteQueue(Q);
    deleteTree(B);
}*/
void BFS(struct NodeTree* tree){
    struct Queue* q = createEmptyQueue();
    bool valid = true;
    enqueue(q, tree, &valid);
    while(!isQueueEmpty(q)){
        struct NodeTree* B = dequeue(q, &valid);
        if(!isTreeEmpty(B)){
            printf("%d  ", root(B));
            enqueue(q,left(B), &valid);
            enqueue(q, right(B), &valid);
        }
    }
}


struct NodeTree* buildTreeFromPreIn(int pre[],int in[],int sp,int ep,int si,int ei) {
    if (si>ei) {
        return NULL;
    }
    struct NodeTree *tree4=bin(createEmptyTree(),pre[sp],createEmptyTree());
    if (sp==ep) {
        return tree4;
    }
    int i=si;
    while (in[i]!=pre[sp]&&i<ei){
        i++;
    }
    return bin(buildTreeFromPreIn(pre,in,sp+1,i,si,i-1),pre[sp],buildTreeFromPreIn(pre,in, ep-ei+i+1, ep, i+1, ei));
}

struct NodeTree* buildTreeFromPostIn(int post[],int in[],int sp,int ep,int si,int ei){
    if (si>ei) {
        return NULL;
    }
    if (sp==ep) {
        return bin(createEmptyTree(),post[ep],createEmptyTree());
    }
    int i=si;
    while (in[i]!=post[ep]&&i<ei){
        i++;
    }
    return bin(buildTreeFromPostIn(post,in,sp,sp+i-1-si,si,i-1),post[ep],buildTreeFromPostIn(post,in,sp-si+i,ep-1,i+1,ei));
}

struct NodeTree* buildTreeFromBFSIn(int bfs[],int in[],int sb,int eb,int si,int ei){
    if (si>ei) {
        return NULL;
    }
    if (sb==eb) {
        return bin(createEmptyTree(),bfs[sb],createEmptyTree());
    }
    int i=si;
    while (in[i]!=bfs[sb]&&i<ei){
        i++;
    }
    int k=0;
    int newBFS[MAX_SIZE]={0};
    for(int j=sb;j<=eb;j++){
        for(int r=si;r<i;r++){
            if (bfs[j]==in[r]){
                newBFS[k]=in[r];
                k++;
                break;
            }
        }
    }

    int k2=0;
    int newBFS2[MAX_SIZE]={0};
    for(int j=sb;j<=eb;j++){
        for(int r=i+1;r<=ei;r++){
            if (bfs[j]==in[r]){
                newBFS2[k2]=in[r];
                k2++;
            }
        }
    }
    return bin(buildTreeFromBFSIn(newBFS,in,0,k,si,i-1),bfs[sb],buildTreeFromBFSIn(newBFS2,in,0,k2,i+1,ei));
}



/*
void printByLevel(struct NodeTree* tree) {
    if (!isTreeEmpty(tree)) {
        for (int i = 1; i <= height(tree); i++) {
            for (int j = 0; j < i; j++) {
                printf("-");
            }
            printf("%d\n", sumlevel(tree, i));
        }
    }
}*/