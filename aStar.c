#include <stdio.h>

#define X_SIZE 10
#define Y_SIZE 10
#define INF 999999

typedef struct NodeStruct{
	int x;
	int y;
} Node;
Node globalPath[X_SIZE * Y_SIZE];

//Make global List of Obstacle'd Nodes
int obstacleMap[X_SIZE][Y_SIZE] = {0};
//obstacleMap[2][3] = 1;

int hScore(int xStart, int yStart, int xEnd, int yEnd);
void makePath(Node** cameFrom, Node* current);
void nodePush(Node data, Node* nodeArray);
Node nodePop(Node* nodeArray);
Node nodePopNum(Node* nodeArray, int index);
int lowestFScore(Node* setToCheck, int fScoreTable[X_SIZE][Y_SIZE]);
int isInSet(Node testNode, Node* testSet);
void printPath();

void printPath(){
	int place=0;
	while(globalPath[place].x != INF){
		printf("(%d,%d) ",globalPath[place].x,globalPath[place].y);
	}
	printf("\n");
}

int AStar(Node start, Node end){
	Node finishedSet[X_SIZE * Y_SIZE];
	Node workingSet[X_SIZE * Y_SIZE];
	int i,j;
	for(i=0;i<(X_SIZE*Y_SIZE);i++){
		Node maxNode;
		maxNode.x = INF;
		maxNode.y = INF;
		workingSet[i] = maxNode;
		Node maxNode2;
		maxNode2.x = INF;
		maxNode2.y = INF;
		finishedSet[i] = maxNode2;
	}
	nodePush(start,workingSet);
	Node cameFrom[X_SIZE][Y_SIZE];
	for(i=0;i<X_SIZE;i++){
		for(j=0;j<Y_SIZE;j++){
			Node maxNode;
			maxNode.x = INF;
			maxNode.y = INF;
			cameFrom[i][j] = maxNode;
		}
	}
	
	int gScore[X_SIZE][Y_SIZE];
	gScore[start.x][start.y] = 0;
	int fScore[X_SIZE][Y_SIZE];
	for(i=0;i<X_SIZE;i++){
		for(j=0;j<Y_SIZE;j++){
			gScore[i][j] = INF;
			fScore[i][j] = INF;
		}
	}
	fScore[start.x][start.y] = gScore[start.x][start.y] + hScore(start.x,start.y,end.x,end.y);
	Node current;
	int lowestIndex;
	while(workingSet[0].x != INF){
		lowestIndex = lowestFScore(workingSet,fScore);
		current = workingSet[lowestIndex];
		if(current.x == end.x && current.y == end.y){
			makePath(&cameFrom,&current);		
			return 1;
		}
		nodePopNum(&workingSet,lowestIndex);
		nodePush(current,&finishedSet);
		int i=0;
		Node neighbor;
		for(i=0;i<4;i++){
			switch(i){
				case 0:
					neighbor.x = current.x+1;
					neighbor.y = current.y;
					break;
				case 1:
					neighbor.x = current.x-1;
					neighbor.y = current.y;
					break;
				case 2:
					neighbor.x = current.x;
					neighbor.y = current.y+1;
					break;
				case 3:
					neighbor.x = current.x;
					neighbor.y = current.y-1;
					break;
			}
			if(isInSet(neighbor,&finishedSet) == 1){}
			else if(obstacleMap[neighbor.x][neighbor.y] == 1){}
			else{
				int tempGScore = gScore[current.x][current.y] + 1;
				if(0==isInSet(neighbor,&workingSet) || tempGScore < gScore[neighbor.x][neighbor.y]){
					cameFrom[neighbor.x][neighbor.y] = current;
					gScore[neighbor.x][neighbor.y] = tempGScore;
					fScore[neighbor.x][neighbor.y] = tempGScore + hScore(neighbor.x,neighbor.y,end.x,end.y);
					if(0==isInSet(neighbor,&workingSet)){
						nodePush(neighbor,&workingSet);
					}
				}
			}
			
		}
	}
	printf("SHIT DONT WORK DAWG\n");
	return -1;
	
}

int isInSet(Node testNode, Node* testSet){
	int z = 0;
	while(testSet[z].x != INF){
		if(testNode.x == testSet[z].x && testNode.y == testSet[z].y){
			return 1;
		}
	}
	return 0;
}

int lowestFScore(Node* setToCheck, int fScoreTable[X_SIZE][Y_SIZE]){
	int i=0;
	int minIndex = INF;
	int minVal = INF;
	while(setToCheck[i].x != INF){
		if(fScoreTable[setToCheck[i].x][setToCheck[i].y] < minVal){
			minVal = fScoreTable[setToCheck[i].x][setToCheck[i].y];
			minIndex = i;
		}
		i++;
	}
	return minIndex;
}

Node nodePopNum(Node* nodeArray, int index){
	Node temp;
	temp.x = nodeArray[index].x;
	temp.y = nodeArray[index].y;
	int i=index;
	while(nodeArray[i+1].x != INF){
		nodeArray[i].x = nodeArray[i+1].x;
		nodeArray[i].y = nodeArray[i+1].y;
		i++;
	}
	nodeArray[i].x = INF;
	nodeArray[i].y = INF;
	return temp;
}

Node nodePop(Node* nodeArray){
	int i=0;
	while(nodeArray[i].x != INF){i++;}
	Node temp;
	temp.x = nodeArray[i-1].x;
	temp.y = nodeArray[i-1].y;
	nodeArray[i-1].x = INF;
	nodeArray[i-1].y = INF;
	return temp;
}

void nodePush(Node data, Node* nodeArray){
	int i=0;
	while(i<(X_SIZE*Y_SIZE) && nodeArray[i].x != INF){i++;}
	nodeArray[i] = data;
}

//Helper Function to return Heuristic Cost between two arbitrary points
int hScore(int xStart, int yStart, int xEnd, int yEnd){
	int temp1 = xEnd - xStart;
	if(temp1 < 0){
		temp1 = -temp1;
	}
	int temp2 = yEnd - yStart;
	if(temp2 < 0){
		temp2 = -temp2;
	}
	
	return temp1 + temp2;
}


//This might work, won't be able to test until further functionality

//Returns a path in an array of Node's once algorithm is finished

/*Node**/void makePath(Node** cameFrom, Node* current){
	//Node path[X_SIZE * Y_SIZE];
	Node temp;
	Node clearNode;
	clearNode.x = INF;
	clearNode.y = INF;
	temp.x = current->x;
	temp.y = current->y;
	int i = 0;
	for(i=0;i<X_SIZE * Y_SIZE;i++){
		globalPath[i] = clearNode;
	}
	i = 0;
	globalPath[i] = temp;
	i++;
	while(cameFrom[temp.x][temp.y].x != INF){
		int xTemp = temp.x;
		int yTemp = temp.y;
		temp.x = cameFrom[xTemp][yTemp].x;
		temp.y = cameFrom[xTemp][yTemp].y;
		globalPath[i] = temp;
		i++;
	}
	//return path;
}




int main(){
	Node start;
	Node end;
	start.x = 0;
	start.y = 0;
	end.x = 9;
	end.y = 9;
	if(1==AStar(start,end)){
		printPath();
	}
	else{
		printf("AStar Didn't work, PANIC!\n");
	}
}
