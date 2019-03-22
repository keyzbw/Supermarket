#pragma once
#include "employee.h"
class employeeDao
{
public:
	employeeDao();
	~employeeDao();
	employee getEmployee(CString employeeNo);
	bool addEmployee(employee e);
	bool updateEmployee(employee e);
	bool deleteEmployee(CString employeeNo);
};

