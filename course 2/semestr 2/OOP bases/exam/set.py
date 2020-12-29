from sl_cyclic import *
from b_tree import *
from avl_tree import *


class Set:

    def __init__(self, id, structure):
        self._id = id
        self._strct_name = structure
        self._struct = None
        if structure == 'List':
            self._struct = List(id)
        else:
            if structure == 'B-tree':
                self._struct = BTree(id)
            else:
                if structure == 'AVL-tree':
                    self._struct = AVLTree(id)

    def get_id(self):
        return self._id

    def get_string_id(self):
        return 'Set(' + self._strct_name + ') #' + str(self._id)

    def add(self, value):
        if not self._struct.get(value):
            return self._struct.add(value)
        else:
            return False

    def del_(self, value):
        return self._struct.del_(value)

    def get(self, value):
        return self._struct.get(value)

    def change(self, value_from, value_to):
        return self._struct.change(value_from, value_to)

    def output(self):
        return self._struct.output('Set(' + self._strct_name + ')')

    def top(self):
        return self._struct.top()

    def get_struct(self):
        return self._strct_name

    def empty(self):
        return self._struct.empty()

    @staticmethod
    def _convert(a):
        a1 = Set(a.get_id(), 'List')
        while not a.empty():
            a1.add(a.top())
            a.del_(a.top())
        return a1

    @staticmethod
    def union(a, b, id_):
        ans = None
        if a.get_struct() != b.get_struct():
            a = Set._convert(a)
            b = Set._convert(b)
            ans = Set(id_, 'List')
        else:
            ans = Set(id_, a.get_struct())

        while not a.empty():
            val = a.top()
            a.del_(val)
            ans.add(val)
        while not b.empty():
            val = b.top()
            b.del_(val)
            ans.add(val)
        return ans

    @staticmethod
    def intersection(a, b, id_):
        ans = None
        if a.get_struct() != b.get_struct():
            a = Set._convert(a)
            b = Set._convert(b)
            ans = Set(id_, 'List')
        else:
            ans = Set(id_, a.get_struct())

        while not a.empty() and not b.empty():
            val = a.top()
            if b.get(val):
                ans.add(val)
                b.del_(val)
            a.del_(val)

        return ans

    @staticmethod

    def difference(a, b, id_):
        ans = None
        if a.get_struct() != b.get_struct():
            a = Set._convert(a)
            b = Set._convert(b)
            ans = Set(id_, 'List')
        else:
            ans = Set(id_, a.get_struct())

        while not a.empty() and not b.empty():
            val = a.top()
            if not b.get(val):
                ans.add(val)
            a.del_(val)
        return ans

    @staticmethod
    def sim_difference(a, b, id_):
        ans = None
        if a.get_struct() != b.get_struct():
            a = Set._convert(a)
            b = Set._convert(b)
            ans = Set(id_, 'List')
        else:
            ans = Set(id_, a.get_struct())

        while not a.empty() and not b.empty():
            val = a.top()
            if not b.get(val):
                ans.add(val)
            else:
                b.del_(val)
            a.del_(val)

        while not b.empty():
            val = b.top()
            ans.add(val)
            b.del_(val)

        return ans
