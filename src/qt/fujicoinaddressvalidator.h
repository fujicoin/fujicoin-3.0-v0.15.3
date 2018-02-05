// Copyright (c) 2011-2014 The Fujicoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef FUJICOIN_QT_FUJICOINADDRESSVALIDATOR_H
#define FUJICOIN_QT_FUJICOINADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class FujicoinAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit FujicoinAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** Fujicoin address widget validator, checks for a valid fujicoin address.
 */
class FujicoinAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit FujicoinAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // FUJICOIN_QT_FUJICOINADDRESSVALIDATOR_H
