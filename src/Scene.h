#include <functional>
#include <map>
#include <string>
#include <vector>
class Scene {
   private:
    std::vector<std::pair<std::string, std::function<void(void)> > > menus;

   public:
    Scene() = default;
    Scene(std::vector<std::pair<std::string, std::function<void(void)> > >);
    void show();
};

// a vector contains '1'-'9', 'a'-'z', 'A'-'Z'
const std::vector<std::string> ALPHABET = {
    "1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b", "c", "d",
    "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q",
    "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D",
    "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q",
    "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
// a map convert ALPHABET to index
const std::map<std::string, int> ALPHABET_MAP = {
    {"1", 0},  {"2", 1},  {"3", 2},  {"4", 3},  {"5", 4},  {"6", 5},  {"7", 6},
    {"8", 7},  {"9", 8},  {"a", 9},  {"b", 10}, {"c", 11}, {"d", 12}, {"e", 13},
    {"f", 14}, {"g", 15}, {"h", 16}, {"i", 17}, {"j", 18}, {"k", 19}, {"l", 20},
    {"m", 21}, {"n", 22}, {"o", 23}, {"p", 24}, {"q", 25}, {"r", 26}, {"s", 27},
    {"t", 28}, {"u", 29}, {"v", 30}, {"w", 31}, {"x", 32}, {"y", 33}, {"z", 34},
    {"A", 35}, {"B", 36}, {"C", 37}, {"D", 38}, {"E", 39}, {"F", 40}, {"G", 41},
    {"H", 42}, {"I", 43}, {"J", 44}, {"K", 45}, {"L", 46}, {"M", 47}, {"N", 48},
    {"O", 49}, {"P", 50}, {"Q", 51}, {"R", 52}, {"S", 53}, {"T", 54}, {"U", 55},
    {"V", 56}, {"W", 57}, {"X", 58}, {"Y", 59}, {"Z", 60}};
