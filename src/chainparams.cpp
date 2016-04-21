// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2014-2015 The Dacrs developers
// Copyright (c) 2016 The Polopoints developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "assert.h"
#include "core.h"
#include "protocol.h"
#include "util.h"
#include "key.h"
#include "tx.h"
#include "main.h"

#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string/case_conv.hpp> // for to_lower()
#include <boost/algorithm/string/predicate.hpp> // for startswith() and endswith()
#include <boost/filesystem.hpp>
using namespace boost::assign;
using namespace std;

map<string, string> CBaseParams::m_mapArgs;
map<string, vector<string> > CBaseParams::m_mapMultiArgs;



vector<string> intPubKey_mainNet = {
		"0310b67015f3da33a250c8b13d4d62929a8f461d82554602dcafea8646eededb83",
		"0323d31c961e16c5ef8a4ffecf0aa5de7c08a7698d4dc444153f5be9beb2059e41"
};

vector<string> initPubKey_testNet = { //
		"02e6505027f041a5fdb7525278af9b0dc923937dd3a1ccef54a46cf0c8de3f13b8",
		"0316b1e536ea6a4a55574870788c84c35480c0490cb55740fdfcff1c5effccafea"
};

vector<string> initPubkey_regTest = {
		"02560c6add9c1bb177a766555660904e6052e57eb9a23472d92403e0e8180e102b",
		"02f463d5423d3798ca7e4c9888aad7fc18b5f40e8c6bd26e2c620bf9f1479cae98",
		"02a6b1f1f62d5f5078f0f5585b30c5c9e565ed4f052824739930c0fc2c0e09e212",
		"0341d09e7c50a1406d8d63200fbb51babd89d133a361060f80c36be9eab4467c14",
		"02ce125943ac355374cf019fe5c27686df562fdde291cd2dfcd92ab0e473235e22",
		"02986782dd87dd857176e1092d30e8460684dc1fd9eb11fd23385488d54bdb8426",
		"0275200bf4e88724af5111c7c956d174270a76dbe94827dbf4584afe3c357dab3e",
		"02a4087370f17771c25cffae7fdcd72a95f5d6a65e699ab50f4e90e175f86fa7a7",
		"02c87a55039723554b01405940c99853bdc6bdfc46ced225f9f91a61c541db38f6",
		"03dea07cf50a82ee03cc3ed71b24a34685e5662756b07d671f70a0161a2df5a600",
		"038bb7205aa82121a895668204f093f2f0ddec2a7027977af52832d0e34e2762ff",

		"03b94cea2cea39f03254bc679ce368b293cf70245e1b4a3b0d1818a8136ab319ef",
		"02ae43a2ef88414b1b1ab9a35493909930819512ef1f136bfbfc112d72ac404bc5",
		"03bc72551eaff2090f892eae8a34b0c3857e1f375a94a6d6d01c547068fca2ae89",
		"0207b9b3005236752cf287b7bfba82b0173f82361918fa0d61c3f76df174b21f17",
		"0393848f4e1b6861cb569e76279cca0e1df121d3ae8ee16bc824209442d1485869",
		"02af52880dace8ed9538bab40a7ab9fdfa5e87070575c70495f2c56ef9b732a536",
		"032797a1e479c21d5296687844cf5e0b23e3bccc7fc698693afbd3f17cd88607a1",
		"02104ec38c5305cbca08596113b3bb90bfd2bf907d42d823c463bbbc59e479984a",
		"036fd8953b10c4fbd8380dede638b6fd1fd6b78d32b0f439b931968608b32093d6",
		"025d4c4909576371d2d56bba46835d5f41455007a99ef89719b22e295f1e13141b"
};
unsigned int pnSeed[] = //
		{0x8c841a78, 0x0a513778, 0x7fd3c865, 0x5d092a79, 0x55cc602a, 0x9a944c78};

class CMainParams: public CBaseParams {
public:
	CMainParams() {

// The message start string is designed to be unlikely to occur in normal data.
// The characters are rarely used upper ASCII, not valid as UTF-8, and produce
// a large 4-byte int at any alignment.
		pchMessageStart[0] = 0xff;
		pchMessageStart[1] = 0xfe;
		pchMessageStart[2] = 0x1C;
		pchMessageStart[3] = 0x50;
		vAlertPubKey =	ParseHex("03146e6f0d502bbd112bb5d8870834f8acb329a1a346968920d96399d10f658200");
		nDefaultPort = 6668;
		nRPCPort = 6669;
		strDataDir = "main";
		bnProofOfStakeLimit =~arith_uint256(0) >> 10;        //00 3f ff ff
		nSubsidyHalvingInterval = 2590000;

		assert(CreateGenesisRewardTx(genesis.vptx, intPubKey_mainNet));
		genesis.SetHashPrevBlock(uint256());
		genesis.SetHashMerkleRoot(genesis.BuildMerkleTree());
		genesis.SetHashPos(uint256());
		genesis.SetVersion(1);
		genesis.SetTime(1458906662);
		genesis.SetBits(0x1f3fffff);        //00 3f ff
		genesis.SetNonce(888);
		genesis.SetFuelRate(INIT_FUEL_RATES);
		genesis.SetHeight(0);
		genesis.ClearSignature();
		hashGenesisBlock = genesis.GetHash();
		publicKey = "03146e6f0d502bbd112bb5d8870834f8acb329a1a346968920d96399d10f658200";
//		{
//			cout << "main hashGenesisBlock:\r\n" << hashGenesisBlock.ToString() << endl;
//			cout << "main hashMerkleRoot:\r\n" << genesis.GetHashMerkleRoot().ToString() << endl;
//		}
		assert(hashGenesisBlock == uint256S("0x4f822175a56fcc9291c3bf1fc26b5c0f9e16fc445a51577083a82d3cb1de5c19"));
		assert(genesis.GetHashMerkleRoot() == uint256S("0x0e706fffa5348d5e6384a6f08bd22641fdb665e3fe103538bfc285a1a2d64c34"));

//      vSeeds.push_back(CDNSSeedData("soypay.org.cn", "seed_cn_0.dspay.org"));
//      vSeeds.push_back(CDNSSeedData("soypay.org.us", "seed_us_0.dspay.org"));

        base58Prefixes[PUBKEY_ADDRESS] = {0x29};
		base58Prefixes[SCRIPT_ADDRESS] = {8};
		base58Prefixes[SECRET_KEY] = {138};
		base58Prefixes[EXT_PUBLIC_KEY] = {0x05,0x86,0xC3,0x3D};
		base58Prefixes[EXT_SECRET_KEY] = {0x05,0x85,0xA4,0x4F};

		// Convert the pnSeeds array into usable address objects.
		for (unsigned int i = 0; i < ARRAYLEN(pnSeed); i++) {
			// It'll only connect to one or two seed nodes because once it connects,
			// it'll get a pile of addresses with newer timestamps.
			// Seed nodes are given a random 'last seen time' of between one and two
			// weeks ago.
			const int64_t nOneWeek = 7 * 24 * 60 * 60;
			struct in_addr ip;
			memcpy(&ip, &pnSeed[i], sizeof(ip));
			CAddress addr(CService(ip, GetDefaultPort()));
			addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
			vFixedSeeds.push_back(addr);
		}
	}

	virtual const CBlock& GenesisBlock() const {
		return genesis;
	}
	virtual Network NetworkID() const {
		return CBaseParams::MAIN;
	}
	virtual bool InitalConfig() {
		return CBaseParams::InitalConfig();
	}
	virtual int GetBlockMaxNonce() const
	{
		return 1000;
	}
	virtual const vector<CAddress>& FixedSeeds() const {
		return vFixedSeeds;
	}
	virtual bool IsInFixedSeeds(CAddress &addr) {
		vector<CAddress>::iterator iterAddr = find(vFixedSeeds.begin(), vFixedSeeds.end(), addr);
		return iterAddr != vFixedSeeds.end();
	}

protected:
	CBlock genesis;
	vector<CAddress> vFixedSeeds;
};
//static CMainParams mainParams;

//
// Testnet (v3)
//
class CTestNetParams: public CMainParams {
public:
	CTestNetParams() {
		// The message start string is designed to be unlikely to occur in normal data.
		// The characters are rarely used upper ASCII, not valid as UTF-8, and produce
		// a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xfe;
        pchMessageStart[1] = 0x1d;
        pchMessageStart[2] = 0xac;
        pchMessageStart[3] = 0x20;
		vAlertPubKey =	ParseHex("0393d16cb247643e713161e8ebeb5d61ca80f0b60db98bde0675cdaf23abb85e0a");
		nDefaultPort = 16668;
		nRPCPort = 16669;
		strDataDir = "testnet";
		publicKey = "0393d16cb247643e713161e8ebeb5d61ca80f0b60db98bde0675cdaf23abb85e0a";
		// Modify the testnet genesis block so the timestamp is valid for a later start.
		genesis.SetTime(1457904215);
		genesis.SetNonce(888);
		genesis.vptx.clear();
		assert(CreateGenesisRewardTx(genesis.vptx, initPubKey_testNet));
		genesis.SetHashMerkleRoot(genesis.BuildMerkleTree());
		hashGenesisBlock = genesis.GetHash();
		for(auto & item : vFixedSeeds)
			item.SetPort(GetDefaultPort());

//		{
//			cout << "testnet hashGenesisBlock:\r\n" << hashGenesisBlock.ToString() << endl;
//		}
		assert(hashGenesisBlock == uint256S("0x6957e70aa4b2fb2d1c64b74a933b52f8730eb2628d9a0669c8037482e3544058"));
//		vSeeds.clear();
//		vSeeds.push_back(CDNSSeedData("bluematt.me", "testnet-seed.bluematt.me"));

		base58Prefixes[PUBKEY_ADDRESS] = {100};
		base58Prefixes[SCRIPT_ADDRESS] = {18};
		base58Prefixes[SECRET_KEY]     = {108};
		base58Prefixes[EXT_PUBLIC_KEY] = {0x05,0x85,0x88,0xAF};
		base58Prefixes[EXT_SECRET_KEY] = {0x05,0x85,0x82,0xCA};
	}
	virtual Network NetworkID() const {return CBaseParams::TESTNET;}
	virtual bool InitalConfig()
	{
		CMainParams::InitalConfig();
		fServer = true;
		return true;
	}
	virtual int GetBlockMaxNonce() const
	{
		return 1000;
	}
};
//static CTestNetParams testNetParams;

//
// Regression test
//
class CRegTestParams: public CTestNetParams {
public:
	CRegTestParams() {
		pchMessageStart[0] = 0xf1;
		pchMessageStart[1] = 0x1c;
		pchMessageStart[2] = 0x3b;
		pchMessageStart[3] = 0xc1;
		nSubsidyHalvingInterval = 500;
		bnProofOfStakeLimit = ~arith_uint256(0) >> 6;     //target:00000011 11111111 11111111
		genesis.SetTime(1457904215);
		genesis.SetBits(0x2003ffff);
		genesis.SetNonce(888);
		genesis.vptx.clear();
		assert(CreateGenesisRewardTx(genesis.vptx, initPubkey_regTest));
		genesis.SetHashMerkleRoot(genesis.BuildMerkleTree());
		hashGenesisBlock = genesis.GetHash();
		nDefaultPort = 16666;
		nTargetSpacing = 20;
		nTargetTimespan = 30 * 20;
		strDataDir = "regtest";
//		{
//			CBigNum bnTarget;
//			bnTarget.SetCompact(genesis.nBits);
//			cout << "regtest bnTarget:" << bnTarget.getuint256().GetHex() << endl;
//			cout << "regtest hashGenesisBlock:\r\n" << hashGenesisBlock.ToString() << endl;
//			cout << "regtest hashMerkleRoot:\r\n" << genesis.hashMerkleRoot.ToString() << endl;
//		}
		assert(hashGenesisBlock == uint256S("0x7a54dd0298bbdc002f0f1664a6629e7b8f4a36c3c2b1b9be2755199a2c379452"));

		vFixedSeeds.clear();
		vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
	}

	virtual bool RequireRPCPassword() const {
		return false;
	}
	virtual Network NetworkID() const {
		return CBaseParams::REGTEST;
	}
	virtual bool InitalConfig() {
		CTestNetParams::InitalConfig();
		fServer = true;
		return true;
	}
};
//static CRegTestParams regTestParams;

//static CBaseParams *pCurrentParams = &mainParams;

//CBaseParams &Params() {
//	return *pCurrentParams;
//}

//void SelectParams(CBaseParams::Network network) {
//	switch (network) {
//	case CBaseParams::MAIN:
//		pCurrentParams = &mainParams;
//		break;
//	case CBaseParams::TESTNET:
//		pCurrentParams = &testNetParams;
//		break;
//	case CBaseParams::REGTEST:
//		pCurrentParams = &regTestParams;
//		break;
//	default:
//		assert(false && "Unimplemented network");
//		return;
//	}
//}

//bool SelectParamsFromCommandLine() {
//	bool fRegTest = GetBoolArg("-regtest", false);
//	bool fTestNet = GetBoolArg("-testnet", false);
//
//	if (fTestNet && fRegTest) {
//		return false;
//	}
//
//	if (fRegTest) {
//		SelectParams(CBaseParams::REGTEST);
//	} else if (fTestNet) {
//		SelectParams(CBaseParams::TESTNET);
//	} else {
//		SelectParams(CBaseParams::MAIN);
//	}
//	return true;
//}

/********************************************************************************/
const vector<string> &CBaseParams::GetMultiArgs(const string& strArg) {
	return m_mapMultiArgs[strArg];
}
int CBaseParams::GetArgsSize() {
	return m_mapArgs.size();
}
int CBaseParams::GetMultiArgsSize() {
	return m_mapMultiArgs.size();
}

string CBaseParams::GetArg(const string& strArg, const string& strDefault) {
	if (m_mapArgs.count(strArg))
		return m_mapArgs[strArg];
	return strDefault;
}

int64_t CBaseParams::GetArg(const string& strArg, int64_t nDefault) {
	if (m_mapArgs.count(strArg))
		return atoi64(m_mapArgs[strArg]);
	return nDefault;
}

bool CBaseParams::GetBoolArg(const string& strArg, bool fDefault) {
	if (m_mapArgs.count(strArg)) {
		if (m_mapArgs[strArg].empty())
			return true;
		return (atoi(m_mapArgs[strArg]) != 0);
	}
	return fDefault;
}

bool CBaseParams::SoftSetArg(const string& strArg, const string& strValue) {
	if (m_mapArgs.count(strArg))
		return false;
	m_mapArgs[strArg] = strValue;
	return true;
}

bool CBaseParams::SoftSetArgCover(const string& strArg, const string& strValue) {
	m_mapArgs[strArg] = strValue;
	return true;
}

void CBaseParams::EraseArg(const string& strArgKey) {
	m_mapArgs.erase(strArgKey);
}

bool CBaseParams::SoftSetBoolArg(const string& strArg, bool fValue) {
	if (fValue)
		return SoftSetArg(strArg, string("1"));
	else
		return SoftSetArg(strArg, string("0"));
}

bool CBaseParams::IsArgCount(const string& strArg) {
	if (m_mapArgs.count(strArg)) {
		return true;
	}
	return false;
}

CBaseParams &SysCfg() {
	static shared_ptr<CBaseParams> pParams;

	if (pParams.get() == NULL) {
		bool fRegTest = CBaseParams::GetBoolArg("-regtest", false);
		bool fTestNet = CBaseParams::GetBoolArg("-testnet", false);
		if (fTestNet && fRegTest) {
			fprintf(stderr, "Error: Invalid combination of -regtest and -testnet.\n");
//			assert(0);
		}

		if (fRegTest) {
			//LogPrint("spark", "In Reg Test Net\n");
			pParams = make_shared<CRegTestParams>();
		} else if (fTestNet) {
			//LogPrint("spark", "In Test Net\n");
			pParams = make_shared<CTestNetParams>();
		} else {
			//LogPrint("spark", "In Main Net\n");
			pParams = make_shared<CMainParams>();
		}

	}
	assert(pParams != NULL);
	return *pParams.get();
}

//write for test code
const CBaseParams &SysParamsMain() {
	static std::shared_ptr<CBaseParams> pParams;
	pParams = make_shared<CMainParams>();
	assert(pParams != NULL);
	return *pParams.get();
}

//write for test code
const CBaseParams &SysParamsTest() {
	static std::shared_ptr<CBaseParams> pParams;
	pParams = make_shared<CTestNetParams>();
	assert(pParams != NULL);
	return *pParams.get();
}

//write for test code
const CBaseParams &SysParamsReg() {
	static std::shared_ptr<CBaseParams> pParams;
	pParams = make_shared<CRegTestParams>();
	assert(pParams != NULL);
	return *pParams.get();
}

static void InterpretNegativeSetting(string name, map<string, string>& mapSettingsRet) {
	// interpret -nofoo as -foo=0 (and -nofoo=0 as -foo=1) as long as -foo not set
	if (name.find("-no") == 0) {
		string positive("-");
		positive.append(name.begin() + 3, name.end());
		if (mapSettingsRet.count(positive) == 0) {
			bool value = !SysCfg().GetBoolArg(name, false);
			mapSettingsRet[positive] = (value ? "1" : "0");
		}
	}
}

void CBaseParams::ParseParameters(int argc, const char* const argv[]) {
	m_mapArgs.clear();
	m_mapMultiArgs.clear();
	for (int i = 1; i < argc; i++) {
		string str(argv[i]);
		string strValue;
		size_t is_index = str.find('=');
		if (is_index != string::npos) {
			strValue = str.substr(is_index + 1);
			str = str.substr(0, is_index);
		}
#ifdef WIN32
		boost::to_lower(str);
		if (boost::algorithm::starts_with(str, "/"))
			str = "-" + str.substr(1);
#endif
		if (str[0] != '-')
			break;

		m_mapArgs[str] = strValue;
		m_mapMultiArgs[str].push_back(strValue);
	}

	// New 0.6 features:
//	BOOST_FOREACH(const PAIRTYPE(string,string)& entry, m_mapArgs) {
	for (auto& entry : m_mapArgs) {
		string name = entry.first;

		//  interpret --foo as -foo (as long as both are not set)
		if (name.find("--") == 0) {
			string singleDash(name.begin() + 1, name.end());
			if (m_mapArgs.count(singleDash) == 0)
				m_mapArgs[singleDash] = entry.second;
			name = singleDash;
		}

		// interpret -nofoo as -foo=0 (and -nofoo=0 as -foo=1) as long as -foo not set
		InterpretNegativeSetting(name, m_mapArgs);
	}
#if 0
	for(const auto& tmp:m_mapArgs) {
		printf("key:%s - value:%s\n", tmp.first.c_str(), tmp.second.c_str());
	}
#endif
}

bool CBaseParams::CreateGenesisRewardTx(vector<std::shared_ptr<CBaseTransaction> > &vRewardTx, const vector<string> &vInitPubKey) {
	int length = vInitPubKey.size();
	for (int i = 0; i < length; ++i) {
		int64_t money(0);
		if (i > 0) {
			if (length > 15) {   //regtest net
				money = 1000000000 * COIN;
			} else {
				money = 10000000000 * COIN;
			}
		}
		shared_ptr<CRewardTransaction> pRewardTx = make_shared<CRewardTransaction>(ParseHex(vInitPubKey[i].c_str()),
				money, 0);
		pRewardTx->nVersion = nTxVersion1;
		if (pRewardTx.get())
			vRewardTx.push_back(pRewardTx);
		else
			return false;
	}
	return true;

};

bool CBaseParams::IntialParams(int argc, const char* const argv[]) {
	ParseParameters(argc, argv);
	if (!boost::filesystem::is_directory(GetDataDir(false))) {
		fprintf(stderr, "Error: Specified data directory \"%s\" does not exist.\n", CBaseParams::m_mapArgs["-datadir"].c_str());
		return false;
	}
	try {
		ReadConfigFile(CBaseParams::m_mapArgs, CBaseParams::m_mapMultiArgs);
	} catch (exception &e) {
		fprintf(stderr, "Error reading configuration file: %s\n", e.what());
		return false;
	}
	return true;
}

int64_t CBaseParams::GetTxFee() const{
     return paytxfee;
}
int64_t CBaseParams::SetDeflautTxFee(int64_t fee)const{
	paytxfee = fee;

	return fee;
}

CBaseParams::CBaseParams() {
	fImporting = false;
	fReindex = false;
	fBenchmark = false;
	fTxIndex = false;
	nIntervalPos = 1;
	nLogmaxsize = 100 * 1024 * 1024;//100M
	nTxCacheHeight = 500;
	nTimeBestReceived = 0;
	nScriptCheckThreads = 0;
	nViewCacheSize = 2000000;
	nTargetSpacing = 60;
	nTargetTimespan = 30 * 60;
	nSubsidyHalvingInterval = 0;
	paytxfee = 10000;
	nDefaultPort = 0;
	fPrintToConsole= 0;
	fPrintToToFile = 0;
	fLogTimestamps = 0;
	fLogPrintFileLine = 0;
	fDebug = 0;
	fDebugAll= 0 ;
	fServer = 0 ;
	fServer = 0;
	nRPCPort = 0;
	bOutPut = false;


}
/********************************************************************************/

