/*
 * (c) Copyright Ascensio System SIA 2010-2019
 *
 * This program is a free software product. You can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License (AGPL)
 * version 3 as published by the Free Software Foundation. In accordance with
 * Section 7(a) of the GNU AGPL its Section 15 shall be amended to the effect
 * that Ascensio System SIA expressly excludes the warranty of non-infringement
 * of any third-party rights.
 *
 * This program is distributed WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR  PURPOSE. For
 * details, see the GNU AGPL at: http://www.gnu.org/licenses/agpl-3.0.html
 *
 * You can contact Ascensio System SIA at 20A-12 Ernesta Birznieka-Upisha
 * street, Riga, Latvia, EU, LV-1050.
 *
 * The  interactive user interfaces in modified source and object code versions
 * of the Program must display Appropriate Legal Notices, as required under
 * Section 5 of the GNU AGPL version 3.
 *
 * Pursuant to Section 7(b) of the License you must retain the original Product
 * logo when distributing the program. Pursuant to Section 7(e) we decline to
 * grant you any rights under trademark law for use of our trademarks.
 *
 * All the Product's GUI elements, including illustrations and icon sets, as
 * well as technical writing content are licensed under the terms of the
 * Creative Commons Attribution-ShareAlike 4.0 International. See the License
 * terms at http://creativecommons.org/licenses/by-sa/4.0/legalcode
 *
*/

#ifndef CMESSAGE_H
#define CMESSAGE_H

#include <QMessageBox>
#include <QLabel>
#include <QCoreApplication>
#include <QPushButton>
#include <initializer_list>
#include <memory>

namespace CMessageOpts {
    enum class moButtons {
        mbYesDefNo,
        mbYesNo,
        mbYesNoCancel,
        mbYesDefNoCancel,
        mbOkCancel,
        mbOkDefCancel,
        mbYesDefSkipNo
    };
}

class CMessagePrivateIntf;

class CMessage : public QDialog
{
public:
    explicit CMessage(QWidget *);
             CMessage(QWidget *, CMessageOpts::moButtons);
    ~CMessage() override;

    void setButtons(std::initializer_list<QString>);
    void setButtons(CMessageOpts::moButtons);
    void setIcon(int);
    void setText(const QString&);
    void applyForAll(const QString&, bool);
    bool isForAll();

    int info(const QString& m);
    int warning(const QString& m);
    int error(const QString& m);
    int confirm(const QString& m);

    static int info(QWidget *, const QString& m);
    static int warning(QWidget *, const QString& m);
    static int error(QWidget *, const QString& m);
    static int confirm(QWidget *, const QString& m);

private:
    QWidget * m_boxButtons = nullptr;
    QWidget * m_centralWidget;
    QLabel * m_message,
           * m_typeIcon;
    int m_modalresult;

    void modal();

    friend class CMessagePrivateIntf;
    std::unique_ptr<CMessagePrivateIntf> m_priv;

    Q_DECLARE_TR_FUNCTIONS(CMessage)
};

#endif // CMESSAGE_H
