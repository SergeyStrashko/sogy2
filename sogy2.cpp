#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Data
{
	int vertical;
	char horizontal;
	string color;
	string figure;
};

struct Table
{
	Data node;
	Table *prev, *next;
};

void Add(Table **list, Data &data)
{
	Table *temp = new Table;
	temp->node = data;
	temp->prev = nullptr;
	temp->next = *list;
	*list = temp;
}

void Add_End(Table **list, Data &data)
{
	Table *insert = new Table;
	insert->node = data;
	Table *temp = *list;
	if (!temp)
	{
		Add(list, data);
		return;
	}
	while (temp)
	{
		if (temp->next == nullptr)
		{
			temp->next = insert;
			insert->prev = temp;
			insert->next = nullptr;
		}
		temp = temp->next;
	}
}

void Create_Table(Table **list)
{
	string keys = "abcdefghi";
	Data data;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 9; j > 0; j--)
		{
			data.vertical = j;
			data.horizontal = keys[i];
			data.figure = " ";
			data.color = " ";
			Add_End(list, data);
		}
	}
}

void Show_State(Table *list)
{
	Table *temp = list;
	string keys = "abcdefghi";
	cout << "\n       Game table:\n" << endl;
	cout << "      ";
	for (int i = 9; i > 0; i--) cout << " " << i << "  ";
	cout << endl << endl;
	int j = 0;
	while (temp)
	{
		int i = 0;
		cout << "      ";
		while (i < 9)
		{
			cout << " " << temp->node.figure << temp->node.color[0] << " ";
			temp = temp->next;
			i++;
		}
		cout << "   " << keys[j] << endl;
		j++;
	}
	cout << endl;
}

void Add_One(Table *list, string figure, string color)
{
	Table *temp = list;
	int index;
	char key;
	if (figure == "K")
	{
		index = 5;
		if (color == "white") key = 'a';
		else key = 'i';
	}
	else if (figure == "B")
	{
		if (color == "white")
		{
			key = 'b';
			index = 2;
		}
		else
		{
			key = 'h';
			index = 8;
		}
	}
	else
	{
		if (color == "white")
		{
			key = 'b';
			index = 8;
		}
		else
		{
			key = 'h';
			index = 2;
		}
	}
	while (temp) {
		if (temp->node.horizontal == key)
		{
			if (temp->node.vertical == index)
			{
				temp->node.figure = figure;
				temp->node.color = color;
				return;
			}
			else temp = temp->next;
		}
		else temp = temp->next;
	}
}

void Add_Double(Table *list, string figure, string color)
{
	Table *temp = list;
	vector<int> index;
	char key;
	if (figure == "G")
	{
		index = { 4, 6 };
	}
	else if (figure == "S")
	{
		index = { 7, 3 };
	}
	else if (figure == "N")
	{
		index = { 8, 2 };
	}
	else
	{
		index = { 9, 1 };
	}
	if (color == "white") key = 'a';
	else key = 'i';
	while (temp) {
		if (temp->node.horizontal == key)
		{
			if (temp->node.vertical == index[0] || temp->node.vertical == index[1])
			{
				temp->node.figure = figure;
				temp->node.color = color;
				temp = temp->next;
			}
			else temp = temp->next;
		}
		else temp = temp->next;
	}
}

void Add_P(Table *list, string color)
{
	Table *temp = list;
	char key;
	if (color == "white") key = 'c';
	else key = 'g';
	while (temp)
	{
		if (temp->node.horizontal == key)
		{
			for (int i = 0; i < 9; i++)
			{
				temp->node.figure = "P";
				temp->node.color = color;
				temp = temp->next;
			}
			return;
		}
		else temp = temp->next;

	}
}

void Fill_White(Table *list)
{
	string color = "white";
	Add_One(list, "K", color);
	Add_One(list, "B", color);
	Add_One(list, "R", color);
	Add_Double(list, "G", color);
	Add_Double(list, "S", color);
	Add_Double(list, "L", color);
	Add_Double(list, "N", color);
	Add_P(list, color);
}

void Fill_Black(Table *list)
{
	string color = "black";
	Add_One(list, "K", color);
	Add_One(list, "R", color);
	Add_One(list, "B", color);
	Add_Double(list, "G", color);
	Add_Double(list, "S", color);
	Add_Double(list, "L", color);
	Add_Double(list, "N", color);
	Add_P(list, color);
}

void Delete(Table **list, char x, int y)
{
	Table *temp = *list;
	while (temp)
	{
		if (temp->node.horizontal == x && temp->node.vertical == y)
		{
			temp->node.figure = ' ';
			temp->node.color = ' ';
			break;
		}
		temp = temp->next;
	}
}

Table Search(Table **list, char start_x, int start_y)
{
	Table *temp = *list;
	Table *target = new Table;
	while (temp)
	{
		if (temp->node.horizontal == start_x && temp->node.vertical == start_y)
		{
			target->node = temp->node;
			break;
		}
		temp = temp->next;
	}
	return *target;
	delete target;
}

void Change(Table **list, Table *target, char target_x, int target_y)
{
	Table *temp = *list;
	while (temp)
	{
		if (temp->node.horizontal == target_x && temp->node.vertical == target_y)
		{
			temp->node.color = target->node.color;
			temp->node.figure = target->node.figure;
			break;
		}
		temp = temp->next;
	}
}

int getIndex(char value)
{
	string keys = "abcdefghi";
	for (int i = 0; i < 9; i++)
		if (keys[i] == value) return i;
	return -1;
}

bool isClearVertical(Table *list, int vertical, char horizontalFirst, char horizontalSecond)
{
	Table *temp = list;
	char first, second;
	if (getIndex(horizontalFirst) < getIndex(horizontalSecond))
	{
		first = horizontalFirst;
		second = horizontalSecond;
	}
	else
	{
		first = horizontalSecond;
		second = horizontalFirst;
	}
	while (temp)
	{
		if (temp->node.vertical == vertical)
		{
				if (getIndex(first) < getIndex(temp->node.horizontal) && getIndex(second) > getIndex(temp->node.horizontal) && temp->node.figure != " ")
					return false;
		}
		temp = temp->next;
	}
	return true;
}

string getFigure(Table *&list, int vertical, char horizontal)
{
	Table *temp = list;
	while (temp)
	{
		if (temp->node.horizontal == horizontal && temp->node.vertical == vertical) return temp->node.figure;
		temp = temp->next;
	}
	return " ";
}

bool isClearHorizontal(Table *list, char horizontal, int verticalFirst, int verticalSecond)
{
	Table *temp = list;
	int first, second;
	if (verticalFirst < verticalSecond)
	{
		first = verticalFirst;
		second = verticalSecond;
	}
	else
	{
		first = verticalSecond;
		second = verticalFirst;
	}
	while (temp)
	{
		if (temp->node.horizontal == horizontal)
		{
			if (first < temp->node.vertical && second > temp->node.vertical && temp->node.figure != " ")
				return false;
		}
		temp = temp->next;
	}
	return true;
}


bool isYour(Table **list, int vertical, char horizontal, int player)
{
	Table *temp = new Table;
	temp->node = Search(list, horizontal, vertical).node;
	if (temp->node.figure != " ")
	{
		if (player == 1 && temp->node.color == "white") return true;
		else if (player == 2 && temp->node.color == "black") return true;
		else return false;
	}
	else return false;
}

bool flag(Table *list, Table *start, char target_x, int target_y)
{
	string keys = "abcdefghi";
	int index = getIndex(start->node.horizontal);
	if (start->node.figure == "K")
	{
		if ((start->node.vertical == target_y 
			|| start->node.vertical == (target_y - 1) 
			|| start->node.vertical == (target_y + 1)) 
			&& (start->node.horizontal == target_x || keys[index + 1] == target_x || keys[index - 1] == target_x))
			return true;
		else return false;
	}
	else if (start->node.figure == "G" 
		|| start->node.figure == "+P" 
		|| start->node.figure == "+S" 
		|| start->node.figure == "+N" 
		|| start->node.figure == "+L")
	{
		if (((start->node.vertical == target_y 
			|| start->node.vertical == (target_y - 1) 
			|| start->node.vertical == (target_y + 1)) 
			&& (start->node.horizontal == target_x 
				|| (start->node.color == "white" && keys[index + 1] == target_x) 
				|| (start->node.color == "black" && keys[index - 1] == target_x))) 
			|| (start->node.vertical == target_y && (start->node.color == "white" && keys[index - 1] == target_x) 
				|| (start->node.color == "black" && keys[index + 1] == target_x)))
			return true;
		else return false;
	}
	else if (start->node.figure == "S")
	{
		if (((start->node.vertical == target_y 
			|| start->node.vertical == (target_y - 1) 
			|| start->node.vertical == (target_y + 1)) 
			&& ((start->node.color == "white" && keys[index + 1] == target_x) 
				|| (start->node.color == "black" && keys[index - 1] == target_x))) 
			|| ((start->node.vertical == target_y - 1 
				|| start->node.vertical == target_y + 1) 
				&& (start->node.color == "white" && keys[index - 1] == target_x) 
				|| (start->node.color == "black" && keys[index + 1] == target_x)))
			return true;
		else return false;
	}
	else if (start->node.figure == "L")
	{
		if (start->node.vertical == target_y 
			&& ((start->node.color == "white" 
				&& index < getIndex(target_x)) 
				|| (start->node.color == "black" 
					&& index > getIndex(target_x))) 
			&& isClearVertical(list, start->node.vertical, start->node.horizontal, target_x))
			return true;
		else return false;
	}
	else if (start->node.figure == "R")
	{
		if ((start->node.vertical == target_y 
			|| start->node.horizontal == target_x) 
			&& isClearVertical(list, start->node.vertical, start->node.horizontal, target_x) 
			&& isClearHorizontal(list, start->node.horizontal, start->node.vertical, target_y))
			return true;
		else return false;
	}
	else if (start->node.figure == "+R")
	{
		if ((start->node.vertical == target_y 
			|| start->node.horizontal == target_x) 
			|| ((start->node.vertical == target_y 
				|| start->node.vertical == (target_y - 1) 
				|| start->node.vertical == (target_y + 1)) 
				&& (start->node.horizontal == target_x 
					|| keys[index + 1] == target_x 
					|| keys[index - 1] == target_x)))
			return true;
		else return false;
	}
	else if (start->node.figure == "+B")
	{
		if (start->node.vertical > target_y && getIndex(target_x) < index)
			for (int i = start->node.vertical - 1; i >= target_y; i--)
			{
				index--;
				if (getFigure(list, i, keys[index]) != " ")
					return false;
				if (i == target_y && target_x == keys[index])
					return true;
			}
		else if (start->node.vertical < target_y && getIndex(target_x) < index)
			for (int i = start->node.vertical + 1; i <= target_y; i++)
			{
				index--;
				if (getFigure(list, i, keys[index]) != " ")
					return false;
				if (i == target_y && target_x == keys[index])
					return true;
			}
		else if (start->node.vertical > target_y && getIndex(target_x) > index)
			for (int i = start->node.vertical - 1; i >= target_y; i--)
			{
				index++;
				if (getFigure(list, i, keys[index]) != " ")
					return false;
				if (i == target_y && target_x == keys[index])
					return true;
			}
		else if (start->node.vertical < target_y && getIndex(target_x) > index)
			for (int i = start->node.vertical + 1; i <= target_y; i++)
			{
				index++;
				if (getFigure(list, i, keys[index]) != " ")
					return false;
				if (i == target_y && target_x == keys[index])
					return true;
			}
		if (((start->node.vertical + 1 == target_y || start->node.vertical - 1 == target_y) && start->node.horizontal == target_x) 
			|| ((keys[index + 1] == target_x || keys[index - 1] == target_x) && start->node.vertical == target_y))
			return true;
		else return false;
	}
	else if (start->node.figure == "B")
	{
		if (start->node.vertical > target_y && getIndex(target_x) < index)
			for (int i = start->node.vertical - 1; i >= target_y; i--)
			{
				index--;
				if (getFigure(list, i, keys[index]) != " ")
					return false;
				if (i == target_y && target_x == keys[index])
					return true;
			}
		else if (start->node.vertical < target_y && getIndex(target_x) < index)
			for (int i = start->node.vertical + 1; i <= target_y; i++)
			{
				index--;
				if (getFigure(list, i, keys[index]) != " ")
					return false;
				if (i == target_y && target_x == keys[index])
					return true;
			}
		else if (start->node.vertical > target_y && getIndex(target_x) > index)
			for (int i = start->node.vertical - 1; i >= target_y; i--)
			{
				index++;
				if (getFigure(list, i, keys[index]) != " ")
					return false;
				if (i == target_y && target_x == keys[index])
					return true;
			}
		else if (start->node.vertical < target_y && getIndex(target_x) > index)
			for (int i = start->node.vertical + 1; i <= target_y; i++)
			{
				index++;
				if (getFigure(list, i, keys[index]) != " ")
					return false;
				if (i == target_y && target_x == keys[index])
					return true;
			}
		else return false;
	}
	else if (start->node.figure == "N")
	{
		if ((start->node.vertical == target_y - 1 
			|| start->node.vertical == target_y + 1) 
			&& ((start->node.color == "white" 
				&& keys[index + 2] == target_x) 
				|| (start->node.color == "black" 
					&& keys[index - 2] == target_x)))
			return true;
		else return false;
	}
	else if (start->node.figure == "P")
	{ 
		if (start->node.vertical == target_y 
			&& ((start->node.color == "white" 
				&& keys[index + 1] == target_x) 
				|| (start->node.color == "black" 
					&& keys[index - 1] == target_x)))
			return true;
		else return false;
	}
	return false;
}

bool canYou(Table **list, int verticalFirst, char horizontalFirst, int verticalSecond, char horizontalSecond, int player)
{
	Table *start = new Table;
	Table *target = new Table;
	start->node = Search(list, horizontalFirst, verticalFirst).node;
	target->node = Search(list, horizontalSecond, verticalSecond).node;
	if (flag(*list, start, horizontalSecond, verticalSecond))
	{
		if (target->node.figure == " ") return true ;
		else if (player == 1 && target->node.color == "black")
			return true;
		else if (player == 2 && target->node.color == "white")
			return true;
		else return false;
	}
	else return false;
	delete &start;
	delete &target;
}

void Move(Table **list, char start_x, int start_y, char target_x, int target_y)
{
	Table *insert = new Table;
	insert->node = Search(list, start_x, start_y).node;
	Delete(list, insert->node.horizontal, insert->node.vertical);
	Change(list, insert, target_x, target_y);
	delete insert;
}

void showReserve(vector<string> &reserve)
{
	for(unsigned i = 0; i < reserve.size(); i++)
		cout << reserve[i] << " ";
	cout << endl;
}

int counter(Table *&list, string color)
{
	int count = 0;
	Table *temp = list;
	while (temp)
	{
		if (temp->node.color == color)
			count++;
		temp = temp->next;
	}
	return count;
}

bool hasKing(Table *&list, string color)
{
	Table *temp = list;
	while (temp)
	{
		if (temp->node.color == color && temp->node.figure == "K")
			return true;
		temp = temp->next;
	}
	return false;
}

bool isEnd(Table *&list)
{
	if (counter(list, "black") == 0 || !hasKing(list, "black"))
	{
		cout << "Player 1 WIN!" << endl;
		return true;
	}
	else if (counter(list, "white") == 0 || !hasKing(list, "white"))
	{
		cout << "Player 2 WIN!" << endl;
		return true;
	}
	else return false;
}

int getIndex(vector<string> &vector, string figure)
{
	for (unsigned int i = 0; i < vector.size(); i++)
	{
		if (vector[i] == figure)
			return i;
	}
	return -1;
}

bool canYouInsert(Table **list, char x, int y, Data node)
{
	Table *temp = *list;
	string keys = "abcdefghi";
	if (node.figure == "P")
	{
		while (temp)
		{
			if (temp->node.vertical == y 
				&& ((temp->node.figure == "P" && temp->node.color == node.color) 
					|| (node.color == "white" 
					    && getFigure(*list, temp->node.vertical, keys[getIndex(x) + 1]) == "K"))
					|| (node.color == "black" 
					    && getFigure(*list, temp->node.vertical, keys[getIndex(x) - 1]) == "K"))
				return false;
			temp = temp->next;
		}
	}
	else return false;
}

bool insertFigure(Table **list, vector<string> &reserve, Table &insert)
{
	Table *tempT = *list;
	bool present = false;
	for(unsigned int i = 0; i < reserve.size(); i++)
	{
		if (reserve[i] == insert.node.figure)
		{
			present = true;
			break;
		}
	}
	if (!present)
	{
		cout << "       You haven't this figure";
		return false;
	}
	else
	{
		while (tempT)
		{
			if (tempT->node.horizontal == insert.node.horizontal 
			    && tempT->node.vertical == insert.node.vertical 
			    && tempT->node.figure == " "
			    && canYouInsert(list, tempT->node.horizontal, tempT->node.vertical, insert.node))
			{
				tempT->node.figure = insert.node.figure;
				tempT->node.color = insert.node.color;
				reserve.erase(reserve.begin() + getIndex(reserve, insert.node.figure));
				return true;
			}
			tempT = tempT->next;
		}
		cout << "       The place aren't empty\n";
		return false;
	}
}

int main()
{
	Table *list = nullptr;
	vector <string> reserve1 = {};
	vector <string> reserve2 = {};
	Create_Table(&list);
	Fill_Black(list);
	Fill_White(list);
	int player = 2;
	while (!isEnd(list))
	{
		Show_State(list);
		cout << "\n       Player's 1 reserve: ";
		showReserve(reserve1);
		cout << "\n       Player's 2 reserve: ";
		showReserve(reserve2);
		cout << "\n       Player " << player << " your turn.\n";
		int vertical[2];
		char horizontal[2];
		bool attempt = true;
		int action;
		if (player == 1 && !reserve1.empty() || player == 2 && !reserve2.empty())
		{
			cout << "       Select action:\n       1. Move figure;\n       2. Insert to table;\n       ";
			cin >> action;
		}
		else action = 1;
		switch (action)
		{
		case 1:
		{
			while (attempt)
			{
				cout << "       Select figure: ";
				cin >> horizontal[0] >> vertical[0];
				while (!isYour(&list, vertical[0], horizontal[0], player))
				{
					cout << "       Select figure: ";
					cin >> horizontal[0] >> vertical[0];
				}
				cout << "       To: ";
				cin >> horizontal[1] >> vertical[1];
				if (!canYou(&list, vertical[0], horizontal[0], vertical[1], horizontal[1], player))
				{
					cout << "       It's imposible!\n";
					attempt = true;
				}
				else attempt = false;
			}
			string temp = getFigure(list, vertical[1], horizontal[1]);
			if (temp != " ")
			{
				if (player == 1) reserve1.push_back(temp);
				else reserve2.push_back(temp);
			}
			Move(&list, horizontal[0], vertical[0], horizontal[1], vertical[1]);
			break;
		}
		case 2:
			while (attempt)
			{
				Table *temp = new Table;
				cout << "       Select figure: ";
				cin >> temp->node.figure;
				cout << "       To: ";
				cin >> temp->node.horizontal >> temp->node.vertical;
				if (player == 1)
				{
					temp->node.color = "white";
					attempt = !insertFigure(&list, reserve1, *temp);
				}
				else
				{
					temp->node.color = "black";
					attempt = !insertFigure(&list, reserve2, *temp);
				}
				cout << endl;
				delete temp;
			}
			break;
		default:
			break;
		}
		if (player == 2) player--;
		else player++;
		system("cls");
	}
	return 0;
}
