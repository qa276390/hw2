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
bool intersect1D(double ,double,double,double);
bool intersect(Node*,Node*,Node*,Node*);
void concave(int pos,int neg,double PArea,double NArea,Poly* poly);
void show(Poly* poly);

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
	
	}
	for(int idx=0;idx<num;idx++){
		
		Node *tmpNode=polylist[idx].getstart();
		bool intersects=false;
		
		tmpNode=polylist[idx].getstart();
		Node* itmpNode;
		for(int jdx=0;jdx<polylist[idx].getN();jdx++)
		{	
			Node* itmpNode=polylist[idx+1].getstart();
			for(int kdx=0;kdx<polylist[idx+1].getN();kdx++)
			{
				if(intersect(tmpNode,tmpNode->nextNode,itmpNode,itmpNode->nextNode))
				{
					cout<<"Intersection"<<endl;
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
	/*	
	if(poly->simple==false)
	{
		cout<<"\n(a) This polygon is not a simple polygon."<<endl;
		cout<<"(b) Intersected Edges:"<<poly->intersects<<endl;
		
	}
	else
	{*/
		//cout<<"\n(a) This polygon is a simple polygon."<<endl;
		if(poly->concave==true)
		{
			cout<<"\n(a) Concave.\n(b) ";
			Node *tmpNode=poly->getstart();
			int count=0;
			for(int idx=0;idx<poly->getN();idx++)
			{
				if(tmpNode->getcavepoint()==1)
				{
					if(count)
						cout<<",";
						
					cout<<tmpNode->NO;
					count++;
				}
				tmpNode=tmpNode->nextNode;
			}
			cout<<"\n";
		}
		else
		{
			cout<<"\n(a) Convex. \n";
			cout<<"(b) \n";
		}
		if(poly->simple==false)
		{
			cout<<"(c) Not simple \n";
			cout<<"(d) "<<poly->intersects<<endl;	
		}
		else
		{
			cout<<"(c) Simple"<<endl;
			cout<<"(d) "<<endl;
		}
			
	//}

}
void concave(int pos,int neg,double PArea,double NArea,Poly* poly)
{
	int cavesign;

	if(pos<3||neg<3)
	{cavesign=(pos>neg)?-1:1;}
	else
	{cavesign=(PArea>NArea)?-1:1;}
	Node* tmpNode=poly->getstart();
	for(int jdx=0;jdx<poly->getN();jdx++)
	{	
		if(tmpNode->getoutter()*cavesign>0)
		{
			tmpNode->setcavepoint(1);
			poly->concave=true;
		}
		tmpNode=tmpNode->nextNode;
		
	}
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
