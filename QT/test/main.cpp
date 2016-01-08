#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QFont>
#include <QIcon>
#include <QLocale>
#include <QTranslator>
#include <QLibraryInfo>
//#include <QtWidgets>
#include "mafenetre.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    /* Pour traduire en FR */
    QString locale = QLocale::system().name().section('_', 0, 0);

    QTranslator translator;

    translator.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));

    app.installTranslator(&translator);
    /* Fin */

    MaFenetre w(230,120);

    w.show();

    return app.exec();
}
