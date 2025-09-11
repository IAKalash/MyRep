int pow(int base, int power)  //степень int ПОЛОЖИТЕЛЬНАЯ
{
    if (power == 0)
    {
        return 1;
    }
    else
    {
        return base * pow(base, power - 1);
    }
}

//**************************************************************************************

int AnyToInt(int sys, char *nums)
{
    int power = 0, sum = 0, num;
    int lenght = len(nums);

    while (lenght != 0) // перевод в десятичную
    {
        num = nums[lenght - 1];
        nums[lenght - 1] = 0;
        lenght -= 1;

        if (Isalpha(num) == 1)
        {
            num -= 87;
        }

        sum += num * pow(sys, power);
        ++power;
    }
    return (sum);
}

//****************************************************************************************** 

int Reverse(int num) // ТОЛЬКО ДЛЯ int
{
    int res;
    while (num > 0)
    {
        res = res * 10 + num % 10;
        num /= 10;
    }
    return res;
}

void reverse(char *start, int len) // Вывод строки в обратном  порядке
{
    for (int i = len - 1; i >= 0; --i)
    {
        printf("%c", start[i]);
    }
}

//******************************************************************************************

int Vis(int year) { // Високосный год (1,0)
    int fl;
    if (year % 4 == 0) {
        if (year % 100 == 0){
            fl = (year % 400 == 0) ? 1 : 0;
        }
        else{
            fl = 1;
        }
    }
    else {
        fl = 0;
    }
    return (fl);
} 
//******************************************************************************************
int Isalpha(char let) {  //Проверка на букву (латиница)
    return (let >= 'A' && let <= 'Z') || (let >= 'a' && let <= 'z');
}
//******************************************************************************************
int Not (int fl) { // Not gate 
    return (fl == 1) ? 0 : 1;
}

//******************************************************************************************

void bubble(int els, int *array) // Пузырёк
{
    int x;
    for (int i = 0; i < els; ++i)
    {
        for (int j = i + 1; j < els; ++j)
        {
            if (array[i] > array[j])
            {
                x = array[j];
                array[j] = array[i];
                array[i] = x;
            }
        }
    }
}

//******************************************************************************************

int len(char *string) // Длина строки
{
    char sym = ' ';
    int i = 0;
    while (sym != '\0')
    {
        sym = string[i];
        ++i;
    }
    return i - 1;
}

int len(int num) //Число разрядов
{
    int i = 0;
    while (num > 0)
    {
        num /= 10;
        ++i;
    }
    return i;
}

//******************************************************************************************

char *concat(char *pref, char *suff) // Добавление второй строки в конец первой
{
    int n = 0;
    for (int i = len(pref); i < len(pref) + len(suff); ++i)
    {
        pref[i] = suff[n];
        ++n;
    }
}

//******************************************************************************************

//--------------------------------ДЛИННЫЕ ЧИСЛА-------------------------

typedef struct LongNum_s //форма длинного числа
{
    int len;      // сколько цифр в числе
    int arr[500]; // массив десятичных цифр числа
} LongNum;

//----------------------------------------------------------------------

void sum(LongNum *num1, LongNum *num2, LongNum *res)   // сложение длинных чисел
{
    for (int i = 0; i < num2->len; ++i)
    {
        res->arr[i + 1] = (num1->arr[i] + num2->arr[i] + res->arr[i]) / 10;
        res->arr[i] = (num1->arr[i] + num2->arr[i] + res->arr[i]) % 10;
    }
    res->len = (res->arr[num2->len] && 1) ? num2->len + 1 : num2->len;
}

//----------------------------------------------------------------------

void printstruct(LongNum *num)  // вывод длинных чисел
{
    for (int i = num->len - 1; i >= 0; --i)
    {
        printf("%d", num->arr[i]);
    }
}

//----------------------------------------------------------------------

void mult(LongNum *num, int num2) // умножение длинных чисел
{
    int carry = 0, x;
    for (int i = 0; i < num->len; ++i)
    {
        x = num->arr[i] * num2 + carry;
        num->arr[i] = x % 10;
        carry = x / 10;
    }
    int n = 0;
    while (carry >= 1)
    {
        num->arr[num->len + n] = carry % 10;
        ++n;
        carry /= 10;
    }
    num->len += n;
    while (num->arr[num->len] != 0)
    {
        ++num->len;
    }
}

//----------------------------------------------------------------------
