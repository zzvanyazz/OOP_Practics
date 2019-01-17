#include "testmodel.h"
#include <QDebug>
testModel::testModel(QObject *parent, int Group, bool semester, bool formOfEducation):
    QAbstractTableModel(parent),
    IdGroup(Group),
    semester(semester),
    formOfEducation(formOfEducation)

{

    qDebug() << ">1<" << endl;
    if(formOfEducation)
        students  = new QSqlQuery(*dbHelper.getStudent("Grup = "+QString().number(Group)+" AND form_of_education = "+ QString().number(formOfEducation)+" group by surname"));
    else
         students  = new QSqlQuery(*dbHelper.getStudent("Grup = "+QString().number(Group)+" group by surname"));
    qDebug() << ">2<" << endl;
    subjects = new QSqlQuery(dbHelper.db);
    subjects->exec("SELECT DISTINCT subject FROM education_progress WHERE \"group\"="+QString().number(Group)+";");






}

int testModel::columnCount(const QModelIndex &parent) const {

    int a = 1;
    if(subjects->first())
        while(subjects->next()) a++;
    else return 1;
    return a+1;
}
int testModel::rowCount(const QModelIndex &parent) const {

    int a = 1;
    if(students->first())
        while(students->next()) a++;
    else return 1;
    return a+1;
}


QSqlQuery* testModel::getStudents() const{
    return students;
}
QSqlQuery* testModel::getSubjects() const{
    return subjects;
}
QVariant testModel::data(const QModelIndex &index, int role) const{

    if(role == Qt::DisplayRole){
        if (index.column() == 0 && index.row() == 0) return QVariant(" ");
        else if (index.column() == 0){


            students->seek(index.row()-1);
            return QVariant(students->value((int)DatabaseHelper::ColumnsOfStudent::surname).toString()+
                            students->value((int)DatabaseHelper::ColumnsOfStudent::name).toString());
        }
        else if (index.row() == 0){
            subjects->seek(index.column()-1);
            QSqlQuery *Sub = dbHelper.getSubject("ID = "+QString().number(subjects->value(0).toInt()));
            Sub->first();

           return Sub->value((int)DatabaseHelper::ColumnsOfSubject::name);

        }
        else{
            subjects->seek(index.column()-1);
            students->seek(index.row()-1);
            QSqlQuery *data = new QSqlQuery(dbHelper.db);
            data->exec("SELECT mark from education_progress WHERE student = "+students->value((int)DatabaseHelper::ColumnsOfStudent::ID).toString()
                       +" AND subject = "+subjects->value(0).toString()+" AND semester = "+QString().number(semester));
            if (data->first()){
                return data->value(0);
            }else{
                //delete data;
                return QVariant("-");
            }
        }

    }
    return QVariant();

}



