#include "pch.h"
#include "CppUnitTest.h"
#include "../LAB_12.13_CXT/LAB_12.13_CXT.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(TestMethod1)
        {
            ClosedHashTable phoneBook;
            Employee emp1("Doe", "123", "101");
            Employee emp2("Smith", "456", "102");

            // Test addEmployee method
            phoneBook.addEmployee(emp1);
            phoneBook.addEmployee(emp2);

            // Test searchByPhoneNumber method
            Employee* foundEmployee = phoneBook.searchByPhoneNumber("123");
            Assert::AreEqual(foundEmployee->lastName, std::string("Doe"));
            Assert::AreEqual(foundEmployee->roomNumber, std::string("101"));
            delete foundEmployee;

            // Test deleteEmployee method
            phoneBook.deleteEmployee("123");
            Assert::IsNull(phoneBook.searchByPhoneNumber("123"));
        }
    };
}
