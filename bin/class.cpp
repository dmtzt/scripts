#include <algorithm>
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Class.h"
#define TYPE 0
#define IDENTIFIER 1
#define ALT_IDENTIFIER 2

using namespace std;

void getWriteVariables(ofstream &outfile, Class &fileclass);
void writeConstructorDeclarations(ofstream &outfile, Class &fileclass);
void writeConstructorImplementations(ofstream &outfile, Class &fileclass);
void writeCustomFunctionImplementations(ofstream &outfile, Class &fileclass);
void writeCustomFunctionDeclarations(ofstream &outfile);
void writeFooter(ofstream &outfile);
void writeGetterDeclarations(ofstream &outfile, Class &fileclass);
void writeGetterImplementations(ofstream &outfile, Class &fileclass);
void writeHeader(ofstream &outfile, Class &fileclass);
void writeSetterDeclarations(ofstream &outfile, Class &fileclass);
void writeSetterImplementations(ofstream &outfile, Class &fileclass);
void writeVariables(ofstream &outfile, string line);
string indent(int hierarchy);
string newline(int quantity);
string getCurrentDate();

int main(int argc, char const *argv[])
{
    // Revisar uso correcto del programa
    if (argc != 3)
    {
        cout << "Uso: class <nombre> <tipo>" << newline(1);
        return 1;
    }

    Class fileclass;
    ofstream outfile;
    string filename;

    // Generar nombre y crear archivo
    fileclass.setClassName(argv[1]);
    fileclass.setClassType(argv[2]);
    fileclass.generateFileName();

    filename = fileclass.getFileName();

    outfile.open(filename.c_str());

    // Escribir encabezado de clase previo a declaracion de variables
    writeHeader(outfile, fileclass);

    // Bienvenida al programa
    cout << "Bienvenido al Asistente de clases de C++!" << newline(1);
    cout << fileclass.getFileName() << " ha sido creado exitosamente" << newline(1);    
    
    cout << "1/2 Variables" << newline(1)
         << "Por favor introduce las variables de la clase en formato: "
         << "<tipo> <nombre> <nombre> <nombre>" << newline(1)
         << "Al terminar, presiona dos veces Enter" << newline(1);
    // 1/2 Obtener, almacenar y escribir variables
    getWriteVariables(outfile, fileclass);
    
    cout << "2/2 Constructores" << newline(1) << newline(1);
    // 2 Solicitar y escribir declaraciones de diferentes constructores
    writeConstructorDeclarations(outfile, fileclass);

    cout << "Generando getters..." << newline(1);
    // Escribir declaraciones de getters
    writeGetterDeclarations(outfile, fileclass);

    cout << "Generando setters..." << newline(1);
    // Escribir declaraciones de setters
    writeSetterDeclarations(outfile, fileclass);

    cout << "Generando funciones personalizadas..." << newline(1);
    // Escribir declaraciones de funciones personalizadas
    writeCustomFunctionDeclarations(outfile);

    // Implementar constructores
    writeConstructorImplementations(outfile, fileclass);

    // Escribir implementaciones de getters
    writeGetterImplementations(outfile, fileclass);

    // Escribir implementaciones de setters
    writeSetterImplementations(outfile, fileclass);

    // Escribir implementaciones de funciones personalizadas
    writeCustomFunctionImplementations(outfile, fileclass);

    // Escribir footer
    writeFooter(outfile);

    // Cerrar archivo
    outfile.close();

    cout << "La plantilla se ha generado exitosamente!" << newline(1)
         << "Happy programming!";

    // Success!
    return 0;
}

void getWriteVariables(ofstream &outfile, Class &fileclass)
{
    unsigned int start, end;
    string line, delimiter, type, identifier;

    // Establecer el valor del delimitador entre palabras
    delimiter = " ";
    
    do
    {
        // Lee la linea completa introducida por el usuario
        getline(cin, line);

        // Identificar y extraer tipo de dato del conjunto de variables
        start = 0;
        end = line.find(delimiter);
        type = line.substr(start, end);

        while((start + end) != string::npos)
        { 
            vector<string> variable(3);

            // Identificar nombre de cada variable
            start += end + 1;
            end = line.find(delimiter, start) - start;
            identifier = line.substr(start, end);

            // Almacenar tipo de dato, nombre y nombre alternativo de la variable
            variable[TYPE] = type;
            variable[IDENTIFIER] = identifier;
            variable[ALT_IDENTIFIER] = identifier;
            variable[ALT_IDENTIFIER][0] = toupper(identifier[0]);

            fileclass.addVariable(variable);
        }

        writeVariables(outfile, line);

    } while (!line.empty());
}

void writeConstructorDeclarations(ofstream &outfile, Class &fileclass)
{
    char choice;

    outfile << indent(1) << "public:" << newline(1);

    cout << "Deseas un constructor default? (s/n) ";
    do
    {
        cin >> choice;
        choice = tolower(choice);
    } while (choice != 's' && choice != 'n');

    if (choice == 's')
    {
        outfile << indent(2) << fileclass.getClassName() << "();" << newline(1);
        fileclass.setDefaultConstructor(true);
    }   

    cout << "Deseas un constructor con todas las variables como argumentos? (s/n) ";
    do
    {
        cin >> choice;
        choice = tolower(choice);
    } while (choice != 's' && choice != 'n');

    if (choice == 's')
    {
        vector< vector<string> > variables = fileclass.getVariables();
        outfile << indent(2) << fileclass.getClassName() << "(" << variables[0][TYPE];
        fileclass.setVariablesConstructor(true);

        for (unsigned int i = 1; i < variables.size(); i++)
            outfile << ", " << variables[i][TYPE];

        outfile << ");" << newline(1);
    }
}

void writeConstructorImplementations(ofstream &outfile, Class &fileclass)
{
    vector< vector<string> > variables = fileclass.getVariables();

    if (fileclass.getDefaultConstructor())
    {
        outfile << fileclass.getClassName() 
                << "::" 
                << fileclass.getClassName() 
                << "()" 
                << newline(1) 
                << "{" 
                << newline(1);

        for (unsigned int i = 0; i < variables.size(); i++)
        {
            outfile << indent(1) << variables[i][IDENTIFIER] << " = ";

            if (!variables[i][TYPE].compare("string"))
                outfile << "\"N/A\"";
            else if (!variables[i][TYPE].compare("int"))
                outfile << "0";
            else if (!variables[i][TYPE].compare("float") 
                     || !variables[i][TYPE].compare("double"))
                outfile << "0.0";
            else if (!variables[i][TYPE].compare("bool"))
                outfile << "false";
            else if (!variables[i][TYPE].compare("char"))
                outfile << "'NUL'";

            outfile << ";" << newline(1);
        }

        outfile << "}" << newline(2);
    }

    if (fileclass.getVariablesConstructor())
    {
        outfile << fileclass.getClassName() 
                << "::" 
                << fileclass.getClassName() 
                << "(" 
                << variables[0][TYPE] 
                << " " 
                << variables[0][IDENTIFIER];

        for (unsigned int i = 1; i < variables.size(); i++)
            outfile << ", " << variables[i][TYPE] << " " << variables[i][IDENTIFIER];

        outfile << ")" << newline(1) << "{" << newline(1);

        for (unsigned int i = 0; i < variables.size(); i++)
            outfile << indent(1) << "this->" << variables[i][IDENTIFIER] << " = " 
                    << variables[i][IDENTIFIER] << ";" << newline(1);

        outfile << "}" << newline(2);
    }
}

void writeCustomFunctionDeclarations(ofstream &outfile)
{
    outfile << indent(2) << "void toString();" << newline(1);
    outfile << "};" << newline(2);
}

void writeCustomFunctionImplementations(ofstream &outfile, Class &fileclass)
{
    vector < vector<string> > variables = fileclass.getVariables();

    outfile << "void " 
            << fileclass.getClassName() 
            << "::toString()" 
            << newline(1) 
            << "{" 
            << newline(1);

    for (unsigned int i = 0; i < variables.size(); i++)
        outfile << indent(1) 
                << "cout << " 
                << variables[i][IDENTIFIER] 
                << " << endl;" 
                << newline(1);

    outfile << "}" << newline(1);
}

void writeHeader(ofstream &outfile, Class &fileclass)
{
    fileclass.generateFileName();
    fileclass.generateAltFileName();
    
    outfile << "/*" << newline(1)
            << " * " << fileclass.getFileName() << newline(1)
            << " * " << newline(1) 
            << " * Description" << newline(1) 
            << " * " << newline(1)
            << " * David Alejandro Martinez Tristan" << newline(1)
            << " * " << getCurrentDate() << newline(1)
            << " */" << newline(2);

    outfile << "#ifndef " << fileclass.getAltFileName() << newline(1)
            << "#define " << fileclass.getAltFileName() << newline(1)
            << "#include <iostream>" << newline(2)
            << "using namespace std;" << newline(2)
            << "class " << fileclass.getClassName() << newline(1) 
            << "{" << newline(1);
}

void writeFooter(ofstream &outfile)
{
    outfile << "#endif";
}

void writeGetterDeclarations(ofstream &outfile, Class &fileclass)
{
    vector< vector<string> > variables = fileclass.getVariables();

    for (unsigned int i = 0; i < variables.size(); i++)
    {
        outfile << indent(2) 
                << variables[i][TYPE] 
                << " get" 
                << variables[i][ALT_IDENTIFIER] 
                << "();" 
                << newline(1);  
    }
}

void writeGetterImplementations(ofstream &outfile, Class &fileclass)
{
    vector< vector<string> > variables = fileclass.getVariables();

    for (unsigned int i = 0; i < variables.size(); i++)
    {
        outfile << variables[i][TYPE] 
                << " " 
                << fileclass.getClassName() 
                << "::get" 
                << variables[i][ALT_IDENTIFIER] 
                << "()" 
                << newline(1);

        outfile << "{" 
                << newline(1) 
                << indent(1)
                << "return " 
                << variables[i][IDENTIFIER] 
                << ";" 
                << newline(1) 
                << "}" 
                << newline(2);
    }
}

void writeSetterDeclarations(ofstream &outfile, Class &fileclass)
{
    vector< vector<string> > variables = fileclass.getVariables();

    for (unsigned int i = 0; i < variables.size(); i++)
    {
        outfile << indent(2) 
                << "void set" 
                << variables[i][ALT_IDENTIFIER] 
                << "(" 
                << variables[i][TYPE] 
                << ");" 
                << newline(1);  
    }
}

void writeSetterImplementations(ofstream &outfile, Class &fileclass)
{
    vector< vector<string> > variables = fileclass.getVariables();

    for (unsigned int i = 0; i < variables.size(); i++)
    {
        outfile << "void " 
                << fileclass.getClassName()
                << "::set" 
                << variables[i][ALT_IDENTIFIER]
                << "("
                << variables[i][TYPE]
                << " "
                << variables[i][IDENTIFIER]
                << ")"
                << newline(1);

        outfile << "{" 
                << newline(1)
                << indent(1) 
                << "this->" 
                << variables[i][IDENTIFIER] 
                << " = " 
                << variables[i][IDENTIFIER]
                << ";"
                << newline(1)
                << "}" 
                << newline(2);
    }
}

void writeVariables(ofstream &outfile, string line)
{
    if (line.empty())
        return;

    int pos = line.find(" ");

    while (line.find(" ", pos + 1) != string::npos)
    {
        pos = line.find(" ", pos + 1);
        line.insert(pos, ",");
        pos++;
    }
    
    outfile << indent(1) << "private:" << newline(1) 
            << indent(2) << line << ";" << newline(1);
}

string indent(int hierarchy)
{
    string indentation = "";
    for (int i = 0; i < hierarchy; i++)
        indentation.append("\t");

    return indentation;
}

string newline(int quantity)
{
    string lines = "";
    for (int i = 0; i < quantity; i++)
        lines.append("\n");

    return lines;
}

string getCurrentDate()
{
    string date;
    stringstream stream;
    time_t now = time(0);
    tm *ltm = localtime(&now);

    stream << (ltm->tm_mday) << "/" << (ltm->tm_mon + 1) << "/" << (ltm->tm_year + 1900);
    date = stream.str();

    return date;
}