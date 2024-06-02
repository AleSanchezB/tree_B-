#include "../headers/Queue.hpp"

/**************************************************************************/
template <typename T, int m>
Tree_B<T, m>::Tree_B(){
    root = nullptr;
}
/**************************************************************************/
template <typename T, int m>
Tree_B<T, m>::~Tree_B(){
    free(root);
    // root->free();
    // delete root;
}
/**************************************************************************/
template <typename T, int m>
Tree_B<T, m>::Tree_B(const Tree_B<T, m>& g){ *this = g; }
/**************************************************************************/
template <typename T, int m>
Tree_B<T, m>& Tree_B<T, m>::operator=(const Tree_B<T, m>& g){ return *this; }

template <typename T, int m>
void Tree_B<T, m>::free(Node* p){
    if (p == nullptr) return;
    for(int i = 0; i < p->children_size; ++i){
        free(p->children[i]);
    }
    p->free();
    delete p;
}
/**************************************************************************/
template <typename T, int m>
void Tree_B<T, m>::insert(const T& d){ insert(d, root); }
/**************************************************************************/
template <typename T, int m>
void Tree_B<T, m>::insert(const T& d, Node*& p){
    if (p == nullptr) {
        p = new Node(true, true);
        p->key[0] = d;
        p->n++;
        p->children_size++;

    } else {
        int i = 0;
        while (i < p->n && d > p->key[i]) {
            i++;
        }
        if(!p->leaf) {
            insert(d, p->children[i]);
            return;
        }

        if(p->isroot){
            p->insertionSort(i, d);
            p->n++;
            print();
            if(p->isOverflow()){
                Node* new_node = new Node();
                Node* child = p;
                Node* new_father = new Node(false, p->isroot, p->parent);

                int mid = child->n;
                new_father->children[0] = child;
                new_father->children[1] = new_node;
                int new_node_key = 0;
                if(mid % 2 == 0) {
                    mid = mid/2;
                    new_node_key = mid;
                }
                else {
                    mid = mid/2 + 1;
                    new_node_key = mid - 1;
                }
                std::cout << "child->n: " << child->n << std::endl;
                child->children_size = mid + 1;

                new_father->n = 1;
                new_father->children_size = 2;
                new_father->key[0] = child->key[mid-1];
                for (int j = 0; j < new_node_key; ++j) {
                    new_node->key[j] = child->key[j + mid];
                    new_node->n++;
                    new_node->children_size++;
                }
                child->n = mid - 1;
                child->children_size = mid +1;
                // for (int j = child->n - 1; j > 0; --j) {
                //     new_node->children[j] = child->children[j + child->n/2];
                // }

                // for(int j = 0; j < child->n; ++j){
                //     new_node->children[j] = child->children[j + child->n/2];
                // }
                // child->children_size++;
                root = new_father;
                child->isroot = false;
                child->parent = new_father;
                new_node->parent = new_father;
            }else p->children_size++;
        }else{
            p->insertionSort(i, d);
            p->n++;
            if(p->isOverflow()){
                if(!verifyRotate(p->parent, p->searchIndex())){
                    std::cout << "Overflow" << std::endl;
                    split(p);
                }
            }else p->children_size++;
        }
        // if(p->children[i] != nullptr) {
        //         if (p->children[i]->isOverflow()) {
        //             std::cout << "Overflow" << std::endl;
        //             verifyRotate(p, i);
        //             //split(p, i);
        //             return;
        //         }
        //         insert(d, p->children[i]);
        //         return;
        //     }
        //     if (p->isOverflow()) {
        //         p->insertionSort(i, d);
        //         p->n++;
        //         // split(p, i);
        //         Node* new_node = new Node();
        //         Node* child = p;
        //         Node* new_father = new Node(p->leaf, p->isroot);
            
        //         for (int j = 0; j < child->n / 2; ++j) {
        //             new_node->key[j] = child->key[j + child->n/2];
        //             new_node->n++;
        //         }

        //         new_father->n = 1;
        //         new_father->children_size = 2;
        //         new_father->key[0] = child->key[child->n/2-1];

        //         new_father->children[0] = child;
        //         new_father->children[1] = new_node;

        //         if(child->n % 2 == 0) child->n = child->n/2 - 1;
        //         else child->n = child->n/2 + 1;
        //         child->children_size = child->children_size/2;
            
        //         for (int j = child->n - 1; j > 0; --j) {
        //             new_node->children[j] = child->children[j + child->n/2];
        //         }

        //         for(int j = 0; i < child->n; ++j){
        //             new_node->children[j] = child->children[j + child->n/2];
        //         }
        //         child->children_size++;
        //         root = new_father;
        //         return;
        //     }
        //     else {
        //         p->insertionSort(i, d);
        //         p->n++;
        //         p->children_size++;

        //     }
        // }
    }
}
/**************************************************************************/
template <typename T, int m>
bool Tree_B<T, m>::verifyRotate(Node* p, int i) {
    if (i == 0) {
        if(p->children[i+1]->isOverflow()) return false;
        std::cout << "Rotate right " << p->children[i+1]->max_children << std::endl;
        rotateRight(p, i);
    } else {
        if(p->children[i-1]->isOverflow()) return false;
        std::cout << "Rotate left" << std::endl;
        rotateLeft(p, i);
    }
    return true;
}
/**************************************************************************/
template <typename T, int m>
void Tree_B<T, m>::Node::insertionSort(int index, const T& d) {
    for (int i = n; i > index; --i) {
        key[i] = key[i - 1];
    }
    key[index] = d;
}
/**************************************************************************/
template <typename T, int m>
bool Tree_B<T, m>::search(const T& d) const {
    return search(d, root);
}
/**************************************************************************/
template <typename T, int m>
void Tree_B<T, m>::print() const {
    print(root);
}
/**************************************************************************/
template <typename T, int m>
void Tree_B<T, m>::split(Node* p){
    p->print();
    if(p->searchIndex() == 0){
        std::cout << "Splitting pasando del nodo 0 al 1" << std::endl;
        split(p->parent, 1);
    }else{
        std::cout << "Splitting" << std::endl;
        split(p->parent, p->searchIndex());
    }
}
/**************************************************************************/
template <typename T, int m>
void Tree_B<T, m>::split(Node* p, int i) {
    print();
    Node* left = p->children[i - 1];
    Node* right = p->children[i];

    std::cout << "Left: " << std::endl;
    left->print();
    std::cout << "right: " << std::endl;
    right->print();
    int n_total = left->n + right->n + 1;
    int alpha = 2*(m-1)/3;
    int beta = (2*(2*m-2)/3)+1;
    Node* new_node = new Node(true, false, p);
    T* keys = new T[n_total];
    for(int j = 0; j < left->n; ++j) keys[j] = left->key[j];
    keys[left->n] = p->key[i-1];
    for(int j = 0; j < right->n; ++j) keys[j + left->n + 1] = right->key[j];

    for(int j = 0; j < n_total; ++j) std::cout << keys[j] << ", ";
    std::cout << std::endl;

    left->n = alpha;
    left->children_size = alpha + 1;
    right->n = beta - (alpha+1);
    right->children_size = beta - alpha;
    new_node->n = n_total - (beta + 1);
    new_node->children_size = n_total - beta;
    for(int j = 0; j < alpha; ++j) left->key[j] = keys[j];
    
    std::cout << "new node: "<< beta << std::endl;
    
    p->key[i-1] = keys[alpha];

    for(int j = alpha + 1; j < beta; ++j) right->key[j - alpha - 1] = keys[j];

    p->key[i] = keys[beta];

    for(int j = beta + 1; j < n_total; ++j) new_node->key[j - beta - 1] = keys[j];

    p->children[i+1] = new_node;
    std::cout << "Left: " << std::endl;
    left->print();
    std::cout << "right: " << std::endl;
    right->print();
    std::cout << "new node: " << std::endl;
    new_node->print();

    std::cout << "p: " << std::endl;     

    p->n = 2;
    p->children_size = p->n+ 1;
    delete[] keys;
}
/**************************************************************************/
template <typename T, int m>
void Tree_B<T, m>::print(Node* p) const{
    if (p == nullptr) return;

    Queue<Node*> q;
    q.enqueue(root);
    Node* aux;
    std::cout << "Printing tree" << std::endl;
    while(!q.isEmpty()){
        aux = q.getFront();
        q.dequeue();
        aux->print();
        for(int i = 0; i < aux->children_size; ++i){
            if(aux->children[i] != nullptr)
                q.enqueue(aux->children[i]);
        }
    }
}
/**************************************************************************/
template <typename T, int m>
bool Tree_B<T, m>::search(const T& d, Node* p) const {
    if (p == nullptr) {
        std::cout << "Not found" << std::endl;
        return false;
    } else {
        int i = 0;
        while (i < p->children_size && d > p->key[i]) {
            i++;
        }
        if (i < p->children_size && d == p->key[i]) {
            std::cout << "Found" << std::endl;
            return true;
        } else if (p->leaf) {
            std::cout << "Not found" << std::endl;
            return false;
        } else {
            search(d, p->children[i]);
        }
    }
    return false;
}
/**************************************************************************/
template <typename T, int m>
void Tree_B<T, m>::rotateLeft(Node* p, int i) {
    Node* left = p->children[i - 1];
    Node* right = p->children[i];
    
    left->key[left->n] = p->key[i-1];
    left->n++;
    left->children_size = left->n + 1;
    p->key[i-1] = right->key[0];
    right->n--;
    right->children_size = right->n + 1;
    
    for (int j = 0; j < right->n; ++j) {
        right->key[j] = right->key[j + 1];
    }
}
/**************************************************************************/
template <typename T, int m>
void Tree_B<T, m>::rotateRight(Node* p, int i) {
    Node* left = p->children[i];
    Node* right = p->children[i + 1];
    
    for (int j = right->n; j > 0; --j) {
        right->key[j] = right->key[j - 1];
    }
    right->key[0] = p->key[i];
    p->key[i] = left->key[left->n - 1];
    left->n--;
    left->children_size = left->n + 1;
    right->n++;
    right->children_size = right->n + 1;

}
/**************************************************************************/
/*Node functions*/
/**************************************************************************/
template <typename T, int m>
Tree_B<T, m>::Node::Node(bool leaf, bool isroot, Node* parent) : leaf(leaf), isroot(isroot), parent(parent), children_size(1), n(0) {
    min_keys = 2*m/3;
    if(!isroot) {
        max_keys = m + 1;
        if(!leaf) min_children = (2*m-1)/3;
        else min_children = 0;
        
        max_children = m;
    } else {
        max_keys = 3*min_keys + 2;
        min_children = 2;
        //max_children = 2*((2*m-2)/3)+1;
        max_children = m;
    }

    key = new T[max_keys +1];
    children = new Node*[max_children + 1];
    for (int i = 0; i < max_children; ++i) {
        children[i] = nullptr;
    }
}
/**************************************************************************/
template <typename T, int m>
void Tree_B<T, m>::Node::free() {
    delete[] key;
    delete[] children;
}
/**************************************************************************/
template <typename T, int m>
bool Tree_B<T, m>::Node::isOverflow() const {
    return children_size == max_children;
}
/**************************************************************************/
template <typename T, int m>
bool Tree_B<T, m>::Node::isUnderflow() const {
    return children_size < min_children;
}
/**************************************************************************/
template <typename T, int m>
void Tree_B<T, m>::Node::print() const {
    for (int i = 0; i < n; ++i) {
        std::cout << key[i] << ", ";
    }
    std::cout << "\b\b \n";
}
/**************************************************************************/
template <typename T, int m>
typename Tree_B<T, m>::Node* Tree_B<T, m>::Node::searchParentLeft(){
    Node* aux = parent;
    for(int i = 0; i < aux->children_size; ++i){
        if(aux->children[i] == this){
            return (i == 0) ? nullptr : aux->children[i-1];
        }
    }
    return nullptr;
}
/**************************************************************************/
template <typename T, int m>
typename Tree_B<T, m>::Node* Tree_B<T, m>::Node::searchParentRight(){
    if(isroot) return nullptr;
    Node* aux = parent;
    for(int i = 0; i < aux->children_size; ++i){
        if(aux->children[i] == this){
            aux->print();
            return (i == aux->children_size - 1) ? nullptr : aux->children[i+1];
        }
    }
    return nullptr;
}
/**************************************************************************/
template <typename T, int m>
int Tree_B<T, m>::Node::searchIndex() const {
    int i = 0;
    for(int i = 0; i < parent->children_size; ++i){
        if(parent->children[i] == this) return i;
    }
    return i;
}
