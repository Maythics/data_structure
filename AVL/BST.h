/**
 * @file BST.h
 * @author M. A. Weiss (you@domain.com)
 * @brief 课本代码的注释和改进
 * @version 0.1
 * @date 2024-10-29
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>

/// 临时性的异常类，用于表示树为空的异常
class UnderflowException { };
class IllegalArgumentException { };
class ArrayIndexOutOfBoundsException { };
class IteratorOutOfBoundsException { };
class IteratorMismatchException { };
class IteratorUninitializedException { };

/**
 * @brief 二叉搜索树模板类
 *
 * @tparam Comparable 模板参数，表示树中存储的元素类型
 */
template <typename Comparable>
class BinarySearchTree
{
public:
    /**
     * @brief 默认构造函数
     *
     * 初始化一个空的二叉搜索树。
     */
    BinarySearchTree() : root{ nullptr } {}

    /**
     * @brief 拷贝构造函数
     *
     * 创建一个新树，它是给定树的深拷贝。这里相比课本代码，引用更直接，有利于编译器优化。
     *
     * @param rhs 要拷贝的二叉搜索树
     */
    BinarySearchTree(const BinarySearchTree &rhs) : root{ clone(rhs.root) } {}

    /**
     * @brief 移动构造函数
     *
     * 将给定树的资源转移到新树中。这里 noexcept 用于指示该函数不会抛出异常。
     * 因为移动构造不涉及内存分配，所以不会抛出异常。这里显式声明 noexcept 是为了提高性能。
     * 让编译器知道这个函数不会抛出异常，从而优化代码。
     *
     * @param rhs 要移动的二叉搜索树
     */
    BinarySearchTree(BinarySearchTree &&rhs) noexcept : root{ rhs.root } {
        rhs.root = nullptr;
    }

    /**
     * @brief 析构函数
     *
     * 释放树中所有节点占用的内存。
     */
    ~BinarySearchTree() {
        makeEmpty();
    }

    /**
     * @brief 查找并返回树中的最小元素
     *
     * 这是一个公有接口，它调用了私有的递归函数。
     *
     * @return 最小元素的引用
     */
    const Comparable &findMin() const {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin(root)->element;
    }

    /**
     * @brief 查找并返回树中的最大元素
     *
     * @return 最大元素的引用
     */
    const Comparable &findMax() const {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax(root)->element;
    }

    /**
     * @brief 检查树中是否包含指定的元素
     *
     * @param x 要查找的元素
     * @return 如果树中包含该元素，则返回 true；否则返回 false
     */
    bool contains(const Comparable &x) const {
        return contains(x, root);
    }

    /**
     * @brief 检查树是否为空
     *
     * @return 如果树为空，则返回 true；否则返回 false
     */
    bool isEmpty() const {
        return root == nullptr;
    }

    /**
     * @brief 打印树的结构
     *
     * 将树的结构输出到指定的输出流，默认输出到标准输出流。
     *
     * @param out 输出流，默认为 std::cout
     */

    void printTree(std::ostream &out = std::cout) const {
         if (isEmpty()) {
            out << "Empty tree" << std::endl;
        } else {
            printTree(root, out);
        }
    }

    /**
     * @brief 清空树中的所有元素
     *
     * 释放树中所有节点占用的内存，使树变为空。
     */
    void makeEmpty() {
        makeEmpty(root);
    }

    /**
     * @brief 插入一个常量引用元素到树中
     *
     * @param x 要插入的元素
     */
    void insert(const Comparable &x) {
        insert(x, root);
    }

    /**
     * @brief 插入一个右值引用元素到树中
     *
     * @param x 要插入的元素
     */
    void insert(Comparable &&x) {
        insert(std::move(x), root);
    }

    /**
     * @brief 从树中移除指定的元素
     *
     * @param x 要移除的元素
     */
    void remove(const Comparable &x) {
        remove(x, root);
    }

    /**
     * @brief 拷贝赋值运算符
     *
     * 将一个树的资源拷贝到当前树中。对自赋值进行了排除。
     *
     * @param rhs 要拷贝的二叉搜索树
     * @return 当前树的引用
     */
    BinarySearchTree &operator=(const BinarySearchTree &rhs) {
    if (this != &rhs) {
        BinarySearchTree temp(rhs);
        std::swap(root, temp.root);
    }
    return *this;
    }


    /**
     * @brief 移动赋值运算符
     *
     * 将一个树的资源移动到当前树中。
     *
     * @param rhs 要移动的二叉搜索树
     * @return 当前树的引用
     */
    BinarySearchTree &operator=(BinarySearchTree &&rhs) noexcept {
        std::swap(root, rhs.root);
        return *this;
    }

protected:

    /**
     * @brief 二叉树节点结构体
     */
    struct BinaryNode
    {
        Comparable element;  ///< 节点存储的元素
        BinaryNode *left;    ///< 左子节点指针
        BinaryNode *right;   ///< 右子节点指针
        int height; ///< 树中该节点高度

        /**
         * @brief 构造函数，接受常量引用
         *
         * @param theElement 要存储的元素
         * @param lt 左子节点指针
         * @param rt 右子节点指针
         */
        BinaryNode(const Comparable &theElement, BinaryNode *lt, BinaryNode *rt, int h=1) ///根据要求，初始化为1
            : element{ theElement }, left{ lt }, right{ rt }, height{ h }{}
        /**
         * @brief 构造函数，接受右值引用
         *
         * @param theElement 要存储的元素
         * @param lt 左子节点指针
         * @param rt 右子节点指针
         */
        BinaryNode(Comparable &&theElement, BinaryNode *lt, BinaryNode *rt,int h =1) ///根据要求，初始化为1
            : element{ std::move(theElement) }, left{ lt }, right{ rt },height{ h }{}

    };

    BinaryNode *root;  ///< 树的根节点指针

    /**
     * @brief 递归查找最小元素
     *
     * @param t 当前节点指针
     * @return 最小元素所在的节点指针
     */
    BinaryNode *findMin(BinaryNode *t) const {
        /// 从一个空节点开始查找，返回空指针
        if (t == nullptr) {
            return nullptr;
        }
        /// 向左无路了，当前节点就是最小元素
        if (t->left == nullptr) {
            return t;
        }
        /// 否则继续向左查找
        return findMin(t->left);
    }

    /**
     * @brief 递归查找最大元素
     *
     * @param t 当前节点指针
     * @return 最大元素所在的节点指针
     */
    BinaryNode *findMax(BinaryNode *t) const {
        /// 这里没有使用递归，而是使用循环，更高效
        /// findMin 也可以改成循环实现
        if (t != nullptr) {
            while (t->right != nullptr) {
                t = t->right;
            }
        }
        return t;
    }

    /**
     * @brief 递归检查树中是否包含指定的元素
     *
     * @param x 要查找的元素
     * @param t 当前节点指针
     * @return 如果树中包含该元素，则返回 true；否则返回 false
     */
    bool contains(const Comparable &x, BinaryNode *t) const {
        /// 这是递归版本，也可以有循环版本
        if (t == nullptr) {
            return false;
        }
        if (x < t->element) {
            return contains(x, t->left);
        }
        else if (x > t->element) {
            return contains(x, t->right);
        }
        else {
            return true;  // 找到元素
        }
    }

    /**
     * @brief 递归打印树的结构
     *
     * @param t 当前节点指针
     * @param out 输出流
     */
    void printTree(BinaryNode *t, std::ostream &out) const {
        /// 中序遍历
        if (t != nullptr) {
            printTree(t->left, out);  // 先打印左子树
            out << t->element << std::endl;  // 打印当前节点
            printTree(t->right, out);  // 再打印右子树
        }
    }

    /**
     * @brief 递归清空树中的所有元素
     *
     * @param t 当前节点指针
     */
    void makeEmpty(BinaryNode * &t) {
        /// 这必须是一个后序遍历，为什么？
        if (t != nullptr) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
            /// delete 并不会自动将指针置空，这里需要手动置空
            t = nullptr;
        }
    }

    /**
     * @brief 递归插入一个常量引用元素到树中
     *
     * @param x 要插入的元素
     * @param t 当前节点指针
     */
    void insert(const Comparable &x, BinaryNode * &t) {
        /// 这句话乍一看不可思异，怎么能对一个空指针赋值呢？
        /// 但是这里是引用，所以实际上是对指针 t 的引用，t 现在存了 nullptr,
        /// 所以可以修改指针 t 的值
        if (t == nullptr) {
            /// 创建一个新节点，包含 x 的值，左右子节点为空
            /// 挂在 t 指向的节点上
            /// 而在递归过程中，t 总是会指向父节点的左子节点或右子节点
            /// 所以这里实际上是将新节点挂在父节点的左子节点或右子节点上
            t = new BinaryNode{x, nullptr, nullptr};
        } else if (x < t->element) {
            insert(x, t->left);
        } else if (x > t->element) {
            insert(x, t->right);
        } else {
            /// 如果元素已存在，则不进行插入
            /// 这种情况不可遗漏，严格的规则中也可以抛出异常
        }
        balance(t); /// 为了通用的目的，可以增加一个balance
    }

    /**
     * @brief 递归插入一个右值引用元素到树中
     *
     * @param x 要插入的元素
     * @param t 当前节点指针
     */
    void insert(Comparable &&x, BinaryNode * &t) {
        /// 一样的逻辑
        if (t == nullptr) {
            t = new BinaryNode{std::move(x), nullptr, nullptr};
        } else if (x < t->element) {
            insert(std::move(x), t->left);
        } else if (x > t->element) {
            insert(std::move(x), t->right);
        } else {
            // 如果元素已存在，则不进行插入
        }
    }


    /**
     * @brief 递归克隆树的结构
     *
     * @param t 当前节点指针
     * @return 新的节点指针
     */
    BinaryNode *clone(BinaryNode *t) const {
        if (t == nullptr) {
            return nullptr;
        }
        return new BinaryNode{t->element, clone(t->left), clone(t->right)};
    }

//////////////////////////////*以下为作业部分*////////////////////////////////////////////////

    void remove(const Comparable &x, BinaryNode *&t) {
        /// 逻辑其实是 find and remove, 从 t 开始
        if (t == nullptr) {
            return;  /// 空，啥都不做
        }
        if (x < t->element) {
            remove(x, t->left);
        } else if (x > t->element) {
            remove(x, t->right);
        }
        /// 进入以下这两个分支，都是说明找到了要删除的元素
        else if (t->left != nullptr && t->right != nullptr) {
            /// 有两个子节点
            BinaryNode* successor = detachMin(t->right); /// 用detach传回该待删除的节点的继任者（右子树最小）
            successor->left = t->left;   /// 该继任者把t的左子树接来
            successor->right = t->right; /// 该继任者把t的左子树接来
            delete t; ///把该节点释放
            t = successor;
        } else {
            /// 有一个或没有子节点的情形是简单的
            BinaryNode *oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode;
        }
        balance(t); /// remove结束后，进行树的平衡（由于递归，仅需对t balance）
    }

    BinaryNode *detachMin(BinaryNode *&t){
        if (t == nullptr) {
            return nullptr; /// 为空直接返回
        }
        /// 向左无路了，则当前节点就是最小元素，进行脱离操作
        if (t->left == nullptr) {
            BinaryNode *detached = t; /// 先用一个指针把即将解除的节点记下来
            /// 由于已经是最小元素没有左子树，因此
            t = t->right; /// 将该节点的右子树接回去,也可能为nullptr
            return detached;
        }
        /// 否则继续向左查找
        BinaryNode *detachedptr =  detachMin(t->left);
        balance(t); ///执行了递归后，到这句话时，底下的结构已经动过了，所以需要balance一下
        return detachedptr;

    }

    int height( BinaryNode *t ) const
        {
            return t == nullptr ? 0 : t->height;
        }

    int max(int a,int b) const
    {
        return a>b?a:b;
    }

    void balance( BinaryNode * & t )
    {
        if( t == nullptr )
            return; /// 空，直接返回

        if( height( t->left ) - height( t->right ) > 1)
            if( height( t->left->left ) >= height( t->left->right ) ) /// 如果左单调增大两层，case1
                rotateWithLeftChild( t );
            else /// 否则是case2
                doubleWithLeftChild( t );
        else
        if( height( t->right ) - height( t->left ) > 1)
            if( height( t->right->right ) >= height( t->right->left ) ) /// 如果右单调增大两层，case4
                rotateWithRightChild( t );
            else /// 否则是case3
                doubleWithRightChild( t );

        t->height = max(height( t->left ), height( t->right ))  + 1; /// 更新该层高度（别的子节点高度已在调用的函数里更新了）
        ///std::cout<< t->height<< "height"<< std::endl;
    }

    void rotateWithLeftChild( BinaryNode * & t) /// 参照教材Fig 4.34写
    {
        BinaryNode * k2 = t;
        BinaryNode * k1 = t->left;
        k2->left = k1->right; /// 先把k2的左边连到Y子树
        k1->right = k2; /// 父子地位转化
        t = k1;
        /// 最后，别忘更新height
        k1->height = max(height(k1->left), height(k1->right))+1;
        k2->height = max(height(k2->left), height(k2->right))+1;

    }

    void rotateWithRightChild( BinaryNode * & t) /// 同上面一段，参照教材Fig 4.36写
    {
        BinaryNode * k1 = t;
        BinaryNode * k2 = t->right;
        k1->right = k2->left; /// 先把k1的右边连到Y子树
        k2->left = k1; /// 父子地位转化
        t = k2;
        /// 最后，别忘更新height
        k1->height = max(height(k1->left), height(k1->right))+1;
        k2->height = max(height(k2->left), height(k2->right))+1;

    }

    void doubleWithLeftChild( BinaryNode * & t) /// 参照教材Fig4.38
    {
        rotateWithRightChild(t->left);/// 先把k1和k2处理好
        rotateWithLeftChild(t);/// 此刻的t仍是k3，执行完该句后成为k2
    }

    void doubleWithRightChild( BinaryNode * & t) /// 参照教材Fig4.39
    {
        rotateWithLeftChild(t->right);/// 先把k2和k3处理好
        rotateWithRightChild(t);/// 此刻的t仍是k1，执行完该句后成为k2
    }

/////////////////////////////////////////////////////////////////////////////

};


