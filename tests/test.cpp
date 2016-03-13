#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JuuhCode
#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include <string>
#include <fstream>

#include "../src/juuhcode.hpp"
#include "../src/juuhqueue.hpp"

// test that adding something to the priorityqueue increases its size
BOOST_AUTO_TEST_CASE(TestForCorrectQueuePushing) {
  JuuhQueue queue;
  const size_t expectedSize = 1;

  Node *n = new Node(128, 'a');
  queue.push(n);

  BOOST_CHECK_EQUAL(queue.size(), expectedSize);
}

BOOST_AUTO_TEST_CASE(TestForCorrectQueuePoppingSize) {
  JuuhQueue queue;
  const size_t expectedSize = 0;

  Node *n = new Node(128, 'a');
  queue.push(n);


  Node *r = queue.pop();

  BOOST_CHECK_EQUAL(queue.size(), expectedSize);
}

BOOST_AUTO_TEST_CASE(TestForCorrectQueuePoppingContent) {
  JuuhQueue queue;

  Node *n = new Node(128, 'a');
  queue.push(n);
  Node *r = queue.pop();

  BOOST_CHECK_EQUAL(r, n);
}

BOOST_AUTO_TEST_CASE(TestForCorrectQueuePoppingContentAfterInserts) {
  JuuhQueue queue;

  Node *n = new Node(128, 'a');
  Node *nn = new Node(129, 'b');

  queue.push(n);
  queue.push(nn);

  Node *r = queue.pop();

  BOOST_CHECK_EQUAL(r, n);
}

BOOST_AUTO_TEST_CASE(TestForCorrectStringEncodingAndDecoding) {
  const std::string inputFile = "fresh.txt";
  const std::string outputFile = "encodedfresh";
  const std::string decodedFile = "decoded.txt";
  const std::string expected = "fresh beer enjoyment";

  JuuhCode j = JuuhCode();
  j.encodeFile(inputFile, outputFile);
  j.decodeFile(outputFile, decodedFile);
  std::ifstream f(decodedFile);
  std::string line;
  std::getline(f, line);

  BOOST_CHECK_EQUAL(line, expected);
}


BOOST_AUTO_TEST_CASE(TestForCorrectStringEncodingAndDecodingWithEmojis) {
  const std::string inputFile = "emoji.txt";
  const std::string outputFile = "encodedemoji";
  const std::string decodedFile = "decodedemoji.txt";
  const std::string expected = "fresh beer enjoyment 🍺🍺🍺";

  JuuhCode j = JuuhCode();
  j.encodeFile(inputFile, outputFile);
  j.decodeFile(outputFile, decodedFile);
  std::ifstream f(decodedFile);
  std::string line;
  std::getline(f, line);

  BOOST_CHECK_EQUAL(line, expected);
}
