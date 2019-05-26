#ifndef __H_LOGGER__
#define __H_LOGGER__

#include <cstdio>
#include <tchar.h>

class Logger
{
private:
    const TCHAR *fileName;

public:
    enum class Level
    {
        LEVEL_ERROR,
        LEVEL_WARN,
        LEVEL_INFO,
        LEVEL_DEBUG
    };

    Logger(const TCHAR *fileName)
    {
        this->fileName = fileName;
    }

    bool log(Level level, const TCHAR *message)
    {
        FILE *fp = _tfopen(this->fileName, _T("a"));
        if (nullptr == fp) {
            return false;
        }
        if (Level::LEVEL_ERROR == level) {
            _fputts(_T("[ERROR]"), fp);
        } else if (Level::LEVEL_WARN == level) {
            _fputts(_T("[WARN]"), fp);
        } else if (Level::LEVEL_INFO == level) {
            _fputts(_T("[INFO]"), fp);
        } else /*if (Level::LEVEL_DEBUG == level)*/ {
            _fputts(_T("[DEBUG]"), fp);
        }
        if (_ftprintf(fp, _T(" %s\n"), message) <= 0) {
            return false;
        }
        return fclose(fp) == 0;
    }

    bool debug(const TCHAR *message)
    {
        return log(Level::LEVEL_DEBUG, message);
    }

    bool info(const TCHAR *message)
    {
        return log(Level::LEVEL_INFO, message);
    }

    bool warn(const TCHAR *message)
    {
        return log(Level::LEVEL_WARN, message);
    }

    bool error(const TCHAR *message)
    {
        return log(Level::LEVEL_ERROR, message);
    }
};
#endif // __H_LOGGER__