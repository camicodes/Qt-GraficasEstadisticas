#include "principal.h"
#include "ui_principal.h"

#include <QPainter>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

Principal::Principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);
    lienzo = QPixmap(500,500);
    this->dibujar();
    ui->outCuadro->setPixmap(lienzo);
    connect(ui->actionPromediar, SIGNAL(triggered()),
            this, SLOT(on_cmdPromediar_clicked()));
}

Principal::~Principal()
{
    delete ui;
}

void Principal::dibujar()
{    
    lienzo.fill(Qt::white);
    //Picasso
    QPainter painter(&lienzo);
    int xplano = 50;
    int yplano = 50;
    int xplano1 = xplano;
    int yplano2 = yplano+400;

    //Crear un pincel para el plano
    QPen pincel;
    pincel.setWidth(3);
    pincel.setColor(Qt::black);
    pincel.setJoinStyle(Qt::MiterJoin);
    painter.setPen(pincel);
    painter.drawLine(xplano1, yplano-30, xplano1, yplano+400);
    painter.drawLine(xplano1,yplano2,xplano1+400,yplano2);
    QColor colorLinea(138,43,226);
    pincel.setColor(colorLinea);
    painter.setPen(pincel);
    //Poner numeros al plano cartesiano
    int num = 100;
    for(int i=yplano; i<450; i+=100){
        painter.drawLine(xplano-5,i,xplano+5,i);
        QString linea = QString::number(num);
        painter.drawLine(xplano1-5, i, yplano2+5, i);
        linea = QString::number(num);
        painter.drawText(xplano-25,i,linea);
        num-=25;
    }
    //Colocar nombres a las barras
    QColor nota(87, 53, 78);
    pincel.setColor(nota);
    painter.setPen(pincel);
    for (int o=xplano1; o<450; o+=100) {
        QString nota1 = "NOTA 1";
        painter.drawText(xplano1+65, yplano+415, nota1);
        QString nota2 = "NOTA 2";
        painter.drawText(xplano1+183, yplano+415, nota2);
        QString nota3 = "NOTA 3";
        painter.drawText(xplano1+302, yplano+415, nota3);
    }

    //Graficar barras
    int xbarra = 0;
    int ybarra = 0;

    //Crear un pincel para los bordes
    QPen pincel2;
    pincel2.setWidth(4);
    QColor colorBorde1( 5, 52, 56);
    pincel2.setColor(colorBorde1);
    QColor colorRelleno1(20, 208, 225);
    painter.setBrush(colorRelleno1);
    pincel2.setJoinStyle(Qt::MiterJoin);

    painter.setPen(pincel2);

    //Dibujar primera barra
    painter.drawRect(xbarra+80, ybarra+52, 100, 396);

    //Crear un objeto color para el relleno
    QColor colorRelleno(190,120,162);
    //Crear otro objeto color para el borde
    QColor colorBorde(78,3,48);

    //Cambiar el color del pincel
    pincel2.setColor(colorBorde);

    //Volver a establecer el pincel al "pintor"
    painter.setPen(pincel2);

    //Establecer el color al brush (relleno)
    painter.setBrush(colorRelleno);

    //Dibujar segunda barra
    //coordenada en x, y, ancho, alto
    painter.drawRect(xbarra+200,ybarra+197, 100, 250);

    //Creando colores de la tercera barra
    QColor colorRellenoBarra3(227, 183, 161);
    QColor colorBordeBarra3(59, 49, 42);

    //Estableciendo colores al pincel y al painter
    pincel2.setColor(colorBordeBarra3);
    painter.setPen(pincel2);
    painter.setBrush(colorRellenoBarra3);

    //Dibujar tercera barra
    painter.drawRect(xbarra+320, ybarra+297, 100, 150);
}

void Principal::on_actionGuardar_triggered()
{
    QString nombreArchivo = QFileDialog::getSaveFileName(
                this, "Guardar imagen", QString(), "Imagenes (*.png");
    if (!nombreArchivo.isEmpty()){
        if(lienzo.save(nombreArchivo))
            QMessageBox::information(this, "Guardar imagen", "Archivo guardado en: " + nombreArchivo);
        else
            QMessageBox::warning(this, "Guardar imagen", "No se pudo guardar el archivo");
    }
}

void Principal::on_cmdPromediar_clicked()
{    
    int nota1 = ui->inNota1->value();
    int nota2 = ui->inNota2->value();
    int nota3 = ui->inNota3->value();
    int promedio;
    promedio = ((nota1 + nota2 + nota3) / 3);
    qDebug () << promedio;
}
