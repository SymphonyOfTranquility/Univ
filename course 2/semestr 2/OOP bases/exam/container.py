from book_creature import *


def check_types(a, b):
    if isinstance(a, Book) and isinstance(b, Book):
        return True
    else:
        if isinstance(a, Book) or isinstance(b, Book):
            return False
    x = str(a)
    y = str(b)
    if isinstance(a, Container) and isinstance(b, Container):
        x = str(a.key)
        y = str(b.key)
        if x.isdigit() and not y.isdigit():
            return False
        else:
            return True
    else:
        if isinstance(a, Container) or isinstance(b, Container):
            return False
    if x.isdigit() and not y.isdigit():
        return False
    else:
        return True


def reset_value(value):
    if not isinstance(value, (Container, Book)):
        x = str(value)
        if x.isdigit():
            return int(value)
    return value


def compare(a, b):
    x = a
    y = b
    if isinstance(a, Container):
        x = a.key
        y = b.key
    else:
        if isinstance(a, Book):
            return a.compare2(b)
    if x > y:
        return 1
    else:
        if x < y:
            return -1
        else:
            return 0




class Container:

    def __init__(self, key, value):
        self.key = key
        self.value = value

    def output(self):
        ans = "{ "
        if isinstance(self.key, (Book, Container)):
            ans += self.key.output() + ', '
        else:
            ans += str(self.key) + ', '

        if isinstance(self.value, (Book, Container)):
            ans += self.value.output() + ' }'
        else:
            ans += str(self.value) + ' }'

        return ans


