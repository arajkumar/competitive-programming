#include <iostream>
#include <memory>

template <typename T> struct List {
    struct Node {
        T data;

        Node* next { };

        Node(const T& data) : data(data)
        {
            // std::cout << __func__ << " data:" << data << std::endl;
        }

    };

    // head and tail ptr to keep track of the nodes
    Node* head { };
    Node* tail { };

    List() = default;

    void insert(const T& data)
    {
        auto node = new Node { data };
        if (!head && !tail) {
            head = tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }

    void reverse()
    {
        if (!head)
          return;

        auto r_head { this->head };
        auto node { this->head->next };
        r_head->next = nullptr;
        while (node) {
            auto temp_r_head = r_head;
            r_head = node;
            auto temp_node_next { node->next };
            node->next = temp_r_head;
            node = temp_node_next;
        }
        head = r_head;
    }

    void print() const
    {
        auto node { this->head };
        while (node) {
            std::cout << node->data << std::endl;
            node = node->next;
        }
    }

};

int main()
{
    auto list = std::make_unique<List<int>>();
    list->insert(1);
    list->insert(2);
    list->insert(3);
    list->insert(4);
    list->insert(5);
    list->insert(6);
    list->reverse();
    list->print();
    return 0;
}
