// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2018 The Bitcoin Core developers
// Copyright (c) 2014-2018 The Fujicoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include "chainparamsseeds.h"

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 0 << CScriptNum(999) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 * CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1231006505, nBits=1d00ffff, nNonce=2083236893, vtx=1)
 *   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
 *   vMerkleTree: 4a5e1e
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "Mount Fuji is the most beautiful mountain in Japan, altitude is 3776.24m";
    const CScript genesisOutputScript = CScript();
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

void CChainParams::UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    consensus.vDeployments[d].nStartTime = nStartTime;
    consensus.vDeployments[d].nTimeout = nTimeout;
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 210000; //fujicoin do not use
        consensus.BIP34Height = 0;
        consensus.BIP34Hash = uint256S("0xadb6d9cfd74075e7f91608add4bd2a2ea636f70856183086842667a1597714a0");
        // consensus.BIP65Height = 0;
        // consensus.BIP66Height = 0;
        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 1.4 * 24 * 60 * 60; //1.4 days
        consensus.nPowTargetSpacing = 1.0 * 60;
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1512; // 75% of 2016
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        // Test dummy
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1522540800; // Apr 1st, 2018 (UTC)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1554076800; // Apr 1st, 2019 (UTC)

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1522540800; // Apr 1st, 2018 (UTC)
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1554076800; // Apr 1st, 2019 (UTC)

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1522540800; // Apr 1st, 2018 (UTC)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1554076800; // Apr 1st, 2019 (UTC)

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00000000000000000000000000000000000000000000000000048095ae8a7742");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0xe775a240c6e6d358ce523ba754aa5607a2c6a60c7bf08080557952a5f44a2bb9"); //1866650

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0x66;
        pchMessageStart[1] = 0x75;
        pchMessageStart[2] = 0x6a;
        pchMessageStart[3] = 0x69;
        nDefaultPort = 3777;
        nPruneAfterHeight = 100000;

        genesis = CreateGenesisBlock(1403910000, 2560786, 0x1e0ffff0, 1, 1 * COIN); //(nTime, nNonce, nBits, nVersion, genesisReward)
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0xadb6d9cfd74075e7f91608add4bd2a2ea636f70856183086842667a1597714a0"));
        assert(genesis.hashMerkleRoot == uint256S("0xf951a273c3055d1bb36b4291e7f9edd491c2d435bd5737318ef8a643cab84b61"));

        // Note that of those with the service bits flag, most only support a subset of possible options
        vSeeds.emplace_back("seed1.fujicoin.org", true); // Fujicoin official seed
        vSeeds.emplace_back("seed2.fujicoin.org", true); // Fujicoin official seed

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,36);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,16);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,164);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x88, 0xB2, 0x1E};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x88, 0xAD, 0xE4};

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;

        checkpointData = (CCheckpointData) {
            {
                {      0, uint256S("0xadb6d9cfd74075e7f91608add4bd2a2ea636f70856183086842667a1597714a0")},
                { 100000, uint256S("0x1d16bb119ef3b45134055b7e16a55f99d3ef5e211922037b9fb7274a988562f6")},
                { 200000, uint256S("0x588a542ff995394bc16731e3b53ea62f403fdfec4df5f8b4a38ad61a451523ec")},
                { 300000, uint256S("0x29d9a3d44ccc482980f6e5a2559c0588dd71e9bcc802dba8c6d18d10bb406ad2")},
                { 400000, uint256S("0x3c45c562ebccdf9ee7c0cb7509d9eebcbda9298636c9f4e3950fef2f6d29b8f5")},
                { 500000, uint256S("0x91c0fbc72fc8e421d85a922ec4f6477e5763c04729d13c4f58c1b79c83232b81")},
                { 600000, uint256S("0xc7105925a54a06fb27b4574f3b5732965d7c5b975d71b91c12c1672b68045c38")},
                { 700000, uint256S("0x0e9946a0196fcd286ef16d7873b38c9729ac8c1bc6b540ec12225ebc0291d5d2")},
                { 800000, uint256S("0xf3cb5bb24c7ae26f9ffe8001d594d4a951cc9a58589ac74519357add723f5602")},
                { 900000, uint256S("0x0b5b53332af404ac740965c717a3e797cff330d9d42fb8821eedb97856d11248")},
                {1000000, uint256S("0xe267f45f1552c735a0f879403030c3f0904e8e9e0dc84cf2e6d13fcc32520dc3")},
                {1100000, uint256S("0x34c2396e76d0dba38cce0f247766e1b85fad5938598f0a4eb29c3b5aeccbb60b")},
                {1200000, uint256S("0x00d47aac9bef0bfb211ebeabf5077520da5170cb269389955d1612aa0cb2757a")},
                {1300000, uint256S("0xa4f63f7b5b92a46e73cbf3e208f5dacb2b09a39287f561541a2fc90d44b97148")},
                {1400000, uint256S("0x86c187cf79e3723189221337b457947bf88448414205e1c37435c56a9dc55052")},
                {1500000, uint256S("0xda3ce4ee4d6715aa5b9b6b94099b0d05cf28585473ab206c8b179c7a73ebbde8")},
                {1600000, uint256S("0xfbe956df17cb237f6ad438c6f94215e383259b88226ebcf38f13c611313442a7")},
                {1700000, uint256S("0xaf35ad36a43ac08d1f2d764984ccd46855d4e968853bb2287a6662ea798d6383")},
                {1800000, uint256S("0x0f5353f137b5e3f0e45d5643843ba452ac84bb6470ba608eae71994f0be87412")},
            }
        };

        chainTxData = ChainTxData{
            1516945775, // * UNIX timestamp of last known number of transactions
            347536,     // * total number of transactions between genesis and that timestamp
                        //   (the tx=... number in the SetBestChain debug.log lines)
            0.01        // * estimated number of transactions per second after that timestamp
        };
    }
};

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 210000;
        consensus.BIP34Height = 1800000;
        consensus.BIP34Hash = uint256S("0x0f5353f137b5e3f0e45d5643843ba452ac84bb6470ba608eae71994f0be87412");
        consensus.BIP65Height = 1800000;
        consensus.BIP66Height = 1800000;
        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 1.4 * 24 * 60 * 60; 
        consensus.nPowTargetSpacing = 1.0 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 26; // 25% for testchains
        consensus.nMinerConfirmationWindow = 50; // nPowTargetTimespan / nPowTargetSpacing

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1522540800; // Apr 1st, 2018 (UTC)
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1554076800; // Apr 1st, 2019 (UTC)

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1522540800; // Apr 1st, 2018 (UTC)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1554076800; // Apr 1st, 2019 (UTC)

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000000100010");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x96bd214d68bcbfe9c786c4da26cf71fb6bbb6f24032065bdf2f4cd2b003d9c72"); //0

        pchMessageStart[0] = 0x69;
        pchMessageStart[1] = 0x6a;
        pchMessageStart[2] = 0x75;
        pchMessageStart[3] = 0x66;
        nDefaultPort = 13777;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1402725600, 3578955, 0x1e0ffff0, 1, 1 * COIN); //(nTime, nNonce, nBits, nVersion, genesisReward)
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x96bd214d68bcbfe9c786c4da26cf71fb6bbb6f24032065bdf2f4cd2b003d9c72"));
        assert(genesis.hashMerkleRoot == uint256S("0xf951a273c3055d1bb36b4291e7f9edd491c2d435bd5737318ef8a643cab84b61"));

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        //vSeeds.emplace_back("testseed.fujicoin.org", false);

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,74);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,202);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;


        checkpointData = (CCheckpointData) {
            {
                {0, uint256S("0x96bd214d68bcbfe9c786c4da26cf71fb6bbb6f24032065bdf2f4cd2b003d9c72")},
            }
        };

        chainTxData = ChainTxData{
            // Data as of block 00000000000001c200b9790dc637d3bb141fe77d155b966ed775b17e109f7c6c (height 1156179)
            0,
            0,
            0
        };

    }
};

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 150;
        consensus.BIP34Height = 1800000;
        consensus.BIP34Hash = uint256S("0x0f5353f137b5e3f0e45d5643843ba452ac84bb6470ba608eae71994f0be87412");
        consensus.BIP65Height = 1800000;
        consensus.BIP66Height = 1800000;
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 14 * 24 * 60 * 60; // two weeks
        consensus.nPowTargetSpacing = 1.0 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 999999999999ULL;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0x69;
        pchMessageStart[1] = 0x6a;
        pchMessageStart[2] = 0x75;
        pchMessageStart[3] = 0x66;
        nDefaultPort = 16777;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1402725600, 3578955, 0x1e0ffff0, 1, 1 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x96bd214d68bcbfe9c786c4da26cf71fb6bbb6f24032065bdf2f4cd2b003d9c72"));
        assert(genesis.hashMerkleRoot == uint256S("0xf951a273c3055d1bb36b4291e7f9edd491c2d435bd5737318ef8a643cab84b61"));

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;

        checkpointData = (CCheckpointData) {
            {
                {0, uint256S("0x96bd214d68bcbfe9c786c4da26cf71fb6bbb6f24032065bdf2f4cd2b003d9c72")},
            }
        };

        chainTxData = ChainTxData{
            0,
            0,
            0
        };

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};
    }
};

static std::unique_ptr<CChainParams> globalChainParams;

const CChainParams &Params() {
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr<CChainParams> CreateChainParams(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return std::unique_ptr<CChainParams>(new CMainParams());
    else if (chain == CBaseChainParams::TESTNET)
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    else if (chain == CBaseChainParams::REGTEST)
        return std::unique_ptr<CChainParams>(new CRegTestParams());
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    globalChainParams = CreateChainParams(network);
}

void UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    globalChainParams->UpdateVersionBitsParameters(d, nStartTime, nTimeout);
}
