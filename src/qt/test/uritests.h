// Copyright (c) 2009-2018 The Bitcoin Core developers
// Copyright (c) 2014-2018 The Fujicoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef FUJICOIN_QT_TEST_URITESTS_H
#define FUJICOIN_QT_TEST_URITESTS_H

#include <QObject>
#include <QTest>

class URITests : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void uriTests();
};

#endif // FUJICOIN_QT_TEST_URITESTS_H
