#include <initializer_list>
#include <iostream>
#include <stdexcept>

template <typename T>
class SingleLinkedList
{
private:

    class Node
    {
    private:
        T data;
        Node *next = nullptr;
        Node(T _val){data = _val;}
        friend class SingleLinkedList<T>;
    };

    Node* head = nullptr;
    int size = 0;
    Node* currentPos = nullptr;

    void _emptyList();
    void _copy(const SingleLinkedList<T> &_l);

public:
    /// 返回当前位置的值
    T getCurrentVal() const;
    /// 设置当前位置的值
    void setCurrentVal(const T &_val);
    /// 如果链表为空，返回 true；否则返回 false
    bool isEmpty() const;

    int getSize() const;
    void emptyList();
    bool find (const T &_val);


    SingleLinkedList(){};
    ~SingleLinkedList();

    SingleLinkedList(std::initializer_list<T> _l);
    SingleLinkedList(const SingleLinkedList<T> &_l);

    void printList() const;

    SingleLinkedList<T>& operator=(const SingleLinkedList<T> &_l);

    /// 在 currentPos 后面插入一个元素，数据为 _val
    void insert(T _val);

    /// 如果找到，返回 true, currentPos 停留在第一个 _val 的位置。
    /// 否则返回 false, currentPos 不动。
    bool find(const T &_val) const;

    /// 删除 currentPos 后面的元素
    void remove();
};

template<typename T>
bool SingleLinkedList<T>::find(const T &_val)
{
    Node *p = head;
    while (p != nullptr)
    {
        if (p->data == _val)
        {
            currentPos = p;
            return true;
        }
        p = p->next;
    }
    return false;
}

template<typename T>
int SingleLinkedList<T>::getSize() const
{
    return size;
}

template <typename T>
SingleLinkedList<T>::SingleLinkedList(std::initializer_list<T> _l)
{
    for (auto i = _l.begin(); i != _l.end(); ++i)
    {
        Node* newNode = new Node(*i); //新分配
        if (head == nullptr)
        {
            head = newNode;
            currentPos = head;
        }
        else
        {
            currentPos->next = newNode;
            currentPos = newNode;
        }
        ++size;
    }
}

template <typename T>
void SingleLinkedList<T>::_emptyList()
{
    Node* p = head;
    while (p != nullptr)
    {
        Node* t = p;
        p = p->next;
        delete t;
    }
}

template <typename T>
void SingleLinkedList<T>::printList() const
{
    Node* p = head;
    while (p != nullptr)
    {
        std::cout << p->data << "\t";
        p = p->next;
    }
    std::cout << std::endl;
}

template <typename T>
SingleLinkedList<T>::~SingleLinkedList()
{
    _emptyList();
};

template<typename T>
SingleLinkedList<T>::SingleLinkedList(const SingleLinkedList<T> &_l)
{
    _copy(_l);
}

template<typename T>
void SingleLinkedList<T>::emptyList()
{
    _emptyList();
    head = nullptr;
    currentPos = nullptr;
    size = 0;
}

template<typename T>
SingleLinkedList<T>& SingleLinkedList<T>::operator=(const SingleLinkedList<T> &_l)
{
    if (this == &_l)
        return *this;
    emptyList();
    _copy(_l);
    return *this;
}

template <typename T>
void SingleLinkedList<T>::_copy(const SingleLinkedList<T> &_l)
{
    Node *p = _l.head;
    while (p != nullptr)  //如果本来就有东西，调用_copy会在currentPos后面追加_l的内容
    {
        Node* newNode = new Node(p->data);

        if (head == nullptr)
        {
            head = newNode;
            currentPos = head;
        }
        else
        {
            currentPos->next = newNode;
            currentPos = newNode;
        }

        ++size;
        p = p->next;
    }
}



///////////////////////////////////HW////////////////////////////////////////////
/// 返回当前位置的值
template <typename T>
T SingleLinkedList<T>::getCurrentVal() const
{
    if(currentPos!=nullptr)
        return currentPos->data;
    else
        std::cout<< "Empty current position! Can't get value!"<<std::endl;
        exit(1);
        ///退出
}



/// 设置当前位置的值
template <typename T>
void SingleLinkedList<T>::setCurrentVal(const T &_val)
{
    if(currentPos!=nullptr)
        currentPos->data = _val;
    else
        std::cout <<"Empty current position! Can't set value!" << std::endl;
}


/// 如果链表为空，返回 true；否则返回 false
template <typename T>
bool SingleLinkedList<T>::isEmpty() const
{
    if (head==nullptr)
        return true;
    else
        return false;
}


/// 在 currentPos 后面插入一个元素，数据为 _val
template <typename T>
void SingleLinkedList<T>::insert(T _val)
{
    Node* newNode = new Node(_val);
    if (head == nullptr) ///若为空链表
    {
        head = newNode;
        currentPos = head;
        head->next = nullptr;
	size++;
    }
    else
    {
        Node* real_next = currentPos->next;
        currentPos->next = newNode;
        newNode->next = real_next;
        currentPos = currentPos->next;
        size ++;
    }
}


/// 删除 currentPos 后面的元素。若当前位置为空则不进行操作；若链表仅有一个元素则删除此元素成为空链表；若链表有超过一个元素且当前位置不为最后一个，则删除后一个元素.
template <typename T>
void SingleLinkedList<T>::remove()
{
    if (currentPos == nullptr)
        return; ///若根本为空，不操作返回


    if(size ==1) ///仅有一个元素，将成为空链表
    {
        emptyList();
        return;
    }

    ///若当前为最后一个，也不操作返回
    if (currentPos->next == nullptr)
        return;

    /// 若当前不为最后一个，则删除后一个
    Node* pt = currentPos->next;
    Node* real_next = pt->next;
    delete pt;
    currentPos->next = real_next;
    size --;
    return;

}
