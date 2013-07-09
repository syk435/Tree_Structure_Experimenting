#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_URL_LENGTH 100

 struct tnode { /* the tree node: */
   char *key; /* points to the url string */
   int count; /* number of occurrences */
   struct tnode *left; /* left child */
   struct tnode *right; /* right child */
 };


 /* add_to_tree:  add a node with url, at or below p */
 struct tnode* add_to_tree(struct tnode* p, char* url)
 {
	int x;
	struct tnode* newnode;
	struct tnode* nextnode;
	char* nodeurl;
    char urlarray[MAX_URL_LENGTH];
	char* b = (char*)malloc(strlen(url)+1);

	if(p){ //if the first node isn't null do this, handle if next node is null within this
		nodeurl = p->key;
		//b = urlarray;
		
		strcpy(b,url);
		x = strcmp(b, nodeurl);

		if(x > 0){
			nextnode = (p->right);
			if((p->right)){ //so if next node isn't null keep traversing tree
				add_to_tree(nextnode, url);
				return p;
			}
			else{ //otherwise if it is null previous condition won't go, we've reached the end of the branch. so new node and link current to it
				newnode = (struct tnode*)malloc(sizeof(struct tnode));
				newnode->count = 1;
				newnode->key = url;	//is this okay? to ponint at url?
				newnode->left = NULL;
				newnode->right = NULL;
				(p->right) = newnode;
				return p;
			}
		}

		else if(x < 0){
			nextnode = (p->left);
			if((p->left)){ //so if next node isn't null keep traversing tree
				add_to_tree(nextnode, url);
				return p;
			}
			else{ //otherwise if it is null previous condition won't go, we've reached the end of the branch. so new node and link current to it
				newnode = (struct tnode*)malloc(sizeof(struct tnode));
				newnode->count = 1;
				newnode->key = url;	//is this okay? to ponint at url?
				newnode->left = NULL;
				newnode->right = NULL;
				(p->left) = newnode;
				return p;
			}
		}

		else if(x == 0){
			(p->count)++;
			return p;
		}

	}

	else { //if no other nodes in tree, this is first node
		newnode = (struct tnode*)malloc(sizeof(struct tnode));
		newnode->count = 1;
		newnode->key = url;	//is this okay? to ponint at url?
		newnode->left = NULL;
		newnode->right = NULL;
		return newnode;
	}
 }
 //don't forget about freeing memory after allocating it

 /* populate_tree: repeatedly call add_to_tree on urls from a file */
 void populate_tree(char *url_file, struct tnode** R)
 {
	 int x;
	 char temp[MAX_URL_LENGTH];
	 char* a;
	 char* b;
	 char* fgetscheck;
	 FILE* fp = fopen(url_file,"r"); //dont' forget fclose(fp)

	 while(!feof(fp)){
		fgetscheck = fgets(temp,MAX_URL_LENGTH,fp);
		if(fgetscheck){
		a =(char*)malloc(MAX_URL_LENGTH+1);
		strcpy(a,temp);
		b = a;

		for(x = 0;x<MAX_URL_LENGTH; x++){
			if (*b == NULL ){
				*(b-1) = NULL;
				break;
			}
			b++;
		}
	 	add_to_tree(*R,a);
		//increment fp,though i think this current code might work too
	 }
	 }
	 
	 fclose(fp);
	 return;
 }



 /* lookup:  look up a url in the tree rooted at p, return the frequency of that url */
 int lookup(struct tnode* p, char* url) // Return the frequency of the url
 {
    int x;
	struct tnode* nextnode;
	char* nodeurl;
    char urlarray[MAX_URL_LENGTH];
	char* b;
	
	if(p){ //if the first node isn't null do this, handle if next node is null within this
		nodeurl = p->key;
		b = urlarray;
		
		strcpy(b,url);
		x = strcmp(b, nodeurl);

		if(x > 0){
			nextnode = (p->right);
			if((p->right)){ //so if next node isn't null keep traversing tree
				return lookup(nextnode, url);
			}
			else{ //otherwise if it is null previous condition won't go, we've reached the end of the branch. so new node and link current to it
				return 0;
			}
		}

		else if(x < 0){
			nextnode = (p->left);
			if((p->left)){ //so if next node isn't null keep traversing tree
				return lookup(nextnode, url);
			}
			else{ //otherwise if it is null previous condition won't go, we've reached the end of the branch. so new node and link current to it
				return 0;
			}
		}

		else if(x == 0){
			return (p->count);
		}

	}
	else{return 0;}
 }


 /* treeprint:  in-order print of tree p
 Set the urls in the passed in array in alphabetical fashion. Also set their respective frequencies in a second int array.Return the number of elements set
 */ 
int treeprint(int size, struct tnode* p, char URL_array[][MAX_URL_LENGTH], int *n)
{
	//char wordarray[10][MAX_URL_LENGTH];
	//int x;

	if(size < 10 && ((p) || (p->left) || (p->right))){ //so while size is less than 10 and any of the three nodes are valid
		if(p->left){ //if left node isn't null
			if(size<10){
				size = treeprint(size,(p->left),URL_array,n);
			}
		}
		if(p){ //then current node
			if(size<10){
			strcpy(&URL_array[size][0],p->key);
			*(n+size) = p->count;
			size++; //only increment size if you put something in array
			}
		}
		if(p->right){ //then if right node isn't null
			if(size<10){
			size = treeprint(size,(p->right),URL_array,n);
			}
		}
			//for a total of 10 nodes, return first the left node(s) then current node then the right node(s) recursively
	}

	return size;
}

