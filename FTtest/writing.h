

#ifndef WRITING_H
#define WRITING_H

#include <QAbstractItemModel>
#include <QBitArray>
#include <QObject>

class Writing: public QAbstractTableModel
{
    Q_OBJECT

public:
    Writing(QObject *parent = nullptr);

//    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
//    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

public slots:
    void setStartAddress(int address);
    void setNumberOfValues(const QString &number);

signals:
    void updateViewport();

public:
    int m_number;
    int m_address;
    QBitArray m_coils;
    QVector<quint16> m_holdingRegisters;
};

#endif // WRITING_H
