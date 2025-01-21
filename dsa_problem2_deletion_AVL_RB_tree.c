// NOTE:- This program will takes few hours to run...
// This is the code for deletion in the AVL tree and Red-Black tree
// and making the count of number of rotation and height 
// then computing the average of this and storing this in two different text files, one for AVL tree and another for Red-Black tree
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// the above headers gives to a permission to use the inbuild librarys such as printf(), fprintf(), fsacnf() for reading and writing to files.
// malloc(), free(), rand() to create memeory location during runtime and also free the space and for random number generation.
// string.h help to perform all possible operation with the stirngs.

// 
// This is the user defined data type for AVL tree.
typedef struct Node {
     // this store key value of a node in a tree, here key value is integer.
    int key;
    struct Node *left, *right;
    // this is to the value of the hight
    int height;
} Node;

// this function helps me to create a new node
Node* creating_a_new_node(int key) {
    // here i am creating the node in runtime and inseting the value of the arrya, then one by one rest of the key.
    // and the childs are null initailay(means no child it has).
    Node *node = (Node *) malloc(sizeof(Node));
    if (!node) {
        printf("Dynamicaly memory allocation is fail for the node\n");
        exit(1);
    }
    node->key = key;
    node->left = node->right = NULL;
    // the initial height for the AVL tree is 1.
    node->height = 1; 
    return node;
}

// Helper function to get maximum of two values
int maxi(int a, int b) {
    if(a<=b) 
        return b;
    else 
        return a;
}

// this is the AVL tree helper function.
int height_of_avl(Node *N) {
    if(N != NULL) return N->height;
    else return 0;
}

// it will help me to find baall factor by subtracting left hieght and right height.
int get_baall_the_tree(Node *N) {
    if (N == NULL)
        return 0;
    // the diff must be either 1, or eithre 0 and either -1.
    int diff = height_of_avl(N->left) - height_of_avl(N->right);
    return diff;
}

// this will help me to rotate left the tree. 
// and it will also make count of a numbser of rotation.
Node *lft_rotate_in_avl(Node *x, int *rtnCnt) {
    Node *y = x->right;
    Node *zz = y->left;

    // this helps me to perform rotation 
    y->left = x;
    x->right = zz;

    // this will finds the max height and add it with one and then update heights
    x->height = maxi(height_of_avl(x->left), height_of_avl(x->right)) + 1;
    y->height = maxi(height_of_avl(y->left), height_of_avl(y->right)) + 1;

    // // incrementing the rotation count, whenever rotaion is performed only while deletion.
    if (rtnCnt != NULL)
        (*rtnCnt) = (*rtnCnt) + 1;

    return y;
}

// this will help me to rotate right the tree. 
// and it will also make count of a numbser of rotaiton.
Node *rght_rotate_in_avl(Node *y, int *rtnCnt) {
    Node *x = y->left;
    Node *zz = x->right;

    // this helps me to perform rotation 
    x->right = y;
    y->left = zz;

    // this will finds the max height and add it with one and then update heights
    y->height = maxi(height_of_avl(y->left), height_of_avl(y->right)) + 1;
    x->height = maxi(height_of_avl(x->left), height_of_avl(x->right)) + 1;

    // incrementing the rotation count, whenever rotaion is performed.
    if (rtnCnt != NULL) (*rtnCnt)++; 

    return x;
}

// Insert function for AVL Tree (without rotation count)
Node* insert_in_avl(Node* node, int key) {
    // intialy i insrt elements into the tree like a normal BST tree.
    if (node == NULL)
        // this will help to create a new node
        return creating_a_new_node(key);

    // the below if else statements helps to insert new element after checking its correct possion.
    // whether should i insert have to insert it in left sub tree or right subtree.
    if (key < node->key)
        node->left = insert_in_avl(node->left, key);
    else if (key > node->key)
        node->right = insert_in_avl(node->right, key);
    else
        return node;


    // it will updating the height of its ancestor node.
    // afte finding the max height between left subtree and right subtree.
    node->height = 1 + maxi(height_of_avl(node->left), height_of_avl(node->right));
    // it helps to find the baall factor.
    int baall = get_baall_the_tree(node);

    // The following if helps me to baallif the baalld factor is grt violated
    // basically what it do, it uses rotation to restore the baall factor value.

    if (baall > 1 && key < node->left->key)
        return rght_rotate_in_avl(node, NULL);

    if (baall < -1 && key > node->right->key)
        return lft_rotate_in_avl(node, NULL);

    if (baall > 1 && key > node->left->key) {
        node->left = lft_rotate_in_avl(node->left, NULL);
        return rght_rotate_in_avl(node, NULL);
    }

    if (baall < -1 && key < node->right->key) {
        node->right = rght_rotate_in_avl(node->right, NULL);
        return lft_rotate_in_avl(node, NULL);
    }

    return node;
}

// Function to find the node with minimum key value
Node* minValueNode(Node* node) {
    Node* current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}

// this function help me delete elements for AVL Tree by making the rotation count
Node* deleteAVL(Node* root, int key, int* rtnCnt) {
    if (root == NULL)
        return root;
    if (key < root->key)
        root->left = deleteAVL(root->left, key, rtnCnt);
    else if (key > root->key)
        root->right = deleteAVL(root->right, key, rtnCnt);
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            Node* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
            free(temp);
        }
        else {
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteAVL(root->right, temp->key, rtnCnt);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + maxi(height_of_avl(root->left), height_of_avl(root->right));

    int baall = get_baall_the_tree(root);

    // baall the tree if needed (with rotation count)
    if (baall > 1 && get_baall_the_tree(root->left) >= 0)
        return rght_rotate_in_avl(root, rtnCnt);
    if (baall > 1 && get_baall_the_tree(root->left) < 0) {
        root->left = lft_rotate_in_avl(root->left, rtnCnt);
        return rght_rotate_in_avl(root, rtnCnt);
    }
    if (baall < -1 && get_baall_the_tree(root->right) <= 0)
        return lft_rotate_in_avl(root, rtnCnt);
    if (baall < -1 && get_baall_the_tree(root->right) > 0) {
        root->right = rght_rotate_in_avl(root->right, rtnCnt);
        return lft_rotate_in_avl(root, rtnCnt);
    }

    return root;
}

int rb_oprn()
{
    // creating a pointer which help me for file handling
    FILE *file_ptr;

    // here i am opening a text file, with writing permission, that means it allows me write into a file.
    file_ptr = fopen("rb_average_rotations_and_height_deletions.txt", "w");

    // Close the file
    fclose(file_ptr);
    return 0;
}

// it helps me to free the dynamicaly allocated memory for AVL and Red-Black tree nodes.
void freeing_tree_space(Node *node) {
    if (node == NULL)
        return;
    // this call recurcively to free space
    freeing_tree_space(node->left);
    freeing_tree_space(node->right);
    free(node);
}

// below function will help us to swap two numbers
void swop(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// this function is to process arrays
void processing_array_size(int sz[], int numsz, const char *out_text_file) {
    // here i am open the text file, so that i can write the result of an AVL tree.
    FILE *outFile = fopen(out_text_file, "w");
    if (!outFile) {
        perror("Facing an error to open an output file");
        return;
    }

    // this is the name of  the coloum in the output file for AVl tree.
    fprintf(outFile, "Size\tAvg Rotations\tAvg Height\n");

    for (int i = 0; i < numsz; i++) {
        int size = sz[i];
        printf("Lets process with array size: %d\n", size);
        double totl_rotation_in_avl = 0;
        double totl_height_in_avl = 0;

        for (int trial = 0; trial < 100; trial++) {
            char fileName[100];
            // it open the array text file to perform insertion in the tree.
            snprintf(fileName, sizeof(fileName), "array_%d_of_size_%d.txt", trial + 1, size);

             // here 'r' represent we only wants to get reading access to the file.
            FILE *input = fopen(fileName, "r");

            // if it facing an error to open an file, it prints an error occurs to open file, and try again to open the file, until it unable to open an file.
            if (!input) {
                printf("Error opening file: %s\n", fileName);
                continue;
            }

            Node *root_of_avl = NULL;
            int rotn_cnt_in_avl = 0, value;

            // i am allocate dynamic memory for storing array values which is taken fromthe files.
            int *val_of_arra = (int *)malloc(size * sizeof(int));
            if (val_of_arra == NULL) {
                printf("Memory allocation failed for val_of_arra\n");
                fclose(input);
                continue;
            }

            int valueCount = 0;

             // using below while loop inserting elements into AVL tree 
            while (11) {
                if (fscanf(input, "%d", &value) != EOF)
                {
                    root_of_avl = insert_in_avl(root_of_avl, value);
                }
                else 
                {
                    break;
                }
            }

            // below line of code is used to closed the opened file.
            fclose(input);

             // below few line of code is the implementaition of a Fisher Yates Algorithm, used to shuffel the element of a array in random permutation.
            for (int j = valueCount -1; j > 0; i--) {
            // below line of code is used find the randdom index and stored that index in j, the value between index i and index j is swaped, i.e. how it will randomised the array. 
            // by using this algorithm, it ensures that every element has equal probability of being placed in any position, i.e. how it will generate random permutation of the array.
            int k = rand() % (j+1);
            // calling another function swap element at index i and j.
            swop(&val_of_arra[j], &val_of_arra[k]);
             }

            rb_oprn();
            int numToDelete = valueCount / 10;
            int rotation_count_in_avl_while_deletion = 0;

            // now deleteting the 1/10th of thearray elements from the AVL tree and tracking the rotations count.
            for (int j = 0; j < numToDelete; j++) {
                int keyToDelete = val_of_arra[j];
                root_of_avl = deleteAVL(root_of_avl, keyToDelete, &rotation_count_in_avl_while_deletion);
            }

            // computing height of an AVL tree by using specific function for it, then assigning it into the new variable.
            int avl_tree_height_after_deletion = height_of_avl(root_of_avl);

            // it will computes the total number of rotation and height of a AVL tree.
            totl_rotation_in_avl = totl_rotation_in_avl + rotation_count_in_avl_while_deletion;
            totl_height_in_avl = totl_height_in_avl + avl_tree_height_after_deletion;

            // below line of code free the memeory space by removing the trees.
            free(val_of_arra);
            freeing_tree_space(root_of_avl);
        }

        // It will writes the computed values in the AVL tree file.
        fprintf(outFile, "%d\t%.2f\t%.2f\n", size, totl_rotation_in_avl / 100, totl_height_in_avl / 100);
    }

    // below line of code is used to closed the opened file.
    fclose(outFile);
}

int hrbavl()
{
    printf("Programing Assignment 1, DSA Question number 2 part b. deletion in the AVL tree and Red-Black tree.\n");
    return 0;
}

int main() {
    srand(time(0));

    hrbavl();
    // this is the array of different size, which is provided in the question. 
    int sz[] = {10000, 100000, 1000000, 10000000};
    // here i am finding the size of array.
    // here i can directly write 4 but i am writing a code such that i will work not only for this data for other also.
    int numsz = sizeof(sz) / sizeof(sz[0]);

    // here i am creting text file, for storing the computd vlues of a avl tree, during deletion.
    const char *out_text_file = "avl_average_rotations_and_height_deletions.txt";

    // this is the fuction which will call and do the all task for computing average hight and rotaion for avl tree during deletion. 
    processing_array_size(sz, numsz, out_text_file);

    //  it indicates that the task is completed 
    printf("Processing complete. Results written to %s\n", out_text_file);

    return 0;
}
