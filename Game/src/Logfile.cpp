#include "../include/Logfile.hpp"

CLogfile::CLogfile (string strFileName)
{
    m_strFileName = strFileName;
    string strNewRunBorder = "----------------------------------------------------------\n";
    ofstream Output (m_strFileName + ".txt", ios::app);
    if (Output.good ())
        Output.write (strNewRunBorder.c_str (), strNewRunBorder.size ());
    else
        cout << "failed to open file " << m_strFileName << ".txt" << endl;
    Output.close ();
}

void CLogfile::Write (string strText)
{
    strText.append ("\n");
    ofstream Output (m_strFileName + ".txt", ios::app);
    if (Output.good ())
        Output.write (strText.c_str (), strText.size ());
    else
        cout << "failed to open file " << m_strFileName << ".txt" << endl;
    Output.close ();
}
