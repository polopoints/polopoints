include Makefile.include

AM_CPPFLAGS += -I$(builddir)

noinst_LIBRARIES = \
  libpolopoints_server.a \
  libpolopoints_common.a \
  libpolopoints_cli.a
if ENABLE_WALLET
noinst_LIBRARIES += libpolopoints_wallet.a
endif

bin_PROGRAMS =

if BUILD_BITCOIND
  bin_PROGRAMS += polopointsd
endif


SUBDIRS = . $(BUILD_QT) $(BUILD_P_TEST) $(BUILD_TEST)
#DIST_SUBDIRS = . qt test
DIST_SUBDIRS = . test ptest
.PHONY: FORCE
# bitcoin core #
POLOPOINTS_CORE_H = \
  addrman.h \
  alert.h \
  allocators.h \
  base58.h bignum.h \
  bloom.h \
  chainparams.h \
  checkpoints.h \
  checkqueue.h \
  clientversion.h \
  compat\compat.h \
  core.h \
  database.h \
  crypter.h \
  hash.h \
  init.h \
  key.h \
  keystore.h \
  leveldbwrapper.h \
  limitedmap.h \
  main.h \
  miner.h \
  mruset.h \
  netbase.h \
  net.h \
  noui.h \
  protocol.h \
  random.h   \
  rpc/rpcclient.h \
  rpc/rpcprotocol.h \
  rpc/rpcserver.h \
  support/cleanse.h \
  serialize.h \
  sync.h \
  threadsafety.h \
  tinyformat.h \
  txdb.h \
  txmempool.h \
  ui_interface.h \
  uint256.h \
  util.h \
  version.h \
  wallet/wallet.h \
  wallet/db.h  \
  arith_uint256.h 

JSON_H = \
  json/json_spirit.h \
  json/json_spirit_error_position.h \
  json/json_spirit_reader.h \
  json/json_spirit_reader_template.h \
  json/json_spirit_stream_reader.h \
  json/json_spirit_utils.h \
  json/json_spirit_value.h \
  json/json_spirit_writer.h \
  json/json_spirit_writer_template.h
  
# VmScript #
		
	
VM_H = \
	vm/vm8051.h \
	vm/vmrunevn.h \
	vm/script.h \
	vm/testmcu.h \
	vm/appaccount.h

	

VM_CPP = \
	vm/vm8051.cpp \
	vm/vmrunevn.cpp \
	vm/script.cpp \
	vm/testmcu.cpp \
	vm/appaccount.cpp

	
	
  

obj/build.h: FORCE
	@$(MKDIR_P) $(abs_top_builddir)/src/obj
	@$(top_srcdir)/share/genbuild.sh $(abs_top_builddir)/src/obj/build.h \
	  $(abs_top_srcdir)
version.o: obj/build.h

libpolopoints_server_a_SOURCES = \
  tx.cpp \
  addrman.cpp \
  alert.cpp \
  bloom.cpp \
  checkpoints.cpp \
  database.cpp \
  init.cpp \
  leveldbwrapper.cpp \
  main.cpp \
  miner.cpp \
  net.cpp \
  noui.cpp \
  rpc/rpcblockchain.cpp \
  rpc/rpcmining.cpp \
  rpc/rpcmisc.cpp \
  rpc/rpcnet.cpp \
  rpc/rpcrawtransaction.cpp \
  rpc/rpcserver.cpp \
  txdb.cpp \
  txmempool.cpp \
  cuiserver.cpp	\
  $(VM_CPP) \
  $(VM_H) \
  $(JSON_H) \
  $(POLOPOINTS_CORE_H)

libpolopoints_wallet_a_SOURCES = \
  wallet/db.cpp  \
  crypter.cpp \
  rpc/rpcdump.cpp \
  rpc/rpcwallet.cpp \
  keystore.cpp \ 
  wallet/wallet.cpp \
  wallet/walletdb.cpp \
  rpc/rpctx.cpp \
  $(POLOPOINTS_CORE_H)

libpolopoints_common_a_SOURCES = \
  base58.cpp \
  allocators.cpp \
  arith_uint256.cpp \
  chainparams.cpp \
  core.cpp \
  hash.cpp \
  key.cpp \
  netbase.cpp \
  protocol.cpp \
  random.cpp  \
  rpc/rpcprotocol.cpp \
  support/cleanse.cpp \
  sync.cpp \
  syncdata.cpp \
  syncdatadb.cpp \
  util.cpp \
  uint256.cpp \
  version.cpp \
  json/json_spirit_reader.cpp \
  json/json_spirit_value.cpp \
  json/json_spirit_writer.cpp \
  $(POLOPOINTS_CORE_H)

if GLIBC_BACK_COMPAT
libpolopoints_common_a_SOURCES += compat/glibc_compat.cpp
libpolopoints_common_a_SOURCES += compat/glibcxx_compat.cpp
endif

libpolopoints_cli_a_SOURCES = \
  rpc/rpcclient.cpp \
  $(POLOPOINTS_CORE_H)

nodist_libpolopoints_common_a_SOURCES = $(top_srcdir)/src/obj/build.h
#

# polopoints binary #
polopointsd_LDADD = \
  libpolopoints_server.a \
  libpolopoints_wallet.a \
  libpolopoints_cli.a \
  libpolopoints_common.a \
  $(LIBLEVELDB) \
  $(LIBMEMENV)
#if ENABLE_WALLET
#polopoints_LDADD += libpolopoints_wallet.a
#endif
polopointsd_SOURCES = polopointsd.cpp
#

if TARGET_WINDOWS
polopointsd_SOURCES += polopointsd-res.rc
endif

AM_CPPFLAGS += $(BDB_CPPFLAGS)
polopointsd_LDADD += $(BOOST_LIBS) $(BDB_LIBS)



# NOTE: This dependency is not strictly necessary, but without it make may try to build both in parallel, which breaks the LevelDB build system in a race
leveldb/libleveldb.a: leveldb/libmemenv.a

leveldb/%.a:
	@echo "Building LevelDB ..." && $(MAKE) -C $(@D) $(@F) CXX="$(CXX)" \
	  CC="$(CC)" PLATFORM=$(TARGET_OS) AR="$(AR)" $(LEVELDB_TARGET_FLAGS) \
	  OPT="$(CXXFLAGS) $(CPPFLAGS)"

qt/bitcoinstrings.cpp: $(libpolopoints_server_a_SOURCES) $(libpolopoints_common_a_SOURCES) $(libpolopoints_cli_a_SOURCES)
	@test -n $(XGETTEXT) || echo "xgettext is required for updating translations"
	@cd $(top_srcdir); XGETTEXT=$(XGETTEXT) share/qt/extract_strings_qt.py

#
#CLEANFILES = leveldb/libleveldb.a leveldb/libmemenv.a *.gcda *.gcno
CLEANFILES =  *.gcda *.gcno
#

DISTCLEANFILES = obj/build.h

EXTRA_DIST = leveldb Makefile.include

clean-local:
	-$(MAKE) -C leveldb clean
	rm -f leveldb/*/*.gcno leveldb/helpers/memenv/*.gcno
