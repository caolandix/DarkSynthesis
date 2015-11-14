#include <QTime>

#include <math.h>
#include "physelectrostatic.h"
#include "physscience.h"

PhysElectroStatic::PhysElectroStatic() {

    // Setting the global parameters to their default values.
    l = 6.283185307;
    dt = 0.2;
    nsp = 1;
    epsi = 1.0;
    ng = 32;
    iw = 2;
    ec = 0;
    ins[1] = 1;
    vbins[1] = 1;  // sets up the start of vbin.
    interval = 1;
}

PhysElectroStatic::~PhysElectroStatic() {
    if (nms) { delete [] nms; nms = NULL; }
    if (ms) { delete [] ms; ms = NULL; }
    if (qs) { delete [] qs; qs = NULL; }
    if (ts) { delete [] ts; ts = NULL; }
    if (x_array) { delete [] x_array; x_array = NULL; }
    if (rho) { delete [] rho; rho = NULL; }
    if (phi) { delete [] phi; phi = NULL; }
    if (phik) { delete [] phik; phik = NULL; }
    if (e) { delete [] e; e = NULL; }
    if (acc) { delete [] acc; acc = NULL; }
    if (t_array) { delete [] t_array; t_array = NULL; }
    if (ese) { delete [] ese; ese = NULL; }
    if (ke) { delete [] ke; ke = NULL; }
    if (te) { delete [] te; te = NULL; }
    if (kes_hist) { delete [] kes_hist; kes_hist = NULL; }
    if (pxs_hist) { delete [] pxs_hist; pxs_hist = NULL; }
    if (esem_hist) { delete [] esem_hist; esem_hist = NULL; }
    if (x) { delete [] x; x = NULL; }
    if (vx) { delete [] vx; vx = NULL; }
    if (vy) { delete [] vy; vy = NULL; }
    if (vbint) { delete [] vbint; vbint = NULL; }
    if (vbin) { delete [] vbin; vbin = NULL; }
    if (vbin_inst) { delete [] vbin_inst; vbin_inst = NULL; }
    if (dvbin) { delete [] dvbin; dvbin = NULL; }
    if (vbinstart) { delete [] vbinstart; vbinstart = NULL; }
    if (v_array) { delete [] v_array; v_array = NULL; }

    // arrays of pointers
    if (nms) { delete [] kes; kes = NULL; }
    if (nms) { delete [] pxs; pxs = NULL; }
    if (nms) { delete [] esem; esem = NULL; }
}

void PhysElectroStatic::init(int *il1, int *il2, double *m, double *q, double *t,
                             double *nm, int *vbin1, int *vbin2, double *dvb, double *vstart, int *nvbin) {
    double wp = 1.0, wc = 0.0, qm = -1.0, vt1 = 0.0, vt2 = 0.0, v0 =0.0,
        x1 = 0.0, v1 = 0.0, thetax = 0.0, thetav = 0.0, ddx, x0,
        vmax, dv, vvnv2, vv, fv, df, xs, xsi, theta, lg, vupper,vlower;
    int ngr, j, i1, i2, n = 128, nlg = 1, nv2 = 0, mode = 1, nbins = 100;
    char a_char[80];

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

    *t = tan(-0.5 * wc * dt);
    *il2 = *il1 + n;

    *q = l * wp * wp / (epsi * n * qm);
    *m = *q / qm;
    *nm = n * (*m);
    ngr = n / nlg;
    lg = l / nlg;
    ddx = l / n;


    if (nbins > NVBINMAX)
        nbins = NVBINMAX;
    if (nbins < 2)
        nbins = 2;
    *nvbin = nbins;
    *vbin2 = *vbin1 + nbins;
    if (vupper - vlower < 0.0) {
        qDebug("\nError in INIT: vupper must be > vlower!");
        return;
    }
    if (vt1 < 0 || vt2 < 0) {
        qDebug("\nError in INIT: can't have negative thermal voltages!");
        return;
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
        v_array[i] = (*vstart + (i - *vbin1 + 0.5) * (*dvb));

    for (int i = 1; i <= ngr; i++) {
        i1 = i - 1 + *il1;
        x0 = (i - 0.5) * ddx;
        x[i1] = x0;
        vx[i1] = v0;
    }
    if (vt2 != 0.0) {
        vmax = 5.0 * vt2;
        dv = 2.0 * vmax / (n - 1);
        vvnv2 = 1.0;
        x[*il1] = 0.0;
        for (int i = 2; i <= n; i++) {
            vv = ((i - 1.5) * dv - vmax) / vt2;
            if (nv2 != 0)
                vvnv2 = pow(vv, (double)nv2);
            fv = vvnv2 * exp(-0.5 * vv * vv);
            i1 = i - 1 + *il1;
            x[i1] = x[i1 - 1] + ((fv >= 0.0) ? fv : 0.0);
        }
        df = x[i1]/ngr;
        i1 = *il1;
        j = *il1;
        for (int i = 1; i <= ngr; i++) {
            fv = (i - 0.5) * df;
            while (fv >= x[j + 1]) {
                j++;
                if (j > (*il2 - 2))
                    qDebug("distribution function error");
            }
            vv = dv * (j - *il1 + (fv - x[j]) / (x[j + 1] - x[j])) - vmax;
            vx[i1] += vv;
            i1++;
        }
        xs = 0.0;
        for (int i = 1; i <= ngr; i++) {
            i1 = i - 1 + *il1;
            x[i1] = xs * lg + 0.5 * ddx;
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
            vv = vx[i1];
            theta = 2 * PhysConsts::PI * frand();
            vx[i1] = vv * cos(theta);
            vy[i1] = vv * sin(theta);
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
                x[i2] = x[i1] + xs;
                vx[i2] = vx[i1];
                if (wc != 0.0)
                    vy[i2] = vy[i1];
            }
        }
    }
    if (vt1 != 0.0) {
        for (int i = 1;i <= n; i++) {
            i1 = i - 1 + *il1;
            for (int j = 0; j < 12; j++) {
                if (wc != 0.0)
                    vy[i1] += vt1 * (frand() - 0.5);
                vx[i1] += vt1 * (frand() - 0.5);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        i1 = i - 1 + *il1;
        theta = 2 * PhysConsts::PI * mode * x[i1] / l;
        x[i1] += x1 * cos(theta + thetax);
        vx[i1] += v1 * sin(theta + thetav);
    }
    setrho(*il1, *il2 - 1, *q, (*q) * n / l);
}

void PhysElectroStatic::start(int argc, char *argv) {
    char a_char[80];
    bool WasInputFileGiven = false;
    QString filename;

    // InputDeck = (!WasInputFileGiven) ? fopen("es1data","r") :  fopen(theInputFile,"r");
    // if (!InputDeck) {
    if (false) {
        qDebug("Can't find input file %s",argv[1]);
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
        if (nsp > NSPM) {
            qDebug("Number of species nsp cannot exceed NSPM");
            return;
        }

        if (accum<0) {
            qDebug("Error:  accum can't be negative!");
            return;
        }

        if(!(ec == 1 || ec == 0)) {
            qDebug("Error:  What are you thinking?  There are only two possible values of ec");
            qDebug("0 and 1.  %d is not 0 or 1.",ec);
            return;
        }
        if (!iw && ec) {
            qDebug("Error:  There IS no energy-conserving algorithm for NGP");
            return;
        }

        ecconst = (ec) ? 0.5 : 0.0;
        if (iw > 3 || iw < 0) {
            qDebug("Error:  bad iw flag!  Please check your input deck!");
            return;
        }

        if (ng > NGMAX) {
            printf("Number of grids ng cannot exceed NGMAX");
            return;
        }
        dx = l / ng;
        ng1 = ng + 1;
        k_hi = ng / 2;

        // Allocating space for arrays
        nms = new double[nsp + 1];
        ms = new double[nsp + 1];
        qs = new double[nsp + 1];
        ts = new double[nsp + 1];

        x_array = new double[ng + 1];
        for (int i = 0; i <= ng; i++)
            x_array[i] = i * dx;

        rho = new double[ng + 3];
        phi = new double[ng + 2];
        phik = new double[ng + 2];
        k_array = new double[ng];
        for (int i = 0; i < k_hi; i++)
            k_array[i] = i * 2 * PhysConsts::PI / l;
        e = new double[ng + 2];
        acc = new double[ng + 3];

        t_array = new double[HISTMAX];
        ese = new double[HISTMAX];
        ke = new double[HISTMAX];
        te = new double[HISTMAX];

        kes_hist = new double[nsp+1];
        pxs_hist = new double[nsp+1];
        esem_hist = new double[mmax+1];

        kes = new double*[nsp];
        for (int i = 0; i < nsp; i++)
            kes[i] = new double[HISTMAX];

        pxs = new double*[nsp];
        for (int i=0; i< nsp; i++)
            pxs[i] = new double[HISTMAX];

        esem = new double*[mmax];
        for (int i=0; i< mmax; i++)
            esem[i] = new double[HISTMAX];

        x = new double[MAXPARTICLES];
        vx = new double[MAXPARTICLES];
        vy = new double[MAXPARTICLES];

        vbint = new double[NVBINMAX];
        vbin = new double[nsp * NVBINMAX];
        vbin_inst = new double[nsp * NVBINMAX];
        for (int i = 0; i < nsp * NVBINMAX; i++)
            vbin_inst[i]= 0.0;
        dvbin = new double[nsp + 1];
        vbinstart = new double[nsp + 1];
        v_array = new double[NVBINMAX * nsp];

        if (!x || !vx || !vy || !vbint || !vbin_inst || !dvbin || !v_array ) {
            qDebug("START: Could not get enough memory for x or v's.");
            return;
        }

        qDebug("nsp = %2d     l = %8.5f", nsp, l);
        qDebug("dt = %4.2f    nt = %4d", dt, nt);
        qDebug("ng = %5d   iw = %2d   ec = %2d  accum = %4d", ng, iw, ec, accum);
        qDebug("epsi = %4.2f  a1 = %4.2f  a2 = %4.2f", epsi ,a1, a2);

        for (int i = 1; i <= nsp; i++)
            init(&ins[i], &ins[i + 1], &ms[i], &qs[i], &ts[i], &nms[i], &vbins[i], &vbins[i+1], &dvbin[i], &vbinstart[i], &nvbin[i]);

        // added vbins to param list
        // fclose(InputDeck);

        for (int i=1; i<= nsp; i++)
            np[i]= ins[i+1] -ins[i];

        for (int i=0; i < nsp; i++) {
            for (int j=0; j < HISTMAX; j++) {
                kes[i][j] = 0.0;
                pxs[i][j] = 0.0;
            }
        }
        rho[1] += rho[ng1];   // These resolve the periodic boundary conditions.
        rho[2] += rho[ng + 2];
        rho[ng] += rho[0];
        rho[0] = rho[ng];
        rho[ng + 2] = rho[2];
        rho[ng1] = rho[1];
        fields(0);

        for (int i = 1; i <= nsp; i++) {
            setv(ins[i], ins[i + 1] - 1, qs[i], ms[i], ts[i], &pxs_hist[i], &kes_hist[i]);

            // scale all the velocities  properly
            dvbin[i] *= dt / dx;
            vbinstart[i] *= dt / dx;
        }
        startvel();
    }
}


// all this function does is set up the initial velocity distribution diagnostic to reflect the startup values.
void PhysElectroStatic::startvel() {
    int s, nbinmaxi;
    double *vsps;          // vsps is a pointer to the part of the velocity bin array where the species starts
    double vst,dvt;        // this is the vstart[isp],dv[isp]

    // This code does the velocity-distribution stuff.
    for (int i = 1; i <= nsp; i++) {
        vsps = &(vbin[vbins[i]]);
        vst = vbinstart[i];
        dvt = dvbin[i];
        nbinmaxi = nvbin[i];
        for (int j = vbins[i]; j <= vbins[i] + nvbin[i]; j++)
            vbin[j] = 0.0;
        if (nbinmaxi > 0 && accum) {
            for (int j = ins[i]; j < ins[i + 1]; j++) {
                s = (vx[j] - vst) / dvt;
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
    dxdt = dx / dt;
    ae = (q / m) * (dt / dxdt);
    if (t != 0.0)
        ae *= 0.5;
    if (ae != ael) {
        ng1 = ng + 1;

        // tem = ae/ael;  this does nothing, is not used later
        for (int j = 1; j <= ng1; j++)
            acc[j] = e[j] * ae;
        acc[0] = ae * e[ng];
        acc[ng + 2] = ae * e[2];
        acc[ng1] = ae * e[1];
        ael = ae;
    }
    switch (iw - ec) {
    case Zero_Order :
        v1s = v2s = 0.0;
        for (int i = il; i <= iu; i++) {
            j = x[i] + 0.5 - ecconst;  // ecconst is .5 for energy conserving, 0 for momentum conserving
            vo = vx[i];
            vn = vo + acc[j+1];
            v1s += vn;
            v2s += vn * vo;
            vx[i] = vn;
        }
        *p = m * v1s * dxdt;
        *ke = 0.5 * m * v2s * dxdt * dxdt;
        break;
    case First_Order :
        if (t != 0.0) {
            s = 2.0 * t / (1.0 + t * t);
            v2s = 0.0;
            for (int i = il; i <= iu; i++) {
                xii = x[i] - ecconst + 1.0;
                j = xii;
                xii -= 1.0;
                j -= 1;

                // the reason for the addition and subtraction of 1 to xii is to avoid an error condition
                // in which the truncation causes it to truncate UP instead of round down when 0<= x[i] <0.5.
                // The modification ensures that it gets set to the right value.
                aa = acc[j + 1] + (xii - j) * (acc[j + 2] - acc[j + 1]);
                vyy = vy[i];
                vxx = vx[i] - t * vyy + aa;
                vyy += s * vxx;
                vxx -= t * vyy;
                v2s += vxx * vxx + vyy * vyy;
                vx[i] = vxx + aa;
                vy[i] = vyy;
            }
            *ke = 0.5 * m * v2s * dxdt * dxdt;
        }
        else {
            v1s = v2s = 0.0;
            for (int i = il; i <= iu; i++) {
                xii = x[i] - ecconst + 1;
                j = xii;
                xii -= 1.0;
                j -= 1;
                // the reason for the addition and subtraction of 1 to xii is to avoid an error condition
                // in which the truncation causes it to truncate UP instead of round down when 0<= x[i] <0.5.
                // The modification ensures that it gets set to the right value.
                vo = vx[i];
                vn = vo + acc[j + 1] + (xii - j) * (acc[j + 2] - acc[j + 1]);
                v1s += vn;
                v2s += vo * vn;
                vx[i] = vn;
            }
            *p = m * v1s * dxdt;
            *ke = 0.5 * m * v2s * dxdt * dxdt;
        }
        break;
    case Quadratic_Spline :
        v1s = v2s = 0.0;
        for (int i = il; i <= iu; i++) {
            xii = x[i] - ecconst; //Grab the value of x[i] so we don't have to keep dereferencing a pointer
            j = xii + 0.5;   // Grab the nearest grid point.
            vo = vx[i];    // Grab the value of the current velocity
            a = 0.75 - sqr(j - xii);
            b = 0.5 * sqr(0.5 - j + xii);
            vn = vo + a * acc[j + 1] + b * acc[j + 2] + (1 - a - b) * acc[j];
            v1s += vn;
            v2s += vn * vo;
            vx[i] = vn;
        }
        *p = m * v1s * dxdt;
        *ke = 0.5 * m * v2s * dxdt * dxdt;
        break;
    case Cubic_Spline :
        v1s = v2s = 0.0;
        for (int i = il; i <= iu; i++) {
            xii = x[i];
            j = xii + 0.5;
            vo = vx[i];
            jxii = j - xii;
            if (jxii >= 0) {
                // The commented assignments are unoptimized.  The uncommented assignments below are optimized
                // to reduce the number of multiplications, etc...

                //a=.5*cube(jxii)-sqr(jxii)+.6666666667;
                a = twothirds + jxii * jxii * (-1.0 + 0.5 * jxii);

                // b= -.5*cube(jxii-1)-sqr(jxii-1)+.6666666667;
                b = onesix+ 0.5 * jxii * (1.0 + jxii * (1.0 - jxii));

                // c= -cube(jxii+1)/6.0+sqr(jxii+1)-2*(jxii+1)+1.3333333;
                c = onesix + onesix * jxii * (-3.0 + jxii * (3.0 - jxii));
                vn = vo + a * acc[j + 1] + b * acc[j] + c * acc[j + 2] + (1.0 - a - b - c) * acc[j - 1];
            }
            else {
                // a= -.5*cube(jxii)-sqr(jxii)+.6666666667;
                a = twothirds - jxii * jxii * ( 1.0 + 0.5 * jxii);

                // b=.5*cube(jxii+1)-sqr(jxii+1)+.6666666667;
                b = onesix + 0.5 * jxii*(-1.0 + jxii * ( 1.0 + jxii));

                // c= cube(jxii-1)/6.0+sqr(jxii-1)+2*(jxii-1)+1.3333333;
                c = onesix + onesix * jxii * (3 + jxii * (3 + jxii));

                vn = vo + a * acc[j + 1] + b * acc[j + 2] + c * acc[j] + (1.0 - a - b - c) * acc[j + 3];
            }
            v1s += vn;
            v2s += vn * vo;
            vx[i] = vn;
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
    static double *ksqi, *sm;
    int kk, km;
    int k, j;
    double kdx2, li, hdx, eses, eot, hdxi, dxi, temp, temp1, e0t, kperp2;

    if (ng2 == 0) {
        ng2 = ng / 2;
        ksqi = new double[ng2 + 1];
        sm = new double[ng2 + 1];
        ng1 = ng + 1;
        kperp2 = AKPERP * AKPERP * (la / l * la / l); /* a = charge disk radius*/
        for (int k = 1; k <= ng2; k++) {
            kdx2 = (PhysConsts::PI / ng) * k;
            if ((a1 != 0.0) || (a2 != 0.0)) {
                temp = (k < ng2) ? tan(kdx2) : 10000.0;
                temp *= temp;
                temp *= temp; // suspect overflows at k=ng2
                temp1 = sin(kdx2);
                temp1 *= temp1;
                sm[k] = exp(a1 * temp1 - a2 * temp);
                if (sm[k] < 1.0E-10)
                    sm[k] = 0.0;
            }
            else
                sm[k] = 1.0;
            temp = 2.0 * sin(kdx2) / dx;
            temp = temp * temp;
            temp += kperp2;
            ksqi[k] = (epsi / temp) * sm[k] * sm[k];
        }
    }
    hdx = 0.5 * dx;
    for (int j = 1; j <= ng; j++) {
        rho[j] *= hdx;
        e[j] = 0.0;
    }
    cpft(rho, e, ng, 1, 1.0);
    rpft2(rho, e, ng, 1);
    rho[1] = eses = phi[1] = 0.0;
    for (int k = 2;k <= ng2 ;k++) {
        kk = ng + 2 - k;
        phi[k] = ksqi[k-1] * rho[k];
        phi[kk] = ksqi[k-1] * rho[kk];
        eses += rho[k] * phi[k] + rho[kk] * phi[kk];
    }
    phi[ng2 + 1] = ksqi[ng2] * rho[ng2 + 1];
    ese_hist = (2.0 * eses + rho[ng2 + 1] * phi[ng2 + 1]) / (2.0 * l);
    li = 1.0 / l;

    for (int km=1; km <=mmax; km++) {
        k = km +1;
        if (k ==1)
            break;
        kk = ng +2 -k;
        esem_hist[km] = (rho[k]*phi[k] + rho[kk]*phi[kk])*li;
        if (k == kk)
            esem_hist[km] *= 0.25;
    }
    for (int k=2; k<=ng2; k++){
        kk = ng-k;
        rho[k] *= sm[k-1];
        rho[kk] *= sm[k-1];
    }
    rho[ng2+1] *= sm[ng2];
    for (int k=1; k <= ng ;k++) {
        rho[k] *= li;
        phi[k] *= li;
    }

    phik[1] = 1e-30;
    for (int k=1;k <=ng2; k++) {
        kk = ng +2 -k;
        phik[k] = li*fabs(phi[k]*rho[k] +phi[kk]*rho[kk]) +1e-30;
    }
    rpfti2(phi, rho, ng, 1);
    cpft(phi, rho, ng, 1, -1.0);
    phi[ng1] = phi[1];
    rho[ng1] = rho[1];
    e0t = (e0 != 0.0) ?  e0 * cos(w0 * t) : 0.0;
    switch (ec) {
    case Momentum_Conserving:
        hdxi = 0.5/dx;
        for (int j=2;j <= ng;j++) e[j] = (phi[j-1]-phi[j+1])*hdxi + e0t;
        e[1] = (phi[ng]-phi[2])*hdxi + e0t;
        e[ng + 1] = e[1];
        break;
    case Energy_Conserving:
        dxi = 1.0/dx;
        for (int j=1;j <= ng;j++) e[j] = (phi[j]-phi[j+1])*dxi + e0t;
        e[ng + 1] = e[1];
        break;
    default:
        qDebug("Bad ec switch in fields");
        // exit(-1);
        break;
    }
    ael = 1.0;
}

void PhysElectroStatic::move(const int ilp, const int iup, const double q) {
    int il, iu;
    int j;
    double xn, qdx, drho;
    double a, b, c, xii;
    double jxii;  // = j-xii:  we use it so much it's worth defining it.

    il = ilp;
    iu = iup;
    qdx = q/dx;
    xn = ng;
    switch (iw) {
    case Zero_Order :
        for (int i = il; i <= iu; i++) {
            x[i] += vx[i];
            if (x[i] < 0.0)
                x[i] += xn;
            else {
                if (x[i] >= xn)
                    x[i] -= xn;
            }
            j = x[i] + 0.5;
            rho[j+1] += qdx;
        }
        break;
    case First_Order :
        for (int i = il; i <= iu; i++) {
            x[i] += vx[i];
            if (x[i] < 0.0)
                x[i] += xn;
            else {
                if (x[i] >= xn)
                    x[i] -= xn;
            }
            j = x[i];
            drho = qdx * (x[i] - j);
            rho[j + 1] += qdx - drho;
            rho[j + 2] += drho;
        }
        break;
    case Quadratic_Spline :
        for (int i = il; i <= iu; i++) {
            x[i] += vx[i];
            if (x[i] < 0.0)
                x[i] += xn;
            else {
                if (x[i] >= xn)
                    x[i] -= xn;
            }

            // By looking up x[i] and storing it in xii, I save three additions: I must do an addition every
            // time I use a subscript!
            xii = x[i];

            // Extract the nearest grid point: using truncation to do rounding- j is int.
            j = xii + 0.5;

            // Get the coefficient for the nearest grid point. It's a function of the distance.
            a = 0.75 - sqr(j - xii);
            b = 0.5 * sqr(0.5 - j + xii);

            // Get the coefficient for the grid location one to the right.
            rho[j + 1] += a * qdx;
            rho[j + 2] += b * qdx;
            rho[j] += (1.0 - a - b) * qdx;
        }
        break;
    case Cubic_Spline :
        for (int i = il; i <= iu; i++) {
            x[i] += vx[i];
            if (x[i] < 0.0)
                x[i] += xn;
            else {
                if (x[i] >= xn)
                    x[i] -= xn;
            }
            xii = x[i];
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

                rho[j + 1] += a * qdx;
                rho[j + 2] += c * qdx;
                rho[j] += b * qdx;
                rho[j - 1] += (1.0 - a - b - c) * qdx;
            }
            else {

                // a= -.5*cub(jxii)-sqr(jxii)+twothirds;
                a=twothirds -jxii*jxii*( 1.0 + 0.5*jxii);

                // b=.5*cub(jxii+1)-sqr(jxii+1)+twothirds;
                b=onesix + 0.5 * jxii*(-1.0 + jxii*( 1.0 + jxii));

                // c= cub(jxii-1)/6.0+sqr(jxii-1)+2*(jxii-1)+1.3333333;
                c=onesix+ onesix*jxii*(3+jxii*(3+jxii));

                rho[j+1]+=a*qdx;
                rho[j+2]+=b*qdx;
                rho[j]+=c*qdx;
                rho[j+3]+=(1.0 -a -b -c) * qdx;
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

    qdx = q / dx;
    if (il == 1) {
        for (int j = 1; j <= ng; j++)
            rho[j] = rho0;
        rho[ng1] = 0.0;
        rho[0] = rho[ng + 2]=0.0;
        dxi = 1.0 / dx;
        xn = ng;
    }
    rho0 -= rhos;
    for (j = 1; j <= ng; j++)
        rho[j] -= rhos;
    switch (iw) {
    case Zero_Order :
        for (int i = il; i <= iu; i++) {
            x[i] *= dxi;
            if (x[i] < 0.0)
                x[i] += xn;
            if (x[i] >= xn)
                x[i] -= xn;
            j = x[i] + 0.5;
            rho[j + 1] += qdx;
        }
        break;
    case First_Order :
        for (int i = il; i <= iu; i++) {
            x[i] *= dxi;
            if (x[i] < 0.0)
                x[i] += xn;
            if (x[i] >= xn)
                x[i] -= xn;
            j = x[i];
            drho = qdx * (x[i] - j);
            rho[j + 1] += qdx - drho;
            rho[j + 2] += drho;
        }
        break;
    case Quadratic_Spline :
        for (int i = il; i <= iu; i++) {
            x[i] *= dxi;
            if (x[i] < 0.0)
                x[i] += xn;
            else {
                if (x[i] >= xn)
                    x[i] -= xn;
            }
            // By looking up x[i] and storing it in xii, save three additions --
            // I must do an addition every time I use a subscript!
            xii = x[i];

            // Extract the nearest grid point: using truncation to do rounding- j is int.
            j = xii + 0.5;

            // Get the coefficient for the nearest grid point.  It's a function of the distance.
            a = 0.75 - sqr(j - xii);

            // Get the coefficient for the grid location one to the right.  Since (j+2)-xii is aways
            // postive the fabs doesn`t need to be there.
            b = 0.5 * sqr(1.5 -  (j+1) + xii);
            rho[j + 1] += a * qdx;
            rho[j + 2] += b * qdx;
            rho[j] += (1.0 - a - b) * qdx;
        }
        break;
    case Cubic_Spline :
        for (int i = il ;i <= iu; i++) {
            x[i] *= dxi;
            if (x[i] <0.0)
                x[i] += xn;
            else {
                if (x[i] >= xn)
                    x[i] -= xn;
            }
            xii = x[i];
            j = xii + 0.5;
            if ((j - xii) >= 0) {
                a = 0.5 * cube(j - xii) - sqr(j - xii) + twothirds;
                b = -0.5 * cube(j - 1 - xii) - sqr(j - 1 - xii) + twothirds;
                c = -cube(j + 1 - xii) / 6.0 + sqr(j + 1 - xii) - 2 * (j + 1 - xii) + 1.3333333;
                rho[j + 1] += a * qdx;
                rho[j + 2] += c * qdx;
                rho[j] += b * qdx;
                rho[j - 1] += (1.0 - a - b - c) * qdx;
            }
            else {
                a = -0.5 * cube(j - xii) - sqr(j - xii) + twothirds;
                b = 0.5 * cube(j + 1 - xii) - sqr(j + 1 - xii) + twothirds;
                c = cube(j - 1 - xii) / 6.0 + sqr(j - 1 - xii) + 2 * (j - 1 - xii) + 1.3333333;
                rho[j + 1] += a * qdx;
                rho[j + 2] += b * qdx;
                rho[j] += c * qdx;
                rho[j + 3] += (1.0 - a - b - c) * qdx;
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
    double dtdx, c, s, vxx;
    dtdx = dt / dx;
    if (t != 0.0) {
        c = 1.0 / sqrt(1.0 + t * t);
        s = c * t;
        for (int i = il; i <= iu; i++) {
            vxx = vx[i];
            vx[i] =  c * vxx + s * vy[i];
            vy[i] = -s * vxx + c * vy[i];
            vy[i] *= dtdx;
        }
    }
    for (int i = il; i <= iu; i++)
        vx[i] *= dtdx;
    accel(il, iu, -0.5 * q, m, 0.0, p, ke);
}

void PhysElectroStatic::velocity() {
    int s, nbinmaxi;
    static int count = 5;
    double pval;
    double *vsps;    // vsps is a pointer to the part of the velocity bin array where the species starts
    double vst, dvt; // this is the vstart[isp],dv[isp]

    if (!accum)
        return; // if the accum is set to zero, don't bother making a current velocity distribution profile.
    pval = 1.0 / accum;

    // This code does the velocity-distribution stuff.
    count--;
    if (!count) {
        for (int j = 0; j <= nvbin[1]; j++)
            vbint[j] = 0.0;
        for(int i = 1; i <= nsp; i++) {
            for (int j = vbins[i]; j <= vbins[i] + nvbin[i]; j++) {
                vbin[j] = ms[i] * vbin_inst[j];
                vbin_inst[j] = 0.0;
            }
            for (int j = 0; j <= nvbin[1]; j++)
                vbint[j] += vbin[j + vbins[i]];
        }
    }
    if (!count)
        count = accum;
    for (int i = 1; i <= nsp; i++) {
        vsps = & (vbin_inst[vbins[i]]);
        vst = vbinstart[i];
        dvt = dvbin[i];
        nbinmaxi = nvbin[i];
        if (nbinmaxi > 0) {
            for (int j = ins[i]; j < ins[i + 1]; j++) {
                s = (vx[j] - vst) / dvt;
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
    if (hist_hi >= HISTMAX) {
        for (int j = 0; j < nsp; j++) {
            for (int i = 1, k = 4; i < HISTMAX / 4; i++, k += 4) {
                kes[j][i] = kes[j][k];
                pxs[j][i] = pxs[j][k];
            }
        }
        for (int j = 0; j < mmax; j++) {
            for (int i = 1, k = 4; i < HISTMAX / 4; i++, k += 4)
                esem[j][i] = esem[j][k];
        }
        for (i = 1, k = 4; i < HISTMAX / 4; i++, k += 4) {
            ese[i] = ese[k];
            ke[i] = ke[k];
            te[i] = te[k];
            t_array[i] = t_array[k];
        }
        hist_hi = i;
        interval *= 4;
    }
    t_array[hist_hi] = t;
    for (int i = 0; i < mmax; i++)
        esem[i][hist_hi] = fabs(esem_hist[i + 1]) + 1e-30;
    ke[hist_hi] = 1e-30;
    for (int j = 0; j < nsp; j++) {
        kes[j][hist_hi] = kes_hist[j + 1];
        ke[hist_hi] += kes_hist[j + 1];
        pxs[j][hist_hi] = pxs_hist[j + 1];
    }
    te[hist_hi] = ke[hist_hi] + ese_hist;
    ese[hist_hi] = ese_hist + 1e-30;
    hist_hi++;
    count = interval;
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
