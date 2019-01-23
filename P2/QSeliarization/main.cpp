#include <QCoreApplication>
#include <QXmlSerializer>
#include <QXmlQuery>
#include <QBuffer>
#include <QXmlStreamReader>
#include <QDebug>
#include <iostream>
#include <QFile>
#include <QDir>
#include <QXmlStreamWriter>


using namespace std;
class testSerialzationi{
public:
    int arg1;
    QString arg2;
    bool arg3;
    float arg4;
    testSerialzationi() = default;

    void serealize(QString name){
        QFile* file = new QFile(name);
        if (!file->open(QIODevice::WriteOnly | QIODevice::Text))
        {
            cout << "error1" << endl;
            return;
        }
        QXmlStreamWriter xml(file);
        xml.setAutoFormatting(true);
        xml.writeStartDocument();
        xml.writeStartElement("etap");
        xml.writeStartElement("first");
        xml.writeCharacters(QString().number(arg1));
        xml.writeEndElement();
        xml.writeStartElement("second");
        xml.writeCharacters(arg2);
        xml.writeEndElement();
        xml.writeStartElement("third");
        xml.writeCharacters(QString().number(arg3));
        xml.writeEndElement();
        xml.writeStartElement("fourth");
        xml.writeCharacters(QString().number(arg4));
        xml.writeEndElement();
        xml.writeEndElement();
        xml.writeEndDocument();
        file->close();
    }

    testSerialzationi(QString name){
        QFile* file = new QFile(name);
        if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
        {
            cout << "error1" << endl;
            return;
        }
        QXmlStreamReader xml(file);
        if (xml.atEnd()){
            cout << "error2" << endl;
            if(xml.hasError()) {
                cout << "error3" << endl;
                return;
            }
            return;
        }
        while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "etap"))
        {
            if (xml.tokenType() == QXmlStreamReader::StartElement)
            {
                if (xml.name() == "first")
                    arg1 =  xml.readElementText().toInt();
                if (xml.name() == "second")
                    arg2 =  xml.readElementText();
                if (xml.name() == "third")
                    arg3 =  xml.readElementText().toInt();
                if (xml.name() == "fourth"){
                    arg4 =  xml.readElementText().toFloat();
                    break;
                }
            }
            xml.readNext();
        }
        file->close();
    }


};


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    testSerialzationi* test1 = new testSerialzationi();
    test1->arg1 = 22;
    test1->arg2 = "test";
    test1->arg3 = true;
    test1->arg4 = 45.5555f;
    test1->serealize("config.xml");
    testSerialzationi* test2 = new testSerialzationi("config.xml");
    cout << test2->arg1 << test2->arg2.toStdString() << endl;


    return a.exec();
}
