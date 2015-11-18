#-----------------------------------------------
#
# Project created by QtCreator 2015-07-25T23:21:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DarkSynthesis
TEMPLATE = app


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
    physctrllineedit.cpp \
    physctrldoublespinbox.cpp \
    jumpdrive/src/jumpdrive/CustomFunction.cpp \
    jumpdrive/src/jumpdrive/CustomOperator.cpp \
    jumpdrive/src/jumpdrive/ExpressionBuilder.cpp \
    jumpdrive/src/jumpdrive/ExpressionUtil.cpp \
    jumpdrive/src/jumpdrive/FunctionToken.cpp \
    jumpdrive/src/jumpdrive/IllegalArgumentException.cpp \
    jumpdrive/src/jumpdrive/NumberToken.cpp \
    jumpdrive/src/jumpdrive/OperatorToken.cpp \
    jumpdrive/src/jumpdrive/ParenthesisToken.cpp \
    jumpdrive/src/jumpdrive/RPNConverter.cpp \
    jumpdrive/src/jumpdrive/RPNExpression.cpp \
    jumpdrive/src/jumpdrive/Token.cpp \
    jumpdrive/src/jumpdrive/Tokenizer.cpp \
    jumpdrive/src/jumpdrive/ValueSet.cpp \
    jumpdrive/src/main/main.cpp \
    jumpdrive/main/main.cpp \
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
    jumpdrive/ValueSet.cpp

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
    physctrllineedit.h \
    physctrldoublespinbox.h \
    jumpdrive/src/jumpdrive/ArithmeticException.h \
    jumpdrive/src/jumpdrive/Calculable.h \
    jumpdrive/src/jumpdrive/commondefs.h \
    jumpdrive/src/jumpdrive/CustomFunction.h \
    jumpdrive/src/jumpdrive/CustomFunctionABS.h \
    jumpdrive/src/jumpdrive/CustomFunctionACOS.h \
    jumpdrive/src/jumpdrive/CustomFunctionASIN.h \
    jumpdrive/src/jumpdrive/CustomFunctionATAN.h \
    jumpdrive/src/jumpdrive/CustomFunctionCBRT.h \
    jumpdrive/src/jumpdrive/CustomFunctionCEILING.h \
    jumpdrive/src/jumpdrive/CustomFunctionCOS.h \
    jumpdrive/src/jumpdrive/CustomFunctionCOSH.h \
    jumpdrive/src/jumpdrive/CustomFunctionEXP.h \
    jumpdrive/src/jumpdrive/CustomFunctionEXPM1.h \
    jumpdrive/src/jumpdrive/CustomFunctionFLOOR.h \
    jumpdrive/src/jumpdrive/CustomFunctionLOG.h \
    jumpdrive/src/jumpdrive/CustomFunctions.h \
    jumpdrive/src/jumpdrive/CustomFunctionSIN.h \
    jumpdrive/src/jumpdrive/CustomFunctionSINH.h \
    jumpdrive/src/jumpdrive/CustomFunctionSQRT.h \
    jumpdrive/src/jumpdrive/CustomFunctionTAN.h \
    jumpdrive/src/jumpdrive/CustomFunctionTANH.h \
    jumpdrive/src/jumpdrive/CustomOperator.h \
    jumpdrive/src/jumpdrive/CustomOperatorAdd.h \
    jumpdrive/src/jumpdrive/CustomOperatorDiv.h \
    jumpdrive/src/jumpdrive/CustomOperatorMod.h \
    jumpdrive/src/jumpdrive/CustomOperatorMult.h \
    jumpdrive/src/jumpdrive/CustomOperatorPow.h \
    jumpdrive/src/jumpdrive/CustomOperators.h \
    jumpdrive/src/jumpdrive/CustomOperatorSub.h \
    jumpdrive/src/jumpdrive/CustomOperatorUMin.h \
    jumpdrive/src/jumpdrive/ExpressionBuilder.h \
    jumpdrive/src/jumpdrive/ExpressionUtil.h \
    jumpdrive/src/jumpdrive/FunctionSeparatorToken.h \
    jumpdrive/src/jumpdrive/FunctionToken.h \
    jumpdrive/src/jumpdrive/IllegalArgumentException.h \
    jumpdrive/src/jumpdrive/InvalidCustomFunctionException.h \
    jumpdrive/src/jumpdrive/jumpdrivedefs.h \
    jumpdrive/src/jumpdrive/NumberToken.h \
    jumpdrive/src/jumpdrive/OperatorToken.h \
    jumpdrive/src/jumpdrive/ParenthesisToken.h \
    jumpdrive/src/jumpdrive/RPNConverter.h \
    jumpdrive/src/jumpdrive/RPNExpression.h \
    jumpdrive/src/jumpdrive/Token.h \
    jumpdrive/src/jumpdrive/Tokenizer.h \
    jumpdrive/src/jumpdrive/UnparsableExpressionException.h \
    jumpdrive/src/jumpdrive/ValueSet.h \
    jumpdrive/src/jumpdrive/VariableToken.h \
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
    jumpdrive/VariableToken.h

FORMS    += cmainwindow.ui \
    cartesiangraphsettingsdlg.ui
