private void leftRotate(Node x) {  // x.right is not null
  Node y = x.right;
  x.right = y.left;
  if (y.left != null)
    y.left.parent = x;
  y.parent = x.parent;
  if (x.parent == null)
    root = y;
  else {
    if (x==x.parent.left)
      x.parent.left = y;
    else
      x.parent.right = y;
  }
  y.left = x;
  x.parent = y;
}

public void delete(Node z){
  Node y,x;
  if(z.left==null || z.right == null)
    y=z;
  else
    y=successor(z);

  if(y.left != null)
    x=y.left;
  else
    x=y.right;

  if(x!=null)
    x.parent = y.parent;

  boolean isLeftChild;
  if(y.parent == null) {
    root = x;
    x.color = BLACK;
    return;
  }
  else if(y==y.parent.left) {
    y.parent.left = x;
    isLeftChild = true;
  }
  else {
    y.parent.right = x;
    isLeftChild = false;
  }

  if(y!=z){
    z.key = y.key;
    z.value = y.value;
  }

  if (y.color==BLACK)
    deleteFixUp(x, y.parent, isLeftChild);
    // x is possibly null, not root
    // y.parent is the parent of x
}

private void deleteFixUp(Node x, Node px, boolean isXLeftChild) {
  while (x!=root && (x==null || x.color==BLACK)) {
    if (isXLeftChild) {  // case 1,2,3,4
      Node w = px.right;  // w is not null since x is double black
      if (w.color==RED) {  // case 1
        w.color = BLACK;
        px.color = RED;
        leftRotate(px);
        w = px.right;
      }
      if ((w.left==null || w.left.color==BLACK) && (w.right==null || w.right.color==BLACK)) {
        w.color = RED;
        x = px;
      }
      else {
        if (w.right == null || w.right.color==BLACK) {
          w.left.color = BLACK;
          w.color = RED;
          rightRotate(w);
          w = px.right;
        }
        w.color = px.color;
        px.color = BLACK;
        w.right.color = BLACK;
        leftRotate(px);
        x = root;
      }
    }
    else {
      Node w = px.left;
      if (w.color==RED) {
        w.color = BLACK;
        px.color = RED;
        rightRotate(px);
        w = px.left;
      }
      if ((w.left==null || w.right.color==BLACK) && (w.right==null || w.left.color==BLACK)) {
        w.color = RED;
        x = px;
      }
      else {
        if (w.left==null || w.left.color==BLACK) {
          w.right.color = BLACK;
          w.color = RED;
          leftRotate(w);
          w = px.left;
        }
        w.color = px.color;
        px.color = BLACK;
        w.left.color = BLACK;
        rightRotate(px);
        x = root;
      }
    }
    if (x!=root) {
      px = x.parent;
      isXLeftChild = (x == px.left);
    }
  }
  x.color = BLACK;
}

/* Test if a binary search tree is a RBT. */
/* root is the root of the tree */
private boolean isRedBlackTree() {
		if (root==null)
			return true;
		if (root.color==RED)
			return false;
		return isRedBlackTree(root)!=-1;
}

private int isRedBlackTree(Node x) {
		if (x==null)
			return 1;
		if (x.color==RED && (x.left!=null && x.left.color==RED || x.right!=null && x.right.color==RED))
			return -1;
		int result1 = isRedBlackTree(x.left);
		if (result1==-1)
			return -1;
		int result2 = isRedBlackTree(x.right);
		if (result2==-1 || result1 != result2)
			return -1;
		return result1+(x.color==BLACK?1:0);
}
