nucpe /home/giovanni/Desktop/TALENT2017/nushellx/sps/sd.sp          sd.sp        
nucpe /home/giovanni/Desktop/TALENT2017/nushellx/sps/usdb.int       usdb.int     
         
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
         
nudel f_220051.trl
nudel f_220051.lnz
nudel f_220051.tmp
nudel f_220051.lev
nudel f_220151.trl
nudel f_220151.lnz
nudel f_220151.tmp
nudel f_220151.lev
nudel f_220251.trl
nudel f_220251.lnz
nudel f_220251.tmp
nudel f_220251.lev
nudel f_220351.trl
nudel f_220351.lnz
nudel f_220351.tmp
nudel f_220351.lev
nudel f_220451.trl
nudel f_220451.lnz
nudel f_220451.tmp
nudel f_220451.lev
nudel f_220551.trl
nudel f_220551.lnz
nudel f_220551.tmp
nudel f_220551.lev
nudel f_220651.trl
nudel f_220651.lnz
nudel f_220651.tmp
nudel f_220651.lev
nudel f_220751.trl
nudel f_220751.lnz
nudel f_220751.tmp
nudel f_220751.lev
nudel f_220851.trl
nudel f_220851.lnz
nudel f_220851.tmp
nudel f_220851.lev
nudel f_220951.trl
nudel f_220951.lnz
nudel f_220951.tmp
nudel f_220951.lev
nudel f_220_51.trl
nudel f_220_51.lnz
nudel f_220_51.tmp
nudel f_220_51.lev
         
nuaddint f_220bb.addint f_220.int f_220.ant
nucp  f_220.ppar p.par
nucp  f_220.npar n.par

nudel f_220sl.inf
NuShellX < f_220.modelx > f_220mod.out
NuShellX < f_220.levelx > f_220lev.out
source shellx.bat > f_220.cpu
nuren shellx.bat shellx1.bat
nucp  bb1600.lph f_220051.eng f_220.modelx f_220.levelx bb1600.lpe > nucp.txt
nuren f_220051.lp bb1600.lp
nuren f_220051.ls bb1600.ls
nuren f_220051.nhw bb1600.nhw
nucp  bb1602.lph f_220151.eng f_220.modelx f_220.levelx bb1602.lpe > nucp.txt
nuren f_220151.lp bb1602.lp
nuren f_220151.ls bb1602.ls
nuren f_220151.nhw bb1602.nhw
nucp  bb1604.lph f_220251.eng f_220.modelx f_220.levelx bb1604.lpe > nucp.txt
nuren f_220251.lp bb1604.lp
nuren f_220251.ls bb1604.ls
nuren f_220251.nhw bb1604.nhw
nucp  bb1606.lph f_220351.eng f_220.modelx f_220.levelx bb1606.lpe > nucp.txt
nuren f_220351.lp bb1606.lp
nuren f_220351.ls bb1606.ls
nuren f_220351.nhw bb1606.nhw
nucp  bb1608.lph f_220451.eng f_220.modelx f_220.levelx bb1608.lpe > nucp.txt
nuren f_220451.lp bb1608.lp
nuren f_220451.ls bb1608.ls
nuren f_220451.nhw bb1608.nhw
nucp  bb160a.lph f_220551.eng f_220.modelx f_220.levelx bb160a.lpe > nucp.txt
nuren f_220551.lp bb160a.lp
nuren f_220551.ls bb160a.ls
nuren f_220551.nhw bb160a.nhw
nucp  bb160c.lph f_220651.eng f_220.modelx f_220.levelx bb160c.lpe > nucp.txt
nuren f_220651.lp bb160c.lp
nuren f_220651.ls bb160c.ls
nuren f_220651.nhw bb160c.nhw
nucp  bb160e.lph f_220751.eng f_220.modelx f_220.levelx bb160e.lpe > nucp.txt
nuren f_220751.lp bb160e.lp
nuren f_220751.ls bb160e.ls
nuren f_220751.nhw bb160e.nhw
nucp  bb160g.lph f_220851.eng f_220.modelx f_220.levelx bb160g.lpe > nucp.txt
nuren f_220851.lp bb160g.lp
nuren f_220851.ls bb160g.ls
nuren f_220851.nhw bb160g.nhw
nucp  bb160i.lph f_220951.eng f_220.modelx f_220.levelx bb160i.lpe > nucp.txt
nuren f_220951.lp bb160i.lp
nuren f_220951.ls bb160i.ls
nuren f_220951.nhw bb160i.nhw
nucp  bb160k.lph f_220_51.eng f_220.modelx f_220.levelx bb160k.lpe > nucp.txt
nuren f_220_51.lp bb160k.lp
nuren f_220_51.ls bb160k.ls
nuren f_220_51.nhw bb160k.nhw
nulev f_22b     
levp f_22b     

NuShellX < transt.o_2200000 > transto_2200000.tcpu
source shellx.bat > trans.cpu
nucp bb0600_1600.txi f_220051060.din bb0600_1600.trz > nucp2.txt
nulsf  sdpn.sp       bb0600.lpe    bb1600.lpe    bb0600_1600.trz bb0600_1600.obd bb0600_1600.lsa o_220.occ       > nulsf.dao

NuShellX < transt.o_2200002 > transto_2200002.tcpu
source shellx.bat > trans.cpu
nucp bb0600_1602.txi f_220151060.din bb0600_1602.trz > nucp2.txt
nulsf  sdpn.sp       bb0600.lpe    bb1602.lpe    bb0600_1602.trz bb0600_1602.obd bb0600_1602.lsa o_220.occ       > nulsf.dao

dens < o_220b.ben   
nucpe /home/giovanni/Desktop/TALENT2017/nushellx/sps/xfg.dai        xfg.dai      
nucpe /home/giovanni/Desktop/TALENT2017/nushellx/sps/fgtw.dai       fgtw.dai     
beta < o_220b.beq
