#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QAbstractTableModel>

#include <fish.h>
#include <QList>
#include <QTime>
#include <QString>

class GameModel: public QAbstractTableModel
{
    Q_OBJECT
    Q_ENUMS(Roles)

public:
    enum Roles {
        Empty,
        Female_Prey,
        Male_Prey,
        Female_Predator,
        Male_Predator,
        Let
    };

    QHash<int, QByteArray> roleNames() const override {
        return {
            {Empty, "value" }
        };
    }

    explicit GameModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;


    void objectsMapGeneration();
    QList<int> searchNeighboringCells(size_t cellIndex);
    int searchFoodForShark(size_t cellIndex);


    Q_INVOKABLE void nextStep();
    Q_INVOKABLE void clear();
    Q_INVOKABLE void changeCellType();
    Q_INVOKABLE QString roleNames(int role) const;



private:
    static constexpr int width = 15;
    static constexpr int height = 15;

    static constexpr int size = width * height;

    using StateContainer = std::array<Roles, size>;
    StateContainer m_currentState;

    QList <Fish*>m_fishList;
    static bool areCellCoordinatesValid(const QPoint &coordinates);
    static bool areCellIndexValid(const int cellIndex);
    static QPoint cellCoordinatesFromIndex(const int cellIndex);
    static std::size_t cellIndex(const QPoint &coordinates);
    static QModelIndex& cellModelIndexFromIndex(const int cellIndex);
};

#endif // GAMEMODEL_H
