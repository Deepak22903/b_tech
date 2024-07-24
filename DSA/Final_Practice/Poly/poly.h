typedef struct node{
	int coef;
	int exponent;
	struct node* next;
}node;

typedef node* list;
void init(list *head);
void append(list *head, int c, int e);
void display(list *head);
void add(list *head, list *L1, list *L2);
void sub(list *head, list *L1, list *L2);
