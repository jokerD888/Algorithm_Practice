// SizeBalanceTree SB树---------------------------------------------------------------------------------
//	SBT是一种通过大小（Size）域来保持平衡的二叉搜索树，对于平衡限制没有AVL那么严格，实际竞赛中较易改写,仅在添加时才进行平衡性的调整（Maintain)
// 特性：即每棵子树的大小不小于其兄弟的子树大小。	简单来说，即叔叔节点个数不小于侄子节点个数
//	即1. t.right.s ≥ t.le ft.le ft.s且t.right.s > t.left.right.s
//    2. t.left.s > t.right.le ft.s且t.le ft.s ≥ t.right.right.s
// 其四种违规类型类似AVL,LL,LR,RL,RR,不过违规的是叔侄间的节点数量关系,同时也会有多种违规一同出现，如LL和LR,RR和RL,处理和AVL相同，分别按LL和RR处理
class Code01_SizeBalancedTreeMap {
public:
	template<typename K, typename V>
	class SBTNode {
	public:
		K key;
		V value;
		SBTNode* left;
		SBTNode* right;
		int size;
		SBTNode(K k, V v) :key(k), value(v), size(1),left(nullptr),right(nullptr) {}
	};

	template<typename K, typename V>
	class SizeBalancedTreeMap {
	public:
		using SBTNode = SBTNode<K, V>;
		SBTNode* root;
		SizeBalancedTreeMap():root(nullptr){}
		SBTNode* RightRotate(SBTNode* cur) {
			// 右旋
			SBTNode* leftNode = cur->left;
			cur->left = leftNode->right;
			leftNode->right = cur;
			// 节点数量调整,cur 和 leftNode 的结构发生了变化，进行调整
			leftNode->size = cur->size;		// leftNode作为新头，节点数量直接为原头的节点数量
			// cur节点数=左数节点数+右树节点数 + 1
			cur->size = (cur->left ? cur->left->size : 0) + (cur->right ? cur->right->size : 0) + 1;
			return leftNode;
		}

		SBTNode* LeftRotate(SBTNode* cur) {
			// 处理类似上述右旋
			SBTNode* rightNode = cur->right;
			cur->right = rightNode->left;
			rightNode->left = cur;
			rightNode->size = cur->size;
			cur->size = (cur->left ? cur->left->size : 0) + (cur->right ? cur->right->size : 0) + 1;
			return rightNode;
		}
		SBTNode* Maintain(SBTNode* cur) {
			if (!cur)
				return nullptr;
			int LSize = cur->left ? cur->left->size : 0;
			int LLSize = cur->left && cur->left->left ? cur->left->left->size : 0;
			int LRSize = cur->left && cur->left->right ? cur->left->right->size : 0;
			int RSize = cur->right ? cur->right->size : 0;
			int RRSize = cur->right && cur->right->right ? cur->right->right->size : 0;
			int RLSize = cur->right && cur->right->left ? cur->right->left->size : 0;
			if (LLSize > RSize) {	// LL型违规，左左侄的节点数大于右叔
				cur = RightRotate(cur);	// 右旋
				cur->right = Maintain(cur->right);	// 右旋完后，新树cur的右孩子结构发生了改变，调整
				cur = Maintain(cur);	// cur本身是新根，结构也发生了改变，调整
			} else if (LRSize > RSize) {	
				// LR型违规，左右侄的节点数大于右叔，若LL和LR同时出现，LL以先判断，走到这里就不会出现这种情况了
				cur->left = LeftRotate(cur->left);	
				cur = RightRotate(cur);
				// 三个节点结构均发生改变，调整
				cur->left = Maintain(cur->left);
				cur->right = Maintain(cur->right);
				cur = Maintain(cur);
			} else if (RRSize > LSize) {	// RR型
				cur = LeftRotate(cur);
				cur->left = Maintain(cur->left);
				cur = Maintain(cur);
			} else if(RLSize>LSize){		// RL型
				cur->right = RightRotate(cur->right);
				cur = LeftRotate(cur);
				cur->left = Maintain(cur->left);
				cur->right = Maintain(cur->right);
				cur = Maintain(cur);
			}
			return cur;
		}
		// 查找key，找不到，返回最接近于key的
		SBTNode* FindLastIndex(K key) {
			SBTNode* pre = root, * cur = root;
			while (cur) {
				pre = cur;
				if (key == cur->key)
					break;
				else if (key < cur->key)
					cur = cur->left;
				else
					cur = cur->right;
			}
			return pre;
		}
		// 查找不小于key的 即>=
		SBTNode* FindLastNoSmallIndex(K key) {
			SBTNode* ans = nullptr, * cur = root;
			while (cur) {
				if (key == cur->key) {
					ans = cur;
					break;
				} else if (key < cur->key) {
					ans = cur;
					cur = cur->left;
				} else {
					cur = cur->right;
				}
			}
			return ans;
		}
		
		SBTNode* FindLastNoBigIndex(K key) {
			SBTNode* ans = nullptr, * cur = root;
			while (cur) {
				if (key == cur->key) {
					ans = cur;
					break;
				} else if (key < cur->key) {
					cur = cur->left;
				} else {
					ans = cur;
					cur = cur->right;
				}
			}
			return ans;
		}

		// 现在，以cur为头的树上，新增，加(key, value)这样的记录
		// 加完之后，会对cur做检查，该调整调整
		// 返回，调整完之后，整棵树的新头部
		SBTNode* Add(SBTNode* cur, K key, V val) {
			if (!cur)
				return new SBTNode(key, val);
			else {
				++cur->size;	//沿途节点数量++
				if (key < cur->key) {
					cur->left = Add(cur->left, key, val);
				} else {
					cur->right = Add(cur->right, key, val);
				}
				return Maintain(cur);	// 沿途往上调整
			}
		}

		// 在cur这棵树上，删掉key所代表的节点
		// 返回cur这棵树的新头部
		SBTNode* Delete(SBTNode* cur, K key) {
			--cur->size;	//沿途节点数量--
			if (key == cur->key) {
				// 当前要删除cur
				if (!cur->left && !cur->right) {	// 左空右空
					delete cur;
					cur = nullptr;
				} else if (!cur->left && cur->right) { // 左空
					delete cur;
					cur = cur->right;
				} else if (!cur->right && cur->left) {	// 右空
					delete cur;
					cur = cur->left;
				} else {	// 有左有右
					// 找右子树最左节点进行替换删除
					SBTNode* pre = nullptr, * des = cur->right;
					// 沿途节点数--
					--des->size;
					while (des->left) {
						pre = des;
						des = des->left;
						--des->size;
					}
					if (pre) {
						pre->left = des->right;	//pre左指针接收最左孩子的右孩子
						des->right = cur->right;	// 替换cur的地位
					}
					des->left = cur->left;		// 替换cur的地位
					des->size = des->left->size + (des->right ? des->right->size : 0) + 1;
					delete cur;
					cur = des;
				}
			} else if (key < cur->key) {
				cur->left = Delete(cur->left, key);
			} else {
				cur->right = Delete(cur->right, key);
			}
			return cur;
		}
		// 查找第k个元素
		SBTNode* GetIndex(SBTNode* cur, int kth) {
			if (kth == (cur->left ? cur->left->size : 0) + 1)	// 在当前根
				return cur;
			else if (kth <= (cur->left ? cur->left->size : 0))	// 在左子树
				return GetIndex(cur->left, kth);
			else												// 在右子树
				return GetIndex(cur->right, kth - (cur->left ? cur->left->size : 0) - 1);
		}
		int Size() {
			return root ? root->size : 0;
		}
		bool ContainsKey(K key) {
			SBTNode* lastNode = FindLastIndex(key);
			return lastNode && lastNode->key == key;
		}
		void Put(K key, V val) {
			SBTNode* lastNode = FindLastIndex(key);
			if (lastNode && key == lastNode->key) {
				lastNode->value = val;
			} else {
				root = Add(root, key, val);
			}
		}
		void Remove(K key) {
			if (ContainsKey(key))
				root = Delete(root, key);
		}

		K GetIndexKey(int index) {
			if (index < 0 || index >= Size()) {
				throw invalid_argument("invalid parameter.");
			}
			return GetIndex(root, index + 1)->key;
		}
		V GetIndexValue(int index) {
			if (index < 0 || index >= Size()) {
				throw invalid_argument("invalid parameter.");
			}
			return GetIndex(root, index + 1)->value;
		}
		// 若树空返回true
		bool Empty() {
			return !root;
		}
		V Get(K key) {
			SBTNode* lastNode = FindLastIndex(key);
			if (lastNode && key == lastNode->key)
				return lastNode->value;
			else
				throw invalid_argument("key does not exist.");
		}
		
		K FirstKey() {
			if (Empty())
				throw runtime_error("SBTree is empty.");
			SBTNode* cur = root;
			while (cur->left) {
				cur = cur->left;
			}
			return cur->key;
		}
		
		K LastKey() {
			if (Empty()) {
				throw runtime_error("SBTree is empty.");
			}
			SBTNode* cur = root;
			while (cur->right) {
				cur = cur->right;
			}
			return cur->key;
		}
	};

	// for test=======================
	// 以下均为测试代码
	void PrintAll(SBTNode<string, int>* head) {
		cout << ("Binary Tree:") << endl;
		PrintInOrder(head, 0, "H", 17);
		cout << endl;
	}

	// for test
	void PrintInOrder(SBTNode<string, int>* head, int height, string to, int len) {
		if (!head) {
			return;
		}
		PrintInOrder(head->right, height + 1, "v", len);
		string val = to + "(" + head->key + "," + to_string(head->value) + ")" + to;
		int lenM = val.length();
		int lenL = (len - lenM) / 2;
		int lenR = len - lenM - lenL;
		val = getSpace(lenL) + val + getSpace(lenR);
		cout << (getSpace(height * len) + val) << endl;
		PrintInOrder(head->left, height + 1, "^", len);
	}

	// for test
	string getSpace(int num) {
		string space = " ";
		string ans;
		for (int i = 0; i < num; i++) {
			ans.append(space);
		}
		return ans;
	}

	void Test() {
		SizeBalancedTreeMap<string, int> sbt;
		sbt.Put("d", 4);
		sbt.Put("c", 3);
		sbt.Put("a", 1);
		sbt.Put("b", 2);
		// sbt.put("e", 5);
		sbt.Put("g", 7);
		sbt.Put("f", 6);
		sbt.Put("h", 8);
		sbt.Put("i", 9);
		sbt.Put("a", 111);
		cout<<(sbt.Get("a"));
		sbt.Put("a", 1);
		cout<<(sbt.Get("a"));
		for (int i = 0; i < sbt.Size(); i++) {
			cout << sbt.GetIndexKey(i) << " , " << sbt.GetIndexValue(i) << endl;
		}
		PrintAll(sbt.root);
		cout << (sbt.FirstKey()) << endl;
		cout << (sbt.LastKey()) << endl;
		cout << (sbt.FindLastNoBigIndex("g")->key) << endl;
		cout << (sbt.FindLastNoSmallIndex("g")->key) << endl;
		cout << (sbt.FindLastNoBigIndex("e")->key) << endl;
		cout << (sbt.FindLastNoSmallIndex("e")->key) << endl;
		cout << (sbt.FindLastNoBigIndex("")->key) << endl;
		cout << (sbt.FindLastNoSmallIndex("")->key) << endl;
		cout << (sbt.FindLastNoBigIndex("j")->key) << endl;
		cout << (sbt.FindLastNoSmallIndex("j")? sbt.FindLastNoSmallIndex("j")->key:"null") << endl;
		sbt.Remove("d");
		PrintAll(sbt.root);
		sbt.Remove("f");
		PrintAll(sbt.root);
	}
};
void testSBTree() {
	Code01_SizeBalancedTreeMap code01;
	code01.Test();
}
