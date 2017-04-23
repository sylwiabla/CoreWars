//
// Created by Sylwia Blach on 4/18/17.
//
#include "SourceCodeManager.hpp"

char SourceCodeManager::getNext ()
{
    boost::mutex::scoped_lock scoped_lock(readMutex_);

    if(!opened_)
        openFile();

    fin_.exceptions (std::ifstream::badbit);
    char result = DEFAULT_CHAR;
    if (!(fin_ >> std::noskipws >> result))
        endReached_ = true;

    return result;
}

void SourceCodeManager::openFile ()
{
    boost::filesystem::path file(fileName_);
    if(boost::filesystem::exists(file))
    {
        fin_.open(fileName_);
        opened_ = true;
    }
    else
        throw new SourceFileNotFound();
}