
#include<iostream>
using namespace std;

 struct x_and_y{
	 int x;
	 int y;
 };

class Graph
{
public:
	vector<Vector3>path_nodes;
	Vector3 Nodes[192][64];
	bool AdjacentMatrix[192][64];
	Vector3 GetNearestNode(int x,int z)
	{
		Vector3 P;
		P.y = 0;
		int zIndex = (z-100)/16;
		int xIndex = (x+500)/16;
		P.x = xIndex;
		P.z = zIndex;
		return P;
	}
	void InitializeNodes()
	{
		for(int i = 0 ; i < 192 ; i++)
			for(int j = 0 ; j < 64 ; j++)
			{
				Nodes[i][j].x = -1;
				Nodes[i][j].y = -1;
				Nodes[i][j].z = -1;
			}
	}
	void constructAdjacentMatrix()
	{
		for(int i = 0 ; i < 192 ; i++)
			for(int j = 0 ; j < 64 ; j++)
				AdjacentMatrix[i][j] = 0;
		for(int i = 0 ; i < 192 ; i++)
			for(int j = 0 ; j < 64 ; j++)
			{
				//upper row
				if(i-1 >= 0 && j-1 >= 0)
					if(Nodes[i-1][j-1].x != -1)
						AdjacentMatrix[i-1][j-1] = 1;
				if(i-1 >= 0)
					if(Nodes[i-1][j].x != -1)
						AdjacentMatrix[i-1][j] = 1;
				if(i-1 >= 0 && j+1 <= 63)
					if(Nodes[i-1][j+1].x != -1)
						AdjacentMatrix[i-1][j+1] = 1;
				//current row
				if(j-1 >= 0)
					if(Nodes[i][j-1].x != -1)
						AdjacentMatrix[i][j-1] = 1;
				if(j+1 <= 63)
					if(Nodes[i][j+1].x != -1)
						AdjacentMatrix[i][j+1] = 1;
				//next row
				if(i+1 <= 191 && j-1 >= 0)
					if(Nodes[i+1][j-1].x != -1)
						AdjacentMatrix[i+1][j-1] = 1;
				if(i+1 <= 191)
					if(Nodes[i+1][j].x != -1)
						AdjacentMatrix[i+1][j] = 1;
				if(i+1 <= 191 && j+1 <= 63)
					if(Nodes[i+1][j+1].x != -1)
						AdjacentMatrix[i+1][j+1] = 1;

			}
	}
	vector<Vector3> A_star(Vector3 start,Vector3 end ) //start=enemy & end=palyer
	{
		Vector3 d;
		float min=99999999999;
		Vector3 index;
		float absolute;
		//upper row
		if(start.z-1 >= 0 && start.x-1 >= 0)
			if(Nodes[(int)start.z-1][(int)start.x-1].x != -1)
				d=(Nodes[(int)end.z][(int)end.x]-Nodes[(int)start.z-1][(int)start.x-1]);
		absolute=fabs(d.Magnitude());
		if(min>absolute){
			min=absolute;
			if(min==0)
				return path_nodes;
			index.x=start.x-1;
			index.z=start.z-1;}

		if(start.z-1 >= 0)
			if(Nodes[(int)start.z-1][(int)start.x].x != -1)
				d=Nodes[(int)end.z][(int)end.x]- Nodes[(int)start.z-1][(int)start.x];
		absolute=fabs(d.Magnitude());
		if(min>absolute){
			min=absolute;
			if(min==0)
				return path_nodes;
			index.x=start.x;
			index.z=start.z-1;}


		if(start.z-1 >= 0 && start.x+1 <= 63)
			if(Nodes[(int)start.z-1][(int)start.x+1].x != -1)
				d=Nodes[(int)end.z][(int)end.x]-Nodes[(int)start.z-1][(int)start.x+1];
		absolute=fabs(d.Magnitude());
		if(min>absolute){
			min=absolute;
			if(min==0)
				return path_nodes;
			index.x=start.x+1;
			index.z=start.z-1;}
		//current row
		if(start.x-1 >= 0)
			if(Nodes[(int)start.z][(int)start.x-1].x != -1)
				d=Nodes[(int)end.z][(int)end.x]-Nodes[(int)start.z][(int)start.x-1];
		absolute=fabs(d.Magnitude());
		if(min>absolute){
			min=absolute;
			if(min==0)
				return path_nodes;
			index.x=start.x-1;
			index.z=start.z;}

		if(start.x+1 <= 63)
			if(Nodes[(int)start.z][(int)start.x+1].x != -1)
				d=Nodes[(int)end.z][(int)end.x]-Nodes[(int)start.z][(int)start.x+1];
		absolute=fabs(d.Magnitude());
		if(min>absolute){
			min=absolute;
			if(min==0)
				return path_nodes;
			index.x=start.x+1;
			index.z=start.z;}
		//next row
		if(start.z+1 <= 191 && start.x-1 >= 0)
			if(Nodes[(int)start.z+1][(int)start.x-1].x != -1)
				d=Nodes[(int)end.z][(int)end.x]-Nodes[(int)start.z+1][(int)start.x-1];
		absolute=fabs(d.Magnitude());
		if(min>absolute){
			min=absolute;
			if(min==0)
				return path_nodes;
			index.x=start.x-1;
			index.z=start.z+1;}

		if(start.z+1 <= 191)
			if(Nodes[(int)start.z+1][(int)start.x].x != -1)
				d=Nodes[(int)end.z][(int)end.x]-Nodes[(int)start.z+1][(int)start.x];
		absolute=fabs(d.Magnitude());
		if(min>absolute){
			min=absolute;
			if(min==0)
				return path_nodes;
			index.x=start.x;
			index.z=start.z+1;}

		if(start.z+1 <= 191 && start.x+1 <= 63)
			if(Nodes[(int)start.z+1][(int)start.x+1].x != -1)
				d=Nodes[(int)end.z][(int)end.x]-Nodes[(int)start.z+1][(int)start.x+1];
		absolute=fabs(d.Magnitude());
		if(min>absolute){
			min=absolute;
			if(min==0)
				return path_nodes;
			index.x=start.x+1;
			index.z=start.z+1;}
		Vector3 Value = Vector3(Nodes[(int)index.z][(int)index.x].x-500,0,Nodes[(int)index.z][(int)index.x].z+100);
		path_nodes.push_back(Value);

		return A_star(index,end );
	}
	Vector3 GetNextNode(Vector3 start,Vector3 end)
	{
		Vector3 d;
		Vector3 Null(0,0,0);
		float min=99999999999;
		Vector3 index;
		float absolute;
		//upper row
		if(start.z-1 >= 0 && start.x-1 >= 0)
			if(Nodes[(int)start.z-1][(int)start.x-1].x != -1)
				d=(Nodes[(int)end.z][(int)end.x]-Nodes[(int)start.z-1][(int)start.x-1]);
		absolute=fabs(d.Magnitude());
		if(min>absolute){
			min=absolute;
			if(min==0)
				return Null;
			index.x=start.x-1;
			index.z=start.z-1;}

		if(start.z-1 >= 0)
			if(Nodes[(int)start.z-1][(int)start.x].x != -1)
				d=Nodes[(int)end.z][(int)end.x]- Nodes[(int)start.z-1][(int)start.x];
		absolute=fabs(d.Magnitude());
		if(min>absolute){
			min=absolute;
			if(min==0)
				return Null;
			index.x=start.x;
			index.z=start.z-1;}


		if(start.z-1 >= 0 && start.x+1 <= 63)
			if(Nodes[(int)start.z-1][(int)start.x+1].x != -1)
				d=Nodes[(int)end.z][(int)end.x]-Nodes[(int)start.z-1][(int)start.x+1];
		absolute=fabs(d.Magnitude());
		if(min>absolute){
			min=absolute;
			if(min==0)
				return Null;
			index.x=start.x+1;
			index.z=start.z-1;}
		//current row
		if(start.x-1 >= 0)
			if(Nodes[(int)start.z][(int)start.x-1].x != -1)
				d=Nodes[(int)end.z][(int)end.x]-Nodes[(int)start.z][(int)start.x-1];
		absolute=fabs(d.Magnitude());
		if(min>absolute){
			min=absolute;
			if(min==0)
				return Null;
			index.x=start.x-1;
			index.z=start.z;}

		if(start.x+1 <= 63)
			if(Nodes[(int)start.z][(int)start.x+1].x != -1)
				d=Nodes[(int)end.z][(int)end.x]-Nodes[(int)start.z][(int)start.x+1];
		absolute=fabs(d.Magnitude());
		if(min>absolute){
			min=absolute;
			if(min==0)
				return Null;
			index.x=start.x+1;
			index.z=start.z;}
		//next row
		if(start.z+1 <= 191 && start.x-1 >= 0)
			if(Nodes[(int)start.z+1][(int)start.x-1].x != -1)
				d=Nodes[(int)end.z][(int)end.x]-Nodes[(int)start.z+1][(int)start.x-1];
		absolute=fabs(d.Magnitude());
		if(min>absolute){
			min=absolute;
			if(min==0)
				return Null;
			index.x=start.x-1;
			index.z=start.z+1;}

		if(start.z+1 <= 191)
			if(Nodes[(int)start.z+1][(int)start.x].x != -1)
				d=Nodes[(int)end.z][(int)end.x]-Nodes[(int)start.z+1][(int)start.x];
		absolute=fabs(d.Magnitude());
		if(min>absolute){
			min=absolute;
			if(min==0)
				return Null;
			index.x=start.x;
			index.z=start.z+1;}

		if(start.z+1 <= 191 && start.x+1 <= 63)
			if(Nodes[(int)start.z+1][(int)start.x+1].x != -1)
				d=Nodes[(int)end.z][(int)end.x]-Nodes[(int)start.z+1][(int)start.x+1];
		absolute=fabs(d.Magnitude());
		if(min>absolute){
			min=absolute;
			if(min==0)
				return Null;
			index.x=start.x+1;
			index.z=start.z+1;}
		Vector3 Value = Vector3(Nodes[(int)index.z][(int)index.x].x-500,0,Nodes[(int)index.z][(int)index.x].z+100);

		return Value;
	}
};