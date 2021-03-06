#define SEATS 12
#define NMAX 15
#define DATAMAX 40
#define SOLDPOS 3
#define NAMEPOS 9
struct plane
{
	int number;
	bool sold = 0;
	char *lname;
	char *fname;
};

void load_file(FILE *data,struct plane *seat)
{
	char dataline[DATAMAX];
	for (int n = 0; fgets(dataline, DATAMAX, data); n++)
	{
		seat[n].number = n + 1;
		if (dataline[SOLDPOS] == 'S')
		{
			int pos = NAMEPOS;
			int length;
			seat[n].sold = 1;
			char temp[NMAX];
			memset(temp, '\0', NMAX);
			for (int m = 0; isalpha(dataline[pos]); m++, pos++)
				temp[m] = dataline[pos];
			pos++;
			length = strlen(temp) + 1;
			seat[n].fname = (char *)malloc(length);
			strcpy_s(seat[n].fname, length, temp);
			memset(temp, '\0', NMAX);
			for (int m = 0; isalpha(dataline[pos]); m++, pos++)
				temp[m] = dataline[pos];
			length = strlen(temp) + 1;
			seat[n].lname = (char *)malloc(length);
			strcpy_s(seat[n].lname, length, temp);
		}
		else
			continue;
	}
}

void deln(char *str)
{
	int n = 0;
	while (1)
	{
		if (str[n] == '\n')
		{
			str[n] = '\0';
			break;
		}
		n++;
	}
}
void getname(struct plane * one)
{
	char temp[NMAX];
	int length;
	printf("Please enter the passenger's first name:");
	fgets(temp, NMAX, stdin);
	deln(temp);
	length = strlen(temp) + 1;
	one->fname = (char *)malloc(length);
	strcpy_s(one->fname, length, temp);
	printf("Please enter the passenger's last name:");
	fgets(temp, NMAX, stdin);
	deln(temp);
	length = strlen(temp) + 1;
	one->lname = (char *)malloc(length);
	strcpy_s(one->lname, length, temp);
}

char menu(void)
{
	char choice;
	printf("To choose a function, enter its letter label:\n");
	printf("a) Show number of empty seats\n");
	printf("b) Show list of empty seats\n");
	printf("c) Show alphabetical list of seats\n");
	printf("d) Assign a customer to a seat assignment\n");
	printf("e) Delete a seat assignment\n");
	printf("f) Quit     ");
	scanf_s("%c", &choice,1);
	getchar();
	return choice;
}

void clean_name(struct plane *seat)
{
	seat->fname = (char *)malloc(1);
	seat->lname = (char *)malloc(1);
	seat->fname[0] = '\0';
	seat->lname[0] = '\0';
}

void show_empty_number(struct plane *seat)
{
	int empty = 0;
	for (int n = 0; n < SEATS; n++)
	{
		if (seat[n].sold)
			continue;
		empty++;
	}
	printf("\nThere are %d empty seats.\n\n", empty);
}

void show_empty_list(struct plane *seat)
{
	printf("\nEmpty seats:");
		for (int n = 0; n < SEATS; n++)
			if (!seat[n].sold)
				printf("#%d ", seat[n].number);
	printf("\n\n");
}

void show_alphabetical_list(struct plane *seat)
{
	struct plane temp;
	int top, seek;
	for (top = 0; top < SEATS - 1; top++)
	{
		for (seek = top + 1; seek < SEATS; seek++)
		{
			if (seat[top].sold && seat[seek].sold)
			{
				if (strcmp(seat[top].fname, seat[seek].fname) > 0)
				{
					temp = seat[top];
					seat[top] = seat[seek];
					seat[seek] = temp;
				}
				if (strcmp(seat[top].lname, seat[seek].lname) == 0 && strcmp(seat[top].lname, seat[seek].lname) > 0)
				{
					temp = seat[top];
					seat[top] = seat[seek];
					seat[seek] = temp;
				}
			}
		}
	}
	for (int n = 0; n < SEATS; n++)
	{
		if(seat[n].sold)
			printf("\n%s %s   #%d\n", seat[n].fname, seat[n].lname, seat[n].number);
		continue;
	}
	printf("\n");
}

void add_assign(struct plane *seat)
{
	int n;
	printf("\nPlease enter the number of the seat:");
	scanf_s("%d", &n);
	getchar();
	if (seat[n-1].sold)
	{
		printf("The seat has been sold.\n\n");
		return;
	}
	getname(&seat[n-1]);
	seat[n-1].sold = 1;
	printf("The info has been added.\n\n");
}

void del_assign(struct plane *seat)
{
	int n;
	printf("\nPlease enter the number you want to delete.");
	scanf_s("%d", &n);
	getchar();
	if (!seat[n-1].sold)
	{
		printf("It hasn't been sold.\n\n");
		return;
	}
	seat[n-1].sold = 0;
	clean_name(&seat[n]);
	printf("The assignment has been deleted.\n\n");
}

void numsort(struct plane *seat)
{
	struct plane temp;
	int top, seek;
	for (top = 0; top < SEATS - 1; top++)
	{
		for (seek = top + 1; seek < SEATS; seek++)
		{
			if (seat[top].number > seat[seek].number)
			{
				temp = seat[top];
				seat[top] = seat[seek];
				seat[seek] = temp;
			}
		}
	}
}