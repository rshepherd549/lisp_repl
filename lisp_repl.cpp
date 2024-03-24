#include <lisp_repl.h>

List CreateInitialContext_()
{
  //A list of named entities, with the last added given precedence
  //Each entry is a pair of string name and value
  const auto Entry = [](std::string_view name, const Car_t& value)
  {
    List list;
    list = Cons(value, list);
    list = Cons(name, list);
    return list;
  };

  List list;
  list = Cons(Entry("a", "A"), list);

  return list;
}

const List& InitialContext()
{
  static auto list = CreateInitialContext_();
  return list;
}

List Find(const List& list, const std::function<bool(const List&)>& pred)
{
  if (pred(list))
    return list;

  if (IsEmptyList(list))
    return EmptyList;

  return Find(Cdr(list), pred);
}
List FindKey(const List& list, const Car_t& key)
{
  return Find(list, [&key](const List& list)
         {
           return IsEqual(Car(list), key);
         });
}
List FindKeyValue(const List& list, const Car_t& key)
{
  return Find(list, [&key](const List& list)
         {
           return IsEqual(Car(list), key);
         });
}

template<typename TChar>
List ReadList(TChar /*begin*/, TChar /*end*/)
{
  return {};
}

List Read(const std::string_view text)
{
  return ReadList(text.cbegin(), text.cend());
}
List Eval(const List& list, const List& context)
{
  if (IsEmptyList(list))
    return list;

  const auto& car = Car(list);

  const auto& contextEntry = FindKeyValue(context, car);
  (void*)(&contextEntry);
  return list;
}
