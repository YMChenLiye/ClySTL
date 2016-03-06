#ifndef BinarySearchTree_h
#define BinarySearchTree_h

template<typename Comparable>
class BinarySearchTree{
	public:
		BinarySearchTree();
		BinarySearchTree(const BinarySearchTree& rhs);
		~BinarySearchTree();

		const Comparable& findMin() const;
		const Comparable& findMax() const;
		bool contains(const Comparable & x) const;
		bool isEmpty() const;
		void printTree() const;

		void makeEmpty();
		void insert(const Comparable & x);
		void remove(const Comparable & x);

		const BinarySearchTree & operator=(const BinarySearchTree & rhs);

	private:
		struct BinaryNode{
			Comparable element;
			BinaryNode *left;
			BinaryNode *right;

			BinaryNode(const Comparable & theElement,BinaryNode *lt,BinaryNode *rt)
				:element(theElement),left(lt),right(rt) { }
		};

		BinaryNode *root;

		void insert(const Comparable & x,BinaryNode * t) const;
		void remove(const Comparable & x,BinaryNode * t) const;
		BinaryNode * findMin(BinaryNode * t) const;
		BinaryNode * findMax(BinaryNode * t) const;
		bool contains(const Comparable & x,BinaryNode * t) const;
		void makeEmpty(BinaryNode * t);
		void printTree(BinaryNode * t) const ;
		BinaryNode * clone(BinaryNode * t) const;
};

	template<typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(const BinarySearchTree & rhs)
{
	root = rhs.root;
}

	template<typename Comparable>
BinarySearchTree<Comparable>::~BinarySearchTree()
{
	makeEmpty();
}

template<typename Comparable>
const Comparable & BinarySearchTree<Comparable>::findMin() const 
{
	return findMin(root)->element;
}

template<typename Comparable>
const Comparable & BinarySearchTree<Comparable>::findMax() const
{
	return findMax(root)->element;
}

template<typename Comparable>
bool BinarySearchTree<Comparable>::contains(const Comparable & x) const
{
	return contains(x,root);
}

template<typename Comparable>
bool BinarySearchTree<Comparable>::isEmpty() const 
{
	return root == nullptr;
}

template<typename Comparable>
void BinarySearchTree<Comparable>::printTree() const
{
	printTree(root);
}

	template<typename Comparable>
void BinarySearchTree<Comparable>::makeEmpty()
{
	makeEmpty(root);
}

	template<typename Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable & x)
{
	insert(x,root);
}

	template<typename Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable & x)
{
	remove(x,root);
}

	template<typename Comparable>
const BinarySearchTree<Comparable> & BinarySearchTree<Comparable>::operator=(const BinarySearchTree & rhs)
{
	if(this != &rhs)
	{
		makeEmpty();
		root = clone(rhs.root);
	}
	return *this;

}

template<typename Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable & x,BinaryNode * t) const
{
	if( t == nullptr)
		t = new BinaryNode(x,nullptr,nullptr);
	else if(x < t->element)
		insert(x,t->left);
	else if(t->left < x)
		insert(x,t->right);
	else ;//do nothing
}

template<typename Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable & x,BinaryNode * t) const
{
	if( t == nullptr )
		return ;// item not found;do nothing
	if(x < t->element)
		remove(x,t->left);
	else if(t->element < x)
		remove(x,t->right);
	else if(t->left != nullptr && t->right != nullptr) // two children
	{
		t->element = findMin(t->right)->element;
		remove(t->element,t->right);
	}
	else
	{
		BinaryNode * oldNode = t;
		t = (t->left != nullptr) ? t->left : t->right;
		delete oldNode;
	}
}

template<typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode * BinarySearchTree<Comparable>::findMin(BinaryNode * t) const
{
	if( t == nullptr )
		return nullptr;
	if(t->left == nullptr)
		return t;
	return findMin(t->left);
}

template<typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode * BinarySearchTree<Comparable>::findMax(BinaryNode * t) const
{
	if(t != nullptr)
		while(t->right != nullptr)
			t = t->right;
	return t;
}

template<typename Comparable>
bool BinarySearchTree<Comparable>::contains(const Comparable & x,BinaryNode * t) const 
{
	if(t == nullptr)
		return false;
	else if( x < t->element)
		return contains(x,t->left);
	else if(t->element < x)
		return contains(x,t->right);
	else
		return true;//match
}

	template<typename Comparable>
void BinarySearchTree<Comparable>::makeEmpty(BinaryNode * t)
{
	if(t != nullptr)
	{
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}
	t = nullptr;
}

template<typename Comparable>
void BinarySearchTree<Comparable>::printTree(BinaryNode * t) const
{
	if(t != nullptr)
	{
		printTree(t->left);
		printTree(t->right);
		//print t->element;
	}
}

template<typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode * BinarySearchTree<Comparable>::clone(BinaryNode * t) const
{
	if( t==nullptr)
		return nullptr;
	return new BinaryNode(t->element,clone(t->left),clone(t->right));
}


#endif
