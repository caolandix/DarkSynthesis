#-----------------------------------------------
#
# Project created by QtCreator 2015-07-25T23:21:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DarkSynthesis
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x

INCLUDEPATH = ./boost_1_59_0

SOURCES += main.cpp \
    cmainwindow.cpp \
    node.cpp \
    edge.cpp \
    graphwidget.cpp \
    cartesiangraph.cpp \
    physparticle.cpp \
    cartesianlabel.cpp \
    cartesiangraphsettingsdlg.cpp \
    physvector.cpp \
    cartesiangraphdataobj.cpp \
    physbaseitem.cpp \
    physobjectnavigator.cpp \
    comboboxdelegate.cpp \
    spinboxdelegate.cpp \
    physmodulenavigator.cpp \
    physoutputnavigator.cpp \
    physobjectpropsnavigator.cpp \
    physmodule.cpp \
    physeqsolver.cpp \
    physprintview.cpp \
    physeqsolverdelegate.cpp \
    physeqsolveritem.cpp \
    physvectordataobj.cpp \
    physparticledataobj.cpp \
    xes1/es1.cpp \
    xes1/fft.cpp \
    xes1/fields.cpp \
    xes1/init.cpp \
    xes1/initwin.cpp \
    xes1/move.cpp \
    xes1/set.cpp \
    xes1/physelectrostatic.cpp \
    xes1/accel.cpp \
    jumpdrive/CustomFunction.cpp \
    jumpdrive/CustomOperator.cpp \
    jumpdrive/ExpressionBuilder.cpp \
    jumpdrive/ExpressionUtil.cpp \
    jumpdrive/FunctionToken.cpp \
    jumpdrive/IllegalArgumentException.cpp \
    jumpdrive/NumberToken.cpp \
    jumpdrive/OperatorToken.cpp \
    jumpdrive/ParenthesisToken.cpp \
    jumpdrive/RPNConverter.cpp \
    jumpdrive/RPNExpression.cpp \
    jumpdrive/Token.cpp \
    jumpdrive/Tokenizer.cpp \
    jumpdrive/ValueSet.cpp \
    physobjectpropdelegate.cpp \
    physobjectpropeditor.cpp \
    physctrldoublespinboxdelegate.cpp \
    physctrldoublespinbox.cpp

HEADERS  += cmainwindow.h \
    node.h \
    edge.h \
    graphwidget.h \
    cartesiangraph.h \
    physparticle.h \
    cartesianlabel.h \
    cartesiangraphsettingsdlg.h \
    physvector.h \
    cartesiangraphdataobj.h \
    physbaseitem.h \
    physobjectnavigator.h \
    comboboxdelegate.h \
    spinboxdelegate.h \
    physmodulenavigator.h \
    physoutputnavigator.h \
    physobjectpropsnavigator.h \
    physmodule.h \
    physscience.h \
    physeqsolver.h \
    physprintview.h \
    physeqsolverdelegate.h \
    physeqsolveritem.h \
    physvectordataobj.h \
    physparticledataobj.h \
    xes1/es1.h \
    xes1/physelectrostatic.h \
    jumpdrive/ArithmeticException.h \
    jumpdrive/Calculable.h \
    jumpdrive/commondefs.h \
    jumpdrive/CustomFunction.h \
    jumpdrive/CustomFunctionABS.h \
    jumpdrive/CustomFunctionACOS.h \
    jumpdrive/CustomFunctionASIN.h \
    jumpdrive/CustomFunctionATAN.h \
    jumpdrive/CustomFunctionCBRT.h \
    jumpdrive/CustomFunctionCEILING.h \
    jumpdrive/CustomFunctionCOS.h \
    jumpdrive/CustomFunctionCOSH.h \
    jumpdrive/CustomFunctionEXP.h \
    jumpdrive/CustomFunctionEXPM1.h \
    jumpdrive/CustomFunctionFLOOR.h \
    jumpdrive/CustomFunctionLOG.h \
    jumpdrive/CustomFunctions.h \
    jumpdrive/CustomFunctionSIN.h \
    jumpdrive/CustomFunctionSINH.h \
    jumpdrive/CustomFunctionSQRT.h \
    jumpdrive/CustomFunctionTAN.h \
    jumpdrive/CustomFunctionTANH.h \
    jumpdrive/CustomOperator.h \
    jumpdrive/CustomOperatorAdd.h \
    jumpdrive/CustomOperatorDiv.h \
    jumpdrive/CustomOperatorMod.h \
    jumpdrive/CustomOperatorMult.h \
    jumpdrive/CustomOperatorPow.h \
    jumpdrive/CustomOperators.h \
    jumpdrive/CustomOperatorSub.h \
    jumpdrive/CustomOperatorUMin.h \
    jumpdrive/ExpressionBuilder.h \
    jumpdrive/ExpressionUtil.h \
    jumpdrive/FunctionSeparatorToken.h \
    jumpdrive/FunctionToken.h \
    jumpdrive/IllegalArgumentException.h \
    jumpdrive/InvalidCustomFunctionException.h \
    jumpdrive/jumpdrivedefs.h \
    jumpdrive/NumberToken.h \
    jumpdrive/OperatorToken.h \
    jumpdrive/ParenthesisToken.h \
    jumpdrive/RPNConverter.h \
    jumpdrive/RPNExpression.h \
    jumpdrive/Token.h \
    jumpdrive/Tokenizer.h \
    jumpdrive/UnparsableExpressionException.h \
    jumpdrive/ValueSet.h \
    jumpdrive/VariableToken.h \
    physobjectpropdelegate.h \
    physobjectpropeditor.h \
    physctrldoublespinboxdelegate.h \
    physctrldoublespinbox.h

FORMS    += cmainwindow.ui \
    cartesiangraphsettingsdlg.ui
