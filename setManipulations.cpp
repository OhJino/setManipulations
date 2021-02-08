//Author: Jino Enriquez
//File: setManipulations.cpp
#include <iostream>
#include <string>
#include <iterator>

using namespace std;


//////////////////////////////////////
//      FUNCTION PROTOTYPES         //
//////////////////////////////////////
void displayMenu();
void displaySet(string*, int*);
bool inputValidate(string *, string, int *);
string * getUniversalSet(char, int *);
string * getSet(char, int*, string *, int *);
string * setUnion(string*, string*, int, int, int*);
string * setIntersect(string*, string*, int, int, int*);
string * setComplement(string*, string*, int, int, string*, int, int*);
string * setDifference(string*, string*, int, int, int*);
string * setSymDifference(string*, string*, int, int, int*);



//////////////////////////////////////
//              main()              //
//////////////////////////////////////
int main()
{
    //Create a pointer to a string called U for Universal Set
    string *U;
    //Create int to store size of universal set
    int u_size;
    //User will input size and values of universal set
    U = getUniversalSet('U', &u_size);
    //Create Set A
    string *A;
    int a_size;
    //User will input size and values of Set A
    //Values must be from the universal set
    A = getSet('A', &a_size, U, &u_size);
    //Create Set B
    string *B;
    int b_size;
    //User will input size and values of Set B
    //Values must be from the universal set
    B = getSet('B', &b_size, U, &u_size);
    //User will input value to determine what action to perform with the sets
    char set_action;
    //Create new set to represent the finished product of the action
    string *result_set;
    //Loop until user quits
    while(true)
    {
        //Give user options on what actions can be performed
        displayMenu();
        cin >> set_action;
        int new_set_size;
        //User wants a union of both sets
        if (toupper(set_action) == 'U')
        {
            cout << "Getting union of A and B....." << endl;
            result_set = setUnion(A, B, a_size, b_size, &new_set_size);
        }
        //User wants an intersection of both sets
        else if (toupper(set_action) == 'I')
        {
            cout << "Getting intersection of A and B....." << endl;
            result_set = setIntersect(A, B, a_size, b_size, &new_set_size);
        }
        //User wants a complement of both sets
        else if (toupper(set_action) == 'C')
        {
            cout << "Getting complement of A and B....." << endl;
            result_set = setComplement(A, B, a_size, b_size, U, u_size, &new_set_size);
        }
        //User wants a difference of both sets
        else if (toupper(set_action) == 'D')
        {
            cout << "Getting difference of A and B [A-B]..." << endl;
            result_set = setDifference(A, B, a_size, b_size, &new_set_size);
        }
        //User wants a symmetrical difference of both sets
        else if (toupper(set_action) == 'S')
        {
            cout << "Getting symmetrical difference of A and B..." << endl;
            result_set = setSymDifference(A, B, a_size, b_size, &new_set_size);
        }
        //Userr wants to display the set to the screen
        else if (toupper(set_action) == 'A')
        {
            if (result_set != nullptr)
            {
                cout << "Displaying items from set:" << endl;
                displaySet(result_set, &new_set_size);
            }
            else
            {
                cout << "No set available to display. Please perform an action first." << endl;
            }
        }
        //User wants to quit the program
        else if (toupper(set_action) == 'Q')
        {
            delete [] result_set;
            result_set = nullptr;
            break;
        }
        //User entered incorrect input. Retry.
        else
        {
            cout << "Invalid input. Please enter in a valid option:" << endl;
        }
    }   
    return 0;
}





//////////////////////////////////////////////////
// Function Name: displayMenu()                 //
// Provides user with actions to perform on set //
//////////////////////////////////////////////////
void displayMenu()
{
    cout << "Enter U for a union of Set A and Set B" << endl;
    cout << "Enter I for an intersection of Set A and Set B" << endl;
    cout << "Enter C for a complement of Set A and Set B" << endl;
    cout << "Enter D for a difference of Set A and Set B [A-B]" << endl;
    cout << "Enter S for a symmetrical difference of Set A and Set B" << endl;
    cout << "Enter A to display the set [CANNOT BE DONE UNLESS AN ACTION HAS BEEN PERFORMED]" << endl;
    cout << "Enter Q to quit" << endl;
    return;
}


//////////////////////////////////////////////////
// Function Name: displayset()                  //
// Displays all set elements to user            //
//////////////////////////////////////////////////
void displaySet(string * set, int * set_size)
{
    for (int i = 0; i < *set_size; i++)
    {
        cout << set[i] << endl;
    }
    return;
}


/////////////////////////////////////////////////////////
// Function Name: inputValidate()                      //
// Validates user input a value from the universal set //
/////////////////////////////////////////////////////////
bool inputValidate(string * universalSet, string input, int *size_u)
{
    //Return value
    //Determines if input is correct
    bool validated_input = false;
    //Check through all elements of the universal set
    for (int i = 0; i < *size_u; i++)
    {
        //True if input is found in universal set
        if (input == universalSet[i])
        {
            validated_input = true;
        }
    }
    return validated_input;
}


/////////////////////////////////////////////////
// Function Name: getSet()                     //
//                                             //
/////////////////////////////////////////////////
string * getUniversalSet(char setName, int *array_size)
{
    //User will input the size of the Universal Set
    cout << "How many elements are in Set " << setName << ": " << endl;
    cin >> *array_size;
    //Create dynamic array of strings to return back to main
    string* array = new string[*array_size];
    //User will input the value of each element of the Universal Set
    for (int i = 0; i < *array_size; i++)
    {
        cout << "Input Item # " << i << ": " << endl;
        cin >> array[i];
        cout << endl;
    }
    return array;
}

string * getSet(char setName, int *set_size, string * uni_set, int *uni_size)
{
    //User will input the size of the set
    cout << "How many elements are in Set " << setName << ": " << endl;
    cin >> *set_size;
    //Create dynamic array of strings to return back to main
    string* array = new string[*set_size];
    //User will input the value of each element of the set
    //Each value must be from the universal set
    for (int i = 0; i < *set_size; i++)
    {
        //Give user the list of valid values to input
        cout << "You may input these numbers from the Universal Set: " << endl;
        for (int j = 0; j < *uni_size; j++)
        {
            cout << uni_set[j] << "  ";
        }
        cout << endl;
        //User will input value of element
        cout << "Input Item # " << i << ": " << endl;
        cin >> array[i];
        //Loop until a value from the Universal Set is input
        while(!inputValidate(uni_set, array[i], uni_size))
        {
            cout << "Incorrect input, please enter either:" << endl;
            for (int j = 0; j < *uni_size; j++)
            {
                cout << uni_set[j] << "  ";
            }
            cout << endl;
            cin >> array[i];
        }
        cout << endl;
    }
    return array;
}


//Each function passes 2 arrays as arguments and returns one array

/////////////////////////////////////////////////
// Function Name: setUnion()                   //
//                                             //
/////////////////////////////////////////////////
string * setUnion(string * A, string * B, int size_a, int size_b, int *size_new)
{
    int array_size = size_a + size_b;
    for (int i = 0; i < size_a; i++)
    {
        for (int j = 0; j < size_b; j++)
        {
            if (A[i] == B[j])
            {
                array_size -= 1;
            }
        }
    }
    *size_new = array_size;
    //Create new array with length of sum of Set A and Set B lengths
    string* union_array = new string[array_size];
    for (int i = 0; i < size_a; i++)
    {
        union_array[i] = A[i];
    }
    int next_item = 0;
    for (int j = 0; j < size_b; j++)
    {
        bool duplicate_flag = false;
        for (int k = 0; k < size_a; k++)
        {
            if (union_array[k] == B[j])
            {
                duplicate_flag = true;
            }
        }
        for (int q = j+1; q < size_b; q++)
            {
                if (B[j] == B[q])
                {
                    duplicate_flag = true;
                }
            }
        if (!duplicate_flag)
        {
            union_array[size_a + next_item] = B[j];
            next_item++;
        }
    }
    return union_array;
}


/////////////////////////////////////////////////
// Function Name: setIntersect()               //
//                                             //
/////////////////////////////////////////////////
string * setIntersect(string * setA, string * setB, int sz_a, int sz_b, int * new_array_size)
{
    int arr_size = 0;
    for (int i = 0; i < sz_a; i++)
    {
        for (int j = 0; j < sz_b; j++)
        {
            if (setA[i] == setB[j])
            {
                arr_size += 1;
            }
        }
    }
    *new_array_size = arr_size;
    string* intersect_array = new string[arr_size];
    int next_index = 0;
    for (int i = 0; i < sz_a; i++)
    {
        for (int j = 0; j < sz_b; j++)
        {
            if (setA[i] == setB[j])
            {
                intersect_array[next_index] = setA[i];
                next_index++;
            }
        }
    }
    return intersect_array;
}


/////////////////////////////////////////////////
// Function Name: setComplement()              //
//                                             //
/////////////////////////////////////////////////
string * setComplement(string* A_set, string* B_set, int a_size, int b_size, string *univ_set, int univ_size, int * array_new_size)
{
    int * new_size = 0;
    int array_length = univ_size;
    for (int i = 0; i < univ_size; i++)
    {
        bool dup_flag = false;
        //Check through each element of set A for matches
        for (int j = 0; j < a_size; j++)
        {
            if (univ_set[i] == A_set[j])
            {
                dup_flag = true;
            }
        }
        //Check through each element of set A for matches
        for (int j = 0; j < b_size; j++)
        {
            if (univ_set[i] == B_set[j])
            {
                dup_flag = true;
            }
        }
        if (dup_flag)
        {
            array_length -= 1;
        }
    }
    cout << "Array size: " << array_length << endl;
    *array_new_size = array_length;
    string *complement_set = new string[array_length];
    int next_index = 0;
    bool match_flag = false;
    for (int i = 0; i < univ_size; i++)
    {
        for (int j = 0; j < a_size; j++)
        {
            if (univ_set[i] == A_set[j])
            {
                match_flag = true;
            }
        }
        //Check through each element of set A for matches
        for (int j = 0; j < b_size; j++)
        {
            if (univ_set[i] == B_set[j])
            {
                match_flag = true;
            }
        }
        if (!match_flag)
        {
            complement_set[next_index] = univ_set[i];
            next_index++;
        }
        match_flag = false;
    }
    return complement_set;
}


/////////////////////////////////////////////////
// Function Name: setDifference()              //
//                                             //
/////////////////////////////////////////////////
string * setDifference(string * Aset, string * Bset, int Asize, int Bsize, int *size_new)
{
    int size_new_array = Asize;
    bool matching_flag = false;
    for (int i = 0; i < Asize; i++)
    {
        for (int j = 0; j < Bsize; j++)
        {
            if (Aset[i] == Bset[j])
            {
                matching_flag = true;
            }
        }
        if (matching_flag)
        {
            size_new_array -= 1;
            
        }
        matching_flag = false;
    }
    *size_new = size_new_array;
    string *difference_set = new string[size_new_array];
    int iterator = 0;
    for (int i = 0; i < Asize; i++)
    {
        for (int j = 0; j < Bsize; j++)
        {
            if (Aset[i] == Bset[j])
            {
                matching_flag = true;
            }
        }
        if (!matching_flag)
        {
            difference_set[iterator] = Aset[i];
            iterator++;
        }
        matching_flag = false;
    }
    return difference_set;
}


/////////////////////////////////////////////////
// Function Name: setSymDifference()           //
//                                             //
/////////////////////////////////////////////////
string *setSymDifference(string *array_A, string *array_B, int sizeOfA, int sizeOfB, int *updated_array_size)
{
    //Get union of both sets
    int union_size;
    string * union_set = setUnion(array_A, array_B, sizeOfA, sizeOfB, &union_size);
    //Get intersection of both sets
    int intersect_size;
    string * intersection_set = setIntersect(array_A, array_B, sizeOfA, sizeOfB, &intersect_size);
    //Get the difference of the union and the intersection
    int sym_diff_size;
    string * sym_diff_set = setDifference(union_set, intersection_set, union_size, intersect_size, &sym_diff_size);
    *updated_array_size = sym_diff_size;
    delete [] union_set;
    union_set = nullptr;
    delete [] intersection_set;
    intersection_set = nullptr;
    return sym_diff_set;
}
