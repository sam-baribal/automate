#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <cstddef>
#include <iosfwd>
#include <iostream>
#include <set>
#include <string>
#include <map>
#include <cassert>


namespace fa {

  constexpr char Epsilon = '\0';  

  class Transition {
    private:
      char alpha;
      int to;
    
    public:
      /**
      * Build a transition between two states with a specific symbol
      */
      Transition(char alpha, int to);
      
      /**
       * Return the symbol of the transition
       */
      char getAlpha() const;

      /**
       * Return the number of the state the transition is aiming at
       */
      int getTo() const;

      /**
       * < operator for the Transition class
       */
      bool operator <(const Transition &other) const;
  };

  class State {
    private:
      std::set<fa::Transition> transitions;
      bool initial = false;
      bool terminal = false;

    public:
      /**
      * Build a new state without any transitions
      */
      State(); 

      /**
      * Add a transition to another state
      */
      bool addTransition(char alpha, int to);

      /**
      * Remove a transition to another state
      */
      bool removeTransition(char alpha, int to);

      /**
      * Tell if a transition exists
      */
      bool hasTransition(char alpha, int to) const;

      /**
       * Tell if there is an epsilon transition coming from this state
       */
      bool hasEpsilonTransition() const;

      /**
       * Tell if the state is initial
       */
      bool isInitial() const;

      /**
       * Tell if the state is final
       */
      bool isFinal() const;

      /**
       * Set the state to initial
       */
      void setInitial(bool initial);

      /**
       * Set the state to final
       */
      void setFinal(bool terminal);

      /**
       * Count the number of transitions coming from this state
       */
      std::size_t countTransitions() const;

      /**
       * Count the number of transitions coming from this state with the symbol alpha
       */
      std::size_t countTransitions(char alpha) const;

      /**
       * Shows the transition of this state in a convivial way
       */
      void printTransitions(std::ostream& os, int state) const;

      /**
       * Returns the set of transitions coming from this state
       */
      std::set<Transition> getTransitions() const;
  };

  class Automaton {
    private:
      std::set<char> alphabet;
      std::map<int, fa::State> states;
    public:
      /**
      * Build an empty automaton (no state, no transition).
      */
      Automaton();

      /**
       * Return a map containing the states of the automaton
       */
      std::map<int, fa::State> getStates() const;

      /**
       * Return a set containing all the symbols of the automaton
       */
      std::set<char> getAlphabet() const;

      /**
      * Tell if an automaton is valid.
      *
      * A valid automaton has a non-empty set of states and a non-empty set of symbols
      */
      bool isValid() const;

      /**
      * Add a symbol to the automaton
      *
      * Epsilon is not a valid symbol.
      * Returns true if the symbol was effectively added
      */
      bool addSymbol(char symbol);

      /**
      * Remove a symbol from the automaton
      *
      * Returns true if the symbol was effectively removed
      */
      bool removeSymbol(char symbol);

      /**
      * Tell if the symbol is present in the automaton
      */
      bool hasSymbol(char symbol) const;

      /**
      * Count the number of symbols
      */
      std::size_t countSymbols() const;

      /**
      * Add a state to the automaton.
      *
      * By default, a newly added state is not initial and not final.
      * Returns true if the state was effectively added and false otherwise.
      */
      bool addState(int state);

      /**
      * Remove a state from the automaton.
      *
      * The transitions involving the state are also removed.
      * Returns true if the state was effectively removed and false otherwise.
      */
      bool removeState(int state);

      /**
      * Tell if the state is present in the automaton.
      */
      bool hasState(int state) const;

      /**
      * Compute the number of states.
      */
      std::size_t countStates() const;

      /**
      * Set the state initial.
      */
      void setStateInitial(int state);

      /**
      * Tell if the state is initial.
      */
      bool isStateInitial(int state) const;

      /**
      * Set the state final.
      */
      void setStateFinal(int state);

      /**
      * Tell if the state is final.
      */
      bool isStateFinal(int state) const;

      /**
      * Add a transition
      *
      * Returns true if the transition was effectively added and false otherwise.
      * If one of the state or the symbol does not exists, the transition is not added.
      */
      bool addTransition(int from, char alpha, int to);

      /**
      * Remove a transition
      *
      * Returns true if the transition was effectively removed and false otherwise.
      */
      bool removeTransition(int from, char alpha, int to);

      /**
      * Tell if a transition is present.
      */
      bool hasTransition(int from, char alpha, int to) const;

      /**
      * Compute the number of transitions.
      */
      std::size_t countTransitions() const;

      /**
      * Print the automaton in a friendly way
      */
      void prettyPrint(std::ostream& os) const;

      /**
      * Print the automaton with respect to the DOT specification
      */
      // void dotPrint(std::ostream& os) const;

      /**
      * Tell if the automaton has one or more epsilon-transition
      */
      bool hasEpsilonTransition() const;

      /**
      * Tell if the automaton is deterministic
      */
      bool isDeterministic() const;

      /**
      * Tell if the automaton is complete
      */
      bool isComplete() const;

      /**
      * Make a transition from a set of states with a character.
      */
      std::set<int> makeTransition(const std::set<int>& origin, char alpha) const;

      /**
      * Read the string and compute the state set after traversing the automaton
      */
      std::set<int> readString(const std::string& word) const;

      /**
      * Tell if the word is in the language accepted by the automaton
      */
      bool match(const std::string& word) const;

      /**
      * Remove non-accessible states
      */
      void removeNonAccessibleStates();

      /**
      * Remove non-co-accessible states
      */
      void removeNonCoAccessibleStates();

      /**
      * Check if the language of the automaton is empty
      */
      bool isLanguageEmpty() const;

      /**
      * Tell if the intersection with another automaton is empty
      */
      bool hasEmptyIntersectionWith(const Automaton& other) const;

      /**
      * Tell if the langage accepted by the automaton is included in the
      * language accepted by the other automaton
      */
      bool isIncludedIn(const Automaton& other) const;

      /**
      * Create a mirror automaton
      */
      static Automaton createMirror(const Automaton& automaton);

      /**
      * Create a complete automaton, if not already complete
      */
      static Automaton createComplete(const Automaton& automaton);

      /**
      * Create a complement automaton
      */
      static Automaton createComplement(const Automaton& automaton);

      /**
      * Create the intersection of the languages of two automata
      */
      static Automaton createIntersection(const Automaton& lhs, const Automaton& rhs);

      /**
      * Create a deterministic automaton, if not already deterministic
      */
      static Automaton createDeterministic(const Automaton& other);

      /**
      * Create an equivalent minimal automaton with the Moore algorithm
      */
      static Automaton createMinimalMoore(const Automaton& other);

      /**
      * Create an equivalent minimal automaton with the Brzozowski algorithm
      */
      static Automaton createMinimalBrzozowski(const Automaton& other);
  };

}

#endif // AUTOMATON_H
