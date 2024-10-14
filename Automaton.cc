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

  bool State::isInitial() const {return this->initial;}

  bool State::isFinal() const {return this->terminal;}

  void State::setInitial(bool initial) {this->initial = initial;}

  void State::setFinal(bool terminal) {this->terminal = terminal;}

  std::size_t State::countTransitions() const {return transitions.size();}

  void State::printTransitions(std::ostream& os, int state) const {
    os << "\tFor state " << state << ":";
    char currSymbol = '\0';
    char newSymbol;
    for(std::set<Transition>::const_iterator it = transitions.begin();it != transitions.end(); it++){
      newSymbol = it->getAlpha();
      if (newSymbol != currSymbol){
        currSymbol = newSymbol;
        os << "\n\t\tFor letter " << currSymbol << ":";
      }
      os << " " << it->getTo();
    }
    os << "\n";
  }

  Automaton::Automaton() {}

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
}

