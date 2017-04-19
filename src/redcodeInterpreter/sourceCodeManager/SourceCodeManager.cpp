//
// Created by Sylwia Blach on 4/18/17.
//
#include "SourceCodeManager.hpp"

int SourceCodeManager::getNext ()
{
    if(!opened_)
        openFile();

    fin_.exceptions (std::ifstream::badbit);
    try
    {
        return fin_.eof() ? -1 : fin_.get();
    }
    catch (const std::ifstream::failure & e) {
        //throw new ReadFileException ();
    }
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
