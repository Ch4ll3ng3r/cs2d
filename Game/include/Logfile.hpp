#ifndef LOGFILE_HPP_INCLUDED
#define LOGFILE_HPP_INCLUDED

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class CLogfile
{
    public:
        CLogfile (string strFileName);
        void Write (string strText);

    private:
        string m_strFileName;
};

#endif // LOGFILE_HPP_INCLUDED
