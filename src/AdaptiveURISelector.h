/* <!-- copyright */
/*
 * aria2 - The high speed download utility
 *
 * Copyright (C) 2006 Tatsuhiro Tsujikawa
 * Copyright (C) 2008 Aurelien Lefebvre, Mandriva
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * In addition, as a special exception, the copyright holders give
 * permission to link the code of portions of this program with the
 * OpenSSL library under certain conditions as described in each
 * individual source file, and distribute linked combinations
 * including the two.
 * You must obey the GNU General Public License in all respects
 * for all of the code used other than OpenSSL.  If you modify
 * file(s) with this exception, you may extend this exception to your
 * version of the file(s), but you are not obligated to do so.  If you
 * do not wish to do so, delete this exception statement from your
 * version.  If you delete this exception statement from all source
 * files in the program, then also delete it here.
 */
/* copyright --> */
#ifndef _D_ADAPTIVE_URI_SELECTOR_H_
#define _D_ADAPTIVE_URI_SELECTOR_H_
#include "URISelector.h"
#include "SharedHandle.h"

namespace aria2 {

class ServerStatMan;
class RequestGroup;
class ServerStat;
class Logger;

class AdaptiveURISelector:public URISelector {
private:
  SharedHandle<ServerStatMan> _serverStatMan;
  SharedHandle<RequestGroup> _requestGroup;
  unsigned int _nbServerToEvaluate;
  unsigned int _nbConnections;

  static const unsigned int MAX_TIMEOUT = 60;

  Logger* _logger;

  void mayRetryWithIncreasedTimeout(std::deque<std::string>& uris);

  std::string selectOne(const std::deque<std::string>& uris);
  void adjustLowestSpeedLimit(const std::deque<std::string>& uris,
			      DownloadCommand* command) const;
  unsigned int getMaxDownloadSpeed(const std::deque<std::string>& uris) const;
  std::string getMaxDownloadSpeedUri(const std::deque<std::string>& uris) const;
  std::deque<std::string> getUrisBySpeed(const std::deque<std::string>& uris,
					 unsigned int min) const;
  std::string selectRandomUri(const std::deque<std::string>& uris) const;
  std::string getFirstNotTestedUri(const std::deque<std::string>& uris) const;
  std::string getFirstToTestUri(const std::deque<std::string>& uris) const;
  SharedHandle<ServerStat> getServerStats(const std::string& uri) const;
  unsigned int getNbTestedServers(const std::deque<std::string>& uris) const;
public:
  AdaptiveURISelector(const SharedHandle<ServerStatMan>& serverStatMan, 
          const SharedHandle<RequestGroup>& requestGroup);

  virtual ~AdaptiveURISelector();

  virtual std::string select(std::deque<std::string>& uris);
  virtual void tuneDownloadCommand(const std::deque<std::string>& uris,
				   DownloadCommand* command);

  virtual void resetCounters();
};

} // namespace aria2
#endif // _D_ADAPTIVE_URI_SELECTOR_H_