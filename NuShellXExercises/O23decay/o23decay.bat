nucpe /home/giovanni/Desktop/TALENT2017/nushellx/sps/sd.sp          sd.sp        
nucpe /home/giovanni/Desktop/TALENT2017/nushellx/sps/usdb.int       usdb.int     
         
nudel o_230270.trl
nudel o_230270.lnz
nudel o_230270.tmp
nudel o_230270.lev
         
nuaddint o_230bb.addint o_230.int o_230.ant
nucp  o_230.ppar p.par
nucp  o_230.npar n.par
nudel o_230sl.inf
NuShellX < o_230.modelx > o_230mod.out
NuShellX < o_230.levelx > o_230lev.out
nucp nul > opd.dat
source shellx.bat > o_230.cpu
nuren shellx.bat shellx1.bat
nudel opd.dat
nucp  bb0705.lph o_230270.eng o_230.modelx o_230.levelx bb0705.lpe > nucp.txt
nuren o_230270.lp bb0705.lp
nuren o_230270.ls bb0705.ls
nuren o_230270.nhw bb0705.nhw
nulev o_23b     
levp o_23b     
         
nudel o_220060.trl
nudel o_220060.lnz
nudel o_220060.tmp
nudel o_220060.lev
         
nuaddint o_220bb.addint o_220.int o_220.ant
nucp  o_220.ppar p.par
nucp  o_220.npar n.par
nudel o_220sl.inf
NuShellX < o_220.modelx > o_220mod.out
NuShellX < o_220.levelx > o_220lev.out
nucp nul > opd.dat
source shellx.bat > o_220.cpu
nuren shellx.bat shellx1.bat
nudel opd.dat
nucp  bb0600.lph o_220060.eng o_220.modelx o_220.levelx bb0600.lpe > nucp.txt
nuren o_220060.lp bb0600.lp
nuren o_220060.ls bb0600.ls
nuren o_220060.nhw bb0600.nhw
nulev o_22b     
levp o_22b     

NuShellX < trans1.o_2200005 > trans1o_2200005.tcpu
source shellx.bat > trans.cpu
nucp bb0600_0705.txi o_220060270.din bb0600_0705.trz > nucp.txt
nulsf  sdpn.sp       bb0600.lpe    bb0705.lpe    bb0600_0705.trz bb0600_0705.lsf bb0600_0705.lsa o_220.occ       > nulsf.dao
nuaddlsf  o23decayb
