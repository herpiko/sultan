/*
 * purchasereturnwidget.cpp
 * Copyright 2017 - ~, Apin <apin.klas@gmail.com>
 *
 * This file is part of Turbin.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include "purchasereturnwidget.h"
#include "ui_normalwidget.h"
#include "tablewidget.h"
#include "tablemodel.h"
#include "global_constant.h"
#include "guiutil.h"
#include "tableview.h"
#include "tableitem.h"
#include "dbutil.h"
#include "headerwidget.h"
#include "db_constant.h"
#include "message.h"
#include "flashmessagemanager.h"
#include "returnadddialog.h"
#include "tilewidget.h"
#include "preference.h"
#include <QMessageBox>

using namespace LibGUI;
using namespace LibG;

PurchaseReturnWidget::PurchaseReturnWidget(MessageBus *bus, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NormalWidget),
    mTableWidget(new TableWidget(this)),
    mTotalCredit(new TileWidget(this))
{
    ui->setupUi(this);
    setMessageBus(bus);
    ui->labelTitle->setText(tr("Purchase return"));
    mTotalCredit->setTitleValue(tr("Total Credit"), tr("loading..."));
    ui->verticalLayout->addWidget(mTotalCredit);
    ui->verticalLayout->addWidget(mTableWidget);
    mTableWidget->initCrudButton();
    auto model = mTableWidget->getModel();
    model->setMessageBus(bus);
    model->addColumn("created_at", tr("Date"), Qt::AlignLeft, [](TableItem *item, const QString &key) {
        return LibDB::DBUtil::sqlDateToDateTime(item->data(key).toString()).toString("dd-MM-yyyy");
    });
    model->addColumn("barcode", tr("Number"));
    model->addColumn("name", tr("Name"));
    model->addColumn("suplier", tr("Suplier"));
    /*model->addColumn("payment_type", tr("Type"), Qt::AlignLeft, [](TableItem *item, const QString &key) {
        return item->data(key).toInt() == PURCHASEPAYMENT::DIRECT ? tr("Direct") : tr("Deadline");
    });
    model->addColumn("deadline", tr("Deadline"), Qt::AlignLeft, [](TableItem *item, const QString &key) {
        return LibDB::DBUtil::sqlDateToDate(item->data(key).toString()).toString("dd-MM-yyyy");
    });
    model->addColumn("status", tr("Status"), Qt::AlignLeft, [](TableItem *item, const QString &key) {
        int type = item->data("payment_type").toInt();
        if(type == PURCHASEPAYMENT::DIRECT) return tr("Paid");
        return (item->data(key) == PAYMENT_STATUS::PAID ? tr("Paid") : tr("Unpaid"));
    });
    model->addColumnMoney("total", tr("Sub-total"));
    model->addColumn("discount_formula", tr("Disc. Form"));
    model->addColumnMoney("discount", tr("Discount"));
    model->addColumnMoney("final", tr("Total"));
    model->addHeaderFilter("number", HeaderFilter{HeaderWidget::LineEdit, TableModel::FilterLike, QVariant()});
    model->addHeaderFilter("suplier", HeaderFilter{HeaderWidget::LineEdit, TableModel::FilterLike, QVariant()});
    model->addHeaderFilter("payment_type", HeaderFilter{HeaderWidget::Combo, TableModel::FilterEQ, QVariant()});
    model->addHeaderFilter("status", HeaderFilter{HeaderWidget::Combo, TableModel::FilterEQ, QVariant()});*/
    model->setTypeCommand(MSG_TYPE::PURCHASE_RETURN, MSG_COMMAND::QUERY);
    model->setTypeCommandOne(MSG_TYPE::PURCHASE_RETURN, MSG_COMMAND::GET);
    mTableWidget->setupTable();
    GuiUtil::setColumnWidth(mTableWidget->getTableView(), QList<int>() << 150 << 150 << 200 << 100 << 100 << 100 << 100 << 100 << 100);
    mTableWidget->getTableView()->horizontalHeader()->setStretchLastSection(true);
    /*auto button = new QPushButton(QIcon(":/images/16x16/money-arrow.png"), "");
    button->setToolTip(tr("Payment"));
    button->setFlat(true);
    connect(button, SIGNAL(clicked(bool)), SLOT(paymentClicked()));
    mTableWidget->addActionButton(button);*/
    model->setSort("created_at DESC");
    model->refresh();

    connect(mTableWidget, SIGNAL(addClicked()), SLOT(addClicked()));
    connect(mTableWidget, SIGNAL(updateClicked(QModelIndex)), SLOT(updateClicked(QModelIndex)));
    connect(mTableWidget, SIGNAL(deleteClicked(QModelIndex)), SLOT(deleteClicked(QModelIndex)));
    //connect(mAddDialog, SIGNAL(successAdd()), mTableWidget->getModel(), SLOT(refresh()));
    //connect(mAddDialog, SIGNAL(successUpdate(QVariant)), mTableWidget->getModel(), SLOT(resfreshOne(QVariant)));
    //connect(mTableWidget->getTableView(), SIGNAL(doubleClicked(QModelIndex)), SLOT(tableDoubleClicked(QModelIndex)));
    //connect(model, SIGNAL(firstDataLoaded()), SLOT(getSummary()));
}

void PurchaseReturnWidget::messageReceived(LibG::Message *msg)
{

}

void PurchaseReturnWidget::addClicked()
{
    ReturnAddDialog dialog(mMessageBus, this);
    dialog.reset();
    dialog.exec();
}

void PurchaseReturnWidget::updateClicked(const QModelIndex &index)
{

}

void PurchaseReturnWidget::deleteClicked(const QModelIndex &index)
{

}
