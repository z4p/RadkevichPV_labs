#ifndef LISTEXCEPTIONS_H
#define	LISTEXCEPTIONS_H

#include <exception>

class NotFoundException : public std::exception {
public:
    virtual const char* what() const throw() {
        return "Element not found";
    }
};

class DuplicateKeyException : public std::exception {
public:
    virtual const char* what() const throw() {
        return "Inserting element with the same key is disabled";
    }
};

#endif	/* LISTEXCEPTIONS_H */

