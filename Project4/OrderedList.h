/*
        Author: Caleb Johnson
        OrderedList.h
*/

#ifndef _ORDERED_LIST_GUARD
#define _ORDERED_LIST_GUARD 1
#define _ARRAY_LIST_MAX_NUM_OF_NODES 100

using namespace std;

template <class T>

class OrderedList
{
	
	private:
		int length; 	// number of items currently in the list
		T nodes[_ARRAY_LIST_MAX_NUM_OF_NODES];	// place where the list is stored 
		
		/* the following prototype is for an optional function,
		 * if you don't wish for searchReturnIndex to be used, 
		 * you may comment the prototype out */
		//int searchReturnIndex(string lastName, string firstName);
		/* If there exists a student in the list with a matching 
		 * first name and matching last name (known as target), return its index
		 * otherwise, return -1 if target would be the first item
		 * and return index of highest item lower than what would be
		 * the index of the target, had the target existed in the list
		 * 
		 * Note: The term "target" is used to indicate a first and last
		 * name that a function may search for, and the student, which may 
		 * or may not exist in the list with both a matching first and last name.
		 * All searches done by this class are done by first and last name.
		 * */
	 
	public:
		/* constructer */
		OrderedList()
		{
			length = 0;
		}
		
		/* destructer */
		~OrderedList()
		{

		}
		
		T getNode(int index)
		{
			return nodes[index];
		}
		int getLength()
		{
			return length;
		}
		
		void setNode(int index, T value)
		{
			nodes[index] = value;
		}
		
		
		bool remove(string lastName, string firstName, string(T::*toStringFunction)() const)
		{
			for (int i = 0; i < length; i++)
			{
				if ((lastName + ", " + firstName) == (nodes[i].*toStringFunction)())
				{
					for (int j = i; j < length - 1; j++)
					{
						nodes[j] = nodes[j + 1];
					}
					length -= 1;
					return true;
				}
			}
			return false;
		}
	 
		bool insert(T newItem)
		{
			nodes[length] = newItem;
			length += 1;
			return true;
		}
	 
		T* search(string lastName, string firstName, string (T::*toStringFunction)() const)
		{
			for (int i = 0; i < length; i++)
			{
				if ((lastName + ", " + firstName) == (nodes[i].*toStringFunction)())
				{
					return &nodes[i];
				}
			}
			return nullptr;
		}
		 
		void traverse(string(T::*toStringFunction)() const, char (T::*letterFunction)() const)
		{
			bool finishedsorting = false;
			T temp;
			while (!finishedsorting)
			{
				finishedsorting = true;
				for (int i = 0; i < length - 1; i++)
				{
					string a = (nodes[i].*toStringFunction)();
					string b = (nodes[i + 1].*toStringFunction)();
					int comparer = a.compare(b);
					if (comparer > 0)
					{
						finishedsorting = false;

						temp = nodes[i];
						nodes[i] = nodes[i + 1];
						nodes[i + 1] = temp;
					}
				}
			}

			for (int i = 0; i < length; i++)
			{
				cout << i + 1 << ".\t" << (nodes[i].*toStringFunction)() << " - " << (nodes[i].*letterFunction)() << endl;
			}
		}
		 
		void traverseByGrade(string(T::*toStringFunction)() const, double (T::*calculationFunction)() const, char (T::*letterFunction)() const)
		{
			bool finishedsorting = false;
			T temp;
			while (!finishedsorting)
			{
				finishedsorting = true;
				for (int i = 0; i < length - 1; i++)
				{
					string a = (nodes[i].*toStringFunction)();
					string b = (nodes[i + 1].*toStringFunction)();

					int comparer;
					if ((nodes[i].*calculationFunction)() > (nodes[i + 1].*calculationFunction)())
					{
						comparer = -1;
					}
					else if ((nodes[i].*calculationFunction)() < (nodes[i + 1].*calculationFunction)())
					{
						comparer = 1;
					}
					else
					{
						comparer = a.compare(b);
					}
					if (comparer > 0)
					{
						finishedsorting = false;

						temp = nodes[i];
						nodes[i] = nodes[i + 1];
						nodes[i + 1] = temp;
					}
				}
			}

			for (int i = 0; i < length; i++)
			{
				cout << i + 1 << ".\t" << (nodes[i].*toStringFunction)() << " - " << (nodes[i].*letterFunction)() << endl;
			}
		}
		 
		void traverseOut(ofstream *f, double hwWeight, double qzWeight, double fxWeight, string(T::*lastNameFunction)() const, string(T::*firstNameFunction)() const, int(T::*HWFunction)(int) const, int(T::*QZFunction)(int) const, int(T::*finalExamFunction)() const)
		{
			string newRoster;

			newRoster = to_string(hwWeight) + '\n' + to_string(qzWeight) + '\n' + to_string(fxWeight) + '\n' + to_string(length) + '\n';
			for (int i = 0; i < length; i++)
			{
				newRoster += (nodes[i].*lastNameFunction)() + "\t" + (nodes[i].*firstNameFunction)();
				for (int j = 0; j < 4; j++)
				{
					int a = (nodes[i].*HWFunction)(j);
					newRoster += "\t" + to_string(a);
				}
				for (int j = 0; j < 4; j++)
				{
					int a = (nodes[i].*QZFunction)(j);
					newRoster += "\t" + to_string(a);
				}
				newRoster += "\t" + to_string((nodes[i].*finalExamFunction)()) + '\n';
			}
			*f << newRoster;
		}

		void traverseDisplayFunctions(void (T::*displayFunction)() const)
		{
			for (int i = 0; i < length; i++)
			{
				(nodes[i].*displayFunction)();
			}
		}

		void calculateAverage(double (T::*calculationFunction)() const)
		{
			double total = 0;
			for (int i = 0; i < length; i++)
			{
				total += (nodes[i].*calculationFunction)();
			}
			cout << "The average grade for this class is " << total / length << endl;
		}
};

#endif
