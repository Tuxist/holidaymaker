#include <iostream>
#include <sstream>
#include <config.h>
#include <algorithm>
#include <cstring>

#include <tinyxml2.h>

#include "employee.h"

int holidaymaker::Employee::getID(){
  return _ID;      
}
    
void holidaymaker::Employee::setForename(const char *forename){
  if(_Forename)
    delete[] _Forename;
  int forlen=strlen(forename);
  _Forename = new char[forlen+1];
  std::copy(forename,forename+forlen,_Forename);
  _Forename[forlen]='\0';
}

const char *holidaymaker::Employee::getForename(){
  return _Forename;  
}
    
void holidaymaker::Employee::setSurname(const char *surname){
  if(_Surname)
    delete[] _Surname;
  int surlen=strlen(surname);
  _Surname=new char[surlen+1];
  std::copy(surname,surname+surlen,_Surname);
  _Surname[surlen]='\0';
}

const char *holidaymaker::Employee::getSurname(){
  return _Surname;  
}

void holidaymaker::Employee::setWorktime(int worktime){
  _Worktime=worktime;
}

int holidaymaker::Employee::getWorktine(){
  return _Worktime;
}

void holidaymaker::Employee::setWorkdays(int workdays){
  _Workdays=workdays;
}

int holidaymaker::Employee::getWorkdays(){
  return _Workdays;  
}

void holidaymaker::Employee::setBirthdayDay(int day){
  _BirthdayDay=day;
}

int holidaymaker::Employee::getBirthdayDay(){
  return _BirthdayDay;  
}
    
void holidaymaker::Employee::setBirthdayMonth(int month){
  _BirthdayMonth=month;
}

int holidaymaker::Employee::getBirthdayMonth(){
   return _BirthdayMonth; 
}
    
void holidaymaker::Employee::setBirthdayYear(int year){
  _BirthdayYear=year;    
}

int holidaymaker::Employee::getBirthdayYear(){
  return _BirthdayYear;  
}
    
holidaymaker::Employee *holidaymaker::Employee::nextEmployee(){
  return _nextEmployee;        
}

holidaymaker::Employee::Employee(){
  _ID=-1;
  _Forename=NULL;
  _Surname=NULL;
  _Workdays=5;
  _Worktime=40;
  /*Birthday*/
  _BirthdayDay=1;
  _BirthdayMonth=1;
  _BirthdayYear=1970;
  _nextEmployee=NULL;
}

holidaymaker::Employee::~Employee(){
  delete[] _Forename;
  delete[] _Surname;
  delete _nextEmployee;
}

holidaymaker::EmployeePool::EmployeePool(){
  _firstEmployee=NULL;
  _lastEmployee=NULL;
  _lastID=0;
  _XMLFile = new tinyxml2::XMLDocument();
}

holidaymaker::EmployeePool::~EmployeePool(){
  delete _firstEmployee;
  _lastEmployee=NULL;
  delete _XMLFile;
}

holidaymaker::Employee *holidaymaker::EmployeePool::addEmployee(){
  if(_firstEmployee){
    _lastEmployee->_nextEmployee=new Employee;
    _lastEmployee=_lastEmployee->_nextEmployee;
  }else{
    _firstEmployee=new Employee;
    _lastEmployee=_firstEmployee;
  }
  _lastEmployee->_ID=_lastID;
  _lastID++;
  return _lastEmployee;
}

holidaymaker::Employee *holidaymaker::EmployeePool::delEmployee(holidaymaker::Employee* delemployee){
  holidaymaker::Employee *prevemployee=NULL;
  for(holidaymaker::Employee *curemployee=_firstEmployee; curemployee; curemployee=curemployee->nextEmployee()){
    if(curemployee==delemployee){
      if(prevemployee){
        prevemployee->_nextEmployee=curemployee->_nextEmployee;
        if(_lastEmployee==delemployee)
          _lastEmployee=prevemployee;
      }else{
        _firstEmployee=curemployee->_nextEmployee;
        if(_lastEmployee==delemployee)
          _lastEmployee=_firstEmployee;
      }
      curemployee->_nextEmployee=NULL;
      delete curemployee;
      break;
    }
    prevemployee=curemployee;
  }
  if(prevemployee && prevemployee->_nextEmployee){
    return prevemployee->_nextEmployee;
  }else{
    return _firstEmployee;
  }  
}

holidaymaker::Employee * holidaymaker::EmployeePool::getfirstEmployee(){
  return _firstEmployee;
}

holidaymaker::Employee * holidaymaker::EmployeePool::getlastEmployee(){
  return _lastEmployee;
}

int holidaymaker::EmployeePool::getEmployeeSize(){
  int count=0;
  for(holidaymaker::Employee *curemployee=_firstEmployee; curemployee; curemployee=curemployee->nextEmployee()){
    count++;
  }
  return count;
}

bool holidaymaker::EmployeePool::loadFile(const char* path){
  _XMLFile->LoadFile(path);
  if(_XMLFile->ErrorID() == 0) { 
    tinyxml2::XMLElement *docRoot=NULL,*emplnode=NULL;
    docRoot = _XMLFile->FirstChildElement("holidaymaker");
    if(docRoot){
      emplnode=docRoot->FirstChildElement("employees");
      if(emplnode){
        for(tinyxml2::XMLElement *curempl = emplnode->FirstChildElement("employee"); curempl; 
            curempl=curempl->NextSiblingElement("employee")){
            holidaymaker::Employee *addempl=addEmployee();
            if(addempl->_ID>_lastID){
              _lastID=addempl->_ID;
            }
            addempl->_ID=curempl->IntAttribute("id");
            addempl->setForename(curempl->Attribute("forename"));
            addempl->setSurname(curempl->Attribute("surname"));
            const char *btpl =curempl->Attribute("birthday");
            sscanf(btpl,"%d/%d/%d",&addempl->_BirthdayDay,
                                   &addempl->_BirthdayMonth,
                                   &addempl->_BirthdayYear);
        }
        return true;
      }else{
        return false;
      }
    }else{
      return false;
    }
  }else{
    return false;
  }
}

bool holidaymaker::EmployeePool::saveFile(const char* path){
  _XMLFile->LoadFile(path);
  tinyxml2::XMLElement *docRoot=NULL,*emplnode=NULL;
  docRoot = _XMLFile->FirstChildElement("holidaymaker");
  if(!docRoot){
    docRoot = _XMLFile->NewElement("holidaymaker");
    _XMLFile->InsertFirstChild(docRoot);
  }
  emplnode=docRoot->FirstChildElement("employees");
  if(emplnode){
    docRoot->DeleteChild(emplnode);
  }
  emplnode = _XMLFile->NewElement("employees");
  docRoot->InsertEndChild(emplnode);
  for(holidaymaker::Employee *curemply=_firstEmployee; curemply;
    curemply=curemply->nextEmployee()
  ){
    tinyxml2::XMLElement *newempl = _XMLFile->NewElement("employee");
    newempl->SetAttribute("id",curemply->getID());
    newempl->SetAttribute("forename",curemply->getForename());
    newempl->SetAttribute("surname",curemply->getSurname());
    std::stringstream bstream;
    bstream << curemply->getBirthdayDay() << "/" << curemply->getBirthdayMonth() 
            << "/" << curemply->getBirthdayYear(); 
    newempl->SetAttribute("birthday",bstream.str().c_str());
    emplnode->InsertEndChild(newempl);
  }
   if(_XMLFile->SaveFile(path)==0)
     return true;
  return false;
}



