from PyQt5.QtCore import pyqtSignal
from functools import partial
from PyQt5.QtWidgets import *
import copy

from sl_cyclic import *
from set import *
from b_tree import *
from avl_tree import *


class Window(QWidget):

    def __init__(self):
        super().__init__()
        self._initUI()
        self._init_back()

    def _initUI(self):
        self._create_obj_button = QPushButton('Create object', self)
        self._create_obj_button.clicked.connect(self._create_object)
        self._work_with_union_button = QPushButton('Work with union', self)
        self._work_with_union_button.clicked.connect(self._work_with_union)
        self._sorting_button = QPushButton('Sorting', self)
        size_x = 110
        size_y = 25
        self._create_obj_button.resize(size_x, size_y)
        self._work_with_union_button.resize(size_x, size_y)
        self._sorting_button.resize(size_x, size_y)

        self._create_obj_button.move(20, 25)
        self._work_with_union_button.move(20, 55)
        self._sorting_button.move(20, 85)

        self._field_label = QLabel('Data set', self)
        self._field_label.move(140, 7)

        self._field_with_data = QTextEdit(self)
        self._field_with_data.resize(400, 500)
        self._field_with_data.move(140, 25)
        self._field_with_data.setReadOnly(True)

        self.setWindowTitle('Exam')
        self.show()

    def _init_back(self):
        self._list_of_structures = []

    def _create_object(self):
        self._cr_obj = _CreateObject(self._list_of_structures)
        self._cr_obj.trigger.connect(partial(self._adding_to_list, self._cr_obj))

    def _work_with_union(self):
        self._union = _WorkWithSets(self._list_of_structures)
        self._union.trigger.connect(partial(self._adding_to_list, self._union))

    def _show_objects(self):
        ans = ""
        for value in self._list_of_structures:
            ans += value.output() + '\n'

        self._field_with_data.setText(ans)

    def _adding_to_list(self, obj):
        self._list_of_structures = obj.get_list()
        self._show_objects()

    def closeEvent(self, event):
        if hasattr(self, '_cr_obj'):
            self._cr_obj.close()
        if hasattr(self, '_union'):
            self._union.close()
        event.accept()


class _CreateObject(QWidget):

    trigger = pyqtSignal()

    def __init__(self, list_of_structures):
        super().__init__()
        self._init_UI()
        self._init_back(list_of_structures)

    def _init_UI(self):
        # choose structure
        self._label_combo_structure = QLabel('Choose structure:', self)
        self._combo_structure = QComboBox(self)
        self._combo_structure.addItem('Set (List)', 's_list')
        self._combo_structure.addItem('Set (B-Tree)', 's_b-tree')
        self._combo_structure.addItem('Set (AVL-Tree)', 's_avl_tree')
        self._combo_structure.addItem('List', 'list')
        self._combo_structure.addItem('B-tree', 'b-tree')
        self._combo_structure.addItem('AVL-tree', 'AVL-tree')
        self._create_structure = QPushButton('Create structure', self)

        # choose existing structure
        self._label_exist_structure = QLabel('Existing structure:', self)
        self._exist_structure = QComboBox(self)
        self._exist_structure.addItem('empty', 'empty')
        self._ch_exist_structure = QPushButton('Choose structure', self)

        # all buttons
        self._button_dict = {'add': QPushButton('Add element', self),
                             'get': QPushButton('Get element', self),
                             'change': QPushButton('Change element', self),
                             'del': QPushButton('Delete element', self)
                             }

        self._button_controls()

        # display field
        self._field_with_data = QTextEdit(self)
        self._field_with_data.setReadOnly(True)

        self._set_positions()

        self._status_bar = QStatusBar(self)

        self._message_box = QMessageBox()
        self._message_box.setStandardButtons(QMessageBox.Ok)
        self._message_box.hide()

        self.setWindowTitle('Create object')
        self.resize(380, 300)
        self.show()

    def _set_positions(self):
        self._label_combo_structure.move(20, 20)
        self._combo_structure.move(119, 17)
        self._combo_structure.resize(120, 20)
        self._create_structure.move(250, 16)
        self._create_structure.resize(110, 23)

        self._label_exist_structure.move(20, 45)
        self._exist_structure.move(119, 42)
        self._exist_structure.resize(120, 20)
        self._ch_exist_structure.move(250, 41)
        self._ch_exist_structure.resize(110, 23)

        i = 0
        for key in self._button_dict:
            self._button_dict[key].resize(110, 25)
            self._button_dict[key].move(250, 80 + i*30)
            i += 1

        self._field_with_data.resize(220, 200)
        self._field_with_data.move(20, 80)

    def _init_back(self, list_of_values):
        self._list_of_structures = list_of_values
        self._current_struct = -1

        if len(self._list_of_structures) != 0:

            if self._exist_structure.currentData() == 'empty':
                self._exist_structure.removeItem(0)
            self._current_struct = 0

            for i in range(len(self._list_of_structures)):
                self._exist_structure.addItem(self._list_of_structures[i].get_string_id(),
                                              str(self._list_of_structures[i].get_id()))

            self._show_structure(self._list_of_structures[0])

    def get_list(self):
        return self._list_of_structures

    def _button_controls(self):
        self._create_structure.clicked.connect(self._create_struct_func)
        self._ch_exist_structure.clicked.connect(self._choose_struct_func)
        self._button_dict['add'].clicked.connect(self._add_element)
        self._button_dict['get'].clicked.connect(self._get_element)
        self._button_dict['del'].clicked.connect(self._del_element)
        self._button_dict['change'].clicked.connect(self._change_element)

    def _create_struct_func(self):
        data = self._combo_structure.currentData()
        temp = None
        if data == 'list':
            temp = List(len(self._list_of_structures))
            self._list_of_structures.append(temp)
        else:
            if data == 's_list':
                temp = Set(len(self._list_of_structures), 'List')
                self._list_of_structures.append(temp)
            elif data == 's_b-tree':
                temp = Set(len(self._list_of_structures), 'B-tree')
                self._list_of_structures.append(temp)
            elif data == 's_avl_tree':
                temp = Set(len(self._list_of_structures), 'AVL-tree')
                self._list_of_structures.append(temp)
            else:
                if data == 'b-tree':
                    temp = BTree(len(self._list_of_structures))
                    self._list_of_structures.append(temp)
                else:
                    if data == 'AVL-tree':
                        temp = AVLTree(len(self._list_of_structures))
                        self._list_of_structures.append(temp)
                    else:
                        self._message_box.setIcon(QMessageBox.Warning)
                        self._message_box.setWindowTitle('Choose structure')
                        self._message_box.setText('There is no such structure in program')
                        self._message_box.show()
                        return

        if self._exist_structure.currentData() == 'empty':
            self._exist_structure.removeItem(0)

        self._current_struct = len(self._list_of_structures)-1
        self._exist_structure.addItem(self._list_of_structures[-1].get_string_id(),
                                      str(self._list_of_structures[-1].get_id()))
        self._show_structure(temp)
        self.trigger.emit()

    def _choose_struct_func(self):
        n = self._exist_structure.currentData()
        if n != 'empty':
            self._show_structure(self._list_of_structures[int(n)])
            self._current_struct = int(n)
        else:
            self._message_box.setIcon(QMessageBox.Warning)
            self._message_box.setWindowTitle('Choose structure')
            self._message_box.setText('Sorry there is no existing structures')
            self._message_box.show()

    def _show_structure(self, current_val):
        self._field_with_data.setText(current_val.output())

    def _add_element(self):
        if self._current_struct != -1:
            self._adding_widget = _AddingObject(self._list_of_structures[self._current_struct], 0, 'Add')
            self._adding_widget.trigger.connect(self._add_to_struct)

    def _add_to_struct(self):
        n = self._current_struct
        if self._list_of_structures[n].add(self._adding_widget.get_item()):
            self._message_box.setIcon(QMessageBox.Information)
            self._message_box.setText('Successfully added')
        else:
            if isinstance(self._list_of_structures[n], BTree)\
                    or isinstance(self._list_of_structures[n], AVLTree):
                self._message_box.setIcon(QMessageBox.Warning)
                self._message_box.setText('Different types, cannot add')

        self._show_structure(self._list_of_structures[n])
        self.trigger.emit()
        self._adding_widget.close()

        self._message_box.setWindowTitle('Add')
        self._message_box.show()

    def _get_element(self):
        if self._current_struct != -1:
            self._adding_widget = _AddingObject(self._list_of_structures[self._current_struct], 0, 'Get')
            self._adding_widget.trigger.connect(self._get_in_struct)

    def _get_in_struct(self):
        n = self._current_struct
        self._message_box.setWindowTitle('Getting')
        if self._list_of_structures[n].get(self._adding_widget.get_item()):
            self._message_box.setText('Element exist in structure')
            self._message_box.setIcon(QMessageBox.Information)
        else:
            self._message_box.setText('Element does not exist in structure')
            self._message_box.setIcon(QMessageBox.Warning)
        self._message_box.show()
        self._show_structure(self._list_of_structures[n])
        self.trigger.emit()
        self._adding_widget.close()

    def _change_element(self):
        if self._current_struct != -1:
            self._adding_widget = _AddingObject(self._list_of_structures[self._current_struct], 0, 'Change from')
            self._adding_widget.trigger.connect(self._change_to)

    def _change_to(self):
        if self._current_struct != -1:
            n = self._current_struct
            if self._list_of_structures[n].get(self._adding_widget.get_item()):
                self._temp_item = self._adding_widget.get_item()
                self._adding_widget.close()
                self._adding_widget = _AddingObject(self._list_of_structures[self._current_struct], 0, 'Change to')
                self._adding_widget.trigger.connect(self._change_in_struct)
            else:
                self._message_box.setWindowTitle('Change')
                self._message_box.setText('Element does not exist in structure')
                self._message_box.setIcon(QMessageBox.Warning)
                self._message_box.show()

    def _change_in_struct(self):
        n = self._current_struct
        if self._list_of_structures[n].change(self._temp_item, self._adding_widget.get_item()):
            self._message_box.setWindowTitle('Change')
            self._message_box.setText('Successfully changed')
            self._message_box.show()
            self._message_box.setIcon(QMessageBox.Information)
        else:
            self._message_box.setWindowTitle('Change')
            self._message_box.setText('Different types, cannot add')
            self._message_box.setIcon(QMessageBox.Warning)
            self._message_box.show()
        self._show_structure(self._list_of_structures[n])
        self.trigger.emit()
        self._adding_widget.close()


    def _del_element(self):
        if self._current_struct != -1:
            self._adding_widget = _AddingObject(self._list_of_structures[self._current_struct], 0, 'Delete')
            self._adding_widget.trigger.connect(self._del_in_struct)

    def _del_in_struct(self):
        n = self._current_struct
        if self._list_of_structures[n].del_(self._adding_widget.get_item()):
            self._message_box.setWindowTitle('Delete')
            self._message_box.setText('Successfully deleted')
            self._message_box.setIcon(QMessageBox.Information)
            self._message_box.show()
        else:
            self._message_box.setIcon(QMessageBox.Warning)
            self._message_box.setWindowTitle('Delete')
            self._message_box.setText('Element does not exist in structure')
            self._message_box.show()
        self._show_structure(self._list_of_structures[n])
        self.trigger.emit()
        self._adding_widget.close()

    def closeEvent(self, event):
        if hasattr(self, '_adding_widget'):
            self._adding_widget.close()

        if hasattr(self, '_message_box'):
            self._message_box.close()
        event.accept()


class _AddingObject(QWidget):

    trigger = pyqtSignal()

    def __init__(self, struct, depth, mean):
        super().__init__()
        self._init_back(struct, depth, mean)
        self._initUI(mean)

    def _initUI(self, mean):
        # combo add
        self._label_combo_add = [
            QLabel('Choose type of containers:', self),
            QLabel('Key container:', self),
            QLabel('Choose type of values:', self)
            ]

        self._combo_add = [
            QComboBox(self),
            QComboBox(self)
            ]
        if self._depth == 0:
            self._combo_add[0].addItem('Container key-value', 'key')
            self._combo_add[0].addItem('Book entity', 'book')
            self._combo_add[0].addItem('Single value', 'single')

            self._combo_add[1].addItem('Single value', 'single')
            self._combo_add[1].addItem('Book entity', 'book')
            self._combo_add[1].addItem('Container key-value', 'key')
        else:
            self._combo_add[1].addItem('Single value', 'single')
            self._combo_add[1].addItem('Book entity', 'book')
            self._combo_add[1].addItem('Container key-value', 'key')
            self._combo_add[0].addItem('Container key-value', 'key')

        self._button_add = QPushButton(mean + ' element', self)
        self._button_add.clicked.connect(self._element_addition)

        # input field for containers
        # input field
        self._field_simple = [QLineEdit(self), QLineEdit(self), QLineEdit(self)]
        self._label_simple = [QLabel('Value:', self), QLabel('Value:', self), QLabel('Value:', self)]

        self._field_entity = []
        for i in range(3):
            self._label_combo_add[i].hide()
            self._field_simple[i].hide()
            self._label_simple[i].hide()

        for i in range(2):
            self._combo_add[i].hide()
            self._field_entity.append([QLabel('Author:', self), QLineEdit(self),
                                       QLabel('Title:', self), QLineEdit(self),
                                       QLabel('Year:', self), QLineEdit(self),
                                       QLabel('Genre:', self), QLineEdit(self),
                                       QLabel('Publishing:', self), QLineEdit(self)
                                       ])
            for x in self._field_entity[i]:
                x.hide()

        self._show_field = QTextEdit(self)
        self._show_field.setReadOnly(True)

        self._message_box = QMessageBox()
        self._message_box.setStandardButtons(QMessageBox.Ok)
        self._message_box.hide()

        self._combo_add[0].currentTextChanged.connect(self._main_add)
        self._combo_add[1].currentTextChanged.connect(self._add_keys)

        self._label_for_book = QLabel('Choose key for book:', self)
        self._label_for_book.hide()
        self._combobox_for_book = QComboBox(self)
        self._combobox_for_book.addItem('Author', 'author')
        self._combobox_for_book.addItem('Name', 'name')
        self._combobox_for_book.addItem('Year', 'year')
        self._combobox_for_book.addItem('Genre', 'genre')
        self._combobox_for_book.addItem('Publishing', 'publish')
        self._combobox_for_book.hide()

        self._set_positions()
        self.resize(500, 330)
        self.setWindowTitle('Create object #' + str(self._depth))
        self.show()

    def _set_positions(self):
        self._button_add.move(250, 20)
        self._button_add.resize(180, 50)
        self._button_add.show()

        self._label_combo_add[0].move(30, 20)
        self._combo_add[0].move(30, 40)
        self._label_combo_add[0].show()
        self._combo_add[0].show()

        self._label_combo_add[1].move(30, 80)
        self._label_combo_add[2].move(250, 80)
        self._combo_add[1].move(250, 100)
        self._label_combo_add[1].show()
        self._label_combo_add[2].show()
        self._combo_add[1].show()

        for x in range(5):
            self._field_entity[0][2*x].move(30, 80 + x*30)
            self._field_entity[0][2*x + 1].move(100, 75 + x*30)
            self._field_entity[0][2*x].hide()
            self._field_entity[0][2*x + 1].hide()

            self._field_entity[1][2 * x].move(250, 140 + x * 30)
            self._field_entity[1][2 * x + 1].move(320, 135 + x * 30)
            self._field_entity[1][2 * x].hide()
            self._field_entity[1][2 * x + 1].hide()

        self._label_for_book.move(30, 240)
        self._combobox_for_book.move(30, 260)

        self._label_simple[0].move(30, 80)
        self._field_simple[0].move(70, 77)

        self._label_simple[1].move(30, 105)
        self._field_simple[1].move(70, 103)
        self._label_simple[1].show()
        self._field_simple[1].show()

        self._label_simple[2].move(250, 140)
        self._field_simple[2].move(290, 137)
        self._label_simple[2].show()
        self._field_simple[2].show()

        self._show_field.resize(200, 150)
        self._show_field.move(250, 140)
        self._show_field.hide()

    def _main_add(self):
        self._show_field.hide()
        self._combobox_for_book.hide()
        self._label_for_book.hide()

        if self._combo_add[0].currentData() == 'book':

            if (isinstance(self._struct, BTree) or isinstance(self._struct, AVLTree)
                    or isinstance(self._struct, Set) and (self._struct.get_struct() == 'B-tree'
                    or self._struct.get_struct() == 'AVL-tree')) and self._struct.empty():
                self._combobox_for_book.show()
                self._label_for_book.show()

            self._label_combo_add[1].hide()

            self._combo_add[1].hide()
            self._label_combo_add[2].hide()

            for j in range(5):
                self._field_entity[0][2 * j].show()
                self._field_entity[0][2 * j + 1].show()
                self._field_entity[0][2 * j + 1].clear()

                self._field_entity[1][2 * j].hide()
                self._field_entity[1][2 * j + 1].hide()
                self._field_entity[1][2 * j + 1].clear()

            for i in range(3):
                self._label_simple[i].hide()
                self._field_simple[i].hide()
                self._field_simple[i].clear()

        else:
            if self._combo_add[0].currentData() == 'key':
                self._label_combo_add[1].show()

                self._combo_add[1].show()
                self._label_combo_add[2].show()

                for y in range(2):
                    for x in range(5):
                        self._field_entity[y][2 * x].hide()
                        self._field_entity[y][2 * x + 1].hide()
                        self._field_entity[y][2 * x + 1].clear()

                for i in range(2):
                    self._label_simple[i + 1].show()
                    self._field_simple[i + 1].show()
                    self._field_simple[i + 1].clear()

                self._label_simple[0].hide()
                self._field_simple[0].hide()
                self._field_simple[0].clear()

            else:
                self._label_combo_add[1].hide()

                self._combo_add[1].hide()
                self._label_combo_add[2].hide()

                for i in range(2):
                    for j in range(5):
                        self._field_entity[i][2 * j].hide()
                        self._field_entity[i][2 * j + 1].hide()
                        self._field_entity[i][2 * j + 1].clear()

                self._label_simple[0].show()
                self._field_simple[0].show()
                self._field_simple[0].clear()

                for i in range(2):
                    self._label_simple[i+1].hide()
                    self._field_simple[i+1].hide()
                    self._field_simple[i+1].clear()

    def _add_keys(self):
        if self._combo_add[1].currentData() == 'book':
            self._show_field.hide()
            for j in range(5):
                self._field_entity[1][2 * j].show()
                self._field_entity[1][2 * j + 1].show()
                self._field_entity[1][2 * j + 1].clear()

            self._label_simple[2].hide()
            self._field_simple[2].hide()
            self._field_simple[2].clear()

        else:
            if self._combo_add[1].currentData() == 'single':
                self._show_field.hide()
                for i in range(5):
                    self._field_entity[1][2 * i].hide()
                    self._field_entity[1][2 * i + 1].hide()
                    self._field_entity[1][2 * i + 1].clear()

                self._label_simple[2].show()
                self._field_simple[2].show()
                self._field_simple[2].clear()
            else:
                self._show_field.show()
                self._show_field.clear()
                for i in range(5):
                    self._field_entity[1][2 * i].hide()
                    self._field_entity[1][2 * i + 1].hide()
                    self._field_entity[1][2 * i + 1].clear()

                self._label_simple[2].hide()
                self._field_simple[2].hide()
                self._field_simple[2].clear()

                self._new_table = _AddingObject(self._struct, self._depth+1, self._mean)
                self._new_table.trigger.connect(self._show_container_key)

    def _show_container_key(self):
        if self._item is None or not (isinstance(self._item, Container)):
            self._item = Container(None, self._new_table.get_item())
        else:
            self._item.value = self._new_table.get_item()
        self._new_table.close()

        if isinstance(self._item.value, (Container, Book)):
            self._show_field.setText(self._item.value.output())
        else:
            self._show_field.setText(str(self._item.value))

    def _check_function(self, i):
        temp = None
        if i == 2:
            if self._field_simple[1].text() != "":
                temp = self._field_simple[1].text()
        else:
            if self._combo_add[-i].currentData() == 'single':
                if self._field_simple[-i].text() != "":
                    temp = self._field_simple[-i].text()
            else:
                ok = True
                for x in range(5):
                    if self._field_entity[-i][2 * x + 1].text() == "":
                        ok = False
                if ok is True:
                    sort_ = 'name'
                    if (i == 0 and (isinstance(self._struct, BTree) or isinstance(self._struct, AVLTree)
                        or isinstance(self._struct, Set) and (self._struct.get_struct() == 'B-tree'
                                    or self._struct.get_struct() == 'AVL-tree'))
                            and self._struct.empty()):
                        sort_ = self._combobox_for_book.currentData()
                    if not self._field_entity[-i][5].text().isdigit():
                        temp = None
                    else:
                        temp = Book(
                            self._field_entity[-i][1].text(),
                            self._field_entity[-i][3].text(),
                            self._field_entity[-i][5].text(),
                            self._field_entity[-i][7].text(),
                            self._field_entity[-i][9].text(),
                            sort_
                        )

        if i == 0:
            self._item = temp
        else:
            if i == 2:
                self._item.key = temp
            else:
                self._item.value = temp

    def _element_addition(self):
        if self._combo_add[0].currentData() == 'key':
            if self._item is None:
                self._item = Container(None, None)

            if self._item.key is None:
                self._check_function(2)

            if self._item.value is None:
                self._check_function(1)

            if self._item.key is not None and self._item.value is not None:
                self.trigger.emit()
            else:
                if self._combo_add[1].currentData() == 'book' and not self._field_entity[1][5].text().isdigit():
                    self._message_box.setIcon(QMessageBox.Warning)
                    self._message_box.setWindowTitle('Fields')
                    self._message_box.setText('Field of year have to be int')
                    self._message_box.show()
                else:
                    self._message_box.setIcon(QMessageBox.Warning)
                    self._message_box.setWindowTitle('Fields')
                    self._message_box.setText('Some fields are empty')
                    self._message_box.show()
        else:
            self._check_function(0)
            if self._item is not None:
                self.trigger.emit()
            else:
                if self._combo_add[0].currentData() == 'book' and not self._field_entity[0][5].text().isdigit():
                    self._message_box.setIcon(QMessageBox.Warning)
                    self._message_box.setWindowTitle('Fields')
                    self._message_box.setText('Field of year have to be int')
                    self._message_box.show()
                else:
                    self._message_box.setIcon(QMessageBox.Warning)
                    self._message_box.setWindowTitle('Fields')
                    self._message_box.setText('Some fields are empty')
                    self._message_box.show()

    def get_item(self):
        return self._item

    def get_string_item(self):
        if isinstance(self._item, Book) or isinstance(self._item, Container):
            return self._item.output()
        else:
            return str(self._item)

    def _init_back(self, struct, depth, mean):
        self._struct = struct
        self._depth = depth
        self._item = None
        self._mean = mean

    def closeEvent(self, event):
        if hasattr(self, '_new_table'):
            self._new_table.close()

        if hasattr(self, '_message_box'):
            self._message_box.close()
        event.accept()


class _WorkWithSets(QWidget):

    trigger = pyqtSignal()

    def __init__(self, list_of_structs):
        super().__init__()
        self._init_back(list_of_structs)
        self._initUI()

    def _initUI(self):
        self._label_set_a = QLabel('Choose first set', self)
        self._label_set_b = QLabel('Choose second set', self)
        self._combo_set_a = QComboBox(self)
        self._combo_set_b = QComboBox(self)

        ok = False
        for i in self._list_of_structs:
            if isinstance(i, Set):
                self._combo_set_a.addItem(i.get_string_id(), i.get_id())
                self._combo_set_b.addItem(i.get_string_id(), i.get_id())
                ok = True

        if not ok:
            self._combo_set_a.addItem('empty', 'empty')
            self._combo_set_b.addItem('empty', 'empty')

        self._edit_set_a = QTextEdit(self)
        self._edit_set_b = QTextEdit(self)

        self._combo_set_a.currentTextChanged.connect(partial(self._change_text, self._combo_set_a, self._edit_set_a))
        self._combo_set_b.currentTextChanged.connect(partial(self._change_text, self._combo_set_b, self._edit_set_b))

        self._edit_set_ans = QTextEdit(self)
        self._combo_ans = QComboBox(self)
        self._combo_ans.addItem('Union', '+')
        self._combo_ans.addItem('Intersecion', '*')
        self._combo_ans.addItem('Difference', '/')
        self._combo_ans.addItem('Symmetric difference', '\\')
        self._combo_ans.currentTextChanged.connect(self._change_ans)

        if self._combo_set_a.currentData() != 'empty':
            self._change_text(self._combo_set_a, self._edit_set_a)
            self._change_text(self._combo_set_b, self._edit_set_b)

        self._add_button = QPushButton('Add to main list', self)
        self._add_button.clicked.connect(self._add_to_main)
        self._set_positions()
        self.setWindowTitle('Work with unions')
        self.show()

    def _set_positions(self):
        self._label_set_a.move(30, 28)
        self._label_set_b.move(440, 28)
        self._combo_set_a.move(115, 23)
        self._combo_set_b.move(540, 23)
        self._combo_set_a.resize(120, 25)
        self._combo_set_b.resize(120, 25)
        self._edit_set_a.move(30, 50)
        self._edit_set_a.resize(205, 220)
        self._edit_set_b.move(440, 50)
        self._edit_set_b.resize(220, 220)

        self._combo_ans.move(252, 50)
        self._combo_ans.resize(170, 25)
        self._edit_set_ans.resize(170, 163)
        self._edit_set_ans.move(252, 76)

        self._add_button.move(251, 240)
        self._add_button.resize(172, 30)

    def _change_text(self, combo, edit):
        value = combo.currentData()
        edit.setText(self._list_of_structs[int(value)].output())
        self._change_ans()

    def _change_ans(self):
        if self._combo_set_a.currentData() == 'empty':
            return

        value = self._combo_ans.currentData()
        self._cur_ans = None
        set_a = self._list_of_structs[int(self._combo_set_a.currentData())]
        set_b = self._list_of_structs[int(self._combo_set_b.currentData())]

        if value == '*':
            self._cur_ans = Set.intersection(copy.deepcopy(set_a), copy.deepcopy(set_b), len(self._list_of_structs))
        elif value == '+':
            self._cur_ans = Set.union(copy.deepcopy(set_a), copy.deepcopy(set_b), len(self._list_of_structs))
        elif value == '/':
            self._cur_ans = Set.difference(copy.deepcopy(set_a), copy.deepcopy(set_b), len(self._list_of_structs))
        else:
            self._cur_ans = Set.sim_difference(copy.deepcopy(set_a), copy.deepcopy(set_b), len(self._list_of_structs))

        self._edit_set_ans.setText(self._cur_ans.output())

    def get_list(self):
        return self._list_of_structs

    def _add_to_main(self):
        if self._cur_ans is not None:
            self._list_of_structs.append(self._cur_ans)
            self._combo_set_a.addItem(self._cur_ans.get_string_id(), self._cur_ans.get_id())
            self._combo_set_b.addItem(self._cur_ans.get_string_id(), self._cur_ans.get_id())
            self._change_ans()
            self.trigger.emit()

    def _init_back(self, list_of_structs):
        self._list_of_structs = list_of_structs
        self._cur_ans = None
