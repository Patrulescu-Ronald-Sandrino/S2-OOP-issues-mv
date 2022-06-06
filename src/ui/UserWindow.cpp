//
// Created by kamui on 06.06.2022.
//

#include <QHBoxLayout>
#include <QLabel>
#include <QFormLayout>
#include <QMessageBox>
#include "UserWindow.h"
#include "IssuesModel.h"

UserWindow::UserWindow(QWidget *parent, IssuesModel* issuesModel, const User &user): QWidget(parent), issuesModel(issuesModel), user(user) {
    initializeUI();
    connectSignalsAndSlots();
}

void UserWindow::initializeUI() {
    setWindowTitle(QString::fromStdString(user.getName() + " - " + user.getType()));

    auto mainLayout = new QVBoxLayout(this);

    issuesTableView = new QTableView(this);
    mainLayout->addWidget(issuesTableView);
    issuesTableView->setModel(issuesModel);
    issuesTableView->setSelectionMode(QAbstractItemView::SingleSelection);

    removeSelectedClosedIssueButton = new QPushButton("&Remove");
    mainLayout->addWidget(removeSelectedClosedIssueButton);

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
        mainLayout->addWidget(resolveIssueForProgrammerButton);
    }
}

void UserWindow::connectSignalsAndSlots() {
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

void UserWindow::handleRemoveIssueButton() {
    callAndHandleAction([&]() {
        issuesModel->removeIssue(getCurrentRow());
    });
}

void UserWindow::handleAddIssueButton() {
    callAndHandleAction([&]() {
        auto description = addIssueDescriptionLineEdit->text().toStdString();
        issuesModel->addIssue(description, user);
    });
}

void UserWindow::handleResolveIssueButton() {
    callAndHandleAction([&]() {
        issuesModel->solveIssue(getCurrentRow(), user);
    });
}

template <typename A>
void UserWindow::callAndHandleAction(A action) const {
    try {
        action();
    }
    catch (exception& e) {
        QMessageBox qMessageBox(QMessageBox::Information, "failed", e.what(), QMessageBox::Ok);
        qMessageBox.exec();
    }
}
