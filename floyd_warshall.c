/* This is a code for COMP 201 assignment 3.
 * In this code, Floyd-Warshall algorithm is implemented
 * to find the shortest paths between any two cities
 * in a given graph of cities.
 */
 
 // Özgün Ozan Nacitarhan
 // ID: 63923
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int INF = 1e7; 
int lookup_string(char str[30]); 

/* Array of vertices. 
 * Each element of the str array contains a city name and 
 * its index in str becomes the city's numeric id.
 */
typedef struct vertices 
{
	// This attribute shows the size of dynamically allocated memory
	int size;
	// This attribute shows the number of cities in the array
	int city_count;
	// This attribute is the array of city names
	char (* str)[30];
} 
vertices;

/* Array of edges. 
 * Each element of the edge array contains the ids of two cities 
 * connected directy by a road and the length of the road.
 */
typedef struct edges 
{
	// This attribute shows the size of dynamically allocated memory
	int size;
	// This attribute shows the number of roads in the array
	int edge_count;
	// This attribute is the array of road information
	int (* edge)[3];
} 
edges;

vertices cities;

edges roads;

/* A two-dimensional array that shows 
 * the length of the shortest path connecting 
 * any two cities.
 */
int **city_graph;

/* A two-dimensional array that shows the direction 
 * to the shortest path between any two cities.
 */
int **shortest_paths;

/* A function that implements Floyd-Warshall algorithm. 
 * This algorithm finds the shortest path between 
 * any two vertices in a given graph.
 */
void floydWarshall()  
{  
	for (int k = 0; k < cities.city_count; k++) 
	{  
		for (int i = 0; i < cities.city_count; i++) 
		{  
			for (int j = 0; j < cities.city_count; j++) 
			{  

				// We cannot cross a road that doesn't exist  
				if ((city_graph[i][k] == INF) || (city_graph[k][j] == INF))  
				{
					continue;
				}  

				if (city_graph[i][j] > (city_graph[i][k] + city_graph[k][j])) 
				{  
					city_graph[i][j] = city_graph[i][k] + city_graph[k][j];  
					shortest_paths[i][j] = shortest_paths[i][k];  
				}  
			}  
		}  
	}  
} 

/* A function that initializes the values in 
 * city_graph and shortest_paths arrays.
 */
void initialise()  
{  
	for (int i = 0; i < cities.city_count; i++) 
	{  
		for (int j = 0; j < cities.city_count; j++) 
		{    

			// No edge between node i and j  
			if (city_graph[i][j] == INF)  
			{
				shortest_paths[i][j] = -1;
			}  
			else
			{
				shortest_paths[i][j] = j;
			}  
		}  
	}  
}

/* A function that inserts the name of a new city 
 * to the cities array.
 */
int insert_to_cities(char str[30]) 
{
	// Write your code here
	// Check if the city name already exists in the array 
	// If it does, return the array index of the city 
	
	// If the city name doesn't exist, it is inserted to the cities array, and
	// return the array index of the city

	// If the dynamically allocated size of cities array is not large enough, 
	// the size of cities array is enlarged and the city name is inserted 
	// to the newly added region
	// Return the array index of the city.
	int arr_size = (sizeof(char[30])); // defining the size of cahr array 
	if(lookup_string(str) >= 0)
		return lookup_string(str);
	
	if(cities.size <= cities.city_count * arr_size) // if memory is not enough, it reallocates the memory
	{
		cities.str = realloc(cities.str, arr_size * (cities.city_count + 1));	
	}
	strcpy(*(cities.str + cities.city_count), str);
	cities.city_count++;
	int arr_index = cities.city_count - 1;
	return arr_index;
}

/* A function that looks up if a city name
 * is already in the cities array. 
 */
int lookup_string(char str[30]) 
{
	for(int i = 0; i < cities.city_count; i++) {
		if(strncmp(str, cities.str[i], 30) == 0)
			return i;
	}
	printf("city %s is not found\n", str);
	return -1;
}

void printPath(int u, int v)  
{  
	int *path_arr = (int *) malloc(cities.city_count * sizeof(int));
	if(shortest_paths[u][v] == -1)
		printf("\n**** NO PATH ****\n");
	else
	{
		int index = 1;
		path_arr[0] = u;
		while(1)
		{
			u = shortest_paths[u][v];
			path_arr[index] = u;
			index++;
			if(u == v)	break;
		}
		for(int i = 0; i < index; i++)
		{
			printf("%s ",*(cities.str+path_arr[i]));
		}
		printf("\n");
	}	
	free(path_arr);
} 

int main(int argc, char *argv[])
{
	// Write your code here

	// Allocate memory regions dynamically to cities array 
	// and roads array.

	// Read and parse the input file. Insert the city names to cities array.
	// The index of the city name in the cities array becomes the city id. 
	// Insert city ids and road lengths to roads array.

	// Allocate memory regions dynamically to city_graph, 
	// distance, and shortest_paths arrays.

	// Initialize the values in city_graph array with road lengths, 
	// such that the value in city_graph[i][j] is the road length 
	// between cities i and j if these cities are directly connected 
	// by a road 
	// For cities m and n that are not connected directly by a road, 
	// the value in city_graph[m][n] will be INF, 
    // which is a large value like 10M, 
	// that is assumed to be infinite. 
	
	
	cities.size = 12 * sizeof(char[30]); // <13
	cities.str = (char(*) [30]) malloc(cities.size);
	cities.city_count =0;
	
	roads.size = 17 * sizeof(int[3]);  // >16
	roads.edge = (int(*) [3]) malloc(roads.size);
	roads.edge_count = 0;
	
	// Reading and parsing the input file.
	int size_char_arr = sizeof(char[100]);
	FILE *fp;
    fp = fopen("input.txt","r");
    char * file_str= (char *) malloc(size_char_arr);
    if (fp == NULL){
        printf("Error opening file");
        return 0;
    } 
	while (fgets(file_str,size_char_arr,fp) != NULL) {
        char * char1= strtok(file_str," ");
		char * char2 = strtok(NULL, " ");
		int char1index = insert_to_cities(char1);
		int char2index;
		if (char2 != NULL)
		{
			char2index = insert_to_cities(char2); 
		}
		char * length1 = strtok(NULL, " ");
		int length = 0;
		if (length1 != NULL)
			length = atoi(length1);

		*(*(roads.edge + roads.edge_count) ) = char1index;
    	*(*(roads.edge + roads.edge_count) + 1) = char2index;
    	*(*(roads.edge + roads.edge_count) + 2) = length;
		roads.edge_count++;
	}
	free(file_str);
	fclose(fp);
	
	// Allocating memory regions dynamically.
	city_graph = (int **) malloc(cities.city_count * sizeof(int *));
	shortest_paths = (int **) malloc(cities.city_count * sizeof(int *));
	for (int i = 0; i < cities.city_count; i++) {
		city_graph[i] = (int *) calloc(cities.city_count,sizeof(int));                 
		shortest_paths[i] =  (int *) calloc(cities.city_count,sizeof(int));                                                        
	}
	
	for(int i = 0; i < roads.edge_count; i++){
		int a = *(*(roads.edge + i) + 0);
		int b = *(*(roads.edge +i) + 1);
		int dist = *(*(roads.edge +i) + 2);
		city_graph[a][b] = dist;
		city_graph[b][a] = city_graph[a][b];	
	}
	
	for(int i=0;i<cities.city_count;i++){
		for(int j=0;j<cities.city_count;j++){
			if(city_graph[i][j]==0)
				city_graph[i][j]= 100000000;
		}
	}
    
	initialise();
	floydWarshall();
	printf("\nType end to exit");
	
	char * input = (char *) malloc(size_char_arr);
	while(1) {
		// prompt user to enter two city names
		// print the shortest path between the two cities
		// print the length of the path
		printf("\nEnter the Cities: \n");
		fgets(input,99,stdin);
		if (strncmp(input,"end",3)==0 )
			break;
		char * city1= strtok(input," ");
		int index1 = lookup_string(city1);
		char * city2 = strtok(NULL, "\n");
		
		int index2 = 2; 
		if (city2 != NULL)
			index2 = lookup_string(city2);
		if(index1 != -1 && index2 != -1){
			printPath(index1,index2);
			printf("%d",city_graph[index1][index2]);
		} else {
			printf("WRONG INPUT");
			continue;
		}		
	}
	
	// frees all allocations
	free(city_graph); 
	free(shortest_paths); 
	free(input);
	free(cities.str);
	free(roads.edge);
	return 0;	
	
}
