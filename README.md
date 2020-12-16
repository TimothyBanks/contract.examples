### How to execute the examples
* Build
    * mkdir build
    * cd build
    * cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_FRAMEWORK_PATH=/Users/timothy.banks/Work/issues/rocksdb-training/eos/release -DCMAKE_FRAMEWORK_PATH=/Users/timothy.banks/Work/issues/rocksdb-training/eosio.cdt/release -DEOSIO_ROOT=/Users/timothy.banks/Work/issues/rocksdb-training/eos/release -DEOSIO_CDT_ROOT=/Users/timothy.banks/Work/issues/rocksdb-training/eosio.cdt/release ..
    * make -j7

* Run
    * cleos wallet create --to-console
        * Save the wallet password:  PW5KV6fL5jVDtXvQQt9ETj2px24HbdJtQ5EnZJbWWJcurhVE9PbM6
    * cleos wallet unlock
    * cleos wallet create_key
        * Save the public key:  EOS5xT2eyxPec1tC1ZGWQyVvY6m5SQaE84obveth9Lg8gDXiZnLxf
    * Import the development key
        * cleos wallet import
        * development private key: 5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3
        * development public key: EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV
    * Register contracts and enable protocol features
        * execute script eos/contracts/enable-kv.sh
    * Start keosd
        * keods &
    * Start nodeos
        * nodeos -e -p eosio \
                    --data-dir=. \
                    --plugin eosio::producer_plugin \
                    --plugin eosio::producer_api_plugin \
                    --plugin eosio::chain_api_plugin \
                    --plugin eosio::http_plugin \
                    --plugin eosio::history_plugin \
                    --plugin eosio::history_api_plugin \
                    --filter-on="*" \
                    --access-control-allow-origin='*' \
                    --contracts-console \
                    --http-validate-host=false \
                    --verbose-http-errors >> nodeos.log 2>&1 &
    * Create test accounts
        * cleos create account eosio bob EOS5xT2eyxPec1tC1ZGWQyVvY6m5SQaE84obveth9Lg8gDXiZnLxf
        * cleos create account eosio alice EOS5xT2eyxPec1tC1ZGWQyVvY6m5SQaE84obveth9Lg8gDXiZnLxf
        * cleos create account eosio kvcontract EOS5xT2eyxPec1tC1ZGWQyVvY6m5SQaE84obveth9Lg8gDXiZnLxf
        * cleos create account eosio dbcontract EOS5xT2eyxPec1tC1ZGWQyVvY6m5SQaE84obveth9Lg8gDXiZnLxf

    * Deploy contracts
        * cleos set contract dbcontract dbcontract -p dbcontract@active
        * cleos set contract kvcontract kvcontract -p kvcontract@active

* Exercise dbcontract
    * cleos push action dbcontract insert '[alice, 0, "Hello world"]' -p alice@active
    * cleos push action dbcontract print '[alice, 0]' -p alice@active
    * cleos push action dbcontract modify '[alice, 0, "Hello world 2"]' -p alice@active
    * cleos push action dbcontract print '[alice, 0]' -p alice@active
    * cleos push action dbcontract erase '[alice, 0]' -p alice@active
    * cleos push action dbcontract print '[alice, 0]' -p alice@active

* Exercise kvcontract
    * cleos push action kvcontract insert '[bob, 0, "Hello world"]' -p bob@active
    * cleos push action kvcontract print '[bob, 0]' -p bob@active
    * cleos push action kvcontract modify '[bob, 0, "Hello world 2"]' -p bob@active
    * cleos push action kvcontract print '[bob, 0]' -p bob@active
    * cleos push action kvcontract erase '[bob, 0]' -p bob@active
    * cleos push action kvcontract print '[bob, 0]' -p bob@active

* Print tables with cleos
    * cleos push action dbcontract insert '[alice, 0, "Hello world"]' -p alice@active
    * cleos get table dbcontract dbcontract row
    * cleos push action kvcontract insert '[bob, 0, "Hello world"]' -p bob@active
    * cleos push action kvcontract insert '[bob, 0, "Hello world"]' -p bob@active
    * cleos get kv_table kvcontract kvtable map.index --lower '0' --encode-type uint64