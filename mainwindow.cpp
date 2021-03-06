#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <printer.h>
#include <portutility.h>
#include <ScannerAgentThread.h>
int item_price=0;
int item_quantity_length=6;

QString quantity_str;
QString quantity_result_str="";

QString WorkingPrinter = "epson" ;
// QString WorkingPrinter = "ray" ;

QString usb_printer="/dev/usb/lp0" ;
QString rs232_printer="/dev/ttyUSB1" ;
QString rs232_printer_BAUDRATE="19200" ;

QString rs232_VFD="/dev/ttymxc3";
QString rs232_VFD_BAUDRATE="38400";

QString rs232_Scanner="/dev/ttyUSB0";
QString rs232_Scanner_BAUDRATE="9600" ;


bool receipt_enable = false ;

struct product_detail
{
       QString price;
       QString product_name;
       QString product_id;
       QString quantity;
       QString total_price;

};
product_detail All_Product ;

struct product {
    QString price;
    QString product_name;
    QString product_id;

};
typedef struct list_element list_element;

struct list_element {
   product pp1 ;
   list_element * next;
};
product Item1;
product Item2;
product Item3;
product Item4;
product Item5;
product Item6;
product Item7;
product Item8;
product Item9;
product Item10;
product Item11;
product Item12;


/*
Item1 ("12" , "Belt" ,	"00A01" ) ,
        Item2 ("20" , "Jacket" ,"00A02" ) ,
        Item3 ("9" , "Shoes" ,	"00A03" ) ,
        Item4 ("12" , "Sweater" ,"00A04" ) ,
        Item5 ("36" , "Jeans" ,	"00A05" ) ,
        Item6 ("39" , "Skirt" ,	"00A06" ) ,
        Item7 ("38" , "Sweatshirt" ,"00A07" ) ,
        Item8 ("28" , "Pajamas" ,"00A08" ) ,
        Item9 ("28" , "Slacks" ,"00A09" ) ,
        Item10 ("33" , "T-shirt" ,"00A10" ) ,
        Item11 ("27" , "Taincoat" ,"00A11" ) ,
        Item12 ("25" , "Socks" ,"00A12" ) ;
*/
QGraphicsScene *scene;


void MainWindow::configureIODevice()
{
    WorkingPrinter = "epson" ;
    // QString WorkingPrinter = "ray" ;

    usb_printer="/dev/usb/lp0" ;
    rs232_printer="/dev/ttyUSB1" ;
    rs232_printer_BAUDRATE="19200" ;

    rs232_VFD="/dev/ttymxc3";
    rs232_VFD_BAUDRATE="38400";

    rs232_Scanner="/dev/ttyUSB0";
    rs232_Scanner_BAUDRATE="9600" ;

}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this, SIGNAL(itemSelect(int)),this, SLOT(doitemSelect(int)));
    connect(this, SIGNAL(numSelect(int)),this, SLOT(donumSelect(int)));
	current_total=0;

    //openScanner();   // Evan modified
    prepare_product_data();   // Evan modified
}

void MainWindow::prepare_product_data()
{
    Item1.price ="12";
    Item1.product_name="Belt";
    Item1.product_id="00A01";

    Item2.price ="20";
    Item2.product_name="Jacket";
    Item2.product_id="00A02";

    Item3.price ="9";
    Item3.product_name="Shoes";
    Item3.product_id="00A03";

    Item4.price ="12";
    Item4.product_name="Sweater";
    Item4.product_id="00A04";

    Item5.price ="36";
    Item5.product_name="Jeans";
    Item5.product_id="00A05";

    Item6.price ="39";
    Item6.product_name="Skirt";
    Item6.product_id="00A06";

    Item7.price ="38";
    Item7.product_name="Sweatshirt";
    Item7.product_id="00A07";

    Item8.price ="28";
    Item8.product_name="Pajamas";
    Item8.product_id="00A08";

    Item9.price ="28";
    Item9.product_name="Slacks";
    Item9.product_id="00A09";

    Item10.price ="33";
    Item10.product_name="T-shirt";
    Item10.product_id="00A10";

    Item11.price ="27";
    Item11.product_name="Taincoat";
    Item11.product_id="00A11";

    Item12.price ="25";
    Item12.product_name="Socks";
    Item12.product_id="00A12";

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::doitemSelect(int select)
{
    switch(select) {

            case 1:
                item_price=12;
                showPrice(item_price);
                showSelectImage(":/picture/picture/P_01.bmp");
                break;

            case 2:
                item_price=20;
                showPrice(item_price);
                showSelectImage(":/picture/picture/P_02.bmp");
                break;

            case 3:
                item_price=9;
                showPrice(item_price);
                showSelectImage(":/picture/picture/P_03.bmp");
                break;

            case 4:
                item_price=12;
                showPrice(item_price);
                showSelectImage(":/picture/picture/P_04.bmp");
                break;

            case 5:
                item_price=36;
                showPrice(item_price);
                showSelectImage(":/picture/picture/P_05.bmp");
                break;

            case 6:
                item_price=39;
                showPrice(item_price);
                showSelectImage(":/picture/picture/P_06.bmp");
                break;

            case 7:
                item_price=38;
                showPrice(item_price);
                showSelectImage(":/picture/picture/P_07.bmp");
                break;

            case 8:
                item_price=28;
                showPrice(item_price);
                showSelectImage(":/picture/picture/P_08.bmp");
                break;

            case 9:
                item_price=28;
                showPrice(item_price);
                showSelectImage(":/picture/picture/P_09.bmp");
                break;

            case 10:
                item_price=33;
                showPrice(item_price);
                showSelectImage(":/picture/picture/P_10.bmp");
                break;

            case 11:
                item_price=27;
                showPrice(item_price);
                showSelectImage(":/picture/picture/P_11.bmp");
                break;

            case 12:
                item_price=25;
                showPrice(item_price);
                showSelectImage(":/picture/picture/P_12.bmp");
                break;

            default:
                item_price=0;
                showPrice(item_price);
        }

}

void MainWindow::donumSelect(int num)
{
    {
        switch(num) {

                case 10:
                    quantity_str.clear();
                    quantity_str="0";
                    showQuantity(quantity_str);
                    break;

                case 100:
                    quantity_str.clear();
                    quantity_str="00";
                    showQuantity(quantity_str);
                    break;

                case 1000:
                    quantity_str.clear();
                    quantity_str="000";
                    showQuantity(quantity_str);
                    break;

                case 1:
                    quantity_str.clear();
                    quantity_str="1";
                    showQuantity(quantity_str);
                    break;

                case 2:
                    quantity_str.clear();
                    quantity_str="2";
                    showQuantity(quantity_str);
                    break;

                case 3:
                    quantity_str.clear();
                    quantity_str="3";
                    showQuantity(quantity_str);
                    break;

                case 4:
                    quantity_str.clear();
                    quantity_str="4";
                    showQuantity(quantity_str);
                    break;

                case 5:
                    quantity_str.clear();
                    quantity_str="5";
                    showQuantity(quantity_str);
                    break;

                case 6:
                    quantity_str.clear();
                    quantity_str="6";
                    showQuantity(quantity_str);
                    break;

                case 7:
                    quantity_str.clear();
                    quantity_str="7";
                    showQuantity(quantity_str);
                    break;

                case 8:
                    quantity_str.clear();
                    quantity_str="8";
                    showQuantity(quantity_str);
                    break;

                case 9:
                    quantity_str.clear();
                    quantity_str="9";
                    showQuantity(quantity_str);
                    break;

                default:
                    quantity_str.clear();
                    quantity_str="";
                    showQuantity(quantity_str);
            }

    }
}



void MainWindow::showSelectImage(QString image_name)
{
    if(scene)
        delete scene;

    QImage image;
    image.load(image_name);
    scene =  new  QGraphicsScene;
    scene->addPixmap(QPixmap::fromImage(image));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->resize(image.width() + 10, image.height() + 10);
    ui->graphicsView->show();
}


void MainWindow::getProductDetail(QString price , QString product_name , QString product_id)
{
    All_Product.price = price;
    All_Product.product_name = product_name;
    All_Product.product_id = product_id;

}
void MainWindow::clearProductDetail()
{
    All_Product.price = "";
    All_Product.product_name = "";
    All_Product.product_id = "";
    All_Product.quantity = "";
    All_Product.total_price = "" ;
    receipt_enable = false;
    quantity_result_str.clear(); //Evan modified 2014.0227.20:42
    current_total=0;   //Evan modified 2014.0227.20:42
}
void MainWindow::setCalculateResult(QString quantity, QString total) {
    // TODO Auto-generated method stub
    All_Product.quantity = quantity;
    All_Product.total_price = total ;
    printf("setCalculateResult -> total = %s \n" , All_Product.total_price.toStdString().c_str()  );
}

void MainWindow::makeReceipt()
{
    receipt_enable = true;
}
void MainWindow::printReceipt()
{
    //QString strbuf="epson";
    QString strbuf= WorkingPrinter;
    if (receipt_enable == true)
    {
       // printf("print receipt\n");
        printer_fun(strbuf);
        //printer_fun("ray");
       // Log.d("printer", "VFD open");
        print_VFD();
        receipt_enable = false;
    }

}


void MainWindow::printer_fun (QString printer_vendor)
{

    /*   printer myprinter ;
     myprinter.printerOpen("/dev/ttyUSB0" , false);
     myprinter.printerSetSpeed(9600);
     myprinter.printerWrite("test") ;

     sleep(1);
     myprinter.printerRead();
     myprinter.printerClose();

 */
  QString strbuf_pinfo;

  strbuf_pinfo+="   Item id:"; strbuf_pinfo+=All_Product.product_id.toStdString().c_str();
  strbuf_pinfo+=" " ; strbuf_pinfo +=All_Product.product_name.toStdString().c_str();
  strbuf_pinfo+= " - price " ; strbuf_pinfo+=All_Product.price.toStdString().c_str();
  strbuf_pinfo+=" * " ; strbuf_pinfo+=All_Product.quantity.toStdString().c_str();
  QString strbuf_ptotal;

  strbuf_ptotal+="        $"; strbuf_ptotal+=All_Product.total_price.toStdString().c_str();

     printf("product_id = %s , product_name =%s , product_price = %s , product_quantity =%s ,totoal_price =%s  \n"
         ,All_Product.product_id.toStdString().c_str()
         ,All_Product.product_name.toStdString().c_str()
         ,All_Product.price.toStdString().c_str()
         ,All_Product.quantity.toStdString().c_str()
         ,All_Product.total_price.toStdString().c_str());


     if (printer_vendor== "epson")
     {
         PortUtility myprinter = PortUtility(usb_printer ,0 ,true );

        printf("printer_vendor== epson \n") ;

        if (myprinter.open() == -1)
         {
             printf("usb printer port open fail \n");

         }
         myprinter.init();
        // sleep(1);
         myprinter.print("*****EPSON Receipt START*****");
       //  sleep(1);
         myprinter.print_and_return();
        // sleep(1);
         myprinter.PrintLogo(1); // Printer number 1
// sleep(1);

         myprinter.formFeed();
         myprinter.init();
         myprinter.Enlarged_Normal();
         myprinter.print("Tweverlight Corp ");
         myprinter.print_and_return();
         myprinter.lineFeed();
         myprinter.init();
         myprinter.DoubleStrike_Normal();
         myprinter.print("    Unified Serial No:12345678 ");
         myprinter.lineFeed();
         myprinter.init();
         myprinter.print("      ");
         myprinter.DoubleStrike_Emphasized();
         myprinter.Set_white_black();

         myprinter.print("Evan Agency Receipt");
         myprinter.lineFeed();
         //sleep(1);
         myprinter.lineFeed();

         myprinter.init();
         myprinter.formFeed();
         myprinter.Emphasized();

         myprinter.print( strbuf_pinfo  ); //print product info


         myprinter.print_and_return();
         myprinter.lineFeed();
         sleep(1);
         myprinter.lineFeed();

         myprinter.init();
         myprinter.Enlarged_Normal();
         myprinter.print("Total :");
         myprinter.Underline_Mode();

         myprinter.print(strbuf_ptotal);  //print product total price

         myprinter.lineFeed();

         myprinter.init();

         myprinter.SetBarCodeHeight(32);
         myprinter.SetBarCodeHSize(2);  //Horizontal  SIZE 0~ 6
         myprinter.BarCodePrint128(10,"RR.","123465");

         myprinter.init();

         myprinter.DoubleStrike_Emphasized();
         myprinter.print("     Service (FAX) : 02-123456789");
         myprinter.print_and_return();
         myprinter.lineFeed();
         myprinter.print("     Service (TEL) : 02-987654321");
         myprinter.print_and_return();
         myprinter.init();
         myprinter.formFeed();
         myprinter.formFeed();


         myprinter.print("*****Receipt END*****");
         myprinter.print_and_return();

       //  escprinter.Cutter();
         myprinter.close();
    }else if (printer_vendor== "ray")
    {
    PortUtility rayprinter = PortUtility(rs232_printer ,rs232_printer_BAUDRATE.toInt() ,false );
         if (rayprinter.open() == -1)
         {
              printf("RS232 ray printer port open fail \n");
              return;
         }
         rayprinter.init();



         rayprinter.print("*****RAY Receipt START*****");

         rayprinter.print_and_return();

         rayprinter.PrintLogo(1); // Printer number 1

         rayprinter.formFeed();
         rayprinter.init();
         rayprinter.Enlarged_Normal();
         rayprinter.print("Tweverlight Corp ");
         rayprinter.print_and_return();
         //rayprinter.lineFeed();
         rayprinter.init();
         rayprinter.DoubleStrike_Normal();
         rayprinter.print("    Unified Serial No:12345678 ");
         rayprinter.lineFeed();
         rayprinter.init();
         rayprinter.print("      ");
         rayprinter.DoubleStrike_Emphasized();
         rayprinter.Set_white_black();

         rayprinter.print("Evan Agency Receipt");
         rayprinter.lineFeed();

         rayprinter.lineFeed();

         rayprinter.init();
         rayprinter.formFeed();
         rayprinter.Emphasized();

         rayprinter.print( strbuf_pinfo  ); //print product info

         rayprinter.print_and_return();

         rayprinter.lineFeed();


         rayprinter.init();
         rayprinter.Enlarged_Normal();
         rayprinter.print("Total :");
         rayprinter.Underline_Mode();
         rayprinter.print(strbuf_ptotal);  //print product total price
         rayprinter.lineFeed();

         rayprinter.init();

         rayprinter.SetBarCodeHeight(32);
         rayprinter.SetBarCodeHSize(2);  //Horizontal  SIZE 0~ 6
         rayprinter.BarCodePrintEAN13(12,"123465789012");
         rayprinter.init();

         rayprinter.DoubleStrike_Emphasized();
         rayprinter.print("     Service (FAX) : 02-123456789");
         rayprinter.print_and_return();
         //rayprinter.lineFeed();
         rayprinter.print("     Service (TEL) : 02-987654321");
         rayprinter.print_and_return();
         rayprinter.init();
         rayprinter.formFeed();
         rayprinter.formFeed();

         rayprinter.print("*****Receipt END*****");
         rayprinter.print_and_return();
         //rayprinter.Cutter();*/
         rayprinter.close();


    }

}



int MainWindow::print_VFD() {
    // TODO Auto-generated method stub
    QString strbuf="";
    PortUtility vfd = PortUtility(rs232_VFD ,rs232_VFD_BAUDRATE.toInt() ,false );
    if (vfd.open() == -1)
    {
        printf( "VFD printer port open fail");
        return 1;
    }
    vfd.init();
    strbuf+=All_Product.product_name; strbuf+=" * ";strbuf+=All_Product.quantity;
    strbuf+=vfd_0a;strbuf+=vfd_return ; strbuf+="price:" ; strbuf+=All_Product.price;
    strbuf+=" " ; strbuf+= "Total:" ; strbuf+=All_Product.total_price;


    vfd.print(strbuf);
   // vfd.print("" + this.All_Product.product_name  + " * " +  this.All_Product.Quantity + vfd.vfd_0a
   //         + vfd.vfd_return + "price:" + this.All_Product.price  + " " + "Total:" + this.All_Product.Total_price    );

    // vfd.print("1" + vfd.vfd_0a +"23456" + vfd.vfd_return +"ttt" + vfd.vfd_clear );

    vfd.close();
    return 0;
}


void MainWindow::showPrice(int price)
{
    ui->lcdNumber_price->display(price);

    ui->label_Quantity->setText("Quantity");
    quantity_result_str.clear();
    ui->lcdNumber_quantity->display(quantity_result_str);
}

void MainWindow::showQuantity(QString Quantity)
{
    ui->label_Quantity->setText("Quantity");

    quantity_result_str+=Quantity;

    if(quantity_result_str.at(0)=='0')
        quantity_result_str.clear();

    if(quantity_result_str.length()>item_quantity_length){
        quantity_result_str.clear();
        if(Quantity.at(0)=='0')
            quantity_result_str.clear();
        else
            quantity_result_str=Quantity;
    }
    ui->lcdNumber_quantity->display(quantity_result_str);
}

int MainWindow::showTotal(QString Total)
{
    if(quantity_result_str.isEmpty())
        return -1;

    int total_price = (quantity_result_str.toInt()*item_price); //Evan modified
    current_total +=total_price;  //Evan modified 2014.0227.20:42
   
    QString str_total_price = QString::number(total_price); //Evan modified
    ui->lcdNumber_quantity->display(current_total);  //quantity_result_str.toInt()*item_price
 
    printf("current_total %d \n" ,current_total);
    setCalculateResult(quantity_result_str,str_total_price);  //Evan modified
    quantity_result_str.clear();
     All_Product.total_price = QString::number(current_total);  //Evan modified 2014.0227.20:42
    ui->label_Quantity->setText("Total");
    return 0;
}

void MainWindow::on_pushButton_item1_clicked()
{
    emit itemSelect(1);
     getProductDetail(Item1.price, Item1.product_name, Item1.product_id);
}

void MainWindow::on_pushButton_item2_clicked()
{
    emit itemSelect(2);
     getProductDetail(Item2.price, Item2.product_name, Item2.product_id);
}

void MainWindow::on_pushButton_item3_clicked()
{
    emit itemSelect(3);
     getProductDetail(Item3.price, Item3.product_name, Item3.product_id);
}

void MainWindow::on_pushButton_item4_clicked()
{
    emit itemSelect(4);
     getProductDetail(Item4.price, Item4.product_name, Item4.product_id);
}

void MainWindow::on_pushButton_item5_clicked()
{
    emit itemSelect(5);
     getProductDetail(Item5.price, Item5.product_name, Item5.product_id);
}

void MainWindow::on_pushButton_item6_clicked()
{
    emit itemSelect(6);
     getProductDetail(Item6.price, Item6.product_name, Item6.product_id);
}

void MainWindow::on_pushButton_item7_clicked()
{
    emit itemSelect(7);
     getProductDetail(Item7.price, Item7.product_name, Item7.product_id);
}

void MainWindow::on_pushButton_item8_clicked()
{
    emit itemSelect(8);
     getProductDetail(Item8.price, Item8.product_name, Item8.product_id);
}

void MainWindow::on_pushButton_item9_clicked()
{
    emit itemSelect(9);
     getProductDetail(Item9.price, Item9.product_name, Item9.product_id);
}

void MainWindow::on_pushButton_item10_clicked()
{
    emit itemSelect(10);
     getProductDetail(Item10.price, Item10.product_name, Item10.product_id);
}

void MainWindow::on_pushButton_item11_clicked()
{
    emit itemSelect(11);
     getProductDetail(Item11.price, Item11.product_name, Item11.product_id);
}
void MainWindow::on_pushButton_item12_clicked()
{
    emit itemSelect(12);
    getProductDetail(Item12.price, Item12.product_name, Item12.product_id);
}

void MainWindow::on_pushButton_num0_clicked()
{
    emit numSelect(10);
}

void MainWindow::on_pushButton_num00_clicked()
{
    emit numSelect(100);
}

void MainWindow::on_pushButton_num000_clicked()
{
    emit numSelect(1000);
}

void MainWindow::on_pushButton_num1_clicked()
{
    emit numSelect(1);
}

void MainWindow::on_pushButton_num2_clicked()
{
    emit numSelect(2);
}

void MainWindow::on_pushButton_num3_clicked()
{
    emit numSelect(3);
}

void MainWindow::on_pushButton_num4_clicked()
{
    emit numSelect(4);
}

void MainWindow::on_pushButton_num5_clicked()
{
    emit numSelect(5);
}

void MainWindow::on_pushButton_num6_clicked()
{
    emit numSelect(6);
}

void MainWindow::on_pushButton_num7_clicked()
{
    emit numSelect(7);
}

void MainWindow::on_pushButton_num8_clicked()
{
    emit numSelect(8);
}

void MainWindow::on_pushButton_num9_clicked()
{
    emit numSelect(9);
}

void MainWindow::on_pushButton_enter_clicked()
{
    if (-1 !=showTotal(quantity_result_str))
    {
        makeReceipt();
	print_VFD();
    }
    //showTotal(quantity_result_str);
}

void MainWindow::on_pushButton_admin_clicked()
{
     //---get the focus---
     admindialog.setModal(true);

     //---set dialog always top---
     //admindialog.setWindowFlags(Qt::WindowStaysOnTopHint);

     //---set dialog disable minimize button and set dialog always top---
     //admindialog.setWindowFlags( Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
     admindialog.setWindowFlags( Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);

     admindialog.show();

     //admindialog.setFixedSize(640,480);

     //---move dialog to center of screen---
     admindialog.setGeometry(
                 QStyle::alignedRect(
                     Qt::LeftToRight,
                     Qt::AlignCenter,
                     admindialog.size(),
                     qApp->desktop()->availableGeometry()
                 ));
	     
	admindialog.setFocus();
}

void MainWindow::on_pushButton_exit_clicked()
{
    this->close();
}

void MainWindow::on_pushButton_clear_clicked()
{
    quantity_result_str.clear();
    ui->lcdNumber_quantity->display(quantity_result_str);
    ui->label_Quantity->setText("Quantity");
    clearProductDetail(); //Evan modified
    print_VFD(); //Evan modified 2014.0227.20:42
}

void MainWindow::on_pushButton_print_clicked()
{
    printReceipt();
}
void MainWindow::receiveslot(QString s)
{
    //printf("receiveslot = %s \n" ,s);
   // QString string = QString::fromLocal8Bit(s);
    processBarcodeData(s);

}
void MainWindow::processBarcodeData(QString data)
{
    QString str = "BCDEF" ;
    if(QString::compare(data,str)== 0)
    {
        emit itemSelect(12);
        getProductDetail(Item12.price, Item12.product_name, Item12.product_id);
        printf("get PRODCUT NUMBER \n ");
    }

}
void MainWindow::openScanner()
{
    ScannerAgentThread *mth= new ScannerAgentThread(rs232_Scanner,rs232_Scanner_BAUDRATE) ;
    QObject::connect(mth,SIGNAL(send(QString)),this,SLOT(receiveslot(QString)));
    mth->start();

}

