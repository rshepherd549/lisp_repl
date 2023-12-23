#include <list.h>

List Null;
Car_t CarNull{Null};

List::~List()
{
  auto cons = cons_;
  while (cons)
  {
    --cons->numWatchers_;
    if (cons->numWatchers_ != 0)
      break;

    const auto cdr = cons->cdr_;
    delete cons;
    cons = cdr;
  }
}

List::List() = default;

List::List(Cons_ const * cons):
  cons_{cons}
{
  if (cons_)
    ++cons_->numWatchers_;
}

List::List(const List& list, const Car_t& car):
  cons_{new Cons_{car, list.cons_, 1}}
{
  if (cons_->cdr_)
    ++cons_->cdr_->numWatchers_;
}

List::List(const List& list):
  List{list.cons_}
{
}
List& List::operator=(List list)
{
  std::swap(cons_, list.cons_);
  return *this;
}
List List::Cons(const Car_t& value) const
{
  return List(*this, value);
}

const Car_t& List::Car() const
{
  return cons_ ? cons_->car_ : CarNull;
}
List List::Cdr() const
{
  return cons_ ? List{cons_->cdr_} : Null;
}
bool List::IsNull() const
{
  return !cons_;
}

List Cons(const Car_t& car, const List& cdr)
{
  return cdr.Cons(car);
}
const Car_t& Car(const Car_t& car)
{
  const auto list = std::get_if<List>(&car);
  return list ? list->Car() : car;
}
List Cdr(const Car_t& car)
{
  const auto list = std::get_if<List>(&car);
  return list ? list->Cdr() : List{};
}
bool IsNull(const Car_t& car)
{
  const auto list = std::get_if<List>(&car);
  return !list || list->IsNull();
}
bool IsAtom(const Car_t& car)
{
  const auto list = std::get_if<List>(&car);
  return !list;
}
bool IsEqual(const Car_t& lhs, const Car_t& rhs)
{
  if (IsNull(lhs) != IsNull(rhs))
    return false;
  if (IsNull(lhs))
    return true;

  switch (lhs.index())
  {
    case Car_::text:
    {
      const auto& lhsString = std::get<std::string_view>(lhs);
      if (const auto rhsString = std::get_if<std::string_view>(&rhs))
        return lhsString == *rhsString;
      break;
    }
    case Car_::list:
    {
      const auto& lhsList = std::get<List>(lhs);
      if (const auto rhsList = std::get_if<List>(&rhs))
        return IsEqual(Car(lhsList),Car(*rhsList))
            && IsEqual(Cdr(lhsList),Cdr(*rhsList));
      break;
    }
  }
  return false;
}
std::string Print(const List& list)
{
  return IsNull(list) ? "" : Print(Car(list)) + Print(Cdr(list));
}
std::string Print(const Car_t& car)
{
  if (const auto text = std::get_if<std::string_view>(&car))
    return std::string{*text} + " ";

  if (const auto list = std::get_if<List>(&car))
    return "( " + Print(*list) + ") ";

  return "Unknown type?";
}
