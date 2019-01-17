#ifndef TESTMODEL_H
#define TESTMODEL_H
#include <QAbstractTableModel>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <databasehelper.h>
#include <QLineEdit>
class testModel : public QAbstractTableModel
{
    int IdGroup;
    bool semester;
    bool formOfEducation;

    QSqlQuery* students;
    QSqlQuery* subjects;


public:
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    explicit testModel(QObject *parent , int, bool, bool);
    QVariant data(const QModelIndex &index, int role) const override;

    QSqlQuery* getSubjects() const;
    QSqlQuery* getStudents() const;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
    { return true; }
    QWidget* createEditor(QWidget *, const QStyleOptionViewItem &, const QModelIndex &) const
    { return new QLineEdit(); }





};

#endif // TESTMODEL_H
