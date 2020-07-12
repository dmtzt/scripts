/*
 * Class.h
 * 
 * Description
 * 
 * David Alejandro Martinez Tristan
 * 4/3/2019
 */

#ifndef CLASS_H
#define CLASS_H
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Class
{
	private:
		string className, classType, fileName, altClassName, altClassType, altFileName;
		vector< vector<string> > variables;
		bool defaultConstructor, variablesConstructor;
	public:
		Class();
		//Class(string, string, string, string, string, vector<vector<string>>, bool, bool);
		string getClassName();
		string getClassType();
		string getFileName();
		string getAltClassName();
		string getAltClassType();
		string getAltFileName();
		vector< vector<string> > getVariables();
		bool getDefaultConstructor();
		bool getVariablesConstructor();
		void setClassName(string);
		void setClassType(string);
		void setFileName(string);
		void setAltClassName(string);
		void setAltClassType(string);
		void setAltFileName(string);
		void setVariables(vector <vector<string> >);
		void setDefaultConstructor(bool);
		void setVariablesConstructor(bool);
		void generateFileName();
		void generateAltFileName();
		void addVariable(vector<string>);
		void toString();
};

Class::Class()
{
	className = "";
	classType = "";
	fileName = "";
	altClassName = "";
	altClassType = "";
	defaultConstructor = 0.0;
	variablesConstructor = 0.0;
}

/*
Class::Class(string classname, string classtype, string filename, string altClassname, string altClasstype, vector<vector<string>> variables, bool defaultConstructor, bool variablesConstructor)
{
	this->classname = classname;
	this->classtype = classtype;
	this->filename = filename;
	this->altClassname = altClassname;
	this->altClasstype = altClasstype;
	this->variables = variables;
	this->defaultConstructor = defaultConstructor;
	this->variablesConstructor = variablesConstructor;
}
*/

string Class::getClassName()
{
	return className;
}

string Class::getClassType()
{
	return classType;
}

string Class::getFileName()
{
	return fileName;
}

string Class::getAltClassName()
{
	return altClassName;
}

string Class::getAltClassType()
{
	return altClassType;
}

string Class::getAltFileName()
{
	return altFileName;
}

vector< vector<string> > Class::getVariables()
{
	return variables;
}

bool Class::getDefaultConstructor()
{
	return defaultConstructor;
}

bool Class::getVariablesConstructor()
{
	return variablesConstructor;
}

void Class::setClassName(string className)
{
	this->className = className;
}

void Class::setClassType(string classType)
{
	this->classType = classType;
}

void Class::setFileName(string fileName)
{
	this->fileName = fileName;
}

void Class::setAltClassName(string altClassName)
{
	this->altClassName = altClassName;
}

void Class::setAltClassType(string altClassType)
{
	this->altClassType = altClassType;
}

void Class::setVariables(vector< vector<string> > variables)
{
	this->variables = variables;
}

void Class::setDefaultConstructor(bool defaultConstructor)
{
	this->defaultConstructor = defaultConstructor;
}

void Class::setVariablesConstructor(bool variablesConstructor)
{
	this->variablesConstructor = variablesConstructor;
}

void Class::generateFileName()
{
	fileName = className + "." + classType;
}

void Class::generateAltFileName()
{
	altClassName = className;
	altClassType = classType;

	transform(altClassName.begin(), altClassName.end(), altClassName.begin(), ::toupper);
    transform(altClassType.begin(), altClassType.end(), altClassType.begin(), ::toupper);

	altFileName = altClassName + "_" + altClassType;
}

void Class::addVariable(vector<string> variable)
{
	variables.push_back(variable);
}

void Class::toString()
{
	cout << className << endl;
	cout << classType << endl;
	cout << fileName << endl;
	cout << altClassName << endl;
	cout << altClassType << endl;
	cout << defaultConstructor << endl;
	cout << variablesConstructor << endl;
}
#endif