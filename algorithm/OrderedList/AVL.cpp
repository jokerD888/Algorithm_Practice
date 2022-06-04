// AVL 平衡二叉搜索树---------------------------------------------------------------------------------
// AVL 是一个二叉搜索树，在此基础上增加了平衡机制，即左右子树高度差不超过1，若出现违规情况（LL,RL,LR,RR),通过“旋转”进行平衡调整。
class Code01_AVLTreeMap {
public:
	// 对于K这种类型，需要是可比较的类型
	template<typename K, typename V>
	class AVLNode {
	public:
		K k;	 //key
		V v;	 //value
		AVLNode* left;
		AVLNode* right;
		int h;	 //high
		// init
		AVLNode(K key, V value) :k(key), v(value), h(1) {}
	};
	template<typename K, typename V>
	class AVLTreeMap {
	private:
		using AVLNode = AVLNode<K, V>;	// 模板别名
		AVLNode* root;
		int size;
	public:
		// init
		AVLTreeMap() :root(nullptr), size(0) {}
		~AVLTreeMap() {
			if (root)
				Destroy(root);
		}
	private:
		void Destroy(AVLNode* cur) {
			if (!cur->left && !cur->right) {
				delete cur;
				return;
			}
			if(cur->left)
				Destroy(cur->left);
			if(cur->right)
				Destroy(cur->right);
			delete cur;
		}

		// rightRotate
		AVLNode* rightRotate(AVLNode* cur) {
			AVLNode* leftNode = cur->left;
			cur->left = leftNode->right;
			leftNode->right = cur;
			cur->h = max(cur->left ? cur->left->h : 0, cur->right ? cur->right->h : 0) + 1;
			leftNode->h = max(leftNode->left ? leftNode->left->h : 0, leftNode->right ? leftNode->right->h : 0) + 1;
			return leftNode;	// 返回新根
		}
		// leftRotate
		AVLNode* leftRotate(AVLNode* cur) {
			AVLNode* rightNode = cur->right;
			cur->right = rightNode->left;
			rightNode->left = cur;
			cur->h = max(cur->left ? cur->left->h : 0, cur->right ? cur->right->h : 0) + 1;
			rightNode->h = max(rightNode->left ? rightNode->left->h : 0, rightNode->right ? rightNode->right->h : 0) + 1;
			return rightNode;	// 返回新根
		}
		// maintain(保持平衡）
		AVLNode* maintain(AVLNode* cur) {
			if (!cur)
				return cur;
			int leftH = cur->left ? cur->left->h : 0;
			int rightH = cur->right ? cur->right->h : 0;
			if (abs(leftH - rightH) > 1) {
				// 对应于LL型和LR型违规
				if (leftH > rightH) {
					// LLH :leftLeftHigh 左孩子的左孩子的高度  LRH同理
					int LLH = cur->left && cur->left->left ? cur->left->left->h : 0;
					int LRH = cur->left && cur->left->right ? cur->left->right->h : 0;
					if (LLH >= LRH) {	// 既LL型又有LR型，按LL型违规处理
						cur = rightRotate(cur);		// 右旋处理
					} else {
						cur->left = leftRotate(cur->left);	//对左孩子左旋处理
						cur = rightRotate(cur);				//再对整体右旋
					}
				} else {	//RR型和RL型违规
					int RRH = cur->right && cur->right->right ? cur->right->right->h : 0;
					int RLH = cur->right && cur->right->left ? cur->right->left->h : 0;
					if (RRH >= RLH) {	// RR型 && RL型  按RR型左旋处理
						cur = leftRotate(cur);
					} else {
						cur->right = rightRotate(cur->right);
						cur = leftRotate(cur);
					}
				}
			}
			return cur;
		}
	public:
		// 查找key
		AVLNode* findLastIndex(K key) {
			AVLNode* cur = root;
			while (cur) {
				if (key == cur->k) {
					return cur;
				} else if (key < cur->k) {
					cur = cur->left;
				} else {
					cur = cur->right;
				}
			}
			return nullptr;
		}
		// 找到大于等于key的
		AVLNode* findLastNoSmallIndex(K key) {
			AVLNode* ans = nullptr, * cur = root;
			while (cur) {
				if (key == cur->k) {
					ans = cur;
					break;
				} else if (key < cur->k) {
					ans = cur;
					cur = cur->left;
				} else {
					cur = cur->right;
				}
			}
			return ans;
		}
		// 查找小于等于key的
		AVLNode* findLastNoBigIndex(K key) {
			AVLNode* ans = nullptr, * cur = root;
			while (cur) {
				if (cur->k == key) {
					ans = cur;
					break;
				} else if (key < cur->k) {
					cur = cur->left;
				} else {
					ans = cur;
					cur = cur->right;
				}

			}
			return ans;
		}
		// add,添加节点
		AVLNode* add(AVLNode* cur, K key, V value) {
			if (!cur) {
				return  new AVLNode(key, value);
			} else {
				if (key < cur->k) {
					cur->left = add(cur->left, key, value);
				} else {
					cur->right = add(cur->right, key, value);
				}
				cur->h = max(cur->left ? cur->left->h : 0, cur->right ? cur->right->h : 0) + 1;
				return maintain(cur);	// 从加入的节点开始一路向上维持平衡
			}
		}
		// 在cur这颗树上，删除key所代表的节点，并返回cur这颗树的新头
		AVLNode* deleteNode(AVLNode* cur, K key) {
			if (key < cur.k) {
				cur->left = deleteNode(cur->left, key);
			} else if (key > cur.k) {
				cur->right = deleteNode(cur->right, key);
			} else {
				if (!cur->left && !cur->right) {	// 无左无右
					delete cur;
					cur = nullptr;
				} else if (!cur->left && cur->right) {	// 无左有右
					AVLNode* rightNode = cur->right;
					delete cur;
					cur = rightNode;
				} else if (cur->left && !cur->right) {	// 无右有左
					AVLNode* leftNode = cur->left;
					delete cur;
					cur = leftNode;
				} else {		// 有左有右，右子树上找最左的节点删除，在把返回值作为cur的右孩子
					AVLNode* des = cur->right;
					while (des->left) {		// 找最左叶
						des = des->left;
					}
					cur->right = deleteNode(cur->right, des->k);	// 从左最被替换删除的位置一路到被实际删除的位置做平衡调整
					des->left = cur->left;	// 和最左节点交换信息，并不直接更改key
					des->right = cur->right;
					cur = des;
				}
			}
			if (cur) {
				cur->h = max(cur->left ? cur->left->h : 0, cur->right ? cur->right->h : 0) + 1;
			}
			return maintain(cur);	// 从删除的位置一路向上维持平衡
		}
		int getSize() {
			return size;
		}
		bool containsKey(K key) {
			AVLNode* lastNode = findLastNoBigIndex(key);
			return lastNode && key == lastNode->k;
		}
		// 放入数据，若已存在，更改值，否则add
		void put(K key, V value) {
			AVLNode* lastNode = findLastIndex(key);
			if (lastNode && key == lastNode->k) {
				lastNode->v = value;
			} else {
				++size;
				root = add(root, key, value);
			}
		}
		// remove进行数据有效性的判断，再调用deleteNode进行删除
		bool remove(K key) {
			if (!root)
				return false;
			if (containsKey(key)) {
				--size;
				root = deleteNode(root, key);
				return true;
			}
			return false;
		}
		V get(K key) {
			AVLNode* lastNode = findLastIndex(key);
			if (lastNode && key == lastNode->k) {
				return lastNode->v;
			}
			return V();
		}
		K firstKey() {
			AVLNode* cur = root;
			while (cur->left) {
				cur = cur->left;
			}
			return cur->k;
		}
		K lastKey() {
			AVLNode* cur = root;
			while (cur->right) {
				cur = cur->right;
			}
			return cur->k;
		}
		K floorKey(K key) {
			AVLNode* lastNoBigNode = findLastNoBigIndex(key);
			return lastNoBigNode ? lastNoBigNode->k : K();
		}
		K ceilingKey(K key) {
			AVLNode* lastNoSmallNode = findLastNoSmallIndex(key);
			return lastNoSmallNode ? lastNoSmallNode->k : K();
		}

	};
};

void testAVL() {
	Code01_AVLTreeMap::AVLTreeMap<int, int> m;
	m.put(1, 2);
	m.put(1, 3);
	m.put(4, 4);
	cout << m.get(1) << " " << m.get(4) << endl;
}