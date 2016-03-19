//Employee.c
Person* new_Employee(const char* const pFirstName, const char* const pLastName,
                     const char* const pDepartment, 
                     const char* const pCompany, int nSalary)
{
    Employee* pEmpObj;
    //calling base class construtor
    Person* pObj = new_Person(pFirstName, pLastName);
    //allocating memory
    pEmpObj = malloc(sizeof(Employee));
    if (pEmpObj == NULL)
    {
        pObj->Delete(pObj);
        return NULL;
    }
    pObj->pDerivedObj = pEmpObj; //pointing to derived object
    
    //initialising derived class members
    pEmpObj->pDepartment = malloc(sizeof(char)*(strlen(pDepartment)+1));
    if(pEmpObj->pDepartment == NULL)
    {
        return NULL;
    }
    strcpy(pEmpObj->pDepartment, pDepartment);
    pEmpObj->pCompany = malloc(sizeof(char)*(strlen(pCompany)+1));
    if(pEmpObj->pCompany== NULL)
    {
        return NULL;
    }
    strcpy(pEmpObj->pCompany, pCompany);
    pEmpObj->nSalary = nSalary;
        
    //Changing base class interface to access derived class functions
    //virtual destructor
    //person destructor pointing to destrutor of employee
    pObj->Delete = delete_Employee;
    pObj->Display = Employee_DisplayInfo;
    pObj->WriteToFile = Employee_WriteToFile;

    return pObj;
}
