//
// Created by kamui on 06.06.2022.
//

#include <QHBoxLayout>
#include <QTableView>
#include <QLabel>
#include <QFormLayout>
#include "UserWindow.h"
#include "IssuesModel.h"

UserWindow::UserWindow(QWidget *parent, IssueRepository &issueRepository, const User &user): QWidget(parent), issueRepository(issueRepository), user(user) {
    initializeUI();
    connectSignalsAndSlots();
}

void UserWindow::initializeUI() {
    setWindowTitle(QString::fromStdString(user.getName() + " - " + user.getType()));

    auto mainLayout = new QVBoxLayout(this);
    auto issuesTableView = new QTableView(this);
    mainLayout->addWidget(issuesTableView);
    issuesModel = new IssuesModel(issueRepository);
    issuesTableView->setModel(issuesModel);

    removeSelectedClosedIssueButton = new QPushButton("&Remove");
    mainLayout->addWidget(removeSelectedClosedIssueButton);
    removeSelectedClosedIssueButton->setDisabled(true);

    if (user.getType() == "tester") {
        auto addForm = new QWidget(this);
        mainLayout->addWidget(addForm);
        auto addFormLayout = new QFormLayout(addForm);

        auto addIssueDescriptionLabel = new QLabel("Description", this);
        addIssueDescriptionLineEdit = new QLineEdit(this);
        addIssueDescriptionLabel->setBuddy(addIssueDescriptionLineEdit);
        addFormLayout->addRow(addIssueDescriptionLabel, addIssueDescriptionLineEdit);

        addIssueForTesterButton = new QPushButton("&Add");
        mainLayout->addWidget(addIssueForTesterButton);
    }
    else if (user.getType() == "programmer") {
        resolveIssueForProgrammerButton = new QPushButton("Re&solve");
        resolveIssueForProgrammerButton->setDisabled(true);
        mainLayout->addWidget(resolveIssueForProgrammerButton);
    }
}

void UserWindow::connectSignalsAndSlots() {

}
