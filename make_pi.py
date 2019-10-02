import mpmath

mpmath.mp.prec = 3000

tmp = mpmath.frac(mpmath.mp.pi)

with open('pi.inc', 'w') as f:
    print('{', file=f)
    nbytes = 2281 // 8 + 1
    for i in range(0, nbytes):
        end = ','
        if i == nbytes - 1:
            end = ''
        tmp = mpmath.fmul(tmp, 16 * 16)
        print('  ', hex(int(mpmath.floor(tmp))), end, sep='', file=f)
        tmp = mpmath.frac(tmp)
    print('};', file=f)
