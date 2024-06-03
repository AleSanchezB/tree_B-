#ifndef TREE_B_HPP
#define TREE_B_HPP

template <typename T, int m>
class Tree_B{
private:
    struct Node{
        Node(bool leaf = true, bool isroot = false, Node* parent = nullptr);
        T* key;
        Node** children;         
        bool leaf;
        bool isroot;
        Node* parent;
        int children_size;
        
        bool isOverflow() const;
        bool isUnderflow() const;
        void insertionSort(int i, const T& key);
        void insertNonFull(const T& key);
        void actuallyParent(Node* parent);
        Node* searchParentLeft();
        Node* searchParentRight();
        
        int searchIndex() const;

        int n;

        void print() const;
        void free();

        int min_keys;
        int max_keys;
        int min_children;
        int max_children;
    };
    Node* root;

    void remove(Node* p, const T& d);
    int findKey(Node* p, const T& d);
    void removeFromLeaf(Node* p, int idx);
    void removeFromNonLeaf(Node* p, int idx);
    T getPred(Node* p, int idx);
    T getSucc(Node* p, int idx);
    void fill(Node* p, int idx);
    void borrowFromPrev(Node* p, int idx);
    void borrowFromNext(Node* p, int idx);
    void merge(Node* p, int idx);

    void print_preorder(Node* root, int d) const;
    void print_postorder(Node* root) const;
    void print(Node* root) const;
    void insert(const T& key, Node*& root);
    bool search(const T& key, Node* root) const;
    void free(Node* root);
    void split(Node *parent, int index);
    void split(Node *parent);
    void splitRoot();
    void rotateRight(Node* parent, int index);
    void rotateLeft(Node* parent, int index);
    bool verifyRotate(Node* root, int index);
    void splitNotLeaf(Node* parent, int index);

    void printTree(Node* node, int depth, std::ostringstream& oss);
public:
	Tree_B();
 	~Tree_B();
	Tree_B(const Tree_B<T, m>& g);
	Tree_B<T, m>& operator=(const Tree_B<T, m>& g);

    void insert(const T& key);
    void remove(const T& key);
    bool search(const T& key) const;
    void clear(Node* root);
    void print() const;
    void print_preorder() const;
    void printTree(std::ostringstream& oss);
    
};

#include "../templates/Tree_B.tpp"

#endif
