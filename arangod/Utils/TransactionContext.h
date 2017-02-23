////////////////////////////////////////////////////////////////////////////////
/// DISCLAIMER
///
/// Copyright 2014-2016 ArangoDB GmbH, Cologne, Germany
/// Copyright 2004-2014 triAGENS GmbH, Cologne, Germany
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///     http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
/// Copyright holder is ArangoDB GmbH, Cologne, Germany
///
/// @author Jan Steemann
////////////////////////////////////////////////////////////////////////////////

#ifndef ARANGOD_UTILS_TRANSACTION_CONTEXT_H
#define ARANGOD_UTILS_TRANSACTION_CONTEXT_H 1

#include "Basics/Common.h"
#include "Basics/Mutex.h"
#include "Basics/SmallVector.h"
#include "VocBase/voc-types.h"

#include <velocypack/Options.h>

struct TRI_vocbase_t;

namespace arangodb {
namespace basics {
class StringBuffer;
}

namespace velocypack {
class Builder;
struct CustomTypeHandler;
}

class CollectionNameResolver;
class DocumentDitch;
class LogicalCollection;
namespace transaction {
class Methods;
}
;
class TransactionState;

class TransactionContext {
 public:
  TransactionContext(TransactionContext const&) = delete;
  TransactionContext& operator=(TransactionContext const&) = delete;

 protected:

  /// @brief create the context
  explicit TransactionContext(TRI_vocbase_t* vocbase);

 public:

  /// @brief destroy the context
  virtual ~TransactionContext();

  /// @brief factory to create a custom type handler, not managed
  static arangodb::velocypack::CustomTypeHandler* createCustomTypeHandler(
           TRI_vocbase_t*,
           arangodb::CollectionNameResolver const*);

  /// @brief return the vocbase
  TRI_vocbase_t* vocbase() const { return _vocbase; }
  
  /// @brief order a document ditch for the collection
  /// this will create one if none exists. if no ditch can be created, the
  /// function will return a nullptr!
  DocumentDitch* orderDitch(arangodb::LogicalCollection*);
  
  /// @brief return the ditch for a collection
  /// this will return a nullptr if no ditch exists
  DocumentDitch* ditch(TRI_voc_cid_t) const;

  /// @brief temporarily lease a StringBuffer object
  basics::StringBuffer* leaseStringBuffer(size_t initialSize);

  /// @brief return a temporary StringBuffer object
  void returnStringBuffer(basics::StringBuffer* stringBuffer);
  
  /// @brief temporarily lease a Builder object
  arangodb::velocypack::Builder* leaseBuilder();
  
  /// @brief return a temporary Builder object
  void returnBuilder(arangodb::velocypack::Builder*);
  
  /// @brief get velocypack options with a custom type handler
  arangodb::velocypack::Options* getVPackOptions();
  
  /// @brief get velocypack options for dumping
  arangodb::velocypack::Options* getVPackOptionsForDump();
  
  /// @brief unregister the transaction
  /// this will save the transaction's id and status locally
  void storeTransactionResult(TRI_voc_tid_t id, bool hasFailedOperations) noexcept;
  
  /// @brief get a custom type handler
  virtual std::shared_ptr<arangodb::velocypack::CustomTypeHandler>
  orderCustomTypeHandler() = 0;

  /// @brief return the resolver
  virtual CollectionNameResolver const* getResolver() = 0;

  /// @brief get parent transaction (if any)
  virtual TransactionState* getParentTransaction() const = 0;

  /// @brief whether or not the transaction is embeddable
  virtual bool isEmbeddable() const = 0;

  /// @brief register the transaction in the context
  virtual void registerTransaction(TransactionState*) = 0;
  
  /// @brief unregister the transaction
  virtual void unregisterTransaction() = 0;

 protected:
  
  /// @brief create a resolver
  CollectionNameResolver const* createResolver();
 
 protected:
  
  TRI_vocbase_t* _vocbase; 
  
  CollectionNameResolver const* _resolver;
  
  std::shared_ptr<velocypack::CustomTypeHandler> _customTypeHandler;
  
  std::unordered_map<TRI_voc_cid_t, DocumentDitch*> _ditches;

  SmallVector<arangodb::velocypack::Builder*, 32>::allocator_type::arena_type _arena;
  SmallVector<arangodb::velocypack::Builder*, 32> _builders;
  
  std::unique_ptr<arangodb::basics::StringBuffer> _stringBuffer;

  arangodb::velocypack::Options _options;
  arangodb::velocypack::Options _dumpOptions;

  struct {
    TRI_voc_tid_t id; 
    bool hasFailedOperations;
  } _transaction;

  bool _ownsResolver;
};
}

#endif
