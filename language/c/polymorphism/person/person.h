//Person.h

typedef struct _Person Person;

//declaration of pointers to functions
typedef void    (*fptrDisplayInfo)(Person*);
typedef void    (*fptrWriteToFile)( Person*, const char*);
typedef void    (*fptrDelete)( Person *) ;

//Note: In C all the members are by default public. We can achieve 
//the data hiding (private members), but that method is tricky. 
//For simplification of this article
// we are considering the data members     //public only.
typedef struct _Person 
{
    char* pFName;
    char* pLName;
    //interface for function
    fptrDisplayInfo   Display;
    fptrWriteToFile   WriteToFile;
    fptrDelete      Delete;
}Person;

person* new_Person(const char* const pFirstName, 
                   const char* const pLastName); //constructor
void delete_Person(Person* const pPersonObj);    //destructor

void Person_DisplayInfo(Person* const pPersonObj);
void Person_WriteToFile(Person* const pPersonObj, const char* pFileName);