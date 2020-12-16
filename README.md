### How to execute the examples
1.  Build
1.1 mkdir build
1.2 cd build
1.3 cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_FRAMEWORK_PATH=/Users/timothy.banks/Work/issues/rocksdb-training/eos/release -DCMAKE_FRAMEWORK_PATH=/Users/timothy.banks/Work/issues/rocksdb-training/eosio.cdt/release -DEOSIO_ROOT=/Users/timothy.banks/Work/issues/rocksdb-training/eos/release -DEOSIO_CDT_ROOT=/Users/timothy.banks/Work/issues/rocksdb-training/eosio.cdt/release ..
1.4 make -j7

2.  Run
2.1 cleos wallet create --to-console
2.1.1 Save the wallet password:  PW5KV6fL5jVDtXvQQt9ETj2px24HbdJtQ5EnZJbWWJcurhVE9PbM6
2.2 cleos wallet unlock
2.3 cleos wallet create_key
2.3.1 Save the public key:  EOS5xT2eyxPec1tC1ZGWQyVvY6m5SQaE84obveth9Lg8gDXiZnLxf
2.4 Import the development key
2.4.1 cleos wallet import
2.4.2 development private key: 5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3
2.4.3 development public key: EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV
2.5 Register contracts and enable protocol features
2.5.1 execute script eos/contracts/enable-kv.sh
2.6 Start keosd
2.6.1 keods &
2.7 Start nodeos
2.7.1 nodeos -e -p eosio \
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
2.8 Create test accounts
2.8.1 cleos create account eosio bob EOS5xT2eyxPec1tC1ZGWQyVvY6m5SQaE84obveth9Lg8gDXiZnLxf
2.8.2 cleos create account eosio alice EOS5xT2eyxPec1tC1ZGWQyVvY6m5SQaE84obveth9Lg8gDXiZnLxf
2.8.3 cleos create account eosio kvcontract EOS5xT2eyxPec1tC1ZGWQyVvY6m5SQaE84obveth9Lg8gDXiZnLxf
2.8.3 cleos create account eosio dbcontract EOS5xT2eyxPec1tC1ZGWQyVvY6m5SQaE84obveth9Lg8gDXiZnLxf

2.9 Deploy contracts
2.9.1 cleos set contract dbcontract dbcontract -p dbcontract@active
2.9.2 cleos set contract kvcontract kvcontract -p kvcontract@active

3.0 Exercise dbcontract
3.1 cleos push action dbcontract insert '[alice, 0, "Hello world"]' -p alice@active
3.2 cleos push action dbcontract print '[alice, 0]' -p alice@active
3.3 cleos push action dbcontract modify '[alice, 0, "Hello world 2"]' -p alice@active
3.4 cleos push action dbcontract print '[alice, 0]' -p alice@active
3.5 cleos push action dbcontract erase '[alice, 0]' -p alice@active
3.6 cleos push action dbcontract print '[alice, 0]' -p alice@active

4.0 Exercise kvcontract
4.1 cleos push action kvcontract insert '[bob, 0, "Hello world"]' -p bob@active
4.2 cleos push action kvcontract print '[bob, 0]' -p bob@active
4.3 cleos push action kvcontract modify '[bob, 0, "Hello world 2"]' -p bob@active
4.4 cleos push action kvcontract print '[bob, 0]' -p bob@active
4.5 cleos push action kvcontract erase '[bob, 0]' -p bob@active
4.6 cleos push action kvcontract print '[bob, 0]' -p bob@active

5.0 Print tables with cleos
5.1 cleos push action dbcontract insert '[alice, 0, "Hello world"]' -p alice@active
5.2 cleos get table dbcontract dbcontract row
5.3 cleos push action kvcontract insert '[bob, 0, "Hello world"]' -p bob@active
5.4 cleos push action kvcontract insert '[bob, 0, "Hello world"]' -p bob@active
5.5 cleos get kv_table kvcontract kvtable map.index --lower '0' --encode-type uint64