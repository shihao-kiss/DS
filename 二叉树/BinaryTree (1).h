#pragma once
#include <queue>
#include <stack>

template<class T>
struct BinaryTreeNode
{
	T _data;
	BinaryTreeNode<T>* _left;
	BinaryTreeNode<T>* _right;

	BinaryTreeNode(const T& x)
		:_data(x)
		,_left(NULL)
		,_right(NULL)
	{}
};
template<class T>
class BinaryTree
{
public:
	BinaryTree()
		:_root(NULL)
	{}

	BinaryTree(const T* a, size_t size)
	{
		size_t index = 0;
		_root = _CreateTree(a, size, index);
	}

	~BinaryTree()
	{
		_Destroy(_root);
		_root = NULL;
	}

	BinaryTree(const BinaryTree<T>& t)
	{
		_root = _Copy(t._root);
	}

	/*BinaryTree<T>& operator= (const BinaryTree<T>& t)
	{
		if (this != &t)
		{
			this->_Destroy(_root);
			_root = _Copy(t._root);
		}
		return *this;
	}*/

	BinaryTree<T>& operator= (BinaryTree<T> t)
	{
		swap(_root, t._root);

		return *this;
	}

	void PrevOrder()
	{
		_PrevOrder(_root);
		cout<<endl;
	}

	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}

	void PostOrder()
	{
		_PostOrder(_root);
		cout<<endl;
	}

	void LevelOrder()
	{
		queue<BinaryTreeNode<T>*> q;
		if (_root)
			q.push(_root);

		while (!q.empty())
		{
			BinaryTreeNode<T>* front = q.front();
			q.pop();
			cout<<front->_data<<" ";

			if (front->_left)
			{
				q.push(front->_left);
			}

			if (front->_right)
			{
				q.push(front->_right);
			}
		}

		cout<<endl;
	}

	int Size()
	{
		int size = 0;
		_Size(_root, size);
		return size;
	}

	int Depth()
	{
		return _Depth(_root);
	}

	BinaryTreeNode<T>* Find(const T& x)
	{
		return _Find(_root, x);
	}

	void PrevOrder_NonR()
	{
		stack<BinaryTreeNode<T>*> s;
		if (_root)
			s.push(_root);

		while (!s.empty())
		{
			BinaryTreeNode<T>* top = s.top();
			s.pop();
			cout<<top->_data<<" ";
			
			if (top->_right)
			{
				s.push(top->_right);
			}

			if (top->_left)
			{
				s.push(top->_left);
			}
		}

		cout<<endl;
	}

	void InOrder_NonR()
	{
		stack<BinaryTreeNode<T>*> s;
		BinaryTreeNode<T>* cur = _root;
		while (cur || !s.empty())
		{
			// 将cur指向树的所有左路节点入栈
			while(cur)
			{
				s.push(cur);
				cur = cur->_left;
			}

			// 访问节点，并让cur指向右子树
			if (!s.empty())
			{
				BinaryTreeNode<T>* top = s.top();
				cout<<top->_data<<" ";
				s.pop();

				cur = top->_right;
			}
		}

		cout<<endl;
	}

	void PostOrder_NonR()
	{
		stack<BinaryTreeNode<T>*> s;
		BinaryTreeNode<T>* cur = _root;
		BinaryTreeNode<T>* prevVisited = NULL;
		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}

			BinaryTreeNode<T>* top = s.top();
			if (top->_right == NULL 
				|| top->_right == prevVisited)
			{
				cout<<top->_data<<" ";
				prevVisited = top;
				s.pop();
			}
			else
			{
				cur = top->_right;
			}
		}

		cout<<endl;
	}

	int GetLeafNum()
	{
		int num = 0;
		_GetLeafNum(_root, num);
		return num;
	}

protected:
	BinaryTreeNode<T>* _Copy(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
		{
			return NULL;
		}

		BinaryTreeNode<T>* newRoot = new BinaryTreeNode<T>(root->_data);
		newRoot->_left = _Copy(root->_left);
		newRoot->_right = _Copy(root->_right);

		return newRoot;
	}

	void _Destroy(BinaryTreeNode<T>*& root)
	{
		if (root == NULL)
		{
			return;
		}

		if (root->_left == NULL && root->_right == NULL)
		{
			delete root;
			root = NULL;
			return;
		}

		_Destroy(root->_left);
		_Destroy(root->_right);
		delete root;
	}

	BinaryTreeNode<T>* _CreateTree(const T* a,
		size_t size, size_t& index)
	{
		BinaryTreeNode<T>* root = NULL;
		if (index < size && a[index] != '#')
		{
			root = new BinaryTreeNode<T>(a[index]);
			root->_left = _CreateTree(a, size, ++index);
			root->_right = _CreateTree(a, size, ++index);
		}

		return root;
	}

	void _PrevOrder(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
			return;

		cout<<root->_data<<" ";
		_PrevOrder(root->_left);
		_PrevOrder(root->_right);
	}

	void _InOrder(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
		{
			return;
		}

		_InOrder(root->_left);
		cout<<root->_data<<" ";
		_InOrder(root->_right);
	}

	void _PostOrder(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
			return;

		_PostOrder(root->_left);
		_PostOrder(root->_right);
		cout<<root->_data<<" ";
	}

	/*int _Size(BinaryTreeNode<T>* root)
	{
		if (root==NULL)
		{
			return 0;
		}

		return _Size(root->_left) + _Size(root->_right) +1;
	}*/

	// 线程安全==》
	/*int _Size(BinaryTreeNode<T>* root)
	{
		static int size = 0;
		if (root == NULL)
		{
			return 0;
		}
		else
		{
			++size;
		}

		_Size(root->_left);
		_Size(root->_right);

		return size;
	}*/

	void _Size(BinaryTreeNode<T>* root, int& size)
	{
		if (root == NULL)
			return;
		else
			++size;

		_Size(root->_left, size);
		_Size(root->_right, size);
	}

	int _Depth(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
		{
			return 0;
		}

		int leftDepth = _Depth(root->_left);
		int rightDepth = _Depth(root->_right);

		return leftDepth > rightDepth ? leftDepth+1: rightDepth+1;

		//return _Depth(root->_left) > _Depth(root->_right) ? 
		//	_Depth(root->_left)+1 : _Depth(root->_right)+1;
	}

	BinaryTreeNode<T>* _Find(BinaryTreeNode<T>* root,
		const T& x)
	{
		if (root == NULL)
		{
			return NULL;
		}
		else if (root->_data == x)
		{
			return root;
		}
		else
		{
			BinaryTreeNode<T>* ret = _Find(root->_left, x);
			if (ret)
				return ret;
			else
				return _Find(root->_right, x);

		/*	if (_Find(root->_left, x))
				return _Find(root->_left, x);
			
			if (_Find(root->_right, x))
				return _Find(root->_right, x);

			return NULL;*/
		}
	}

	/*BinaryTreeNode<T>* FindParent(BinaryTreeNode<T>* child)
	{
		
	}*/

	void _GetLeafNum(BinaryTreeNode<T>* root, int& num)
	{
		if (root == NULL)
			return;

		if (root->_left == NULL && root->_right == NULL)
		{
			++num;
			return;
		}

		_GetLeafNum(root->_left, num);
		_GetLeafNum(root->_right, num);
	}

	//int _GetLeafNum(BinaryTreeNode<T>* root)
	//{
	//	static int num = 0;
	//	if (root == NULL)
	//	{
	//		return 0;
	//	}

	//	if (root->_left == NULL && root->_right == NULL)
	//	{
	//		++num;
	//		return num;
	//	}

	//	_GetLeafNum(root->_left);
	//	_GetLeafNum(root->_right);

	//	return num;
	//}


	/*int _GetLeafNum(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
		{
			return 0;
		}

		if (root->_left == NULL && root->_right == NULL)
		{
			return 1;
		}

		return _GetLeafNum(root->_left) + _GetLeafNum(root->_right);
	}*/

protected:
	BinaryTreeNode<T>* _root;
};

void Test1()
{
	/*int a[10] = {1, 2, 3, '#', '#', 4, '#' , '#', 5, 6};
	BinaryTree <int>t1(a, 10);
	t1.PrevOrder();
	t1.InOrder();
	t1.PostOrder();
	t1.LevelOrder();
	cout<<"Size:"<<t1.Size()<<endl;
	cout<<"Depth:"<<t1.Depth()<<endl;

	int a1[15] = {1,2,'#',3,'#','#',4,5,'#',6,'#',7,'#','#',8};
	BinaryTree <int>t2(a1, 15);
	t2.PrevOrder();
	cout<<"Size:"<<t2.Size()<<endl;
	cout<<"Depth:"<<t2.Depth()<<endl;

	cout<<t2.Find(8)->_data<<endl;
	cout<<t2.Find(10)<<endl;*/

	int a[10] = {1, 2, 3, '#', '#', 4, '#' , '#', 5, 6};
	BinaryTree <int>t1(a, 10);
	BinaryTree<int> t2(t1);
	t1.PrevOrder();
	t2.PrevOrder();

	//t1.PrevOrder();
	//t1.PrevOrder_NonR();

	//t1.InOrder();
	//t1.InOrder_NonR();

	//t1.PostOrder();
	//t1.PostOrder_NonR();
	//cout<<"叶子节点的个数:"<<t1.GetLeafNum()<<endl;
}

template<class T>
struct BinaryTreeNode_P
{
	T _data;
	BinaryTreeNode_P<T>* _left;
	BinaryTreeNode_P<T>* _right;
	BinaryTreeNode_P<T>* _parent;

	BinaryTreeNode_P(const T& x)
		:_data(x)
		,_left(NULL)
		,_right(NULL)
		,_parent(NULL)
	{}
};

template<class T>
class BinaryTree_P
{
public:
	BinaryTree_P(const T* array, size_t size)
	{
		size_t index = 0; 
		_root = _CreateTree(array, size, index);
	}

	BinaryTreeNode_P<T>* _CreateTree(const T* array,
		size_t size, size_t& index)
	{
		BinaryTreeNode_P<T>* root = NULL;
		if (index < size && array[index] != '#')
		{
			root = new BinaryTreeNode_P<T>(array[index]);
			root->_left = _CreateTree(array, size, ++index);
		
			if (root->_left)
			{
				root->_left->_parent = root;
			}

			root->_right = _CreateTree(array, size, ++index);

			if (root->_right)
			{
				root->_right->_parent = root;
			}
		}

		return root;
	}

protected:
	BinaryTreeNode_P<T>* _root;
};

void Test2()
{
	int a[10] = {1, 2, 3, '#', '#', 4, '#' , '#', 5, 6};
	BinaryTree_P <int>t1(a, 10);
}