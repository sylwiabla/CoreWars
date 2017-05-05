//
// Created by Sylwia Blach on 5/5/17.
//

#include "FilesystemSourceManager.hpp"

void FilesystemSourceManager::openFile ()
{
    boost::filesystem::path file(fileName_);
    if(boost::filesystem::exists(file))
    {
        fin_.open(fileName_);
        lineNr_ = 1;
        opened_ = true;
    }
    else
        throw new SourceFileNotFound();
}

char FilesystemSourceManager::getNext ()
{
    boost::mutex::scoped_lock scoped_lock(readMutex_);

    if(!opened_)
        openFile();

    fin_.exceptions (std::ifstream::badbit);
    char result = DEFAULT_CHAR;
    if (!(fin_ >> std::noskipws >> result))
        endReached_ = true;

    if (result == '\n')
        ++lineNr_;

    return result;
}