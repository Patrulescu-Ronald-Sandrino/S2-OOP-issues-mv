//
// Created by kamui on 06.06.2022.
//

#ifndef ISSUES_MV_USERWINDOW_H
#define ISSUES_MV_USERWINDOW_H


#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
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
    QPushButton* removeSelectedClosedIssueButton{};

    QLineEdit* addIssueDescriptionLineEdit{};
    QPushButton* addIssueForTesterButton{};

    QPushButton* resolveIssueForProgrammerButton{};

    void initializeUI();
    void connectSignalsAndSlots();
};


#endif //ISSUES_MV_USERWINDOW_H
