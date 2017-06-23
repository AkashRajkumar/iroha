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

#ifndef IROHA_TEMPORARYWSV_HPP
#define IROHA_TEMPORARYWSV_HPP

#include <ametsuchi/command_executor.hpp>
#include <ametsuchi/wsv_query.hpp>
#include <dao/block.hpp>
#include <dao/transaction.hpp>

namespace iroha {

  namespace ametsuchi {

    /**
     * Temporary world state view
     * Allows to query the temporal world state view
     */
    class TemporaryWsv : public WsvQuery {
     public:
      /**
       * Applies a transaction to current state
       * using logic specified in function
       * @param transaction Transaction to be applied
       * @param function Function that specifies the logic used to apply the
       * transaction
       * Function parameters:
       *  - Transaction @see transaction
       *  - CommandExecutor
       *  - WSVQuery
       * Function returns true if the transaction is successfully applied, false
       * otherwise.
       * @return True if transaction was successfully applied, false otherwise
       *
       */
      virtual bool apply(
          dao::Transaction transaction,
          std::function<bool(dao::Transaction, CommandExecutor, WsvQuery)>
              function) = 0;
    };

  }  // namespace ametsuchi

}  // namespace iroha

#endif  // IROHA_TEMPORARYWSV_HPP
