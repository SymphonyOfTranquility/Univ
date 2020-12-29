from container import *


class _Element:
    def __init__(self, value):
        self.value = value
        self.next = None


class List:
    def __init__(self, id):
        self._head = None
        self._id = id

    def get_id(self):
        return self._id

    def get_string_id(self):
        return 'List #' + str(self._id)

    def add(self, elem):
        temp = _Element(elem)
        if self._head is None:
            self._head = temp
            self._head.next = self._head
        else:
            move = self._head

            while move.next != self._head:
                move = move.next
            move.next = temp
            temp.next = self._head

        return True

    def top(self):
        if self._head is None:
            return None
        else:
            return self._head.value

    def compare(self, a, b):
        if isinstance(a, Book) and isinstance(b, Book):
            return a.compare(b)
        else:
            if isinstance(a, Container) and isinstance(b, Container):
                return self.compare(a.key, b.key) and self.compare(a.value, b.value)
            else:
                if (not isinstance(a, Container) and
                        not isinstance(b, Container) and
                        not isinstance(a, Book) and
                        not isinstance(b, Book)):

                    return str(a) == str(b)
                else:
                    return False

    def _get_elem(self, value):
        if self._head is None:
            return None
        else:
            move = self._head
            prev = None
            while move.next != self._head:
                if self.compare(move.value, value):
                    return Container(move, prev)

                prev = move
                move = move.next

            if self.compare(move.value, value):
                return Container(move, prev)
            else:
                return None

    def del_(self, value):
        elem = self._get_elem(value)
        if elem is None:
            return False
        else:
            prev = elem.value
            if prev is None:
                if self._head.next == self._head:
                    self._head = None
                    return True

                temp = self._head
                while temp.next != self._head:
                    temp = temp.next
                prev = temp
                self._head = self._head.next

            prev.next = elem.key.next
            return True

    def get(self, value):
        elem = self._get_elem(value)
        if elem is None:
            return False
        else:
            return True

    def change(self, from_value, to_value):
        elem = self._get_elem(from_value)
        if elem is None:
            return False
        else:
            elem.key.value = to_value
            return True

    def output(self, type_='List'):
        if self._head is None:
            return type_ + " #" + str(self._id) + ": (empty)"

        ans = type_ + " #" + str(self._id) + ": [ "
        move = self._head

        while move.next != self._head:
            if move != self._head:
                ans += ', '
            if isinstance(move.value, Book) or isinstance(move.value, Container):
                ans += move.value.output()
            else:
                ans += str(move.value)
            move = move.next

        if move != self._head:
            ans += ', '
        if isinstance(move.value, Book) or isinstance(move.value, Container):
            ans += move.value.output()
        else:
            ans += str(move.value)
        ans += ' ]'
        return ans

    def empty(self):
        if self._head is None:
            return True
        else:
            return False