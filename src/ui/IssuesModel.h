//
// Created by kamui on 06.06.2022.
//

#ifndef ISSUES_MV_ISSUESMODEL_H
#define ISSUES_MV_ISSUESMODEL_H


#include <QAbstractTableModel>
#include "../repository/IssueRepository.h"
#include "../domain/User.h"

class IssuesModel: public QAbstractTableModel {
private:
    IssueRepository& issueRepository;
public:
    IssuesModel(IssueRepository &issueRepository);

    int rowCount(const QModelIndex &parent) const override;

    int columnCount(const QModelIndex &parent) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    void removeIssue(int row);

    void addIssue(const string& description, const User& user);

    void solveIssue(int row, const User& user);

private:
    bool isRowInvalid(int row) const;

    void throwIfRowIsInvalid(int row) noexcept(false);
};


#endif //ISSUES_MV_ISSUESMODEL_H
