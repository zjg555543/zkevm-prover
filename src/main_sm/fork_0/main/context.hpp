#ifndef CONTEXT_HPP_fork_0
#define CONTEXT_HPP_fork_0

#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <gmpxx.h>
#include "main_sm/fork_0/main/rom.hpp"
#include "main_sm/fork_0/main/rom_command.hpp"
#include "main_sm/fork_0/pols_generated/commit_pols.hpp"
#include "main_sm/fork_0/main/full_tracer.hpp"
#include "config.hpp"
#include "goldilocks_base_field.hpp"
#include "smt.hpp"
#include "database.hpp"
#include "input.hpp"
#include "ffiasm/fec.hpp"
#include "ffiasm/fnec.hpp"
#include "prover_request.hpp"
#include "hashdb_interface.hpp"

using namespace std;
using json = nlohmann::json;

namespace fork_0
{

class HashValue
{
public:
    vector<uint8_t> data;
    unordered_map< uint64_t, uint64_t > reads;
    mpz_class digest;
    bool digestCalled;
    bool lenCalled;
    HashValue() : digestCalled(false), lenCalled(false) {};
};

class LastSWrite
{
public:
    Goldilocks &fr;
    uint64_t step;
    Goldilocks::Element key[4];
    Goldilocks::Element keyI[4];
    Goldilocks::Element newRoot[4];
    SmtSetResult res;
    void reset (void)
    {
        step = 0;
        key[0] = fr.zero();
        key[1] = fr.zero();
        key[2] = fr.zero();
        key[3] = fr.zero();
        keyI[0] = fr.zero();
        keyI[1] = fr.zero();
        keyI[2] = fr.zero();
        keyI[3] = fr.zero();
        newRoot[0] = fr.zero();
        newRoot[1] = fr.zero();
        newRoot[2] = fr.zero();
        newRoot[3] = fr.zero();
        res.mode = "";
    }
    LastSWrite(Goldilocks &fr) : fr(fr) { reset(); }
};

class Fea
{
public:
    Goldilocks::Element fe0;
    Goldilocks::Element fe1;
    Goldilocks::Element fe2;
    Goldilocks::Element fe3;
    Goldilocks::Element fe4;
    Goldilocks::Element fe5;
    Goldilocks::Element fe6;
    Goldilocks::Element fe7;
};

class OutLog
{
public:
    vector<string> topics;
    vector<string> data;
};

class TouchedStorageSlot
{
public:
    uint32_t addr;
    uint32_t key;
};

class Context
{
public:

    Goldilocks &fr; // Finite field reference
    const Config &config; // Configuration
    RawFec &fec; // Fec reference
    RawFnec &fnec; // Fnec reference
    MainCommitPols &pols; // PIL JSON file polynomials data
    const Rom &rom; // Rom reference
    LastSWrite lastSWrite; // Keep track of the last storage write
    ProverRequest &proverRequest;
    HashDBInterface *pHashDB;
    uint64_t lastStep;

    Context( Goldilocks &fr,
             const Config &config,
             RawFec &fec,
             RawFnec &fnec,
             MainCommitPols &pols,
             const Rom &rom,
             ProverRequest &proverRequest,
             HashDBInterface *pHashDB ) :
        fr(fr),
        config(config),
        fec(fec),
        fnec(fnec),
        pols(pols),
        rom(rom),
        lastSWrite(fr),
        proverRequest(proverRequest),
        pHashDB(pHashDB),
        lastStep(0)
        {}; // Constructor, setting references

    // Evaluations data
    uint64_t * pZKPC; // Zero-knowledge program counter
    uint64_t * pStep; // Iteration, instruction execution loop counter, polynomial evaluation counter
    uint64_t N; // Polynomials degree
#ifdef LOG_FILENAME
    string   fileName; // From ROM JSON file instruction
    uint64_t line; // From ROM JSON file instruction
#endif

    // HashK database, used in hashK, hashKLen and hashKDigest
    unordered_map< uint64_t, HashValue > hashK;

    // HashP database, used in hashP, hashPLen and hashPDigest
    unordered_map< uint64_t, HashValue > hashP;

    // Variables database, used in evalCommand() declareVar/setVar/getVar
    unordered_map< string, mpz_class > vars;
    
    // Memory map, using absolute address as key, and field element array as value
    unordered_map< uint64_t, Fea > mem; // TODO: Use array<Goldilocks::Element,8> instead of Fea, or declare Fea8, Fea4 at a higher level

    // Repository of eval_storeLog() calls
    unordered_map< uint32_t, OutLog> outLogs;

    // A vector of maps of accessed Ethereum address to sets of keys
    // Every position of the vector represents a context
    vector< map<mpz_class, set<mpz_class>> > accessedStorage;
};

} // namespace

#endif