/* cython_special.c: deprecated code from scipy-v1.1.0/special/cephes/yv.c
 *
 * Rutger van Haasteren, June 29 2023, Den Haag
 *
 * This code is distributed under a compatible license:
 * 
 * Files: scipy/special/cephes/*
 * License: 3-clause BSD
 *   Distributed under 3-clause BSD license with permission from the author,
 *   see https://lists.debian.org/debian-legal/2004/12/msg00295.html
 * 
 *   Cephes Math Library Release 2.8:  June, 2000
 *   Copyright 1984, 1995, 2000 by Stephen L. Moshier
 * 
 *   This software is derived from the Cephes Math Library and is
 *   incorporated herein by permission of the author.
 * 
 *   All rights reserved.
 * 
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions are met:
 *       * Redistributions of source code must retain the above copyright
 *         notice, this list of conditions and the following disclaimer.
 *       * Redistributions in binary form must reproduce the above copyright
 *         notice, this list of conditions and the following disclaimer in the
 *         documentation and/or other materials provided with the distribution.
 *       * Neither the name of the <organization> nor the
 *         names of its contributors may be used to endorse or promote products
 *         derived from this software without specific prior written permission.
 * 
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 *   ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 *   DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *   ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 *
 */


// hyp1f2, and hyp3f0  (hyp2f0 not yet)

#include <math.h>
#include <stdio.h>

#define MACHEP 1.11022302462515654042E-16
#define DEBUG 0

double onef2(double a, double b, double c, double x, double *err)
{
    double n, a0, sum, t;
    double an, bn, cn, max, z;
    double stop = MACHEP;

    an = a;
    bn = b;
    cn = c;
    a0 = 1.0;
    sum = 1.0;
    n = 1.0;
    t = 1.0;
    max = 0.0;

    do {
        if (an == 0)
            goto done;
        if (bn == 0)
            goto error;
        if (cn == 0)
            goto error;
        if ((a0 > 1.0e34) || (n > 200))
            goto error;
        a0 *= (an * x) / (bn * cn * n);
        sum += a0;
        an += 1.0;
        bn += 1.0;
        cn += 1.0;
        n += 1.0;
        z = fabs(a0);
        if (z > max)
            max = z;
        if (sum != 0)
            t = fabs(a0 / sum);
        else
            t = z;
    }
    while (t > stop);

  done:

    *err = fabs(MACHEP * max / sum);

    goto xit;

  error:
    *err = 1.0e38;

  xit:
    return (sum);
}


double threef0(double a, double b, double c, double x, double *err)
{
    double n, a0, sum, t, conv, conv1;
    double an, bn, cn, max, z;
    double stop = MACHEP;

    an = a;
    bn = b;
    cn = c;
    a0 = 1.0;
    sum = 1.0;
    n = 1.0;
    t = 1.0;
    max = 0.0;
    conv = 1.0e38;
    conv1 = conv;

    do {
	if (an == 0.0)
	    goto done;
	if (bn == 0.0)
	    goto done;
	if (cn == 0.0)
	    goto done;
	if ((a0 > 1.0e34) || (n > 200))
	    goto error;
	a0 *= (an * bn * cn * x) / n;
	an += 1.0;
	bn += 1.0;
	cn += 1.0;
	n += 1.0;
	z = fabs(a0);
	if (z > max)
	    max = z;
	if (z >= conv) {
	    if ((z < max) && (z > conv1))
		goto done;
	}
	conv1 = conv;
	conv = z;
	sum += a0;
	if (sum != 0)
	    t = fabs(a0 / sum);
	else
	    t = z;
    }
    while (t > stop);

  done:

    t = fabs(MACHEP * max / sum);
#if DEBUG
    printf(" threef0 cancellation error %.5E\n", t);
#endif

    max = fabs(conv / sum);
    if (max > t)
	t = max;
#if DEBUG
    printf(" threef0 convergence %.5E\n", max);
#endif

    goto xit;

  error:
#if DEBUG
    printf("threef0 does not converge\n");
#endif
    t = 1.0e38;

  xit:

#if DEBUG
    printf("threef0( %.2E %.2E %.2E %.5E ) =  %.3E  %.6E\n", a, b, c, x, n,
	   sum);
#endif

    *err = t;
    return (sum);
}
