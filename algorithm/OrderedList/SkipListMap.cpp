// 跳表 ------------------------------------------------------------------------------------------------
// 跳表是一个随机化的数据结构，实质就是一种可以进行二分查找的有序链表。
// 跳表在原有的有序链表上面增加了多级索引，通过索引来实现快速查找。跳表不仅能提高搜索性能，同时也可以提高插入和删除操作的性能。
// 它采用随机技术决定链表中哪些节点应增加向前指针以及在该节点中应增加多少个指针。跳表结构的头节点需有足够的指针域，以满足可能构造最大级数的需要，而尾节点不需要指针域。
// 表中有几个数就有几个节点，各节点不同的是其内的nextNodes,nextNodes的多少代表其节点的高度
// 因每次高度的决定都是0.5, 0.5的概率高度+1，0.5的概率终止高度的增长，大趋势来说，相邻两层中下一层连接的节点数是上一层连接的节点数的2倍
// 每次从上往下划，在某一上层的一次前移，都可能会划过下层许多的节点，查找，插入和删除的时间复杂度都是O(logN)
class Code02_SkipListMap {
public:
	template<typename K, typename V>
	class SkipListNode {
	public:
		K key;
		V val;
		vector<SkipListNode*> nextNodes;
		SkipListNode(K k=K(), V v=V()) :key(k), val(v) {}

		// node里面的key是否比otherKey小，true，不是false
		bool IsKeyLess(K otherKey) {
			return key < otherKey;
		}
		bool IskeyEqual(K otherKey) {
			return key == otherKey;
		}
	};

	template<typename K, typename V>
	class SkipListMap {
	public:
		using SkipListNode = SkipListNode<K, V>;	//模板别名

		default_random_engine e;
		bernoulli_distribution b;	// 此种随机数分布，0.5概率返回true

		SkipListNode* head;
		int size;		// 节点总数
		int maxLevel;	// 跳表高度

		SkipListMap() :head(new SkipListNode()), size(0), maxLevel(0)
		{
			head->nextNodes.push_back(nullptr);
		}

		// 查找最近的小于key的
		// 从最高层开始，一路找下去，
		// 最终，找到第0层的<key的最右的节点
		SkipListNode* MostRightLessNodeInTree(K key) {
			int level = maxLevel;
			SkipListNode* cur = head;
			while (level >= 0) {
				cur = MostRightLessNodeInLevel(key, cur, level--);
			}
			return cur;
		}
		// 在level层里，如何往右移动
		// 现在来到的节点是cur，来到了cur的level层，在level层上，找到<key最后一个节点并返回
		SkipListNode* MostRightLessNodeInLevel(K key, SkipListNode* cur, int level) {
			SkipListNode* next = cur->nextNodes[level];
			while (next && next->IsKeyLess(key)) {
				cur = next;
				next = cur->nextNodes[level];
			}
			return cur;
		}

		bool ContainsKey(K key) {
			SkipListNode* less = MostRightLessNodeInTree(key);
			SkipListNode* next = less->nextNodes[0];
			return next && next->IskeyEqual(key);
		}

		// 增改value	
		void Put(K key, V value) {
			SkipListNode* less = MostRightLessNodeInTree(key);
			SkipListNode* find = less->nextNodes[0];
			if (find && find->IskeyEqual(key))	// 找到了 ，改
				find->val = value;
			else {	// 增
				++size;
				int newNodeLevel = 0;
				// 随机决定当前节点的高度
				while (b(e)) {
					++newNodeLevel;
				}
				// 当前跳表高度小于当前节点高度，跳表增高
				while (newNodeLevel > maxLevel) {
					head->nextNodes.push_back(nullptr);
					++maxLevel;
				}

				SkipListNode* newNode=new SkipListNode(key, value);
				for (int i = 0; i <= newNodeLevel; ++i) {
					newNode->nextNodes.push_back(nullptr);
				}
				// 从上往下，对newNode做插入
				int level = maxLevel;
				SkipListNode* pre = head;
				while (level >= 0) {
					// level 层中，找到最右的 < key 的节点
					pre = MostRightLessNodeInLevel(key, pre, level);
					if (level <= newNodeLevel) {
						newNode->nextNodes[level] = pre->nextNodes[level];
						pre->nextNodes[level] = newNode;
					}
					--level;
				}
			}
		}
		// 使用Get前请先使用ContainKey查询key是否存在，否则返回值未定义
		V Get(K key) {
			SkipListNode* less = MostRightLessNodeInTree(key);
			SkipListNode* next = less->nextNodes[0];
			return next && next->key == key ? next->val : V();	// 这里为了防止非法访问报错终止程序，返回了V的默认值，也就要求了类型V需要有默认构造
		}

		void Remove(K key) {
			if (ContainsKey(key)) {
				--size;
				int level = maxLevel;
				SkipListNode* pre = head;
				while (level >= 0) {
					pre = MostRightLessNodeInLevel(key, pre, level);
					SkipListNode* next = pre->nextNodes[level];
					// 1）在这一层中，pre下一个就是key
					// 2）在这一层中，pre的下一个key是>要删除key
					if (next && next->IskeyEqual(key)) {
						pre->nextNodes[level]=next->nextNodes[level];
					}
					// 当来到第0层，上层已重连完毕，该释放节点了
					if (level == 0) {
						delete next;
					}
					// 在level层只有一个节点了，就是默认节点head,将该层删除，（不删也行，不影响）
					if (level != 0 && pre == head && pre->nextNodes[level] == nullptr) {
						head->nextNodes.erase(head->nextNodes.begin()+level);
						--maxLevel;
					}
					--level;
				}
			}
		}
		int Size() { return size; }
		bool Empty() { return size != 0; }
		// 使用前先确保表不为空
		K FirstKey() {
			return head->nextNodes[0]->key;
		}
		K LastKey() {
			int level = maxLevel;
			SkipListNode* cur = head;
			while (level >= 0) {
				SkipListNode* next = cur->nextNodes[level];
				while (next) {
					cur = next;
					next = cur->nextNodes[level];
				}
				--level;
			}
			return cur->key;
		}

		// 返回大于等于key的节点
		SkipListNode* CeilingNode(K key) {
			SkipListNode* less = MostRightLessNodeInTree(key);
			SkipListNode* next = less->nextNodes[0];
			return next;
		}
		// 返回小于等于key的节点
		SkipListNode* FloorNode(K key) {
			SkipListNode* less = MostRightLessNodeInTree(key);
			if (less == head) {	// 说明没有小于等于key的
				return nullptr;
			}
			SkipListNode* next = less->nextNodes[0];
			return next && next->IskeyEqual(key) ? next : less;
		}
	};
	// for test=========================================
	void PrintAll(SkipListMap<string, string> obj) {
		for (int i = obj.maxLevel; i >= 0; i--) {
			cout << "Level " << i << " : " << endl;
			SkipListNode<string, string>* cur = obj.head;
			while (cur->nextNodes[i]) {
				SkipListNode<string, string>* next = cur->nextNodes[i];
				cout << "(" << next->key << " , " << next->val << ") " << endl;
				cur = next;
			}
			cout << endl;
		}
	}
	void Test() {
		SkipListMap<string, string> test;
		PrintAll(test);
		cout << ("======================") << endl;
		test.Put("A", "10");
		PrintAll(test);
		cout<<("======================")<<endl;
		test.Remove("A");
		PrintAll(test);
		cout<<("======================")<<endl;
		test.Put("E", "E");
		test.Put("B", "B");
		test.Put("A", "A");
		test.Put("F", "F");
		test.Put("C", "C");
		test.Put("D", "D");
		PrintAll(test);
		cout<<("======================")<<endl;
		cout<<(test.ContainsKey("B"))<<endl;
		cout<<(test.ContainsKey("Z"))<<endl;
		cout<<(test.FirstKey())<<endl;
		cout << (test.LastKey()) << endl;;
		cout<<(test.FloorNode("D")?test.FloorNode("D")->key:"null")<<endl;
		cout<<(test.CeilingNode("D") ? test.CeilingNode("D")->key : "null");
		cout << ("======================") << endl;
		test.Remove("D");
		PrintAll(test);
		cout<<("======================")<<endl;
		cout << (test.FloorNode("D") ? test.FloorNode("D")->key : "null") << endl;
		cout << (test.CeilingNode("D") ? test.CeilingNode("D")->key : "null");
	}

};
void testSkipList() {
	Code02_SkipListMap code2;
	code2.Test();
}
