#pragma once

#include "assert.hpp"

#include <string>
#include <algorithm>

namespace commands {

enum class type_t : unsigned char {
    CREATE,
    MODIFY,
    MOVE,
    ACCESS,
    DELETE,
    UNKNOWN,
};

enum class category_t : unsigned char {
    CUSTOM,
    COMMAND_LINE,
    UI,
};

inline bool equals(const std::string& lhs, const std::string& rhs)
{
    return std::equal(lhs.begin(), lhs.end(),
                      rhs.begin(), rhs.end(),
                      [](char a, char b) {
                          return tolower(a) == tolower(b);
                      });
}

enum class shape_type_t {
    TEXT,
    LINE,
    SQUARE,
    RECTANGLE,
    TRIANGLE,
    CIRCLE,
    ELIPSE,
    ARROW,
    PARALLOGRAM,
    POINT,
    UNKNOWN,
};

enum class key_t {
    STYLE,
    COLOUR,
    THICKNESS,
    UNKNOWN,
};

inline std::string key_to_string(key_t key)
{
    switch (key){
    case key_t::STYLE:
        return "style";
    case key_t::COLOUR:
        return "colour";
    case key_t::THICKNESS:
        return "thikness";
    case key_t::UNKNOWN:
        return "unknown";
    }
}

inline key_t key_type_from_string(const std::string key)
{
    if (equals(key, "style")) {
        return key_t::STYLE;
    } else if (equals(key, "colour")) {
        return key_t::COLOUR;
    } else if (equals(key, "thikness")) {
        return key_t::THICKNESS;
    } else {
        return key_t::UNKNOWN;
    }
}

inline std::string shape_type_to_string(shape_type_t type)
{
    switch (type) {
    case shape_type_t::TEXT:
        return "text";
    case shape_type_t::LINE:
        return "line";
    case shape_type_t::SQUARE:
        return "square";
    case shape_type_t::RECTANGLE:
        return "rectangle";
    case shape_type_t::TRIANGLE:
        return "triangle";
    case shape_type_t::CIRCLE:
        return "circle";
    case shape_type_t::ELIPSE:
        return "elipse";
    case shape_type_t::ARROW:
        return "arrow";
    case shape_type_t::PARALLOGRAM:
        return "parallelogram";
    case shape_type_t::POINT:
        return "point";
    case shape_type_t::UNKNOWN:
        return "unknown";
    default:
        ASSERT_MESSAGE(false, "UNEXPECTED SHAPE INPUT");
        return "unknown";
    }
}

inline shape_type_t shape_type_from_string(const std::string& type_str)
{
    if (type_str.empty()) {
        return shape_type_t::UNKNOWN;
    }
    if (equals(type_str, "text")) {
        return shape_type_t::TEXT;
    } else if (equals(type_str, "line")) {
        return shape_type_t::LINE;
    } else if (equals(type_str, "square")) {
        return shape_type_t::SQUARE;
    } else if (equals(type_str, "rectangle")) {
        return shape_type_t::RECTANGLE;
   } else if (equals(type_str, "triangle")) {
        return shape_type_t::TRIANGLE;
    } else if (equals(type_str, "circle")) {
        return shape_type_t::CIRCLE;
    } else if (equals(type_str, "elipse")) {
        return shape_type_t::ELIPSE;
    } else if (equals(type_str, "arrow")) {
        return shape_type_t::ARROW;
    } else if (equals(type_str, "parallelogram")) {
        return shape_type_t::PARALLOGRAM;
    } else if (equals(type_str, "point")) {
        return shape_type_t::POINT;
    } else {
        return shape_type_t::UNKNOWN;
    }
}

inline std::string type_to_string(type_t type)
{
    switch (type) {
    case type_t::CREATE:
        return "create";
    case type_t::MODIFY:
        return "modify";
    case type_t::MOVE:
        return "move";
    case type_t::ACCESS:
        return "access";
    case type_t::DELETE:
        return "delete";
    case type_t::UNKNOWN:
        return "unknown";
    default:
        ASSERT_MESSAGE(false, "UNEXPECTED INPUT");
        return "unknown";
    }
}

inline type_t type_from_string(const std::string& type_str)
{
    if (type_str.empty()) {
        return type_t::UNKNOWN;
    }
    if (equals(type_str, "create")) {
        return type_t::CREATE;
    } else if (equals(type_str, "modify")) {
        return type_t::MODIFY;
    } else if (equals(type_str, "move")) {
        return type_t::MOVE;
    } else if (equals(type_str, "access")) {
        return type_t::ACCESS;
    } else if (equals(type_str, "delete")) {
        return type_t::DELETE;
    } else {
        return type_t::UNKNOWN;
    }
}

} // end namespace commands
