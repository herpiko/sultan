/*
 * returnadddialog.cpp
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
#include "returnadddialog.h"
#include "ui_returnadddialog.h"
#include "keyevent.h"
#include "message.h"
#include "global_constant.h"
#include "guiutil.h"
#include "purchaseitemselectiondialog.h"
#include <QDebug>

using namespace LibGUI;
using namespace LibG;

ReturnAddDialog::ReturnAddDialog(LibG::MessageBus *bus, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReturnAddDialog)
{
    ui->setupUi(this);
    setMessageBus(bus);
    auto event = new KeyEvent(this);
    event->setFocusEvent(true);
    ui->linePurchaseItem->installEventFilter(event);
    connect(event, SIGNAL(focused(QObject*)), SLOT(purchaseItemFocused()));

    Message msg(MSG_TYPE::SUPLIER, MSG_COMMAND::QUERY);
    msg.setLimit(-1);
    sendMessage(&msg);
}

ReturnAddDialog::~ReturnAddDialog()
{
    delete ui;
}

void ReturnAddDialog::reset()
{
}

void ReturnAddDialog::fill(const QVariantMap &data)
{

}

void ReturnAddDialog::messageReceived(LibG::Message *msg)
{
    if(msg->isType(MSG_TYPE::SUPLIER)) {
        const QVariantList &list = msg->data("data").toList();
        populateSuplier(list);
    }
}

void ReturnAddDialog::populateSuplier(const QVariantList &list)
{
    ui->comboSuplier->clear();
    ui->comboSuplier->addItem(tr("-- Select Suplier --"), 0);
    for(auto &d : list) {
        const QVariantMap &m = d.toMap();
        ui->comboSuplier->addItem(m["name"].toString(), m["id"].toInt());
    }
    GuiUtil::selectCombo(ui->comboSuplier, mCurrentSuplier);
}

void ReturnAddDialog::purchaseItemFocused()
{
    PurchaseItemSelectionDialog dialog(mMessageBus, ui->comboSuplier->currentData().toInt(), this);
    dialog.exec();
    ui->doubleCount->setFocus(Qt::TabFocusReason);
}

void ReturnAddDialog::saveClicked()
{

}
