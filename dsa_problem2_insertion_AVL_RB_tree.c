// NOTE:- This program will takes few hours to run...
// This is the code for insertion in the Red Black tree and AVL tree
// and making the count of number of rotation and height 
// then computing the average of this and storing this in two defferent text files
// one for red-balck tree and avl tree.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// the above headers gives to a permission to use the inbuild librarys such as printf(), fprintf(), fsacnf() for reading and writing to files.
// string.h help to perform all possible operation with the stirngs.

// Here i am initialising the global variable which will be helping me in the red black tree.
int RED = 1, BLACK = 0;

// This is the user defined data type for both AVL and Red-Black trees.
typedef struct Node {
    // this store key value of a node in a tree, here key value is integer.
    int key;
    struct Node *left, *right;
    // this is to the value of the hight
    int height; 
    // In Red-Black tree, in each node we also have mentain the colour of a node.
    // red is represented by 1 and black is represented by 0
    int color; 
} Node;

Node* create_new_node(int key) {
    // here i am creating the node in runtime and inseting the value the value of the arrya, then one by one rest of the key.
    // and the childs are null initailay(means no child it has).
    Node *node = (Node *) malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;
    // the initial height for the AVL tree is 1.
    node->height = 1; 
    // In Red-Black tree, when we insert new node the colour of that node must be RED.
    node->color = RED; 
    return node;
}

// this will help me get the max between two element deffernt element.
int maxi(int a, int b) {
    if(a>b)
        return a;
    else 
        return b;
}

// this is the AVL tree helper function.
int height_of_avl(Node *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

// this will help me to rotate left the tree. 
// and it will also make count of a numbser of rotation.
Node *leftrotationinavl(Node *x, int *rtnCnt) {
    Node *y = x->right;
    Node *zz = y->left;

    // this helps me to perform rotation 
    y->left = x;
    x->right = zz;

    // this will finds the max height and add it with one and then update heights
    x->height = maxi(height_of_avl(x->left), height_of_avl(x->right)) + 1;
    y->height = maxi(height_of_avl(y->left), height_of_avl(y->right)) + 1;

    // // incrementing the rotation count, whenever rotaion is performed.
    (*rtnCnt) = (*rtnCnt) + 1;

    return y;
}

// it will help me to find balance factor by subtracting left hieght and right height.
int get_tree_balanced(Node *N) {
    if (N == NULL)
        return 0;
    // the diff must be either 1, or eithre 0 and either -1.
    int diff = height_of_avl(N->left) - height_of_avl(N->right);
    return diff;
}

// this will help me to rotate right the tree. 
// and it will also make count of a numbser of rotaiton.
Node *rightrotationinavl(Node *y, int *rtnCnt) {
    Node *x = y->left;
    Node *zz = x->right;

    // this helps me to perform rotation 
    x->right = y;
    y->left = zz;

    // this will finds the max height and add it with one and then update heights
    y->height = maxi(height_of_avl(y->left), height_of_avl(y->right)) + 1;
    x->height = maxi(height_of_avl(x->left), height_of_avl(x->right)) + 1;

    // incrementing the rotation count, whenever rotaion is performed.
    (*rtnCnt) = (*rtnCnt) + 1;

    return x;
}

// tis is the helper function for Red-Black Tree 
int is_it_red(Node* node) {
    if (node == NULL) return 0;
    return node->color == RED;
}

// this is the driver function which will help me to insert the element into the avl tree.
Node* insert_in_AVL(Node* node, int key, int *rtnCnt) {
    // intialy i insrt elements into the tree like a normal BST tree.
    if (node == NULL)
        // this will help to create a new node
        return create_new_node(key);

    // the below if else statements helps to insert new element after checking its correct possion.
    // whether should i insert have to insert it in left sub tree or right subtree.
    if (key > node->key)
        node->right = insert_in_AVL(node->right, key, rtnCnt);
    else if (key < node->key)
        node->left = insert_in_AVL(node->left, key, rtnCnt);
    else
        return node;

    // it will updating the height of its ancestor node.
    // afte finding the max height between left subtree and right subtree.
    node->height = 1 + maxi(height_of_avl(node->left), height_of_avl(node->right));

    // it helps to find the balance factor.
    int balance = get_tree_balanced(node);

    // The following if helps me to balanceif the balanced factor is grt violated
    // basically what it do, it uses rotation to restore the balance factor value.

    // this is the Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightrotationinavl(node, rtnCnt);

    // this is the Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftrotationinavl(node->left, rtnCnt);
        return rightrotationinavl(node, rtnCnt);
    }

    // this is the Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftrotationinavl(node, rtnCnt);

    // this is the Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightrotationinavl(node->right, rtnCnt);
        return leftrotationinavl(node, rtnCnt);
    }

    return node;
}

// this is the function which helps to rotate left if it voilates the property of a red balck tree  
Node* left_Rotation_RB(Node* node, int *rtnCnt) {
    Node* right_Child = node->right;
    node->right = right_Child->left;
    right_Child->left = node;
    right_Child->color = node->color;
    node->color = RED;
    (*rtnCnt)++;
    return right_Child;
}

// this is the function which helps to rotate right if it voilates the property of a red balck tree
Node* right_Rotation_RB(Node* node, int *rtnCnt) {
    Node* left_Child = node->left;
    node->left = left_Child->right;
    left_Child->right = node;
    left_Child->color = node->color;
    node->color = RED;
    (*rtnCnt)++;
    return left_Child;
}

// this functio helps to flip the colour, from what initial the colour is.
void changeing_color(Node* node) {
    node->color = RED;
    node->right->color = BLACK;
    node->left->color = BLACK;
}

// this is the driver function, for insertion in a red black tree.
Node* insert_RB(Node* node, int key, int *rtnCnt) {
    // if the node value is null, it seeps the help of another function to create a new node.
    if (node == NULL)
        return create_new_node(key);

    // this helps to properly place the new key by checking it is greater than existing node or less the existing node.
    if (key > node->key)
        node->right = insert_RB(node->right, key, rtnCnt);
    else if (key < node->key)
        node->left = insert_RB(node->left, key, rtnCnt);

    // it checks the need of right or left rotation, if propety gets voilated it rotates the tree.
    if (is_it_red(node->right) && !is_it_red(node->left))
        node = left_Rotation_RB(node, rtnCnt);
    if (is_it_red(node->left) && is_it_red(node->left->left))
        node = right_Rotation_RB(node, rtnCnt);

    // if the colour property of the tree is get voilated it call the flipco;our function which helps to fix the colour issue.
    if (is_it_red(node->left) && is_it_red(node->right))
        changeing_color(node);

    return node;
}

int maxii(int *left_height_of_RB, int *right_height_of_RB)
{
    if(*left_height_of_RB > *right_height_of_RB)
        return *left_height_of_RB;
    else 
        return *right_height_of_RB;
}

//  this is the recursive funtion, help me to find the height of the red black tree, by going to the all possible paths form root to the leaf node.
int height_of_RB_tree(Node* node) {
    // if there is no node is a tree it returns the 0 height.
    if (node == NULL)
        return 0;

    // this will help me to get height of left subtree.
    int left_height_of_RB = height_of_RB_tree(node->left);

    // this will help me to get height of right subtree.
    int right_height_of_RB = height_of_RB_tree(node->right);

    // it finds the max among the left and right height.
    return maxii(&left_height_of_RB, &right_height_of_RB) + 1;
}

// it helps me to free the dynamicaly allocated memory for AVL and Red-Black tree nodes.
void free_tree_space(Node *node) {
    if (node == NULL) 
        return;

    // this call recurcively to free space
    free_tree_space(node->right);
    free_tree_space(node->left);

    free(node);
}

// void filename()
// {
//     // this is the name of  the coloum in the output file for Red-Black tree.
//     fprintf(rbOut, "Size\tAvg Rotations\tAvg Height\n");

//     // this is the name of  the coloum in the output file for AVl tree.
//     fprintf(avlOut, "Size\tAvg Rotations\tAvg Height\n");
// }

// this function to process the arrays
void processing_size_of_array(int sizes[], int numSizes, const char *avlFile, const char *rbFile) 
{
    // here i am open the text file, so that i can write the result of an Red-Black tree.
    FILE *rbOut = fopen(rbFile, "w");

    // here i am open the text file, so that i can write the result of an AVL tree.
    FILE *avlOut = fopen(avlFile, "w");

    if (!avlOut) {
        perror("Facing an error to open the output file");
        return;
    }

    if (!rbOut) {
        perror("Facing an error to open the output file");
        return;
    }

    // filename();
     // this is the name of  the coloum in the output file for Red-Black tree.
    fprintf(rbOut, "Size\tAvg Rotations\tAvg Height\n");

    // this is the name of  the coloum in the output file for AVl tree.
    fprintf(avlOut, "Size\tAvg Rotations\tAvg Height\n");

    for (int i = 0; i < numSizes; i++) {
        int size = sizes[i];
        printf("Performing insertion to find the number of ratation and height uisng bothe the trees, for the array size: %d\n", size);

        double total_Rotn_in_RB = 0;
        double total_Rotn_in_AVL = 0;

        double total_High_in_AVL = 0;
        double total_High_in_RB = 0;

        for (int trial = 0; trial < 100; trial++) {
            char fileName[100];

            // it open the array text file to perform insertion in the tree.
            snprintf(fileName, sizeof(fileName), "array_%d_of_size_%d.txt", trial+1, size);
            // here 'r' represent we only wants to get reading access to the file.
            FILE *input = fopen(fileName, "r");

            // if it facing an error to open an file, it prints an error occurs to open file, and try again to open the file, until it unable to open an file.
            if (!input) {
                printf("Facing an error to open the file: %s\n", fileName);
                continue;
            }

            Node *root_of_AVL = NULL;
            Node *root_of_RB = NULL;
            int rotn_cnt_AVL = 0, rotn_cnt_RB = 0, value;

            while (11) {
                if (fscanf(input, "%d", &value) != EOF)
                {
                    root_of_AVL = insert_in_AVL(root_of_AVL, value, &rotn_cnt_AVL);
                    root_of_RB = insert_RB(root_of_RB, value, &rotn_cnt_RB);
                }
                else 
                {
                    break;
                }
            }

            // below line of code is used to closed the opened file.
            fclose(input);

            // computing height of an Red-Black tree by using specific function for it, then assigning it into the new variable.
            int rb_H = height_of_RB_tree(root_of_RB);

            // computing height of an AVL tree by using specific function for it, then assigning it into the new variable.
            int avl_H = height_of_avl(root_of_AVL);

            // it will computes the total number of rotation and height of a Red_Black tree.
            total_High_in_RB = total_High_in_RB + rb_H;
            total_Rotn_in_RB = total_Rotn_in_RB + rotn_cnt_RB;

            // it will computes the total number of rotation and height of a AVL tree.
            total_High_in_AVL = total_High_in_AVL + avl_H;
            total_Rotn_in_RB = total_Rotn_in_RB + rotn_cnt_AVL;

            // below line of code free the memeory space by removing the trees.
            free_tree_space(root_of_RB);
            free_tree_space(root_of_AVL);
        }

        // it willl computed the average number of ratation in Red-Black trees
        double avg_rotn_in_RB = total_Rotn_in_RB / 100.0;
        // it will computes averge height among all 100 Red-Black trees
        double avg_hgh_in_RB = total_High_in_RB / 100.0;

        // it willl computed the average number of ratation in AVL trees
        double avg_rotn_in_AVL = total_Rotn_in_RB / 100.0;
        // it will computes averge height among all 100 AVL trees
        double avg_hgh_in_AVL = total_High_in_AVL / 100.0;

         // It will writes the computed values in the Red-Black tree file
        fprintf(rbOut, "%d\t%.2lf\t%.2lf\n", size, avg_rotn_in_RB, avg_hgh_in_RB);

        // It will writes the computed values in the AVL tree file.
        fprintf(avlOut, "%d\t%.2lf\t%.2lf\n", size, avg_rotn_in_AVL, avg_hgh_in_AVL);
    }

    // the below command is used to close the text file, this is comes under good programing skills and make the file protected also.
    fclose(avlOut);
    fclose(rbOut);
}

int hrbavl()
{
    printf("Programing Assignment 1, DSA Question number 2 part a. insertion in both the trees.\n");
    return 0;
}

int main() {
    // this is the array of different size, which is provided in the question. 
    int sizes_of_diff_ara[] = {10000, 100000, 1000000, 10000000};
    // here i am finding the size of array.
    // here i can directly write 4 but i am writing a code such that i will work not only for this data for other also.
    int ara_size = sizeof(sizes_of_diff_ara) / sizeof(sizes_of_diff_ara[0]);
    hrbavl();
    // here i am creting two differnt text file, for individualy storing the vlues of a avl tree and red black tree. 
    const char *avl_txt_file = "avl_tree_insertion.txt";
    const char *rb_txt_file = "rb_tree_insertion.txt";

    // this is the fuction which will call and do the all task for computing average hight and rotaion for both the tree red black and avl. 
    processing_size_of_array(sizes_of_diff_ara, ara_size, avl_txt_file, rb_txt_file);

    return 0;
}
