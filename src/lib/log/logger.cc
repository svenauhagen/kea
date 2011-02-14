// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE

#include <stdarg.h>
#include <stdio.h>

#include <log/logger.h>
#include <log/logger_impl.h>
#include <log/message_dictionary.h>
#include <log/message_types.h>
#include <log/root_logger_name.h>
#include <log/strutil.h>

using namespace std;

namespace isc {
namespace log {

// Initialize Logger implementation.  Does not check whether the implementation
// has already been initialized - that was done by the caller (getLoggerPtr()).
void Logger::initLoggerImpl() {
    loggerptr_ = new LoggerImpl(name_, infunc_);
}

// Destructor.

Logger::~Logger() {
    delete loggerptr_;
}

// Get Name of Logger

std::string
Logger::getName() {
    return (getLoggerPtr()->getName());
}

// Set the severity for logging.

void
Logger::setSeverity(isc::log::Severity severity, int dbglevel) {
    getLoggerPtr()->setSeverity(severity, dbglevel);
}

// Return the severity of the logger.

isc::log::Severity
Logger::getSeverity() {
    return (getLoggerPtr()->getSeverity());
}

// Get Effective Severity Level for Logger

isc::log::Severity
Logger::getEffectiveSeverity() {
    return (getLoggerPtr()->getEffectiveSeverity());
}

// Debug level (only relevant if messages of severity DEBUG are being logged).

int
Logger::getDebugLevel() {
    return (getLoggerPtr()->getDebugLevel());
}

// Check on the current severity settings

bool
Logger::isDebugEnabled(int dbglevel) {
    return (getLoggerPtr()->isDebugEnabled(dbglevel));
}

bool
Logger::isInfoEnabled() {
    return (getLoggerPtr()->isInfoEnabled());
}

bool
Logger::isWarnEnabled() {
    return (getLoggerPtr()->isWarnEnabled());
}

bool
Logger::isErrorEnabled() {
    return (getLoggerPtr()->isErrorEnabled());
}

bool
Logger::isFatalEnabled() {
    return (getLoggerPtr()->isFatalEnabled());
}

// Format a message: looks up the message text in the dictionary and formats
// it, replacing tokens with arguments.
//
// Owing to the use of variable arguments, this must be inline (hence the
// definition of the macro).  Also note that it expects that the message buffer
// "message" is declared in the compilation unit.

    

// Output methods

void
Logger::debug(int dbglevel, const isc::log::MessageID& ident, ...) {
    if (isDebugEnabled(dbglevel)) {
        va_list ap;
        va_start(ap, ident);
        getLoggerPtr()->debug(ident, ap);
        va_end(ap);
    }
}

void
Logger::info(const isc::log::MessageID& ident, ...) {
    if (isInfoEnabled()) {
        va_list ap;
        va_start(ap, ident);
        getLoggerPtr()->info(ident, ap);
        va_end(ap);
    }
}

void
Logger::warn(const isc::log::MessageID& ident, ...) {
    if (isWarnEnabled()) {
        va_list ap;
        va_start(ap, ident);
        getLoggerPtr()->warn(ident, ap);
        va_end(ap);
    }
}

void
Logger::error(const isc::log::MessageID& ident, ...) {
    if (isErrorEnabled()) {
        va_list ap;
        va_start(ap, ident);
        getLoggerPtr()->error(ident, ap);
        va_end(ap);
    }
}

void
Logger::fatal(const isc::log::MessageID& ident, ...) {
    if (isFatalEnabled()) {
        va_list ap;
        va_start(ap, ident);
        getLoggerPtr()->fatal(ident, ap);
        va_end(ap);
    }
}

bool Logger::operator==(Logger& other) {
    return (*getLoggerPtr() == *other.getLoggerPtr());
}

// Protected methods (used for testing)

void
Logger::reset() {
    LoggerImpl::reset();
}

} // namespace log
} // namespace isc
