#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <locale.h>
#include <malloc.h>
#include <string.h>

// ���������� �������, ���������� �� ����� ����� � ������� 
bool bpm(bool** graph, int u, bool visited[], int matchR[], int vertices);

// ���������� �������, ���������� �� ����� ���� ������������� 
void printAllMatchings(bool** graph, int vertices);

// ���������� �������, ���������� ����� 
void printMatching(bool** graph, int matchR[], int vertices);

// �������, ���������� �� ����� ���� ������������� 
void printAllMatchingsUtil(bool** graph, int u, bool visited[], int matchR[], int vertices);

// ��������� ������ ��� ������� ���������
int memoryAllocation(bool** graph, int vertices);

// ���������� �������, ���������� �� ��������� ������ ����� � ������� 
void generateRandomGraph(bool** graph, int vertices, int graphType);

// ���������� �������, ���������� ����� ������� ��������� 
void printGraph(bool** graph, int vertices);

// ����� �������������, ���� ��� ���������� 
bool isMatchingPrinted(char* matching);

// ���������� ������� ���������� ������������� 
void saveMatching(char* matching);

// ���������� �������, ������� ���������� ��� ����� 
bool isDirected(bool** graph, int verticesFile);

// ���������� �������, ������� ������������ ��� ����� 
bool isUndirected(bool** graph, int vertices);

char printedMatchings[1000][50]; // ������ ����� ��� �������� ������������� (�� 1000 ����� �� 50 ��������)

// �������� ������� 
int main()
{
    srand(time(NULL)); // ���������� ��������� ����� 
    setlocale(LC_ALL, "RUS"); // ����������� �������� ����� 

    // ����� ���������� 
    printf("���������� ��������������� �����������\n");
    printf("������� \"�������������� �������\"\n");
    printf("�������� ������\n");
    printf("�� ����� \"������ � ������ �������������� � ���������� �������\"\n");
    printf("�� ���� \"���������� ��������� ������ ����������� �������������\"\n");
    printf("�������: ����� �.�. � ������� �.�.\n");
    printf("��������: ������ ������� ������������, ������� ������ 22���3(22���2)\n\n");
    //

    int vertices; // ������ ����� �� ���������� ������ ��� ������ �� ��������� ������ 
    bool work = true; // ���������� ��� ����� 
    while (work)
    {   // ����
        printf("����: \n");
        printf("1) ������ �� ��������� ������.\n");
        printf("2) ������ � ����� ������ �� �����.\n");
        printf("3) ���������� ������.\n\n");
        printf("����� ������� ������ ����� ������� ��� �����.\n\n");
        printf("��� �����: ");
        // 

        // ����� ������������� ������ 
        int typeMode;
        scanf("%d", &typeMode);

        // ���� ���������� ������������� ����� ������������� 
        while (typeMode != 1 && typeMode != 2 && typeMode != 3)
        {   // ����� ��������������    
            printf("\n������! ������� ����� ��������������� ������: ");
            while (getchar() != '\n'); // ���������� ������������ 
            scanf("%d", &typeMode); // ��������� ����
        }
        // ���� ������������ ������ ������ �� ��������� ������ 
        if (typeMode == 1)
        {
            // ���� ���������� ������������� ����� ������������� 
            bool num = false; // ���������� ��� ������ �����
            while (!num)
            {
                // ���� ������ �����
                printf("\n������� ���������� ������ � �����: ");
                if (scanf("%d", &vertices) == 1 && vertices > 0 && vertices <= 1000)  // ���� ������� �����, ������� ������ 0
                {
                    num = true; // ����� �� �����
                }
                else // ����� ���������� ���������
                {   // ����� ��������������    
                    printf("\n������! ������ ������� ������ ���������� ������, ����� 0 � ����� 1000. ��������� �������.\n");
                    while (getchar() != '\n'); // ���������� ������������ 
                }
            }

            int graphType; // ��� ����� 
            printf("\n�������� ��� �����:\n");
            printf("1) ��������������� ����\n");
            printf("2) ����������������� ����\n");

            // ���� ������������� ���� ����� 
            printf("��� �����: ");
            scanf("%d", &graphType);

            // ���� ���������� ������������� ����� ������������� 
            while (graphType != 1 && graphType != 2)
            {   // ����� ��������������    
                printf("\n������! ������� 1 ��� 2 ��� ���������� ������ ���������: ");
                while (getchar() != '\n'); // ���������� ������������ 
                scanf("%d", &graphType); // ��������� ����
            }

            bool** graph = (bool**)malloc(vertices * sizeof(bool*));

            memoryAllocation(graph, vertices); // ����� �������, ������� �������� ������ ��� ������� ��������� 

            generateRandomGraph(graph, vertices, graphType); // ����� �������, ���������� �� ��������� ������ ��������� 

            printGraph(graph, vertices); // ����� �������, ���������� �� ��������� ������ ��������� 

            // ����� ����������� �������������, ����� �������, ���������� �� ���������� ����������� ������������� 
            printf("\n������������� � ����������:\n");
            printAllMatchings(graph, vertices); // ����� �������, ���������� �� ����� �������������
            printf("\n");

            // ������������ ���������� ������, ���������� ��� ������� ��������� 
            for (int i = 0; i < vertices; i++)
            {
                free(graph[i]);
            }
            free(graph);
        } // ���� ������������ ������ ������ �� ����� ������ 
        else if (typeMode == 2)
        {
            // ������ ��� �������� ������� ������ 
            printf("\n");
            printf("������ ��� �������� �������: \n");
            printf("������� ������������������ �����: \t������� ���������������� �����: \n");
            printf("\t    0 0 0 1\t\t\t\t   0 1 0 0\n\t    0 0 1 1\t\t\t\t   0 0 1 0\n\t    0 1 0 0\t\t\t\t   1 0 0 0\n\t    ");
            printf("1 1 0 0\t\t\t\t   0 0 1 0\n");

            int countAll = 0; // ���������� ��� �������� ������ � ������� 
            int verticesFile = 0; // ���������� ��� �������� ������ ��� ������ 
            char fileName[50]; // ��� ����� ����� 
            FILE* fp;

            // ���� ����� �����
            printf("\n������� ��� �����, ����������� ������� �����: ");
            scanf("%s", &fileName);

            // �������� �� ������� ����� � ����� 
            fp = fopen(fileName, "r");
            while (fp == NULL)
            {
                printf("\n������: ���� �� ������!\n");
                printf("\n������� ��� �����, ����������� ������� �����: ");
                while (getchar() != '\n'); // ���������� ������������ 
                scanf("%s", &fileName);
                fp = fopen(fileName, "r");
            }
            fclose(fp);

            // �������� �� ������� �����
            fp = fopen(fileName, "r");
            fseek(fp, 0, SEEK_END);
            if (ftell(fp) == 0)
            {
                printf("\n���� ����.\n\n���������� ��������� ��� � ��������� �������.\n\n����� ;)\n");
                return 1;
            }
            fclose(fp);

            char c; // ���������� ��� �������� ������ 
            // ���������� ���������� ������ 
            fp = fopen(fileName, "r");
            while ((c = fgetc(fp)) != '\n' && c != EOF) // ���� �� ����� �� �������� �� ����� ������ � �� ����� ����� 
            {  // ���� ���� ������ 
                if (c == ' ')
                {
                    countAll++; // ����������� ������� ������ � ������� 
                    continue; // ���������� �������� 
                }
                verticesFile++; // ����������� ������� ������ ��� ������ 
            }
            fclose(fp);

            bool** graph = (bool**)malloc(verticesFile * sizeof(bool*));

            memoryAllocation(graph, verticesFile); // ����� �������, ������� �������� ������ ��� ������� ��������� 
            printf("\n");

            int num; // ���������� ���������� ������� 
            // ��������� ������� ��������� �� ����� 
            fp = fopen(fileName, "r");
            // ��������� ������� �� �����
            for (int i = 0; i < countAll + 1; i++)
            {
                for (int j = 0; j < countAll + 1; j++)
                {
                    fscanf(fp, "%d", &num);
                    if (num == ' ')  // ���� ������ ������
                    {
                        continue;  // ���������� �������� 
                    }
                    else
                    {
                        graph[i][j] = num; // ����� ��������� � ������ 
                    }
                }
            }
            fclose(fp);

            if (isDirected(graph, verticesFile)) // ���� ������� ������������ ������� 
            {
                printf("������� �������: \n");
            }
            else if (isUndirected(graph, verticesFile)) // ���� ������� ������������ ����� 
            {
                printf("������� �����: \n");
            }
            else // ����� ����� ��������� 
            {
                printf("���� ������� �� ������������ ������.\n\n����������� ������� � ��������� ��������� �����.\n\n����� � ��������� �������� ;)\n");
                break; // ����� ������ 
            }
            printGraph(graph, verticesFile); // ����� ����� 

            // ����� ����������� �������������, ����� �������, ���������� �� ���������� ����������� ������������� 
            printf("\n������������� � ����������:\n");
            printAllMatchings(graph, verticesFile); // ����� �������, ���������� �� ����� �������������
            printf("\n");

            // ������������ ���������� ������, ���������� ��� ������� ��������� 
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
    return 0; // ���������� ������ 
}

// ������� ���������� �� ����� ����� 
bool bpm(bool** graph, int u, bool visited[], int matchR[], int vertices)
{
    for (int v = 0; v < vertices; v++)
    {
        // ���� ���� ����� ����� ������������� ��������� � ���� �� ������� v �������� �����.
        if (graph[u][v] && !visited[v])
        {
            visited[v] = true; // �������� ���������� 
            // ���� ������� �� ����� ���� ��� ����� ����� ������ ���� 
            if (matchR[v] < 0 || bpm(graph, matchR[v], visited, matchR, vertices))
            {
                matchR[v] = u; // ������������� ���� 
                return true;
            }
        }
    }
    return false; // ���� �� ������� ����� ���� 
}

// �������, ���������� �� ����� ������������� 
void printMatching(bool** graph, int matchR[], int vertices)
{
    bool* visited = (bool*)calloc(vertices, sizeof(bool)); // �������� ������ ��� ������ ���������� ������ � ��������� 0

    for (int i = 0; i < vertices; i++)
    {
        if (matchR[i] != -1 && !visited[i]) // ���� � ������� i ���� ����, � ������� i �� ���� ��������
        {
            printf("(%d, %d) ", matchR[i], i); // ������� ����
            visited[i] = true; // �������� ������� ���������� 
            visited[matchR[i]] = true;
        }
    }
    printf("\n");

    free(visited); // ����������� ������ 
}

// �������, ���������� �� ����� ���� ������������� 
void printAllMatchingsUtil(bool** graph, int u, bool visited[], int matchR[], int vertices)
{
    for (int v = 0; v < vertices; v++)
    {
        // ���� ���� ����� ����� ������� �������� u � �������� v  � �� ���������� �� ������� v ����� 
        if (graph[u][v] && !visited[v])
        {
            visited[v] = true; // �������� ���������� 
            // ���� ���� � ������� v ���� ��� � ���� ���� ������ ��������� �������
            if (matchR[v] < 0 || !visited[matchR[v]])
            {
                matchR[v] = u; // ������� ������������� 

                char matchingString[50] = ""; // ������������� ������������� ��� ������
                sprintf(matchingString, "(%d, %d)", matchR[u], u);

                // ��������� ���� �� ��� �������� ��� ���� 
                if (!isMatchingPrinted(matchingString))
                {
                    // ���� ��� �����, ��
                    printMatching(graph, matchR, vertices); // ������� �������������
                    saveMatching(matchingString); // ��������� ���������� �������������
                }
            }
        }
    }
    visited[u] = false; // �������� ������� �� ���������� 
}

// �������, ���������� �� ����� ���� ������������� 
void printAllMatchings(bool** graph, int vertices)
{
    int* matchR = (int*)malloc(vertices * sizeof(int)); // ��������� ������ ��� ������ ���
    // ���� ���� ������ ��� ��������� ������ 
    if (matchR == NULL)
    {
        printf("������ ��������� ������.\n");
        return;
    }

    for (int i = 0; i < vertices; i++)
    {
        matchR[i] = -1; // ���������, ��� ����� ������������� ��� �� ����
    }

    bool* visited = (bool*)malloc(vertices * sizeof(bool)); // ��������� ������ ��� ������ ������� ���������� ������ 
    // ��������� �� ������ ��� ��������� ������ 
    if (visited == NULL)
    {
        printf("������ ��������� ������.\n");
        free(matchR); // ������������ ������ 
        return;
    }

    for (int i = 0; i < vertices; i++)
    {
        visited[i] = false; // ��������, ��� ��� ������� �� ���������� 
    }

    for (int u = 0; u < vertices; u++)
    {
        printAllMatchingsUtil(graph, u, visited, matchR, vertices); // ��� ������ ������� ������� ���� ����� ������ �������
    }

    free(matchR); // ������������ ������ 
    free(visited); // ������������ ������ 
}

// �������, ���������� �� ��������� ������ 
void generateRandomGraph(bool** graph, int vertices, int graphType)
{
    // ���� ������������ ������ ������ � ��������
    if (graphType == 1)
    {
        printf("\n������� ��������� ���������������� �����:\n");

        for (int i = 0; i < vertices; i++)
        {
            for (int j = 0; j < vertices; j++)
            {
                if (i == j) {
                    graph[i][j] = 0; // ��� ������
                }
                else {
                    int randomValue = rand() % 5;
                    if (randomValue == 0)
                    {
                        graph[i][j] = 1; // ������������� ����� �� i � j
                    }
                    else {
                        graph[i][j] = 0;
                    }
                }
            }
        }
    } // ���� ������������ ������ ������ � ������
    else
    {
        printf("\n������� ��������� �����:\n");
        // ���������� ������� ��������� ���������� ������� 
        for (int i = 0; i < vertices; i++)
        {
            for (int j = i; j < vertices; j++)
            {
                // ������������� �� ������� ��������� 0 
                if (i == j)
                {
                    graph[i][j] = 0;
                }
                else
                {
                    int randomValue = rand() % 2;
                    graph[i][j] = randomValue;
                    graph[j][i] = randomValue; // ������� �����������
                }
            }
        }
    }
}

// �������, ���������� �� ��������� ������ 
int memoryAllocation(bool** graph, int vertices)
{
    // ��������� ������ ��� ������� ��������� � ��������� 
    if (graph == NULL)
    { // ���� ��������� ������ ��� ��������� ������, ��������� ������
        printf("������ ��������� ������.\n");
        return 0;
    }
    // ��������� ������ ��� ������� ��������� � ��������� 
    for (int i = 0; i < vertices; i++)
    {
        graph[i] = (bool*)malloc(vertices * sizeof(bool));
        if (graph[i] == NULL)
        { // ���� ��������� ������ ��� ��������� ������, ��������� ������, ���������� ������
            printf("������ ��������� ������.\n");
            for (int j = 0; j < i; j++)
            {
                free(graph[j]);
            }
            free(graph);
            return 0;
        }
    }
}

// ������� ��������� ������� ��������� 
void printGraph(bool** graph, int vertices)
{
    // ������ �� ���� �������
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            printf("%d ", graph[i][j]); // ����� ������� �����
        }
        printf("\n");
    }
}
// ����� �������������, ���� ��� ���������� 
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

// ������� ���������� ������������� 
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

// �������, ���������� ��� ����������� ���� ����� 
bool isDirected(bool** graph, int vertices)
{
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            if (graph[i][j] && !graph[j][i])
            {
                return true; // ������� ����� � ���� ������� � ���������� ���������, ���� ���������������
            }
        }
    }
    return false; // ��� ������ �������, ���� �����������������
}

// �������, ���������� �� ����������� ��������� ������� 
bool isUndirected(bool** graph, int vertices)
{
    for (int i = 0; i < vertices; i++)
    {
        // ���� �� ������� ��������� ���� 1
        if (graph[i][i] != 0)
        {
            return false; // ��������, ��� ���� ��������������� 
        }
        for (int j = i; j < vertices; j++)
        {
            if (graph[i][j] != graph[j][i])
            {
                return false; // ������� ������������ � ��������������� ������������, ���� �����������������
            }
        }
    }
    return true; // ��� ������ ������� � ��������������� ������������, ���� ���������������
}