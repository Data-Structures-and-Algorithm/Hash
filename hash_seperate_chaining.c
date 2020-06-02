#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#define HASH_TABLE_SIZE 7

typedef struct Student {
	int id;
	char name[20];
} Student_t;


typedef struct Node {
	Student_t info;
	struct Node *next;
} Node_t;


void insert(Student_t student, Node_t *table[]);
int search(int key, Node_t *table[]);
void delete(int key, Node_t *table[]);
void display(Node_t *table[]);
int hash(int key);


int main(void) 
{
	Node_t *table[HASH_TABLE_SIZE];
	
	Student_t student;

	int choice;

	int key;

	int pos;


	for (int i = 0; i < HASH_TABLE_SIZE; i++) {
		table[i] = NULL;
	}



	while (true) {
		printf("\n1. Insert\n2. Search\n3. Delete\n4. Display" 
			   "\n5. Exit\n\nEnter ur choice: " );
		scanf("%d", &choice);
		
		while (getchar() != '\n');

		switch (choice) {
			case 1:
				printf("\nEnter student ID: ");
				scanf("%d", &student.id);
				printf("\nEnter student name: ");
				scanf("%s", student.name);
				insert(student, table);
				break;
			case 2:
				printf("\nEnter key to be searched: ");
				scanf("%d", &key);
				pos = search(key, table);
				if (pos == -1) {
					printf("\nKey not found\n");
				} else {
					printf("\nFound at %d\n", pos);
					printf("%d %s", table[pos]->info.id, table[pos]->info.name);
				}
				break;
			case 3:
				printf("\nEnter key to be deleted: ");
				scanf("%d", &key);
				delete(key, table);
				break;
			case 4:
				display(table);
				break;
			case 5:
				exit(0);
			default:
				printf("Invalid choice\n");
		
		}
		
		while (getchar() != '\n');
		
		getchar();		
		
		system("clear");
	}	


	return 0;
}



int hash(int key) 
{
	return (key % HASH_TABLE_SIZE);
}


void insert(Student_t student, Node_t *table[])
{
	int key, h, location;

	key = student.id;

	h = hash(key);

	location = h;

	if (search(key, table) != -1) {
		printf("\nDuplicate Key Error...");
		return;
	}

	Node_t *new_node = malloc(sizeof(Node_t));

	new_node->info = student;
	new_node->next = table[location];
	table[location] = new_node;

}




int search(int key, Node_t *table[])
{
	Node_t *temp;

	int h = hash(key);

	int location = h;

	temp = table[location];

	while (temp && temp->info.id != key) {
		temp = temp->next;
	}

	if (temp == NULL) {
		return -1;
	} 

	printf("%d %s", temp->info.id, temp->info.name);

	return location;
}



void delete(int key, Node_t *table[])
{
	Node_t *temp, *del_node;

	int h = hash(key);

	int location = h;

	if (table[location] == NULL) {
		printf("Key Not Found...\n");
		return;	
	}

	if(table[location]->info.id == key) {
		del_node = table[location];
		table[location] = table[location]->next;
		free(del_node);
		return;
	}

	temp = table[location];

	while ((temp->next != NULL) && (temp->next->info.id != key)) {
		temp = temp->next;
	}

	if (temp->next == NULL) {
		printf("Key Not Found...\n");	
	} else {
		del_node = temp->next;
		temp->next = del_node->next;
		free(del_node);
	}

}



void display(Node_t *table[])
{
	Node_t *temp;

	for (int i = 0; i < HASH_TABLE_SIZE; i++) {
		
		printf("%d-->", i);

		temp = table[i];

		while (temp) {
			printf("(%d, %s)-->", temp->info.id, temp->info.name);
			temp = temp->next;
		}

		printf("NULL\n");
	}	
}
















