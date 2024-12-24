// Taleed Hamadneh || #1220006 || Section 3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define infinity 2147483647 // largest integer
struct queue *rear = NULL;  // to know the last element in the Q
char deQword[20];           // this array is used for deQ and return function, to avoid returning local variable, and can make free memory (return word..free temp xxx)
char deletedheap[15];       // to store the word in the min heap when deleting
int isReadcourses = 0;
int isReadBuildings = 0;
int isSorted = 0;

struct graph
{
    char vertname[12];
    int distance;
    struct graph *nextgraph;
    int indegree;
};
typedef struct graph *List;

struct queue
{
    struct queue *next;
    char word[20];
};

struct heap
{
    char word[15];
    int cost;
};

struct table
{
    int *cost;
    int *visited; // if 0 not visited, 1 visited
    int size;
    char *from[15];
    char *to[15];
};

// Dijkstra
void Rfile_building(struct graph *g[25]);                                                             // 8 buildings
void insert_dst(struct graph *g[25], char src[15], char dst[15], int distance);                       // to add the dst building to the src in the list with specific distance (between them)
void Dijkstra(struct graph *g[25], char src[15], char dst[15], struct table *T, struct heap *H[100]); // main function
void printpath(char src[15], char dst[15], int index, struct table *T);                               // print the shortest path

// Table
struct table *CreateTable(int size);                                // malloc .....
void MakeTEmpty(struct table *T, struct graph *G[25]);              // move the nodes from the graph to the table with initial cost infinity
void Update(struct table *T, char from[15], char to[15], int cost); // if the new cost is less than the actual one, change it, and change the previous building(for path)
void DisposeTable(struct table *T);                                 // free all the table
int findinTable(struct table *T, char word[15]);                    // return the index of the needed word

// heap
struct heap *MakeHEmpty(struct heap *H);                              // malloc...
void createheap(struct heap *H[100]);                                 // initial values
void insert_heap(struct heap *H[100], int cost, char word[15]);       // insert building and its cost to the heap
int delete_heap(struct heap *H[100]);                                 // delete the node from the heap and store the cost and the word(in the global)
void recursive_insert(struct heap *H[100], int index, char word[15]); // needed for insertion
int numofcosts(struct heap *h[100]);                                  // num of nodes in the heap
void heapify(struct heap *H[100], int index, char word[15]);          // arrange the heap
void DisposeHeap(struct heap *[100]);                                 // delete the whole heap

// Topological sort
void Rfile_courses(struct graph *G[25]);                                    // 12 course
struct graph *MakeGEmpty(struct graph *G);                                  /// create course list
struct graph *FindNode(struct graph *G[25], char name[12]);                 // find course in the list
int Findnodeindex(struct graph *G[25], char name[12]);                      // return the index of specific course
int NumOfverticies(struct graph *G[25]);                                    // number of courses in the list (# of verticies)
struct graph *lastnode(struct graph *G);                                    // return the last node in the graph for the insertion
void Insertvertix(struct graph *G[25], char name[12]);                      // insert course with specific name fromm the file to the graph && insert buildings
void insertprereq(struct graph *G[25], char course[12], char prereq[12]);   // used for reading from the file
void Insertnode(char name[12], struct graph *List, struct graph *position); // used for the sorted list to add the vertices in it
int numofnodes(List L);                                                     // num of nodes in specific list (used for sorting (cycle))
void Print(List L);                                                         // to print the sorted list
void DisposeGraph(struct graph *G[25]);                                     // delete the graph
struct graph *topological_sort(struct graph *G[25]);

// Queue
int IsEmptyQ(struct queue *q);
struct queue *createQueue();
void Enqueue(char x[50], struct queue *q);
void MakeQEmpty(struct queue *q); // empty the Q without head
void DisposeQ(struct queue *q);   // delete the Q with the head
void Dequeue(struct queue *q);
char *deQandReturn(struct queue *q);

// main
void menu();

int main()
{
    struct graph *courses[25];

    struct graph *sorted = NULL;

    struct graph *buildings[25];

    char src[15];
    char dst[15];
    struct heap *h[100];
    createheap(h);
    struct table *t = NULL;

    menu();
    int k = 0;
    scanf("%d", &k);
    while (k != 6)
    {
        if (k > 0 && k < 7)
        {
            switch (k)
            {
            case 1:
                if (isReadcourses == 1 && isReadBuildings == 1) // check if the file was read
                {
                    printf("You have already loaded the files\n\n");
                }
                else
                {
                    Rfile_building(buildings);
                    Rfile_courses(courses);
                    printf("Files Have been read Successfully\n\n");
                }
                break;
            case 2:
                if (isReadBuildings == 0)
                {
                    printf("Buildings File is not uploaded !! please load it first\n\n");
                }

                else
                {
                    printf("Please enter the first building\n");
                    scanf("%s", &src);
                    if (Findnodeindex(buildings, src) == -1)
                    {
                        printf("This building does not exist\n\n");
                    }
                    else
                    {
                        printf("Please enter the second building\n");
                        scanf("%s", &dst);
                        if (Findnodeindex(buildings, dst) == -1)
                        {
                            printf("This building does not exist\n\n");
                        }

                        else
                        {
                            t = CreateTable(NumOfverticies(buildings));
                            MakeTEmpty(t, buildings);
                            Dijkstra(buildings, src, dst, t, h);
                        }
                    }
                }
                break;

            case 3:
                if (isReadBuildings == 0)
                {
                    printf("Buildings File is not uploaded !! please load it first\n\n");
                }

                else
                {

                    printf("Please enter the first building\n");
                    scanf("%s", &src);
                    if (Findnodeindex(buildings, src) == -1)
                    {
                        printf("This building does not exist\n\n");
                    }
                    else
                    {
                        printf("Please enter the second building\n");
                        scanf("%s", &dst);
                        if (Findnodeindex(buildings, dst) == -1)
                        {
                            printf("This building does not exist\n\n");
                        }

                        else
                        {
                            t = CreateTable(NumOfverticies(buildings));
                            MakeTEmpty(t, buildings);
                            Dijkstra(buildings, src, dst, t, h);
                            printpath(src, dst, findinTable(t, dst), t);
                        }
                    }
                }
                break;

            case 4:
                if (isReadcourses == 0)
                {
                    printf("Courses file is not uploaded !! please load it first\n\n");
                }
                else if (isSorted == 1)
                {
                    printf("Courses have already been sorted!!\n\n");
                }

                else
                {
                    sorted = topological_sort(courses);
                    printf("Words have been sorted successfully\n\n");
                }
                break;

            case 5:
                if (isReadcourses == 0)
                {
                    printf("courses File is not uploaded !! please load it first\n\n");
                }
                else if (isSorted == 0)
                {
                    printf("Courses are not sorted!! please sort them first\n\n");
                }
                else
                {
                    printf("The sorted courses:\n");
                    Print(sorted);
                    printf("\n");
                }
                break;

            default:
                break;
            }
            menu();
            scanf("%d", &k);
        }

        else
        {
            printf("!!! Please enter number between 1 and 6 !!!\n\n");
            menu();
            scanf("%d", &k);
        }
    }
    printf("Bye Bye");

    DisposeTable(t); // Free all allocated memories
    DisposeHeap(h);
    DisposeGraph(courses);
    DisposeGraph(buildings);
}
////////////////////////////////////////// Buildings /////////////////////////////////////////////////////////////

void Rfile_building(struct graph *g[25])
{

    char test[50] = {0};
    char src_building[15] = {0};
    char dst_building[15] = {0};
    char distance[5] = {0};

    for (int i = 0; i < 25; i++) // creating the array
    {
        g[i] = MakeGEmpty(g[i]);
    }

    for (int i = 0; i < 25; i++) // initial names for the courses
    {
        strcpy(g[i]->vertname, "");
    }

    for (int i = 0; i < 25; i++) // distance from the building to itself=0
    {
        g[i]->distance = 0;
    }

    FILE *input;
    input = fopen("input_buildings.txt", "r");
    if (input == NULL)
    {
        printf(" Sorry... Can't open this file :( \n ");
        fclose(input);
        return;
    }

    while (fgets(test, sizeof(test), input) != NULL)
    {

        test[strlen(test) - 1] = '\0'; // remove the \n

        char *token = strtok(test, "#");
        if (token != NULL)
        {
            strcpy(src_building, token);

            token = strtok(NULL, "#");

            if (token != NULL)
            {
                strcpy(dst_building, token);
                token = strtok(NULL, "#");
                if (token != NULL)
                {
                    strcpy(distance, token);
                }
            }
        }
        if (FindNode(g, src_building) == NULL) // if the building is not exist, add it
        {
            Insertvertix(g, src_building);
        }
        insert_dst(g, src_building, dst_building, atoi(distance)); // convert the distance to integer //add the src building to the graph
    }
    isReadBuildings = 1;

    fclose(input);
}

void insert_dst(struct graph *g[25], char src[15], char dst[15], int distance)
{
    struct graph *temp = (struct graph *)malloc(sizeof(struct graph));

    int index = Findnodeindex(g, src);

    struct graph *p = lastnode(g[index]);

    if (p != NULL) // there is last node
    {

        if (temp != NULL)
        {
            strcpy(temp->vertname, dst);
            temp->distance = distance;
            p->nextgraph = temp;
            temp->nextgraph = NULL;
        }
        else
        {
            printf("Out of space :(\n\n");
        }
    }
    else // the first node
    {
        if (temp != NULL)

        {

            strcpy(temp->vertname, dst);
            g[index]->nextgraph = temp;
            temp->distance = distance;
            temp->nextgraph = NULL;
        }

        else
        {
            printf("Out of space :(\n\n");
        }
    }
}

void Dijkstra(struct graph *g[25], char src[15], char dst[15], struct table *T, struct heap *H[100])
{
    List source = FindNode(g, src);
    insert_heap(H, source->distance, source->vertname); // insert the source node to the heap
    for (int i = 0; i < T->size; i++)
    {
        if (strcmp(src, T->to[i]) == 0)
        {
            T->cost[i] = 0; // make the src cost = 0
        }
    }
    int destination = findinTable(T, dst);
    while (numofcosts(H) > 0) //! isempty
    {
        int deletedcost = delete_heap(H);  //& deletedheap global word for H[1]
        List p = FindNode(g, deletedheap); // search in the graph for the deleted word
        int index = findinTable(T, deletedheap);
        if (T->visited[index] == 0) // check if the node is discovered or not
        {
            List temp = p->nextgraph; // if not, go to its edges
            while (temp != NULL)
            {
                Update(T, deletedheap, temp->vertname, temp->distance + deletedcost); // update the cost if needed, and insert it to the heap
                insert_heap(H, temp->distance + deletedcost, temp->vertname);
                temp = temp->nextgraph;
            }
            T->visited[index] = 1; // make it visited
        }
    }
    if (T->cost[destination] > 0)
    {
        printf("\nThe shortest distance between %s and %s =%d\n\n", src, dst, T->cost[destination]);
    }
    else
    {
        printf("Distance can't be negative\n\n");
    }
}

void printpath(char src[15], char dst[15], int index, struct table *T)
{
    char test[15][15];    // array of string
    int varindex = index; // this index prefer to each previous (variable)
    int row = 0;
    strcpy(test[row], T->to[index]); // add the destination to the first row

    while (strcmp(T->to[varindex], src) != 0) // stop when reaching the src, prev->prev->prev---->src
    {
        row++;
        char previous[50];
        strcpy(previous, T->from[varindex]); // store the previous of the dst
        strcpy(test[row], previous);         // move it to the 2D
        varindex = findinTable(T, previous); // update the index (to go to the previous)
    }

    printf("shortest path between %s and %s is:\n", src, dst);
    for (int i = row; i >= 0; i--) // print in reversed (the destination was stored first)
    {
        printf("%s", test[i]);
        if (i > 0)
        {
            printf("--->");
        }
    }
    printf("\n");
    printf("\n");
}

///////////////////////////////////////////////////////// Heap ///////////////////////////////////////////////////////////////////

void createheap(struct heap *H[100])
{
    for (int i = 0; i < 100; i++) // creating the array
    {
        H[i] = MakeHEmpty(H[i]);
    }

    for (int i = 1; i < 100; i++) // initial values
    {
        strcpy(H[i]->word, "");
    }

    for (int i = 1; i < 100; i++)
    {
        H[i]->cost = 0;
    }
}

struct heap *MakeHEmpty(struct heap *H)
{

    H = (struct heap *)malloc(sizeof(struct heap));
    if (H == NULL)
        printf("Out of memory");

    else
    {
        strcpy(H->word, "");
        H->cost = 0;
    }
    return H;
}

int numofcosts(struct heap *h[100])
{

    for (int i = 1; i < 100; i++)
    {
        if (h[i]->cost == 0 && strcmp(h[i]->word, "") == 0)
        {
            return i - 1;
        }
    }
    return 100;
}

void insert_heap(struct heap *H[100], int cost, char word[15])
{

    int index = numofcosts(H) + 1;

    H[index]->cost = cost;

    strcpy(H[index]->word, word);

    if (index > 0)
    {
        recursive_insert(H, index, word);
    }
}

void recursive_insert(struct heap *H[100], int index, char word[15])
{

    int temp;
    char test[15] = {0};
    if (index >= 0 && H[index / 2]->cost > H[index]->cost)
    {

        temp = H[index / 2]->cost;
        strcpy(test, H[index / 2]->word);

        H[index / 2]->cost = H[index]->cost;
        strcpy(H[index / 2]->word, H[index]->word);

        H[index]->cost = temp;
        strcpy(H[index]->word, test);

        recursive_insert(H, index / 2, H[index / 2]->word);
    }
}

void heapify(struct heap *H[100], int index, char word[15])
{

    int left = index * 2;
    int right = index * 2 + 1;
    int min = index;
    int size = numofcosts(H);

    if (left >= size || left < 0)
    {
        left = -1;
    }
    if (right >= size || right < 0)
    {
        right = -1;
    }

    if (left != -1 && H[left]->cost < H[index]->cost) // to know which one will be the root
    {
        min = left;
    }
    if (right != -1 && H[right]->cost < H[min]->cost)
    {
        min = right;
    }

    char test[15];
    if (min != index) // making the root = min
    {
        int temp = H[min]->cost;
        strcpy(test, H[min]->word);

        H[min]->cost = H[index]->cost;
        strcpy(H[min]->word, H[index]->word);

        H[index]->cost = temp;
        strcpy(H[index]->word, test);

        heapify(H, min, H[min]->word); // recursion
    }
}

int delete_heap(struct heap *H[100])
{
    int size = numofcosts(H);
    if (size == 0)
    {
        printf("Cant delete.. heap is empty\n");
        return -1;
    }

    int deleted = H[1]->cost;
    strcpy(deletedheap, H[1]->word); // store it in the global string

    H[1]->cost = H[size]->cost;
    strcpy(H[1]->word, H[size]->word);

    H[size]->cost = 0;
    strcpy(H[size]->word, "");

    heapify(H, 1, H[1]->word);
    return deleted;
}

void DisposeHeap(struct heap *H[100])
{
    for (int i = 0; i < numofcosts(H); i++)
    {
        free(H[i]->word);
    }

    free(H);
}

/////////////////////////////////////////////////////////// Table //////////////////////////////////////////////////////////

struct table *CreateTable(int size)
{
    struct table *Table = (struct table *)malloc(sizeof(struct table));
    if (Table == NULL)
    {
        printf("Out of memory\n");
        return NULL;
    }
    Table->size = size;

    Table->visited = (int *)malloc(sizeof(int) * size);
    if (Table->visited == NULL)
    {
        printf("Out of memory\n");
        return NULL;
    }

    Table->cost = (int *)malloc(sizeof(int) * size);
    if (Table->cost == NULL)
    {
        printf("Out of memory\n");
        return NULL;
    }

    for (int i = 0; i < size; i++)
    {
        Table->from[i] = (char *)(malloc(sizeof(char) * 15)); // assume the word only 15 char
        Table->to[i] = (char *)(malloc(sizeof(char) * 15));
        Table->cost[i] = 0; // initial value
        if (Table->from[i] == NULL || Table->to[i] == NULL)
        {
            printf("Out of space.\n");
            return NULL;
        }
    }

    for (int i = 0; i < size; i++)
    {
        strcpy(Table->from[i], "e"); // initialize
        strcpy(Table->to[i], "e");
    }

    return Table;
}

void MakeTEmpty(struct table *T, struct graph *G[25])
{

    int size = NumOfverticies(G);
    if (size > T->size)
    {
        printf("very small table !! \n\n");
        return;
    }

    for (int i = 0; i < size; i++)
    {
        strcpy(T->to[i], G[i]->vertname);
        T->cost[i] = infinity;
        T->visited[i] = 0;
    }
}

void Update(struct table *T, char from[15], char to[15], int cost)
{

    int index;
    for (int i = 0; i < T->size; i++)
    {
        if (strcmp(T->to[i], to) == 0)
        {
            index = i;
            break;
        }
    }

    if (cost < T->cost[index])
    {
        T->cost[index] = cost;
        strcpy(T->from[index], from); // store the previous building, needed for printing the path
    }
}

void DisposeTable(struct table *T)
{

    for (int i = 0; i < T->size; i++)
    {
        free(T->from[i]);
        free(T->to[i]);
    }

    free(T->cost);
    free(T->visited);
    free(T);
}

int findinTable(struct table *T, char word[15])
{

    for (int i = 0; i < T->size; i++)
    {
        if (strcmp(word, T->to[i]) == 0)
        {

            return i;
        }
    }
    return -1;
}

///////////////////////////////////////////////////// courses ///////////////////////////////////////////////////////////////

void Rfile_courses(struct graph *G[25])
{

    char test[50] = {0};
    char course[12] = {0};
    char prerequisite1[12] = {0};
    char prerequisite2[12] = {0};

    for (int i = 0; i < 25; i++) // creating the array
    {
        G[i] = MakeGEmpty(G[i]);
    }

    for (int i = 0; i < 25; i++) // initial names for the courses
    {
        strcpy(G[i]->vertname, "");
    }

    for (int i = 0; i < 25; i++) // initial names for the courses
    {
        G[i]->indegree = 0;
    }

    FILE *input;
    input = fopen("input_courses.txt", "r");
    if (input == NULL)
    {
        printf(" Sorry... Can't open this file :( \n ");
        fclose(input);
        return;
    }
    while (fgets(test, sizeof(test), input) != NULL)
    {
        test[strlen(test) - 1] = '\0'; // remove the \n

        char *token = strtok(test, "#");
        if (token != NULL)
        {
            strcpy(course, token);

            token = strtok(NULL, "#");

            if (token != NULL)
            {
                strcpy(prerequisite1, token);
                token = strtok(NULL, "#");
                if (token != NULL)
                {
                    strcpy(prerequisite2, token);
                }
            }
        }

        Insertvertix(G, course);

        if (strcmp(prerequisite1, "\0") != 0)
        {
            insertprereq(G, prerequisite1, course);
            G[Findnodeindex(G, course)]->indegree++; // if there is only one pre, indegree will be 1
        }
        if (strcmp(prerequisite2, "\0") != 0)
        {
            insertprereq(G, prerequisite2, course);
            G[Findnodeindex(G, course)]->indegree++; // if there is 2 pre, indegree =2
        }
    }
    isReadcourses = 1;
    fclose(input);
}

struct graph *MakeGEmpty(struct graph *G) // creating course //creating building
{

    G = (struct graph *)malloc(sizeof(struct graph));
    if (G == NULL)
        printf("Out of memory");

    else
    {
        strcpy(G->vertname, "");
        G->nextgraph = NULL;
    }
    return G;
}

void Insertvertix(struct graph *G[25], char name[12]) // insert course with specific name from the file to the graph //insert building to the list
{

    int size = NumOfverticies(G);
    strcpy(G[size]->vertname, name);
    G[size]->nextgraph = NULL;
}

struct graph *FindNode(struct graph *G[25], char name[12])
{
    int s = NumOfverticies(G);
    for (int i = 0; i < s; i++)
    {
        if (strcmp(G[i]->vertname, name) == 0)
        {

            return G[i];
        }
    }
    return NULL;
}

int NumOfverticies(struct graph *G[25])
{
    for (int i = 0; i < 25; i++)
    {
        if (strcmp(G[i]->vertname, "\0") == 0)
        {
            return i;
        }
    }
    return 25;
}

int Findnodeindex(struct graph *G[25], char name[12])
{
    int s = NumOfverticies(G);
    for (int i = 0; i < s; i++)
    {
        if (strcmp(G[i]->vertname, name) == 0)
        {
            return i;
        }
    }
    return -1;
}
struct graph *lastnode(struct graph *G)
{
    struct graph *temp = G->nextgraph;
    if (temp != NULL)
    {
        while (temp->nextgraph != NULL)
        {
            temp = temp->nextgraph;
        }
    }

    return temp;
}

void insertprereq(struct graph *G[25], char course[12], char prereq[12])
{ // used for reading from the file
    struct graph *temp = (struct graph *)malloc(sizeof(struct graph));

    int index = Findnodeindex(G, course);
    struct graph *p = lastnode(G[index]);
    if (p != NULL)
    {

        if (temp != NULL)
        {
            strcpy(temp->vertname, prereq);
            p->nextgraph = temp;
            temp->nextgraph = NULL;
        }
        else
        {
            printf("Out of space :(\n\n");
        }
    }
    else
    {

        strcpy(temp->vertname, prereq);
        G[index]->nextgraph = temp;
        temp->nextgraph = NULL;
    }
}

void Print(List L)
{
    List temp = L->nextgraph;
    while (temp != NULL)
    {
        printf("%s\n", temp->vertname);
        temp = temp->nextgraph;
    }
}
void Insertnode(char name[12], struct graph *List, struct graph *position)
{
    // insert node to a list (linked list for sorting)
    struct graph *temp = (struct graph *)malloc(sizeof(struct graph));
    if (position != NULL)
    {
        if (temp != NULL)
        {
            strcpy(temp->vertname, name);
            temp->nextgraph = NULL;
            position->nextgraph = temp;
        }
    }
    else
    {
        if (temp != NULL)
        {
            strcpy(temp->vertname, name);
            temp->nextgraph = NULL;
            List->nextgraph = temp;
        }
    }
}

///////////////////////////////////////////////// Q ////////////////////////////////////////////////////////

int IsEmptyQ(struct queue *q)
{
    return q->next == NULL;
}

struct queue *createQueue()
{
    struct queue *q = NULL;
    q = (struct queue *)malloc(sizeof(struct queue));

    if (q == NULL)
    {
        printf("Out of Space..\n");
        return q;
    }
    else
    {
        q->next = NULL;
    }
    return q;
}

void Enqueue(char x[100], struct queue *q) // insert last only (Q)
{

    struct queue *temp;
    temp = (struct queue *)malloc(sizeof(struct queue));

    if (temp == NULL)
    {
        printf("Out of space\n\n");
        return;
    }
    else
    {
        strcpy(temp->word, x);
        temp->next = NULL;
        if (rear == NULL) // if there is no nodes (initial state)
        {
            q->next = temp;
            rear = temp; // make the rear pointing on the first node
        }

        else
        {
            rear->next = temp;
            rear = temp; // move rear in each insert operation
        }
    }
}

void Dequeue(struct queue *q) // delete first only
{
    struct queue *temp = NULL;
    temp = q->next;
    if (IsEmptyQ(q))
    {
        printf("Sorry the queue is empty..\n\n");
    }
    else
    {
        if (temp->next == NULL)
        { // if there was only one element, return the rear to null.
            q->next = NULL;
            free(temp);
            rear = NULL;
        }

        else
        {
            q->next = temp->next;
            free(temp);
        }
    }
}

void MakeQEmpty(struct queue *q)
{
    if (q == NULL)
    {
        printf("Out of Space :( \n\n");
    }
    else
    {
        while (!IsEmptyQ(q))
        {
            Dequeue(q);
        }
    }
}

char *deQandReturn(struct queue *q)
{ // deQ and return the word in the Q
    struct queue *temp;
    temp = q->next;
    if (IsEmptyQ(q))
    {
        printf("Sorry the queue is empty..\n\n");
    }
    else
    {

        if (temp->next == NULL)
        { // if there was only one element, return the rear to null.
            q->next = NULL;
            strcpy(deQword, temp->word);
            free(temp);
            rear = NULL;
        }

        else
        {

            q->next = temp->next;
            strcpy(deQword, temp->word);
            free(temp);
        }
        return deQword;
    }
}

void DisposeQ(struct queue *q)
{
    MakeQEmpty(q);
    free(q);
}
int numofnodes(List L)
{ // returns the number of nodes in a linked list(used for checking if there is cycle in the graph)
    int count = 0;
    List p = L->nextgraph;
    while (p != NULL)
    {
        count++;
        p = p->nextgraph;
    }
    return count;
}

struct graph *topological_sort(struct graph *G[12]) // 12 course
{
    List sortedlist = MakeGEmpty(sortedlist); // create the sorted list
    struct queue *Q = createQueue();

    if (G == NULL)
    {
        printf("Graph is not found :(\n\n");
        return NULL;
    }
    for (int i = 0; i < 12; i++)
    {
        if (G[i]->indegree == 0) // no prerequisite --> enQ
        {
            Enqueue(G[i]->vertname, Q);
        }
    }

    while (!IsEmptyQ(Q))
    {

        Insertnode(Q->next->word, sortedlist, lastnode(sortedlist)); // insert to the sorted list (from Q)
        List temp1 = FindNode(G, Q->next->word)->nextgraph;          // to the edges of the Q->head
        List temp2 = NULL;
        while (temp1 != NULL)
        {
            temp2 = FindNode(G, temp1->vertname); // search for the edge in the graph  (comp133->comp2421) the comp2421 we need to update is a head not an edge
            temp2->indegree--;                    // because we will remove the prerequisite of it
            if (temp2->indegree == 0)
            {
                Enqueue(temp2->vertname, Q);
            }
            temp1 = temp1->nextgraph;
        }
        Dequeue(Q);
    }

    if (NumOfverticies(G) != numofnodes(sortedlist)) // num of verticies vs num of sorted courses
    {
        printf("The graph has a cycle :(\n\n");
        return sortedlist;
    }
    isSorted = 1;
    DisposeQ(Q); // free memory
    return sortedlist;
}

void menu()
{
    printf("Please choose one \n");
    printf("1. Load the two files.\n");
    printf("2. Calculate the shortest distance between two buildings.\n");
    printf("3. Print the shortest route between two buildings and the total distance.\n");
    printf("4. Sort the courses using the topological sort.\n");
    printf("5. Print the sorted courses.\n");
    printf("6. Exit the application.\n");
}
void DisposeGraph(struct graph *G[25])
{
    int size = NumOfverticies(G);
    for (int i = 0; i < size; i++)
    {
        List p = NULL;
        p = G[i]->nextgraph;
        List temp = NULL;
        free(G[i]);

        while (p != NULL)
        {

            temp = p->nextgraph;
            p->nextgraph = NULL;
            free(p);
            p = temp;
        }
    }
}

