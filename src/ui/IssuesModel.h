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

    // TODO: IDEA: change the parameter to -int row- and then initialize the model in the constructor in order
    //  to not have access in this class to the repository, after the window is created
    void removeIssue(const Issue& issue);

    void addIssue(const string& description, const User& user);

    void solveIssue(int row, const User& user);
};


#endif //ISSUES_MV_ISSUESMODEL_H
