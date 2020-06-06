#include "Node.h"

Node* nodeConstructor(Node* derivedNode)
{
    Node* temp = malloc(sizeof(struct Node));
    temp->getKeyFromNode = derivedNode->getKeyFromNode; 
    temp->data = derivedNode->data;

    return temp; 
}

//This seems dumb. I will have to be in charge of 
//remembering which Nodes are intNodes and which 
//Nodes are other kinds of Nodes...

int getKeyFromIntNode(Node* inNode)
{
    return *((int*)inNode->data); 
}

/*
int getKeyFromIntervalNode(Node* intervalnode)
{
    return ((int*)(intervalnode->data))[1]; 
}
*/


intNode* intNodeConstructor(int _payload)
{   
    intNode* tempIntNode = malloc(sizeof(intNode)); 
    tempIntNode->data = (int*)malloc(sizeof(int));
    *((int*)(tempIntNode->data)) = _payload;
    tempIntNode->getKeyFromNode = getKeyFromIntNode;

    return tempIntNode;
}
/*
intervalNode* intervalNodeConstructor(int s, int e)
{
    Node* tempNode = malloc(sizeof(Node));
    tempNode->data = (int*)malloc(2*sizeof(int));
    ((int*)(tempNode->data))[0] = s;
    ((int*)(tempNode->data))[1] = e;
    tempNode->getKeyFromNode = getKeyFromIntervalNode;

    return tempNode;
}
*/

int main(int argc, char** argv)
{
    intNode* intNode1 = intNodeConstructor(7);
    Node* intNodeNode1 = nodeConstructor((Node*)intNode1);
   // Node* intervalNode1 = intervalNodeConstructor(3, 10);
    printf("intNode 1's key is %d", intNodeNode1->getKeyFromNode(intNodeNode1));
    
    
    //printf("intervalNode1's key is %d", intervalNode1->getKeyFromNode(intervalNode1));
}

