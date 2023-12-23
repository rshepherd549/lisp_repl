#pragma once

#include <functional>
#include <string>

#include <list.h>

const List& InitialContext();

List Find(const List& list, const std::function<bool(const List&)>& pred);
List FindKey(const List& list, const Car_t& key);
List FindKeyValue(const List& list, const Car_t& key);

List Read(const std::string_view text);
List Eval(const List& list, const List& context);
