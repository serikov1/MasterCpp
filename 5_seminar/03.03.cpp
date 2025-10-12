#include<cassert>
#include<iostream>

class List
{
public:

    bool empty() const
    {
        return head == nullptr;
    }

    void show() const
    {
        Node* current = head;
        while(current)
        {
            std::cout << current->value;
            current = current->next_node;
            if(current)
            {
                std::cout << ", ";
            }
        }
        std::cout << "\n";
    }

    void push_front(int value)
    {
        Node* node = new Node{value, head};
        head = node;
        if(tail == nullptr)
        {
            tail = node;
        }
    }

    void push_back(int value)
    {
        Node* node = new Node{value, nullptr};
        if(tail)
        {
            tail->next_node = node;
            tail = node;
        }
        else
        {
            tail = head = node;
        }
    }

    void pop_back()
    {
        if(empty())
        {
            return;
        }
        if(tail == head)
        {
            delete head;
            head = tail = nullptr;
            return;
        }

        Node* prev = head;
        while(prev->next_node != tail)
        {
            prev = prev->next_node;
        }

        delete tail;
        tail = prev;
        tail->next_node = nullptr;
    }

    void pop_front()
    {
        if(empty())
        {
            return;
        }

        Node* copy = head;
        head = head->next_node;
        delete copy;

        if(head == nullptr)
        {
            tail = nullptr;
        }
    }

    int get() const
    {
        if(empty())
        {
            return NULL;
        }

        Node* slow = head;
        Node* fast = head;

        while (fast && fast->next_node)
        {
            slow = slow->next_node;
            fast = fast->next_node->next_node;
        }

        return slow->value;
    }

    ~List()
    {
        while (head)
        {
            Node* copy = head;
            head = head->next_node;
            delete copy;
        }
        tail = nullptr;
    }

private:

    struct Node
    {
        int value = 0;
        Node* next_node = nullptr;
    };

    Node* head = nullptr;
    Node* tail = nullptr;
};

int main()
{
    List list;
    assert(list.empty());

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.push_front(5);
    list.push_front(2);

    std::cout << "List show() method: ";
    list.show();


    assert(!list.empty());


    int middle = list.get();
    std::cout << "Middle element of the list is: " << middle << "\n";
    assert(middle == 10);


    list.pop_front();
    list.pop_back();
    std::cout << "After front and back pop: ";
    list.show();

    assert(list.get() == 10);


    list.pop_front();
    list.pop_front();
    list.pop_front();
    assert(list.empty());

    return 0;
}