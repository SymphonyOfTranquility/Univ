from set import *
from b_tree import *
from avl_tree import *
import copy

book = Book(1, 2, 3, 4, 6, 'author')
a = Set(1, 'AVL-tree')
b = Set(2, 'List')
cont = Container(23, book)
# m_list.add(book)
for i in range(32):
    a.add(i)

for i in range(20, 40, 1):
    b.add(i)
print(a.output())
print(b.output())


x = Set.union(copy.deepcopy(a), copy.deepcopy(b), 23)
print(a.output())
print(b.output())
print(x.output())

x = Set.intersection(copy.deepcopy(a), copy.deepcopy(b), 25)
print(a.output())
print(b.output())
print(x.output())

x = Set.difference(copy.deepcopy(a), copy.deepcopy(b), 26)
print(a.output())
print(b.output())
print(x.output())

x = Set.sim_difference(copy.deepcopy(a), copy.deepcopy(b), 26)
print(a.output())
print(b.output())
print(x.output())
"""
cont2 = Container(1, cont)
# m_list.add(cont)


print(m_list.output())

# print('change' + str(m_list.change(cont2, Container(23, cont2))))

print('del ' + str(m_list.del_('3e3')))
print('get ' + str(m_list.get('3e3')))
print(m_list.output())
# print('change ' + str(m_list.change(cont, '3e3')))
# print('get ' + str(m_list.get(cont)))
# print(m_list.output())
print('get ' + str(m_list.get('13')))
m_list.add('123')
print(m_list.output())
# print('del' + str(m_list.change('22', '100')))
# print(m_list.output())
# print('del ' + str(m_list.del_('123')))
# print(m_list.output())
# print('get ' + str(m_list.get(book)))
# print('del ' + str(m_list.del_(book)))
# print(m_list.output())
# print('del ' + str(m_list.del_(cont)))
# print('get ' + str(m_list.get(cont)))
# print(m_list.output())

"""