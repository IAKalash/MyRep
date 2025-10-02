class Item:
    def __init__(self, count=3, max_count=16):
        self._count = count
        self._max_count = max_count
        
    def __del__(self):
        return None

    def update_count(self, val):
        if val <= 0:
            print(f"Object {self.my_name()} deleted")
            return self.__del__()
        elif val <= self._max_count:
            self._count = val
            return True
        else:
            return False
        
    @property
    def count(self):
        return self._count
    
    @classmethod
    def my_name(cls):
        return cls.__name__
    
    def __add__(self, num):
        """ Сложение с числом """
        return self.count + num
    
    def __sub__(self, num):
        """ Вычитание числа """
        return self.count - num
    
    def __mul__(self, num):
        """ Умножение на число """
        return self.count * num
    
    def __lt__(self, num):
        """ Сравнение меньше """
        return self.count < num
    
    def __gt__(self, num):
        """ Сравнение больше """
        return self.count > num
    
    def __eq__(self, num):
        """ Сравнение """
        return self.count == num
    
    def __ne__(self, num):
        """ Сравнение """
        return self.count != num
    
    def __le__(self, num):
        """ Сравнение <= """
        return self.count <= num
    
    def __ge__(self, num):
        """ Сравнение >= """
        return self.count >= num

    def __len__(self):
        """ Получение длины объекта """
        return self.count
    
    def __iadd__(self, num):
        """ += """
        if (not self.update_count(self + num)):
            self.update_count(self._max_count)
        return self
    
    def __imul__(self, num):
        """ *= """
        if (not self.update_count(self * num)):
            self.update_count(self._max_count)
        return self
    
    def __isub__(self, num):
        """ -= """
        if (self - num > 0):
            self.update_count(self - num)
            return self
        else: return self.update_count(0)
        


class Fruit(Item):
    def __init__(self, ripe=True, **kwargs):
        super().__init__(**kwargs)
        self._ripe = ripe


class Food(Item):
    def __init__(self, saturation, **kwargs):
        super().__init__(**kwargs)
        self._saturation = saturation
        
    @property
    def eatable(self):
        return self._saturation > 0


class Cake(Food):

    def __init__(self, count=1, max_count=32, saturation=100):
        super().__init__(saturation=saturation, count=count, max_count=max_count)
        
    @property
    def eatable(self):
        return super().eatable
    
class Burger(Food):

    def __init__(self, count=1, max_count=32, saturation=80):
        super().__init__(saturation=saturation, count=count, max_count=max_count)
        
    @property
    def eatable(self):
        return super().eatable
    
class Strawberry(Fruit, Food):
    def __init__(self, ripe, count=1, max_count=32, color='red', saturation=5):
        super().__init__(saturation=saturation, ripe=ripe, count=count, max_count=max_count)
        self._color = color
    
    @property
    def color(self):
        return self._color
        
    @property
    def eatable(self):
        return super().eatable and self._ripe

class Blueberry(Fruit, Food):
    def __init__(self, ripe, count=1, max_count=32, color='blue', saturation=5):
        super().__init__(saturation=saturation, ripe=ripe, count=count, max_count=max_count)
        self._color = color
    
    @property
    def color(self):
        return self._color
        
    @property
    def eatable(self):
        return super().eatable and self._ripe
    
class Inventory:
    def __init__(self, capacity = 16):
        self._capacity = capacity
        self._items = 0
        self._elems = []
        for _ in range(capacity):
            self._elems.append(None)

    @property
    def items(self):
        return self._items
    
    @property
    def capacity(self):
        return self._capacity

    def __getitem__(self, index):
        if index > self._capacity:
            raise IndexError(f'Index {index} more than {self._capacity}')
        return self._elems[index]
    
    def __setitem__(self, index, item):
        if index > self._capacity:
            raise IndexError(f'Index {index} more than {self._capacity}')
        self._elems[index] = item

    def find(self, item):
        for i in range(self._capacity):
            if self[i] == item:
                return i
            
    
inv = Inventory()
print(inv[0])
tort = Cake(3)
berry = Strawberry(True, 7)

inv[3] = tort
inv[0] = berry


print(inv[0].count)
inv[0] *= 2
print(inv[0].count)

print(inv[3] - 1)
inv[3] -= 3
print(inv[3])

