#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JuuhCode
#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include <string>

#include "../src/juuhcode.hpp"

struct cout_redirect {
  cout_redirect(std::streambuf *new_buffer)
      : old(std::cout.rdbuf(new_buffer)) {}

  ~cout_redirect() { std::cout.rdbuf(old); }

private:
  std::streambuf *old;
};

// test for correct print output
BOOST_AUTO_TEST_CASE(TestForCorrectOutput) {
  const std::string s = "fresh";
  auto juuh = JuuhCode(s);
  const std::string expected = "'e': 001\n"
                               "'f': 000\n"
                               "'h': 01\n"
                               "'r': 11\n"
                               "'s': 10\n";

  boost::test_tools::output_test_stream output;
  {
    cout_redirect guard(output.rdbuf());
    juuh.print();
  }

  BOOST_CHECK(output.is_equal(expected));
}
