#include <iostream>
#include <string>
using namespace std;

class Node{
public:
	double x;
	double y;
	int cavepoint;
	double vecx;
	double vecy;
	double outter;
	double angle;
	bool inside;
	bool intersect;
	bool shown;


	int NO;
	Node(){shown=false;inside=false;x=0;y=0;intersectNode=NULL;intersect=false;}
	Node(float a,float b){shown=false;inside=false;x=a;y=b;intersectNode=NULL;intersect=false;}
	Node(Node* n){shown=n->shown;vecx=n->vecx;vecy=n->vecy;inside=n->inside;x=n->getx();y=n->gety();vecx=n->getvecx();vecy=n->getvecy();intersect=n->intersect;}

	Node * nextNode;
	Node * lastNode;
	Node * intersectNode;

	void setNode(double xn,double yn)
	{x=xn;y=yn;}	
	void setvec(double xn,double yn)
	{vecx=xn;vecy=yn;}
	void setoutter(double i){outter=i;}
	double getoutter(){return outter;}
	double getvecx(){return vecx;}
	double getvecy(){return vecy;}
	double getx(){return x;}
	double gety(){return y;}
	bool getin(){return inside;}
	bool setin(){inside=true;}
	void setcavepoint(int a){cavepoint=a;}
	double getcavepoint(){return cavepoint;}
	void setangle(double a){angle=a;}
	double getangle(){return angle;}
	Node* operator-(Node*);
	Node* operator+(Node*);
	Node* operator*(const float&);
	bool operator==(Node*);
};


class Poly{
public:
	
	bool concave;
	int n;
	Node *start;
	bool simple;
	Poly(){start=NULL;simple=true;}
	void Poly_append(Node* nx){
		Node* node=new Node(nx);
		if(start==NULL){start=node;start->nextNode=start;start->lastNode=start;}
		else{
			Node* endNode=start->lastNode;
			start->lastNode=node;
			endNode->nextNode=node;
			node->lastNode=endNode;
			node->nextNode=start;
			n++;
		}
	}
	int getN(){return n;}
	void setN(int nN){n=nN;}
	Node* getstart(){return start;}
	string intersects;
};
