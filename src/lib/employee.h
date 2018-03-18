
namespace tinyxml2 {
  class XMLDocument;
}

namespace holidaymaker {
  class Employee {
  public:
      int         getID();
    
      void        setForename(const char *forename);
      const char *getForename(); 
    
      void        setSurname(const char *surname);
      const char *getSurname();
    
      /*Birthday*/
      void        setBirthdayDay(int day);
      int         getBirthdayDay();
    
      void        setBirthdayMonth(int month);
      int         getBirthdayMounth();
    
      void        setBirthdayYear(int year);
      int         getBirthdayYear();
    
      Employee   *nextEmployee();
    
  private:
      Employee();
      ~Employee();
      int       _ID;
      char     *_Forename;
      char     *_Surname;
      /*Birthday*/
      int       _BirthdayDay;
      int       _BirthdayMonth;
      int       _BirthdayYear;
      Employee *_nextEmployee;
      friend class EmployeePool;
  };

  class EmployeePool {
  public:
    EmployeePool();
    ~EmployeePool();
    
    bool loadFile(const char *path);
    bool saveFile(const char *path);
    
    Employee *addEmployee();
    Employee *delEmployee(Employee *delemployee);
    
    Employee *getfirstEmployee();
    Employee *getlastEmployee();
  private:
    Employee *_firstEmployee;
    Employee *_lastEmployee;
    int       _lastID;
    tinyxml2::XMLDocument *_XMLFile;  
  };
};
