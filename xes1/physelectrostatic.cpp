#include <QTime>

#include <math.h>
#include "physelectrostatic.h"
#include "physscience.h"

PhysElectroStatic::PhysElectroStatic() {

    // Setting the global parameters to their default values.
    m_l = 6.283185307;
    m_dt = 0.2;
    m_nsp = 1;
    m_epsi = 1.0;
    m_ng = 32;
    m_iw = 2;
    m_ec = 0;
    m_ins[1] = 1;
    m_vbins[1] = 1;  // sets up the start of vbin.
    m_interval = 1;
}

PhysElectroStatic::~PhysElectroStatic() {
    if (m_nms) { delete [] m_nms; m_nms = NULL; }
    if (m_ms) { delete [] m_ms; m_ms = NULL; }
    if (m_qs) { delete [] m_qs; m_qs = NULL; }
    if (m_ts) { delete [] m_ts; m_ts = NULL; }
    if (m_x_array) { delete [] m_x_array; m_x_array = NULL; }
    if (m_rho) { delete [] m_rho; m_rho = NULL; }
    if (m_phi) { delete [] m_phi; m_phi = NULL; }
    if (m_phik) { delete [] m_phik; m_phik = NULL; }
    if (m_e) { delete [] m_e; m_e = NULL; }
    if (m_acc) { delete [] m_acc; m_acc = NULL; }
    if (m_t_array) { delete [] m_t_array; m_t_array = NULL; }
    if (m_ese) { delete [] m_ese; m_ese = NULL; }
    if (m_ke) { delete [] m_ke; m_ke = NULL; }
    if (m_te) { delete [] m_te; m_te = NULL; }
    if (m_kes_hist) { delete [] m_kes_hist; m_kes_hist = NULL; }
    if (m_pxs_hist) { delete [] m_pxs_hist; m_pxs_hist = NULL; }
    if (m_esem_hist) { delete [] m_esem_hist; m_esem_hist = NULL; }
    if (m_x) { delete [] m_x; m_x = NULL; }
    if (m_vx) { delete [] m_vx; m_vx = NULL; }
    if (m_vy) { delete [] m_vy; m_vy = NULL; }
    if (m_vbint) { delete [] m_vbint; m_vbint = NULL; }
    if (m_vbin) { delete [] m_vbin; m_vbin = NULL; }
    if (m_vbin_inst) { delete [] m_vbin_inst; m_vbin_inst = NULL; }
    if (m_dvbin) { delete [] m_dvbin; m_dvbin = NULL; }
    if (m_vbinstart) { delete [] m_vbinstart; m_vbinstart = NULL; }
    if (m_v_array) { delete [] m_v_array; m_v_array = NULL; }

    // arrays of pointers
    if (m_nms) { delete [] m_kes; m_kes = NULL; }
    if (m_nms) { delete [] m_pxs; m_pxs = NULL; }
    if (m_nms) { delete [] m_esem; m_esem = NULL; }
}

bool PhysElectroStatic::init(int *il1, int *il2, double *m, double *q, double *t,
                             double *nm, int *vbin1, int *vbin2, double *dvb, double *vstart, int *nvbin) {
    double wp = 1.0, wc = 0.0, qm = -1.0, vt1 = 0.0, vt2 = 0.0, v0 =0.0,
        x1 = 0.0, v1 = 0.0, thetax = 0.0, thetav = 0.0, ddx, x0,
        vmax, dv, vvnv2, vv, fv, df, xs, xsi, theta, lg, vupper,vlower;
    int ngr, j, i1, i2, n = 128, nlg = 1, nv2 = 0, mode = 1, nbins = 100;
    char a_char[80];

    // Make sure we have valid pointers
    if (!(t && il2 && il1 && q && m && nm && dvb))
        return false;
    *dvb = 1.0;  // this is a huge default.

    /*
    while (fscanf(InputDeck, "%d %d %d %d ", &n, &nv2, &nlg, &mode) < 4)  // added nbins
    fscanf(InputDeck,"%s", a_char);
    while (fscanf(InputDeck, "%g %g %g %g %g %g", &wp, &wc, &qm, &vt1, &vt2, &v0) < 6)
    fscanf(InputDeck,"%s", a_char);
    while (fscanf(InputDeck,"%g %g %g %g", &x1, &v1, &thetax, &thetav) < 4)
    fscanf(InputDeck,"%s", a_char);
    while(fscanf(InputDeck," %d %g %g ",&nbins,&vlower,&vupper) < 3)
    fscanf(InputDeck,"%s", a_char);
    */
    qDebug(" n = %4d  nv2 = %4d  nlg = %4d  mode = %4d \n", n, nv2 ,nlg, mode);
    qDebug(" wp = %6.3f   wc = %6.3f   qm = %6.3f \n", wp, wc, qm);
    qDebug(" vt1 = %6.3f  vt2 = %6.3f  v0 = %6.3f \n", vt1, vt2, v0);
    qDebug(" x1 = %6.3f   v1 = %6.3f   thetax = %6.3f   thetav = %6.3f \n", x1, v1, thetax, thetav);
    qDebug(" nbins = %4d   vlower = %6.3f  vupper = %6.3f ", nbins, vlower, vupper);

    *t = tan(-0.5 * wc * m_dt);
    *il2 = *il1 + n;

    *q = m_l * wp * wp / (m_epsi * n * qm);
    *m = *q / qm;
    *nm = n * (*m);
    ngr = n / nlg;
    lg = m_l / nlg;
    ddx = m_l / n;


    if (nbins > NVBINMAX)
        nbins = NVBINMAX;
    if (nbins < 2)
        nbins = 2;
    *nvbin = nbins;
    *vbin2 = *vbin1 + nbins;
    if (vupper - vlower < 0.0) {
        qDebug("\nError in INIT: vupper must be > vlower!");
        return false;
    }
    if (vt1 < 0 || vt2 < 0) {
        qDebug("\nError in INIT: can't have negative thermal voltages!");
        return false;
    }
    if(vupper-vlower > 0.0) {
        *vstart = vlower;
        *dvb = (vupper - vlower) / nbins;
    }
    else {
        if (vt1 + vt2 > 0.0) {
            *vstart = v0 - 5.0 * (vt1 + vt2);
            *dvb = 10.0* (vt1 + vt2) / nbins;  // so that the distribution goes from v0-5*vt to v0+5*vt
        }
        else if (fabs(v0) > 0) {
            if (v0 > 0) {
                *vstart = 0.0;
                *dvb = 2 * v0 / nbins;
            }
            else {
                *vstart=2.0 * v0;
                *dvb= -2 * v0 / nbins;
            }
        }
        else {
            *vstart = 0.0;
            *dvb = 1 / nbins;
        }
    }

    // setup v_array for this species
    for (int i = *vbin1; i < *vbin2; i++)
        m_v_array[i] = (*vstart + (i - *vbin1 + 0.5) * (*dvb));

    for (int i = 1; i <= ngr; i++) {
        i1 = i - 1 + *il1;
        x0 = (i - 0.5) * ddx;
        m_x[i1] = x0;
        m_vx[i1] = v0;
    }
    if (vt2 != 0.0) {
        vmax = 5.0 * vt2;
        dv = 2.0 * vmax / (n - 1);
        vvnv2 = 1.0;
        m_x[*il1] = 0.0;
        for (int i = 2; i <= n; i++) {
            vv = ((i - 1.5) * dv - vmax) / vt2;
            if (nv2 != 0)
                vvnv2 = pow(vv, (double)nv2);
            fv = vvnv2 * exp(-0.5 * vv * vv);
            i1 = i - 1 + *il1;
            m_x[i1] = m_x[i1 - 1] + ((fv >= 0.0) ? fv : 0.0);
        }
        df = m_x[i1]/ngr;
        i1 = *il1;
        j = *il1;
        for (int i = 1; i <= ngr; i++) {
            fv = (i - 0.5) * df;
            while (fv >= m_x[j + 1]) {
                j++;
                if (j > (*il2 - 2)) {
                    qDebug("distribution function error");
                    return false;
                }
            }
            vv = dv * (j - *il1 + (fv - m_x[j]) / (m_x[j + 1] - m_x[j])) - vmax;
            m_vx[i1] += vv;
            i1++;
        }
        xs = 0.0;
        for (int i = 1; i <= ngr; i++) {
            i1 = i - 1 + *il1;
            m_x[i1] = xs * lg + 0.5 * ddx;
            xsi = 1.0;
            do {
                xsi *= 0.5;
                xs -= xsi;
            } while (xs >= 0.0);
            xs += 2.0 * xsi;
        }
        i1 = ngr + *il1 - 1;
    }
    if (wc != 0.0) {
        for (int i = 1; i <= ngr; i++) {
            i1 = i - 1 + *il1;
            vv = m_vx[i1];
            theta = 2 * PhysConsts::PI * frand();
            m_vx[i1] = vv * cos(theta);
            m_vy[i1] = vv * sin(theta);
        }
    }
    if (nlg != 1) {
        j = ngr + 1;
        xs = 0.0;
        for (int i = j; i <= n; i += ngr) {
            xs += lg;
            for (int j = 1; j <= ngr; j++) {
                i1 = j - 1 + *il1;
                i2 = i1 + i - 1;
                m_x[i2] = m_x[i1] + xs;
                m_vx[i2] = m_vx[i1];
                if (wc != 0.0)
                    m_vy[i2] = m_vy[i1];
            }
        }
    }
    if (vt1 != 0.0) {
        for (int i = 1;i <= n; i++) {
            i1 = i - 1 + *il1;
            for (int j = 0; j < 12; j++) {
                if (wc != 0.0)
                    m_vy[i1] += vt1 * (frand() - 0.5);
                m_vx[i1] += vt1 * (frand() - 0.5);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        i1 = i - 1 + *il1;
        theta = 2 * PhysConsts::PI * mode * m_x[i1] / m_l;
        m_x[i1] += x1 * cos(theta + thetax);
        m_vx[i1] += v1 * sin(theta + thetav);
    }
    setrho(*il1, *il2 - 1, *q, (*q) * n / m_l);
    return true;
}

void PhysElectroStatic::start(int argc, char *argv) {
    char a_char[80];
    bool WasInputFileGiven = false;
    QString filename;

    // InputDeck = (!WasInputFileGiven) ? fopen("es1data","r") :  fopen(theInputFile,"r");
    // if (!InputDeck) {
    if (false) {
        qDebug("Can't find input file %s", argv[1]);
        qDebug("Correct syntax is: ES1 -i file.inp");
    }
    else {

        // read lines until we get to numbers
        /*
        while (fscanf(InputDeck,"%d %g %g %d %d %g %d", &nsp, &l, &dt, &nt, &mmax, &la, &accum) < 7)
            fscanf(InputDeck, "%s", a_char);
        // note: la is l/a

        while (fscanf(InputDeck," %d %d %d %g %g %g %g %g", &ng, &iw, &ec, &epsi, &a1, &a2, &e0, &w0) < 8)
            fscanf(InputDeck, "%s", a_char);
        */
        if (m_nsp > NSPM) {
            qDebug("Number of species nsp cannot exceed NSPM");
            return;
        }

        if (m_accum < 0) {
            qDebug("Error:  accum can't be negative!");
            return;
        }

        if(!(m_ec == 1 || m_ec == 0)) {
            qDebug("Error:  What are you thinking?  There are only two possible values of ec");
            qDebug("0 and 1.  %d is not 0 or 1.", m_ec);
            return;
        }
        if (!m_iw && m_ec) {
            qDebug("Error:  There IS no energy-conserving algorithm for NGP");
            return;
        }

        m_ecconst = (m_ec) ? 0.5 : 0.0;
        if (m_iw > 3 || m_iw < 0) {
            qDebug("Error:  bad iw flag!  Please check your input deck!");
            return;
        }

        if (m_ng > NGMAX) {
            printf("Number of grids ng cannot exceed NGMAX");
            return;
        }
        m_dx = m_l / m_ng;
        m_ng1 = m_ng + 1;
        m_k_hi = m_ng / 2;

        // Allocating space for arrays
        m_nms = new double[m_nsp + 1];
        m_ms = new double[m_nsp + 1];
        m_qs = new double[m_nsp + 1];
        m_ts = new double[m_nsp + 1];

        m_x_array = new double[m_ng + 1];
        for (int i = 0; i <= m_ng; i++)
            m_x_array[i] = i * m_dx;

        m_rho = new double[m_ng + 3];
        m_phi = new double[m_ng + 2];
        m_phik = new double[m_ng + 2];
        m_k_array = new double[m_ng];
        for (int i = 0; i < m_k_hi; i++)
            m_k_array[i] = i * 2 * PhysConsts::PI / m_l;
        m_e = new double[m_ng + 2];
        m_acc = new double[m_ng + 3];

        m_t_array = new double[HISTMAX];
        m_ese = new double[HISTMAX];
        m_ke = new double[HISTMAX];
        m_te = new double[HISTMAX];

        m_kes_hist = new double[m_nsp + 1];
        m_pxs_hist = new double[m_nsp + 1];
        m_esem_hist = new double[m_mmax + 1];

        m_kes = new double*[m_nsp];
        for (int i = 0; i < m_nsp; i++)
            m_kes[i] = new double[HISTMAX];

        m_pxs = new double*[m_nsp];
        for (int i = 0; i < m_nsp; i++)
            m_pxs[i] = new double[HISTMAX];

        m_esem = new double*[m_mmax];
        for (int i = 0; i < m_mmax; i++)
            m_esem[i] = new double[HISTMAX];

        m_x = new double[MAXPARTICLES];
        m_vx = new double[MAXPARTICLES];
        m_vy = new double[MAXPARTICLES];

        m_vbint = new double[NVBINMAX];
        m_vbin = new double[m_nsp * NVBINMAX];
        m_vbin_inst = new double[m_nsp * NVBINMAX];
        for (int i = 0; i < m_nsp * NVBINMAX; i++)
            m_vbin_inst[i]= 0.0;
        m_dvbin = new double[m_nsp + 1];
        m_vbinstart = new double[m_nsp + 1];
        m_v_array = new double[NVBINMAX * m_nsp];

        if (!m_x || !m_vx || !m_vy || !m_vbint || !m_vbin_inst || !m_dvbin || !m_v_array ) {
            qDebug("START: Could not get enough memory for x or v's.");
            return;
        }

        qDebug("nsp = %2d     l = %8.5f", m_nsp, m_l);
        qDebug("dt = %4.2f    nt = %4d", m_dt, m_nt);
        qDebug("ng = %5d   iw = %2d   ec = %2d  accum = %4d", m_ng, m_iw, m_ec, m_accum);
        qDebug("epsi = %4.2f  a1 = %4.2f  a2 = %4.2f", m_epsi, m_a1, m_a2);

        for (int i = 1; i <= m_nsp; i++) {
            if (!init(&m_ins[i], &m_ins[i + 1], &m_ms[i], &m_qs[i], &m_ts[i], &m_nms[i], &m_vbins[i], &m_vbins[i + 1], &m_dvbin[i], &m_vbinstart[i], &m_nvbin[i]))
                return;
        }

        // added vbins to param list
        // fclose(InputDeck);

        for (int i = 1; i <= m_nsp; i++)
            m_np[i] = m_ins[i + 1] - m_ins[i];

        for (int i = 0; i < m_nsp; i++) {
            for (int j = 0; j < HISTMAX; j++) {
                m_kes[i][j] = 0.0;
                m_pxs[i][j] = 0.0;
            }
        }
        m_rho[1] += m_rho[m_ng1];   // These resolve the periodic boundary conditions.
        m_rho[2] += m_rho[m_ng + 2];
        m_rho[m_ng] += m_rho[0];
        m_rho[0] = m_rho[m_ng];
        m_rho[m_ng + 2] = m_rho[2];
        m_rho[m_ng1] = m_rho[1];
        fields(0);

        for (int i = 1; i <= m_nsp; i++) {
            setv(m_ins[i], m_ins[i + 1] - 1, m_qs[i], m_ms[i], m_ts[i], &m_pxs_hist[i], &m_kes_hist[i]);

            // scale all the velocities  properly
            m_dvbin[i] *= m_dt / m_dx;
            m_vbinstart[i] *= m_dt / m_dx;
        }
        startvel();
    }
}


// all this function does is set up the initial velocity distribution diagnostic to reflect the startup values.
void PhysElectroStatic::startvel() {
    int s, nbinmaxi;
    double *vsps = NULL;          // vsps is a pointer to the part of the velocity bin array where the species starts
    double vst, dvt;        // this is the vstart[isp],dv[isp]

    // This code does the velocity-distribution stuff.
    for (int i = 1; i <= m_nsp; i++) {
        vsps = &(m_vbin[m_vbins[i]]);
        vst = m_vbinstart[i];
        dvt = m_dvbin[i];
        nbinmaxi = m_nvbin[i];
        for (int j = m_vbins[i]; j <= m_vbins[i] + m_nvbin[i]; j++)
            m_vbin[j] = 0.0;
        if (nbinmaxi > 0 && m_accum) {
            for (int j = m_ins[i]; j < m_ins[i + 1]; j++) {
                s = (m_vx[j] - vst) / dvt;
            }
            if (s >= 0 && s < nbinmaxi)
                vsps[s] += 0.10;
        }
    }
}

double PhysElectroStatic::sign(const double a, const double b) {
    if (b >= 0.0)
        return (a >= 0.0) ? a : -a;
    return (a < 0.0) ? a : -a;
}

void PhysElectroStatic::cpft(double r[], double i[], const int n, const int incp, const double signp) {
    if (n == 1)
        return;
    int span, rc, inc, is, it, ninc, ij, ji, n1, n2;
    int k0, k1;
    static double sines[16] = {
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0
    };
    double r0, r1, i0, i1, t, sgn, c, c0, s, s0;

    if (sines[1] != 1.0) {
        sines[1] = 1.0;
        t = atan(1.0);
        for (int is = 2; is <= 15; is++) {
            sines[is] = sin(t);
            t *= 0.5;
        }
    }

    inc = incp;
    sgn = signp;
    ninc = n * inc;
    span = ninc;
    it = n >> 1;
    if ((it > 16384) || (it < 0)) {
        qDebug(" n out of range in cpft.");
        // exit(1);
    }
    for (int is = 1; is <= 15; is++) {
        if (it == 1)
            break;
        it >>= 1;
    }
    do {
        span >>= 1;
        k0 = 0;
        do {
            k1 = k0 + span;
            r0 = r[k0 + 1];
            i0 = i[k0 + 1];
            r1 = r[k1 + 1];
            i1 = i[k1 + 1];
            r[k0 + 1] = r0 + r1;
            i[k0 + 1] = i0 + i1;
            r[k1 + 1] = r0 - r1;
            i[k1 + 1] = i0 - i1;
            k0 = k1 + span;
        } while (k0 < ninc);
        if (span == inc)
            break;
        c0 = 2.0 * sines[is] * sines[is];
        is--;
        s = sign(sines[is], sgn);
        s0 = s;
        c = 1.0 - c0;
        k0 = inc;
        do {
            k1 = k0 + span;
            r0 = r[k0 + 1];
            i0 = i[k0 + 1];
            r1 = r[k1 + 1];
            i1 = i[k1 + 1];
            r[k0 + 1] = r0 + r1;
            i[k0 + 1] = i0 + i1;
            r0 -= r1;
            i0 -= i1;
            r[k1 + 1] = c*r0 - s*i0;
            i[k1 + 1] = s*r0 + c*i0;
            k0 = k1 + span;
            if (k0 >= ninc) {
                k1 = k0 - ninc;
                c = -c;
                k0 = span - k1;
                if (k1 >= k0) {
                    k0 += inc;
                    if (k0 >= k1)
                        break;
                    t = s + (s0*c - c0*s);
                    c = c - (c0*c + s0*s);
                    s = t;
                }
            }
        } while (true);
    } while (true);
    n1 = ninc - inc;
    n2 = ninc >> 1;
    rc = ij = ji = 0;
    if (n2 != inc) {
        do {
            ij += inc;
            ji += n2;
            t = r[ij + 1];
            r[ij + 1] = r[ji + 1];
            r[ji + 1] = t;
            t = i[ij + 1];
            i[ij + 1] = i[ji + 1];
            i[ji + 1] = t;
            it = n2;
            do {
                it >>= 1;
                rc -= it;
            } while (rc >= 0);
            rc += (it << 1);
            ji = rc;
            ij += inc;
            if (ij < ji) {
                do {
                    ij = n1 - ij;
                    ji = n1 - ji;
                    t = r[ij + 1];
                    r[ij + 1] = r[ji + 1];
                    r[ji + 1] = t;
                    t = i[ij + 1];
                    i[ij + 1] = i[ji + 1];
                    i[ji + 1] = t;
                } while (ij > n2);
            }
            else {
                if (ij >= n2)
                    break;
            }
        } while (true);
    }
}

void PhysElectroStatic::rpft2(double a[], double b[] ,const int n, const int incp) {
    double rp, rm, ip, im;
    int inc, ninc;
    int lp, lm;

    inc = incp;
    ninc = n * inc;
    a[1] = a[1] + a[1];
    b[1] = b[1] + b[1];
    lp = inc;
    lm = ninc - lp;
    if (lp < lm) {
        do {
            rp = a[lp + 1];
            ip = b[lp + 1];
            rm = a[lm + 1];
            im = b[lm + 1];
            a[lp + 1] = rm + rp;
            b[lp + 1] = ip + im;
            a[lm + 1] = ip - im;
            b[lm + 1] = rm - rp;
            lp += inc;
            lm = ninc - lp;
        } while (lp < lm);
    }
    if (lp <= ninc) {
        a[lp + 1] = a[lp + 1] + a[lp + 1];
        b[lp + 1] = b[lp + 1] + b[lp + 1];
    }
}

void PhysElectroStatic::rpfti2(double a[], double b[] ,const int n, const int incp) {
    double ca, sa, cb, sb;
    int inc, ninc;
    int lp, lm;

    inc = incp;
    ninc = n * inc;
    lp = inc;
    lm = ninc - lp;
    if (lp < lm) {
        do {
            ca = a[lp + 1];
            cb = b[lp + 1];
            sa = a[lm + 1];
            sb = b[lm + 1];
            a[lp + 1] = ca - sb;
            b[lp + 1] = cb + sa;
            a[lm + 1] = ca + sb;
            b[lm + 1] = cb - sa;
            lp += inc;
            lm = ninc - lp;
        } while (lp < lm);
    }
}

void PhysElectroStatic::accel(int ilp, int iup, double q, double m, double t, double *p, double *ke) {
    int il, iu, ng1, i, j;
    double a, b, c, xii, dxdt, ae, tem, v1s, v2s, vo, vn, s, aa, vyy, vxx;
    double jxii;  // this is j-xii, which is used a lot, this will save additions

    il = ilp;
    iu = iup;
    dxdt = m_dx / m_dt;
    ae = (q / m) * (m_dt / dxdt);
    if (t != 0.0)
        ae *= 0.5;
    if (ae != m_ael) {
        ng1 = m_ng + 1;

        // tem = ae/ael;  this does nothing, is not used later
        for (int j = 1; j <= ng1; j++)
            m_acc[j] = m_e[j] * ae;
        m_acc[0] = ae * m_e[m_ng];
        m_acc[m_ng + 2] = ae * m_e[2];
        m_acc[ng1] = ae * m_e[1];
        m_ael = ae;
    }
    switch (m_iw - m_ec) {
    case Zero_Order :
        v1s = v2s = 0.0;
        for (int i = il; i <= iu; i++) {
            j = m_x[i] + 0.5 - m_ecconst;  // ecconst is .5 for energy conserving, 0 for momentum conserving
            vo = m_vx[i];
            vn = vo + m_acc[j + 1];
            v1s += vn;
            v2s += vn * vo;
            m_vx[i] = vn;
        }
        *p = m * v1s * dxdt;
        *ke = 0.5 * m * v2s * dxdt * dxdt;
        break;
    case First_Order :
        if (t != 0.0) {
            s = 2.0 * t / (1.0 + t * t);
            v2s = 0.0;
            for (int i = il; i <= iu; i++) {
                xii = m_x[i] - m_ecconst + 1.0;
                j = xii;
                xii -= 1.0;
                j -= 1;

                // the reason for the addition and subtraction of 1 to xii is to avoid an error condition
                // in which the truncation causes it to truncate UP instead of round down when 0<= x[i] <0.5.
                // The modification ensures that it gets set to the right value.
                aa = m_acc[j + 1] + (xii - j) * (m_acc[j + 2] - m_acc[j + 1]);
                vyy = m_vy[i];
                vxx = m_vx[i] - t * vyy + aa;
                vyy += s * vxx;
                vxx -= t * vyy;
                v2s += vxx * vxx + vyy * vyy;
                m_vx[i] = vxx + aa;
                m_vy[i] = vyy;
            }
            *ke = 0.5 * m * v2s * dxdt * dxdt;
        }
        else {
            v1s = v2s = 0.0;
            for (int i = il; i <= iu; i++) {
                xii = m_x[i] - m_ecconst + 1;
                j = xii;
                xii -= 1.0;
                j -= 1;
                // the reason for the addition and subtraction of 1 to xii is to avoid an error condition
                // in which the truncation causes it to truncate UP instead of round down when 0<= x[i] <0.5.
                // The modification ensures that it gets set to the right value.
                vo = m_vx[i];
                vn = vo + m_acc[j + 1] + (xii - j) * (m_acc[j + 2] - m_acc[j + 1]);
                v1s += vn;
                v2s += vo * vn;
                m_vx[i] = vn;
            }
            *p = m * v1s * dxdt;
            *ke = 0.5 * m * v2s * dxdt * dxdt;
        }
        break;
    case Quadratic_Spline :
        v1s = v2s = 0.0;
        for (int i = il; i <= iu; i++) {
            xii = m_x[i] - m_ecconst; //Grab the value of x[i] so we don't have to keep dereferencing a pointer
            j = xii + 0.5;   // Grab the nearest grid point.
            vo = m_vx[i];    // Grab the value of the current velocity
            a = 0.75 - sqr(j - xii);
            b = 0.5 * sqr(0.5 - j + xii);
            vn = vo + a * m_acc[j + 1] + b * m_acc[j + 2] + (1 - a - b) * m_acc[j];
            v1s += vn;
            v2s += vn * vo;
            m_vx[i] = vn;
        }
        *p = m * v1s * dxdt;
        *ke = 0.5 * m * v2s * dxdt * dxdt;
        break;
    case Cubic_Spline :
        v1s = v2s = 0.0;
        for (int i = il; i <= iu; i++) {
            xii = m_x[i];
            j = xii + 0.5;
            vo = m_vx[i];
            jxii = j - xii;
            if (jxii >= 0) {
                // The commented assignments are unoptimized.  The uncommented assignments below are optimized
                // to reduce the number of multiplications, etc...

                //a=.5*cube(jxii)-sqr(jxii)+.6666666667;
                a = twothirds + jxii * jxii * (-1.0 + 0.5 * jxii);

                // b= -.5*cube(jxii-1)-sqr(jxii-1)+.6666666667;
                b = onesix + 0.5 * jxii * (1.0 + jxii * (1.0 - jxii));

                // c= -cube(jxii+1)/6.0+sqr(jxii+1)-2*(jxii+1)+1.3333333;
                c = onesix + onesix * jxii * (-3.0 + jxii * (3.0 - jxii));
                vn = vo + a * m_acc[j + 1] + b * m_acc[j] + c * m_acc[j + 2] + (1.0 - a - b - c) * m_acc[j - 1];
            }
            else {
                // a= -.5*cube(jxii)-sqr(jxii)+.6666666667;
                a = twothirds - jxii * jxii * ( 1.0 + 0.5 * jxii);

                // b=.5*cube(jxii+1)-sqr(jxii+1)+.6666666667;
                b = onesix + 0.5 * jxii*(-1.0 + jxii * ( 1.0 + jxii));

                // c= cube(jxii-1)/6.0+sqr(jxii-1)+2*(jxii-1)+1.3333333;
                c = onesix + onesix * jxii * (3 + jxii * (3 + jxii));

                vn = vo + a * m_acc[j + 1] + b * m_acc[j + 2] + c * m_acc[j] + (1.0 - a - b - c) * m_acc[j + 3];
            }
            v1s += vn;
            v2s += vn * vo;
            m_vx[i] = vn;
        }
        *p = m * v1s * dxdt;
        *ke = 0.5 * m * v2s * dxdt * dxdt;
        break;
    default:
       qDebug("Bad iw switch in accel");
       break;
    }
}

void PhysElectroStatic::fields(const int ith) {
    static int ng2 = 0, ng1 = 0;
    static double *ksqi = NULL, *sm = NULL;
    int kk, km;
    int k, j;
    double kdx2, li, hdx, eses, eot, hdxi, dxi, temp, temp1, e0t, kperp2;

    if (ng2 == 0) {
        ng2 = m_ng / 2;
        ksqi = new double[ng2 + 1];
        sm = new double[ng2 + 1];
        ng1 = m_ng + 1;
        kperp2 = AKPERP * AKPERP * (m_la / m_l * m_la / m_l); /* a = charge disk radius*/
        for (int k = 1; k <= ng2; k++) {
            kdx2 = (PhysConsts::PI / m_ng) * k;
            if ((m_a1 != 0.0) || (m_a2 != 0.0)) {
                temp = (k < ng2) ? tan(kdx2) : 10000.0;
                temp *= temp;
                temp *= temp; // suspect overflows at k=ng2
                temp1 = sin(kdx2);
                temp1 *= temp1;
                sm[k] = exp(m_a1 * temp1 - m_a2 * temp);
                if (sm[k] < 1.0E-10)
                    sm[k] = 0.0;
            }
            else
                sm[k] = 1.0;
            temp = 2.0 * sin(kdx2) / m_dx;
            temp = temp * temp;
            temp += kperp2;
            ksqi[k] = (m_epsi / temp) * sm[k] * sm[k];
        }
    }
    hdx = 0.5 * m_dx;
    for (int j = 1; j <= m_ng; j++) {
        m_rho[j] *= hdx;
        m_e[j] = 0.0;
    }
    cpft(m_rho, m_e, m_ng, 1, 1.0);
    rpft2(m_rho, m_e, m_ng, 1);
    m_rho[1] = eses = m_phi[1] = 0.0;
    for (int k = 2;k <= ng2 ;k++) {
        kk = m_ng + 2 - k;
        m_phi[k] = ksqi[k-1] * m_rho[k];
        m_phi[kk] = ksqi[k-1] * m_rho[kk];
        eses += m_rho[k] * m_phi[k] + m_rho[kk] * m_phi[kk];
    }
    m_phi[ng2 + 1] = ksqi[ng2] * m_rho[ng2 + 1];
    m_ese_hist = (2.0 * eses + m_rho[ng2 + 1] * m_phi[ng2 + 1]) / (2.0 * m_l);
    li = 1.0 / m_l;

    for (int km = 1; km <= m_mmax; km++) {
        k = km + 1;
        if (k == 1)
            break;
        kk = m_ng + 2 - k;
        m_esem_hist[km] = (m_rho[k] * m_phi[k] + m_rho[kk] * m_phi[kk]) * li;
        if (k == kk)
            m_esem_hist[km] *= 0.25;
    }
    for (int k = 2; k <= ng2; k++){
        kk = m_ng - k;
        m_rho[k] *= sm[k - 1];
        m_rho[kk] *= sm[k - 1];
    }
    m_rho[ng2 + 1] *= sm[ng2];
    for (int k = 1; k <= m_ng ;k++) {
        m_rho[k] *= li;
        m_phi[k] *= li;
    }

    m_phik[1] = 1e-30;
    for (int k = 1; k <= ng2; k++) {
        kk = m_ng + 2 - k;
        m_phik[k] = li * fabs(m_phi[k] * m_rho[k] + m_phi[kk] * m_rho[kk]) + 1e-30;
    }
    rpfti2(m_phi, m_rho, m_ng, 1);
    cpft(m_phi, m_rho, m_ng, 1, -1.0);
    m_phi[ng1] = m_phi[1];
    m_rho[ng1] = m_rho[1];
    e0t = (m_e0 != 0.0) ?  m_e0 * cos(m_w0 * m_t) : 0.0;
    switch (m_ec) {
    case Momentum_Conserving:
        hdxi = 0.5 / m_dx;
        for (int j = 2; j <= m_ng; j++) m_e[j] = (m_phi[j - 1] - m_phi[j + 1]) * hdxi + e0t;
        m_e[1] = (m_phi[m_ng] - m_phi[2]) * hdxi + e0t;
        m_e[m_ng + 1] = m_e[1];
        break;
    case Energy_Conserving:
        dxi = 1.0 / m_dx;
        for (int j = 1; j <= m_ng; j++) m_e[j] = (m_phi[j] - m_phi[j + 1]) * dxi + e0t;
        m_e[m_ng + 1] = m_e[1];
        break;
    default:
        qDebug("Bad ec switch in fields");
        // exit(-1);
        break;
    }
    m_ael = 1.0;
}

void PhysElectroStatic::move(const int ilp, const int iup, const double q) {
    int il = ilp, iu = iup;
    int j;
    double qdx = q / m_dx;
    double xn = m_ng;
    double drho;
    double a, b, c, xii;
    double jxii;

    switch (m_iw) {
    case Zero_Order :
        for (int i = il; i <= iu; i++) {
            m_x[i] += m_vx[i];
            if (m_x[i] < 0.0)
                m_x[i] += xn;
            else {
                if (m_x[i] >= xn)
                    m_x[i] -= xn;
            }
            j = m_x[i] + 0.5;
            m_rho[j + 1] += qdx;
        }
        break;
    case First_Order :
        for (int i = il; i <= iu; i++) {
            m_x[i] += m_vx[i];
            if (m_x[i] < 0.0)
                m_x[i] += xn;
            else {
                if (m_x[i] >= xn)
                    m_x[i] -= xn;
            }
            j = m_x[i];
            drho = qdx * (m_x[i] - j);
            m_rho[j + 1] += qdx - drho;
            m_rho[j + 2] += drho;
        }
        break;
    case Quadratic_Spline :
        for (int i = il; i <= iu; i++) {
            m_x[i] += m_vx[i];
            if (m_x[i] < 0.0)
                m_x[i] += xn;
            else {
                if (m_x[i] >= xn)
                    m_x[i] -= xn;
            }

            // By looking up x[i] and storing it in xii, I save three additions: I must do an addition every
            // time I use a subscript!
            xii = m_x[i];

            // Extract the nearest grid point: using truncation to do rounding- j is int.
            j = xii + 0.5;

            // Get the coefficient for the nearest grid point. It's a function of the distance.
            a = 0.75 - sqr(j - xii);
            b = 0.5 * sqr(0.5 - j + xii);

            // Get the coefficient for the grid location one to the right.
            m_rho[j + 1] += a * qdx;
            m_rho[j + 2] += b * qdx;
            m_rho[j] += (1.0 - a - b) * qdx;
        }
        break;
    case Cubic_Spline :
        for (int i = il; i <= iu; i++) {
            m_x[i] += m_vx[i];
            if (m_x[i] < 0.0)
                m_x[i] += xn;
            else {
                if (m_x[i] >= xn)
                    m_x[i] -= xn;
            }
            xii = m_x[i];
            j = xii + 0.5;
            jxii = j - xii;

            if ((jxii) >= 0) {
                // Below, the commented out assignments were the original weighting functions.
                // the actual assignments are optimized versions of the comment assignments.
                // a = 0.5*cub(jxii)-sqr(jxii)+twothirds;
                a = twothirds + jxii * jxii * (-1.0 + 0.5 * jxii);

                // b = -0.5*cub(jxii-1)-sqr(jxii-1)+twothirds;
                b = onesix + 0.5 * jxii * (1.0 + jxii * (1.0 - jxii));

                // c = -cub(jxii+1)/6.0+sqr(jxii+1)-2*(jxii+1)+1.3333333;
                c = onesix + onesix * jxii * (-3.0 + jxii * (3.0 - jxii));

                m_rho[j + 1] += a * qdx;
                m_rho[j + 2] += c * qdx;
                m_rho[j] += b * qdx;
                m_rho[j - 1] += (1.0 - a - b - c) * qdx;
            }
            else {

                // a= -.5*cub(jxii)-sqr(jxii)+twothirds;
                a = twothirds - jxii * jxii * (1.0 + 0.5 * jxii);

                // b=.5*cub(jxii+1)-sqr(jxii+1)+twothirds;
                b = onesix + 0.5 * jxii * (-1.0 + jxii * (1.0 + jxii));

                // c= cub(jxii-1)/6.0+sqr(jxii-1)+2*(jxii-1)+1.3333333;
                c = onesix + onesix * jxii * (3 + jxii * (3 + jxii));

                m_rho[j + 1] += a * qdx;
                m_rho[j + 2] += b * qdx;
                m_rho[j] += c * qdx;
                m_rho[j + 3] += (1.0 - a - b - c) * qdx;
            }
        }
        break;
    default:
        qDebug("Bad iw switch in move");
        // exit(-1);
        break;
    }
}

void PhysElectroStatic::setrho(const int il, const int iu, const double q, const double rhos) {
    double qdx, drho, a, b, c, xii;
    int j = 0;
    static double dxi, xn;

    qdx = q / m_dx;
    if (il == 1) {
        for (int j = 1; j <= m_ng; j++)
            m_rho[j] = m_rho0;
        m_rho[m_ng1] = 0.0;
        m_rho[0] = m_rho[m_ng + 2] = 0.0;
        dxi = 1.0 / m_dx;
        xn = m_ng;
    }
    m_rho0 -= rhos;
    for (j = 1; j <= m_ng; j++)
        m_rho[j] -= rhos;
    switch (m_iw) {
    case Zero_Order :
        for (int i = il; i <= iu; i++) {
            m_x[i] *= dxi;
            if (m_x[i] < 0.0)
                m_x[i] += xn;
            if (m_x[i] >= xn)
                m_x[i] -= xn;
            j = m_x[i] + 0.5;
            m_rho[j + 1] += qdx;
        }
        break;
    case First_Order :
        for (int i = il; i <= iu; i++) {
            m_x[i] *= dxi;
            if (m_x[i] < 0.0)
                m_x[i] += xn;
            if (m_x[i] >= xn)
                m_x[i] -= xn;
            j = m_x[i];
            drho = qdx * (m_x[i] - j);
            m_rho[j + 1] += qdx - drho;
            m_rho[j + 2] += drho;
        }
        break;
    case Quadratic_Spline :
        for (int i = il; i <= iu; i++) {
            m_x[i] *= dxi;
            if (m_x[i] < 0.0)
                m_x[i] += xn;
            else {
                if (m_x[i] >= xn)
                    m_x[i] -= xn;
            }
            // By looking up x[i] and storing it in xii, save three additions --
            // I must do an addition every time I use a subscript!
            xii = m_x[i];

            // Extract the nearest grid point: using truncation to do rounding- j is int.
            j = xii + 0.5;

            // Get the coefficient for the nearest grid point.  It's a function of the distance.
            a = 0.75 - sqr(j - xii);

            // Get the coefficient for the grid location one to the right.  Since (j+2)-xii is aways
            // postive the fabs doesn`t need to be there.
            b = 0.5 * sqr(1.5 - (j + 1) + xii);
            m_rho[j + 1] += a * qdx;
            m_rho[j + 2] += b * qdx;
            m_rho[j] += (1.0 - a - b) * qdx;
        }
        break;
    case Cubic_Spline :
        for (int i = il ;i <= iu; i++) {
            m_x[i] *= dxi;
            if (m_x[i] <0.0)
                m_x[i] += xn;
            else {
                if (m_x[i] >= xn)
                    m_x[i] -= xn;
            }
            xii = m_x[i];
            j = xii + 0.5;
            if ((j - xii) >= 0) {
                a = 0.5 * cube(j - xii) - sqr(j - xii) + twothirds;
                b = -0.5 * cube(j - 1 - xii) - sqr(j - 1 - xii) + twothirds;
                c = -cube(j + 1 - xii) / 6.0 + sqr(j + 1 - xii) - 2 * (j + 1 - xii) + 1.3333333;
                m_rho[j + 1] += a * qdx;
                m_rho[j + 2] += c * qdx;
                m_rho[j] += b * qdx;
                m_rho[j - 1] += (1.0 - a - b - c) * qdx;
            }
            else {
                a = -0.5 * cube(j - xii) - sqr(j - xii) + twothirds;
                b = 0.5 * cube(j + 1 - xii) - sqr(j + 1 - xii) + twothirds;
                c = cube(j - 1 - xii) / 6.0 + sqr(j - 1 - xii) + 2 * (j - 1 - xii) + 1.3333333;
                m_rho[j + 1] += a * qdx;
                m_rho[j + 2] += b * qdx;
                m_rho[j] += c * qdx;
                m_rho[j + 3] += (1.0 - a - b - c) * qdx;
            }
        }
        break;
    default:
        qDebug(" Bad iw switch in setrho.");
        // exit(-1);
        break;
    }
}

void PhysElectroStatic::setv(const int il, const int iu,
                             const double q, const double m,
                             const double t, double *p,
                             double *ke) {

    if (!ke || !p)
        return;
    double dtdx, c, s, vxx;
    dtdx = m_dt / m_dx;
    if (t != 0.0) {
        c = 1.0 / sqrt(1.0 + t * t);
        s = c * t;
        for (int i = il; i <= iu; i++) {
            vxx = m_vx[i];
            m_vx[i] =  c * vxx + s * m_vy[i];
            m_vy[i] = -s * vxx + c * m_vy[i];
            m_vy[i] *= dtdx;
        }
    }
    for (int i = il; i <= iu; i++)
        m_vx[i] *= dtdx;
    accel(il, iu, -0.5 * q, m, 0.0, p, ke);
}

void PhysElectroStatic::velocity() {
    int s, nbinmaxi;
    static int count = 5;
    double pval;
    double *vsps = NULL;    // vsps is a pointer to the part of the velocity bin array where the species starts
    double vst, dvt; // this is the vstart[isp],dv[isp]

    if (!m_accum)
        return; // if the accum is set to zero, don't bother making a current velocity distribution profile.
    pval = 1.0 / m_accum;

    // This code does the velocity-distribution stuff.
    count--;
    if (!count) {
        for (int j = 0; j <= m_nvbin[1]; j++)
            m_vbint[j] = 0.0;
        for (int i = 1; i <= m_nsp; i++) {
            for (int j = m_vbins[i]; j <= m_vbins[i] + m_nvbin[i]; j++) {
                m_vbin[j] = m_ms[i] * m_vbin_inst[j];
                m_vbin_inst[j] = 0.0;
            }
            for (int j = 0; j <= m_nvbin[1]; j++)
                m_vbint[j] += m_vbin[j + m_vbins[i]];
        }
    }
    if (!count)
        count = m_accum;
    for (int i = 1; i <= m_nsp; i++) {
        vsps = &(m_vbin_inst[m_vbins[i]]);
        if (!vsps)
            break;
        vst = m_vbinstart[i];
        dvt = m_dvbin[i];
        nbinmaxi = m_nvbin[i];
        if (nbinmaxi > 0) {
            for (int j = m_ins[i]; j < m_ins[i + 1]; j++) {
                s = (m_vx[j] - vst) / dvt;
                if (s >= 0 && s < nbinmaxi)
                    vsps[s] += pval;
            }
        }
    }
}

void PhysElectroStatic::history() {
    static int count = 1;
    int i = 0, k = 0;

    // only accum every interval steps
    if (--count)
        return;

    // comb time histories
    if (m_hist_hi >= HISTMAX) {
        for (int j = 0; j < m_nsp; j++) {
            for (int i = 1, k = 4; i < HISTMAX / 4; i++, k += 4) {
                m_kes[j][i] = m_kes[j][k];
                m_pxs[j][i] = m_pxs[j][k];
            }
        }
        for (int j = 0; j < m_mmax; j++) {
            for (int i = 1, k = 4; i < HISTMAX / 4; i++, k += 4)
                m_esem[j][i] = m_esem[j][k];
        }
        for (i = 1, k = 4; i < HISTMAX / 4; i++, k += 4) {
            m_ese[i] = m_ese[k];
            m_ke[i] = m_ke[k];
            m_te[i] = m_te[k];
            m_t_array[i] = m_t_array[k];
        }
        m_hist_hi = i;
        m_interval *= 4;
    }
    m_t_array[m_hist_hi] = m_t;
    for (int i = 0; i < m_mmax; i++)
        m_esem[i][m_hist_hi] = fabs(m_esem_hist[i + 1]) + 1e-30;
    m_ke[m_hist_hi] = 1e-30;
    for (int j = 0; j < m_nsp; j++) {
        m_kes[j][m_hist_hi] = m_kes_hist[j + 1];
        m_ke[m_hist_hi] += m_kes_hist[j + 1];
        m_pxs[j][m_hist_hi] = m_pxs_hist[j + 1];
    }
    m_te[m_hist_hi] = m_ke[m_hist_hi] + m_ese_hist;
    m_ese[m_hist_hi] = m_ese_hist + 1e-30;
    m_hist_hi++;
    count = m_interval;
}

double PhysElectroStatic::frand() {

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    return static_cast<qreal>(qrand()) / RAND_MAX ;
    /*
    long a = 16807, m = 2147483647, q = 127773, r = 2836;
    long hi, lo;
    static long seed = 31207321;
    double fnumb;

    hi = seed / q;
    lo = seed - q * hi;
    seed = a * lo - r * hi;

    // "seed" will always be a legal integer of 32 bits (including sign).
    if (seed <= 0)
        seed += m;
    fnumb = seed / 2147483646.0;
    return(fnumb);
    */
}
