c     Simplest fortran example of doing a 1D type 1 transform with FINUFFT,
c     a math test of one output, and how to change from default options.
c     Single-precision (see simple1d1.f for double).
c     Legacy-style: f77, plus dynamic allocation & derived types from f90.

c     To compile (linux/GCC) from this directory, use eg (paste to one line):
      
c     gfortran -fopenmp -I../../include simple1d1f.f -o simple1d1f
c     -L../../lib -lfinufftf

c     Alex Barnett and Libin Lu 5/28/20, single-prec 6/2/20.

      program simple1d1f
      implicit none
      
c     our fortran header, only needed if want to set options...
      include 'finufft.fh'
c     this purely for wall-clock timer...
      include 'omp_lib.h'

c     note some inputs are int (int*4) but others BIGINT (int*8)
      integer ier,iflag
      integer*8 N,ktest,M,j,k,ktestindex
      real*4, allocatable :: xj(:)
      real*4 err,tol,pi,t,fmax
      parameter (pi=3.141592653589793238462643383279502884197d0)
      complex*8, allocatable :: cj(:),fk(:)
      complex*8 fktest

c     this (when unallocated) passes a NULL ptr (0 value) to FINUFFT...
      integer*8, allocatable :: null
c     must use the single-prec version (f) of options struct here...
      type(nufft_optsf) opts
      
c     how many nonuniform pts
      M = 200000
c     how many modes
      N = 100000

      allocate(fk(N))
      allocate(xj(M))
      allocate(cj(M))
      print *,''
      print *,'creating data then run simple interface, default opts...'
c     create some quasi-random NU pts in [-pi,pi], complex strengths
      do j = 1,M
         xj(j) = pi * cos(pi*j/M)
         cj(j) = cmplx( sin((100e0*j)/M), cos(1.0+(50e0*j)/M))
      enddo

      t = omp_get_wtime()
c     mandatory parameters to FINUFFT: sign of +-i in NUFFT
      iflag = 1
c     tolerance
      tol = 1e-6
c     Do transform: writes to fk (mode coeffs), and ier (status flag).
c     here unallocated "null" tells it to use default options:
      call finufft1d1(M,xj,cj,iflag,tol,N,fk,null,ier)
      t = omp_get_wtime()-t
      if (ier.eq.0) then
         print '("done in ",f6.3," sec, ",e10.2" NU pts/s")',t,M/t
      else
         print *,'failed! ier=',ier
      endif

c     math test: single output mode with given freq (not array index) k
      ktest = N/3
      fktest = cmplx(0,0)
      do j=1,M
         fktest = fktest + cj(j) * cmplx( cos(ktest*xj(j)),
     $        sin(iflag*ktest*xj(j)) )
      enddo
c     compute inf norm of fk coeffs for use in rel err
      fmax = 0
      do k=1,N
         fmax = max(fmax,cabs(fk(k)))
      enddo
      ktestindex = ktest + N/2 + 1
      print '("rel err for mode k=",i10," is ",e10.2)',ktest,
     $     cabs(fk(ktestindex)-fktest)/fmax
      
c     do another transform, but now first setting some options...
      print *,''
      print *, 'setting new options, rerun simple interface...'
      call finufft_default_opts(opts)
c     fields of derived type opts may be queried/set as usual...
      opts%debug = 2
      opts%upsampfac = 1.25e0
      print *,'first list our new set of opts values (cf nufft_opts.h):'
      print *,opts
      t = omp_get_wtime()
      call finufft1d1(M,xj,cj,iflag,tol,N,fk,opts,ier)
      t = omp_get_wtime()-t
      if (ier.eq.0) then
         print '("done in ",f6.3," sec, ",e10.2" NU pts/s")',t,M/t
      else
         print *,'failed! ier=',ier
      endif
      
      stop
      end
