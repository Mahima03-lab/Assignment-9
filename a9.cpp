#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class fileRA {
private:
    string filename;  
    fstream file;     
    unsigned int size;     
public:
    
    fileRA(const string& fileName) : filename(fileName) {
        file.open(filename, ios::in | ios::out | ios::binary);
       if(file.fail()){
            cout <<"Cannot open file\n";
            return ;
         }

        file.seekg(0, ios::end);
        size = file.tellg();
        file.seekg(0, ios::beg);  
    }

   
    unsigned int get_size() const {
        return size;
    }

    
    class Descriptor {
    private:
        fstream& file;
        unsigned int position;

    public:
       
        Descriptor(fstream& fileStream, unsigned int p): file(fileStream), position(p) {}

       
        void operator=(char c) {
            file.seekp(position);
            file.put(c);
        }

        
        operator char() const {
            file.seekg(position);
            return file.get();
        }
    };

   
    Descriptor operator[](unsigned int p) {
        return Descriptor(file, p);
    }
};

int main() {
    // Opens the file in read and write mode
    fileRA fobj("Test.txt");

    // Random writing to file
    fobj[4] = 'A';

    // Print the contents of the file
    for (unsigned int i = 0; i < fobj.get_size(); i++) {
       cout << fobj[i];
    }

    // Read a specific character from the file
    char c = fobj[1];  // Implicit conversion to char
   cout << "\nChar is = " << c <<endl;

    return 0;
}
