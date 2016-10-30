/*
Copyright Soramitsu Co., Ltd. 2016 All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

         http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "merkle.hpp"

#include "hash.hpp"
#include "../repository/consensus/merkle_transaction_repository.hpp"

/**
* Implementation of a binary Merkle tree （ハッシュ木）.
*/
namespace merkle {
    
    //void addLeaf(MerkleRepository const merkleTree, std:string const leaf, std::vector<std::string> const rootSignatures) {
    //    std:::string const leafHash = Hash::sha3_256_hex(leaf);
    //}

    // void recomputeAllFromRepository(TransactionRepository const txRepo) {
    //     std::vector<AbstractTransaction> currentLayer = make_unique(std::vector<AbstractTransaction>);
    //     for (std::shared_ptr<AbstractTransaction> tx : txRepo::getAllTransaction() {
    //         std:::string txHash = Hash::sha3_256_hex(tx::getRawData());
    //         currentLayer::add(txHash);
    //     }
        
    //     while (currentLayer::size() > 1) {
    //         for (int ndx = 0; ndx < currentLayer::size() - 1; ndx+=2) {
    //             Hash::sha3_256_hex(currentLayer[ndx], currentLayer[ndx+1]);
    //         }
    //     }
    // }
}  // namespace merkle