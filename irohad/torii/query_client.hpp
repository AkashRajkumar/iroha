/**
 * Copyright Soramitsu Co., Ltd. 2018 All Rights Reserved.
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

#ifndef TORII_UTILS_QUERY_CLIENT_HPP
#define TORII_UTILS_QUERY_CLIENT_HPP

namespace iroha {
  namespace protocol {
    class Query;
    class QueryResponse;
  }  // namespace protocol
}  // namespace iroha

namespace torii_utils {

  /**
   * Interface for access to query service from client.
   */
  class QueryClient {
   public:
    /**
     * requests query to a torii server and returns response (blocking, sync)
     * @param query - contains Query what clients request.
     * @param response - QueryResponse that contains what clients want to get.
     * @return grpc::Status
     */
    virtual grpc::Status Find(
        const iroha::protocol::Query &query,
        iroha::protocol::QueryResponse &response) const = 0;

    virtual ~QueryClient() = default;
  };
}  // namespace torii_utils

#endif  // TORII_UTILS_QUERY_CLIENT_HPP
