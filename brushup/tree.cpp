// clang++ -std=c++14
//
#include <iostream>
#include <memory>

template <typename T> struct Tree {

    struct Node {
        T data;

        Node* left { };
        Node* right { };

        Node(const T& data) : data(data)
        {
            // std::cout << __func__ << " data:" << data << std::endl;
        }

        void insert(const T& data)
        {
            if (data < this->data) {
                if (!this->left) {
                    this->left = new Node { data };
                    return;
                }
                left->insert(data);
            } else {
                if (!this->right) {
                    this->right = new Node { data };
                    return;
                }
                right->insert(data);
            }

        }

        void visit(std::function<void(const T&)>& func)
        {
            if (left)
                left->visit(func);

            func(data);

            if (right)
                right->visit(func);
        }
    };

    Node* head {};

    Tree() = default;

    void insert(const T& data)
    {
        if (!head) {
            this->head = new Node { data };
            return;
        }
        head->insert(data);
    }

    void visit(std::function<void(const T&)> func) const
    {
        if (!head)
            return;
        head->visit(func);
    }
};

int main()
{
    auto tree = std::make_unique<Tree<int>>();
    tree->insert(5);
    tree->insert(2);
    tree->insert(3);
    tree->insert(100);
    tree->insert(500);
    tree->insert(700);
    tree->insert(1);
    tree->visit([](auto d) { std::cout << d <<std::endl; });

    auto str_tree = std::make_unique<Tree<std::string>>();
    str_tree->insert("f");
    str_tree->insert("b");
    str_tree->insert("a");
    str_tree->insert("x");
    str_tree->insert("k");
    str_tree->insert("c");
    str_tree->insert("z");
    str_tree->visit([](auto d) { std::cout << d <<std::endl; });
    return 0;
}
