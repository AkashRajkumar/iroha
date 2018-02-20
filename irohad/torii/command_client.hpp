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

#ifndef TORII_IROHA_COMMAND_CLIENT_HPP
#define TORII_IROHA_COMMAND_CLIENT_HPP

namespace iroha {
  namespace protocol {
    class Transaction;
    class TxStatusRequest;
    class ToriiResponse;
  }
}

namespace torii {

  /**
   * Interface provides access to command server from client.
   */
  class CommandClient {
   public:
    /**
     * requests tx to a torii server and returns response (blocking, sync)
     * @param tx
     * @return grpc::Status - returns connection is success or not.
     */
    virtual grpc::Status Torii(const iroha::protocol::Transaction &tx) const = 0;

    /**
     * @param tx
     * @param response returns ToriiResponse if succeeded
     * @return grpc::Status - returns connection is success or not.
     */
    virtual grpc::Status Status(const iroha::protocol::TxStatusRequest &tx,
                        iroha::protocol::ToriiResponse &response) const = 0;

    /**
     * Acquires stream of transaction statuses from the request
     * moment until final.
     * @param tx - transaction to send.
     * @param response - vector of all statuses during tx pipeline.
     */
    virtual void StatusStream(
        const iroha::protocol::TxStatusRequest &tx,
        std::vector<iroha::protocol::ToriiResponse> &response) const = 0;

    virtual ~CommandClient() = default;
  };
}

#endif //TORII_UTILS_IROHA_COMMAND_CLIENT_HPP
