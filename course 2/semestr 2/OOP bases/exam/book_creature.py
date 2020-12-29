class Book:
    def __init__(self, author="", name="", year="", genre="", pub_house="", sort_='name'):
        self.pub_house = pub_house
        self.genre = genre
        self.year = year
        self.author = author
        self.name = name
        self._sort_on = sort_

    def get_sort(self):
        return self._sort_on

    def set_sort(self, value):
        self._sort_on = value

    def output(self):
        return ('(Author: ' + str(self.author) +
                ', Title: ' + str(self.name) +
                ', Year: ' + str(self.year) +
                ', Genre: ' + str(self.genre) +
                ', Publishing: ' + str(self.pub_house) + ')'
                )

    def compare2(self, a):
        dict_1 = {'name': self.name,
                  'author': self.author,
                  'year': self.year,
                  'genre': self.genre,
                  'publish': self.pub_house}

        dict_2 = {'name': a.name,
                  'author': a.author,
                  'year': a.year,
                  'genre': a.genre,
                  'publish': a.pub_house}

        if dict_1[self._sort_on] < dict_2[self._sort_on]:
            return -1
        else:
            if dict_1[self._sort_on] > dict_2[self._sort_on]:
                return 1
            else:
                return 0

    def compare(self, a):
        if (a.pub_house == self.pub_house and
                a.genre == self.genre and
                a.name == self.name and
                a.year == self.year and
                a.author == self.author):
            return True
        else:
            return False

    def get_sort(self):
        return self._sort_on
