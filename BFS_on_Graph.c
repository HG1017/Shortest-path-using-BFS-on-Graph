#include<stdio.h>
#include<stdlib.h>
#define endl printf("\n")

int queue[100000]; // queue declared globally for the BFS algorithm
int head = -1, tail = -1;

struct node // structure for each node of the linked list
{
    int conn;
    struct node* next;
};

struct list
{
    struct node* one; // points to the starting of the list
};

struct graph // structure for the graph
{
    int vert; // no. of vertices
    struct list* arr;
};

struct node* addlist (int x) // creates a new node with entry x
{
    struct node* first;
    first = (struct node*)malloc(sizeof(struct node));

    first->conn = x;
    first->next = NULL;

    return first;
}

struct graph* generate_graph (int x) // generates a graph of appropriate size with entries initialized to null
{
    struct graph* g;
    g = (struct graph*)malloc(sizeof(struct graph));

    g->vert = x;

    g->arr = (struct list*)malloc(sizeof(struct list) * x);

    for (int i = 0; i < x; i++)
    {
        g->arr[i].one = NULL;
    }

    return g;
}

void create_undirected_edge (struct graph* g, int pt1, int pt2) // function for adding an edge to an undirected graph
{
    struct node* temp = addlist(pt2);

    temp->next = g->arr[pt1].one;
    g->arr[pt1].one = temp;

    temp = addlist(pt1);

    temp->next = g->arr[pt2].one;
    g->arr[pt2].one = temp;
}

void create_directed_edge (struct graph* g, int pt1, int pt2) // function for adding an edge to a directed graph
{
    struct node* temp = addlist(pt2);

    temp->next = g->arr[pt1].one;
    g->arr[pt1].one = temp;
}

void display_graph (struct graph* g) // function for displaying the graph
{
    for (int i = 0; i < g->vert; i++)
    {
        printf("Vertex %d: ", i);

        struct node* dup = g->arr[i].one;

        if(dup == NULL)
        {
            printf("No Edge present");
        }
        else
        {
            while(dup->next!= NULL)
            {
                printf("%d -> ", dup->conn);
                dup = dup->next;
            }
            printf("%d", dup->conn);
        }
        endl;
    }
}

void enqueue(int x) // enqueue function for the queue
{
    if (tail == -1)
    {
        head = tail = 0;
        queue[tail] = x;
    }
    else
    {
        tail = tail + 1;
        queue[tail] = x;
    }
}

int dequeue(void) // dequeue function for the queue
{
    int x;
    if (head == tail)
    {
        x = queue[head];
        head = tail = -1;
        return x;
    }
    else
    {
        x = queue[head];
        head++;
        return x;
    }
}

void BFS(struct graph* g, int s) // BFS algorithm based on the pseudocode given in the CLRS book
{
    int n = g->vert;

    char color[n]; // character array for storing the color for the vertices
    int d[n]; // array for storing the distance of the vertices from the source vertex
    int pi[n]; // array for storing the previous vertex in the path (for all vertices)

    for (int i = 0; i<n; i++)
    {
        if(i!=s)
        {
            color[i] = 'w'; // w stands for white color
            d[i] = 10000; // indicates not reachable vertex
            pi[i] = -10000; // indicates Nill
        }
    }
    color[s] = 'g'; // g stands for gray color
    d[s] = 0; // distance of a vertex from itself is 0
    pi[s] = -10000; // indicates Nill

    enqueue(s); // enqueue s in the queue
    int u;
    int v;
    while(tail!= -1) // loop continues to execute if the queue is not empty
    {
        u = dequeue();
        struct node* dup = g->arr[u].one;

        if(dup == NULL)
        {
            ;
        }
        else
        {
            while(dup!= NULL)
            {
                v = dup->conn;

                if (color[v] == 'w')
                {
                    color[v] = 'g';
                    d[v] = d[u] + 1;
                    pi[v] = u;
                    enqueue(v);
                }
                dup = dup->next;
            }
            color[u] = 'b'; // b stands for black color
        }
    }
    printf("BFS computed the following distances:");
    endl;
    for (int i = 0; i<n; i++)
    {
        if (d[i]== 10000)
        {
            printf("The distance of the vertex %d from the source vertex %d is: vertex is not reachable from the source vertex", i, s);
            endl;
        }
        else
        {
            printf("The distance of the vertex %d from the source vertex %d is: %d", i, s, d[i]);
            endl;
        }
    }


}
int main()
{
    int N;
    printf("Enter the number of vertices: ");
    scanf("%d", &N);

    printf("Your vertices are numbered from ");
    for (int i = 0; i<N-1; i++)
    {
        printf("%d, ",i);
    }
    printf("%d",N-1);
    endl;

    struct graph* G = generate_graph(N);

    int p,q,r;
    char c;
    again:
    printf("Enter D for directed or U for undirected graphs: ");
    scanf("%s", &c);
    if(c!='U' && c!='D')
    {
        printf("Invalid choice, try again...");
        endl;
        goto again;
    }
    else if(c == 'U')
    {
        printf("Enter edges (in format: a b), one by one of your Undirected graph. Once done, enter -1 -1 to quit:");
        endl;
        while(1)
        {
            scanf("%d %d", &p, &q);
            if(p == -1 || q == -1)
            {
                break;
            }
            else
            {
                create_undirected_edge (G,p,q);
            }
        }
        printf("Your undirected graph is as follows:");
        endl;
        display_graph(G);
        endl;
        printf("Enter a source vertex s from where you want to run the BFS algorithm on the graph you entered for problem 1a");
        endl;
        printf("Your options are ");
        for (int i = 0; i<N-1; i++)
            {
                printf("%d, ",i);
            }
        printf("%d: ",N-1);
        scanf("%d", &r);
        BFS(G,r);
    }
    else
    {
        printf("Enter edges (in format: a b), one by one of your Directed graph. Once done, enter -1 -1 to quit:");
        endl;
        while(1)
        {
            scanf("%d %d", &p, &q);
            if(p == -1 || q == -1)
            {
                break;
            }
            else
            {
                create_directed_edge (G,p,q);
            }
        }
        printf("Your directed graph is as follows:");
        endl;
        display_graph(G);
        endl;
        printf("Enter a source vertex s from where you want to run the BFS algorithm on the graph you entered for problem 1a");
        endl;
        printf("Your options are ");
        for (int i = 0; i<N-1; i++)
            {
                printf("%d, ",i);
            }
        printf("%d: ",N-1);
        scanf("%d", &r);
        BFS(G,r);
    }

    return 0;
}
