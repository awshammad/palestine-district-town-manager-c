// Aws Hammad - 1221697 - sec 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct DistrictNode *districtptr;
typedef struct TownNode *townptr;
districtptr findDistrict(districtptr D,char districtTemp[50]);
struct DistrictNode {
    char districtName[50];
    int district_population;
    struct DistrictNode *next;
    struct DistrictNode *prev;
    townptr headTown;
};
struct TownNode {
    char townName[50];
    int town_population;
    struct TownNode *next;
    struct TownNode *prev;
};
int main () {
    districtptr district = (districtptr)malloc(sizeof(struct DistrictNode));// the district that will change
    district->next = NULL;
    district->prev = NULL;
    district->headTown = NULL;
    districtptr districtBefore = (districtptr)malloc(sizeof(struct DistrictNode));// the district that will not change
    districtBefore->next = NULL;
    districtBefore->prev = NULL;
    districtBefore->headTown = NULL;
    int op=0;
    while (op!=14) {
        printMenu();
        scanf("%d",&op);
        switch(op) {
        case 1:
            read_from_user(district);
            read_from_user(districtBefore);
            break;
        case 2:
            print (districtBefore);// giving it districtBefore to print before the sorting
            break;
        case 3:
            sortDistricts(district);
            break;
        case 4:
            sortTowns(district);
            break;
        case 5:
            print (district);// giving it district to print after the sorting
            break;
        case 6:
            addDistrict (district);
            break;
        case 7:
            addTown(district);
            break;
        case 8:
            deleteTown(district);
            break;
        case 9:
            deleteDistrict (district);
            break;
        case 10:
            calculateTotalMaxMin(district);
            break;
        case 11:
            printDistrict(district);
            break;
        case 12:
            ChangeTownPopulation(district);
            break;
        case 13:
            printOnFile(district);
            break;
        case 14:
            printf("\nExiting the program...\nThanks for your time , Bye!\n");
            break;
        default:
            printf("\nERROR! Please enter a number between 1 and 14.\n");
        }
    }
}
// function to display the program menu
void printMenu() {
    printf("\nProgram Menu:\n");
    printf("-------------\n");
    printf("1. Load the input file\n");
    printf("2. Print the loaded information before sorting\n");
    printf("3. Sort the districts alphabetically\n");
    printf("4. Sort the towns for each district based on population in ascending order\n");
    printf("5. Print the sorted information\n");
    printf("6. Add a new district to the list of sorted districts (and sort the list)\n");
    printf("7. Add a new town to a certain district\n");
    printf("8. Delete a town from a specific district\n");
    printf("9. Delete a complete district\n");
    printf("10.Calculate the population of Palestine, the max and min town population\n");
    printf("11.Print the districts and their total population\n");
    printf("12.Change the population of a town\n");
    printf("13.Save to output file\n");
    printf("14.Exit\n");
    printf("\nselect an option by entering its number: ");
}
// function to read the information from the input file
void read_from_user(districtptr D) {
    FILE *in = fopen("districts.txt","r");//open a file to read from it
    if (in == NULL) {
        printf("Error opening file");
        return;
    }
    char line[100];// a line string to go through the file line by line
    while (fgets(line, sizeof(line), in) != NULL) {// read lines from the file until we reach the end of file
        char districtName [50];
        townptr townTemp = (townptr)malloc(sizeof(struct TownNode));// because we will need a town node but not necessarily a district node
        // get district, town, and population information from the file
        strcpy(districtName,strtok(line, "|"));// split the line at the first '|' to get the district name
        removeSpaces(districtName);// remove the spaces from the start and end of the string
        strcpy(townTemp->townName,strtok(NULL, "|"));// split the line at the second '|' to get the district name
        removeSpaces(townTemp->townName);
        townTemp->town_population = atoi(strtok(NULL, "|"));// get the rest of the line to get the town population and convert it to an integer by using atoi
        Insert(D,districtName,townTemp);
    }
    fclose(in);
}

void removeSpaces(char *name) {
    if (name == NULL || *name == '\0') return;
    char *start = name, *end;
    while (*start == ' ' || *start == '\t') start++;// make the start pointer moves forward over the spaces
    if (*start == '\0') {// if only spaces was found set the original string to empty and return
        *name = '\0';
        return;
    }
    end = start + strlen(start) - 1;// set the end pointer to the last character of the string
    while (end > start && (*end == ' ' || *end == '\t')) end--;// make the end pointer moves backwards over the spaces
    *(end + 1) = '\0';// set the character after the last non-space character to '\0' to end the string
    if (start > name) {// if any space in the start was skipped move the non-space part of the string to the beginning
        char *temp = start;
        while (*temp) {// copy characters from 'start' to the beginning of the string
            *name++ = *temp++;
        }
        *name = '\0';// set the character after the last non-space character to '\0' to end the string
    }
}

void Insert(districtptr D, char districtName[50], townptr newt) {
    if (D == NULL || districtName==NULL) {
        printf("Invalid input !\n");
        return;
    }
    districtptr currentD = D;// pointer to move through the districts
    districtptr lastD = D;// pointer to know the last visited district
    // move through the list to find the place to insert the district in
    while (currentD != NULL && strcasecmp(currentD->districtName, districtName) != 0) {
        lastD = currentD;// update the last visited
        currentD = currentD->next;// move to the next district
    }
    if (currentD == NULL) {// if district not found create a new district node
        districtptr newDistrict = (districtptr)malloc(sizeof(struct DistrictNode));
        strcpy(newDistrict->districtName, districtName);// copy the district name to the new node
        // initialize the new node
        newDistrict->district_population = 0;
        newDistrict->headTown = NULL;
        newDistrict->next = NULL;
        newDistrict->prev = lastD;
        lastD->next = newDistrict;
        currentD = newDistrict;// put current district to the new created district
    }
    // if newt is NULL creat a new town node with default values
    if (newt == NULL) {
        newt = (townptr)malloc(sizeof(struct TownNode));
        // initialize the new town node
        strcpy(newt->townName, " "); // setting name to " "
        newt->town_population = 0;// setting population to 0
        newt->next = NULL;
    }
    // insert the new town in the district
    if (currentD->headTown == NULL) {// if the district has no towns add the new town in the head
        currentD->headTown = newt;
        newt->prev = currentD;// set the 'prev' pointer to the district
    } else {
        // if there are towns in the district find the end of the towns and insert the new town
        townptr tempT = currentD->headTown;
        while (tempT->next != NULL) {// go through all the towns
            tempT = tempT->next;
        }
        tempT->next = newt;// insert the new town to the last town in the list
        newt->prev=tempT;// set prev to the previous town
    }
    newt->next = NULL; // set the new town's next pointer to NULL (the last town)
    currentD->district_population+=newt->town_population;// add the the new town's population to the district's population
}

void print (districtptr D) {
    districtptr p = D->next;
    if (p==NULL) printf("There is no towns or districts to print\n");
    while (p!=NULL) {
        townptr t = p->headTown;// Go to the first town in the current district
        if (p->headTown == NULL) printf("%s | %s | %d\n",p->districtName," ",0);// if there is no towns in the district
        while (t!=NULL) {// Go through all towns in the current district
            printf("%s | %s | %d\n",p->districtName,t->townName,t->town_population);
            t=t->next;// Move to the next town in the district
        }
        p=p->next;// Move to the next district
    }
}
int getMaxLength (districtptr D) {
    int max = 0;
    districtptr tempM = D->next;
    while (tempM != NULL) {// Move through all districts in the list
        int length = strlen(tempM->districtName);// Get the length of the current district's name
        if (length > max) {// If the current district's name is longer than the current max
            max = length;//Update max
        }
        tempM = tempM->next;// Move to the next district in the list
    }
    return max;
}
void sortDistricts(districtptr D) {
    if (D == NULL || D->next == NULL) return;
    int max = getMaxLength(D); // get the maximum length of district names in the list
    // array of linked lists for radix sort
    districtptr array[28];// using 28 to include all characters and the special case
    // radix sort starting from the right
    for (int p = max - 1; p >= 0; p--) {
        // initialize the array.
        for (int i = 0; i < 28; i++) {
            array[i] = (districtptr)malloc(sizeof(struct DistrictNode));
            array[i]->next = NULL;
        }
        // put districts in the array based on the current character
        districtptr d = D->next;
        while (d != NULL) {// to go through all the districts
            int index;
            // check if the current character position is in the range of district name length
            if (p < strlen(d->districtName)) {
                // calculate the index of the character according to its lowercase to make all the letters small so it becomes easier to deal with it
                index = tolower(d->districtName[p]) - 'a' + 1;
                // if the index is not between a - z
                if (index < 0 || index >= 27) {
                    index = 0; // put the out of range letters in the special case
                }
            } else {
                // (out of range)
                index = 0;
            }
            // a district pointer to put the elements in the specific index in the array
            districtptr b = array[index];
            while (b->next != NULL) {// get to the last of the list
                b = b->next;
            }
            b->next = d;// insert the district node into 'array'
            d = d->next;// move to the next district
            b->next->next = NULL;// prepare for the next opreation
        }
        // get districts from array to the (last) list and make it point to D to make D have the districts back but in sorted way for the next sort
        districtptr last = D;
        for (int i = 0; i < 28; i++) {
            districtptr b = array[i];
            while (b->next != NULL) {
                last->next = b->next;
                last = last->next;
                b->next = b->next->next;
            }
            free(array[i]); // free the 'array' node to make it empty.
        }
        last->next = NULL; // ensure the last district points to NULL.
    }
}
void sortTowns(districtptr D) {
    if (D==NULL) return; // if the list is empty return

    districtptr tempD = D;
    while (tempD != NULL) { // go through all districts
        int swapped;
        do {
            swapped = 0;// make swapped equals 0 so if we swapped the towns we make it 1 to end the loop
            townptr currentT = tempD->headTown;// pointer to the head town
            townptr prevT = NULL;
            while (currentT != NULL && currentT->next != NULL) {
                // check if the current town population is greater than the next town population
                if (currentT->town_population > currentT->next->town_population) {
                    // if true swap nodes between currentT and currentT->next
                    swap_towns(currentT, currentT->next);
                    swapped = 1; // the swap is done
                }
                prevT = currentT;// make the current is previous to move on
                currentT = currentT->next;// move to the next town
            }
        } while (swapped);
        tempD = tempD->next; // move to the next district
    }
}

void swap_towns(townptr a, townptr b) {
    char temp_town[50];// to have the town name
    int temp_population = a->town_population;// to have the town population

    strcpy(temp_town, a->townName);// copy the town name of the current to the temp
    strcpy(a->townName, b->townName);// copy the town name of the next to the current
    strcpy(b->townName, temp_town);// copy the town name of the temp to the next

    a->town_population = b->town_population;// set the town population of the current equals to the next
    b->town_population = temp_population;// set the town population of the next equals to the temp that have the current population
}
void addDistrict (districtptr D) {
    char tempD [50];// name of the district to add
    printf("Enter a district to add : \n");
    while (getchar() != '\n');// to stop reading when the user write (Enter)
    scanf("%49[^\n]", tempD);
    districtptr d = findDistrict(D,tempD);// to see if the district is already exist
    if (d==NULL) {// if the district does not exist
        Insert(D,tempD,NULL);
        sortDistricts(D);// sort the districts after adding any district
    } else {
        printf("This district already exists !");
        return;
    }
}
void addTown (districtptr D) {
    char tempD[50], tempT[50];// to have the district to put the town in and the name of town
    int populationTemp;
    printf("Enter a district to add a town in: \n");
    while (getchar() != '\n');// to stop reading when the user write (Enter)
    scanf("%49[^\n]", tempD);
    districtptr districtNode = findDistrict(D, tempD);// find the district to put the town in it
    if (districtNode != NULL) {// if the district exists
        // read the name and population of the town we want to insert
        printf("Enter a town to insert in the district: \n");
        while (getchar() != '\n');
        scanf("%49[^\n]", tempT);
        printf("Enter the population of the town: \n");
        scanf("%d", &populationTemp);
        if (strcmp(districtNode->headTown," ")!=0) {// if the head is not empty
            townptr temp = (townptr)malloc(sizeof(struct TownNode));// create a new town node
            // put the information from the user in the town
            strcpy(temp->townName,tempT);
            temp->town_population = populationTemp;
            temp->next = NULL;
            Insert(D,tempD,temp);// insert the town into its district
        } else {// if the head is empty insert the town information in it
            strcpy(districtNode->headTown,tempT);
            districtNode->headTown->town_population = populationTemp;
            districtNode->district_population+=populationTemp;
        }
        sortTowns(D);// sort the towns after adding any town
    } else printf("There is no district have the name %s !\n",tempD);
}
districtptr findDistrict(districtptr D,char tempD[50]) {
    districtptr p = D->next;
    while (p != NULL) {// to move through all the districts
        if (strcasecmp(p->districtName, tempD) == 0) {
            // when the district is found return it
            return p;
            break;
        } else
            p = p->next; // move to the next district
    }
    return NULL;// not found
}
townptr findTown(districtptr D,char tempT[50]) {
    districtptr d = D->next;
    while (d != NULL) {// to move through all the districts
        townptr t = d->headTown;
        while (t != NULL) {// to move through all the towns
            if (strcasecmp(t->townName, tempT) == 0) {
                // when the town is found return it
                return t;
                break;
            } else
                t = t->next; // move to the next town
        }
        d = d->next;
    }
    return NULL;// not found
}
districtptr findDistrictTheTownIn(districtptr D,char townTemp[50]) {
    districtptr d = D->next;
    while (d != NULL) {
        townptr t = d->headTown;
        while (t != NULL) {
            if (strcasecmp(t->townName, townTemp) == 0) {
                // when the district is found return it
                return d;
                break;
            } else
                t = t->next; // Move to the next town.
        }
        d = d->next;
    }
    return NULL;// not found
}
void deleteTown (districtptr D) {
    char townTemp[50];
    printf("Enter a town to delete : \n");
    while (getchar() != '\n');// read the town to delete and stop when the user write (Enter)
    scanf("%49[^\n]", townTemp);
    townptr t = findTown(D,townTemp);// find the town we want to delete and make t points on it
    districtptr d = findDistrictTheTownIn(D,townTemp);// find the district that the town is in it
    if (t != NULL) {// if the town is found
        d->district_population-=t->town_population;
        if (t->next != NULL)// if the town is not the last one
            t->next->prev=t->prev;
        if (strcasecmp(t->prev,d->districtName)==0)// if the town is the first town
            d->headTown=t->next;
        else t->prev->next=t->next;
        free(t);// freeing the town
        printf("Town %s has been deleted !\n",townTemp);
    } else printf("Town %s not found !",townTemp);
}
void deleteDistrict (districtptr D) {
    char districtTemp[50];
    printf("Enter a district to delete: \n");
    while (getchar() != '\n');// to stop reading when the user write (Enter)
    scanf("%49[^\n]", districtTemp);
    districtptr p = D, prev = NULL;// to traverse and have the previous
    while (p->next != NULL && strcasecmp(p->next->districtName, districtTemp) != 0) {
        prev = p; // having the previous district
        p = p->next; // move to the next district
    }
    if (p->next != NULL) { // if the district is found
        districtptr d = p->next; // d is the district to delete
        p->next = d->next; // start removing the district from the list.
        if (d->next != NULL) { // if it is not the last node
            d->next->prev = p;
        }
        // delete the towns in the district before deleting the district
        townptr t = d->headTown, nextTown;
        while (t != NULL) {
            nextTown = t->next;
            free(t);// free the current town
            t = nextTown;// move to the next town
        }
        free(d); // free the district node
        printf("District %s has been deleted!\n", districtTemp);
    } else {
        printf("District %s not found!\n", districtTemp);
    }
}

void calculateTotalMaxMin (districtptr D) {
    districtptr d = D->next;// point on the first district
    townptr t = d->headTown;// point on the first town in the first district
    int total = 0;
    int max = t->town_population;
    int min = t->town_population;
    if (D == NULL || D->next == NULL) {
        printf("The list is empty.\n");
        int total = 0;
        int max = 0;
        int min = 0;
        return;
    }
    while (d!=NULL) {// move through all the districts
        t = d->headTown;// make t every time to point on the first town in the current district
        while (t!=NULL) {
            if (t->town_population >= max) {
                max = t->town_population;// if current town's population is greater than the max, make it the max
            }
            if (t->town_population <= min) {
                min = t->town_population;// if current town's population is smaller than the min, make it the min
            }
            total+=t->town_population;// add the town's population to the total population
            t = t->next;// move to the next town
        }
        d=d->next;// move to the next district
    }
    printf("The population of Palestine is %d \nthe max town population = %d \nThe min town population = %d",total,max,min);
}
void printDistrict(districtptr D) {
    if (D == NULL || D->next == NULL) {// if there is no districts
        printf("The list is empty.\n");
        return;
    }
    districtptr d = D->next;// make d points on the first district
    while (d != NULL) {// move through all districts
        printf("%s District, Population = %d\n", d->districtName, d->district_population);
        d = d->next;// move to the next district
    }
}
void ChangeTownPopulation (districtptr D) {
    char tempD[50];// the district that have the town we want to change its population
    char tempT[50];// the town
    int newPopulation;
    printf("Enter the district that has the town: \n");
    while (getchar() != '\n'); // read the district until the user press (Enter)
    scanf("%49[^\n]", tempD);
    districtptr p = findDistrict(D, tempD);// find the district
    if (p == NULL) {// not found
        printf("There is no district with the name %s\n", tempD);
        return;
    }
    printf("Enter a town in %s to change its population: \n", tempD);// the district is found
    while (getchar() != '\n'); // read the town until the user press (Enter)
    scanf("%49[^\n]", tempT);
    townptr t = findTown(D, tempT); // find the town we want to change its population
    if (t == NULL) {// not found
        printf("Town %s not found in %s!\n", tempT, tempD);
        return;
    }
    p->district_population-=t->town_population;
    printf("Enter the new population: \n");// we found the town
    scanf("%d", &newPopulation);
    t->town_population = newPopulation;// make the town's population equals to the new population
    p->district_population+=newPopulation;
    printf("Town %s population has been changed to %d !\n", tempT, newPopulation);
}
void printOnFile(districtptr D) {
    FILE *out = fopen("sorted_districts.txt", "w");// open the file to print the data on it
    if (D == NULL || D->next == NULL) {
        fprintf(out, "The list is empty.\n");
        return;
    }
    sortDistricts(D);// sort the districts before printing on the file
    sortTowns(D);// sort the towns before printing on the file
    districtptr p = D->next;// point on the first district
    while (p!=NULL) {// move through all the districts
        townptr t = p->headTown;// point on the first town in the district
        fprintf(out, "%s District, Population = %d\n", p->districtName, p->district_population);
        while (t!=NULL) {// move through all the towns
            fprintf(out, "%s, %d\n", t->townName, t->town_population);
            t=t->next;// move to the next town
        }
        p=p->next;// move to the next district
    }
}