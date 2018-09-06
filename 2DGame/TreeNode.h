#ifndef TREENODE_H
#define TREENODE_H

namespace aie {
	class Renderer2D;
}

class TreeNode
{
public:
	TreeNode( int value);//TreeNode* parent
	~TreeNode() = default;
	bool hasLeft() { return (m_left != nullptr); }
	bool hasRight() { return (m_right != nullptr); }
	int getData() { return m_value; }
	TreeNode* getLeft() { if (m_left != nullptr) return m_left; }
	TreeNode* getRight() { if (m_left != nullptr) return m_right; }
	void setData(int value) { m_value = value; }
	void setLeft(TreeNode* node) { m_left = node; }
	void setRight(TreeNode* node) { m_right = node; }
	void draw(aie::Renderer2D*, int x, int y, bool selected = false);

	void setParent(TreeNode* node) { m_parent = node; }
	TreeNode* getParent() const { return m_parent; }
	// node's children
	TreeNode* m_left;
	TreeNode* m_right;
	// this could also be a pointer to another object if you like
	int m_value{ 0 };
private:
	
	//
	TreeNode* m_parent;
	
};
#endif // TREENODE_H
