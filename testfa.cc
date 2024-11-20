
#include "gtest/gtest.h"

#include "Automaton.h"

#define WORD1 "aabbabb"
#define WORD2 "baaaaab"
#define WORD3 "aaabaaa"
#define WORD4 "aaaaaaa"

// exemple d'automate du sujet
// non déterministe et non complet
fa::Automaton initalAutomaton () {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  fa.setStateInitial(0);
  fa.setStateInitial(1);
  fa.setStateFinal(1);
  fa.setStateFinal(4);
  fa.addTransition(0, 'a', 1);
  fa.addTransition(0, 'a', 2);
  fa.addTransition(0, 'a', 3);
  fa.addTransition(1, 'b', 3);
  fa.addTransition(2, 'a', 3);
  fa.addTransition(2, 'b', 4);
  fa.addTransition(3, 'a', 3);
  fa.addTransition(3, 'b', 4);
  fa.addTransition(4, 'a', 4);
  return fa;
}

// exemple du cours slide 104
// déterministe et complet
fa::Automaton deterministicCompleteAutomaton1 () {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(0);
  fa.addState(1);
  fa.setStateInitial(0);
  fa.setStateFinal(1);
  fa.addTransition(0, 'a', 0);
  fa.addTransition(0, 'b', 1);
  fa.addTransition(1, 'a', 1);
  fa.addTransition(1, 'b', 0);
  return fa;
} 

// exemple du cours slide 108
// déterministe et complet
fa::Automaton deterministicCompleteAutomaton2 () {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.setStateInitial(0);
  fa.setStateFinal(3);
  fa.addTransition(0, 'a', 4);
  fa.addTransition(0, 'b', 1);
  fa.addTransition(1, 'a', 2);
  fa.addTransition(1, 'b', 4);
  fa.addTransition(2, 'a', 2);
  fa.addTransition(2, 'b', 3);
  fa.addTransition(3, 'a', 4);
  fa.addTransition(3, 'b', 4);
  fa.addTransition(4, 'a', 4);
  fa.addTransition(4, 'b', 4);
  return fa;
}

// exemple du cours slide 105
// déterministe et non complet
fa::Automaton deterministicAutomaton1 () {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(0);
  fa.setStateFinal(3);
  fa.addTransition(0, 'b', 1);
  fa.addTransition(1, 'a', 2);
  fa.addTransition(2, 'a', 2);
  fa.addTransition(2, 'b', 3);
  return fa;
}

// adaptation de l'exemple du cours slide 113 pour le rendre complet
// non déterministe et complet
fa::Automaton completeAutomaton1 () {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(0);
  fa.setStateFinal(3);
  fa.addTransition(0, 'a', 0);
  fa.addTransition(0, 'a', 2);
  fa.addTransition(0, 'b', 0);
  fa.addTransition(0, 'b', 1);
  fa.addTransition(1, 'b', 3);
  fa.addTransition(2, 'a', 3);
  fa.addTransition(3, 'a', 3);
  fa.addTransition(3, 'b', 3);
  fa.addTransition(1, 'a', 2); // transition ajoutée pour rendre l'automate complet
  fa.addTransition(2, 'b', 3); // idem
  return fa;
}

/**
 * Automaton
 */

TEST(AutomatonExampleTest, Default) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.isValid());
}

/**
 * bool Automaton::isValid() const
 */

TEST(AutomatonIsValidTest, EmptyAutomaton) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.isValid());
}

TEST(AutomatonIsValidTest, EmptyStates) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('c'));
  EXPECT_FALSE(fa.isValid());
}

TEST(AutomatonIsValidTest, EmptyAlphabet) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(0));
  EXPECT_FALSE(fa.isValid());
}

TEST(AutomatonIsValidTest, VaildAutomaton) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('c'));
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.isValid());
}

/**
 * bool Automaton::AddSymbol(char symbol)
 */

TEST(AutomatonAddSymbolTest, Valid){
  fa::Automaton fa;
  for (int i = 0; i<128; i++){
    char c = i;
    if (std::isgraph(c)){
      EXPECT_TRUE(fa.addSymbol(c));
    }
  }
}

TEST(AutomatonAddSymbolTest, Existing){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('c'));
  EXPECT_FALSE(fa.addSymbol('c'));
}

TEST(AutomatonAddSymbolTest, Invalid){
  fa::Automaton fa;
  for (int i = 0; i<128; i++){
    char c = i;
    if (!(std::isgraph(c))){
      EXPECT_FALSE(fa.addSymbol(c));
    }
  }
}

TEST(AutomatonAddSymbolTest, Epsilon){
  fa::Automaton fa;
  EXPECT_FALSE(fa.addSymbol(fa::Epsilon));
}

/**
 * bool Automaton::RemoveSymbol(char symbol)
 */

TEST(AutomatonRemoveSymbolTest, Present){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('c'));
  EXPECT_TRUE(fa.removeSymbol('c'));
}

TEST(AutomatonRemoveSymbolTest, Absent){
  fa::Automaton fa;
  EXPECT_FALSE(fa.removeSymbol('c'));
}

TEST(AutomatonRemoveSymbolTest, Invalid){
  fa::Automaton fa;
  EXPECT_FALSE(fa.removeSymbol('\t'));
  EXPECT_TRUE(fa.addSymbol('c'));
  EXPECT_FALSE(fa.removeSymbol('\t'));
}

TEST(AutomatonRemoveSymbolTest, AlreadyRemoved){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('c'));
  EXPECT_TRUE(fa.removeSymbol('c'));
  EXPECT_FALSE(fa.removeSymbol('c'));
}

TEST(AutomatonRemoveSymbolTest, SymbolInTransition){
  fa::Automaton fa = initalAutomaton();
  fprintf(stderr, "aaaa\n");
  EXPECT_TRUE(fa.hasTransition(1, 'b', 3));
  EXPECT_TRUE(fa.hasTransition(3, 'b', 4));
  EXPECT_TRUE(fa.hasTransition(2, 'b', 4));
  fprintf(stderr, "bbbb\n");
  EXPECT_EQ(9u, fa.countTransitions());
  fprintf(stderr, "cccc\n");
  EXPECT_TRUE(fa.removeSymbol('b'));
  fprintf(stderr, "dddd\n");
  EXPECT_FALSE(fa.hasTransition(1, 'b', 3));
  EXPECT_FALSE(fa.hasTransition(3, 'b', 4));
  EXPECT_FALSE(fa.hasTransition(2, 'b', 4));
  fprintf(stderr, "eeee\n");
  EXPECT_EQ(6u, fa.countTransitions());
  fprintf(stderr, "ffff\n");
}

/**
 * bool Automaton::hasSymbol(char symbol) const
 */

TEST(AutomatonHasSymbolTest, EmptyAlphabet){
  fa::Automaton fa;
  for (int i = 0; i<128; i++){
    char c = i;
    if (std::isgraph(c)){
      EXPECT_FALSE(fa.hasSymbol(c));
    }
  }
}

TEST(AutomatonHasSymbolTest, Present){
  fa::Automaton fa;
  for (int i = 0; i<128; i++){
    char c = i;
    if (std::isgraph(c)){
      EXPECT_TRUE(fa.addSymbol(c));
    }
  }
  for (int i = 0; i<128; i++){
    char c = i;
    if (std::isgraph(c)){
      EXPECT_TRUE(fa.hasSymbol(c));
    }
    else{
      EXPECT_FALSE(fa.hasSymbol(c));
    }
  }
}

TEST(AutomatonHasSymbolTest, Absent){
  fa::Automaton fa;
  for (int i = 0; i<128; i++){
    char c = i;
    if (std::isgraph(c)){
      EXPECT_TRUE(fa.addSymbol(c));
    }
  }
  for (int i = 0; i<128; i++){
    char c = i;
    if (std::isgraph(c)){
      EXPECT_TRUE(fa.removeSymbol(c));
      EXPECT_FALSE(fa.hasSymbol(c));
      EXPECT_TRUE(fa.addSymbol(c));
      EXPECT_TRUE(fa.hasSymbol(c));
    }
  }
}

TEST(AutomatonHasSymbolTest, Invalid){
  fa::Automaton fa;
  for (int i = 0; i<128; i++){
    char c = i;
    fa.addSymbol(c);
  }
  for (int i = 0; i<128; i++){
    char c = i;
    if (!(std::isgraph(c))){
      EXPECT_FALSE(fa.hasSymbol(c));
    }
  }
}

/**
 * std::size_t Automaton::countSymbols() const
 */

TEST(AutomatonCountSymbolsTest, Empty){
  fa::Automaton fa;
  EXPECT_EQ(0u, fa.countSymbols());
}

TEST(AutomatonCountSymbolsTest, OneSymbol){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('c'));
  EXPECT_EQ(1u, fa.countSymbols());
}

TEST(AutomatonCountSymbolsTest, ManySymbols){
  fa::Automaton fa;
  size_t count = 0;
  for (int i = 0; i<128; i++){
    char c = i;
    if(fa.addSymbol(c)){
      count += 1;
    }
  }
  EXPECT_EQ(count, fa.countSymbols());
}

/**
 * bool Automaton::addState(int state)
 */

TEST(AutomatonAddStateTest, New){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
}

TEST(AutomatonAddStateTest, Zero){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(0));
}

TEST(AutomatonAddStateTest, Negative){
  fa::Automaton fa;
  EXPECT_FALSE(fa.addState(-1));
}

TEST(AutomatonAddStateTest, Existing){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_FALSE(fa.addState(1));
}

TEST(AutomatonAddStateTest, Many){
  fa::Automaton fa;
  for (size_t i = 0; i<1000; i++){
    EXPECT_TRUE(fa.addState(i));
  }
}

/**
 * bool Automaton::removeState(int state)
 */

TEST(AutomatonRemoveStateTest, Existing){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.removeState(1));
}

TEST(AutomatonRemoveStateTest, NonExisting){
  fa::Automaton fa;
  EXPECT_FALSE(fa.removeState(1));

}

TEST(AutomatonRemoveStateTest, Invalid){
  fa::Automaton fa;
  EXPECT_FALSE(fa.removeState(-1));
}

TEST(AutomatonRemoveStateTest, Many){
  fa::Automaton fa;
  for (size_t i = 0; i<1000; i++){
    EXPECT_TRUE(fa.addState(i));
  }
  for (size_t i = 0; i<1000; i++){
    EXPECT_TRUE(fa.removeState(i));
  }
}

TEST(AutomatonRemoveStateTest, StateInTransitionFrom){
  fa::Automaton fa = initalAutomaton();
  EXPECT_TRUE(fa.hasTransition(0, 'a', 1));
  EXPECT_TRUE(fa.hasTransition(0, 'a', 2));
  EXPECT_TRUE(fa.hasTransition(0, 'a', 3));
  EXPECT_EQ(9u, fa.countTransitions());
  EXPECT_TRUE(fa.removeState(0));
  EXPECT_FALSE(fa.hasTransition(0, 'a', 1));
  EXPECT_FALSE(fa.hasTransition(0, 'a', 2));
  EXPECT_FALSE(fa.hasTransition(0, 'a', 3));
  EXPECT_EQ(6u, fa.countTransitions());
}

TEST(AutomatonRemoveStateTest, StateInTransitionTo){
  fa::Automaton fa = initalAutomaton();
  EXPECT_TRUE(fa.hasTransition(1, 'b', 3));
  EXPECT_TRUE(fa.hasTransition(0, 'a', 3));
  EXPECT_TRUE(fa.hasTransition(2, 'a', 3));
  EXPECT_TRUE(fa.hasTransition(3, 'a', 3));
  EXPECT_EQ(9u, fa.countTransitions());
  EXPECT_TRUE(fa.removeState(3));
  EXPECT_FALSE(fa.hasTransition(1, 'b', 3));
  EXPECT_FALSE(fa.hasTransition(0, 'a', 3));
  EXPECT_FALSE(fa.hasTransition(2, 'a', 3));
  EXPECT_FALSE(fa.hasTransition(3, 'a', 3));
  EXPECT_EQ(5u, fa.countTransitions());
}

/**
 * bool Automaton::hasState(int state) const
 */

TEST(AutomatonHasStateTest, Existing){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.hasState(1));
}

TEST(AutomatonHasStateTest, NonExisting){
  fa::Automaton fa;
  EXPECT_FALSE(fa.hasState(1));
}

/**
 * std::size_t Automaton::countStates() const
 */

TEST(AutomatonCountStatesTest, Zero){
  fa::Automaton fa;
  EXPECT_EQ(0u, fa.countStates());
}

TEST(AutomatonCountStatesTest, One){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_EQ(1u, fa.countStates());
}

TEST(AutomatonCountStatesTest, Many){
  fa::Automaton fa;
  for (size_t i = 0; i<1000; i++){
    EXPECT_TRUE(fa.addState(i));
  }
  EXPECT_EQ(1000u, fa.countStates());
}

/**
 * bool Automaton::isStateInitial(int state) const
 */

TEST(AutomatonIsStateInitialTest, Initial){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  fa.setStateInitial(1);
  EXPECT_TRUE(fa.isStateInitial(1));
}

TEST(AutomatonIsStateInitialTest, NonInitial){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_FALSE(fa.isStateInitial(1));
}

/**
 * bool Automaton::isStateFinal(int state) const
 */

TEST(AutomatonIsStateFinalTest, Final){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  fa.setStateFinal(1);
  EXPECT_TRUE(fa.isStateFinal(1));
}

TEST(AutomatonIsStateFinalTest, NonFinal){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_FALSE(fa.isStateFinal(1));
}

/**
 * bool Automaton::addTransition(int from, char alpha, int to)
 */

TEST(AutomatonAddTransitionTest, New){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.hasTransition(1, 'a', 2));
}

TEST(AutomatonAddTransitionTest, Existing){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_FALSE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.hasTransition(1, 'a', 2));
}

TEST(AutomatonAddTransitionTest, InvalidFrom){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_FALSE(fa.addTransition(1, 'a', 2));
  EXPECT_FALSE(fa.hasTransition(1, 'a', 2));

}

TEST(AutomatonAddTransitionTest, InvalidTo){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_FALSE(fa.addTransition(1, 'a', 2));
  EXPECT_FALSE(fa.hasTransition(1, 'a', 2));

}

TEST(AutomatonAddTransitionTest, InvalidAlpha){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_FALSE(fa.addTransition(1, 'a', 2));
  EXPECT_FALSE(fa.hasTransition(1, 'a', 2));
}

TEST(AutomatonAddTransitionTest, Epsilon){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addTransition(1, fa::Epsilon, 2));
  EXPECT_TRUE(fa.hasTransition(1, fa::Epsilon, 2));
}

/**
 * bool Automaton::removeTransition(in from, char alpha, int to)
 */

TEST(AutomatonRemoveTransitionTest, Existing){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.removeTransition(1, 'a', 2));
}

TEST(AutomatonRemoveTransitionTest, NonExisting){
  fa::Automaton fa;
  EXPECT_FALSE(fa.removeTransition(1, 'a', 2));
}

/**
 * bool Automaton::hasTransition(int from, char alpha, int to)
 */

TEST(AutomatonHasTransitionTest, Existing){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.hasTransition(1, 'a', 2));
}

TEST(AutomatonHasTransitionTest, NonExisting){
  fa::Automaton fa;
  EXPECT_FALSE(fa.hasTransition(1, 'a', 2));
}

TEST(AutomatonHasTransitionTest, PointingToSelf){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.hasTransition(0, 'a', 0));
}


/**
 * std::size_t Automaton::countTransitions() const
 */

TEST(AutomatonCountTransitionsTest, Zero){
  fa::Automaton fa;
  EXPECT_EQ(0u, fa.countTransitions());
}

TEST(AutomatonCountTransitionsTest, One){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_EQ(1u, fa.countTransitions());
}

/**
 * void prettyPrint(std::ostream& os) const
 */

TEST(AutomatonPrettyPrintTest, Empty){
  fa::Automaton fa;
  fa.prettyPrint(std::cout);
}

TEST(AutomatonPrettyPrintTest, Stuffed){
  fa::Automaton fa = initalAutomaton();
  fa.prettyPrint(std::cout);
}

/**
 * bool hasEpsilonTransition() const
 */

TEST(AutomatonHasEpsilonTransitionTest, Has){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addTransition(1, fa::Epsilon, 2));
  EXPECT_TRUE(fa.hasTransition(1, fa::Epsilon, 2));
  EXPECT_TRUE(fa.hasEpsilonTransition());
}

TEST(AutomatonHasEpsilonTransitionTest, HasNot){
  fa::Automaton fa = initalAutomaton();
  EXPECT_FALSE(fa.hasEpsilonTransition());
}

/**
 * bool isDeterministic() const
 */

TEST(AutomatonIsDeterministicTest, Deterministic){
  fa::Automaton fa = deterministicAutomaton1();
  EXPECT_TRUE(fa.isDeterministic());
}

TEST(AutomatonIsDeterministicTest, Complete){
  fa::Automaton fa = completeAutomaton1();
  EXPECT_FALSE(fa.isDeterministic());
}

TEST(AutomatonIsDeterministicTest, Both1){
  fa::Automaton fa = deterministicCompleteAutomaton1();
  EXPECT_TRUE(fa.isDeterministic());
}

TEST(AutomatonIsDeterministicTest, Both2){
  fa::Automaton fa = deterministicCompleteAutomaton2();
  EXPECT_TRUE(fa.isDeterministic());
}

TEST(AutomatonIsDeterministicTest, Neither){
  fa::Automaton fa = initalAutomaton();
  EXPECT_FALSE(fa.isDeterministic());
}

/**
 * bool isComplete() const
 */

TEST(AutomatonIsCompleteTest, Deterministic){
  fa::Automaton fa = deterministicAutomaton1();
  EXPECT_FALSE(fa.isComplete());
}

TEST(AutomatonIsCompleteTest, Complete){
  fa::Automaton fa = completeAutomaton1();
  EXPECT_TRUE(fa.isComplete());
}

TEST(AutomatonIsCompleteTest, Both1){
  fa::Automaton fa = deterministicCompleteAutomaton1();
  EXPECT_TRUE(fa.isComplete());
}

TEST(AutomatonIsCompleteTest, Both2){
  fa::Automaton fa = deterministicCompleteAutomaton2();
  EXPECT_TRUE(fa.isComplete());
}

TEST(AutomatonIsCompleteTest, Neither){
  fa::Automaton fa = initalAutomaton();
  EXPECT_FALSE(fa.isComplete());
}

/**
 * static Automaton createComplete(const Automaton& automaton)
 */

TEST(AutomatonCreateCompleteTest, AlreadyComplete){
  fa::Automaton fa1 = completeAutomaton1();
  fa::Automaton fa2 = fa::Automaton::createComplete(fa1);
  EXPECT_TRUE(fa1.isComplete());
  EXPECT_TRUE(fa2.isComplete());
}

TEST(AutomatonCreateCompleteTest, NotComplete){
  fa::Automaton fa1 = deterministicAutomaton1();
  fa::Automaton fa2 = fa::Automaton::createComplete(fa1);
  EXPECT_FALSE(fa1.isComplete());
  EXPECT_TRUE(fa2.isComplete());
}

/**
 * static Automaton createComplement(const Automaton& automaton)
 */

TEST(AutomatonCreateComplementTest, Deterministic){
  fa::Automaton fa1 = deterministicAutomaton1();
  EXPECT_TRUE(fa1.isDeterministic());
  EXPECT_FALSE(fa1.isComplete());
  EXPECT_FALSE(fa1.isStateFinal(0));
  EXPECT_FALSE(fa1.isStateFinal(1));
  EXPECT_FALSE(fa1.isStateFinal(2));
  EXPECT_TRUE(fa1.isStateFinal(3));
  fa::Automaton fa2 = fa::Automaton::createComplement(fa1);
  EXPECT_TRUE(fa2.isDeterministic());
  EXPECT_TRUE(fa2.isComplete());
  EXPECT_TRUE(fa2.isStateFinal(0));
  EXPECT_TRUE(fa2.isStateFinal(1));
  EXPECT_TRUE(fa2.isStateFinal(2));
  EXPECT_FALSE(fa2.isStateFinal(3));
}

TEST(AutomatonCreateComplementTest, Complete){
  // TO DO
  std::cout << "!!!  !!!  TO DO  !!!  !!!\n";
}

TEST(AutomatonCreateComplementTest, Both1){
  fa::Automaton fa1 = deterministicCompleteAutomaton1();
  EXPECT_TRUE(fa1.isDeterministic());
  EXPECT_TRUE(fa1.isComplete());
  EXPECT_FALSE(fa1.isStateFinal(0));
  EXPECT_TRUE(fa1.isStateFinal(1));
  fa::Automaton fa2 = fa::Automaton::createComplement(fa1);
  EXPECT_TRUE(fa2.isDeterministic());
  EXPECT_TRUE(fa2.isComplete());
  EXPECT_TRUE(fa2.isStateFinal(0));
  EXPECT_FALSE(fa2.isStateFinal(1));
}

TEST(AutomatonCreateComplementTest, Both2){
  fa::Automaton fa1 = deterministicCompleteAutomaton2();
  EXPECT_TRUE(fa1.isDeterministic());
  EXPECT_TRUE(fa1.isComplete());
  EXPECT_FALSE(fa1.isStateFinal(0));
  EXPECT_FALSE(fa1.isStateFinal(1));
  EXPECT_FALSE(fa1.isStateFinal(2));
  EXPECT_TRUE(fa1.isStateFinal(3));
  EXPECT_FALSE(fa1.isStateFinal(4));
  fa::Automaton fa2 = fa::Automaton::createComplement(fa1);
  EXPECT_TRUE(fa2.isDeterministic());
  EXPECT_TRUE(fa2.isComplete());
  EXPECT_TRUE(fa2.isStateFinal(0));
  EXPECT_TRUE(fa2.isStateFinal(1));
  EXPECT_TRUE(fa2.isStateFinal(2));
  EXPECT_FALSE(fa2.isStateFinal(3));
  EXPECT_TRUE(fa2.isStateFinal(4));
}

TEST(AutomatonCreateComplementTest, Neither){
  // TO DO
  std::cout << "!!!  !!!  TO DO  !!!  !!!\n";
}

/**
 * static Automaton createMirror(const Automaton& automaton)
 */

TEST(AutomatonCreateMirrorTest, Deterministic){
  fa::Automaton fa1 = deterministicAutomaton1();
  EXPECT_TRUE(fa1.isDeterministic());
  EXPECT_FALSE(fa1.isComplete());
  EXPECT_TRUE(fa1.isStateInitial(0));
  EXPECT_TRUE(fa1.isStateFinal(3));
  EXPECT_TRUE(fa1.hasTransition(0, 'b', 1));
  EXPECT_TRUE(fa1.hasTransition(1, 'a', 2));
  EXPECT_TRUE(fa1.hasTransition(2, 'a', 2));
  EXPECT_TRUE(fa1.hasTransition(2, 'b', 3));
  fa::Automaton fa2 = fa::Automaton::createMirror(fa1);
  EXPECT_TRUE(fa2.isStateFinal(0));
  EXPECT_TRUE(fa2.isStateInitial(3));
  EXPECT_TRUE(fa2.hasTransition(1, 'b', 0));
  EXPECT_TRUE(fa2.hasTransition(2, 'a', 1));
  EXPECT_TRUE(fa2.hasTransition(2, 'a', 2));
  EXPECT_TRUE(fa2.hasTransition(3, 'b', 2));
}

TEST(AutomatonCreateMirrorTest, Complete){
  fa::Automaton fa1 = completeAutomaton1();
  EXPECT_FALSE(fa1.isDeterministic());
  EXPECT_TRUE(fa1.isComplete());
  EXPECT_TRUE(fa1.isStateInitial(0));
  EXPECT_TRUE(fa1.isStateFinal(3));
  EXPECT_TRUE(fa1.hasTransition(0, 'a', 0));
  EXPECT_TRUE(fa1.hasTransition(0, 'a', 2));
  EXPECT_TRUE(fa1.hasTransition(0, 'b', 0));
  EXPECT_TRUE(fa1.hasTransition(0, 'b', 1));
  EXPECT_TRUE(fa1.hasTransition(1, 'b', 3));
  EXPECT_TRUE(fa1.hasTransition(2, 'a', 3));
  EXPECT_TRUE(fa1.hasTransition(3, 'a', 3));
  EXPECT_TRUE(fa1.hasTransition(3, 'b', 3));
  EXPECT_TRUE(fa1.hasTransition(1, 'a', 2));
  EXPECT_TRUE(fa1.hasTransition(2, 'b', 3));
  fa::Automaton fa2 = fa::Automaton::createMirror(fa1);
  EXPECT_TRUE(fa2.isStateFinal(0));
  EXPECT_TRUE(fa2.isStateInitial(3));
  EXPECT_TRUE(fa2.hasTransition(0, 'a', 0));
  EXPECT_TRUE(fa2.hasTransition(2, 'a', 0));
  EXPECT_TRUE(fa2.hasTransition(0, 'b', 0));
  EXPECT_TRUE(fa2.hasTransition(1, 'b', 0));
  EXPECT_TRUE(fa2.hasTransition(3, 'b', 1));
  EXPECT_TRUE(fa2.hasTransition(3, 'a', 2));
  EXPECT_TRUE(fa2.hasTransition(3, 'a', 3));
  EXPECT_TRUE(fa2.hasTransition(3, 'b', 3));
  EXPECT_TRUE(fa2.hasTransition(2, 'a', 1));
  EXPECT_TRUE(fa2.hasTransition(3, 'b', 2));
}

TEST(AutomatonCreateMirrorTest, Both1){
  fa::Automaton fa1 = deterministicCompleteAutomaton1();
  EXPECT_TRUE(fa1.isDeterministic());
  EXPECT_TRUE(fa1.isComplete());
  EXPECT_TRUE(fa1.isStateInitial(0));
  EXPECT_TRUE(fa1.isStateFinal(1));
  EXPECT_TRUE(fa1.hasTransition(0, 'a', 0));
  EXPECT_TRUE(fa1.hasTransition(0, 'b', 1));
  EXPECT_TRUE(fa1.hasTransition(1, 'a', 1));
  EXPECT_TRUE(fa1.hasTransition(1, 'b', 0));
  fa::Automaton fa2 = fa::Automaton::createMirror(fa1);
  EXPECT_TRUE(fa2.isStateFinal(0));
  EXPECT_TRUE(fa2.isStateInitial(1));
  EXPECT_TRUE(fa2.hasTransition(0, 'a', 0));
  EXPECT_TRUE(fa2.hasTransition(1, 'b', 0));
  EXPECT_TRUE(fa2.hasTransition(1, 'a', 1));
  EXPECT_TRUE(fa2.hasTransition(0, 'b', 1));
}

TEST(AutomatonCreateMirrorTest, Both2){
  fa::Automaton fa1 = deterministicCompleteAutomaton2();
  EXPECT_TRUE(fa1.isDeterministic());
  EXPECT_TRUE(fa1.isComplete());
  EXPECT_TRUE(fa1.isStateInitial(0));
  EXPECT_TRUE(fa1.isStateFinal(3));
  EXPECT_TRUE(fa1.hasTransition(0, 'a', 4));
  EXPECT_TRUE(fa1.hasTransition(0, 'b', 1));
  EXPECT_TRUE(fa1.hasTransition(1, 'a', 2));
  EXPECT_TRUE(fa1.hasTransition(1, 'b', 4));
  EXPECT_TRUE(fa1.hasTransition(2, 'a', 2));
  EXPECT_TRUE(fa1.hasTransition(2, 'b', 3));
  EXPECT_TRUE(fa1.hasTransition(3, 'a', 4));
  EXPECT_TRUE(fa1.hasTransition(3, 'b', 4));
  EXPECT_TRUE(fa1.hasTransition(4, 'a', 4));
  EXPECT_TRUE(fa1.hasTransition(4, 'b', 4));
  fa::Automaton fa2 = fa::Automaton::createMirror(fa1);
  EXPECT_TRUE(fa2.isStateFinal(0));
  EXPECT_TRUE(fa2.isStateInitial(3));
  EXPECT_TRUE(fa2.hasTransition(4, 'a', 0));
  EXPECT_TRUE(fa2.hasTransition(1, 'b', 0));
  EXPECT_TRUE(fa2.hasTransition(2, 'a', 1));
  EXPECT_TRUE(fa2.hasTransition(4, 'b', 1));
  EXPECT_TRUE(fa2.hasTransition(2, 'a', 2));
  EXPECT_TRUE(fa2.hasTransition(3, 'b', 2));
  EXPECT_TRUE(fa2.hasTransition(4, 'a', 3));
  EXPECT_TRUE(fa2.hasTransition(4, 'b', 3));
  EXPECT_TRUE(fa2.hasTransition(4, 'a', 4));
  EXPECT_TRUE(fa2.hasTransition(4, 'b', 4));

}

TEST(AutomatonCreateMirrorTest, Neither){
  fa::Automaton fa1 = initalAutomaton();
  EXPECT_FALSE(fa1.isDeterministic());
  EXPECT_FALSE(fa1.isComplete());
  EXPECT_TRUE(fa1.isStateInitial(0));
  EXPECT_TRUE(fa1.isStateInitial(1));
  EXPECT_TRUE(fa1.isStateFinal(1));
  EXPECT_TRUE(fa1.isStateFinal(4));
  EXPECT_TRUE(fa1.hasTransition(0, 'a', 1));
  EXPECT_TRUE(fa1.hasTransition(0, 'a', 2));
  EXPECT_TRUE(fa1.hasTransition(0, 'a', 3));
  EXPECT_TRUE(fa1.hasTransition(1, 'b', 3));
  EXPECT_TRUE(fa1.hasTransition(2, 'a', 3));
  EXPECT_TRUE(fa1.hasTransition(2, 'b', 4));
  EXPECT_TRUE(fa1.hasTransition(3, 'a', 3));
  EXPECT_TRUE(fa1.hasTransition(3, 'b', 4));
  EXPECT_TRUE(fa1.hasTransition(4, 'a', 4));
  fa::Automaton fa2 = fa::Automaton::createMirror(fa1);
  EXPECT_TRUE(fa2.isStateFinal(0));
  EXPECT_TRUE(fa2.isStateFinal(1));
  EXPECT_TRUE(fa2.isStateInitial(1));
  EXPECT_TRUE(fa2.isStateInitial(4));
  EXPECT_TRUE(fa2.hasTransition(1, 'a', 0));
  EXPECT_TRUE(fa2.hasTransition(2, 'a', 0));
  EXPECT_TRUE(fa2.hasTransition(3, 'a', 0));
  EXPECT_TRUE(fa2.hasTransition(3, 'b', 1));
  EXPECT_TRUE(fa2.hasTransition(3, 'a', 2));
  EXPECT_TRUE(fa2.hasTransition(4, 'b', 2));
  EXPECT_TRUE(fa2.hasTransition(3, 'a', 3));
  EXPECT_TRUE(fa2.hasTransition(4, 'b', 3));
  EXPECT_TRUE(fa2.hasTransition(4, 'a', 4));
}

/**
 * std::set<int> makeTransition(const std::set<int>&origin, char alpha) const
 */

TEST(AutomatonMakeTransitionTest, Deterministic){
  fa::Automaton fa = deterministicAutomaton1();
  std::set<int> origin, setA, setB;
  origin.insert(0);
  setA = fa.makeTransition(origin, 'a');
  setB = fa.makeTransition(origin, 'b');
  EXPECT_EQ(0u, setA.size());
  EXPECT_EQ(1u, setB.size());
  EXPECT_EQ(1u, setB.count(1));
  origin = setB;
  setA = fa.makeTransition(origin, 'a');
  setB = fa.makeTransition(origin, 'b');
  EXPECT_EQ(1u, setA.size());
  EXPECT_EQ(1u, setA.count(2));
  EXPECT_EQ(0u, setB.size());
  origin = setA;
  setA = fa.makeTransition(origin, 'a');
  setB = fa.makeTransition(origin, 'b');
  EXPECT_EQ(1u, setA.size());
  EXPECT_EQ(1u, setA.count(2));
  EXPECT_EQ(1u, setB.size());
  EXPECT_EQ(1u, setB.count(3));
}

TEST(AutomatonMakeTransitionTest, Complete){
  fa::Automaton fa = completeAutomaton1();
  std::set<int> origin, setA, setB;
  origin.insert(0);
  setA = fa.makeTransition(origin, 'a');
  setB = fa.makeTransition(origin, 'b');
  EXPECT_EQ(2u, setA.size());
  EXPECT_EQ(1u, setA.count(0));
  EXPECT_EQ(1u, setA.count(2));
  EXPECT_EQ(2u, setB.size());
  EXPECT_EQ(1u, setB.count(0));
  EXPECT_EQ(1u, setB.count(1));
  origin = setA;
  setA = fa.makeTransition(origin, 'a');
  setB = fa.makeTransition(origin, 'b');
  EXPECT_EQ(3u, setA.size());
  EXPECT_EQ(1u, setA.count(0));
  EXPECT_EQ(1u, setA.count(2));
  EXPECT_EQ(1u, setA.count(3));
  EXPECT_EQ(3u, setB.size());
  EXPECT_EQ(1u, setB.count(0));
  EXPECT_EQ(1u, setB.count(1));
  EXPECT_EQ(1u, setB.count(3));
  origin = setA;
  setA = fa.makeTransition(origin, 'a');
  setB = fa.makeTransition(origin, 'b');
  EXPECT_EQ(1u, setA.count(0));
  EXPECT_EQ(1u, setA.count(2));
  EXPECT_EQ(1u, setA.count(3));
  EXPECT_EQ(3u, setB.size());
  EXPECT_EQ(1u, setB.count(0));
  EXPECT_EQ(1u, setB.count(1));
  EXPECT_EQ(1u, setB.count(3));
  origin = setB;
  setA = fa.makeTransition(origin, 'a');
  setB = fa.makeTransition(origin, 'b');
  EXPECT_EQ(3u, setA.size());
  EXPECT_EQ(1u, setA.count(0));
  EXPECT_EQ(1u, setA.count(2));
  EXPECT_EQ(1u, setA.count(3));
  EXPECT_EQ(3u, setB.size());
  EXPECT_EQ(1u, setB.count(0));
  EXPECT_EQ(1u, setB.count(1));
  EXPECT_EQ(1u, setB.count(3));
}

TEST(AutomatonMakeTransitionTest, Both1){
  fa::Automaton fa = deterministicCompleteAutomaton1();
  std::set<int> origin, setA, setB;
  origin.insert(0);
  setA = fa.makeTransition(origin, 'a');
  setB = fa.makeTransition(origin, 'b');
  EXPECT_EQ(1u, setA.size());
  EXPECT_EQ(1u, setA.count(0));
  EXPECT_EQ(1u, setB.size());
  EXPECT_EQ(1u, setB.count(1));
  origin = setB;
  setA = fa.makeTransition(origin, 'a');
  setB = fa.makeTransition(origin, 'b');
  EXPECT_EQ(1u, setA.size());
  EXPECT_EQ(1u, setA.count(1));
  EXPECT_EQ(1u, setB.size());
  EXPECT_EQ(1u, setB.count(0));
}

TEST(AutomatonMakeTransitionTest, Both2){
  fa::Automaton fa = deterministicCompleteAutomaton2();
  std::set<int> origin, setA, setB;
  origin.insert(0);
  setA = fa.makeTransition(origin, 'a');
  setB = fa.makeTransition(origin, 'b');
  EXPECT_EQ(1u, setA.size());
  EXPECT_EQ(1u, setA.count(4));
  EXPECT_EQ(1u, setB.size());
  EXPECT_EQ(1u, setB.count(1));
  origin = setA;
  setA = fa.makeTransition(origin, 'a');
  setB = fa.makeTransition(origin, 'b');
  EXPECT_EQ(1u, setA.size());
  EXPECT_EQ(1u, setA.count(4));
  EXPECT_EQ(1u, setB.size());
  EXPECT_EQ(1u, setB.count(4));
  origin.clear();
  origin.insert(0);
  origin = fa.makeTransition(origin, 'b');
  setA = fa.makeTransition(origin, 'a');
  setB = fa.makeTransition(origin, 'b');
  EXPECT_EQ(1u, setA.size());
  EXPECT_EQ(1u, setA.count(2));
  EXPECT_EQ(1u, setB.size());
  EXPECT_EQ(1u, setB.count(4));
  origin = setA;
  setA = fa.makeTransition(origin, 'a');
  setB = fa.makeTransition(origin, 'b');
  EXPECT_EQ(1u, setA.size());
  EXPECT_EQ(1u, setA.count(2));
  EXPECT_EQ(1u, setB.size());
  EXPECT_EQ(1u, setB.count(3));
  origin = setB;
  setA = fa.makeTransition(origin, 'a');
  setB = fa.makeTransition(origin, 'b');
  EXPECT_EQ(1u, setA.size());
  EXPECT_EQ(1u, setA.count(4));
  EXPECT_EQ(1u, setB.size());
  EXPECT_EQ(1u, setB.count(4));
}

TEST(AutomatonMakeTransitionTest, Neither){
  fa::Automaton fa = initalAutomaton();
  std::set<int> origin, setA, setB;
  origin.insert(0);
  origin.insert(1);
  setA = fa.makeTransition(origin, 'a');
  setB = fa.makeTransition(origin, 'b');
  EXPECT_EQ(3u, setA.size());
  EXPECT_EQ(1u, setA.count(1));
  EXPECT_EQ(1u, setA.count(2));
  EXPECT_EQ(1u, setA.count(3));
  EXPECT_EQ(1u, setB.size());
  EXPECT_EQ(1u, setB.count(3));
  origin = setA;
  setA = fa.makeTransition(origin, 'a');
  setB = fa.makeTransition(origin, 'b');
  EXPECT_EQ(1u, setA.size());
  EXPECT_EQ(1u, setA.count(3));
  EXPECT_EQ(2u, setB.size());
  EXPECT_EQ(1u, setB.count(3));
  EXPECT_EQ(1u, setB.count(4));
  origin = setA;
  setA = fa.makeTransition(origin, 'a');
  setB = fa.makeTransition(origin, 'b');
  EXPECT_EQ(1u, setA.size());
  EXPECT_EQ(1u, setA.count(3));
  EXPECT_EQ(1u, setB.size());
  EXPECT_EQ(1u, setB.count(4));
  origin = setB;
  setA = fa.makeTransition(origin, 'a');
  setB = fa.makeTransition(origin, 'b');
  EXPECT_EQ(1u, setA.size());
  EXPECT_EQ(1u, setA.count(4));
  EXPECT_EQ(0u, setB.size());
  origin.clear();
  origin.insert(0);
  origin.insert(1);
  origin = fa.makeTransition(origin, 'a');
  origin = fa.makeTransition(origin, 'b');
  setA = fa.makeTransition(origin, 'a');
  setB = fa.makeTransition(origin, 'b');
  EXPECT_EQ(2u, setA.size());
  EXPECT_EQ(1u, setA.count(3));
  EXPECT_EQ(1u, setA.count(4));
  EXPECT_EQ(1u, setB.size());
  EXPECT_EQ(1u, setB.count(4));
}

/**
 * std::set<int> readString(const std::string& word)
 */

TEST(AutomatonReadStringTest, DeterministicWORD1){
  fa::Automaton fa = deterministicAutomaton1();
  std::set<int> res = fa.readString(WORD1);
  EXPECT_EQ(0u, res.size());
}

TEST(AutomatonReadStringTest, DeterministicWORD2){
  fa::Automaton fa = deterministicAutomaton1();
  std::set<int> res = fa.readString(WORD2);
  EXPECT_EQ(1u, res.size());
  EXPECT_EQ(1u, res.count(3));
}

TEST(AutomatonReadStringTest, DeterministicWORD3){
  fa::Automaton fa = deterministicAutomaton1();
  std::set<int> res = fa.readString(WORD3);
  EXPECT_EQ(0u, res.size());
}

TEST(AutomatonReadStringTest, DeterministicWORD4){
  fa::Automaton fa = deterministicAutomaton1();
  std::set<int> res = fa.readString(WORD4);
  EXPECT_EQ(0u, res.size());
}

TEST(AutomatonReadStringTest, CompleteWORD1){
  fa::Automaton fa = completeAutomaton1();
  std::set<int> res = fa.readString(WORD1);
  EXPECT_EQ(3u, res.size());
  EXPECT_EQ(1u, res.count(0));
  EXPECT_EQ(1u, res.count(1));
  EXPECT_EQ(1u, res.count(3));
}

TEST(AutomatonReadStringTest, CompleteWORD2){
  fa::Automaton fa = completeAutomaton1();
  std::set<int> res = fa.readString(WORD2);
  EXPECT_EQ(3u, res.size());
  EXPECT_EQ(1u, res.count(0));
  EXPECT_EQ(1u, res.count(1));
  EXPECT_EQ(1u, res.count(3));
}

TEST(AutomatonReadStringTest, CompleteWORD3){
  fa::Automaton fa = completeAutomaton1();
  std::set<int> res = fa.readString(WORD3);
  EXPECT_EQ(3u, res.size());
  EXPECT_EQ(1u, res.count(0));
  EXPECT_EQ(1u, res.count(2));
  EXPECT_EQ(1u, res.count(3));
}

TEST(AutomatonReadStringTest, CompleteWORD4){
  fa::Automaton fa = completeAutomaton1();
  std::set<int> res = fa.readString(WORD4);
  EXPECT_EQ(3u, res.size());
  EXPECT_EQ(1u, res.count(0));
  EXPECT_EQ(1u, res.count(2));
  EXPECT_EQ(1u, res.count(3));
}

TEST(AutomatonReadStringTest, Both1WORD1){
  fa::Automaton fa = deterministicCompleteAutomaton1();
  std::set<int> res = fa.readString(WORD1);
  EXPECT_EQ(1u, res.size());
  EXPECT_EQ(1u, res.count(0));
}

TEST(AutomatonReadStringTest, Both1WORD2){
  fa::Automaton fa = deterministicCompleteAutomaton1();
  std::set<int> res = fa.readString(WORD2);
  EXPECT_EQ(1u, res.size());
  EXPECT_EQ(1u, res.count(0));
}

TEST(AutomatonReadStringTest, Both1WORD3){
  fa::Automaton fa = deterministicCompleteAutomaton1();
  std::set<int> res = fa.readString(WORD3);
  EXPECT_EQ(1u, res.size());
  EXPECT_EQ(1u, res.count(1));
}

TEST(AutomatonReadStringTest, Both1WORD4){
  fa::Automaton fa = deterministicCompleteAutomaton1();
  std::set<int> res = fa.readString(WORD4);
  EXPECT_EQ(1u, res.size());
  EXPECT_EQ(1u, res.count(0));
}

TEST(AutomatonReadStringTest, Both2WORD1){
  fa::Automaton fa = deterministicCompleteAutomaton2();
  std::set<int> res = fa.readString(WORD1);
  EXPECT_EQ(1u, res.size());
  EXPECT_EQ(1u, res.count(4));
}

TEST(AutomatonReadStringTest, Both2WORD2){
  fa::Automaton fa = deterministicCompleteAutomaton2();
  std::set<int> res = fa.readString(WORD2);
  EXPECT_EQ(1u, res.size());
  EXPECT_EQ(1u, res.count(3));
}

TEST(AutomatonReadStringTest, Both2WORD3){
  fa::Automaton fa = deterministicCompleteAutomaton2();
  std::set<int> res = fa.readString(WORD3);
  EXPECT_EQ(1u, res.size());
  EXPECT_EQ(1u, res.count(4));
}

TEST(AutomatonReadStringTest, Both2WORD4){
  fa::Automaton fa = deterministicCompleteAutomaton2();
  std::set<int> res = fa.readString(WORD4);
  EXPECT_EQ(1u, res.size());
  EXPECT_EQ(1u, res.count(4));
}

TEST(AutomatonReadStringTest, NeitherWORD1){
  fa::Automaton fa = initalAutomaton();
  std::set<int> res = fa.readString(WORD1);
  EXPECT_EQ(0u, res.size());
}

TEST(AutomatonReadStringTest, NeitherWORD2){
  fa::Automaton fa = initalAutomaton();
  std::set<int> res = fa.readString(WORD2);
  EXPECT_EQ(1u, res.size());
  EXPECT_EQ(1u, res.count(4));
}

TEST(AutomatonReadStringTest, NeitherWORD3){
  fa::Automaton fa = initalAutomaton();
  std::set<int> res = fa.readString(WORD3);
  EXPECT_EQ(1u, res.size());
  EXPECT_EQ(1u, res.count(4));
}

TEST(AutomatonReadStringTest, NeitherWORD4){
  fa::Automaton fa = initalAutomaton();
  std::set<int> res = fa.readString(WORD4);
  EXPECT_EQ(1u, res.size());
  EXPECT_EQ(1u, res.count(3));
}

/**
 * bool match(const std::string& word) const
 */

TEST(AutomatonMatchTest, DeterministicWORD1){
  fa::Automaton fa = deterministicAutomaton1();
  EXPECT_FALSE(fa.match(WORD1));
}

TEST(AutomatonMatchTest, DeterministicWORD2){
  fa::Automaton fa = deterministicAutomaton1();
  EXPECT_TRUE(fa.match(WORD2));
}

TEST(AutomatonMatchTest, DeterministicWORD3){
  fa::Automaton fa = deterministicAutomaton1();
  EXPECT_FALSE(fa.match(WORD3));
}

TEST(AutomatonMatchTest, DeterministicWORD4){
  fa::Automaton fa = deterministicAutomaton1();
  EXPECT_FALSE(fa.match(WORD4));
}

TEST(AutomatonMatchTest, CompleteWORD1){
  fa::Automaton fa = completeAutomaton1();
  EXPECT_TRUE(fa.match(WORD1));
}

TEST(AutomatonMatchTest, CompleteWORD2){
  fa::Automaton fa = completeAutomaton1();
  EXPECT_TRUE(fa.match(WORD2));
}

TEST(AutomatonMatchTest, CompleteWORD3){
  fa::Automaton fa = completeAutomaton1();
  EXPECT_TRUE(fa.match(WORD3));
}

TEST(AutomatonMatchTest, CompleteWORD4){
  fa::Automaton fa = completeAutomaton1();
  EXPECT_TRUE(fa.match(WORD4));
}

TEST(AutomatonMatchTest, Both1WORD1){
  fa::Automaton fa = deterministicCompleteAutomaton1();
  EXPECT_FALSE(fa.match(WORD1));
}

TEST(AutomatonMatchTest, Both1WORD2){
  fa::Automaton fa = deterministicCompleteAutomaton1();
  EXPECT_FALSE(fa.match(WORD2));
}

TEST(AutomatonMatchTest, Both1WORD3){
  fa::Automaton fa = deterministicCompleteAutomaton1();
  EXPECT_TRUE(fa.match(WORD3));
}

TEST(AutomatonMatchTest, Both1WORD4){
  fa::Automaton fa = deterministicCompleteAutomaton1();
  EXPECT_FALSE(fa.match(WORD4));
}

TEST(AutomatonMatchTest, Both2WORD1){
  fa::Automaton fa = deterministicCompleteAutomaton2();
  EXPECT_FALSE(fa.match(WORD1));
}

TEST(AutomatonMatchTest, Both2WORD2){
  fa::Automaton fa = deterministicCompleteAutomaton2();
  EXPECT_TRUE(fa.match(WORD2));
}

TEST(AutomatonMatchTest, Both2WORD3){
  fa::Automaton fa = deterministicCompleteAutomaton2();
  EXPECT_FALSE(fa.match(WORD3));
}

TEST(AutomatonMatchTest, Both2WORD4){
  fa::Automaton fa = deterministicCompleteAutomaton2();
  EXPECT_FALSE(fa.match(WORD4));
}

TEST(AutomatonMatchTest, NeitherWORD1){
  fa::Automaton fa = initalAutomaton();
  EXPECT_FALSE(fa.match(WORD1));
}

TEST(AutomatonMatchTest, NeitherWORD2){
  fa::Automaton fa = initalAutomaton();
  EXPECT_TRUE(fa.match(WORD2));
}

TEST(AutomatonMatchTest, NeitherWORD3){
  fa::Automaton fa = initalAutomaton();
  EXPECT_TRUE(fa.match(WORD3));
}

TEST(AutomatonMatchTest, NeitherWORD4){
  fa::Automaton fa = initalAutomaton();
  EXPECT_FALSE(fa.match(WORD4));
}

/**
 * bool isLanguageEmpty() const
 */

TEST(AutomatonIsLanguageEmptyTest, NoInitialStates){
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 1);
  fa.setStateFinal(1);
  EXPECT_TRUE(fa.isLanguageEmpty());
}

TEST(AutomatonIsLanguageEmptyTest, NoFinalStates){
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 1);
  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isLanguageEmpty());
}

TEST(AutomatonIsLanguageEmptyTest, NoTransition){
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addSymbol('a');
  fa.setStateInitial(0);
  fa.setStateFinal(1);
  EXPECT_TRUE(fa.isLanguageEmpty());
}

TEST(AutomatonIsLanguageEmptyTest, DeterministicAndComplete){
  fa::Automaton fa = deterministicCompleteAutomaton1();
  EXPECT_FALSE(fa.isLanguageEmpty());
}

TEST(AutomatonIsLanguageEmptyTest, Neither){
  fa::Automaton fa = initalAutomaton();
  EXPECT_FALSE(fa.isLanguageEmpty());
}

/**
 * void removeNonAccessibleStates()
 */

TEST(AutomatonRemoveNonAccessibleStatesTest, DeterministicAndComplete){
  fa::Automaton fa = deterministicCompleteAutomaton1();
  fa.removeNonAccessibleStates();
  EXPECT_TRUE(fa.hasState(0));
  EXPECT_TRUE(fa.hasState(1));
}

TEST(AutomatonRemoveNonAccessibleStatesTest, Neither){
  fa::Automaton fa = initalAutomaton();
  fa.removeNonAccessibleStates();
  EXPECT_TRUE(fa.hasState(0));
  EXPECT_TRUE(fa.hasState(1));
  EXPECT_TRUE(fa.hasState(2));
  EXPECT_TRUE(fa.hasState(3));
  EXPECT_TRUE(fa.hasState(4));
}

TEST(AutomatonRemoveNonAccessibleStatesTest, OneRemoval){
  fa::Automaton fa = initalAutomaton();
  fa.addState(5);
  fa.addTransition(5, 'b', 4);
  fa.removeNonAccessibleStates();
  EXPECT_FALSE(fa.hasState(5));
  EXPECT_FALSE(fa.hasTransition(5, 'b', 4));
}

TEST(AutomatonRemoveNonAccessibleStatesTest, SeveralRemovals){
  fa::Automaton fa = initalAutomaton();
  fa.addState(5);
  fa.addState(6);
  fa.addState(7);
  fa.addState(8);
  fa.addState(9);
  fa.addState(10);
  fa.addTransition(5, 'b', 4);
  fa.addTransition(6, 'a', 1);
  fa.addTransition(7, 'b', 0);
  fa.addTransition(8, 'a', 4);
  fa.addTransition(9, 'a', 5);
  fa.addTransition(10, 'b', 2);
  fa.removeNonAccessibleStates();
  EXPECT_FALSE(fa.hasState(5));
  EXPECT_FALSE(fa.hasState(6));
  EXPECT_FALSE(fa.hasState(7));
  EXPECT_FALSE(fa.hasState(8));
  EXPECT_FALSE(fa.hasState(9));
  EXPECT_FALSE(fa.hasState(10));
  EXPECT_FALSE(fa.hasTransition(5, 'b', 4));
  EXPECT_FALSE(fa.hasTransition(6, 'a', 1));
  EXPECT_FALSE(fa.hasTransition(7, 'b', 0));
  EXPECT_FALSE(fa.hasTransition(8, 'a', 4));
  EXPECT_FALSE(fa.hasTransition(9, 'a', 5));
  EXPECT_FALSE(fa.hasTransition(10, 'b', 2));
}


/**
 * void removeNonCoAccessibleStates()
 */

TEST(AutomatonRemoveNonCoAccessibleStatesTest, DeterministicAndComplete){
  fa::Automaton fa = deterministicCompleteAutomaton1();
  fa.removeNonCoAccessibleStates();
  EXPECT_TRUE(fa.hasState(0));
  EXPECT_TRUE(fa.hasState(1));
}

TEST(AutomatonRemoveNonCoAccessibleStatesTest, Neither){
  fa::Automaton fa = initalAutomaton();
  fa.removeNonCoAccessibleStates();
  EXPECT_TRUE(fa.hasState(0));
  EXPECT_TRUE(fa.hasState(1));
  EXPECT_TRUE(fa.hasState(2));
  EXPECT_TRUE(fa.hasState(3));
  EXPECT_TRUE(fa.hasState(4));
}

TEST(AutomatonRemoveNonCoAccessibleStatesTest, OneRemoval){
  fa::Automaton fa = initalAutomaton();
  fa.addState(5);
  fa.addTransition(1, 'b', 5);
  fa.removeNonAccessibleStates();
  EXPECT_TRUE(fa.hasState(0));
  EXPECT_TRUE(fa.hasState(1));
  EXPECT_TRUE(fa.hasState(2));
  EXPECT_TRUE(fa.hasState(3));
  EXPECT_TRUE(fa.hasState(4));
  EXPECT_FALSE(fa.hasState(5));
  EXPECT_FALSE(fa.hasTransition(1, 'b', 5));
}

TEST(AutomatonRemoveNonCoAccessibleStatesTest, SeveralRemovals){
  fa::Automaton fa = initalAutomaton();
  fa.addState(5);
  fa.addState(6);
  fa.addState(7);
  fa.addState(8);
  fa.addState(9);
  fa.addState(10);
  fa.addTransition(1, 'b', 5);
  fa.addTransition(1, 'a', 6);
  fa.addTransition(0, 'b', 7);
  fa.addTransition(4, 'a', 8);
  fa.addTransition(5, 'a', 9);
  fa.addTransition(2, 'b', 10);
  fa.removeNonCoAccessibleStates();
  EXPECT_TRUE(fa.hasState(0));
  EXPECT_TRUE(fa.hasState(1));
  EXPECT_TRUE(fa.hasState(2));
  EXPECT_TRUE(fa.hasState(3));
  EXPECT_TRUE(fa.hasState(4));
  EXPECT_FALSE(fa.hasState(5));
  EXPECT_FALSE(fa.hasState(6));
  EXPECT_FALSE(fa.hasState(7));
  EXPECT_FALSE(fa.hasState(8));
  EXPECT_FALSE(fa.hasState(9));
  EXPECT_FALSE(fa.hasState(10));
  EXPECT_FALSE(fa.hasTransition(1, 'b', 5));
  EXPECT_FALSE(fa.hasTransition(1, 'a', 6));
  EXPECT_FALSE(fa.hasTransition(0, 'b', 7));
  EXPECT_FALSE(fa.hasTransition(4, 'a', 8));
  EXPECT_FALSE(fa.hasTransition(5, 'a', 9));
  EXPECT_FALSE(fa.hasTransition(2, 'b', 10));
}

/**
 * main
 */

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
