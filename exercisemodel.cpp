#include "exercisemodel.h"

#include <QDomDocument>
#include <QFile>
#include <QDateTime>
#include <QDomNodeList>

ExerciseModel::ExerciseModel(const QString& exercisesxml, QObject *parent): QAbstractTableModel(parent)
{

    QDomDocument doc( "SPORTS" );
    QFile file( "/home/asier/projects/custommodel/exercises.xml" );
    //QFile file( exercisesxml );

    if( !file.open( QIODevice::ReadOnly ) )
        QStringList j;
            //return -1;
    if( !doc.setContent( &file ) )
    {
            file.close();
            //return -2;
    }
QStringList a;
a << "id" << "sport-subtype-id"  << "sport-type-id"  <<
  "date"  << "date" << "hour" << "duration"  <<
  "intensity"  << "distance" << "avg-speed" <<
  "avg-heartrate" <<  "ascent" << "hrm-file"  << "comment";

    exercises.append(a);

    QDomNodeList anchors = doc.elementsByTagName("exercise");
    for (uint i = 0; i < anchors.length(); i++)
    {

         /*   qDebug("id="+anchors.item(i).namedItem("id").toElement().text());
            qDebug("sport_type="+anchors.item(i).namedItem("sport-type-id").toElement().text());
            qDebug("sport_subtype="+anchors.item(i).namedItem("sport-subtype-id").toElement().text());
            qDebug("date="+anchors.item(i).namedItem("date").toElement().text());

            QDateTime time = QDateTime::fromString(anchors.item(i).namedItem("date").toElement().text(),Qt::ISODate);

            qDebug("Day of the week:"+QString::number(time.date().day()));

            qDebug("duration="+anchors.item(i).namedItem("duration").toElement().text());
            qDebug("intensity="+anchors.item(i).namedItem("intensity").toElement().text());
            qDebug("distance="+anchors.item(i).namedItem("distance").toElement().text());
            qDebug("avg_speed="+anchors.item(i).namedItem("avg-speed").toElement().text());
            qDebug("avg_heartrate="+anchors.item(i).namedItem("avg-heartrate").toElement().text());
            qDebug("ascent="+anchors.item(i).namedItem("ascent").toElement().text());
            qDebug("hrm_file="+anchors.item(i).namedItem("hrm-file").toElement().text());
            qDebug("comment="+anchors.item(i).namedItem("comment").toElement().text());
*/
        QStringList b;

            b << anchors.item(i).namedItem("id").toElement().text()  <<
            anchors.item(i).namedItem("sport-subtype-id").toElement().text()   <<
            anchors.item(i).namedItem("sport-type-id").toElement().text()   <<
            anchors.item(i).namedItem("date").toElement().text()   <<
           "" << // QDateTime::fromString(anchors.item(i).namedItem("date").toElement().text(),Qt::ISODate)   <<
            //QString::number(time.date().day())   <<
                             "" <<
            anchors.item(i).namedItem("duration").toElement().text()   <<
            anchors.item(i).namedItem("intensity").toElement().text()   <<
            anchors.item(i).namedItem("distance").toElement().text()  <<
            anchors.item(i).namedItem("avg-speed").toElement().text()  <<
            anchors.item(i).namedItem("avg-heartrate").toElement().text()  <<
            anchors.item(i).namedItem("ascent").toElement().text()  <<
            anchors.item(i).namedItem("hrm-file").toElement().text()  <<
            anchors.item(i).namedItem("comment").toElement().text();

            exercises.append(b);



    }

    file.close();


}

int ExerciseModel::rowCount(const QModelIndex &parent ) const
{
  Q_UNUSED(parent);
  return exercises.count() - 2;
}
int ExerciseModel::columnCount(const QModelIndex &parent ) const
{
    Q_UNUSED(parent);
    return exercises.at(0).count();
}
QVariant ExerciseModel::headerData(int section,
                        Qt::Orientation orientation, int role) const
{
  if (orientation == Qt::Horizontal) {
    if (role == Qt::DisplayRole) {
      return exercises.at(0).at(section);
    }
  }
  return QAbstractTableModel::headerData(section, orientation, role);
}
QVariant ExerciseModel::data(const QModelIndex &index,
                                                int role) const
{
  if (!index.isValid()) return QVariant();
  QStringList exercisesRecord = exercises.at(index.row()+1);
  if (role == Qt::DisplayRole || role == Qt::EditRole) {
    return exercisesRecord.at(index.column());
  }
  if (role == Qt::ToolTipRole) {
    QString tip, key, value;
    tip = "<table>";
    int maxLines = exercisesRecord.count();
    for (int i = 0; i < maxLines; i++) {
       key = headerData(i, Qt::Horizontal, Qt::DisplayRole)
                                                .toString();
       value = exercisesRecord.at(i);
       if (!value.isEmpty())
          tip += QString("<tr><td><b>%1</b>: %2</td></tr>")
                                                .arg(key, value);
    }
    tip += "</table>";
    return tip;
  }
  return QVariant();
}
Qt::ItemFlags ExerciseModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}
bool ExerciseModel::setData(const QModelIndex & index,
                                const QVariant& value, int role)
{
  if (index.isValid() && (role == Qt::EditRole ||
                          role == Qt::DisplayRole)) {
    // add 1 to the row index to skip over the header
    exercises[index.row()+1][index.column()] = value.toString();
    emit dataChanged(index, index);
    return true;
  }
  return false;
}
bool ExerciseModel::insertRows(int row, int count,
                                        const QModelIndex & parent)
{
  Q_UNUSED(parent);
  QStringList emptyRecord;
  for (int i=0; i<columnCount(QModelIndex()); i++)
    emptyRecord.append(QString());
  beginInsertRows(QModelIndex(), row, row+count-1);
  for (int i=0; i<count; i++)
    exercises.insert(row+1, emptyRecord);
  endInsertRows();

  return true;
}

bool ExerciseModel::removeRows(int row, int count,
                                        const QModelIndex& parent)
{
  Q_UNUSED(parent);
  if (row-count-1 > exercises.count()-1) return false;
  beginRemoveRows(QModelIndex(), row, row+count-1);
  for(int i=0; i<count; i++)
    exercises.removeAt(row+1);
  endRemoveRows();
  return true;
}
QString ExerciseModel::toString() const
{
   QString ab;
   foreach (QStringList record, exercises) {
     ab += "\"";
     record.join("\",\"");
     ab += "\"\n";
   }
   return ab;
}
