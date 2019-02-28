/************************************************************************

    filter.h

    ld-efm-sampletodata - EFM sample to data processor for ld-decode
    Copyright (C) 2019 Simon Inns

    This file is part of ld-decode-tools.

    ld-efm-sampletodata is free software: you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

************************************************************************/

#ifndef FILTER_H
#define FILTER_H

#include <QCoreApplication>
#include <QDebug>

class Filter
{
public:
    Filter();
    QVector<qint16> dcBlocker(QVector<qint16> inputSample);
    QVector<qint16> channelEqualizer(QVector<qint16> inputSample);

private:
    // DC blocker filter ----------------------------------------------------------------------------------------------

    qint32 acc;
    qint32 previousInputSample;
    qint32 previousOutputSample;

    // Channel equalizer filter ---------------------------------------------------------------------------------------

    // M = Amount of over sampling
    // D = Number of symbols to be spanned by the impulse response
    // N = D * M (where both M and D are integers)
    //
    // Oversampling is 40,000,000 / 4,321,800 = 9.255402841
    // Best if D and M are integer multiples
    //
    // N = 9 * 9 = 81 taps

    // Generated by:   http://www-users.cs.york.ac.uk/~fisher/mkfilter
    //    filtertype 	= 	Raised Cosine
    //    samplerate 	= 	40000000
    //    corner 	= 	2160900
    //    beta 	= 	0.75
    //    impulselen 	= 	81
    //    racos 	= 	yes
    //    comp 	= 	no
    //    bits 	=
    //    logmin 	=

    /* Digital filter designed by mkfilter/mkshape/gencode   A.J. Fisher
       Command line: /www/usr/fisher/helpers/mkshape -c 5.4022500000e-02 7.5000000000e-01 81 -l */

    static const qint32 ceNZeros = 80;
    static constexpr qreal ceGain = 9.242164001e+00;
    qreal ceXv[ceNZeros+1];

    const qreal ceXcoeffs[ceNZeros+1] = {
        +0.0011044895, +0.0010568237, +0.0006633417, -0.0000167251,
        -0.0008134835, -0.0014891333, -0.0018127885, -0.0016467116,
        -0.0010156983, -0.0001320344, +0.0006414018, +0.0008894171,
        +0.0002825805, -0.0012844795, -0.0036026125, -0.0061480156,
        -0.0081944327, -0.0090277780, -0.0082175967, -0.0058704113,
        -0.0027769357, -0.0003753228, -0.0004875344, -0.0048403667,
        -0.0144451771, -0.0289655136, -0.0462338303, -0.0620752464,
        -0.0705532094, -0.0646737727, -0.0374861355, +0.0165819447,
        +0.1003910242, +0.2130286960, +0.3492669318, +0.4997067448,
        +0.6516580575, +0.7906621872, +0.9024331239, +0.9749001734,
        +1.0000000171, +0.9749001734, +0.9024331239, +0.7906621872,
        +0.6516580575, +0.4997067448, +0.3492669318, +0.2130286960,
        +0.1003910242, +0.0165819447, -0.0374861355, -0.0646737727,
        -0.0705532094, -0.0620752464, -0.0462338303, -0.0289655136,
        -0.0144451771, -0.0048403667, -0.0004875344, -0.0003753228,
        -0.0027769357, -0.0058704113, -0.0082175967, -0.0090277780,
        -0.0081944327, -0.0061480156, -0.0036026125, -0.0012844795,
        +0.0002825805, +0.0008894171, +0.0006414018, -0.0001320344,
        -0.0010156983, -0.0016467116, -0.0018127885, -0.0014891333,
        -0.0008134835, -0.0000167251, +0.0006633417, +0.0010568237,
        +0.0011044895,
    };

    // Method prototypes ----------------------------------------------------------------------------------------------
    qreal channelEqualizerFir(qreal inputSample);
};

#endif // FILTER_H