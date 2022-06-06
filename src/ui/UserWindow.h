//
// Created by kamui on 06.06.2022.
//

#ifndef ISSUES_MV_USERWINDOW_H
#define ISSUES_MV_USERWINDOW_H


#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QTableView>
#include "../repository/IssueRepository.h"
#include "../domain/User.h"
#include "IssuesModel.h"

class UserWindow: public QWidget {
Q_OBJECT
private:
    IssueRepository& issueRepository;
    User user;
public:
    UserWindow(QWidget *parent, IssueRepository &issueRepository, const User &user);

private:
    IssuesModel* issuesModel{};
    QTableView* issuesTableView{};
    QPushButton* removeSelectedClosedIssueButton{};

    QLineEdit* addIssueDescriptionLineEdit{};
    QPushButton* addIssueForTesterButton{};

    QPushButton* resolveIssueForProgrammerButton{};

    void initializeUI();
    void connectSignalsAndSlots();

    int getCurrentRow() const;
private slots:
    void handleSelectionChanged();
    void handleRemoveIssueButton();
    void handleAddIssueButton();
    void handleResolveIssueButton();
};


#endif //ISSUES_MV_USERWINDOW_H
