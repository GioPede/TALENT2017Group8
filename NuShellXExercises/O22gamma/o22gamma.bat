nucpe /home/giovanni/Desktop/TALENT2017/nushellx/sps/sd.sp          sd.sp        
nucpe /home/giovanni/Desktop/TALENT2017/nushellx/sps/usdb.int       usdb.int     
         
nudel o_220060.trl
nudel o_220060.lnz
nudel o_220060.tmp
nudel o_220060.lev
nudel o_220160.trl
nudel o_220160.lnz
nudel o_220160.tmp
nudel o_220160.lev
nudel o_220260.trl
nudel o_220260.lnz
nudel o_220260.tmp
nudel o_220260.lev
nudel o_220360.trl
nudel o_220360.lnz
nudel o_220360.tmp
nudel o_220360.lev
nudel o_220460.trl
nudel o_220460.lnz
nudel o_220460.tmp
nudel o_220460.lev
nudel o_220560.trl
nudel o_220560.lnz
nudel o_220560.tmp
nudel o_220560.lev
nudel o_220660.trl
nudel o_220660.lnz
nudel o_220660.tmp
nudel o_220660.lev
nudel o_220760.trl
nudel o_220760.lnz
nudel o_220760.tmp
nudel o_220760.lev
nudel o_220860.trl
nudel o_220860.lnz
nudel o_220860.tmp
nudel o_220860.lev
nudel o_220960.trl
nudel o_220960.lnz
nudel o_220960.tmp
nudel o_220960.lev
nudel o_220_60.trl
nudel o_220_60.lnz
nudel o_220_60.tmp
nudel o_220_60.lev
         
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
nucp  bb0602.lph o_220160.eng o_220.modelx o_220.levelx bb0602.lpe > nucp.txt
nuren o_220160.lp bb0602.lp
nuren o_220160.ls bb0602.ls
nuren o_220160.nhw bb0602.nhw
nucp  bb0604.lph o_220260.eng o_220.modelx o_220.levelx bb0604.lpe > nucp.txt
nuren o_220260.lp bb0604.lp
nuren o_220260.ls bb0604.ls
nuren o_220260.nhw bb0604.nhw
nucp  bb0606.lph o_220360.eng o_220.modelx o_220.levelx bb0606.lpe > nucp.txt
nuren o_220360.lp bb0606.lp
nuren o_220360.ls bb0606.ls
nuren o_220360.nhw bb0606.nhw
nucp  bb0608.lph o_220460.eng o_220.modelx o_220.levelx bb0608.lpe > nucp.txt
nuren o_220460.lp bb0608.lp
nuren o_220460.ls bb0608.ls
nuren o_220460.nhw bb0608.nhw
nucp  bb060a.lph o_220560.eng o_220.modelx o_220.levelx bb060a.lpe > nucp.txt
nuren o_220560.lp bb060a.lp
nuren o_220560.ls bb060a.ls
nuren o_220560.nhw bb060a.nhw
nucp  bb060c.lph o_220660.eng o_220.modelx o_220.levelx bb060c.lpe > nucp.txt
nuren o_220660.lp bb060c.lp
nuren o_220660.ls bb060c.ls
nuren o_220660.nhw bb060c.nhw
nucp  bb060e.lph o_220760.eng o_220.modelx o_220.levelx bb060e.lpe > nucp.txt
nuren o_220760.lp bb060e.lp
nuren o_220760.ls bb060e.ls
nuren o_220760.nhw bb060e.nhw
nucp  bb060g.lph o_220860.eng o_220.modelx o_220.levelx bb060g.lpe > nucp.txt
nuren o_220860.lp bb060g.lp
nuren o_220860.ls bb060g.ls
nuren o_220860.nhw bb060g.nhw
nucp  bb060i.lph o_220960.eng o_220.modelx o_220.levelx bb060i.lpe > nucp.txt
nuren o_220960.lp bb060i.lp
nuren o_220960.ls bb060i.ls
nuren o_220960.nhw bb060i.nhw
nucp  bb060k.lph o_220_60.eng o_220.modelx o_220.levelx bb060k.lpe > nucp.txt
nuren o_220_60.lp bb060k.lp
nuren o_220_60.ls bb060k.ls
nuren o_220_60.nhw bb060k.nhw
nulev o_22b     
levp o_22b     

NuShellX < transt.o_2200002 > transto_2200002.tcpu
source shellx.bat > trans.cpu
nucp bb0600_0602.txi o_220x060160.din o_220y060160.din bb0600_0602.trz > nucp1.txt
nulsf  sdpn.sp       bb0600.lpe    bb0602.lpe    bb0600_0602.trz bb0600_0602.obd bb0600_0602.lsa o_220.occ       > nulsf.dao

NuShellX < transt.o_2200004 > transto_2200004.tcpu
source shellx.bat > trans.cpu
nucp bb0600_0604.txi o_220x060260.din o_220y060260.din bb0600_0604.trz > nucp1.txt
nulsf  sdpn.sp       bb0600.lpe    bb0604.lpe    bb0600_0604.trz bb0600_0604.obd bb0600_0604.lsa o_220.occ       > nulsf.dao

NuShellX < transt.o_2200022 > transto_2200022.tcpu
source shellx.bat > trans.cpu
nucp bb0602_0602.txi o_220x160160.din o_220y160160.din bb0602_0602.trz > nucp1.txt
nulsf  sdpn.sp       bb0602.lpe    bb0602.lpe    bb0602_0602.trz bb0602_0602.obd bb0602_0602.lsa o_220.occ       > nulsf.dao

NuShellX < transt.o_2200024 > transto_2200024.tcpu
source shellx.bat > trans.cpu
nucp bb0602_0604.txi o_220x160260.din o_220y160260.din bb0602_0604.trz > nucp1.txt
nulsf  sdpn.sp       bb0602.lpe    bb0604.lpe    bb0602_0604.trz bb0602_0604.obd bb0602_0604.lsa o_220.occ       > nulsf.dao

NuShellX < transt.o_2200026 > transto_2200026.tcpu
source shellx.bat > trans.cpu
nucp bb0602_0606.txi o_220x160360.din o_220y160360.din bb0602_0606.trz > nucp1.txt
nulsf  sdpn.sp       bb0602.lpe    bb0606.lpe    bb0602_0606.trz bb0602_0606.obd bb0602_0606.lsa o_220.occ       > nulsf.dao

NuShellX < transt.o_2200044 > transto_2200044.tcpu
source shellx.bat > trans.cpu
nucp bb0604_0604.txi o_220x260260.din o_220y260260.din bb0604_0604.trz > nucp1.txt
nulsf  sdpn.sp       bb0604.lpe    bb0604.lpe    bb0604_0604.trz bb0604_0604.obd bb0604_0604.lsa o_220.occ       > nulsf.dao

NuShellX < transt.o_2200046 > transto_2200046.tcpu
source shellx.bat > trans.cpu
nucp bb0604_0606.txi o_220x260360.din o_220y260360.din bb0604_0606.trz > nucp1.txt
nulsf  sdpn.sp       bb0604.lpe    bb0606.lpe    bb0604_0606.trz bb0604_0606.obd bb0604_0606.lsa o_220.occ       > nulsf.dao

NuShellX < transt.o_2200048 > transto_2200048.tcpu
source shellx.bat > trans.cpu
nucp bb0604_0608.txi o_220x260460.din o_220y260460.din bb0604_0608.trz > nucp1.txt
nulsf  sdpn.sp       bb0604.lpe    bb0608.lpe    bb0604_0608.trz bb0604_0608.obd bb0604_0608.lsa o_220.occ       > nulsf.dao

NuShellX < transt.o_2200066 > transto_2200066.tcpu
source shellx.bat > trans.cpu
nucp bb0606_0606.txi o_220x360360.din o_220y360360.din bb0606_0606.trz > nucp1.txt
nulsf  sdpn.sp       bb0606.lpe    bb0606.lpe    bb0606_0606.trz bb0606_0606.obd bb0606_0606.lsa o_220.occ       > nulsf.dao

NuShellX < transt.o_2200068 > transto_2200068.tcpu
source shellx.bat > trans.cpu
nucp bb0606_0608.txi o_220x360460.din o_220y360460.din bb0606_0608.trz > nucp1.txt
nulsf  sdpn.sp       bb0606.lpe    bb0608.lpe    bb0606_0608.trz bb0606_0608.obd bb0606_0608.lsa o_220.occ       > nulsf.dao

NuShellX < transt.o_220006a > transto_220006a.tcpu
source shellx.bat > trans.cpu
nucp bb0606_060a.txi o_220x360560.din o_220y360560.din bb0606_060a.trz > nucp1.txt
nulsf  sdpn.sp       bb0606.lpe    bb060a.lpe    bb0606_060a.trz bb0606_060a.obd bb0606_060a.lsa o_220.occ       > nulsf.dao

NuShellX < transt.o_2200088 > transto_2200088.tcpu
source shellx.bat > trans.cpu
nucp bb0608_0608.txi o_220x460460.din o_220y460460.din bb0608_0608.trz > nucp1.txt
nulsf  sdpn.sp       bb0608.lpe    bb0608.lpe    bb0608_0608.trz bb0608_0608.obd bb0608_0608.lsa o_220.occ       > nulsf.dao

NuShellX < transt.o_220008a > transto_220008a.tcpu
source shellx.bat > trans.cpu
nucp bb0608_060a.txi o_220x460560.din o_220y460560.din bb0608_060a.trz > nucp1.txt
nulsf  sdpn.sp       bb0608.lpe    bb060a.lpe    bb0608_060a.trz bb0608_060a.obd bb0608_060a.lsa o_220.occ       > nulsf.dao

NuShellX < transt.o_220008c > transto_220008c.tcpu
source shellx.bat > trans.cpu
nucp bb0608_060c.txi o_220x460660.din o_220y460660.din bb0608_060c.trz > nucp1.txt
nulsf  sdpn.sp       bb0608.lpe    bb060c.lpe    bb0608_060c.trz bb0608_060c.obd bb0608_060c.lsa o_220.occ       > nulsf.dao

NuShellX < transt.o_22000aa > transto_22000aa.tcpu
source shellx.bat > trans.cpu
nucp bb060a_060a.txi o_220x560560.din o_220y560560.din bb060a_060a.trz > nucp1.txt
nulsf  sdpn.sp       bb060a.lpe    bb060a.lpe    bb060a_060a.trz bb060a_060a.obd bb060a_060a.lsa o_220.occ       > nulsf.dao

NuShellX < transt.o_22000ac > transto_22000ac.tcpu
source shellx.bat > trans.cpu
nucp bb060a_060c.txi o_220x560660.din o_220y560660.din bb060a_060c.trz > nucp1.txt
nulsf  sdpn.sp       bb060a.lpe    bb060c.lpe    bb060a_060c.trz bb060a_060c.obd bb060a_060c.lsa o_220.occ       > nulsf.dao

NuShellX < transt.o_22000ae > transto_22000ae.tcpu
source shellx.bat > trans.cpu
nucp bb060a_060e.txi o_220x560760.din o_220y560760.din bb060a_060e.trz > nucp1.txt
nulsf  sdpn.sp       bb060a.lpe    bb060e.lpe    bb060a_060e.trz bb060a_060e.obd bb060a_060e.lsa o_220.occ       > nulsf.dao

NuShellX < transt.o_22000cc > transto_22000cc.tcpu
source shellx.bat > trans.cpu
nucp bb060c_060c.txi o_220x660660.din o_220y660660.din bb060c_060c.trz > nucp1.txt
nulsf  sdpn.sp       bb060c.lpe    bb060c.lpe    bb060c_060c.trz bb060c_060c.obd bb060c_060c.lsa o_220.occ       > nulsf.dao

NuShellX < transt.o_22000ce > transto_22000ce.tcpu
source shellx.bat > trans.cpu
nucp bb060c_060e.txi o_220x660760.din o_220y660760.din bb060c_060e.trz > nucp1.txt
nulsf  sdpn.sp       bb060c.lpe    bb060e.lpe    bb060c_060e.trz bb060c_060e.obd bb060c_060e.lsa o_220.occ       > nulsf.dao

NuShellX < transt.o_22000cg > transto_22000cg.tcpu
source shellx.bat > trans.cpu
nucp bb060c_060g.txi o_220x660860.din o_220y660860.din bb060c_060g.trz > nucp1.txt
nulsf  sdpn.sp       bb060c.lpe    bb060g.lpe    bb060c_060g.trz bb060c_060g.obd bb060c_060g.lsa o_220.occ       > nulsf.dao

NuShellX < transt.o_22000ee > transto_22000ee.tcpu
source shellx.bat > trans.cpu
nucp bb060e_060e.txi o_220x760760.din o_220y760760.din bb060e_060e.trz > nucp1.txt
nulsf  sdpn.sp       bb060e.lpe    bb060e.lpe    bb060e_060e.trz bb060e_060e.obd bb060e_060e.lsa o_220.occ       > nulsf.dao

NuShellX < transt.o_22000eg > transto_22000eg.tcpu
source shellx.bat > trans.cpu
nucp bb060e_060g.txi o_220x760860.din o_220y760860.din bb060e_060g.trz > nucp1.txt
nulsf  sdpn.sp       bb060e.lpe    bb060g.lpe    bb060e_060g.trz bb060e_060g.obd bb060e_060g.lsa o_220.occ       > nulsf.dao

NuShellX < transt.o_22000ei > transto_22000ei.tcpu
source shellx.bat > trans.cpu
nucp bb060e_060i.txi o_220x760960.din o_220y760960.din bb060e_060i.trz > nucp1.txt
nulsf  sdpn.sp       bb060e.lpe    bb060i.lpe    bb060e_060i.trz bb060e_060i.obd bb060e_060i.lsa o_220.occ       > nulsf.dao

NuShellX < transt.o_22000gg > transto_22000gg.tcpu
source shellx.bat > trans.cpu
nucp bb060g_060g.txi o_220x860860.din o_220y860860.din bb060g_060g.trz > nucp1.txt
nulsf  sdpn.sp       bb060g.lpe    bb060g.lpe    bb060g_060g.trz bb060g_060g.obd bb060g_060g.lsa o_220.occ       > nulsf.dao

NuShellX < transt.o_22000gi > transto_22000gi.tcpu
source shellx.bat > trans.cpu
nucp bb060g_060i.txi o_220x860960.din o_220y860960.din bb060g_060i.trz > nucp1.txt
nulsf  sdpn.sp       bb060g.lpe    bb060i.lpe    bb060g_060i.trz bb060g_060i.obd bb060g_060i.lsa o_220.occ       > nulsf.dao

NuShellX < transt.o_22000gk > transto_22000gk.tcpu
source shellx.bat > trans.cpu
nucp bb060g_060k.txi o_220x860_60.din o_220y860_60.din bb060g_060k.trz > nucp1.txt
nulsf  sdpn.sp       bb060g.lpe    bb060k.lpe    bb060g_060k.trz bb060g_060k.obd bb060g_060k.lsa o_220.occ       > nulsf.dao

NuShellX < transt.o_22000ii > transto_22000ii.tcpu
source shellx.bat > trans.cpu
nucp bb060i_060i.txi o_220x960960.din o_220y960960.din bb060i_060i.trz > nucp1.txt
nulsf  sdpn.sp       bb060i.lpe    bb060i.lpe    bb060i_060i.trz bb060i_060i.obd bb060i_060i.lsa o_220.occ       > nulsf.dao

NuShellX < transt.o_22000ik > transto_22000ik.tcpu
source shellx.bat > trans.cpu
nucp bb060i_060k.txi o_220x960_60.din o_220y960_60.din bb060i_060k.trz > nucp1.txt
nulsf  sdpn.sp       bb060i.lpe    bb060k.lpe    bb060i_060k.trz bb060i_060k.obd bb060i_060k.lsa o_220.occ       > nulsf.dao

NuShellX < transt.o_22000kk > transto_22000kk.tcpu
source shellx.bat > trans.cpu
nucp bb060k_060k.txi o_220x_60_60.din o_220y_60_60.din bb060k_060k.trz > nucp1.txt
nulsf  sdpn.sp       bb060k.lpe    bb060k.lpe    bb060k_060k.trz bb060k_060k.obd bb060k_060k.lsa o_220.occ       > nulsf.dao

dens < o_220b.den   
gamma o_220b
map o_220b.dei
