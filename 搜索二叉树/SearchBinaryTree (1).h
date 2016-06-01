#pragma once

// 过滤
//template<class K>

template<class K, class V>
struct BSTNode
{
	// KV
	K _key;
	V _value;

	BSTNode<K, V>* _left;
	BSTNode<K, V>* _right;

	BSTNode(const K& key, const V& value)
		:_key(key)
		,_value(value)
		,_left(NULL)
		,_right(NULL)
	{}
};

// set/map ==> 红黑树 == pair

//template<class K, class V>
//struct pair
//{
//	K _first;
//	V _second;
//};

template<class K, class V>
class BSTree
{
	typedef BSTNode<K, V> Node;
public:
	BSTree()
		:_root(NULL)
	{}

	~BSTree()
	{}

	//pair<bool, Node*> Insert(const K& key, const V& value)
	bool Insert(const K& key, const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
			return true;
		}

		Node* parent = NULL;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}

		if (parent->_key < key)
			parent->_right = new Node(key, value);
		else
			parent->_left = new Node(key, value);

		return true;
	}

	bool Insert_R(const K& key, const V& value)
	{
		return _Insert_R(_root, key, value);
	}
	
	bool _Insert_R(Node* & root, const K& key, const V& value)
	{
		if (root == NULL)
		{
			root = new Node(key, value);
			return true;
		}

		if (root->_key > key)
		{
			return _Insert_R(root->_left, key, value);
		}
		else if (root->_key < key)
		{
			return _Insert_R(root->_right, key, value);
		}
		else
		{
			return false;
		}
	}

	Node* Find(const K& key)
	{
		Node* cur = _root;
		while(cur)
		{
			if (cur->_key > key)
			{
				cur = cur->_left;
			}
			else if (cur->_key < key)
			{
				cur = cur->_right;
			}
			else
			{
				return cur;
			}
		}

		return NULL;
	}

	Node* Find_R(const K& key);

	bool Remove(const K& key)
	{
		if (_root == NULL)
		{
			return false;
		}
		else if (_root->_left == NULL && _root->_right == NULL)
		{
			delete _root;
			_root = NULL;
			return true;
		}

		Node* parent = NULL;
		Node* del = _root;
		while (del)
		{
			if (del->_key > key)
			{
				parent = del;
				del = del->_left;
			}
			else if (del->_key < key)
			{
				parent = del;
				del = del->_right;
			}
			else
			{
				break;
			}
		}

		if (del)
		{
			// 左树为空，则用右树调补
			if (del->_left == NULL)
			{
				if (del == _root)
				{
					_root = del->_right;
				}
				else
				{
					if(del == parent->_left)
						parent->_left = del->_right;
					else
						parent->_right = del->_right;

				}
			}
			else if (del->_right == NULL)
			{
				if (del == _root)
				{
					_root = del->_left;
				}
				else
				{
					if(del == parent->_left)
						parent->_left = del->_left;
					else
						parent->_right = del->_left;
				}
			}
			else
			{
				// 查找右子树的中序遍历的第一个节点
				Node* subRight = del->_right; 
				Node* firstInOrder = del->_right;
				Node* parent = del;
				while(firstInOrder->_left)
				{
					parent = firstInOrder;
					firstInOrder = firstInOrder->_left;
				}

				swap(del->_key, firstInOrder->_key);
				swap(del->_value, firstInOrder->_value);

				if (firstInOrder == parent->_left)
				{
					parent->_left = firstInOrder->_right;
				}
				else
				{
					parent->_right = firstInOrder->_right;
				}

				del = firstInOrder;
			}

			delete del;
		}
		else
		{
			return false;
		}

		return true;
	}

	bool Remove_R(const K& key)
	{
		return _Remove_R(_root, key);
	}

	bool _Remove_R(Node*& root, const K& key)
	{
		if (root == NULL)
		{
			return false;
		}

		if (root->_key < key)
		{
			return _Remove_R(root->_right, key);
		}
		else if (root->_key > key)
		{
			return _Remove_R(root->_left, key);
		}
		else
		{
			Node* del = root;
			if (root->_left == NULL)
			{
				root = root->_right;
				delete del;
			}
			else if (root->_right == NULL)
			{
				root = root->_left;
				delete del;
			}
			else
			{
				Node* firstInOrder = root->_right;
				while (firstInOrder->_left)
				{
					firstInOrder = firstInOrder->_left;
				}

				swap(del->_key, firstInOrder->_key);
				swap(del->_value, firstInOrder->_value);

				return _Remove_R(root->_right, key);
			}
		}
	}

	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}

	void _InOrder(Node* root)
	{
		if (root == NULL)
			return;

		_InOrder(root->_left);
		cout<<root->_key<<" ";
		_InOrder(root->_right);
	}

protected:
	Node* _root;
};

void Test1()
{
	int a[] = {5,3,4,1,7,8,2,6,0,9};

	BSTree<int, double> t1; 
	for (int i = 0; i < sizeof(a)/sizeof(int);++i)
	{
		//t1.Insert(a[i], a[i]);
		t1.Insert_R(a[i], a[i]);
	}

	t1.InOrder();

	/*t1.Remove(2);
	t1.InOrder();

	t1.Remove(8);
	t1.InOrder();*/

	//t1.Remove(7);
	//t1.InOrder();

	for (int i = 0; i < sizeof(a)/sizeof(int);++i)
	{
		//t1.Insert(a[i], a[i]);
		t1.Remove_R(a[i]);
	}

	t1.InOrder();
}