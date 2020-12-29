from container import *


class _TNode:

    def __init__(self):
        self.t = 4
        self.keys = [None]*(2*self.t-1)
        self.sons = [None]*(2*self.t)
        self.leaf = True
        self.n = 0

    def output(self):
        ans = '[ '
        for i in range(self.n):
            if i != 0:
                ans += ", "
            if self.leaf is False and self.sons[i] is not None:
                ans += self.sons[i].output() + ", "
            if isinstance(self.keys[i], (Container, Book)):
                ans += self.keys[i].output()
            else:
                ans += str(self.keys[i])

        if self.leaf is False and self.sons[self.n] is not None:
            ans += ", " + self.sons[self.n].output()
        ans += ' ]'

        return ans

    def get(self, value):
        i = 0
        while i < self.n and compare(value, self.keys[i]) == 1:
            i += 1

        if i < self.n and value == self.keys[i]:
            return True

        if self.leaf is True or self.sons[i] is None:
            return False

        return self.sons[i].get(value)

    def insert_non_full(self, value):
        i = self.n - 1

        if self.leaf is True:
            while i >= 0 and compare(self.keys[i], value) == 1:
                self.keys[i+1] = self.keys[i]
                i -= 1

            self.keys[i+1] = value
            self.n += 1

        else:
            while i >= 0 and compare(self.keys[i], value) == 1:
                i -= 1

            if self.sons[i+1] is not None and self.sons[i+1].n == 2*self.t - 1:
                self.split_child(i+1, self.sons[i+1])
                if compare(self.keys[i+1], value) == -1:
                    i += 1

            self.sons[i+1].insert_non_full(value)

    def split_child(self, i, y):
        z = _TNode()
        z.leaf = y.leaf
        z.n = z.t - 1

        for j in range(z.t-1):
            z.keys[j] = y.keys[j + z.t]

        if y.leaf is False:
            for j in range(z.t):
                z.sons[j] = y.sons[j + z.t]

        y.n = y.t - 1

        for j in range(self.n, i, -1):
            self.sons[j + 1] = self.sons[j]

        self.sons[i + 1] = z

        for j in range(self.n-1, i-1, -1):
            self.keys[j + 1] = self.keys[j]

        self.keys[i] = y.keys[y.t - 1]
        self.n += 1

    def _find_key(self, value):
        index = 0
        while index < self.n and compare(self.keys[index], value) == -1:
            index += 1
        return index

    def _remove_from_leaf(self, index):
        for i in range(index + 1, self.n, 1):
            self.keys[i - 1] = self.keys[i]

        self.n -= 1

    def _get_prev(self, index):
        cur = self.sons[index]
        while not cur.leaf:
            cur = cur.sons[cur.n]
        return cur.keys[cur.n - 1]

    def _get_next(self, index):
        cur = self.sons[index + 1]
        while not cur.leaf:
            cur = cur.sons[0]
        return cur.keys[0]

    def _merge(self, index):
        child = self.sons[index]
        sibling = self.sons[index + 1]
        child.keys[self.t-1] = self.keys[index]
        for i in range(sibling.n):
            child.keys[i+self.t] = sibling.keys[i]

        if child.leaf:
            for i in range(sibling.n+1):
                child.sons[i+self.t] = sibling.sons[i]

        for i in range(index+1, self.n, 1):
            self.keys[i-1] = self.keys[i]

        for i in range(index+2, self.n+1, 1):
            self.sons[i-1] = self.sons[i]

        child.n += sibling.n+1
        self.n -= 1

    def _remove_from_non_leaf(self, index):
        key = self.keys[index]
        if self.sons[index].n >= self.t:
            prev = self._get_prev(index)
            self.keys[index] = prev
            self.sons[index].del_(prev)

        else:
            if self.sons[index+1].n >= self.t:
                next_ = self._get_next(index)
                self.keys[index] = next_
                self.sons[index+1].del_(next_)
            else:
                self._merge(index)
                self.sons[index].del_(key)

    def _borrow_from_prev(self, index):
        child = self.sons[index]
        sibling = self.sons[index-1]

        for i in range(child.n - 1, -1, -1):
            child.keys[i+1] = child.keys[i]

        if not child.leaf:
            for i in range(child.n, -1, -1):
                child.sons[i+1] = child.sons[i]

        child.keys[0] = self.keys[index-1]

        if not child.leaf:
            child.sons[0] = sibling.sons[sibling.n]

        self.keys[index-1] = sibling.keys[sibling.n-1]

        child.n += 1
        sibling.n -= 1

    def _borrow_from_next(self, index):
        child = self.sons[index]
        sibling = self.sons[index+1]

        child.keys[child.n] = self.keys[index]

        if not child.leaf:
            child.sons[child.n+1] = sibling.sons[0]

        self.keys[index] = sibling.keys[0]

        for i in range(child.n - 1):
            sibling.keys[i] = sibling.keys[i+1]

        if not sibling.leaf:
            for i in range(sibling.n):
                sibling.sons[i] = sibling.sons[i+1]

        child.n += 1
        sibling.n -= 1

    def _fill(self, index):
        if index != 0 and self.sons[index-1].n >= self.t:
            self._borrow_from_prev(index)
        else:
            if index != self.n and self.sons[index+1].n >= self.t:
                self._borrow_from_next(index)
            else:
                if index != self.n:
                    self._merge(index)
                else:
                    self._merge(index-1)

    def del_(self, value):
        index = self._find_key(value)

        if index < self.n and compare(self.keys[index], value) == 0:
            if self.leaf:
                self._remove_from_leaf(index)
            else:
                self._remove_from_non_leaf(index)
            return True
        else:
            if self.leaf:
                return False

            flag = False
            if index == self.n:
                flag = True

            if self.sons[index].n < self.t:
                self._fill(index)

            if flag and index > self.n:
                return self.sons[index-1].del_(value)
            else:
                return self.sons[index].del_(value)


class BTree:

    def __init__(self, id_):
        self._root = None
        self._id = id_

    def get_id(self):
        return self._id

    def get_string_id(self):
        return 'B-Tree #' + str(self._id)

    def output(self, type_='B-Tree'):
        if self._root is None:
            return str(type_) + " #" + str(self._id) + ": (empty)"
        else:
            return str(type_) + " #" + str(self._id) + ": " + str(self._root.output())

    def get(self, value):
        if self._root is None:
            return False
        else:
            if not check_types(self._root.keys[0], value):
                return False
            else:
                value = reset_value(value)
                return self._root.get(value)

    def add(self, value):
        if self._root is None:
            self._root = _TNode()
            self._root.leaf = True
            value = reset_value(value)
            self._root.keys[0] = value
            self._root.n = 1
            return True
        else:
            if not check_types(self._root.keys[0], value):
                return False
            if isinstance(value, Book):
                value.set_sort(self._root.keys[0].get_sort())
            else:
                value = reset_value(value)

            if self._root.n == 2*self._root.t - 1:
                s = _TNode()
                s.leaf = False
                s.sons[0] = self._root
                s.split_child(0, self._root)

                s.output()
                i = 0
                if compare(s.keys[0], value) == -1:
                    i = 1
                s.sons[i].insert_non_full(value)
                self._root = s
            else:
                self._root.insert_non_full(value)

            return True

    def del_(self, value):
        if self._root is None:
            return False

        if not check_types(self._root.keys[0], value):
            return False
        value = reset_value(value)

        ok = self._root.del_(value)

        if self._root.n == 0:
            if self._root.leaf:
                self._root = None
            else:
                self._root = self._root.sons[0]

        return ok

    def change(self, value_from, value_to):
        if self._root is None:
            return False

        if not check_types(self._root.keys[0], value_from):
            return False

        if not check_types(self._root.keys[0], value_to):
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

    def top(self):
        if self._root is None:
            return None
        else:
            return self._root.keys[0]
