#ifndef CARTESIANGRAPHDATAOBJ_H
#define CARTESIANGRAPHDATAOBJ_H

#include <QDataStream>

class CartesianGraphDataObj {
public:
    CartesianGraphDataObj() {}
    virtual ~CartesianGraphDataObj();

    // copy ctor and assignment
    CartesianGraphDataObj(const CartesianGraphDataObj &);

    // operator overloads
    CartesianGraphDataObj &operator=(const CartesianGraphDataObj &);
    bool operator==(const CartesianGraphDataObj &);
private:

};
QDataStream &operator<<(QDataStream &out, const CartesianGraphDataObj &obj);
QDataStream &operator>>(QDataStream &in, CartesianGraphDataObj &obj);

#endif // CARTESIANGRAPHDATAOBJ_H

