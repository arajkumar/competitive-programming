#include <iostream>
#include <memory>

template <typename T> struct TreeNode {
    T data;

    TreeNode<T>* left { };
    TreeNode<T>* right { };

    TreeNode(T data) : data(data)
    {
        // std::cout << __func__ << " data:" << data << std::endl;
    }

    void insert(const T& data)
    {
        if (data < this->data) {
            if (!left) {
                left = new TreeNode<T> { data };
                return;
            }
            left->insert(data);
        } else {
            if (!right) {
                right = new TreeNode<T> { data };
                return;
            }
            right->insert(data);
        }
    }

    void print() const
    {
        if (left)
            left->print();
        std::cout << data << std::endl;
        if (right)
            right->print();
    }

    using uptr = std::unique_ptr<TreeNode<T>>;
};

int main()
{
    using uptr_i = TreeNode<int>::uptr;
    uptr_i head = std::make_unique<TreeNode<int>>(1);
    head->insert(2);
    head->insert(3);
    head->insert(100);
    head->insert(1);
    head->print();
    return 0;
}
