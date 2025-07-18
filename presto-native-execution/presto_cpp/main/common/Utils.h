/*
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once
#include <folly/io/async/SSLContext.h>
#include <glog/logging.h>
#include <folly/io/IOBuf.h>

namespace facebook::presto::util {

#define PRESTO_STARTUP_LOG_PREFIX "[PRESTO_STARTUP] "
#define PRESTO_STARTUP_LOG(severity) LOG(severity) << PRESTO_STARTUP_LOG_PREFIX

#define PRESTO_SHUTDOWN_LOG_PREFIX "[PRESTO_SHUTDOWN] "
#define PRESTO_SHUTDOWN_LOG(severity) \
  LOG(severity) << PRESTO_SHUTDOWN_LOG_PREFIX

using DateTime = std::string;
DateTime toISOTimestamp(uint64_t timeMilli);

std::shared_ptr<folly::SSLContext> createSSLContext(
    const std::string& clientCertAndKeyPath,
    const std::string& ciphers);

/// Returns current process-wide CPU time in nanoseconds.
long getProcessCpuTimeNs();

/// Install a custom signal handler.
/// On MacOS use a Google based implementation and on
/// Linux (other platforms) use a Folly (Velox) based implementation.
/// The reason is that the Folly based implementation relies
/// on libunwind to perform the symbolization which doesn't
/// exist for MacOS.
/// In addition, the Velox based implementation provides additonal
/// context such as the queryId.
void installSignalHandler();

std::string extractMessageBody(
    const std::vector<std::unique_ptr<folly::IOBuf>>& body);

inline std::string addDefaultNamespacePrefix(
    const std::string& prestoDefaultNamespacePrefix,
    const std::string& functionName) {
  return fmt::format("{}{}", prestoDefaultNamespacePrefix, functionName);
}
} // namespace facebook::presto::util
