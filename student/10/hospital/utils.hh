/* Module: Utils
 * ----------
 * COMP.CS.110 SPRING 2024
 * ----------
 * Module for different utilities needed in the program.
 *
 * Note: Students shouldn't need to make changes to this module.
 * */
#ifndef UTILS_HH
#define UTILS_HH

#include "date.hh"
#include <vector>
#include <string>

namespace utils
{
/**
 * @brief split
 * @param str
 * @param delim
 * @return vector containing the parts, no delim chars
 * Splits the given string at every delim char
 */
std::vector<std::string> split( std::string& str, char delim = ';');

/**
 * @brief is_numeric
 * @param s
 * @param zero_allowed : if zero is allowed to be the whole string
 * @return true if given string is numeric
 */
bool is_numeric(std::string& s, bool zero_allowed);

/**
 * @brief today
 * Static means this variable will only be created once per run.
 */
static Date today = Date(24, 2, 2024);
}

#endif // UTILS_HH
