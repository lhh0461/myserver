#include "tinyxml2.h"
#include <string>
#include <iostream>

using namespace tinyxml2;
using namespace std;

void ParseAttr(XMLElement *elem)
{
    XMLElement *attr_elem = elem->FirstChildElement();
    cout << attr_elem->Value() << endl;
    cout << attr_elem->GetText() << endl;

    while ((attr_elem = attr_elem->NextSiblingElement()) != NULL) {
        cout << attr_elem->Value() << endl;
        if (strcmp(attr_elem->Value(), "args") == 0) {
            XMLElement *arg_elem = attr_elem->FirstChildElement();
            cout << "test " << arg_elem->GetText() << endl;
            const char *name = arg_elem->Value();
            while ((arg_elem = arg_elem->NextSiblingElement(name)) != NULL) {
                cout << "test " << arg_elem->GetText() << endl;
            }

        } else {
            cout << "test " << attr_elem->GetText() << endl;
        }
    }
}

void ParseXML(XMLElement *root)
{
    XMLElement *type_elem = root->FirstChildElement();

    const char *type_name = type_elem->Value();
    XMLElement *mytype_elem = type_elem;
    ParseAttr(mytype_elem);

    while ((mytype_elem = mytype_elem->NextSiblingElement(type_name)) != NULL) {
        ParseAttr(mytype_elem);
        //cout << mytype_elem->Value() << endl;
        //cout << mytype_elem->GetText() << endl;
    }

    while ((type_elem = type_elem->NextSiblingElement()) != NULL) {
        ParseAttr(type_elem);
        //cout << type_elem->Value() << endl;
        //cout << type_elem->GetText() << endl;
    }
}

int main()
{
    XMLDocument doc;
    doc.LoadFile("../rpc/config.xml");
    XMLElement *root = doc.FirstChildElement("root");
    if (root) {
        ParseXML(root);
    }
}
