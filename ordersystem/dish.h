#ifndef DISH_H
#define DISH_H
#include <QString>
class dish{
private:
    int dishid;
    QString dname;
    int price;
public:
    dish(int id,QString n,int p){
        dishid=id;
        dname=n;
        price=p;
    }
    dish(){}
    int get_id(){return dishid;}
    QString get_name(){return dname;}
    int get_price(){return price;}

};

#endif // DISH_H
