#pragma once
#include <string>
#include <memory>
#include <variant>

template <typename TVariant, typename TType, size_t idx = 0>
constexpr size_t variant_index()
{
  if constexpr (idx == std::variant_size_v<TVariant>) //NOLINT(readability-braces-around-statements)
  {
    //Return size if idx reaches size without a match
    return idx;
  }
  else if constexpr (std::is_same_v<std::variant_alternative_t<idx, TVariant>, TType>) //NOLINT(readability-braces-around-statements)
  {
    //Return idx if the type matches
    return idx;
  }
  else //NOTE: if constexpr needs the elses
  {
    //Recurse to the next value of idx
    return variant_index<TVariant, TType, idx + 1>();
  }
}

class List;

extern const List EmptyList;

using Car_t = std::variant<std::string_view, List>;
enum Car_
{
  text = variant_index<Car_t, std::string_view>(),
  list = variant_index<Car_t, List>(),
};

extern const Car_t CarNull;

struct Cons_
{
  Car_t const & car_;
  Cons_ const * cdr_{};
  mutable size_t numWatchers_{};
};

class List
{
  Cons_ const * cons_{};
  List(Cons_ const * cons);
public:

  ~List();
  List();
  List(const List& list);
  List(const List& list, const Car_t& value);
  List& operator=(List list);

  const Car_t& Car() const;
  List Cdr() const;
  bool IsEmpty() const;
};

List Cons(const Car_t& car, const List& cdr);
const Car_t& Car(const Car_t& car);
List Cdr(const Car_t& car);

List MakeList();
List MakeList(const Car_t& car);

template <typename... Rest>
List MakeList(const Car_t& car, Rest... cdr) {
  return Cons(car, MakeList(cdr...));
}

bool IsEmptyList(const Car_t& car);
bool IsAtom(const Car_t& car);
bool IsEqual(const Car_t& lhs, const Car_t& rhs);
std::string to_string(const Car_t& car);
