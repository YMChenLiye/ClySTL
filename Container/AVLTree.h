#ifndef AVLTree_h
#define AVLTree_h

template<typename Comparable>
class AVLTree{
	public:
		AVLTree();
		AVLTree(const AVLTree & rhs);
		~AVLTree();

		const Comparable& findMin() const;
		const Comparable& findMax() const;
		bool contains(const Comparable & x) const;
		bool isEmpty() const;
		void printTree() const;

		void makeEmpty();
		void insert(const Comparable & x);
		void remove(const Comparable & x);

		const AVLTree& operator=(const AVLTree & rhs);

	private:
		struct AVLNode{
			Comparable element;
			AVLNode * left;
			AVLNode * right;
			int height;

			AVLNode(const Comparable & theElement,AVLNode *lt,AVLNode *rt,int h=0)
				:element(theElement),left(lt),right(rt),height(h) { }
		};

		AVLNode * root;
		int max(int a,int b) { return a>b ? a : b; }
		int height(AVLNode * t) { return t==nullptr ? -1 : t->height; }

		void rotateWithLeftChild(AVLNode * & t);
		void rotateWithRightChild(AVLNode * & t);
		void doubleWithLeftChild(AVLNode * & t);
		void doubleWithRightChild(AVLNode * & t);

		void insert(const Comparable & x,AVLNode * t);
		void remove(const Comparable & x,AVLNode * t);
		AVLNode * findMin(AVLNode * t) const;
		AVLNode * findMax(AVLNode * t) const;
		bool contains(const Comparable & x,AVLNode * t) const;
		void makeEmpty(AVLNode * t);
		void printTree(AVLNode * t) const;
		AVLNode * clone(AVLNode * t) const;
};

template<typename Comparable>
AVLTree<Comparable>::AVLTree():root(nullptr) { }

	template<typename Comparable>
AVLTree<Comparable>::AVLTree(const AVLTree &rhs)
{
	root = clone(rhs.root);
}

	template<typename Comparable>
AVLTree<Comparable>::~AVLTree()
{
	makeEmpty();
}

template<typename Comparable>
const Comparable& AVLTree<Comparable>::findMin() const
{
	return findMin(root)->element;
}

template<typename Comparable>
const Comparable& AVLTree<Comparable>::findMax() const
{
	return findMax(root)->element;
}

template<typename Comparable>
bool AVLTree<Comparable>::contains(const Comparable & x) const
{
	return contains(x,root);
}

template<typename Comparable>
bool AVLTree<Comparable>::isEmpty() const
{
	return root == nullptr;
}

template<typename Comparable>
void AVLTree<Comparable>::printTree() const
{
	printTree(root);
}

	template<typename Comparable>
void AVLTree<Comparable>::makeEmpty()
{
	makeEmpty(root);
}

	template<typename Comparable>
void AVLTree<Comparable>::insert(const Comparable & x)
{
	insert(x,root);
}

	template<typename Comparable>
void AVLTree<Comparable>::remove(const Comparable & x)
{
	remove(x,root);
}

	template<typename Comparable>
const AVLTree<Comparable>& AVLTree<Comparable>::operator=(const AVLTree & rhs)
{
	makeEmpty();
	root = clone(rhs.root);
}

	template<typename Comparable>
void AVLTree<Comparable>::rotateWithLeftChild(AVLNode * & k2)
{
	AVLNode *k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = max(height(k2->left),height(k2->right)) + 1;
	k1->height = max(height(k1->left),height(k1->right)) + 1;
	k2 = k1;
}

	template<typename Comparable>
void AVLTree<Comparable>::rotateWithRightChild(AVLNode * & k2)
{
	AVLNode * k1 = k2->right;
	k2->right = k1->left;
	k1->left = k2;
	k2->height = max(height(k2->left),height(k2->right)) + 1;
	k1->height = max(height(k1->left),height(k1->right)) + 1;
	k2 = k1;
}

	template<typename Comparable>
void AVLTree<Comparable>::doubleWithLeftChild(AVLNode * & k3)
{
	rotateWithRightChild(k3->left);
	rotateWithLeftChild(k3);
}

	template<typename Comparable>
void AVLTree<Comparable>::doubleWithRightChild(AVLNode * & k3)
{
	rotateWithLeftChild(k3->right);
	rotateWithRightChild(k3);
}

	template<typename Comparable>
void AVLTree<Comparable>::insert(const Comparable & x,AVLNode * t)
{
	if(t==nullptr)
		t = new AVLNode(x,nullptr,nullptr);
	else if( x < t->element)
	{
		insert(x,t->left);
		if(height(t->left) - height(t->right) == 2)
		{
			if(x < t->left->element)
				rotateWithLeftChild(t);
			else
				doubleWithLeftChild(t);
		}
	}
	else if(t->element < x)
	{
		insert(x,t->right);
		if(height(t->right) - height(t->left) == 2)
		{
			if(t->right->element < x)
				rotateWithRightChild(t);
			else
				doubleWithRightChild(t);
		}
	}
	else
		;//duplicate;do nothing
	t->height = max(height(t->left),height(t->right)) + 1;
}

	template<typename Comparable>
void AVLTree<Comparable>::remove(const Comparable & x,AVLNode * t)
{
	//to do
	//because this operate will destroy the balance of the avltree
	//我们可以使用伪删除，标记这个节点已被删除
}

template<typename Comparable>
typename AVLTree<Comparable>::AVLNode * AVLTree<Comparable>::findMin(AVLNode * t) const
{
	if( t == nullptr)
		return nullptr;
	if(t->left == nullptr)
		return t;
	return findMin(t->left);
}

template<typename Comparable>
typename AVLTree<Comparable>::AVLNode * AVLTree<Comparable>::findMax(AVLNode * t) const
{
	if(t == nullptr)
		return nullptr;
	if(t->right == nullptr)
		return t;
	return findMax(t->right);
}

template<typename Comparable>
bool AVLTree<Comparable>::contains(const Comparable & x,AVLNode * t) const
{
	if(t == nullptr)
		return false;
	else if(x < t->element)
		return contains(x,t->left);
	else if(t->element < x)
		return contains(x,t->right);
	else
		return true;
}

	template<typename Comparable>
void AVLTree<Comparable>::makeEmpty(AVLNode * t)
{
	if( t != nullptr)
	{
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}
	t = nullptr;
}

template<typename Comparable>
void AVLTree<Comparable>::printTree(AVLNode * t) const
{
	if(t != nullptr)
	{
		printTree(t->left);
		printTree(t->right);
		//print t->element
	}
}

template<typename Comparable>
typename AVLTree<Comparable>::AVLNode * AVLTree<Comparable>::clone(AVLNode * t) const
{
	if(t == nullptr)
		return nullptr;
	return new AVLNode(t->element,clone(t->left),clone(t->right));
}




#endif
