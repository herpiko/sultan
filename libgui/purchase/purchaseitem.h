#ifndef PURCHASEITEM_H
#define PURCHASEITEM_H

#include <QVariantMap>

namespace LibGUI {

struct PurchaseItem
{
    QString barcode;
    QString name;
    float count;
    double price;
    double discount;
    double total;
    double final;
    void fill(const QVariantMap &data);
};

}

#endif // PURCHASEITEM_H
