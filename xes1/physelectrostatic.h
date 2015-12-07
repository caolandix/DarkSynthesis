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

    static constexpr double onesix = 0.16666666667;
    static constexpr double twothirds = 0.6666666667;
    static constexpr double AKPERP = 2.405;
    static const int K8 = 8192;
    static const int NGMAX = K8;
    static const int NXV = K8;
    static const int NVY = NXV / 2;
    static const int NSPM = 8;
    static const int HISTMAX = 512;
    static const int NVBINMAX = 1024;
    static const int MAXPARTICLES = 920001;

    // member methods
    bool init(int *, int *, double *, double *, double *, double *, int *, int *, double *, double *, int *);
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

    double sqr(const double val) { return val * val; }
    double cube(const double val) { return val * val * val; }

    // member properties
    int m_ng;
    double m_dx;
    double *m_x;
    double m_l, m_dt, m_la, m_ael, m_epsi, m_rho0, m_a1, m_a2, m_e0, m_w0, m_ese_hist, m_p, m_ecconst;
    double *m_kes_hist, *m_pxs_hist, *m_esem_hist, *m_ms, *m_qs, *m_ts, *m_nms;
    double *m_ese, **m_kes, **m_pxs, **m_esem, *m_ke, *m_te, *m_vx, *m_vy;
    double *m_x_array, *m_t_array, *m_k_array, *m_rho, *m_phi, *m_phik, *m_e;
    double *m_acc, *m_dvbin, *m_v_array, *m_vbint, *m_vbin, *m_vbinstart, *m_vbin_inst;
    double m_t;
    int m_it, m_nt, m_ith, m_ithl, m_hist_hi, m_interval, m_nsp, m_localnsp, m_accum, m_mmax, m_ng1, m_iw, m_ec, m_k_hi;
    int m_ins[NSPM + 2], m_np[NSPM + 2], m_vbins[NSPM + 2], m_nvbin[NSPM];
    QFile *m_InputDeck;

};

#endif // PHYSELECTROSTATIC_H
