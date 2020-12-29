from container import *


class _TNode:

    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None
        self.height = 1


class AVLTree:

    def __init__(self, id_):
        self._id = id_
        self._root = None

    def get_id(self):
        return self._id

    def get_string_id(self):
        return "AVL-Tree #" + str(self._id)

    def _get_height(self, root):
        if root is None:
            return 0
        return root.height

    def _get_balance(self, root):
        if root is None:
            return 0
        return self._get_height(root.left) - self._get_height(root.right)

    def _left_rotate(self, z):
        y = z.right
        temp = y.left

        y.left = z
        z.right = temp

        z.height = 1 + max(self._get_height(z.left),
                           self._get_height(z.right))
        y.height = 1 + max(self._get_height(y.left),
                           self._get_height(y.right))

        return y

    def _right_rotate(self, z):
        y = z.left
        temp = y.right

        y.right = z
        z.left = temp

        z.height = 1 + max(self._get_height(z.left),
                           self._get_height(z.right))
        y.height = 1 + max(self._get_height(y.left),
                           self._get_height(y.right))

        return y

    def _rec_add(self, root, value):
        if root is None:
            return _TNode(value)
        elif compare(root.val, value) == 1:
            root.left = self._rec_add(root.left, value)
        else:
            root.right = self._rec_add(root.right, value)

        root.height = 1 + max(self._get_height(root.left),
                              self._get_height(root.right))

        balance = self._get_balance(root)

        if balance > 1 and compare(value, root.left.val) == -1:
            return self._right_rotate(root)

        if balance < -1 and compare(value, root.right.val) == 1:
            return self._left_rotate(root)

        if balance > 1 and compare(value, root.left.val) == 1:
            root.left = self._left_rotate(root.left)
            return self._right_rotate(root)

        if balance < -1 and compare(value, root.right.val) == -1:
            root.right = self._right_rotate(root.right)
            return self._left_rotate(root)

        return root

    def add(self, value):
        if self._root is None:
            value = reset_value(value)
            self._root = self._rec_add(self._root, value)
            return True
        else:
            if check_types(self._root.val, value):
                value = reset_value(value)
                self._root = self._rec_add(self._root, value)
                return True
            else:
                return False

    def _get_min_value_node(self, root):
        if root is None or root.left is None:
            return root

        return self._get_min_value_node(root.left)

    def _rec_del(self, root, value):
        if root is None:
            return root
        elif compare(value, root.val) == -1:
            root.left = self._rec_del(root.left, value)
        elif compare(value, root.val) == 1:
            root.right = self._rec_del(root.right, value)
        else:
            if root.left is None:
                temp = root.right
                root = None
                return temp
            elif root.right is None:
                temp = root.left
                root = None
                return temp

            temp = self._get_min_value_node(root.right)
            root.val = temp.val
            root.right = self._rec_del(root.right, temp.val)

        if root is None:
            return root

        root.height = 1 + max(self._get_height(root.left),
                              self._get_height(root.right))

        balance = self._get_balance(root)

        if balance > 1 and self._get_balance(root.left) >= 0:
            return self._right_rotate(root)

        if balance < -1 and self._get_balance(root.right) <= 0:
            return self._left_rotate(root)

        if balance > 1 and self._get_balance(root.left) < 0:
            root.left = self._left_rotate(root.left)
            return self._right_rotate(root)

        if balance < -1 and self._get_balance(root.right) > 0:
            root.right = self._right_rotate(root.right)
            return self._left_rotate(root)

        return root

    def _rec_get(self, root, value):
        if root is None:
            return False
        if compare(root.val, value) == 1:
            return self._rec_get(root.left, value)
        if compare(root.val, value) == 0:
            return True

        return self._rec_get(root.right, value)

    def get(self, value):
        if self._root is None:
            return False
        else:
            if check_types(self._root.val, value):
                value = reset_value(value)
                return self._rec_get(self._root, value)
            else:
                return False

    def del_(self, value):
        if self._root is None:
            return False
        else:
            if check_types(self._root.val, value):
                value = reset_value(value)
                self._root = self._rec_del(self._root, value)
                return True
            else:
                return False

    def _rec_output(self, root):
        ans = ''
        if root is None:
            return ''
        if root.left is not None:
            ans += self._rec_output(root.left)

        if len(ans) > 0:
            ans += ', '
        if isinstance(root.val, (Book, Container)):
            ans += root.val.output()
        else:
            ans += str(root.val)

        if root.right is not None:
            if len(ans) > 0:
                ans += ', '
            ans += self._rec_output(root.right)

        return ans

    def change(self, value_from, value_to):
        if self._root is None:
            return False

        if not check_types(self._root.val, value_from):
            return False

        if not check_types(self._root.val, value_to):
            return False

        value_to = reset_value(value_to)
        value_from = reset_value(value_from)

        if not self.del_(value_from):
            return False

        self.add(value_to)
        return True

    def empty(self):
        if self._root is None:
            return True
        else:
            return False

    def output(self, type_='AVL Tree'):
        if self._root is None:
            return str(type_) + " #" + str(self._id) + ":(empty)"

        return str(type_) + " #" + str(self._id) + ": [" + self._rec_output(self._root) + " ]"

    def top(self):
        if self._root is None:
            return None
        else:
            return self._root.val
