
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

TEST(AddSymbolTest, Valid){
  fa::Automaton fa;
  for (int i = 0; i<128; i++){
    char c = i;
    if (std::isgraph(c) || c == fa::Epsilon){
      EXPECT_TRUE(fa.addSymbol(c));
    }
  }
}

TEST(AddSymbolTest, Existing){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('c'));
  EXPECT_FALSE(fa.addSymbol('c'));
}

TEST(AddSymbolTest, Invalid){
  fa::Automaton fa;
  for (int i = 0; i<128; i++){
    char c = i;
    if (!(std::isgraph(c) || c == fa::Epsilon)){
      EXPECT_FALSE(fa.addSymbol(c));
    }
  }
}

/**
 * bool Automaton::RemoveSymbol(char symbol)
 */

TEST(RemoveSymbolTest, Present){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('c'));
  EXPECT_TRUE(fa.removeSymbol('c'));
}

TEST(RemoveSymbolTest, Absent){
  fa::Automaton fa;
  EXPECT_FALSE(fa.removeSymbol('c'));
}

TEST(RemoveSymbolTest, Invalid){
  fa::Automaton fa;
  EXPECT_FALSE(fa.removeSymbol('\t'));
  EXPECT_TRUE(fa.addSymbol('c'));
  EXPECT_FALSE(fa.removeSymbol('\t'));
}

TEST(RemoveSymbolTest, AlreadyRemoved){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('c'));
  EXPECT_TRUE(fa.removeSymbol('c'));
  EXPECT_FALSE(fa.removeSymbol('c'));
}

/**
 * bool Automaton::hasSymbol(char symbol) const
 */

TEST(HasSymbolTest, EmptyAlphabet){
  fa::Automaton fa;
  for (int i = 0; i<128; i++){
    char c = i;
    if (std::isgraph(c)){
      EXPECT_FALSE(fa.hasSymbol(c));
    }
  }
}

TEST(HasSymbolTest, Present){
  fa::Automaton fa;
  for (int i = 0; i<128; i++){
    char c = i;
    if (std::isgraph(c) || c == fa::Epsilon){
      EXPECT_TRUE(fa.addSymbol(c));
    }
  }
  for (int i = 0; i<128; i++){
    char c = i;
    if (std::isgraph(c) || c == fa::Epsilon){
      EXPECT_TRUE(fa.hasSymbol(c));
    }
    else{
      EXPECT_FALSE(fa.hasSymbol(c));
    }
  }
}

TEST(HasSymbolTest, Absent){
  fa::Automaton fa;
  for (int i = 0; i<128; i++){
    char c = i;
    if (std::isgraph(c) || c == fa::Epsilon){
      EXPECT_TRUE(fa.addSymbol(c));
    }
  }
  for (int i = 0; i<128; i++){
    char c = i;
    if (std::isgraph(c) || c == fa::Epsilon){
      EXPECT_TRUE(fa.removeSymbol(c));
      EXPECT_FALSE(fa.hasSymbol(c));
      EXPECT_TRUE(fa.addSymbol(c));
      EXPECT_TRUE(fa.hasSymbol(c));
    }
  }
}

TEST(HasSymbolTest, Invalid){
  fa::Automaton fa;
  for (int i = 0; i<128; i++){
    char c = i;
    fa.addSymbol(c);
  }
  for (int i = 0; i<128; i++){
    char c = i;
    if (!(std::isgraph(c) || c == fa::Epsilon)){
      EXPECT_FALSE(fa.hasSymbol(c));
    }
  }
}

/**
 * std::size_t Automaton::countSymbols() const
 */

TEST(CountSymbolsTest, Empty){
  fa::Automaton fa;
  EXPECT_EQ(0u, fa.countSymbols());
}

TEST(CountSymbolsTest, OneSymbol){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('c'));
  EXPECT_EQ(1u, fa.countSymbols());
}

TEST(CountSymbolsTest, ManySymbols){
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

TEST(AddStateTest, New){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
}

TEST(AddStateTest, Zero){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(0));
}

TEST(AddStateTest, Negative){
  fa::Automaton fa;
  EXPECT_FALSE(fa.addState(-1));
}

TEST(AddStateTest, Existing){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_FALSE(fa.addState(1));
}

TEST(AddStateTest, Many){
  fa::Automaton fa;
  for (size_t i = 0; i<1000; i++){
    EXPECT_TRUE(fa.addState(i));
  }
}

/**
 * bool Automaton::removeState(int state)
 */

TEST(RemoveStateTest, Existing){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.removeState(1));
}

TEST(RemoveStateTest, NonExisting){
  fa::Automaton fa;
  EXPECT_FALSE(fa.removeState(1));

}

TEST(RemoveStateTest, Invalid){
  fa::Automaton fa;
  EXPECT_FALSE(fa.removeState(-1));
}

TEST(RemoveStateTest, Many){
  fa::Automaton fa;
  for (size_t i = 0; i<1000; i++){
    EXPECT_TRUE(fa.addState(i));
  }
  for (size_t i = 0; i<1000; i++){
    EXPECT_TRUE(fa.removeState(i));
  }
}

/**
 * bool Automaton::hasState(int state) const
 */

TEST(HasStateTest, Existing){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.hasState(1));
}

TEST(HasStateTest, NonExisting){
  fa::Automaton fa;
  EXPECT_FALSE(fa.hasState(1));
}

/**
 * std::size_t Automaton::countStates() const
 */

TEST(CountStatesTest, Zero){
  fa::Automaton fa;
  EXPECT_EQ(0u, fa.countStates());
}

TEST(CountStatesTest, One){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_EQ(1u, fa.countStates());
}

TEST(CountStatesTest, Many){
  fa::Automaton fa;
  for (size_t i = 0; i<1000; i++){
    EXPECT_TRUE(fa.addState(i));
  }
  EXPECT_EQ(1000u, fa.countStates());
}

/**
 * bool Automaton::isStateInitial(int state) const
 */

TEST(IsStateInitialTest, Initial){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  fa.setStateInitial(1);
  EXPECT_TRUE(fa.isStateInitial(1));
}

TEST(IsStateInitialTest, NonInitial){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_FALSE(fa.isStateInitial(1));
}

/**
 * bool Automaton::isStateFinal(int state) const
 */

TEST(IsStateFinalTest, Final){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  fa.setStateFinal(1);
  EXPECT_TRUE(fa.isStateFinal(1));
}

TEST(IsStateFinalTest, NonFinal){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_FALSE(fa.isStateFinal(1));
}

/**
 * bool Automaton::addTransition(int from, char alpha, int to)
 */

TEST(AddTransitionTest, New){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.hasTransition(1, 'a', 2));
}

TEST(AddTransitionTest, Existing){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_FALSE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.hasTransition(1, 'a', 2));
}

TEST(AddTransitionTest, InvalidFrom){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_FALSE(fa.addTransition(1, 'a', 2));
    EXPECT_FALSE(fa.hasTransition(1, 'a', 2));

}

TEST(AddTransitionTest, InvalidTo){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_FALSE(fa.addTransition(1, 'a', 2));
    EXPECT_FALSE(fa.hasTransition(1, 'a', 2));

}

TEST(AddTransitionTest, InvalidAlpha){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_FALSE(fa.addTransition(1, 'a', 2));
  EXPECT_FALSE(fa.hasTransition(1, 'a', 2));
}

/**
 * bool Automaton::removeTransition(in from, char alpha, int to)
 */

TEST(RemoveTransitionTest, Existing){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.removeTransition(1, 'a', 2));
}

TEST(RemoveTransitionTest, NonExisting){
  fa::Automaton fa;
  EXPECT_FALSE(fa.removeTransition(1, 'a', 2));
}

/**
 * bool Automaton::hasTransition(int from, char alpha, int to)
 */

TEST(HasTransitionTest, Existing){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.hasTransition(1, 'a', 2));
}

TEST(HasTransitionTest, NonExisting){
  fa::Automaton fa;
  EXPECT_FALSE(fa.hasTransition(1, 'a', 2));
}

TEST(HasTransitionTest, PointingToSelf){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.hasTransition(0, 'a', 0));
}


/**
 * std::size_t Automaton::countTransitions() const
 */

TEST(CountTransitionsTest, Zero){
  fa::Automaton fa;
  EXPECT_EQ(0u, fa.countTransitions());
}

TEST(CountTransitionsTest, One){
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

TEST(PrettyPrintTest, Empty){
  fa::Automaton fa;
  fa.prettyPrint(std::cout);
}

TEST(PrettyPrintTest, Stuffed){
  fa::Automaton fa = initalAutomaton();
  fa.prettyPrint(std::cout);
}

/**
 * bool hasEpsilonTransition() const
 */

TEST(HasEpsilonTransitionTest, Has){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addSymbol(fa::Epsilon));
  EXPECT_TRUE(fa.addTransition(1, fa::Epsilon, 2));
  EXPECT_TRUE(fa.hasTransition(1, fa::Epsilon, 2));
  EXPECT_TRUE(fa.hasEpsilonTransition());
}

TEST(HasEpsilonTransitionTest, HasNot){
  fa::Automaton fa = initalAutomaton();
  EXPECT_FALSE(fa.hasEpsilonTransition());
}

/**
 * bool isDeterministic() const
 */

TEST(IsDeterministicTest, Deterministic){
  fa::Automaton fa = deterministicAutomaton1();
  EXPECT_TRUE(fa.isDeterministic());
}

TEST(IsDeterministicTest, Complete){
  fa::Automaton fa = completeAutomaton1();
  EXPECT_FALSE(fa.isDeterministic());
}

TEST(IsDeterministicTest, Both1){
  fa::Automaton fa = deterministicCompleteAutomaton1();
  EXPECT_TRUE(fa.isDeterministic());
}

TEST(IsDeterministicTest, Both2){
  fa::Automaton fa = deterministicCompleteAutomaton2();
  EXPECT_TRUE(fa.isDeterministic());
}

TEST(IsDeterministicTest, Neither){
  fa::Automaton fa = initalAutomaton();
  EXPECT_FALSE(fa.isDeterministic());
}

/**
 * bool isComplete() const
 */

TEST(IsCompleteTest, Deterministic){
  fa::Automaton fa = deterministicAutomaton1();
  EXPECT_FALSE(fa.isComplete());
}

TEST(IsCompleteTest, Complete){
  fa::Automaton fa = completeAutomaton1();
  EXPECT_TRUE(fa.isComplete());
}

TEST(IsCompleteTest, Both1){
  fa::Automaton fa = deterministicCompleteAutomaton1();
  EXPECT_TRUE(fa.isComplete());
}

TEST(IsCompleteTest, Both2){
  fa::Automaton fa = deterministicCompleteAutomaton2();
  EXPECT_TRUE(fa.isComplete());
}

TEST(IsCompleteTest, Neither){
  fa::Automaton fa = initalAutomaton();
  EXPECT_FALSE(fa.isComplete());
}

/**
 * static Automaton createComplete(const Automaton& automaton)
 */

TEST(CreateCompleteTest, AlreadyComplete){
  fa::Automaton fa1 = completeAutomaton1();
  fa::Automaton fa2 = fa::Automaton::createComplete(fa1);
  EXPECT_TRUE(fa1.isComplete());
  EXPECT_TRUE(fa2.isComplete());
}

TEST(CreateCompleteTest, NotComplete){
  fa::Automaton fa1 = deterministicAutomaton1();
  fa::Automaton fa2 = fa::Automaton::createComplete(fa1);
  EXPECT_FALSE(fa1.isComplete());
  EXPECT_TRUE(fa2.isComplete());
}

/**
 * static Automaton createComplement(const Automaton& automaton)
 */

TEST(CreateComplementTest, Deterministic){
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

TEST(CreateComplementTest, Complete){
  // TO DO
  std::cout << "!!!  !!!  TO DO  !!!  !!!\n";
}

TEST(CreateComplementTest, Both1){
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

TEST(CreateComplementTest, Both2){
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

TEST(CreateComplementTest, Neither){
  // TO DO
  std::cout << "!!!  !!!  TO DO  !!!  !!!\n";
}

/**
 * static Automaton createMirror(const Automaton& automaton)
 */

TEST(CreateMirrorTest, Deterministic){
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

TEST(CreateMirrorTest, Complete){
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

TEST(CreateMirrorTest, Both1){
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

TEST(CreateMirrorTest, Both2){
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

TEST(CreateMirrorTest, Neither){
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

TEST(MakeTransitionTest, Deterministic){
  fa::Automaton fa = deterministicAutomaton1();
  std::set<int> origin, setA, setB;
  origin.insert(0);
  setA = fa.makeTransition(origin, 'a');
  setB = fa.makeTransition(origin, 'b');
  EXPECT_EQ(0, setA.size());
  EXPECT_EQ(1, setB.size());
  EXPECT_EQ(1, setB.count(1));
  origin = setB;
  setA = fa.makeTransition(origin, 'a');
  setB = fa.makeTransition(origin, 'b');
  EXPECT_EQ(1, setA.size());
  EXPECT_EQ(1, setA.count(2));
  EXPECT_EQ(0, setB.size());
  origin = setA;
  setA = fa.makeTransition(origin, 'a');
  setB = fa.makeTransition(origin, 'b');
  EXPECT_EQ(1, setA.size());
  EXPECT_EQ(1, setA.count(2));
  EXPECT_EQ(1, setB.size());
  EXPECT_EQ(1, setB.count(3));
}

TEST(MakeTransitionTest, Complete){
  fa::Automaton fa = completeAutomaton1();
  std::set<int> origin, setA, setB;
  origin.insert(0);
  setA = fa.makeTransition(origin, 'a');
  setB = fa.makeTransition(origin, 'b');
  EXPECT_EQ(2, setA.size());
  EXPECT_EQ(1, setA.count(0));
  EXPECT_EQ(1, setA.count(2));
  EXPECT_EQ(2, setB.size());
  EXPECT_EQ(1, setB.count(0));
  EXPECT_EQ(1, setB.count(1));
  origin = setA;
  setA = fa.makeTransition(origin, 'a');
  setB = fa.makeTransition(origin, 'b');
  EXPECT_EQ(3, setA.size());
  EXPECT_EQ(1, setA.count(0));
  EXPECT_EQ(1, setA.count(2));
  EXPECT_EQ(1, setA.count(3));
  EXPECT_EQ(3, setB.size());
  EXPECT_EQ(1, setB.count(0));
  EXPECT_EQ(1, setB.count(1));
  EXPECT_EQ(1, setB.count(3));
  origin = setA;
  setA = fa.makeTransition(origin, 'a');
  setB = fa.makeTransition(origin, 'b');
  EXPECT_EQ(1, setA.count(0));
  EXPECT_EQ(1, setA.count(2));
  EXPECT_EQ(1, setA.count(3));
  EXPECT_EQ(3, setB.size());
  EXPECT_EQ(1, setB.count(0));
  EXPECT_EQ(1, setB.count(1));
  EXPECT_EQ(1, setB.count(3));
  origin = setB;
  setA = fa.makeTransition(origin, 'a');
  setB = fa.makeTransition(origin, 'b');
  EXPECT_EQ(3, setA.size());
  EXPECT_EQ(1, setA.count(0));
  EXPECT_EQ(1, setA.count(2));
  EXPECT_EQ(1, setA.count(3));
  EXPECT_EQ(3, setB.size());
  EXPECT_EQ(1, setB.count(0));
  EXPECT_EQ(1, setB.count(1));
  EXPECT_EQ(1, setB.count(3));
}

TEST(MakeTransitionTest, Both1){
  fa::Automaton fa = deterministicCompleteAutomaton1();
  std::set<int> origin, setA, setB;
  origin.insert(0);
  setA = fa.makeTransition(origin, 'a');
  setB = fa.makeTransition(origin, 'b');
  EXPECT_EQ(1, setA.size());
  EXPECT_EQ(1, setA.count(0));
  EXPECT_EQ(1, setB.size());
  EXPECT_EQ(1, setB.count(1));
  origin = setB;
  setA = fa.makeTransition(origin, 'a');
  setB = fa.makeTransition(origin, 'b');
  EXPECT_EQ(1, setA.size());
  EXPECT_EQ(1, setA.count(1));
  EXPECT_EQ(1, setB.size());
  EXPECT_EQ(1, setB.count(0));
}

TEST(MakeTransitionTest, Both2){
  fa::Automaton fa = deterministicCompleteAutomaton2();
  std::set<int> origin, setA, setB;
  origin.insert(0);
  setA = fa.makeTransition(origin, 'a');
  setB = fa.makeTransition(origin, 'b');
  EXPECT_EQ(1, setA.size());
  EXPECT_EQ(1, setA.count(4));
  EXPECT_EQ(1, setB.size());
  EXPECT_EQ(1, setB.count(1));
  origin = setA;
  setA = fa.makeTransition(origin, 'a');
  setB = fa.makeTransition(origin, 'b');
  EXPECT_EQ(1, setA.size());
  EXPECT_EQ(1, setA.count(4));
  EXPECT_EQ(1, setB.size());
  EXPECT_EQ(1, setB.count(4));
  origin.clear();
  origin.insert(0);
  origin = fa.makeTransition(origin, 'b');
  setA = fa.makeTransition(origin, 'a');
  setB = fa.makeTransition(origin, 'b');
  EXPECT_EQ(1, setA.size());
  EXPECT_EQ(1, setA.count(2));
  EXPECT_EQ(1, setB.size());
  EXPECT_EQ(1, setB.count(4));
  origin = setA;
  setA = fa.makeTransition(origin, 'a');
  setB = fa.makeTransition(origin, 'b');
  EXPECT_EQ(1, setA.size());
  EXPECT_EQ(1, setA.count(2));
  EXPECT_EQ(1, setB.size());
  EXPECT_EQ(1, setB.count(3));
  origin = setB;
  setA = fa.makeTransition(origin, 'a');
  setB = fa.makeTransition(origin, 'b');
  EXPECT_EQ(1, setA.size());
  EXPECT_EQ(1, setA.count(4));
  EXPECT_EQ(1, setB.size());
  EXPECT_EQ(1, setB.count(4));
}

TEST(MakeTransitionTest, Neither){
  fa::Automaton fa = initalAutomaton();
  std::set<int> origin, setA, setB;
  origin.insert(0);
  origin.insert(1);
  setA = fa.makeTransition(origin, 'a');
  setB = fa.makeTransition(origin, 'b');
  EXPECT_EQ(3, setA.size());
  EXPECT_EQ(1, setA.count(1));
  EXPECT_EQ(1, setA.count(2));
  EXPECT_EQ(1, setA.count(3));
  EXPECT_EQ(1, setB.size());
  EXPECT_EQ(1, setB.count(3));
  origin = setA;
  setA = fa.makeTransition(origin, 'a');
  setB = fa.makeTransition(origin, 'b');
  EXPECT_EQ(1, setA.size());
  EXPECT_EQ(1, setA.count(3));
  EXPECT_EQ(2, setB.size());
  EXPECT_EQ(1, setB.count(3));
  EXPECT_EQ(1, setB.count(4));
  origin = setA;
  setA = fa.makeTransition(origin, 'a');
  setB = fa.makeTransition(origin, 'b');
  EXPECT_EQ(1, setA.size());
  EXPECT_EQ(1, setA.count(3));
  EXPECT_EQ(1, setB.size());
  EXPECT_EQ(1, setB.count(4));
  origin = setB;
  setA = fa.makeTransition(origin, 'a');
  setB = fa.makeTransition(origin, 'b');
  EXPECT_EQ(1, setA.size());
  EXPECT_EQ(1, setA.count(4));
  EXPECT_EQ(0, setB.size());
  origin.clear();
  origin.insert(0);
  origin.insert(1);
  origin = fa.makeTransition(origin, 'a');
  origin = fa.makeTransition(origin, 'b');
  setA = fa.makeTransition(origin, 'a');
  setB = fa.makeTransition(origin, 'b');
  EXPECT_EQ(2, setA.size());
  EXPECT_EQ(1, setA.count(3));
  EXPECT_EQ(1, setA.count(4));
  EXPECT_EQ(1, setB.size());
  EXPECT_EQ(1, setB.count(4));
}

/**
 * std::set<int> readString(const std::string& word)
 */

TEST(ReadStringTest, ZeroWORD1){
  fa::Automaton fa;
  std::set<int> res = fa.readString(WORD1);
  EXPECT_EQ(0, res.size());
}

TEST(ReadStringTest, ZeroWORD2){
  fa::Automaton fa;
  std::set<int> res = fa.readString(WORD2);
  EXPECT_EQ(0, res.size());
}

TEST(ReadStringTest, ZeroWORD3){
  fa::Automaton fa;
  std::set<int> res = fa.readString(WORD3);
  EXPECT_EQ(0, res.size());
}

TEST(ReadStringTest, ZeroWORD4){
  fa::Automaton fa;
  std::set<int> res = fa.readString(WORD4);
  EXPECT_EQ(0, res.size());
}

TEST(ReadStringTest, DeterministicWORD1){
  fa::Automaton fa = deterministicAutomaton1();
  std::set<int> res = fa.readString(WORD1);
  EXPECT_EQ(0, res.size());
}

TEST(ReadStringTest, DeterministicWORD2){
  fa::Automaton fa = deterministicAutomaton1();
  std::set<int> res = fa.readString(WORD2);
  EXPECT_EQ(1, res.size());
  EXPECT_EQ(1, res.count(3));
}

TEST(ReadStringTest, DeterministicWORD3){
  fa::Automaton fa = deterministicAutomaton1();
  std::set<int> res = fa.readString(WORD3);
  EXPECT_EQ(0, res.size());
}

TEST(ReadStringTest, DeterministicWORD4){
  fa::Automaton fa = deterministicAutomaton1();
  std::set<int> res = fa.readString(WORD4);
  EXPECT_EQ(0, res.size());
}

TEST(ReadStringTest, CompleteWORD1){
  fa::Automaton fa = completeAutomaton1();
  std::set<int> res = fa.readString(WORD1);
  EXPECT_EQ(3, res.size());
  EXPECT_EQ(1, res.count(0));
  EXPECT_EQ(1, res.count(1));
  EXPECT_EQ(1, res.count(3));
}

TEST(ReadStringTest, CompleteWORD2){
  fa::Automaton fa = completeAutomaton1();
  std::set<int> res = fa.readString(WORD2);
  EXPECT_EQ(3, res.size());
  EXPECT_EQ(1, res.count(0));
  EXPECT_EQ(1, res.count(1));
  EXPECT_EQ(1, res.count(3));
}

TEST(ReadStringTest, CompleteWORD3){
  fa::Automaton fa = completeAutomaton1();
  std::set<int> res = fa.readString(WORD3);
  EXPECT_EQ(3, res.size());
  EXPECT_EQ(1, res.count(0));
  EXPECT_EQ(1, res.count(2));
  EXPECT_EQ(1, res.count(3));
}

TEST(ReadStringTest, CompleteWORD4){
  fa::Automaton fa = completeAutomaton1();
  std::set<int> res = fa.readString(WORD4);
  EXPECT_EQ(3, res.size());
  EXPECT_EQ(1, res.count(0));
  EXPECT_EQ(1, res.count(2));
  EXPECT_EQ(1, res.count(3));
}

TEST(ReadStringTest, Both1WORD1){
  fa::Automaton fa = deterministicCompleteAutomaton1();
  std::set<int> res = fa.readString(WORD1);
  EXPECT_EQ(1, res.size());
  EXPECT_EQ(1, res.count(0));
}

TEST(ReadStringTest, Both1WORD2){
  fa::Automaton fa = deterministicCompleteAutomaton1();
  std::set<int> res = fa.readString(WORD2);
  EXPECT_EQ(1, res.size());
  EXPECT_EQ(1, res.count(0));
}

TEST(ReadStringTest, Both1WORD3){
  fa::Automaton fa = deterministicCompleteAutomaton1();
  std::set<int> res = fa.readString(WORD3);
  EXPECT_EQ(1, res.size());
  EXPECT_EQ(1, res.count(1));
}

TEST(ReadStringTest, Both1WORD4){
  fa::Automaton fa = deterministicCompleteAutomaton1();
  std::set<int> res = fa.readString(WORD4);
  EXPECT_EQ(1, res.size());
  EXPECT_EQ(1, res.count(0));
}

TEST(ReadStringTest, Both2WORD1){
  fa::Automaton fa = deterministicCompleteAutomaton2();
  std::set<int> res = fa.readString(WORD1);
  EXPECT_EQ(1, res.size());
  EXPECT_EQ(1, res.count(4));
}

TEST(ReadStringTest, Both2WORD2){
  fa::Automaton fa = deterministicCompleteAutomaton2();
  std::set<int> res = fa.readString(WORD2);
  EXPECT_EQ(1, res.size());
  EXPECT_EQ(1, res.count(3));
}

TEST(ReadStringTest, Both2WORD3){
  fa::Automaton fa = deterministicCompleteAutomaton2();
  std::set<int> res = fa.readString(WORD3);
  EXPECT_EQ(1, res.size());
  EXPECT_EQ(1, res.count(4));
}

TEST(ReadStringTest, Both2WORD4){
  fa::Automaton fa = deterministicCompleteAutomaton2();
  std::set<int> res = fa.readString(WORD4);
  EXPECT_EQ(1, res.size());
  EXPECT_EQ(1, res.count(4));
}

TEST(ReadStringTest, NeitherWORD1){
  fa::Automaton fa = initalAutomaton();
  std::set<int> res = fa.readString(WORD1);
  EXPECT_EQ(0, res.size());
}

TEST(ReadStringTest, NeitherWORD2){
  fa::Automaton fa = initalAutomaton();
  std::set<int> res = fa.readString(WORD2);
  EXPECT_EQ(1, res.size());
  EXPECT_EQ(1, res.count(4));
}

TEST(ReadStringTest, NeitherWORD3){
  fa::Automaton fa = initalAutomaton();
  std::set<int> res = fa.readString(WORD3);
  EXPECT_EQ(1, res.size());
  EXPECT_EQ(1, res.count(4));
}

TEST(ReadStringTest, NeitherWORD4){
  fa::Automaton fa = initalAutomaton();
  std::set<int> res = fa.readString(WORD4);
  EXPECT_EQ(1, res.size());
  EXPECT_EQ(1, res.count(3));
}

/**
 * bool match(const std::string& word) const
 */

TEST(matchTest, ZeroWORD1){
  fa::Automaton fa;
  EXPECT_FALSE(fa.match(WORD1));
}

TEST(matchTest, ZeroWORD2){
  fa::Automaton fa;
  EXPECT_FALSE(fa.match(WORD2));
}

TEST(matchTest, ZeroWORD3){
  fa::Automaton fa;
  EXPECT_FALSE(fa.match(WORD3));
}

TEST(matchTest, ZeroWORD4){
  fa::Automaton fa;
  EXPECT_FALSE(fa.match(WORD4));
}

TEST(matchTest, DeterministicWORD1){
  fa::Automaton fa = deterministicAutomaton1();
  EXPECT_FALSE(fa.match(WORD1));
}

TEST(matchTest, DeterministicWORD2){
  fa::Automaton fa = deterministicAutomaton1();
  EXPECT_TRUE(fa.match(WORD2));
}

TEST(matchTest, DeterministicWORD3){
  fa::Automaton fa = deterministicAutomaton1();
  EXPECT_FALSE(fa.match(WORD3));
}

TEST(matchTest, DeterministicWORD4){
  fa::Automaton fa = deterministicAutomaton1();
  EXPECT_FALSE(fa.match(WORD4));
}

TEST(matchTest, CompleteWORD1){
  fa::Automaton fa = completeAutomaton1();
  EXPECT_TRUE(fa.match(WORD1));
}

TEST(matchTest, CompleteWORD2){
  fa::Automaton fa = completeAutomaton1();
  EXPECT_TRUE(fa.match(WORD2));
}

TEST(matchTest, CompleteWORD3){
  fa::Automaton fa = completeAutomaton1();
  EXPECT_TRUE(fa.match(WORD3));
}

TEST(matchTest, CompleteWORD4){
  fa::Automaton fa = completeAutomaton1();
  EXPECT_TRUE(fa.match(WORD4));
}

TEST(matchTest, Both1WORD1){
  fa::Automaton fa = deterministicCompleteAutomaton1();
  EXPECT_FALSE(fa.match(WORD1));
}

TEST(matchTest, Both1WORD2){
  fa::Automaton fa = deterministicCompleteAutomaton1();
  EXPECT_FALSE(fa.match(WORD2));
}

TEST(matchTest, Both1WORD3){
  fa::Automaton fa = deterministicCompleteAutomaton1();
  EXPECT_TRUE(fa.match(WORD3));
}

TEST(matchTest, Both1WORD4){
  fa::Automaton fa = deterministicCompleteAutomaton1();
  EXPECT_FALSE(fa.match(WORD4));
}

TEST(matchTest, Both2WORD1){
  fa::Automaton fa = deterministicCompleteAutomaton2();
  EXPECT_FALSE(fa.match(WORD1));
}

TEST(matchTest, Both2WORD2){
  fa::Automaton fa = deterministicCompleteAutomaton2();
  EXPECT_TRUE(fa.match(WORD2));
}

TEST(matchTest, Both2WORD3){
  fa::Automaton fa = deterministicCompleteAutomaton2();
  EXPECT_FALSE(fa.match(WORD3));
}

TEST(matchTest, Both2WORD4){
  fa::Automaton fa = deterministicCompleteAutomaton2();
  EXPECT_FALSE(fa.match(WORD4));
}

TEST(matchTest, NeitherWORD1){
  fa::Automaton fa = initalAutomaton();
  EXPECT_FALSE(fa.match(WORD1));
}

TEST(matchTest, NeitherWORD2){
  fa::Automaton fa = initalAutomaton();
  EXPECT_TRUE(fa.match(WORD2));
}

TEST(matchTest, NeitherWORD3){
  fa::Automaton fa = initalAutomaton();
  EXPECT_TRUE(fa.match(WORD3));
}

TEST(matchTest, NeitherWORD4){
  fa::Automaton fa = initalAutomaton();
  EXPECT_FALSE(fa.match(WORD4));
}

/**
 * main
 */

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
