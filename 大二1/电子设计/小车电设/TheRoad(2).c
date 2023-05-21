#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int map[6][6][4] = {0}; //0为无障碍物，0U，1D，3L，4R
int Road[6][6] = {0};   //0代表没走过，1代表走过，因为走过的说明之前更短就能到达，就不必继续了
int Value[6][6] = {0};
char operationTotal[30];
char FinalOP[30];
int ui = 0;
int u = 1;
typedef struct node
{
    struct node *last;
    char dir; //从上一节点到此节点的方向
    int x;
    int y;
    struct node *next;
} Node;
Node *NodeSon[4]; //0U,1D,2L,3R
typedef struct queue
{
    Node *front;
    Node *rear;
} Queue;

Queue *RoadFinder;
Node *hospital;

int getValue(int x, int y, int V)
{
    Value[x][y] = V;
}

void InitializeQueue(Queue *pq, Node *start)
{
    pq->front = start;
    pq->rear = start;
    pq->front->next = pq->rear;
}

void Roadzero()
{
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++)
            Road[i][j] = 0;
}

bool EnQueue(Node *pnew, Queue *pq)
{
    pnew->next = NULL;
    pq->rear->next = pnew;
    pq->rear = pnew;
    return true;
}

Node *DeQueue(Queue *pq)
{
    Node *pt;
    pt = pq->front;
    if (pq->front != pq->rear)
        pq->front = pq->front->next;
    return pt;
}

void EmptyQueue(Node *start)
{
    Node *node2;
    while (start->next != NULL)
    {
        node2 = start->next;
        if (start != hospital)
            free(start);
        start = node2;
    }
    free(RoadFinder);
}
void Emptymiddle(Node *start, Node *end)
{
    Node *node2 = start;
    node2 = node2->next;
    while (node2 != NULL)
    {
        start = node2;
        node2 = start->next;
        if (start != hospital)
            free(start);
    }
    free(RoadFinder);
}
Node **CNB(Node *temp) // Create Node Branch
{
    if (temp->x > 0 && map[temp->x][temp->y][0] == 0 && Road[(temp->x) - 1][temp->y] != 1) //向上能走且没走过
    {
        NodeSon[0] = (Node *)malloc(sizeof(Node));
        NodeSon[0]->last = temp;
        NodeSon[0]->dir = 'U';
        NodeSon[0]->x = (temp->x) - 1;
        NodeSon[0]->y = (temp->y);
        Road[temp->x - 1][temp->y] = 1;
    }
    else
    {
        NodeSon[0] = NULL;
    }

    if (temp->x < 5 && map[temp->x][temp->y][1] == 0 && Road[(temp->x) + 1][temp->y] != 1) //向下能走且没走过
    {
        NodeSon[1] = (Node *)malloc(sizeof(Node));
        NodeSon[1]->last = temp;
        NodeSon[1]->dir = 'D';
        NodeSon[1]->x = (temp->x) + 1;
        NodeSon[1]->y = (temp->y);
        Road[temp->x + 1][temp->y] = 1;
    }
    else
    {
        NodeSon[1] = NULL;
    }

    if (temp->y > 0 && map[temp->x][temp->y][2] == 0 && Road[temp->x][temp->y - 1] != 1) //向下能走且没走过
    {
        NodeSon[2] = (Node *)malloc(sizeof(Node));
        NodeSon[2]->last = temp;
        NodeSon[2]->dir = 'L';
        NodeSon[2]->x = temp->x;
        NodeSon[2]->y = temp->y - 1;
        Road[temp->x][temp->y - 1] = 1;
    }
    else
    {
        NodeSon[2] = NULL;
    }

    if (temp->y < 5 && map[temp->x][temp->y][3] == 0 && Road[temp->x][temp->y + 1] != 1) //向下能走且没走过
    {
        NodeSon[3] = (Node *)malloc(sizeof(Node));
        NodeSon[3]->last = temp;
        NodeSon[3]->dir = 'R';
        NodeSon[3]->x = temp->x;
        NodeSon[3]->y = temp->y + 1;
        Road[temp->x][temp->y + 1] = 1;
    }
    else
    {
        NodeSon[3] = NULL;
    }
    return NodeSon;
}

Node *Check(Node **next4mb, Node *end)
{
    int i;
    for (i = 0; i < 4; i++)
    {
        if (next4mb[i] == NULL)
            continue;
        else
        {
            if (next4mb[i]->x == end->x && next4mb[i]->y == end->y)
                break;
        }
    }
    if (i == 4)
        return NULL;
    else
        return next4mb[i];
}

int En4mbQueue(Node **next4mb, Queue *RoadFinder)
{
    for (int i = 0; i < 4; i++)
    {
        if (next4mb[i] != NULL)
            EnQueue(next4mb[i], RoadFinder);
    }
    return 1;
}
int PrintRoad(Node *EndInQueue, int Printb) //Printb is 1 the Print
{
    char operation[100];
    Node *nod1 = EndInQueue, *nod2;
    int i;
    for (i = 0; i < 100; i++)
    {
        nod2 = nod1->last;
        if (nod2 == NULL)
            break;
        if (Value[nod2->x][nod2->y] == 10 && Printb == 1)
            Value[nod2->x][nod2->y] = 0;
        operation[i] = nod1->dir;
        nod1 = nod2;
    }
    if (Printb == 1)
    {
        for (int m = i - 1; m >= 0; m--)
        {
            operationTotal[ui] = operation[m];
            ui++;
        }
    }
    return i; //共走了i步
}
int FindRoad(Node *start, Node *end)
{
    Roadzero();
    Node *temp; //FIFO出来的节点
    Node *EndInQueue = NULL;
    RoadFinder = (Queue *)malloc(sizeof(Queue));
    InitializeQueue(RoadFinder, start);
    RoadFinder->front = start;
    while (EndInQueue == NULL)
    {
        temp = DeQueue(RoadFinder);
        Node **next4mb = CNB(temp); //找到4个temp的下一部分节点
        EndInQueue = Check(next4mb, end);
        En4mbQueue(next4mb, RoadFinder);
    }
    if (PrintRoad(EndInQueue, 1))
        return 1;
    else
        return 0;
}
int CalDistance(Node *start, Node *end)
{
    Roadzero();
    RoadFinder = (Queue *)malloc(sizeof(Queue));
    Node *temp; //FIFO出来的节点
    Node *EndInQueue = NULL;

    InitializeQueue(RoadFinder, start);
    RoadFinder->front = start;
    while (EndInQueue == NULL)
    {
        temp = DeQueue(RoadFinder);
        Node **next4mb = CNB(temp); //找到4个temp的下一部分节点
        EndInQueue = Check(next4mb, end);
        En4mbQueue(next4mb, RoadFinder);
    }
    return PrintRoad(EndInQueue, 0);
}
Node *findtheclose(Node *start)
{

    int l = 0;
    int distance[10];
    Node *head = (Node *)malloc(sizeof(Node));
    Node *temp1 = head;
    Node *temp2;
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++)
        {
            if (Value[i][j] > 0 && Value[i][j] < 15)
            {
                temp1->x = i;
                temp1->y = j;
                if (Value[i][j] == 10)
                {
                    distance[l] = CalDistance(start, temp1);
                    Emptymiddle(start, temp1);
                }
                else
                {
                    distance[l] = CalDistance(start, temp1);
                    Emptymiddle(start, temp1);
                    temp1->last = NULL;
                    for (int m = 0; m < 6; m++)
                        for (int n = 0; n < 6; n++)
                            if (Value[m][n] == 25)
                            {
                                hospital->x = m;
                                hospital->y = n;
                            }
                    distance[l] += CalDistance(temp1, hospital);
                    distance[l] = distance[l] / 3;
                    Emptymiddle(start, temp1);
                }
                temp2 = temp1;
                temp1 = (Node *)malloc(sizeof(Node));
                temp2->next = temp1;
                l++;
            } //共有0-l-1个有用节点（实质上有0——l个）和hospital节点
        }
    int i;
    int j;
    for (i = 0; i < l; i++)
    {
        for (j = 0; j < l; j++)
        {
            if (distance[i] <= distance[j])
                continue;
            else
                break;
        }
        if (j == l)
            break;
    }
    Node *good = head;
    for (j = 0; j < i; j++)
    {
        good = good->next;
    }
    Node *temp = head;
    Node *ml;
    for (int m = 0; m < l + 1; m++)
    {
        ml = temp->next;
        if (m != i)
            free(temp);
        temp = ml;
    }
    return good;
}

Node *generateRoad(Node *start)
{
    start->last = NULL;
    Node *end = findtheclose(start);
    FindRoad(start, end);
    end->last = NULL;
    if (Value[end->x][end->y] == 5)
    {
        FindRoad(end, hospital);
        Value[hospital->x][hospital->y] = 0;
        Value[end->x][end->y] = 0;
        EmptyQueue(start);
        return hospital;
    }
    Value[end->x][end->y] = 0;
    EmptyQueue(start);
    return end;
}
void getmap()
{
    map[0][0][3] = 1;
    map[0][1][2] = 1;
    map[1][3][3] = 1;
    map[1][4][2] = 1;
    map[1][1][1] = 1;
    map[2][1][0] = 1;
    map[3][4][3] = 1;
    map[3][5][2] = 1;
    map[3][3][1] = 1;
    map[4][3][0] = 1;
    map[4][1][3] = 1;
    map[4][2][2] = 1;
    map[4][4][1] = 1;
    map[5][4][0] = 1;
    map[5][4][3] = 1;
    map[5][5][2] = 1;
    map[3][1][3] = 1;
    map[3][2][2] = 1;
}
void ValueSet()
{
    getValue(0, 2, 10); //到时候可能需要定时中断，定过程中断
    getValue(2, 4, 10);
    getValue(3, 0, 10);
    getValue(3, 4, 10);
    getValue(4, 5, 10);
    getValue(5, 2, 10);
    getValue(2, 2, 5);
    getValue(5, 0, 25);
}

void Roadtrans()
{
    FinalOP[0] = operationTotal[0];
    char reference = operationTotal[0];
    int l = 0;
    for (int i = 0; i < ui; i++)
    {
        if (operationTotal[i] == reference)
        {
            l++;
        }
        else
        {
            FinalOP[u] = 48 + l;
            u++;
            FinalOP[u] = operationTotal[i];
            reference = operationTotal[i];
            u++;
            l = 1;
        }
        if(i == ui-1)
        {
            FinalOP[u] = l + 48;
            u++;
        }
    }
}
int main()
{
    hospital = (Node *)malloc(sizeof(Node));
    getmap();
    ValueSet();
    Node *start;
    start = (Node *)malloc(sizeof(Node));
    scanf("%d%d", &start->x, &start->y);
    for (int i = 0; i < 3; i++)
        start = generateRoad(start);
    Roadtrans();
    free(start);
    free(hospital);
    for(int i = 0;i < u;i++)
        printf("%c",FinalOP[i]);
    system("pause");
}
//待添加，可能出现障碍物的死循环
