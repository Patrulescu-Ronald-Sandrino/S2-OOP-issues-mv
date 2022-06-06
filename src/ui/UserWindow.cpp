//
// Created by kamui on 06.06.2022.
//

#include <QHBoxLayout>
#include <QLabel>
#include <QFormLayout>
#include <QMessageBox>
#include "UserWindow.h"
#include "IssuesModel.h"

UserWindow::UserWindow(QWidget *parent, IssueRepository &issueRepository, const User &user): QWidget(parent), issueRepository(issueRepository), user(user) {
    initializeUI();
    connectSignalsAndSlots();
}

void UserWindow::initializeUI() {
    setWindowTitle(QString::fromStdString(user.getName() + " - " + user.getType()));

    auto mainLayout = new QVBoxLayout(this);
    issuesTableView = new QTableView(this);
    mainLayout->addWidget(issuesTableView);
    issuesModel = new IssuesModel(issueRepository);
    issuesTableView->setModel(issuesModel);
    issuesTableView->setSelectionMode(QAbstractItemView::SingleSelection);

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
    QObject::connect(issuesTableView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &UserWindow::handleSelectionChanged);
    QObject::connect(removeSelectedClosedIssueButton, &QPushButton::clicked, this, &UserWindow::handleRemoveIssueButton);
    if (user.getType() == "tester") {
        QObject::connect(addIssueForTesterButton, &QPushButton::clicked, this, &UserWindow::handleAddIssueButton);
    }
    else if (user.getType() == "programmer") {
        QObject::connect(resolveIssueForProgrammerButton, &QPushButton::clicked, this, &UserWindow::handleResolveIssueButton);
    }
}

int UserWindow::getCurrentRow() const {
    return issuesTableView->currentIndex().row();
}

void UserWindow::handleSelectionChanged() {
    auto row = getCurrentRow();
    if (row == -1) {
        removeSelectedClosedIssueButton->setDisabled(true);
        if (user.getType() == "programmer") {
            resolveIssueForProgrammerButton->setDisabled(true);
        }
    }
    else {
        auto issue = issueRepository.getAll()[row];
        removeSelectedClosedIssueButton->setEnabled(issue.isClosed());
        if (user.getType() == "programmer") {
            resolveIssueForProgrammerButton->setEnabled(issue.isOpen());
        }
    }
}

void UserWindow::handleRemoveIssueButton() {
    auto issue = issueRepository.getAll()[getCurrentRow()];
    try {
        issuesModel->removeIssue(issue);
    }
    catch (exception& e) {
        QMessageBox qMessageBox(QMessageBox::Information, "failed", e.what(), QMessageBox::Ok);
        qMessageBox.exec();
    }
}

void UserWindow::handleAddIssueButton() {
    auto description = addIssueDescriptionLineEdit->text().toStdString();
    try {
        issuesModel->addIssue(description, user);
    }
    catch (exception& e) {
        QMessageBox qMessageBox(QMessageBox::Information, "failed", e.what(), QMessageBox::Ok);
        qMessageBox.exec();
    }
}

void UserWindow::handleResolveIssueButton() {
    auto row = getCurrentRow();
    try {
        issuesModel->solveIssue(row, user);
    }
    catch (exception& e) {
        QMessageBox qMessageBox(QMessageBox::Information, "failed", e.what(), QMessageBox::Ok);
        qMessageBox.exec();
    }
}
