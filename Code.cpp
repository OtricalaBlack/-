#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <locale.h>
#include <malloc.h>
#include <string.h>

// Объявление функции, отвечающей за обход графа в глубину 
bool bpm(bool** graph, int u, bool visited[], int matchR[], int vertices);

// Объявление функции, отвечающей за вывод всех паросочетаний 
void printAllMatchings(bool** graph, int vertices);

// Объявление функции, отвечающей вывод 
void printMatching(bool** graph, int matchR[], int vertices);

// Функция, отвечающие за поиск всех паросочетаний 
void printAllMatchingsUtil(bool** graph, int u, bool visited[], int matchR[], int vertices);

// Выделение памяти для матрицы смежности
int memoryAllocation(bool** graph, int vertices);

// Объявление функции, отвечающей за генерацию матриц графа и орграфа 
void generateRandomGraph(bool** graph, int vertices, int graphType);

// Объявление функции, отвечающей вывод матрицы смежности 
void printGraph(bool** graph, int vertices);

// Вывод паросочетания, если оно уникальное 
bool isMatchingPrinted(char* matching);

// Объявление функции сохранение паросочетания 
void saveMatching(char* matching);

// Объявление функции, которая определяет тип графа 
bool isDirected(bool** graph, int verticesFile);

// Объявление функции, которая доопределяет тип графа 
bool isUndirected(bool** graph, int vertices);

char printedMatchings[1000][50]; // Массив строк для хранения паросочетаний (до 1000 строк по 50 символов)

// Основная функция 
int main()
{
    srand(time(NULL)); // Подключаем случайные числа 
    setlocale(LC_ALL, "RUS"); // Подключение русского языка 

    // Вывод титульника 
    printf("Пензенский государственный университет\n");
    printf("Кафедра \"Вычислительная техника\"\n");
    printf("Курсовая работа\n");
    printf("По курсу \"Логика и основы алгоритмизации в инженерных задачах\"\n");
    printf("На тему \"Реализация алгоритма поиска наибольшего паросочетания\"\n");
    printf("Приняли: Юрова О.В. и Акифьев И.В.\n");
    printf("Выполнил: Байков Алексей Владимирович, учебная группа 22ВВВ3(22ВВП2)\n\n");
    //

    int vertices; // Размер графа по количеству вершин при работе со случайным графом 
    bool work = true; // Переменная для цикла 
    while (work)
    {   // Меню
        printf("Меню: \n");
        printf("1) Работа со случайным графом.\n");
        printf("2) Работа с вашим графом из файла.\n");
        printf("3) Завершение работы.\n\n");
        printf("Чтобы выбрать нужный пункт введите его номер.\n\n");
        printf("Ваш выбор: ");
        // 

        // Выбор пользователем режима 
        int typeMode;
        scanf("%d", &typeMode);

        // Цикл устранения некорректного ввода пользователем 
        while (typeMode != 1 && typeMode != 2 && typeMode != 3)
        {   // Вывод предупреждения    
            printf("\nОшибка! Введите номер соответсвуюгено пункта: ");
            while (getchar() != '\n'); // Устранение зацикливания 
            scanf("%d", &typeMode); // Повторный ввод
        }
        // Если пользователь выбрал работу со случайным графом 
        if (typeMode == 1)
        {
            // Цикл устранения некорректного ввода пользователем 
            bool num = false; // Переменная для работы цикла
            while (!num)
            {
                // Ввод вершин графа
                printf("\nВведите количество вершин в графе: ");
                if (scanf("%d", &vertices) == 1 && vertices > 0 && vertices <= 1000)  // Если введено число, которое больше 0
                {
                    num = true; // Выход из цикла
                }
                else // Иначе продолжаем обработку
                {   // Вывод предупреждения    
                    printf("\nОшибка! Размер матрицы должен задаваться числом, более 0 и менее 1000. Повторите попытку.\n");
                    while (getchar() != '\n'); // Устранение зацикливания 
                }
            }

            int graphType; // Тип графа 
            printf("\nВыберите тип графа:\n");
            printf("1) Ориентированный граф\n");
            printf("2) Неориентированный граф\n");

            // Ввод пользователем типа графа 
            printf("Ваш выбор: ");
            scanf("%d", &graphType);

            // Цикл устранения некорректного ввода пользователем 
            while (graphType != 1 && graphType != 2)
            {   // Вывод предупреждения    
                printf("\nОшибка! Введите 1 или 2 для дальнейшей работы программы: ");
                while (getchar() != '\n'); // Устранение зацикливания 
                scanf("%d", &graphType); // Повторный ввод
            }

            bool** graph = (bool**)malloc(vertices * sizeof(bool*));

            memoryAllocation(graph, vertices); // Вызов функции, которая выделяет память под матрицу смежности 

            generateRandomGraph(graph, vertices, graphType); // Вызов функции, отвечающую за генерацию матриц смежности 

            printGraph(graph, vertices); // Вызов функции, отвечающую за генерацию матриц смежности 

            // Вывод наибольшего паросочетания, Вызов функции, отвечающую за нахождение наибольшего паросочетания 
            printf("\nПаросочетания и наибольшее:\n");
            printAllMatchings(graph, vertices); // Вызов функции, отвечающую за вывод паросочетаний
            printf("\n");

            // Освобождение выделенной памяти, выделенной для матрицы смежности 
            for (int i = 0; i < vertices; i++)
            {
                free(graph[i]);
            }
            free(graph);
        } // Если пользователь выбрал работу со своим графом 
        else if (typeMode == 2)
        {
            // Пример как выглядят матрицы графов 
            printf("\n");
            printf("Пример как выглядят матрицы: \n");
            printf("Матрица неориентированного графа: \tМатрица ориентированного графа: \n");
            printf("\t    0 0 0 1\t\t\t\t   0 1 0 0\n\t    0 0 1 1\t\t\t\t   0 0 1 0\n\t    0 1 0 0\t\t\t\t   1 0 0 0\n\t    ");
            printf("1 1 0 0\t\t\t\t   0 0 1 0\n");

            int countAll = 0; // Переменная для подсчета вершин с мусором 
            int verticesFile = 0; // Переменная для подсчета вершин без мусора 
            char fileName[50]; // Для имени файла 
            FILE* fp;

            // Ввод имени файла
            printf("\nВведите имя файла, содержащего матрицу графа: ");
            scanf("%s", &fileName);

            // Проверка на наличие файла в цикле 
            fp = fopen(fileName, "r");
            while (fp == NULL)
            {
                printf("\nОшибка: Файл не найден!\n");
                printf("\nВведите имя файла, содержащего матрицу графа: ");
                while (getchar() != '\n'); // Устранение зацикливания 
                scanf("%s", &fileName);
                fp = fopen(fileName, "r");
            }
            fclose(fp);

            // Проверка на пустоту файла
            fp = fopen(fileName, "r");
            fseek(fp, 0, SEEK_END);
            if (ftell(fp) == 0)
            {
                printf("\nФайл пуст.\n\nПопробуйте заполнить его и повторите попытку.\n\nУдачи ;)\n");
                return 1;
            }
            fclose(fp);

            char c; // Переменная для подсчета вершин 
            // Определяем количество вершин 
            fp = fopen(fileName, "r");
            while ((c = fgetc(fp)) != '\n' && c != EOF) // Пока не дошли до перехода на новую строку и до конца файла 
            {  // Если есть пробел 
                if (c == ' ')
                {
                    countAll++; // Увеличиваем счетчик вершин с мусором 
                    continue; // Пропускаем итерацию 
                }
                verticesFile++; // Увеличиваем счетчик вершин без мусора 
            }
            fclose(fp);

            bool** graph = (bool**)malloc(verticesFile * sizeof(bool*));

            memoryAllocation(graph, verticesFile); // Вызов функции, которая выделяет память под матрицу смежности 
            printf("\n");

            int num; // Переменная фильтрации пробела 
            // Заполняем матрицу введенную из файла 
            fp = fopen(fileName, "r");
            // Считываем матрицу из файла
            for (int i = 0; i < countAll + 1; i++)
            {
                for (int j = 0; j < countAll + 1; j++)
                {
                    fscanf(fp, "%d", &num);
                    if (num == ' ')  // Если пришел пробел
                    {
                        continue;  // Пропускаем итерацию 
                    }
                    else
                    {
                        graph[i][j] = num; // Иначе добавляем в массив 
                    }
                }
            }
            fclose(fp);

            if (isDirected(graph, verticesFile)) // Если матрица соответсвует орграфу 
            {
                printf("Матрица орграфа: \n");
            }
            else if (isUndirected(graph, verticesFile)) // Если матрица соответсвует графу 
            {
                printf("Матрица графа: \n");
            }
            else // Иначе вывод сообщения 
            {
                printf("Ваша матрица не соотвествует графам.\n\nПеределайте матрицу и запустите праграмму снова.\n\nУдачи в следующих запусках ;)\n");
                break; // Конец работы 
            }
            printGraph(graph, verticesFile); // Вывод графа 

            // Вывод наибольшего паросочетания, Вызов функции, отвечающую за нахождение наибольшего паросочетания 
            printf("\nПаросочетания и наибольшее:\n");
            printAllMatchings(graph, verticesFile); // Вызов функции, отвечающую за вывод паросочетаний
            printf("\n");

            // Освобождение выделенной памяти, выделенной для матрицы смежности 
            for (int i = 0; i < verticesFile; i++)
            {
                free(graph[i]);
            }
            free(graph);
        }
        else
        {
            work = false;
        }
    }
    return 0; // Завершение работы 
}

// Функция отвечающая за обход графа 
bool bpm(bool** graph, int u, bool visited[], int matchR[], int vertices)
{
    for (int v = 0; v < vertices; v++)
    {
        // Если есть ребро между сравниваемыми вершинами и была ли вершина v посещена ранее.
        if (graph[u][v] && !visited[v])
        {
            visited[v] = true; // Отмечаем посещенной 
            // Если вершина не имеет пару или можно найти другую пару 
            if (matchR[v] < 0 || bpm(graph, matchR[v], visited, matchR, vertices))
            {
                matchR[v] = u; // Устанавливаем пару 
                return true;
            }
        }
    }
    return false; // Если не удалось найти путь 
}

// Функция, отвечающая за вывод паросочетания 
void printMatching(bool** graph, int matchR[], int vertices)
{
    bool* visited = (bool*)calloc(vertices, sizeof(bool)); // Выделяем память под массив посещенных вершин и заполняем 0

    for (int i = 0; i < vertices; i++)
    {
        if (matchR[i] != -1 && !visited[i]) // Если у вершины i есть пара, и вершина i не была посещена
        {
            printf("(%d, %d) ", matchR[i], i); // Выводим пару
            visited[i] = true; // Помечаем вершину посещенной 
            visited[matchR[i]] = true;
        }
    }
    printf("\n");

    free(visited); // Освобождаем память 
}

// Функция, отвечающие за поиск всех паросочетаний 
void printAllMatchingsUtil(bool** graph, int u, bool visited[], int matchR[], int vertices)
{
    for (int v = 0; v < vertices; v++)
    {
        // Если есть ребро между текущей вершиной u и вершиной v  и не посещалась ли вершина v ранее 
        if (graph[u][v] && !visited[v])
        {
            visited[v] = true; // Отмечаем посещенной 
            // Если есть у вершины v пара или у этой пары другая свободная вершина
            if (matchR[v] < 0 || !visited[matchR[v]])
            {
                matchR[v] = u; // Создаем паросочетание 

                char matchingString[50] = ""; // Представление паросочетания как строки
                sprintf(matchingString, "(%d, %d)", matchR[u], u);

                // Проверяем была ли уже выведена эта пара 
                if (!isMatchingPrinted(matchingString))
                {
                    // Если она новая, то
                    printMatching(graph, matchR, vertices); // Выводим паросочетание
                    saveMatching(matchingString); // Сохраняем выведенное паросочетание
                }
            }
        }
    }
    visited[u] = false; // Отмечаем вершину не посещенной 
}

// Функция, отвечающая за вывод всех паросочетания 
void printAllMatchings(bool** graph, int vertices)
{
    int* matchR = (int*)malloc(vertices * sizeof(int)); // Выделение памяти под массив пар
    // Если была ошибка при выделение памяти 
    if (matchR == NULL)
    {
        printf("Ошибка выделения памяти.\n");
        return;
    }

    for (int i = 0; i < vertices; i++)
    {
        matchR[i] = -1; // Указываем, что никак паросочетаний еще не было
    }

    bool* visited = (bool*)malloc(vertices * sizeof(bool)); // Выделение памяти под массив текущих посещенных вершин 
    // Проверяем на ошибку при выделение памяти 
    if (visited == NULL)
    {
        printf("Ошибка выделения памяти.\n");
        free(matchR); // Освобождение памяти 
        return;
    }

    for (int i = 0; i < vertices; i++)
    {
        visited[i] = false; // Отмечаем, что все вершины не посещенные 
    }

    for (int u = 0; u < vertices; u++)
    {
        printAllMatchingsUtil(graph, u, visited, matchR, vertices); // Для каждой вершины находим пару через другие вершины
    }

    free(matchR); // Освобождение памяти 
    free(visited); // Освобождение памяти 
}

// Функция, отвечающая за генерацию матриц 
void generateRandomGraph(bool** graph, int vertices, int graphType)
{
    // Если пользователь выбрал работу с орграфом
    if (graphType == 1)
    {
        printf("\nМатрица смежности ориентированного графа:\n");

        for (int i = 0; i < vertices; i++)
        {
            for (int j = 0; j < vertices; j++)
            {
                if (i == j) {
                    graph[i][j] = 0; // Нет петель
                }
                else {
                    int randomValue = rand() % 5;
                    if (randomValue == 0)
                    {
                        graph[i][j] = 1; // Устанавливаем ребро от i к j
                    }
                    else {
                        graph[i][j] = 0;
                    }
                }
            }
        }
    } // Если пользователь выбрал работу с графом
    else
    {
        printf("\nМатрица смежности графа:\n");
        // Заполнение матрицы смежности случайными числами 
        for (int i = 0; i < vertices; i++)
        {
            for (int j = i; j < vertices; j++)
            {
                // Устанавливаем на главной диагонали 0 
                if (i == j)
                {
                    graph[i][j] = 0;
                }
                else
                {
                    int randomValue = rand() % 2;
                    graph[i][j] = randomValue;
                    graph[j][i] = randomValue; // Матрица симметрична
                }
            }
        }
    }
}

// Функция, отвечающая за выделение памяти 
int memoryAllocation(bool** graph, int vertices)
{
    // Выделение памяти под матрицу смежности с проверкой 
    if (graph == NULL)
    { // Если произошла ошибка при выделение памяти, завершить работу
        printf("Ошибка выделения памяти.\n");
        return 0;
    }
    // Выделение памяти под матрицу смежности с проверкой 
    for (int i = 0; i < vertices; i++)
    {
        graph[i] = (bool*)malloc(vertices * sizeof(bool));
        if (graph[i] == NULL)
        { // Если произошла ошибка при выделение памяти, завершить работу, освободить память
            printf("Ошибка выделения памяти.\n");
            for (int j = 0; j < i; j++)
            {
                free(graph[j]);
            }
            free(graph);
            return 0;
        }
    }
}

// Функция выводящая матрицу смежности 
void printGraph(bool** graph, int vertices)
{
    // Проход по всей матрице
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            printf("%d ", graph[i][j]); // Вывод каждого ребра
        }
        printf("\n");
    }
}
// Вывод паросочетания, если оно уникальное 
bool isMatchingPrinted(char* matching)
{
    for (int i = 0; i < 1000; ++i)
    {
        if (strcmp(printedMatchings[i], matching) == 0)
        {
            return true;
        }
    }
    return false;
}

// Функция сохранение паросочетания 
void saveMatching(char* matching)
{
    for (int i = 0; i < 1000; ++i)
    {
        if (strlen(printedMatchings[i]) == 0)
        {
            strcpy(printedMatchings[i], matching);
            break;
        }
    }
}

// Функция, отвечающая для определение типа графа 
bool isDirected(bool** graph, int vertices)
{
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            if (graph[i][j] && !graph[j][i])
            {
                return true; // Найдено ребро в одну сторону и отсутствие обратного, граф ориентированный
            }
        }
    }
    return false; // Нет прямых отличий, граф неориентированный
}

// Функция, отвечающая за определение ошибочной матрицы 
bool isUndirected(bool** graph, int vertices)
{
    for (int i = 0; i < vertices; i++)
    {
        // Если на главной диоганали есть 1
        if (graph[i][i] != 0)
        {
            return false; // Отмечаем, что граф ореинтированный 
        }
        for (int j = i; j < vertices; j++)
        {
            if (graph[i][j] != graph[j][i])
            {
                return false; // Найдено противоречие в противоположных направлениях, граф неориентированный
            }
        }
    }
    return true; // Нет прямых отличий в противоположных направлениях, граф ориентированный
}