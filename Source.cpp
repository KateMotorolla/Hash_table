#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <fstream>


using namespace std;

struct list_node
{
	string key;
	list_node* p;
};

bool key_is_valid(string word)
{
	return (word[0] >= 'a' && word[0] <= 'z') || (word[0] >= 'A' && word[0] <= 'Z');
}

void hash_table_insert(list_node** arr, int arr_count, string word)
{
	hash<string> hash_function;
	int index = hash_function(word) % arr_count;
	if (arr[index] == nullptr)
	{
		arr[index] = new list_node;
		arr[index]->key = word;
		arr[index]->p = nullptr;
	}
	else
	{
		list_node* head = arr[index];
		while (head->p != nullptr)
			head = head->p;
		head->p = new list_node;
		head->p->key = word;
		head->p->p = nullptr;
	}
}

void main()
{
    string survey;
    bool is_continue = true;
    ifstream fin;

	const int arr_count = 10;
	list_node* arr[arr_count];
	for (int i = 0; i < arr_count; ++i)
		arr[i] = nullptr;
	
	
    while (is_continue)
    {
        cout << "Choose a solution option:" << endl;
        cout << "1 - Enter the line yourself " << endl;
        cout << "2 - Read a line from a file " << endl;
        cout << "1/2:  ";
        cin >> survey;
        if (survey.length() > 1)
        {
            cout << "Error" << endl;
            continue;
        }
        if (survey[0]== '1')
		{
			string input;
			cout << endl << "Enter the line: ";
			while(getline(cin, input) && input.empty());
			stringstream input_stream(input);
			while (!input_stream.eof())
			{
				string potential_key;
				input_stream >> potential_key;
				if (key_is_valid(potential_key))
					hash_table_insert(arr, arr_count, potential_key);
			}
			cout << endl;
			for (int i = 0; i < arr_count; ++i)
			{
				if (arr[i] == nullptr)
					cout << "-" << endl;
				else
				{
					list_node* head = arr[i];
					while (head->p != nullptr)
					{
						cout << head->key << "\t";
						head = head->p;
					}
					cout << head->key << endl;
				}
			}
			is_continue = false;
			break;
		}
		else if (survey[0] == '2')
		{
			fin.open("input.txt");
			string input;
			while (getline(fin, input) && input.empty());
			stringstream input_stream(input);
			while (!input_stream.eof())
			{
				string potential_key;
				input_stream >> potential_key;
				if (key_is_valid(potential_key))
					hash_table_insert(arr, arr_count, potential_key);
			}
			cout << endl;
			for (int i = 0; i < arr_count; ++i)
			{
				if (arr[i] == nullptr)
					cout << "-" << endl;
				else
				{
					list_node* head = arr[i];
					while (head->p != nullptr)
					{
						cout << head->key << "\t";
						head = head->p;
					}
					cout << head->key << endl;
				}
			}
			fin.close();
			is_continue = false;
			break;
		}
		else
		{
            cout << "Error" << endl;
            break;
        }
    }

}