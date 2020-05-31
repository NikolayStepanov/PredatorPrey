#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QAbstractTableModel>

#include <mediatorfishmotor.h>

#include "common.h"

class GameModel: public QAbstractTableModel
{
    Q_OBJECT
    Q_ENUMS(Roles)

public:
    enum Roles
    {
      IdObject,
      TypeCell,
      IndexCell
    };

    QHash<int, QByteArray> roleNames() const override
    {
        QHash<int, QByteArray> roles;
        roles[IdObject] = "id";
        roles[TypeCell] = "type";
        roles[IndexCell] = "index";
        return roles;
    }

    explicit GameModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    Q_INVOKABLE void nextStep();
    Q_INVOKABLE void changeTypeCell(QVariant id, QVariant type, QVariant index);

    QVector<int> getAllRolesIndex();

public slots:
    void slotCellUpdate(size_t indexCell);

private:
    MediatorFishMotor * mediator;
};

#endif // GAMEMODEL_H
