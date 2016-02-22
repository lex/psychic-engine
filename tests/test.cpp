#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JuuhCode
#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include <string>

#include "../src/juuhcode.hpp"
#include "../src/juuhqueue.hpp"

struct cout_redirect {
  cout_redirect(std::streambuf *new_buffer)
      : old(std::cout.rdbuf(new_buffer)) {}

  ~cout_redirect() { std::cout.rdbuf(old); }

private:
  std::streambuf *old;
};

// test for correct code output
BOOST_AUTO_TEST_CASE(TestForCorrectCodeOutput) {
  const std::string s = "fresh";
  auto juuh = JuuhCode(s);
  const std::string expected = "'e': 11"
                               "\n"
                               "'f': 000"
                               "\n"
                               "'h': 01"
                               "\n"
                               "'r': 001"
                               "\n"
                               "'s': 10"
                               "\n";
  boost::test_tools::output_test_stream output;
  {
    cout_redirect guard(output.rdbuf());
    juuh.printCodes();
  }

  BOOST_CHECK(output.is_equal(expected));
}

// test for correct encoded string
BOOST_AUTO_TEST_CASE(TestForCorrectEncodedStringOutput) {
  const std::string s = "freshfreshfresh";
  auto juuh = JuuhCode(s);
  const std::string expected = "000001111001000001111001000001111001\n";

  boost::test_tools::output_test_stream output;
  {
    cout_redirect guard(output.rdbuf());
    juuh.printEncodedString();
  }

  BOOST_CHECK(output.is_equal(expected));
}

// test for correct stats output
BOOST_AUTO_TEST_CASE(TestForCorrectEncodedStatsOutput) {
  const std::string s = "freshfreshfresh";
  auto juuh = JuuhCode(s);
  const std::string expected = "Original size:	15 bytes"
                               "\n"
                               "Encoded size:	4 bytes (26.6667% of original)"
                               "\n";

  boost::test_tools::output_test_stream output;
  {
    cout_redirect guard(output.rdbuf());
    juuh.printStats();
  }

  BOOST_CHECK(output.is_equal(expected));
}

// test that adding something to the priorityqueue increases its size 
BOOST_AUTO_TEST_CASE(TestForCorrectQueuePushing) {
  auto queue = JuuhQueue();
  Node* n = new Node(128, 'a');
  queue.push(n);
  const size_t expectedSize = 1;

  BOOST_CHECK_EQUAL(queue.size(), expectedSize);
}

BOOST_AUTO_TEST_CASE(TestForCorrectQueuePoppingSize) {
  auto queue = JuuhQueue();
  Node* n = new Node(128, 'a');
  queue.push(n);
  const size_t expectedSize = 0;

  Node* r = queue.pop();
  BOOST_CHECK_EQUAL(queue.size(), expectedSize);
}

BOOST_AUTO_TEST_CASE(TestForCorrectQueuePoppingContent) {
  auto queue = JuuhQueue();
  Node* n = new Node(128, 'a');
  queue.push(n);
  Node* r = queue.pop();
  BOOST_CHECK_EQUAL(r, n);
}
