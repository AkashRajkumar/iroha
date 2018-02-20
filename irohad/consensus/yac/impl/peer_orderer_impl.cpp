/**
 * Copyright Soramitsu Co., Ltd. 2017 All Rights Reserved.
 * http://soramitsu.co.jp
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "consensus/yac/impl/peer_orderer_impl.hpp"
#include <algorithm>
#include <random>
#include "ametsuchi/peer_query.hpp"
#include "consensus/yac/cluster_order.hpp"
#include "consensus/yac/yac_hash_provider.hpp"

namespace iroha {
  namespace consensus {
    namespace yac {

      PeerOrdererImpl::PeerOrdererImpl(
          std::shared_ptr<ametsuchi::PeerQuery> peer_query)
          : query_(std::move(peer_query)) {}

      nonstd::optional<ClusterOrdering> PeerOrdererImpl::getInitialOrdering() {
        auto shared_lst = query_->getLedgerPeers();
        auto lst = shared_lst | [](auto &a) {
          std::vector<model::Peer> peers;
          std::transform(
              a.begin(), a.end(), std::back_inserter(peers), [](auto &peer) {
                return *std::unique_ptr<iroha::model::Peer>(peer->makeOldModel());
              });
          return nonstd::make_optional(peers);
        };
        return lst |
            [](const auto &peers) { return ClusterOrdering::create(peers); };
      }

      nonstd::optional<ClusterOrdering> PeerOrdererImpl::getOrdering(
          const YacHash &hash) {
        return query_->getLedgerPeers() | [](auto &a) {
          std::vector<model::Peer> peers;
          std::transform(
              a.begin(), a.end(), std::back_inserter(peers), [](auto &peer) {
                return *std::unique_ptr<iroha::model::Peer>(peer->makeOldModel());
              });
          return nonstd::make_optional(peers);
        } | [&hash](auto peers) {
            std::seed_seq seed(hash.block_hash.begin(), hash.block_hash.end());
            std::default_random_engine gen(seed);
            std::shuffle(peers.begin(), peers.end(), gen);
            return ClusterOrdering::create(peers);
          };
        }
      }  // namespace yac
    }    // namespace yac
  }      // namespace consensus
