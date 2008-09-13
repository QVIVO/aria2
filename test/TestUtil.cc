#include "TestUtil.h"
#include "a2io.h"
#include "File.h"
#include "StringFormat.h"
#include "FatalException.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cerrno>
#include <cstring>

namespace aria2 {

void createFile(const std::string& path, size_t length)
{
  File(File(path).getDirname()).mkdirs();
  int fd = creat(path.c_str(), OPEN_MODE);
  if(fd == -1) {
    throw FatalException(StringFormat("Could not create file=%s. cause:%s",
				      path.c_str(), strerror(errno)).str());
  }
  if(-1 == ftruncate(fd, length)) {
    throw FatalException(StringFormat("ftruncate failed. cause:%s",
				      strerror(errno)).str());
  }
  close(fd);
}

};