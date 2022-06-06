#include <QApplication>
#include <QPushButton>
#include <fstream>
#include "domain/User.h"
#include "repository/IssueRepository.h"
#include "ui/UserWindow.h"

using namespace std;


int main(int argc, char *argv[]) {
    // read the issues from file and create the repository
    IssueRepository issueRepository("issues.txt");

    // open the users file
    ifstream file("users.txt");
    if (!file.is_open()) {
        fprintf(stderr, "failed to read users.txt\n");
        return -1;
    }

    QApplication a(argc, argv);
    vector<QWidget*> userWindows;
    User user;

    while (file >> user) { // read the users and create a window (widget) for each user
        auto userWindow = new UserWindow(nullptr, issueRepository, user);
        userWindow->show();
        userWindows.push_back(userWindow);
    }

    // close the file, since all the users were read
    file.close();

    // start the application
    const int execReturn = QApplication::exec();

    // deallocate the dynamic allocated windows
    for (const auto &item: userWindows) {
        delete item;
    }

    return execReturn;
}
