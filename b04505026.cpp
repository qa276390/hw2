#include <iostream>
#include <string>
#include <stdio.h>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include "Poly.h"
using namespace std;

#define PI 3.1415926

bool Simple(Poly* pl);
float cross(Node* o,Node* a,Node* b);
float dot(Node* o,Node* a,Node* b);
bool intersect1D(double ,double,double,double);
bool intersect(Node*,Node*,Node*,Node*);
void concave(int pos,int neg,double PArea,double NArea,Poly* poly);
Node* intersection(Node *a1,Node* a2,Node* b1,Node* b2);
void show(Poly* poly);
bool in_polygon(Node* n,Poly* p);

int main(){
	int num,nNode;
	cout<<"How many Polygon\n";
	cin>>num;
	
	string str1,str2;
	Poly *polylist= new Poly [num];
	for(int idx=0;idx<num;idx++){
		cout<<"How many Nodes\n";
		cin>>nNode;
		polylist[idx].setN(nNode);
		polylist[idx].start=new Node();
		Node *tmNode=polylist[idx].getstart();
		double xed,yed,xnew,ynew;
		for(int jdx=0;jdx<polylist[idx].getN();jdx++){
			cout<<"Input your coordinate \"x y\" \n";
			cin>>str1>>str2;
			xnew=atof(str1.c_str());
			ynew=atof(str2.c_str());
			tmNode->setNode(xnew,ynew);
			tmNode->NO=jdx;
			if(jdx!=0)
			{	tmNode->lastNode->setvec(xnew-xed,ynew-yed);}
			Node *oldNode=tmNode;
			if(jdx==nNode-1)
			{tmNode->nextNode=polylist[idx].getstart();}
			else
			{tmNode->nextNode=new Node();}
			if(idx==1)
			{
				in_polygon(tmNode,&polylist[0]);
				cout<<"Inside"<<endl;
			}
			xed=xnew;
			yed=ynew;
			tmNode=tmNode->nextNode;
			tmNode->lastNode=oldNode;
		}
	
	}
	for(int idx=0;idx<num;idx++){
		
		Node *tmpNode=polylist[idx].getstart();
		bool intersects=false;
	//	cout<<"1"<<endl;	
		tmpNode=polylist[idx].getstart();
		Node* itmpNode;
		for(int jdx=0;jdx<polylist[idx].getN();jdx++)
		{	
	//		cout<<"2"<<endl;	
			Node* itmpNode=polylist[idx+1].getstart();
			for(int kdx=0;kdx<polylist[idx+1].getN();kdx++)
			{
	//			cout<<"3"<<endl;	
				if(intersect(tmpNode,tmpNode->nextNode,itmpNode,itmpNode->nextNode))
				{
	//				cout<<"4"<<endl;	
					Node *intersectNode=intersection(tmpNode,tmpNode->nextNode,itmpNode,itmpNode->nextNode);
					cout<<"Intersection:"<<intersectNode->getx()<<","<<intersectNode->gety()<<endl;
				}
				itmpNode=itmpNode->nextNode;

			}	
			tmpNode=tmpNode->nextNode;
		}
		
		//show(&polylist[idx]);	
	}		
} 
void show(Poly* poly)
{

}
float dot(Node* o,Node* a,Node* b)
{
	return (a->getx()-o->getx())*(b->getx()-o->getx())+(a->gety()-o->gety())*(b->gety()-o->gety());
}
float cross(Node* o,Node* a,Node* b)
{
	return (a->getx()-o->getx())*(b->gety()-o->gety())-(a->gety()-o->gety())*(b->getx()-o->getx());
}
bool intersect1D(double a1,double a2,double b1,double b2)
{
	if(a1>a2){
		double tmp=a1;
		a1=a2;
		a2=tmp;
	}
	if(b1>b2){
		double tmp=b1;
		b1=b2;
		b2=tmp;
	}
	return max(a1,b1) <= min(a2,b2);
}
bool intersect(Node *a1,Node *a2,Node *b1,Node *b2)
{
	return intersect1D(a1->getx(),a2->getx(),b1->getx(),b2->getx())
	&& intersect1D(a1->gety(),a2->gety(),b1->gety(),b2->gety())
	&& cross(a1,a2,b1)*cross(a1,a2,b2)<=0
	&& cross(b1,b2,a1)*cross(b1,b2,a2)<=0;

}
bool intersect(Node *p,Node *p1,Node *p2)
{
	return cross(p,p1,p2) == 0 && dot(p,p1,p2) <= 0;
}
Node* intersection(Node *a1,Node* a2,Node* b1,Node* b2)
{
	cout<<"a"<<endl;
	Node* a = *a2 - a1;
	Node* b = *b2 - b1;
	Node* s = *b1 - a1;
	cout<<"b"<<endl;
    	float c1 = cross(new Node(0,0),a, b);
   	float c2 = cross(new Node(0,0),s, b);
    	float c4 = cross(new Node(0,0),s, a); 
 	cout<<"c"<<endl;
    	if (c1 < 0){c1 = -c1, c2 = -c2, c4 = -c4;}
 
    	if (c1 != 0 && c2 >= 0 && c2 <= c1 && c4 >= 0 && c4 <= c1)
        	return *a1 + (*a * (c2 / c1));
    	else
        	return NULL; 
}
bool in_polygon(Node* n,Poly* p)
{
	int N=p->getN();
	bool c=false;
	Node* tmp=p->getstart();
	for(int i=0;i<=N;i++)
	{
		if((tmp->gety()>n->gety())!=(tmp->lastNode->gety()>n->gety()) && (n->getx() <(tmp->lastNode->getx()-tmp->getx())*(n->gety()-tmp->gety())/(tmp->lastNode->gety()-tmp->gety())+n->getx()))
			c=!c;
	}
	return c;
}

Node* Node::operator-(Node* n2)
{
	Node* newNode=new Node();
	newNode->setNode(this->getx()-n2->getx(),this->gety()-n2->gety());
	
	return newNode;
}
Node* Node::operator+(Node* n2)
{
	Node* newNode=new Node();
	newNode->setNode(this->getx()+n2->getx(),this->gety()+n2->gety());
	
	return newNode;
}
Node* Node::operator*(const float& l)
{
	Node* newNode=new Node();
	newNode->setNode(this->getx()*l,this->gety()*l);
	
	return newNode;
}
