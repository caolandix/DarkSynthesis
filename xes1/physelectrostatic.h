#ifndef PHYSELECTROSTATIC_H
#define PHYSELECTROSTATIC_H

#include <QFile>


class PhysElectroStatic : public QObject {
    Q_OBJECT
public:
    PhysElectroStatic();
    ~PhysElectroStatic();
    void start(int, char *);
private:

    enum { Zero_Order = 0, First_Order, Quadratic_Spline, Cubic_Spline };
    enum { Momentum_Conserving = 0, Energy_Conserving };

    static const double onesix;
    static const double twothirds;
    static const double AKPERP;

    static const int K8;
    static const int NGMAX;
    static const int NXV;
    static const int NVY;
    static const int NSPM = 8;
    static const int HISTMAX;
    static const int NVBINMAX;
    static const int MAXPARTICLES;

    // member methods
    void init(int *, int *, double *, double *, double *, double *, int *, int *, double *, double *, int *);
    void startvel();
    void accel(int, int, double, double, double, double *, double *);
    void cpft(double [], double [], int, int, double);
    void rpft2(double [], double [] ,const int, const int);
    void rpfti2(double [], double [],const int, const int);
    double sign(const double, const double);
    void fields(const int);
    void move(const int ilp, const int, const double);
    void setv(const int, const int, const double, const double, const double, double *, double *);
    void setrho(const int, const int, const double, const double);
    double frand();
    void velocity();
    void history();

    inline double sqr(const double val) { return val * val; }
    inline double cube(const double val) { return val * val * val; }

    // member properties
    double l, dx, dt, la, ael, epsi, rho0, a1, a2, e0, w0, ese_hist, p, ecconst;

    double *kes_hist, *pxs_hist, *esem_hist, *ms, *qs, *ts, *nms;
    double *ese, **kes, **pxs, **esem, *ke, *te, *x, *vx, *vy;
    double *x_array,  *t_array, *k_array, *rho, *phi, *phik, *e;
    double *acc, *dvbin, *v_array, *vbint, *vbin, *vbinstart, *vbin_inst;
    double t;
    QFile *InputDeck;

    int it, nt, ith, ithl, hist_hi, interval, nsp, localnsp, accum, mmax, ng, ng1, iw, ec, k_hi;
    int ins[NSPM + 2], np[NSPM + 2], vbins[NSPM + 2], nvbin[NSPM];
};

#endif // PHYSELECTROSTATIC_H
