#include <eosio/eosio.hpp>

CONTRACT dbcontract : public eosio::contract {
 private:
   TABLE db_table {
      uint64_t    key{ 0 };
      std::string value;

      uint64_t primary_key() const { return key; }
   };

   using db_tables = eosio::multi_index<"row"_n, db_table>;
   db_tables m_db;

 public:
   using eosio::contract::contract;

   dbcontract(eosio::name receiver, eosio::name code, eosio::datastream<const char*> ds)
       : contract{ receiver, code, ds }, m_db{ get_self(), get_first_receiver().value } {}

   ACTION insert(eosio::name account, uint64_t key, const std::string& value) {
      require_auth(account);
      eosio::check(m_db.find(key) == std::end(m_db), "key already exists");

      m_db.emplace(account, [&](auto& row) {
         row.key   = key;
         row.value = value;
      });
   }

   ACTION modify(eosio::name account, uint64_t key, const std::string& value) {
      require_auth(account);
      auto it = m_db.find(key);
      eosio::check(it != std::end(m_db), "key does not exist");

      m_db.modify(it, account, [&](auto& row) { row.value = value; });
   }

   ACTION erase(eosio::name account, uint64_t key) {
      require_auth(account);
      auto it = m_db.find(key);
      eosio::check(it != std::end(m_db), "key does not exist");
      m_db.erase(it);
   }

   ACTION print(eosio::name account, uint64_t key) {
      require_auth(account);
      auto it = m_db.find(key);
      eosio::check(it != std::end(m_db), "key does not exist");
      eosio::print("Value: ", it->value);
   }
};