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
		"03126e0a0439591f534b740c537e834dbe9165791e91a4c3356819afe68927a5c4",
		"0213e48fe44a4defbb787925b446ab009f97d0df40d265fe6cdd550f5effb00d11"
};

vector<string> initPubKey_testNet = { //
		"03cb28d8ef31adcec6d46cdc43ba262d40e060e4e56a4e38454a620a3d7535ff45",
		"031cf07d62eacaec073134cc8915462b623019594582d8e12d4a72aacab6ed553f"
};

vector<string> initPubkey_regTest = {
		"02a379d2952322467cadec13532f8c84e245308c64e98ae7781894dfea4a23565b",
		"03f2c8334c4b72134dee31dfec101f4382745f7b578580586f33672c8c7b5ff401",
		"022015008867f775d6c23ddea40c5d8edb3a026bb95bc5a1044899f7e9a056aa55",
		"02c0d8d634c95d5018e4078b47c1280b2c7adfc1ea81a2803b4ce97aa08e7af6d4",
		"02d99cf12c8b9c6c21bec7be6242c2df0584d9c335387362ec25cf5f70c7220713",
		"02b30c8dff484fa4135690eb023296878d63adde3b884138022b8bd2b823b668ca",
		"02347915e86c308c9b22d95b927738ef9bfc5b8f95a1ce18219d408b35ea1c01ad",
		"0313de4fc40aba957dd6906677702d0bb9669903e8e30ce822e6ac09cdc04ef5e2",
		"02b9a0c6b64e0ee184c8cc71247c129eb711889058b18d5413721e350ab4d9798c",
		"02c268a9e093faf206fdb8fccb0166ed8e2a3c517dda238387972fa9c2b4e2694a",
		"0384f1210579ee80e39335e28c61f115d1e621794cc40514818926421dd8b1b7c7",

		"031a7bcbb24ca3239e46aeb09286d58bd5d4b9d7ed9b9d34436635752c448d8e71",
		"031bfbdb36afda057833887ef70c8ba284f4c433d904d1f2cbad0beeb2e3406842",
		"034768ef1eb0947df920fba2fcb26239a936764b4bfa8af8d2f867f83b304a6fde",
		"037bb4f3cb86e771824dc495051420012ddf1a175945bd236e0f500ac0c29fb559",
		"02679ebe70488b5f99cf7b60f545fcdb9bf93a142f8bc9fa3536de62840d5fd44b",
		"02d4d2ea0a116f8561ff5b29097d6a477a07a931ea268a34b86fd842a5094903fd",
		"02721aa4c535f8d3c99b8800add0c57b0541a19b7c82df94926b612ceac4269566",
		"03437f94270206dffa7c419b3ff7be8b0aea315b2d42d5e3c00fdf494f0f994004",
		"02ae1bd1280496decd58d629b0eb6691b98e99ffb052ed83f38f06cce3c6f5193a",
		"0397c19fbc5e731566e10b6de25c153b5b1d2cb3b1c9bdf19e63928244fe7ef784"
};
unsigned int pnSeed[] = //
		{0x57b64c78, 0x04524a70, 0x7a3c818b, 0xa2fe387b, 0xbf11c48b, 0xb6481a78};

class CMainParams: public CBaseParams {
public:
	CMainParams() {

// The message start string is designed to be unlikely to occur in normal data.
// The characters are rarely used upper ASCII, not valid as UTF-8, and produce
// a large 4-byte int at any alignment.
		pchMessageStart[0] = 0xff;
		pchMessageStart[1] = 0xfd;
		pchMessageStart[2] = 0x3a;
		pchMessageStart[3] = 0x81;
		vAlertPubKey =	ParseHex("0202c8293d5f2a17809849bee752bdf3fab5d271187bcaa60dbcfd0611220ddcb4");
		nDefaultPort = 9996;
		nRPCPort = 9969;
		strDataDir = "main";
		bnProofOfStakeLimit =~arith_uint256(0) >> 10;        //00 3f ff ff
		nSubsidyHalvingInterval = 2590000;

		assert(CreateGenesisRewardTx(genesis.vptx, intPubKey_mainNet));
		genesis.SetHashPrevBlock(uint256());
		genesis.SetHashMerkleRoot(genesis.BuildMerkleTree());
		genesis.SetHashPos(uint256());
		genesis.SetVersion(1);
		genesis.SetTime(1460422800);
		genesis.SetBits(0x1f3fffff);        //00 3f ff
		genesis.SetNonce(108);
		genesis.SetFuelRate(INIT_FUEL_RATES);
		genesis.SetHeight(0);
		genesis.ClearSignature();
		hashGenesisBlock = genesis.GetHash();
		publicKey = "0202c8293d5f2a17809849bee752bdf3fab5d271187bcaa60dbcfd0611220ddcb4";
//		{
//			cout << "main hashGenesisBlock:\r\n" << hashGenesisBlock.ToString() << endl;
//			cout << "main hashMerkleRoot:\r\n" << genesis.GetHashMerkleRoot().ToString() << endl;
//		}
		assert(hashGenesisBlock == uint256S("0x5a6dd667b2e66ebd1f60468c110f10d35fad8bfbe8924308e4c5a9cf09724f94"));
		assert(genesis.GetHashMerkleRoot() == uint256S("0x04cfb85732065544d2a6ce7b805bc5f51830618ef9e49d75c2f79ab47d9407e9"));

//      vSeeds.push_back(CDNSSeedData("soypay.org.cn", "seed_cn_0.dspay.org"));
//      vSeeds.push_back(CDNSSeedData("soypay.org.us", "seed_us_0.dspay.org"));

        base58Prefixes[PUBKEY_ADDRESS] = {56};
		base58Prefixes[SCRIPT_ADDRESS] = {33};
		base58Prefixes[SECRET_KEY] = {130};
		base58Prefixes[EXT_PUBLIC_KEY] = {0x06,0x96,0xA1,0x5C};
		base58Prefixes[EXT_SECRET_KEY] = {0x06,0x96,0xC2,0x3D};

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

class CTestNetParams: public CMainParams {
public:
	CTestNetParams() {
		// The message start string is designed to be unlikely to occur in normal data.
		// The characters are rarely used upper ASCII, not valid as UTF-8, and produce
		// a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xff;
        pchMessageStart[1] = 0xc1;
        pchMessageStart[2] = 0x2d;
        pchMessageStart[3] = 0x30;
		vAlertPubKey =	ParseHex("038f8d1f93d1d779f1cdd2c21a4bec5186b3e0a34fdc8ef7b8ed97c7c119936387");
		nDefaultPort = 13366;
		nRPCPort = 13399;
		strDataDir = "testnet";
		publicKey = "038f8d1f93d1d779f1cdd2c21a4bec5186b3e0a34fdc8ef7b8ed97c7c119936387";
		// Modify the testnet genesis block so the timestamp is valid for a later start.
		genesis.SetTime(1459472400);
		genesis.SetNonce(99);
		genesis.vptx.clear();
		assert(CreateGenesisRewardTx(genesis.vptx, initPubKey_testNet));
		genesis.SetHashMerkleRoot(genesis.BuildMerkleTree());
		hashGenesisBlock = genesis.GetHash();
		for(auto & item : vFixedSeeds)
			item.SetPort(GetDefaultPort());

//		{
//			cout << "testnet hashGenesisBlock:\r\n" << hashGenesisBlock.ToString() << endl;
//		}
		assert(hashGenesisBlock == uint256S("0x402d62f75dae509ed613c08534baab94c3cae9cece8c487b81928092fea7c04e"));
//		vSeeds.clear();
//		vSeeds.push_back(CDNSSeedData("bluematt.me", "testnet-seed.bluematt.me"));

		base58Prefixes[PUBKEY_ADDRESS] = {118};
		base58Prefixes[SCRIPT_ADDRESS] = {60};
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
		pchMessageStart[0] = 0xfe;
		pchMessageStart[1] = 0x32;
		pchMessageStart[2] = 0x40;
		pchMessageStart[3] = 0x53;
		nSubsidyHalvingInterval = 500;
		bnProofOfStakeLimit = ~arith_uint256(0) >> 6;     //target:00000011 11111111 11111111
		genesis.SetTime(1459472400);
		genesis.SetBits(0x2003ffff);
		genesis.SetNonce(68);
		genesis.vptx.clear();
		assert(CreateGenesisRewardTx(genesis.vptx, initPubkey_regTest));
		genesis.SetHashMerkleRoot(genesis.BuildMerkleTree());
		hashGenesisBlock = genesis.GetHash();
		nDefaultPort = 13333;
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
		assert(hashGenesisBlock == uint256S("0xd909978a7aefe7e22aac42110bb7e61452d961e9761d51a9e739859d326c2995"));

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

