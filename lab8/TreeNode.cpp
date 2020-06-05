#include <iostream>

using namespace std;

class TreeNode {
	int value;
	TreeNode *left;
	TreeNode *right;
public:
	TreeNode(int value = 0);

	int GetValue() const;
	TreeNode* GetLeft() const;
	TreeNode* GetRight() const;

	void SetValue(int value);
	void SetLeft(TreeNode* left);
	void SetRight(TreeNode* right);
};

class BinaryTree {
	TreeNode *root;

	void FreeMemory(TreeNode* node);
	TreeNode* Insert(TreeNode *node, int value);
	TreeNode* Search(TreeNode *node, int value);
	void Print(TreeNode *node, int level) const;
public:
	BinaryTree();

	void Insert(int value);
	TreeNode* Search(int value);

	void Print() const;
	~BinaryTree();
};

TreeNode::TreeNode(int value) {
	this->value = value;
	left = nullptr;
	right = nullptr;
}

int TreeNode::GetValue() const {
	return value;
}

TreeNode* TreeNode::GetLeft() const {
	return left;
}

TreeNode* TreeNode::GetRight() const {
	return right;
}

void TreeNode::SetValue(int value) {
	this->value = value;
}

void TreeNode::SetLeft(TreeNode* left) {
	this->left = left;
}

void TreeNode::SetRight(TreeNode* right) {
	this->right = right;
}


BinaryTree::BinaryTree() {
	root = nullptr;
}

void BinaryTree::FreeMemory(TreeNode* node) {
	if (node == nullptr)
		return;

	FreeMemory(node->GetLeft());
	FreeMemory(node->GetRight());
	delete node;
}

TreeNode* BinaryTree::Insert(TreeNode *node, int value) {
	if (node == nullptr)
		return new TreeNode(value);

	if (value < node->GetValue()) {
		node->SetLeft(Insert(node->GetLeft(), value));
	}
	else {
		node->SetRight(Insert(node->GetRight(), value));
	}

	return node;
}

void BinaryTree::Insert(int value) {
	root = Insert(root, value);
}

TreeNode* BinaryTree::Search(TreeNode *node, int value) {
	if (node == nullptr)
		return node;

	if (node->GetValue() > value)
		return Search(node->GetLeft(), value);

	if (node->GetValue() < value)
		return Search(node->GetRight(), value);

	return node;
}

TreeNode* BinaryTree::Search(int value) {
	return Search(root, value);
}

void BinaryTree::Print(TreeNode *node, int level) const {
	if (node == nullptr)
		return;

	Print(node->GetRight(), level + 1);
	for (int i = 0; i < level; i++)
		cout << "    ";
	cout << node->GetValue() << endl;
	Print(node->GetLeft(), level + 1);
}

void BinaryTree::Print() const {
	Print(root, 0);
}

BinaryTree::~BinaryTree() {
	FreeMemory(root);
}

void CreateMinimalBSTRecursive(BinaryTree &tree, int *array, int start, int end) {
	if (end < start)
		return;

	int mid = (start + end) / 2;
	tree.Insert(array[mid]);

	CreateMinimalBSTRecursive(tree, array, start, mid - 1);
	CreateMinimalBSTRecursive(tree, array, mid + 1, end);
}

BinaryTree CreateMinimalBST(int *array, int start, int end) {
	BinaryTree tree;
	CreateMinimalBSTRecursive(tree, array, start, end);
	return tree;
}

int main() {
	int n;
	cout << "Enter n: ";
	cin >> n;

	int *array = new int[n];

	cout << "Array: ";
	for (int i = 0; i < n; i++) {
		array[i] = i;
		cout << array[i] << " ";
	}

	cout << endl;

	BinaryTree tree = CreateMinimalBST(array, 0, n - 1);

	cout << "Created tree from array:" << endl;
	tree.Print();
}
