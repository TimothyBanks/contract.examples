#include <eosio/eosio.hpp>
#include <eosio/map.hpp>

CONTRACT kvcontract : public eosio::contract {
   using kv_table = eosio::kv::map<"kvtable"_n, uint64_t, std::string>;
   kv_table m_db;

 public:
   using eosio::contract::contract;

   kvcontract(eosio::name receiver, eosio::name code, eosio::datastream<const char*> ds)
       : contract{ receiver, code, ds } {}

   ACTION insert(eosio::name account, uint64_t key, const std::string& value) {
      require_auth(account);
      m_db[key] = value;
   }

   ACTION modify(eosio::name account, uint64_t key, const std::string& value) {
      require_auth(account);
      m_db[key] = value;
   }

   ACTION erase(eosio::name account, uint64_t key) {
      require_auth(account);
      m_db.erase(key);
   }

   ACTION print(eosio::name account, uint64_t key) {
      // search for person by primary key account_name
      auto it = m_db.find(key);
      eosio::check(it != std::end(m_db), "Key does not exist");
      eosio::print("Value: ", it->second());
   }
};