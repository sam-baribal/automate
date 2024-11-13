#include "Automaton.h"


namespace fa {

  Transition::Transition(char newAlpha, int newTo) {
    alpha = newAlpha;
    to = newTo;
  }

  char Transition::getAlpha() const {return alpha;}

  int Transition::getTo() const {return to;}

  bool Transition::operator <(const Transition &other) const {
    if (alpha == other.alpha){
      return (to < other.to);
    }
    return (alpha < other.alpha);
  }

  State::State() {}

  bool State::addTransition(char alpha, int to) {
    return transitions.insert(Transition(alpha, to)).second;
  }

  bool State::removeTransition(char alpha, int to) {
    return transitions.erase(Transition(alpha, to));
  }

  bool State::hasTransition(char alpha, int to) const {
    return (transitions.count(Transition(alpha, to)) == 1);
  }

  bool State::hasEpsilonTransition() const {
    for (std::set<Transition>::const_iterator it = transitions.begin(); it != transitions.end(); it++){
      if (it->getAlpha() == Epsilon){
        return true;
      }
    }
    return false;
  }

  bool State::isInitial() const {return this->initial;}

  bool State::isFinal() const {return this->terminal;}

  void State::setInitial(bool initial) {this->initial = initial;}

  void State::setFinal(bool terminal) {this->terminal = terminal;}

  std::size_t State::countTransitions() const {return transitions.size();}

  std::size_t State::countTransitions(char alpha) const {
    size_t res = 0;
    for (std::set<Transition>::const_iterator it = transitions.begin(); it != transitions.end(); it++){
      if (it->getAlpha() == alpha){
        res++;
      }
    }
    return res;
  }

  void State::printTransitions(std::ostream& os, int state) const {
    os << "\tFor state " << state << ":";
    char currSymbol = '\0';
    char newSymbol;
    for(std::set<Transition>::const_iterator it = transitions.begin(); it != transitions.end(); it++){
      newSymbol = it->getAlpha();
      if (newSymbol != currSymbol){
        currSymbol = newSymbol;
        os << "\n\t\tFor letter " << currSymbol << ":";
      }
      os << " " << it->getTo();
    }
    os << "\n";
  }

  std::set<fa::Transition> State::getTransitions() const {
    return transitions;
  }

  std::set<int> State::getNextStates() const {
    std::set<int> res;
    for (std::set<Transition>::const_iterator it = transitions.begin(); it != transitions.end(); it++){
      res.insert(it->getTo());
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
    if (std::isgraph(symbol) || symbol == Epsilon){
      return alphabet.insert(symbol).second;
    }
    return false;
  }

  bool Automaton::removeSymbol(char symbol) {
    return (alphabet.erase(symbol));
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
    return states.erase(state);
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
    return states.find(state)->second.isInitial();
  }

  void Automaton::setStateFinal(int state) {
    if (hasState(state)){
      states.find(state)->second.setFinal(true);
    }
  }

  bool Automaton::isStateFinal(int state) const {
    return states.find(state)->second.isFinal();
  }

  bool Automaton::addTransition(int from, char alpha, int to) {
    if (hasState(from) && hasState(to) && hasSymbol(alpha) && !(hasTransition(from, alpha, to))){
      return (states.find(from)->second.addTransition(alpha, to));
    }
    return false;
  }

  bool Automaton::removeTransition(int from, char alpha, int to) {
    if (hasState(from) && hasState(to) && hasSymbol(alpha) && (hasTransition(from, alpha, to))){
      return (states.find(from)->second.removeTransition(alpha, to));
    }
    return false;
  }

  bool Automaton::hasTransition(int from, char alpha, int to) const {
    if (hasState(from) && hasState(to) && hasSymbol(alpha)){
      return (states.find(from)->second.hasTransition(alpha, to));
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
      std::set<Transition> transitions = it1->second.getTransitions();
      for(std::set<Transition>::iterator it2 = transitions.begin(); it2 != transitions.end(); it2++){
        newAuto.addTransition(it1->first, it2->getAlpha(), it2->getTo());
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
      std::set<Transition> transitions = it1->second.getTransitions();
      for(std::set<Transition>::iterator it2 = transitions.begin(); it2 != transitions.end(); it2++){
        newAuto.addTransition(it1->first, it2->getAlpha(), it2->getTo());
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
      std::set<Transition> transitions = it1->second.getTransitions();
      for(std::set<Transition>::iterator it2 = transitions.begin(); it2 != transitions.end(); it2++){
        newAuto.addTransition(it2->getTo(), it2->getAlpha(), it1->first);
      }
    }
    return newAuto;
  }

  std::set<int> Automaton::makeTransition(const std::set<int>& origin, char alpha) const {
    std::set<int> res;
    for(std::map<int, State>::const_iterator it1 = states.begin(); it1 != states.end(); it1++){
      if (origin.count(it1->first) == 1){
        std::set<fa::Transition> transitions = getStates().find(it1->first)->second.getTransitions();
        for(std::set<fa::Transition>::const_iterator it2 = transitions.begin(); it2 != transitions.end(); it2++){
          if(it2->getAlpha() == alpha && res.count(it2->getTo()) == 0){
            res.insert(it2->getTo());
          }
        }
      }
    }
    return res;
  }

  std::set<int> Automaton::getInitialStates() const {
    std::set<int> res;
    for (std::map<int, State>::const_iterator it = states.begin(); it != states.end(); it++){
      if (isStateInitial(it->first)){
        res.insert(it->first);
      }
    }
    return res;
  }

  std::set<int> Automaton::getFinalStates() const {
    std::set<int> res;
    for (std::map<int, State>::const_iterator it = states.begin(); it != states.end(); it++){
      if (isStateFinal(it->first)){
        res.insert(it->first);
      }
    }
    return res;
  }

  std::set<int> Automaton::readString(const std::string& word) const {
    std::set<int> from, to;
    from = getInitialStates();
    for (std::string::const_iterator it = word.begin(); it != word.end(); it++){
      to = makeTransition(from, *it);
      from = to;
    }
    return to;
  }

  bool Automaton::match(const std::string& word) const {
    std::set<int> read = readString(word);
    for (std::set<int>::const_iterator it = read.begin(); it != read.end(); it++){
      if (isStateFinal(*it)){
        return true;
      }
    }
    return false;
  }

  void Automaton::removeNonAccessibleStates () {
    fprintf(stderr, "2\n");
    std::set<int> accessibleStates;
    std::set<int> init = getInitialStates();
    fprintf(stderr, "3\n");
    for (std::set<int>::iterator it = init.begin(); it != init.end(); it++){
      removeNonAccessibleStatesRec(*it, accessibleStates);
    }
    fprintf(stderr, "4\n");
    for (std::map<int, State>::iterator it = states.begin(); it != states.end(); it++){
      fprintf(stderr, "FOFOR\n");
      if (init.count(it->first) < 1){
        fprintf(stderr, "AAAA\n");
        states.erase(it->first);
        fprintf(stderr, "BBBB\n");
      }
    }
  }

  void Automaton::removeNonAccessibleStatesRec(int state, std::set<int>& accessibleStates) {
    std::cout << state;
    if (isStateFinal(state)){
      return;
    }
    accessibleStates.insert(state);
    std::set<int> next = getNextStates(state);
    for (std::set<int>::iterator it = next.begin(); it != next.end(); it++){
      if (accessibleStates.count(*it) < 1){
        removeNonAccessibleStatesRec(*it, accessibleStates);
      }
    }
  }

  void Automaton::removeNonCoAccessibleStates() {

  }

  void Automaton::removeNonCoAccessibleStatesRec() {

  }

  bool Automaton::isLanguageEmpty() const {
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
    return states.find(state)->second.getNextStates();
  }

  bool Automaton::hasEmptyIntersectionWith(const Automaton& other) const {
    return false;
  }

  bool Automaton::isIncludedIn(const Automaton& other) const {
    return false;
  }

  Automaton Automaton::createIntersection(const Automaton& lhs, const Automaton& rhs){
    Automaton fa;
    return fa;
  }

  Automaton Automaton::createDeterministic(const Automaton& other){
    Automaton fa;
    return fa;
  }

  Automaton Automaton::createMinimalMoore(const Automaton& other){
    Automaton fa;
    return fa;
  }

  Automaton Automaton::createMinimalBrzozowski(const Automaton& other){
    Automaton fa;
    return fa;
  }
}