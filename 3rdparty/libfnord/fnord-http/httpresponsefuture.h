/**
 * This file is part of the "FnordMetric" project
 *   Copyright (c) 2014 Paul Asmuth, Google Inc.
 *
 * FnordMetric is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License v3.0. You should have received a
 * copy of the GNU General Public License along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */
#ifndef _FNORDMETRIC_HTTPRESPONSEFUTURE_H
#define _FNORDMETRIC_HTTPRESPONSEFUTURE_H
#include "fnord-base/status.h"
#include "fnord-http/httpresponse.h"
#include "fnord-http/httpresponsehandler.h"
#include "fnord-http/httpclientconnection.h"
#include "fnord-base/thread/future.h"
#include "fnord-base/thread/wakeup.h"
#include <memory>

namespace fnord {
namespace http {

class HTTPResponseFuture : public HTTPResponseHandler {
public:
  HTTPResponseFuture(Promise<HTTPResponse> promise);
  virtual ~HTTPResponseFuture();

  HTTPResponseFuture(const HTTPResponseFuture& other) = delete;
  HTTPResponseFuture& operator=(const HTTPResponseFuture& other) = delete;

  void storeConnection(std::unique_ptr<HTTPClientConnection>&& conn);

  virtual void onError(const std::exception& e) override;
  virtual void onVersion(const std::string& version) override;
  virtual void onStatusCode(int status_code) override;
  virtual void onStatusName(const std::string& status) override;
  virtual void onHeader(const std::string& key, const std::string& value) override;
  virtual void onHeadersComplete() override;
  virtual void onBodyChunk(const char* data, size_t size) override;
  virtual void onResponseComplete() override;

protected:
  HTTPResponse res_;
  Promise<HTTPResponse> promise_;
  std::unique_ptr<HTTPClientConnection> conn_;
};

class StreamingResponseFuture : public HTTPResponseFuture {
public:
  typedef Function<void (const char* data, size_t size)> CallbackType;

  StreamingResponseFuture(
      Promise<HTTPResponse> promise,
      CallbackType callback);

  void onBodyChunk(const char* data, size_t size) override;

protected:
  CallbackType callback_;
};

}
}
#endif