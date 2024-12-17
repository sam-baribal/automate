#include "Automaton.h"


namespace fa {

  State::State() {}

  bool State::addTransition(char alpha, int to) {
    if (transitions.count(alpha) == 0){
      std::set<int> destinations;
      transitions.insert({alpha, destinations});
    }
    return transitions[alpha].insert(to).second;
  }

  bool State::removeTransition(char alpha, int to) {
    std::map<char, std::set<int>>::iterator it = transitions.begin();
    while (it != transitions.end()){
      if (it->first == alpha && it->second.count(to) == 1){
        return (it->second.erase(to) > 0);
      }
      it++;
    }
    return true;
  }

  bool State::removeTransitions(char alpha) {
    std::map<char, std::set<int>>::iterator it = transitions.find(alpha);
    if (it != transitions.end()){
      transitions.erase(it);
    }
    return true;
  }

  bool State::removeTransitions(int to) {
    bool res = true;
    std::set<char> alphaSet;
    for (std::map<char, std::set<int>>::iterator it = transitions.begin(); it != transitions.end(); it++){
      if (it->second.count(to) == 1){
        alphaSet.insert(it->first);
      }
    }
    for (std::set<char>::iterator it = alphaSet.begin(); it != alphaSet.end(); it++){
      res = res || (removeTransition(*it, to));
    }
    return res;
  }

  void State::removeAllTransitions() {
    transitions.clear();
  }

  bool State::hasTransition(char alpha, int to) const {
    for (std::map<char, std::set<int>>::const_iterator it = transitions.begin(); it != transitions.end(); it++){
      if (it->first == alpha && it->second.count(to) == 1){
        return true;
      }
    }
    return false;
  }

  bool State::hasEpsilonTransition() const {
    for (std::map<char, std::set<int>>::const_iterator it = transitions.begin(); it != transitions.end(); it++){
      if (it->first == Epsilon){
        return true;
      }
    }
    return false;
  }

  bool State::isInitial() const {return this->initial;}

  bool State::isFinal() const {return this->terminal;}

  void State::setInitial(bool initial) {this->initial = initial;}

  void State::setFinal(bool terminal) {this->terminal = terminal;}

  std::size_t State::countTransitions() const {
    size_t res = 0;
    for (std::map<char, std::set<int>>::const_iterator it = transitions.begin(); it != transitions.end(); it++){
      res = res + it->second.size();
    }
    return res;
  }

  std::size_t State::countTransitions(char alpha) const {
    size_t res = 0;
    for (std::map<char, std::set<int>>::const_iterator it = transitions.begin(); it != transitions.end(); it++){
      if (it->first == alpha){
        res = res + it->second.size();
      }
    }
    return res;
  }

  void State::printTransitions(std::ostream& os, int state) const {
    os << "\tFor state " << state << ":";
    char currSymbol = '\0';
    char newSymbol;
    for(std::map<char, std::set<int>>::const_iterator it = transitions.begin(); it != transitions.end(); it++){
      newSymbol = it->first;
      if (newSymbol != currSymbol){
        currSymbol = newSymbol;
        os << "\n\t\tFor letter " << currSymbol << ":";
      }
      for (std::set<int>::const_iterator it2 = it->second.begin(); it2 != it->second.end(); it2++){
        os << " " << *it2;
      }
    }
    os << "\n";
  }

  std::map<char, std::set<int>> State::getTransitions() const {
    return transitions;
  }

  std::set<int> State::getNextStates() const {
    std::set<int> res;
    for (std::map<char, std::set<int>>::const_iterator it = transitions.begin(); it != transitions.end(); it++){
      for (std::set<int>::const_iterator it2 = it->second.begin(); it2 != it->second.end(); it2++){
        res.insert(*it2);
      }
    }
    return res;
  }

  Automaton::Automaton() {}

  std::map<int, fa::State> Automaton::getStates() const {
    return states;
  }

  std::set<char> Automaton::getAlphabet() const {
    return alphabet;
  }

  bool Automaton::isValid() const {
    return !(alphabet.empty() || states.empty()) ;
  }

  bool Automaton::addSymbol(char symbol) {
    if (std::isgraph(symbol)){
      return alphabet.insert(symbol).second;
    }
    return false;
  }

  bool Automaton::removeSymbol(char symbol) {
    bool res = true;
    if (!(hasSymbol(symbol) && getStates().empty())){
      std::set<int> temp;
      std::map<int, State> tempStates = getStates();
      for (std::map<int,State>::iterator it = tempStates.begin(); it != tempStates.end(); it++){
        temp.insert(it->first);
      }
      for (std::set<int>::iterator it = temp.begin(); it != temp.end(); it++){
        res = (removeTransitions(*it, symbol)) && res;
      }
    }
    return alphabet.erase(symbol) && res;
  }

  bool Automaton::hasSymbol(char symbol) const {
    return alphabet.count(symbol) == 1;
  }

  std::size_t Automaton::countSymbols() const {
    return alphabet.size();
  }

  bool Automaton::addState(int state) {
    if (state >= 0 && states.count(state) == 0){
      return states.insert(std::pair{state, fa::State()}).second;
    }
    return false;
  }

  bool Automaton::removeState(int state) {
    if (hasState(state)){
      bool res = removeTransitions(state);
      return states.erase(state) && res;
    }
    return false;
  }

  bool Automaton::hasState(int state) const {
    return (states.count(state) == 1);
  }

  std::size_t Automaton::countStates() const {
    return states.size();
  }
  
  void Automaton::setStateInitial(int state) {
    if (hasState(state)){
      states.find(state)->second.setInitial(true);
    }
  }

  bool Automaton::isStateInitial(int state) const {
    if (hasState(state)){
      return states.find(state)->second.isInitial();
    }
    return false;
  }

  void Automaton::setStateFinal(int state) {
    if (hasState(state)){
      states.find(state)->second.setFinal(true);
    }
  }

  bool Automaton::isStateFinal(int state) const {
    if (hasState(state)){
      return states.find(state)->second.isFinal();
    }
    return false;
  }

  bool Automaton::addTransition(int from, char alpha, int to) {
    if (hasState(from) && hasState(to) && (hasSymbol(alpha) || alpha == Epsilon)){
      if (!(hasTransition(from, alpha, to))){
        return (states.find(from)->second.addTransition(alpha, to));
      }
    }
    return false;
  }

  bool Automaton::removeTransition(int from, char alpha, int to) {
    return (hasState(from) && hasSymbol(alpha) && hasState(to) && (states.find(from)->second.removeTransition(alpha, to)));
  }

  bool Automaton::removeTransitions(int from, char alpha) {
    return (!(hasSymbol(alpha) && hasState(from)) || states.find(from)->second.removeTransitions(alpha));
  }

  bool Automaton::removeTransitions(int to) {
    bool res = true;
    std::set<int> temp;
    std::map<int, State> tempStates = getStates();
    for (std::map<int, State>::iterator it = tempStates.begin(); it != tempStates.end(); it++){
      temp.insert(it->first);
    }
    for (std::set<int>::iterator it = temp.begin(); it != temp.end(); it++){
      for (std::set<char>::iterator it2 = alphabet.begin(); it2 != alphabet.end(); it2++) {
        if (hasTransition(*it, *it2, to)){
          res = removeTransition(*it, *it2, to) && res;
        }
      }
    }
    return res;
  }

  bool Automaton::hasTransition(int from, char alpha, int to) const {
    std::map<int, State>::const_iterator fromState = states.find(from);
    if (fromState != states.end()){
      return (fromState->second.hasTransition(alpha, to));
    }
    return false;
  }

  std::size_t Automaton::countTransitions() const {
    size_t res = 0;
    for(std::map<int, State>::const_iterator it = states.begin(); it != states.end(); it++){
      res += it->second.countTransitions();
    }
    return res;
  }

  void Automaton::prettyPrint(std::ostream& os) const {
    os << "Initial states:\n\t";
    for(std::map<int, State>::const_iterator it = states.begin(); it != states.end(); it++){
      if(it->second.isInitial()){
        os << it->first << " ";
      }
    }
    os << "\nFinal states:\n\t";
    for(std::map<int, State>::const_iterator it = states.begin(); it != states.end(); it++){
      if(it->second.isFinal()){
        os << it->first << " ";
      }
    }
    os << "\nTransitions:\n";
    for(std::map<int, State>::const_iterator it = states.begin(); it != states.end(); it++){
      it->second.printTransitions(os, it->first);
    }
  }

  bool Automaton::hasEpsilonTransition() const {
    assert(isValid());
    for(std::map<int, State>::const_iterator it = states.begin(); it != states.end(); it++){
      if (it->second.hasEpsilonTransition()){
        return true;
      }
    }
    return false;
  } 

  bool Automaton::isDeterministic() const {
    assert(isValid());
    for(std::map<int, State>::const_iterator it1 = states.begin(); it1 != states.end(); it1++){
      for(std::set<char>::const_iterator it2 = alphabet.begin(); it2 != alphabet.end(); it2++){
        if (it1->second.countTransitions(*it2) > 1){
          return false;
        }
      }
    }
    return true;
  }

  bool Automaton::isComplete() const {
    assert(isValid());
    for(std::map<int, State>::const_iterator it1 = states.begin(); it1 != states.end(); it1++){
      for(std::set<char>::const_iterator it2 = alphabet.begin(); it2 != alphabet.end(); it2++){
        if (it1->second.countTransitions(*it2) < 1){
          return false;
        }
      }
    }
    return true;
  }

  Automaton Automaton::createComplete(const Automaton& automaton) {
    assert(automaton.isValid());
    if (automaton.isComplete()){
      return automaton;
    }
    Automaton newAuto;
    int currMax = 0;
    newAuto.alphabet = automaton.alphabet;
    std::map<int, State> states = automaton.getStates();
    for(std::map<int, State>::iterator it = states.begin(); it != states.end(); it++){
      if (it->first > currMax){
        currMax = it->first;
      }
      newAuto.addState(it->first);
      if (automaton.isStateFinal(it->first)){
        newAuto.setStateFinal(it->first);
      }
      if (automaton.isStateInitial(it->first)){
        newAuto.setStateInitial(it->first);
      }
    }
    int trashState = currMax+1;
    newAuto.addState(trashState);
    for(std::map<int, State>::iterator it1 = states.begin(); it1 != states.end(); it1++){
      std::map<char, std::set<int>> transitions = it1->second.getTransitions();
      for(std::map<char, std::set<int>>::iterator it2 = transitions.begin(); it2 != transitions.end(); it2++){
        for (std::set<int>::iterator it3 = it2->second.begin(); it3 != it2->second.end(); it3++){
          newAuto.addTransition(it1->first, it2->first, *it3);
        }
      }
    }
    std::set<char> alphabet = newAuto.getAlphabet();
    std::map<int, State> newStates = newAuto.getStates();
    for(std::map<int, State>::iterator it1 = newStates.begin(); it1 != newStates.end(); it1++){
      for(std::set<char>::iterator it2 = alphabet.begin(); it2 != alphabet.end(); it2++){
        State currState = newStates.find(it1->first)->second;
        if (currState.countTransitions(*it2) < 1){
          newAuto.addTransition(it1->first, *it2, trashState);
        }
      }
    }
    return newAuto;
  }

  Automaton Automaton::createComplement(const Automaton& automaton) {
    assert(automaton.isValid());
    Automaton currAuto = automaton;
    if (!automaton.isComplete()){
      currAuto = createComplete(automaton);
    }
    if (!currAuto.isDeterministic()){
      //currAuto = createDeterministic(currAuto);
      std::cout << "!!!  !!!  TO DO  !!!  !!!\n\tin createComplement --> createDeterministic\n";
    }
    Automaton newAuto;
    newAuto.alphabet = currAuto.alphabet;
    std::map<int,State> states = currAuto.getStates();
    for(std::map<int, State>::iterator it = states.begin(); it != states.end(); it++){
      newAuto.addState(it->first);
      if (!currAuto.isStateFinal(it->first)){
        newAuto.setStateFinal(it->first);
      }
      if (currAuto.isStateInitial(it->first)){
        newAuto.setStateInitial(it->first);
      }
    }
    for(std::map<int, State>::iterator it1 = states.begin(); it1 != states.end(); it1++){
      std::map<char, std::set<int>> transitions = it1->second.getTransitions();
      for(std::map<char, std::set<int>>::iterator it2 = transitions.begin(); it2 != transitions.end(); it2++){
        for (std::set<int>::iterator it3 = it2->second.begin(); it3 != it2->second.end(); it3++){
          newAuto.addTransition(it1->first, it2->first, *it3);
        }
      }
    }
    return newAuto;
  }

  Automaton Automaton::createMirror(const Automaton& automaton) {
    assert(automaton.isValid());
    Automaton newAuto;
    newAuto.alphabet = automaton.alphabet;
    std::map<int,State> states = automaton.getStates();
    for(std::map<int, State>::iterator it = states.begin(); it != states.end(); it++){
      newAuto.addState(it->first);
      if (automaton.isStateFinal(it->first)){
        newAuto.setStateInitial(it->first);
      }
      if (automaton.isStateInitial(it->first)){
        newAuto.setStateFinal(it->first);
      }
    }
    for(std::map<int, State>::iterator it1 = states.begin(); it1 != states.end(); it1++){
      std::map<char, std::set<int>> transitions = it1->second.getTransitions();
      for(std::map<char, std::set<int>>::iterator it2 = transitions.begin(); it2 != transitions.end(); it2++){
        for (std::set<int>::iterator it3 = it2->second.begin(); it3 != it2->second.end(); it3++){
          newAuto.addTransition(*it3, it2->first, it1->first);
        }
      }
    }
    return newAuto;
  }

  std::set<int> Automaton::makeTransition(const std::set<int>& origin, char alpha) const {
    std::set<int> res;
    for(std::map<int, State>::const_iterator it1 = states.begin(); it1 != states.end(); it1++){
      if (origin.count(it1->first) == 1){
        std::map<char, std::set<int>> transitions = getStates().find(it1->first)->second.getTransitions();
        for(std::map<char, std::set<int>>::const_iterator it2 = transitions.begin(); it2 != transitions.end(); it2++){
          for (std::set<int>::iterator it3 = it2->second.begin(); it3 != it2->second.end(); it3++){
            if(it2->first == alpha && res.count(*it3) == 0){
              res.insert(*it3);
            }
          }
        }
      }
    }
    return res;
  }

  std::set<int> Automaton::getInitialStates() const {
    assert(isValid());
    std::set<int> res;
    for (std::map<int, State>::const_iterator it = states.begin(); it != states.end(); it++){
      if (isStateInitial(it->first)){
        res.insert(it->first);
      }
    }
    return res;
  }

  std::set<int> Automaton::getFinalStates() const {
    assert(isValid());
    std::set<int> res;
    for (std::map<int, State>::const_iterator it = states.begin(); it != states.end(); it++){
      if (isStateFinal(it->first)){
        res.insert(it->first);
      }
    }
    return res;
  }

  std::set<int> Automaton::readString(const std::string& word) const {
    assert(isValid());
    std::set<int> from, to;
    from = getInitialStates();
    if (word.size() == 0){
      for (std::set<int>::const_iterator it = from.begin(); it != from.end(); it++){
        if (isStateFinal(*it)){
          to.insert(*it);
        }
      }
    }
    for (std::string::const_iterator it = word.begin(); it != word.end(); it++){
      to = makeTransition(from, *it);
      from = to;
    }
    return to;
  }

  bool Automaton::match(const std::string& word) const {
    assert(isValid());
    std::set<int> read = readString(word);
    for (std::set<int>::const_iterator it = read.begin(); it != read.end(); it++){
      if (isStateFinal(*it)){
        return true;
      }
    }
    return false;
  }

  void Automaton::removeNonAccessibleStates () {
    assert(isValid());
    if (getInitialStates().size() == 0){
      addState(0);
      setStateInitial(0);
    }
    std::set<int> accessibleStates;
    std::set<int> init = getInitialStates();
    std::map<int, State> statesTemp = states;
    for (std::set<int>::iterator it = init.begin(); it != init.end(); it++){
      removeNonAccessibleStatesRec(*it, accessibleStates);
    }
    for (std::map<int, State>::iterator it = statesTemp.begin(); it != statesTemp.end(); it++){
      if (accessibleStates.count(it->first) < 1 && hasState(it->first)){
        removeState(it->first);
      }
    }
  }

  void Automaton::removeNonAccessibleStatesRec(int state, std::set<int>& accessibleStates) {
    accessibleStates.insert(state);
    if (isStateFinal(state)){
      return;
    }
    std::set<int> next = getNextStates(state);
    for (std::set<int>::iterator it = next.begin(); it != next.end(); it++){
      if (accessibleStates.count(*it) < 1){
        removeNonAccessibleStatesRec(*it, accessibleStates);
      }
    }
  }

  std::set<int> Automaton::getPreviousStates(int state) const {
    std::set<int> res;
    for (std::map<int, State>::const_iterator it1 = states.begin(); it1 != states.end(); it1++){
      for (std::set<char>::const_iterator it2 = alphabet.begin(); it2 != alphabet.end(); it2++){
        if (hasTransition(it1->first, *it2, state)){
          res.insert(it1->first);
        }
      }
    }
    return res;
  }

  void Automaton::removeNonCoAccessibleStates() {
    assert(isValid());
    if (getFinalStates().size() == 0){
      addState(0);
      setStateFinal(0);
    }
    std::set<int> coAccessibleStates;
    std::set<int> fin = getFinalStates();
    std::map<int, State> statesTemp = states;
    for (std::set<int>::iterator it = fin.begin(); it != fin.end(); it++){
      removeNonCoAccessibleStatesRec(*it, coAccessibleStates);
    }
    for (std::map<int, State>::iterator it = statesTemp.begin(); it != statesTemp.end(); it++){
      if (coAccessibleStates.count(it->first) < 1 && hasState(it->first)){
        removeState(it->first);
      }
    }
  }

  void Automaton::removeNonCoAccessibleStatesRec(int state, std::set<int>& coAccessibleStates) {
    coAccessibleStates.insert(state);
    if (isStateInitial(state)){
      return;
    }
    std::set<int> prev = getPreviousStates(state);
    for (std::set<int>::iterator it = prev.begin(); it != prev.end(); it++){
      if (coAccessibleStates.count(*it) < 1){
        removeNonCoAccessibleStatesRec(*it, coAccessibleStates);
      }
    }
  }

  bool Automaton::isLanguageEmpty() const {
    assert(isValid());
    std::set<int> visitedStates;
    std::set<int> init = getInitialStates();
    for (std::set<int>::const_iterator it = init.begin(); it != init.end(); it++){
      if (!isLanguageEmptyRec(*it, visitedStates)){
        return false;
      }
    }
    return true;
  }

  bool Automaton::isLanguageEmptyRec (int state, std::set<int>& visitedStates) const {
    assert(isValid());
    if (isStateFinal(state)){
      return false;
    }
    visitedStates.insert(state);
    std::set<int> next = getNextStates(state);
    for (std::set<int>::const_iterator it = next.begin(); it != next.end(); it++){
      if (visitedStates.count(*it) < 1 && !isLanguageEmptyRec(*it, visitedStates)){
        return false;
      }
    }
    return true;
  }

  std::set<int> Automaton::getNextStates(int state) const {
    assert(isValid());
    return states.find(state)->second.getNextStates();
  }

  bool Automaton::hasEmptyIntersectionWith(const Automaton& other) const {
    assert(isValid());
    assert(other.isValid());
    return false;
  }

  bool Automaton::isIncludedIn(const Automaton& other) const {
    assert(isValid());
    assert(other.isValid());
    return false;
  }

  Automaton Automaton::createIntersection(const Automaton& lhs, const Automaton& rhs){
    assert(lhs.isValid());
    assert(rhs.isValid());
    Automaton fa;
    fa.addState(1);
    fa.addSymbol('a');
    return fa;
  }

  Automaton Automaton::createDeterministic(const Automaton& other){
    assert(other.isValid());
    Automaton fa;
    fa.addState(1);
    fa.addSymbol('a');
    return fa;
  }

  Automaton Automaton::createMinimalMoore(const Automaton& other){
    assert(other.isValid());
    Automaton fa;
    fa.addState(1);
    fa.addSymbol('a');
    return fa;
  }

  Automaton Automaton::createMinimalBrzozowski(const Automaton& other){
    assert(other.isValid());
    Automaton fa;
    fa.addState(1);
    fa.addSymbol('a');
    return fa;
  }
}