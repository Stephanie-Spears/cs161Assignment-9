#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>

#define Array_Size 100 //Array Size counter defined as a constant. C++ can't handle dynamic array sizes, must declare an actual Array size value when initializing an Array.

using namespace std;
//there are two types of parameters: value and reference. A function using a value parameter receives a COPY of the actual parameter that was passed
//This means that if the value is changed in the function, it is changing a copy, not the actual variable.
//reference variables can be changed in the function. so by putting string&, I am making it so that the value of "FileName" can be changed within the void function--like adding .txt.
//so when main calls the void function, it can prompt for a filename, then add .txt, or manipulate it however it wants, and then return it CHANGED back to main. 
//if a function needs to return more than one value, you should make it a void function and use reference parameters to return the values

void GetFileName(string& FileName) //need to use the reference(&) to pass it back out to main
{
	string FileType = ".txt"; //changes the user input of file name to a text file link. Just for convenience
	fstream InputFile; //declare file variable name

	cout << "Enter the input file name: "; //get file name from user
	getline(cin, FileName); //read the entire line entered by user with getline--store it into the referenced FileName variable
	FileName.append(FileType); //append adds FileType (.txt) to the end of user defined FileName
	InputFile.open(FileName, fstream::in); //opens InputFile using appended FileName.txt, fstream is defined as "in," so it's reading from the file, not writing (which would be "out")
	
	while (InputFile.fail()) //loop to allow only filenames that already exist. Will fail if the file can't open.
	{
		cout << "Input file name '" << FileName << "' does not exist. Please try again." << endl;	

		cout << "Enter the input file name: ";
		getline(cin, FileName);
		FileName.append(FileType); 
		InputFile.open(FileName, fstream::in); 
		InputFile.close(); //not sure if i need to close the file from a void function
	}

	if (InputFile.good()) //don't need this but it is useful for reiterating what file we're opening, and shows us the file opened without errors.
	{
		cout << endl << "Input file name '" << FileName << "' opened for reading." << endl;
		InputFile.close();

	}
	else
	{
		InputFile.close();
	}


}


int main()
{

	string FileNamePath;
	fstream InputFile;
	int NumbersArray[Array_Size]; 
	int Num;
	int i = 0;
	int b = 0;

	GetFileName(FileNamePath); //Run the void fuction, and store "string& FileName" into the variable FileNamePath here

	InputFile.open(FileNamePath, fstream::in); //open InputFile
	
	cout << endl << endl;


	while (InputFile >> Num) //while there's still input to be read from the file
	{
		NumbersArray[i] = Num;  //sets the Array up. The integer being read from the file (Num) is put into the position i (starting at 0, ends when the file no longer can read >> Num).  
		i++; //increment the array position for each while loop
		b++; //using as a secondary counter of loops, so we can use that in our for loops instead of the constant "ArraySize = 0"  which used to be declared at the top and in place of "b"
	}
	//if you do cout << array it won't list all of the values stored in the array, instead it will give you the address in the memory for the array itself, as a singular object.
	for (int i = 0; i < b; i++) //reads through the first array up until there would be unfilled positions (because the actual size is 100, but with a file that has only 5 int, it will only fill positions 0-4 on the array). The remaining positions past "b" are unfilled 
	{
		for (int j = 0; j < b; j++)  //runs through all j positions, stores them. next it runs through all i positions and checks if position i value is smaller than position j value. if so, swaps positons. basically the j array stores the unordered ints, and the i array takes the sorted swapped number positions?
		{
			if (NumbersArray[i] < NumbersArray[j]) // checks to see if Array at position i is smaller than the Array at position j
			{
				//debugging:
			//	cout << endl << "Array with i: " << endl << "i: " << i << endl << "Num: " << NumbersArray[i] << endl;

				//cout << endl << "Array with j: " << endl << "j: " << j << endl << "Num: " << NumbersArray[j];

				swap(NumbersArray[i], NumbersArray[j]); 
				//cout << endl << "After Swap i: " << NumbersArray[i] << endl << "After Swap j: " << NumbersArray[j] << endl;

			}
		}

	}
	
	cout << "Sorted Array: " << endl << endl;

	for (int i = 0; i < b; i++)
	{
		cout << NumbersArray[i] << endl;
	}
	cout << endl;

	InputFile.close();

	return 0;
}