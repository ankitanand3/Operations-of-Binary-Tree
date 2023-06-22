#include <iostream>
#include <sstream> // For data conversion
#include <vector>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node* middle;
};

class Tree {
private:
    Node* root;

public:
    Tree() { root = NULL; }

    // Building a tree recursively.
    Node* build_tree(Node* node, int value) {
        if (node == NULL) { // If there's no node at the current position
            node = new Node();   // Create a new node
            node->data = value;  // Create a new node
            node->left = NULL;
            node->middle = NULL;
            node->right = NULL;
        }
        else if (value < node->data) { // If the value is less than the current
            // node's data
            node->left =
                build_tree(node->left, value); // Build a subtree on the left side
        }
        else if (value ==
            node->data) { // If the value is equal to the current node's data
            node->middle =
                build_tree(node->middle, value); // Build a subtree in the middle
        }
        else // If the value is greater than the current node's data
        {
            node->right =
                build_tree(node->right, value); // Build a subtree on the right side
        }
        return node; // Return the root of the subtree
    }

    // Calling the recursive build_tree() function to build the tree.
    void build_tree(int value) { root = build_tree(root, value); }

    // This function returns the root node of the tree.
    Node* getRoot() { return root; }

    // This function traverses the tree in the following order: middle, left,
    // right.
    void traverse_MLWR(Node* node) {
        if (node != NULL) {         // If the current node is not null
            traverse_MLWR(node->middle); // Traverse the middle subtree
            traverse_MLWR(node->left);   // Traverse the left subtree
            cout << node->data << " ";   // Print the node's data
            traverse_MLWR(node->right);  // Traverse the right subtree
        }
    }

    // Calculating the distance of a node from the root.
    int root_distance(int N) {
        int dist = 0;             // Initialize the distance to zero
        Node* curr = root;        // Start at the root node
        while (curr != NULL) { // While the current node is not null
            if (N == curr->data) { // If the value is equal to the current node's data
                return dist;         // Return the distance
            }
            else if (N < curr->data) {  // If the value is less than the current
                // node's data
                curr = curr->left;          // Move to the left subtree
            }
            else if (N == curr->data) { // If the value is equal to the current
                // node's data
                curr = curr->middle;        // Move to the middle subtree
            }
            else { // If the value is greater than the current node's data
                curr = curr->right; // Move to the right subtree
            }
            dist++; // Increment the distance
        }
        cout << "Integer cannot be found." << endl;
        return -1;
    }

    string encode(int N) {
        string encoding = "";
        Node* curr = root;
        // Traverse the tree until the node containing N is found or the end of the
        // tree is reached
        while (curr != NULL) {
            if (N < curr->data) {
                encoding += "0";
                curr = curr->left;
            }
            else if (N == curr->data) {
                encoding += "1";
                curr = curr->middle;
            }
            else {
                encoding += "2";
                curr = curr->right;
            }
            return encoding;
        }
        if (encoding == "") {
            cout << "integer cannot be found." << endl;
        }
        // return encoding;
    }

    // Function to locate an integer in the tree using a given encoding, returning
    // the integer value
    int located_integer(string s) {
        Node* curr = root;
        // Traverse the tree using the encoding until the node containing the
        // integer is found or the end of the tree is reached
        for (char c : s) {
            if (c == '0') {
                curr = curr->left;
            }
            else if (c == '1') {
                curr = curr->middle;
            }
            else {
                curr = curr->right;
            }
            // If the end of the tree is reached, print a message and return -1
            if (curr == NULL) {
                cout << "Integer cannot be found." << endl;
                return -1;
            }
        }
        return curr->data;
    }

    // Recursive function to return nodes in the tree with a certain number of
    // children, returning a comma-separated string
    string return_nodes(Node* node, int k) {
        stringstream ss;
        if (node == NULL) {
            return "";
        }
        else if (k == 0 && node->left == NULL && node->middle == NULL &&
            node->right == NULL) {
            // node is a leaf node
            ss << node->data << ",";
        }
        else if (k == 1 && ((node->left == NULL && node->middle != NULL &&
            node->right == NULL) ||
            (node->left != NULL && node->middle == NULL &&
                node->right == NULL) ||
            (node->left == NULL && node->middle == NULL &&
                node->right != NULL))) {
            // node has only one child
            ss << node->data << ",";
        }
        else if (k == 2 && node->left != NULL && node->middle != NULL &&
            node->right != NULL) {
            // node has three children
            ss << node->data << ",";
        }
        ss << return_nodes(node->left, k);
        ss << return_nodes(node->middle, k);
        ss << return_nodes(node->right, k);
        return ss.str();
    }

    string return_nodes(int k) { return return_nodes(root, k); }

    int depth(Node* node) {
        if (node == NULL) {
            return -1;
        }
        int left_depth = depth(node->left);
        int middle_depth = depth(node->middle);
        int right_depth = depth(node->right);
        int max_child_depth = max(left_depth, max(middle_depth, right_depth));
        return max_child_depth + 1;
    }

    int depth() { return depth(root); }
};

int main() {
    vector<int> v = { 5, 7, 3, 5, 2, 4, 9, 4, 12, 9, 8 };
    Tree T;
    for (int i = 0; i < v.size(); i++) {
        T.build_tree(v[i]);
    }
    Node* root = T.getRoot();


    T.traverse_MLWR(root);
    cout << endl;
    cout << "Root distace of 5: " << T.root_distance(5) << endl;
    cout << "Root distace of 8: " << T.root_distance(8) << endl;

    cout << "Encode value of 5: " << T.encode(5) << endl;
    cout << "Encode value of 7: " << T.encode(7) << endl;
    cout << "Locate integer " << T.located_integer("222") << endl;
    cout << "Return nodes " << T.return_nodes(1) << endl;
    int tree_depth = T.depth();
    cout << "Depth of the tree: " << tree_depth << endl;
    return 0;
}
