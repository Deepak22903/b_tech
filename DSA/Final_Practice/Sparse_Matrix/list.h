typedef struct node{
	int r;
	int c;
	int val;
	struct node * next;
}node;

typedef node* list;

void init(list* head);
void append(list* head, int r, int c, int val);
void sum(list * head1, list * head2, list * res);
void sub(list * head1, list * head2, list * res);
void display(list l);
