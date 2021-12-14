#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>

struct BitFrequency {
  char _mostFrequentBit;
  char _leastFrequentBit;
};

auto findGammaRating(const std::vector<BitFrequency>& bitCounts) -> std::string
{
  auto gammaRating = std::string{""};
  auto concactFunc = [&](const BitFrequency& bf)
  {
    return gammaRating += bf._mostFrequentBit; 
  };
  std::for_each(std::begin(bitCounts), std::end(bitCounts), concactFunc);
  return gammaRating;
}

auto findEpsilonRating(const std::vector<BitFrequency>& bitCounts) -> std::string
{
   auto epsilonRating = std::string{""};
   auto concactFunc = [&](const BitFrequency& bf)
   {
     return epsilonRating += bf._leastFrequentBit; 
   };
   std::for_each(std::begin(bitCounts), std::end(bitCounts), concactFunc);
   return epsilonRating;
}

auto countColBitFrequencies(const std::vector<std::string>& binaryLines) -> std::vector<BitFrequency>
{
  auto colIdx = std::size_t{0};
  std::vector<BitFrequency> bitFrequencies(binaryLines[colIdx].size(), BitFrequency{});
  while (colIdx < binaryLines[colIdx].size())
  {
    auto rowIdx = std::size_t{0};
    auto bitCounts = std::unordered_map<char, std::uint32_t>{};
    while (rowIdx < binaryLines.size())
    {
      auto bitChar = binaryLines[rowIdx][colIdx];
      ++bitCounts[bitChar];
      ++rowIdx;
    }
    auto mostFrequentBit = char{(bitCounts['0'] > bitCounts['1'] ? '0' : '1')};
    auto leastFrequentBit = char{(mostFrequentBit == '1' ? '0' : '1')};
    bitFrequencies[colIdx] = std::move(BitFrequency{std::move(mostFrequentBit), std::move(leastFrequentBit)});
    ++colIdx;
  }
  return bitFrequencies; 
}
auto solvePuzzle(const std::string& inputFileName) -> void
{
  auto ifs = std::ifstream{inputFileName};
  if (!ifs.is_open())
  {
    std::cerr << "ERROR::solvePuzzle(cons std::string&)::FAILED_TO_OPEN_FILE: {" << "}" << std::endl;
    return;
  }
  auto binaryLines = std::vector<std::string>{};
  auto line = std::string{""};
  while (std::getline(ifs, line))
  {
    binaryLines.push_back(line);
  }
  std::cout << "---part 1---" << std::endl; 
  auto colBitCounts = countColBitFrequencies(binaryLines);
  auto gammaRating = findGammaRating(colBitCounts);
  std::cout << "gamma rating: " << gammaRating << std::endl;
  auto epsilonRating = findEpsilonRating(colBitCounts);
  std::cout << "epsilon rating: " << epsilonRating << std::endl;
}

auto main(void) -> int
{
  solvePuzzle("example-input.txt");
  return 0;
}
