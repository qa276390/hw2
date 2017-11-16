#include <iostream>
#include <string>
#include <stdio.h>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <iomanip>
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
bool Inside(Poly*,Poly*);
void showNode(Node *tempNode);
int AorB(Poly* polylist,Poly* poly);
double dot(Node*,Node*);
double cross(Node*,Node*);
int AminusBaround(Poly* polylist,Poly** poly);
void AminusB(Poly* polylist,Node* startNodei,Poly* poly);
int AandB(Poly*,Poly*);

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
			xed=xnew;
			yed=ynew;
			tmNode=tmNode->nextNode;
			tmNode->lastNode=oldNode;
		}
		tmNode=tmNode->lastNode;
		tmNode->setvec(tmNode->nextNode->x-tmNode->x,tmNode->nextNode->y-tmNode->y);
	
	}
	//bool inside=Inside(polylist);
	for(int idx=0;idx<num;idx++){
		
		Node *tmpNode=polylist[idx].getstart();
		bool intersects=false;
	//	cout<<"1"<<endl;	
		tmpNode=polylist[idx].getstart();
		Node* itmpNode;
		for(int jdx=0;jdx<polylist[idx].getN()*2;jdx++)
		{	
	//		cout<<"2"<<endl;	
			Node* itmpNode=polylist[idx+1].getstart();
			for(int kdx=0;kdx<polylist[idx+1].getN()*2;kdx++)
			{
				if(intersect(tmpNode,tmpNode->nextNode,itmpNode,itmpNode->nextNode))
				{
					intersects=true;	
					bool add=false,iadd=false;
	//				cout<<"4"<<endl;	
					Node *intersectNode=intersection(tmpNode,tmpNode->nextNode,itmpNode,itmpNode->nextNode);
					//showNode(intersectNode);
					//cout<<endl;
					if(!(*intersectNode==tmpNode)&&!(*intersectNode==tmpNode->nextNode))
					{
						//cout<<"1"<<endl;
						Node *iNode=new Node(intersectNode);
						iNode->vecx=tmpNode->vecx;
						iNode->vecy=tmpNode->vecy;
						iNode->nextNode=tmpNode->nextNode;
						iNode->lastNode=tmpNode;
						tmpNode->nextNode->lastNode=iNode;
						tmpNode->nextNode=iNode;
						add=true;
					}	
					if(!(*intersectNode==itmpNode)&&!(*intersectNode==itmpNode->nextNode))
					{
						//cout<<"2"<<endl;
						Node *inNode=new Node(intersectNode);
						inNode->vecx=itmpNode->vecx;
						inNode->vecy=itmpNode->vecy;
						inNode->nextNode=itmpNode->nextNode;
						inNode->lastNode=itmpNode;
						itmpNode->nextNode->lastNode=inNode;
						itmpNode->nextNode=inNode;
						iadd=true;
					}
					if(add==true&&iadd==true)
					{	tmpNode->nextNode->intersectNode=itmpNode->nextNode;
						tmpNode->nextNode->intersect=true;
						itmpNode->nextNode->intersectNode=tmpNode->nextNode;
						itmpNode->nextNode->intersect=true;
					}
					if(add==true&&iadd==false)
					{
						itmpNode->nextNode->intersectNode=tmpNode->nextNode;
						itmpNode->nextNode->intersect=true;
						if(*intersectNode==itmpNode)
						{
							tmpNode->nextNode->intersectNode=itmpNode;
							tmpNode->nextNode->intersect=true;
						}else
						{
							tmpNode->nextNode->intersectNode=itmpNode->nextNode;
							tmpNode->nextNode->intersect=true;
						}
					}
					if(add==false&&iadd==true)
					{
						tmpNode->nextNode->intersectNode=itmpNode->nextNode;
						tmpNode->nextNode->intersect=true;
						if(*intersectNode==tmpNode){
							itmpNode->nextNode->intersectNode=tmpNode;
							itmpNode->nextNode->intersect=true;
						}else{
							itmpNode->nextNode->intersectNode=tmpNode->nextNode;
							itmpNode->nextNode->intersect=true;
						}
					}
					if(add==false&&iadd==false)
					{
						if(*intersectNode==tmpNode&&*intersectNode==itmpNode)
						{
							itmpNode->intersectNode=tmpNode;
							itmpNode->intersect=true;
							tmpNode->intersectNode=itmpNode;
							tmpNode->intersect=true;
						}	
						else if(*intersectNode==tmpNode&&*intersectNode==itmpNode->nextNode)
						{
							tmpNode->intersectNode=itmpNode->nextNode;
							itmpNode->nextNode->intersectNode=tmpNode;
							tmpNode->intersect=true;
							itmpNode->nextNode->intersect=true;
						}
						else if(*intersectNode==tmpNode->nextNode&&*intersectNode==itmpNode)
						{
							itmpNode->intersectNode=tmpNode->nextNode;
							tmpNode->nextNode->intersectNode=itmpNode;
						
							tmpNode->nextNode->intersect=true;
							itmpNode->intersect=true;
						}else if(*intersectNode==tmpNode->nextNode&&*intersectNode==itmpNode->nextNode)
						{
							itmpNode->nextNode->intersectNode=tmpNode->nextNode;
							tmpNode->nextNode->intersectNode=itmpNode->nextNode;
						
							itmpNode->nextNode->intersect=true;
							tmpNode->nextNode->intersect=true;
						}
					
					}
				
				}
				itmpNode=itmpNode->nextNode;

			}	
			tmpNode=tmpNode->nextNode;
		}
		//show(&polylist[idx]);	
	}
	//Node** Nodelist=new Node*[2*(polylist[0].getN()+polylist[1].getN())];
	Poly *poly_0=new Poly();
	cout<<"OP      0"<<endl;
	int k=AandB(polylist,poly_0);
	show(poly_0);
	
	Poly *poly_1=new Poly();
	cout<<"OP      1"<<endl;
	AorB(polylist,poly_1);
	show(poly_1);

	Poly **poly_2=new Poly*[50];
	for(int i=0;i<50;i++){poly_2[i]=new Poly();}
	cout<<"OP      2"<<endl;
	int ck=AminusBaround(polylist,poly_2);
	//show(poly_2);
	for(int i=0;i<ck;i++){
		if(poly_2==NULL)
			break;
		else 
			show(poly_2[i]);}
} 
int AandB(Poly* polylist,Poly* poly)
{
	bool outputstart=false;
	int idx;
	Node* endNode;
	Node* startNode;
	Node* endNode2;
	Node* tmpNode;
	if(!Inside(&polylist[0],&polylist[1]))
		startNode=polylist[1].getstart();
	else
		startNode=polylist[0].getstart();
	tmpNode=startNode;
//	cout<<"do!"<<endl;
	do{
		if(tmpNode->intersect&&outputstart==false)
		{	outputstart=true;endNode=tmpNode;endNode2=tmpNode->intersectNode;}
		if(outputstart==true)
		{
			if(tmpNode->intersect&&(cross(tmpNode,tmpNode->intersectNode)==0)&&(dot(tmpNode,tmpNode->intersectNode)<0))
			{
				if(tmpNode->nextNode->intersect)
				{	endNode=tmpNode->nextNode->nextNode;}
				else
				{	endNode=tmpNode->nextNode;}
			}
			if(tmpNode->intersect&&(cross(tmpNode,tmpNode->intersectNode)>0))
			{
			//	cout<<"-----TURN-----"<<endl;
				tmpNode=tmpNode->intersectNode;
			}
			
			poly->Poly_append(tmpNode);
			idx++;
			//showNode(tmpNode);
		}
		tmpNode=tmpNode->nextNode;
		if(tmpNode==startNode&&outputstart==false)
		{
			//showNode(tmpNode);
			poly->Poly_append(tmpNode);
			idx++;
			tmpNode=startNode->nextNode;
			outputstart=true;
			endNode=startNode;
		}


	}while(tmpNode!=endNode&&tmpNode!=endNode2);

	return idx;
}
int AorB(Poly* polylist,Poly* poly)
{
	int idx=0;
	Node* tmpNode;
	Node* startNode;
	if(Inside(&polylist[0],&polylist[1]))
	{	startNode=polylist[1].getstart();
	}else{
		startNode=polylist[0].getstart();
	}
	tmpNode=startNode;
	do{
		if(tmpNode->intersect&&(cross(tmpNode,tmpNode->intersectNode)<0))
		{
			tmpNode=tmpNode->intersectNode;
		}
		//showNode(tmpNode);
		poly->Poly_append(tmpNode);
		idx++;
		tmpNode=tmpNode->nextNode;
	}while(tmpNode!=startNode);
	return idx;
}
int AminusBaround(Poly* polylist,Poly** poly)
{
	int idx=0;
	Node* tmpNode=polylist[0].getstart();
	do{
		if(!(tmpNode->shown)&&!(tmpNode->intersect))
		{	
			AminusB(polylist,tmpNode,poly[idx]);
			idx++;
		}
		tmpNode=tmpNode->nextNode;
	}while(tmpNode!=polylist[0].getstart());
	return idx;	
}
void AminusB(Poly* polylist,Node* startNode,Poly* poly)
{
	
	//cout<<"*** START FORM ***"<<endl;
	//showNode(startNode);
	//cout<<"*** ========== ***"<<endl;
        bool ccl=true;
	bool turn=false;
	Node* endNode=startNode;
	//Node* startNode=startNode;
	Node* tmpNode=startNode;
	do{
		if(tmpNode->intersect)
		{
			ccl=!ccl;
			turn=true;
			tmpNode=tmpNode->intersectNode;
		}
		if(ccl==true)	
			tmpNode=tmpNode->nextNode;
		else
			tmpNode=tmpNode->lastNode;

		tmpNode->shown=true;
		poly->Poly_append(tmpNode);
		//showNode(tmpNode);
		if(tmpNode==polylist[0].getstart()&&turn==false)
		{	//showNode(polylist[1].getstart());
			tmpNode=polylist[1].getstart()->lastNode;
			tmpNode->shown=true;
			//showNode(tmpNode);
			poly->Poly_append(tmpNode);
			ccl=false;
			endNode=polylist[1].getstart();
		}
	}while(tmpNode!=endNode);
}

void show(Poly* poly)
{
	//cout<<"--------SHOW--------"<<endl;
	cout<<"N       "<<(poly->n)+1<<endl;
	Node* tempNode=poly->getstart();
	do{
		showNode(tempNode);
		/*if(tempNode->intersectNode!=NULL)
		{	cout<<"* -> ";showNode(tempNode->intersectNode);cout<<endl;}
		else
			cout<<endl;
	*/
		tempNode=tempNode->nextNode;
	}while(tempNode!=poly->getstart());
	//showNode(tempNode
}
void showNode(Node *tempNode)
{
	
	cout<<"x y     "<<fixed<<setprecision(3)<<tempNode->getx()<<" "<<tempNode->gety()<<endl;

}
bool Inside(Poly* polyA,Poly *polyB)
{
	bool inside=false;
	
	Node *tmNode=polyA->getstart();
	for(int i=0;i<polyA->getN();i++)
	{
		if(in_polygon(tmNode,polyB))
		{	
			tmNode->setin();
			inside=true;
		}
		tmNode=tmNode->nextNode;
	}
	
	return inside;
}
double cross(Node *a,Node *b)
{
	return ((a->vecx)*(b->vecy))-((a->vecy)*(b->vecx));
}
double dot(Node *a,Node *b)
{ 
	return ((a->vecx)*(b->vecx))+((a->vecy)*(b->vecy));
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
	//cout<<"a"<<endl;
	Node* a = *a2 - a1;
	Node* b = *b2 - b1;
	Node* s = *b1 - a1;
	//cout<<"b"<<endl;
    	float c1 = cross(new Node(0,0),a, b);
   	float c2 = cross(new Node(0,0),s, b);
    	float c4 = cross(new Node(0,0),s, a); 
 	//cout<<"c"<<endl;
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
		if((tmp->gety()>n->gety())!=(tmp->lastNode->gety()>n->gety()) && (n->getx() <(tmp->lastNode->getx()-tmp->getx())*(n->gety()-tmp->gety())/(tmp->lastNode->gety()-tmp->gety())+tmp->getx()))
		{	c=!c;}
		tmp=tmp->nextNode;
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
bool Node::operator==(Node* n2)
{
	
	if(this->getx()==n2->getx()&& this->gety()==n2->gety())
		return true;
	else
		return false;
}
