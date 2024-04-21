#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <utility>

template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& pair) {
    os << pair.first << " => " << pair.second;
    return os;
}

std::set<std::string> applyReplacements(const std::string& molecule, const std::vector<std::pair<std::string, std::string>>& replacements) {
    std::set<std::string> result;
    for (const auto& replacement : replacements) {
        size_t pos = 0;
        while ((pos = molecule.find(replacement.first, pos)) != std::string::npos) {
            std::string newMolecule = molecule.substr(0, pos) + replacement.second + molecule.substr(pos + replacement.first.size());
            result.insert(newMolecule);
	    std::cerr << "[DEBUG] using replacement rule " << replacement << " to generate: " << newMolecule << std::endl;	   
            pos += replacement.second.size();
        }
    }
    return result;
}

int main() {
    std::vector<std::pair<std::string, std::string>> replacements;
    std::string line;
    while (getline(std::cin, line) && !line.empty()) {
        size_t arrowPos = line.find(" => ");
        replacements.emplace_back(line.substr(0, arrowPos), line.substr(arrowPos + 4));
    }
    std::string medicine;
    while (getline(std::cin, medicine) && !medicine.empty()) {
      std::set<std::string> molecules = applyReplacements(medicine, replacements);
      std::cout << "Distinct molecules: " << molecules.size() << std::endl;
    }
    return 0;
}
