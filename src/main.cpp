#include <QApplication>
#include <QPushButton>
#include <fstream>
#include "domain/User.h"
#include "repository/IssueRepository.h"
#include "ui/UserWindow.h"


using namespace std;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    IssueRepository issueRepository("issues.txt");
    ifstream file("users.txt");
    if (!file.is_open()) {
        fprintf(stderr, "failed to read users.txt\n");
        return -1;
    }
    User u;
    vector<QWidget*> widgets;
    while (file >> u) {
        auto widget = new UserWindow(nullptr, issueRepository, u);
        widget->show();
        widgets.push_back(widget);
    }
    file.close();
    const int execReturn = QApplication::exec();
    for (const auto &item: widgets) {
        delete item;
    }
    return execReturn;
}
