#include <QApplication.h>
#include "GuiModel.h"
#include "MainWindow.h"

int main(int argc, char * argv[])
{
    QApplication app(argc, argv);

    GuiModel &model = GuiModel::Get();
    MainWindow window(model);
    window.show();
    return app.exec();
}
