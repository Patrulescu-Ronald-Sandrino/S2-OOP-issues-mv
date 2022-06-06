//
// Created by kamui on 06.06.2022.
//

#include "IssuesModel.h"
#include <QBrush>

IssuesModel::IssuesModel(IssueRepository &issueRepository) : issueRepository(issueRepository) {}

int IssuesModel::rowCount(const QModelIndex &parent) const {
    return issueRepository.size();
}

int IssuesModel::columnCount(const QModelIndex &parent) const {
    return 4;
}

QVariant IssuesModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
            case 0: return QString{"Description"};
            case 1: return QString{"Status"};
            case 2: return QString{"Reporter"};
            case 3: return QString{"Solver"};
            default: break;
        }
    }
    return {};
}

QVariant IssuesModel::data(const QModelIndex &index, int role) const {
    int row = index.row();
    int column = index.column();
    auto issue = issueRepository.getAll()[row];

    if (role == Qt::DisplayRole) {
        switch (column) {
            case 0: return QString::fromStdString(issue.getDescription());
            case 1: return QString::fromStdString(issue.getStatus());
            case 2: return QString::fromStdString(issue.getReporter());
            case 3: return QString::fromStdString(issue.getSolver());
            default: break;
        }
    }
    if (role == Qt::BackgroundRole) {
        if (row % 2 == 1) {
            return QBrush(QColor(220, 220, 220));
        }
    }

    return {};
}

Qt::ItemFlags IssuesModel::flags(const QModelIndex &index) const {
    return QAbstractTableModel::flags(index);
}

void IssuesModel::removeIssue(const Issue& issue) {
    issueRepository.removeIssue(issue.getDescription());
    emit dataChanged(createIndex(0, 0), createIndex(issueRepository.size(), 3)); // TODO: maybe: size - 1
}

void IssuesModel::addIssue(const string& description, const User& user) {
    if (description.empty())
        throw std::runtime_error("description must not be empty");
    auto size = issueRepository.size();
    beginInsertRows(QModelIndex(), size, size);
    issueRepository.addIssue(Issue(description, user.getName()));
    endInsertRows();
}

void IssuesModel::solveIssue(int row, const User& user) {
    if (row >= issueRepository.size() && row < 0) {
        throw std::runtime_error("invalid issue selected");
    }
    auto issue = issueRepository.getAll()[row];
    issue.solve(user.getName());
    issueRepository.updateIssue(issue);
    emit dataChanged(createIndex(row, 0), createIndex(row, 3));
}
