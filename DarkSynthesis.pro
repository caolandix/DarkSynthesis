#-----------------------------------------------
#
# Project created by QtCreator 2015-07-25T23:21:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = DarkSynthesis
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x -Wall

INCLUDEPATH = ./boost_1_59_0

SOURCES += main.cpp \
    cmainwindow.cpp \
    graphwidget.cpp \
    cartesiangraph.cpp \
    physparticle.cpp \
    cartesianlabel.cpp \
    cartesiangraphsettingsdlg.cpp \
    physvector.cpp \
    cartesiangraphdataobj.cpp \
    physbaseitem.cpp \
    physobjectnavigator.cpp \
    physmodulenavigator.cpp \
    physoutputnavigator.cpp \
    physobjectpropsnavigator.cpp \
    physmodule.cpp \
    physprintview.cpp \
    physeqsolverdelegate.cpp \
    physeqsolveritem.cpp \
    physvectordataobj.cpp \
    physparticledataobj.cpp \
    xes1/physelectrostatic.cpp \
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
    physeqsolvertable.cpp \
    physeqgrid.cpp \
    physeqgridcell.cpp \
    physeqrow.cpp \
    physeqsolvertableheader.cpp \
    physscience.cpp \
    physdataobj.cpp \
    physdockedwidget.cpp \
    physcommon.cpp \
    jumpdrive/customfunctiondifferentiate.cpp \
    jumpdrive/customfunctionintegrate.cpp \
    physcalculatetimer.cpp \
    phystimeslicedataobj.cpp \
    physcelldataobj.cpp \
    stargate7.cpp \
    xes1/physelectrostaticpropertiesdlg.cpp \
    qcustomplot-1.3.2/qcustomplot.cpp \
    xes1/physelectrostaticview.cpp \
    physeqrowdlg.cpp \
    modulenavigator.cpp \
    physmodulenavigatormodel.cpp \
    objectnavigator.cpp \
    physobjectpropsnavigatordock.cpp \
    physequationsolverdock.cpp \
    physoutputnavigatordock.cpp

HEADERS  += cmainwindow.h \
    graphwidget.h \
    cartesiangraph.h \
    physparticle.h \
    cartesianlabel.h \
    cartesiangraphsettingsdlg.h \
    physvector.h \
    cartesiangraphdataobj.h \
    physbaseitem.h \
    physobjectnavigator.h \
    physmodulenavigator.h \
    physoutputnavigator.h \
    physobjectpropsnavigator.h \
    physmodule.h \
    physscience.h \
    physprintview.h \
    physeqsolverdelegate.h \
    physeqsolveritem.h \
    physvectordataobj.h \
    physparticledataobj.h \
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
    physeqsolvertable.h \
    physeqgrid.h \
    physeqgridcell.h \
    physeqrow.h \
    physeqsolvertableheader.h \
    physdataobj.h \
    physdockedwidget.h \
    physcommon.h \
    jumpdrive/customfunctiondifferentiate.h \
    jumpdrive/customfunctionintegrate.h \
    physcalculatetimer.h \
    phystimeslicedataobj.h \
    physcelldataobj.h \
    stargate7.h \
    qcustomplot-1.3.2/qcustomplot.h \
    xes1/physelectrostaticpropertiesdlg.h \
    xes1/physelectrostaticview.h \
    physeqrowdlg.h \
    SymbolicC++3-3.35/headers/symbolic/constants.h \
    SymbolicC++3-3.35/headers/symbolic/equation.h \
    SymbolicC++3-3.35/headers/symbolic/functions.h \
    SymbolicC++3-3.35/headers/symbolic/integrate.h \
    SymbolicC++3-3.35/headers/symbolic/number.h \
    SymbolicC++3-3.35/headers/symbolic/product.h \
    SymbolicC++3-3.35/headers/symbolic/solve.h \
    SymbolicC++3-3.35/headers/symbolic/sum.h \
    SymbolicC++3-3.35/headers/symbolic/symbol.h \
    SymbolicC++3-3.35/headers/symbolic/symbolic.h \
    SymbolicC++3-3.35/headers/symbolic/symbolicc++.h \
    SymbolicC++3-3.35/headers/symbolic/symerror.h \
    SymbolicC++3-3.35/headers/symbolic/symmatrix.h \
    SymbolicC++3-3.35/headers/array.h \
    SymbolicC++3-3.35/headers/cloning.h \
    SymbolicC++3-3.35/headers/derive.h \
    SymbolicC++3-3.35/headers/identity.h \
    SymbolicC++3-3.35/headers/matnorm.h \
    SymbolicC++3-3.35/headers/matrix.h \
    SymbolicC++3-3.35/headers/multinomial.h \
    SymbolicC++3-3.35/headers/polynomial.h \
    SymbolicC++3-3.35/headers/quatern.h \
    SymbolicC++3-3.35/headers/rational.h \
    SymbolicC++3-3.35/headers/symbolicc++.h \
    SymbolicC++3-3.35/headers/vecnorm.h \
    SymbolicC++3-3.35/headers/vector.h \
    SymbolicC++3-3.35/headers/verylong.h \
    SymbolicC++3-3.35/lisp/lambda/builtin_arith.h \
    SymbolicC++3-3.35/lisp/lambda/builtin_core.h \
    SymbolicC++3-3.35/lisp/lambda/builtin_io.h \
    SymbolicC++3-3.35/lisp/lambda/builtin_list.h \
    SymbolicC++3-3.35/lisp/lambda/builtin_math.h \
    SymbolicC++3-3.35/lisp/lambda/expression.h \
    SymbolicC++3-3.35/lisp/lisp.h \
    modulenavigator.h \
    physmodulenavigatormodel.h \
    objectnavigator.h \
    physobjectpropsnavigatordock.h \
    physequationsolverdock.h \
    physoutputnavigatordock.h

FORMS    += cmainwindow.ui \
    cartesiangraphsettingsdlg.ui \
    physselectparticledlg.ui \
    xes1/physelectrostaticpropertiesdlg.ui \
    xes1/xes1.ui \
    physeqrowdlg.ui \
    modulenavigator.ui \
    objectnavigator.ui \
    physobjectpropsnavigatordock.ui \
    physequationsolverdock.ui \
    physoutputnavigatordock.ui
