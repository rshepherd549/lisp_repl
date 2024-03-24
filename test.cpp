#include <iostream>

#include <list.h>
#include <lisp_repl.h>

std::string testCreateList()
{
  List list0;

  if (!IsEmptyList(list0))
    return "testCreateList: IsNull(list0)";

  const auto list1 = Cons("test", list0);

  if (IsEmptyList(list1))
    return "testCreateList: IsNull(list1)";

  const auto actual = to_string(list1);
  const auto expected = "( test ) ";

  if (actual != expected)
    return "testCreateList, Print: actual:" + actual + " != expected:" + expected + "\n";

  const auto list2 = Cons("test", list0);
  if (!IsEqual(list1, list2))
    return "testCreateList, IsEqual: list1:" + to_string(list1) + " != list2:" + to_string(list2) + "\n";

  if (IsEqual(list1, list0))
    return "testCreateList, !IsEqual: list1:" + to_string(list1) + " == list0:" + to_string(list0) + "\n";

  return "";
}

std::string testFind()
{
  const auto list1 = Cons("a", EmptyList);
  const auto list2 = Cons("b", list1);
  const auto list3 = Cons("c", list2);

  struct
  {
    long line;
    std::string msg;
    List expression;
    List expected;
  } tests[]
  {
    {__LINE__, "find c", FindKey(list3, "c"), list3},
    {__LINE__, "find a", FindKey(list3, "a"), list1},
    {__LINE__, "find z", FindKey(list3, "z"), EmptyList},
  };

  for (const auto& test: tests)
  {
    if (!IsEqual(test.expression, test.expected))
      return "testFind: " + std::to_string(test.line) + " " + test.msg + " "
           + "actual:" + to_string(test.expression) + " "
           + "expected:" + to_string(test.expected) + " "
           + "\n";
  }


  return "";
}

std::string testMakeList()
{
  auto list0 = MakeList();
  auto list1 = MakeList("a");
  auto list2 = MakeList("a", "b");
  auto list2_0 = MakeList("a", MakeList());
  auto list3_2 = MakeList("a", MakeList("b"), "c");

  return "";
}

std::string testRepl()
{
  struct
  {
    long line;
    std::string msg;
    std::string in;
    std::string expected;
  } tests[] =
  {
    {__LINE__,"empty","",""},
  };

  const auto& context = InitialContext();

  std::string err;

  for (const auto& test: tests)
  {
    const auto& sexpRead = Read(test.in);
    const auto& sexpEval = Eval(sexpRead, context);
    const auto& actual = to_string(sexpEval);
    if (actual != test.expected)
      err += "testRepl: line:" + std::to_string(test.line) + " " + test.msg
           + " actual:" + actual
           + " != expected:" + test.expected + "\n";
  }

  return err;
}

int main()
{
  std::cout << "lisp_repl\n";

  std::cout << testCreateList();
  std::cout << testFind();
  std::cout << testMakeList();
//  std::cout << testRepl();

  return 0;
}
