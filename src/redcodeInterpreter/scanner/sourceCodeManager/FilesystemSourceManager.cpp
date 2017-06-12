//
// Created by Sylwia Blach on 5/5/17.
//

#include "FilesystemSourceManager.hpp"

void FilesystemSourceManager::init ()
{
    openFile();
    fin_.exceptions (std::ifstream::badbit);
}

void FilesystemSourceManager::openFile ()
{
    boost::filesystem::path file(fileName_);
    if(boost::filesystem::exists(file))
    {
        fin_.open(fileName_);
        lineNr_ = 1;
    }
    else
        throw new SourceFileNotFound();
}

char FilesystemSourceManager::getNext ()
{
    //boost::mutex::scoped_lock scoped_lock(readMutex_);

    if (endReached_)
        return EOF;

    char result;
    if ((fin_ >> std::noskipws >> result).eof())
        endReached_ = true;

    if (result == '\n')
        ++lineNr_;

    return result;
}