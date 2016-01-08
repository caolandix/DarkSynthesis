#ifndef EQEVALRTSTACK_H
#define EQEVALRTSTACK_H


class EqEvalRTStack {
public:
    EqEvalRTStack() { m_tos = &m_stack[-1]; }
private:
    enum { stackSize = 32 };
    double m_stack[stackSize];
    double *m_tos;
};

#endif // EQEVALRTSTACK_H
