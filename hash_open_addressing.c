#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#define HASH_TABLE_SIZE 19

typedef struct Student {
	int id;
	char name[20];
} Student_t;


typedef enum{
	EMPTY,
	OCCUPIED,
	DELETED
} Student_Status_e; 


typedef struct {
	Student_t student;
	Student_Status_e status; 
} Student_Record_t;	



void insert(Student_t student, Student_Record_t table[]);
int search(int key, Student_Record_t table[]);
void delete(int key, Student_Record_t table[]);
void display(Student_Record_t table[]);
int hash(int key);


int main(void) 
{
	Student_Record_t table[HASH_TABLE_SIZE];
	
	Student_t student;

	int choice;

	int key;

	int pos;


	for (int i = 0; i < HASH_TABLE_SIZE; i++) {
		table[i].status = EMPTY;
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
					printf("%d %s", table[pos].student.id, table[pos].student.name);
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


void insert(Student_t student, Student_Record_t table[])
{
	int key, h, location;

	key = student.id;

	h = hash(key);

	location = h;

	for (int i = 1; i < HASH_TABLE_SIZE; i++) {
	
		if ((table[location].status == EMPTY) ||(table[location].status == DELETED)) {
			table[location].student = student;
			table[location].status  = OCCUPIED;
			printf("Record inserted...\n");
			return;
		}

		if (table[location].student.id == key) {
			printf("Duplicate Key Error...\n");
			return;
		}

		location = (h + i) % HASH_TABLE_SIZE;
	}
	
	printf("Table Overflow Error...\n");


}




int search(int key, Student_Record_t table[])
{
	int h = hash(key);

	int location = h;

	for (int i = 1; i < HASH_TABLE_SIZE; i++) {
		
		if (table[location].status == EMPTY) {
			return -1;
		}	

		if (table[location].student.id == key) {
			return location;
		}

		location = (h + i) % HASH_TABLE_SIZE;
	}

	return -1;
}



void delete(int key, Student_Record_t table[])
{
	int location = search(key, table);

	if (location == -1) {
		printf("Key Not Found...\n");
	} else {
		table[location].status = DELETED;
	}
}



void display(Student_Record_t table[])
{
	for (int i = 0; i < HASH_TABLE_SIZE; i++) {
		
		printf("%d\t", i);
		
		if (table[i].status == OCCUPIED) {
			printf("OCCUPIED\t%d\t%s\n", table[i].student.id, table[i].student.name);
		}

		else if (table[i].status == EMPTY) {
			printf("EMPTY\n");
		}
		
		else { 
			printf("DELETED\n");
		}
	}
}
















