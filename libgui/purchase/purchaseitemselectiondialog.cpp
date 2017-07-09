/*
 * purchaseitemselectiondialog.cpp
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
#include "purchaseitemselectiondialog.h"
#include "ui_purchaseitemselectiondialog.h"
#include "tableview.h"
#include "tableitem.h"
#include "tablemodel.h"
#include "guiutil.h"
#include "global_constant.h"
#include "headerwidget.h"
#include "db_constant.h"

using namespace LibGUI;
using namespace LibG;

PurchaseItemSelectionDialog::PurchaseItemSelectionDialog(LibG::MessageBus *bus, int suplier, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PurchaseItemSelectionDialog)
{
    ui->setupUi(this);
    auto model = ui->tableWidget->getModel();
    model->setMessageBus(bus);
    model->addColumn("barcode", tr("Barcode"));
    model->addColumn("name", tr("Name"));
    model->addColumn("count", tr("Count"), Qt::AlignRight);
    model->addColumnMoney("price", tr("Price"));
    model->addColumnMoney("total", tr("Sub-total"));
    model->addColumnMoney("discount", tr("Discount"));
    model->addColumnMoney("final", tr("Total"));
    model->addHeaderFilter("barcode", HeaderFilter{HeaderWidget::LineEdit, TableModel::FilterLike, QVariant()});
    model->addHeaderFilter("name", HeaderFilter{HeaderWidget::LineEdit, TableModel::FilterLike, QVariant()});
    model->setTypeCommand(MSG_TYPE::PURCHASE_ITEM, MSG_COMMAND::QUERY);
    model->setTypeCommandOne(MSG_TYPE::PURCHASE_ITEM, MSG_COMMAND::GET);
    model->setFilter("suplier_id", COMPARE::EQUAL, suplier);
    ui->tableWidget->setupTable();
    ui->tableWidget->getTableView()->horizontalHeader()->setStretchLastSection(true);
    GuiUtil::setColumnWidth(ui->tableWidget->getTableView(), QList<int>() << 150 << 200 << 100 << 100 << 100 << 100 << 100);
    model->refresh();
    connect(ui->tableWidget->getTableView(), SIGNAL(doubleClicked(QModelIndex)), SLOT(tableDoubleClicked(QModelIndex)));
}

PurchaseItemSelectionDialog::~PurchaseItemSelectionDialog()
{
    delete ui;
}

void PurchaseItemSelectionDialog::tableDoubleClicked(const QModelIndex &index)
{
    auto item = static_cast<TableItem*>(index.internalPointer());
    mItem.fill(item->data());
    close();
}

void PurchaseItem::fill(const QVariantMap &data)
{
    barcode = data["barcode"].toString();
    name = data["name"].toString();
    count = data["count"].toFloat();
    price = data["price"].toDouble();
    discount = data["discount"].toDouble();
    total = data["total"].toDouble();
    final = data["final"].toDouble();
}
