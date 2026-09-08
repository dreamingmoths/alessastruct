meta:
  id: libgraph
  endian: le
  bit-endian: le

types:
    t_t_count:
        seq:
         - id: count
           type: b16
         - id: p0
           type: b16
    t_t_mode:
        seq:
         - id: clks
           type: b2
         - id: gate
           type: b1
         - id: gats
           type: b1
         - id: gatm
           type: b2
         - id: zret
           type: b1
         - id: cue
           type: b1
         - id: cmpe
           type: b1
         - id: ovfe
           type: b1
         - id: equf
           type: b1
         - id: ovff
           type: b1
         - id: p0
           type: b20
    t_t_comp:
        seq:
         - id: comp
           type: b16
         - id: p0
           type: b16
    t_t_hold:
        seq:
         - id: hold
           type: b16
         - id: p0
           type: b16
    t_ipu_cmd_write:
        seq:
         - id: option
           type: b28
         - id: code
           type: b4
    t_ipu_cmd_read:
        seq:
         - id: data
           type: b32
         - id: p0
           type: b31
         - id: busy
           type: b1
    t_ipu_top:
        seq:
         - id: bstop
           type: b32
         - id: p0
           type: b31
         - id: busy
           type: b1
    t_ipu_ctrl:
        seq:
         - id: ifc
           type: b4
         - id: ofc
           type: b4
         - id: cbp
           type: b6
         - id: ecd
           type: b1
         - id: scd
           type: b1
         - id: idp
           type: b2
         - id: p0
           type: b2
         - id: as
           type: b1
         - id: ivf
           type: b1
         - id: qst
           type: b1
         - id: mp1
           type: b1
         - id: pct
           type: b3
         - id: p1
           type: b3
         - id: rst
           type: b1
         - id: busy
           type: b1
    t_ipu_bp:
        seq:
         - id: bp
           type: b7
         - id: p0
           type: b1
         - id: ifc
           type: b4
         - id: p1
           type: b4
         - id: fp
           type: b2
         - id: p2
           type: b14
    t_gif_ctrl:
        seq:
         - id: rst
           type: b1
         - id: p0
           type: b2
         - id: pse
           type: b1
         - id: p1
           type: b28
    t_gif_mode:
        seq:
         - id: m3r
           type: b1
         - id: p0
           type: b1
         - id: imt
           type: b1
         - id: p1
           type: b29
    t_gif_stat:
        seq:
         - id: m3r
           type: b1
         - id: m3p
           type: b1
         - id: imt
           type: b1
         - id: pse
           type: b1
         - id: p0
           type: b1
         - id: ip3
           type: b1
         - id: p3q
           type: b1
         - id: p2q
           type: b1
         - id: p1q
           type: b1
         - id: oph
           type: b1
         - id: apath
           type: b2
         - id: dir
           type: b1
         - id: p1
           type: b11
         - id: fqc
           type: b5
         - id: p2
           type: b3
    t_gif_tag0:
        seq:
         - id: nloop
           type: b15
         - id: eop
           type: b1
         - id: tag
           type: b16
    t_gif_tag1:
        seq:
         - id: tag
           type: b14
         - id: pre
           type: b1
         - id: prim
           type: b11
         - id: flg
           type: b2
         - id: nreg
           type: b4
    t_gif_tag2:
        seq:
         - id: tag
           type: b32
    t_gif_tag3:
        seq:
         - id: tag
           type: b32
    t_gif_cnt:
        seq:
         - id: loopcnt
           type: b15
         - id: p0
           type: b1
         - id: regcnt
           type: b4
         - id: vuaddr
           type: b10
         - id: p1
           type: b2
    t_gif_p3cnt:
        seq:
         - id: p3cnt
           type: b15
         - id: p0
           type: b17
    t_gif_p3tag:
        seq:
         - id: loopcnt
           type: b15
         - id: eop
           type: b1
         - id: p0
           type: b16
    t_vif0_stat:
        seq:
         - id: vps
           type: b2
         - id: vew
           type: b1
         - id: p0
           type: b3
         - id: mrk
           type: b1
         - id: p1
           type: b1
         - id: vss
           type: b1
         - id: vfs
           type: b1
         - id: vis
           type: b1
         - id: int
           type: b1
         - id: ero
           type: b1
         - id: er1
           type: b1
         - id: p2
           type: b10
         - id: fqc
           type: b4
         - id: p3
           type: b4
    t_vif0_fbrst:
        seq:
         - id: rst
           type: b1
         - id: fbk
           type: b1
         - id: stp
           type: b1
         - id: stc
           type: b1
         - id: p0
           type: b28
    t_vif0_err:
        seq:
         - id: mii
           type: b1
         - id: me0
           type: b1
         - id: me1
           type: b1
         - id: p0
           type: b29
    t_vif_mark:
        seq:
         - id: mark
           type: b16
         - id: p0
           type: b16
    t_vif_cycle:
        seq:
         - id: cl
           type: b8
         - id: wl
           type: b8
         - id: p0
           type: b16
    t_vif_mode:
        seq:
         - id: mod
           type: b2
         - id: p0
           type: b30
    t_vif0_num:
        seq:
         - id: num
           type: b8
         - id: p0
           type: b24
    t_vif_mask:
        seq:
         - id: m0
           type: b2
         - id: m1
           type: b2
         - id: m2
           type: b2
         - id: m3
           type: b2
         - id: m4
           type: b2
         - id: m5
           type: b2
         - id: m6
           type: b2
         - id: m7
           type: b2
         - id: m8
           type: b2
         - id: m9
           type: b2
         - id: m10
           type: b2
         - id: m11
           type: b2
         - id: m12
           type: b2
         - id: m13
           type: b2
         - id: m14
           type: b2
         - id: m15
           type: b2
    t_vif_code:
        seq:
         - id: immediate
           type: b16
         - id: num
           type: b8
         - id: cmd
           type: b8
    t_vif_itops:
        seq:
         - id: itops
           type: b10
         - id: p0
           type: b22
    t_vif_itop:
        seq:
         - id: itop
           type: b10
         - id: p0
           type: b22
    t_vif_r0:
        seq:
         - id: r0
           type: b32
    t_vif_r1:
        seq:
         - id: r1
           type: b32
    t_vif_r2:
        seq:
         - id: r2
           type: b32
    t_vif_r3:
        seq:
         - id: r3
           type: b32
    t_vif_c0:
        seq:
         - id: c0
           type: b32
    t_vif_c1:
        seq:
         - id: c1
           type: b32
    t_vif_c2:
        seq:
         - id: c2
           type: b32
    t_vif_c3:
        seq:
         - id: c3
           type: b32
    t_vif1_stat:
        seq:
         - id: vps
           type: b2
         - id: vew
           type: b1
         - id: vgw
           type: b1
         - id: p0
           type: b2
         - id: mrk
           type: b1
         - id: dbf
           type: b1
         - id: vss
           type: b1
         - id: vfs
           type: b1
         - id: vis
           type: b1
         - id: int
           type: b1
         - id: ero
           type: b1
         - id: er1
           type: b1
         - id: p1
           type: b9
         - id: fdr
           type: b1
         - id: fqc
           type: b5
         - id: p2
           type: b3
    t_vif1_fbrst:
        seq:
         - id: rst
           type: b1
         - id: fbk
           type: b1
         - id: stp
           type: b1
         - id: stc
           type: b1
         - id: p0
           type: b28
    t_vif1_err:
        seq:
         - id: mii
           type: b1
         - id: me0
           type: b1
         - id: me1
           type: b1
         - id: p0
           type: b29
    t_vif1_num:
        seq:
         - id: num
           type: b8
         - id: p0
           type: b24
    t_vif1_base:
        seq:
         - id: base
           type: b10
         - id: p0
           type: b22
    t_vif1_ofst:
        seq:
         - id: offset
           type: b10
         - id: p0
           type: b22
    t_vif1_tops:
        seq:
         - id: tops
           type: b10
         - id: p0
           type: b22
    t_vif1_top:
        seq:
         - id: top
           type: b10
         - id: p0
           type: b22
    t_d_chcr:
        seq:
         - id: dir
           type: b1
         - id: p0
           type: b1
         - id: mod
           type: b2
         - id: asp
           type: b2
         - id: tte
           type: b1
         - id: tie
           type: b1
         - id: str
           type: b1
         - id: p1
           type: b7
         - id: tag
           type: b16
    t_d_madr:
        seq:
         - id: addr
           type: b31
         - id: spr
           type: b1
    t_d_qwc:
        seq:
         - id: qwc
           type: b16
         - id: p0
           type: b16
    t_d_tadr:
        seq:
         - id: addr
           type: b31
         - id: spr
           type: b1
    t_d_asr0:
        seq:
         - id: addr
           type: b31
         - id: spr
           type: b1
    t_d_asr1:
        seq:
         - id: addr
           type: b31
         - id: spr
           type: b1
    t_d_sadr:
        seq:
         - id: addr
           type: b14
         - id: p0
           type: b18
    t_d_ctrl:
        seq:
         - id: dmae
           type: b1
         - id: rele
           type: b1
         - id: mfd
           type: b2
         - id: sts
           type: b2
         - id: std
           type: b2
         - id: rcyc
           type: b3
         - id: p0
           type: b21
    t_d_stat:
        seq:
         - id: cis0
           type: b1
         - id: cis1
           type: b1
         - id: cis2
           type: b1
         - id: cis3
           type: b1
         - id: cis4
           type: b1
         - id: cis5
           type: b1
         - id: cis6
           type: b1
         - id: cis7
           type: b1
         - id: cis8
           type: b1
         - id: cis9
           type: b1
         - id: p0
           type: b3
         - id: sis
           type: b1
         - id: meis
           type: b1
         - id: beis
           type: b1
         - id: cim0
           type: b1
         - id: cim1
           type: b1
         - id: cim2
           type: b1
         - id: cim3
           type: b1
         - id: cim4
           type: b1
         - id: cim5
           type: b1
         - id: cim6
           type: b1
         - id: cim7
           type: b1
         - id: cim8
           type: b1
         - id: cim9
           type: b1
         - id: p1
           type: b3
         - id: sim
           type: b1
         - id: meim
           type: b1
         - id: p2
           type: b1
    t_d_pcr:
        seq:
         - id: cpc0
           type: b1
         - id: cpc1
           type: b1
         - id: cpc2
           type: b1
         - id: cpc3
           type: b1
         - id: cpc4
           type: b1
         - id: cpc5
           type: b1
         - id: cpc6
           type: b1
         - id: cpc7
           type: b1
         - id: cpc8
           type: b1
         - id: cpc9
           type: b1
         - id: p0
           type: b6
         - id: cde0
           type: b1
         - id: cde1
           type: b1
         - id: cde2
           type: b1
         - id: cde3
           type: b1
         - id: cde4
           type: b1
         - id: cde5
           type: b1
         - id: cde6
           type: b1
         - id: cde7
           type: b1
         - id: cde8
           type: b1
         - id: cde9
           type: b1
         - id: p1
           type: b5
         - id: pce
           type: b1
    t_d_sqwc:
        seq:
         - id: sqwc
           type: b8
         - id: p0
           type: b8
         - id: tqwc
           type: b8
         - id: p1
           type: b8
    t_d_rbsr:
        seq:
         - id: rmsk
           type: b31
         - id: p0
           type: b1
    t_d_rbor:
        seq:
         - id: addr
           type: b31
         - id: p0
           type: b1
    t_d_stadr:
        seq:
         - id: addr
           type: b31
         - id: p0
           type: b1
    t_d_enabler:
        seq:
         - id: p0
           type: b16
         - id: cpnd
           type: b1
         - id: p1
           type: b15
    t_d_enablew:
        seq:
         - id: p0
           type: b16
         - id: cpnd
           type: b1
         - id: p1
           type: b15
    t_gs_pmode:
        seq:
         - id: en1
           type: b1
         - id: en2
           type: b1
         - id: crtmd
           type: b3
         - id: mmod
           type: b1
         - id: amod
           type: b1
         - id: slbg
           type: b1
         - id: alp
           type: b8
         - id: p0
           type: b16
         - id: p1
           type: u4
    t_gs_smode2:
        seq:
         - id: int
           type: b1
         - id: ffmd
           type: b1
         - id: dpms
           type: b2
         - id: p0
           type: b28
         - id: p1
           type: u4
    t_gs_dispfb1:
        seq:
         - id: fbp
           type: b9
         - id: fbw
           type: b6
         - id: psm
           type: b5
         - id: p0
           type: b12
         - id: dbx
           type: b11
         - id: dby
           type: b11
         - id: p1
           type: b10
    t_gs_display1:
        seq:
         - id: dx
           type: b12
         - id: dy
           type: b11
         - id: magh
           type: b4
         - id: magv
           type: b2
         - id: p0
           type: b3
         - id: dw
           type: b12
         - id: dh
           type: b11
         - id: p1
           type: b9
    t_gs_dispfb2:
        seq:
         - id: fbp
           type: b9
         - id: fbw
           type: b6
         - id: psm
           type: b5
         - id: p0
           type: b12
         - id: dbx
           type: b11
         - id: dby
           type: b11
         - id: p1
           type: b10
    t_gs_display2:
        seq:
         - id: dx
           type: b12
         - id: dy
           type: b11
         - id: magh
           type: b4
         - id: magv
           type: b2
         - id: p0
           type: b3
         - id: dw
           type: b12
         - id: dh
           type: b11
         - id: p1
           type: b9
    t_gs_extbuf:
        seq:
         - id: exbp
           type: b14
         - id: exbw
           type: b6
         - id: fbin
           type: b2
         - id: wffmd
           type: b1
         - id: emoda
           type: b2
         - id: emodc
           type: b2
         - id: p0
           type: b5
         - id: wdx
           type: b11
         - id: wdy
           type: b11
         - id: p1
           type: b10
    t_gs_extdata:
        seq:
         - id: sx
           type: b12
         - id: sy
           type: b11
         - id: smph
           type: b4
         - id: smpv
           type: b2
         - id: p0
           type: b3
         - id: ww
           type: b12
         - id: wh
           type: b11
         - id: p1
           type: b9
    t_gs_extwrite:
        seq:
         - id: write
           type: b1
         - id: p0
           type: b31
         - id: p1
           type: u4
    t_gs_bgcolor:
        seq:
         - id: r
           type: b8
         - id: g
           type: b8
         - id: b
           type: b8
         - id: p0
           type: b8
         - id: p1
           type: u4
    t_gs_csr:
        seq:
         - id: signal
           type: b1
         - id: finish
           type: b1
         - id: hsint
           type: b1
         - id: vsint
           type: b1
         - id: edwint
           type: b1
         - id: p0
           type: b3
         - id: flush
           type: b1
         - id: reset
           type: b1
         - id: p1
           type: b2
         - id: nfield
           type: b1
         - id: field
           type: b1
         - id: fifo
           type: b2
         - id: rev
           type: b8
         - id: id
           type: b8
         - id: p2
           type: u4
    t_gs_imr:
        seq:
         - id: p0
           type: b8
         - id: sigmsk
           type: b1
         - id: finishmsk
           type: b1
         - id: hsmsk
           type: b1
         - id: vsmsk
           type: b1
         - id: edwmsk
           type: b1
         - id: p1
           type: b19
         - id: p2
           type: u4
    t_gs_busdir:
        seq:
         - id: dir
           type: b1
         - id: p0
           type: b31
         - id: p1
           type: u4
    t_gs_siglblid:
        seq:
         - id: sigid
           type: b32
         - id: lblid
           type: b32
    sce_gif_tag:
        seq:
         - id: nloop
           type: b15
         - id: eop
           type: b1
         - id: pad16
           type: b16
         - id: id
           type: b14
         - id: pre
           type: b1
         - id: prim
           type: b11
         - id: flg
           type: b2
         - id: nreg
           type: b4
         - id: regs0
           type: b4
         - id: regs1
           type: b4
         - id: regs2
           type: b4
         - id: regs3
           type: b4
         - id: regs4
           type: b4
         - id: regs5
           type: b4
         - id: regs6
           type: b4
         - id: regs7
           type: b4
         - id: regs8
           type: b4
         - id: regs9
           type: b4
         - id: regs10
           type: b4
         - id: regs11
           type: b4
         - id: regs12
           type: b4
         - id: regs13
           type: b4
         - id: regs14
           type: b4
         - id: regs15
           type: b4
    sce_gif_pack_rgbaq:
        seq:
         - id: r
           type: u8
         - id: g
           type: u8
         - id: b
           type: u8
         - id: a
           type: u8
    sce_gif_pack_ad:
        seq:
         - id: data
           type: u4
         - id: addr
           type: u4
    sce_gif_pack_st:
        seq:
         - id: s
           type: f4
         - id: t
           type: f4
         - id: q
           type: f4
         - id: pad96
           type: u8
    sce_gif_pack_uv:
        seq:
         - id: u
           type: s4
         - id: v
           type: s4
         - id: pad64
           type: s8
    sce_gif_pack_xyzf:
        seq:
         - id: x
           type: s4
         - id: y
           type: s4
         - id: z
           type: u8
         - id: f
           type: b12
         - id: pad108
           type: b3
         - id: adc
           type: b1
         - id: pad112
           type: b16
    sce_gif_pack_xyz:
        seq:
         - id: x
           type: s4
         - id: y
           type: s4
         - id: z
           type: u8
         - id: pad96
           type: b15
         - id: adc
           type: b1
         - id: pad112
           type: b16
    sce_gif_pack_fog:
        seq:
         - id: pad
           type: u8
           repeat: expr
           repeat-expr: 3
         - id: f
           type: u8
    sce_gif_pack_nop:
        seq:
         - id: pad
           type: u4
           repeat: expr
           repeat-expr: 2
    sce_gs_alpha:
        seq:
         - id: a
           type: b2
         - id: b
           type: b2
         - id: c
           type: b2
         - id: d
           type: b2
         - id: pad8
           type: b24
         - id: fix
           type: b8
         - id: pad40
           type: b24
    sce_gs_bitbltbuf:
        seq:
         - id: sbp
           type: b14
         - id: pad14
           type: b2
         - id: sbw
           type: b6
         - id: pad22
           type: b2
         - id: spsm
           type: b6
         - id: pad30
           type: b2
         - id: dbp
           type: b14
         - id: pad46
           type: b2
         - id: dbw
           type: b6
         - id: pad54
           type: b2
         - id: dpsm
           type: b6
         - id: pad62
           type: b2
    sce_gs_clamp:
        seq:
         - id: wms
           type: b2
         - id: wmt
           type: b2
         - id: minu
           type: b10
         - id: maxu
           type: b10
         - id: minv
           type: b10
         - id: maxv
           type: b10
         - id: pad44
           type: b20
    sce_gs_colclamp:
        seq:
         - id: clamp
           type: b1
         - id: pad01
           type: b63
    sce_gs_dimx:
        seq:
         - id: dimx00
           type: b3
         - id: pad00
           type: b1
         - id: dimx01
           type: b3
         - id: pad01
           type: b1
         - id: dimx02
           type: b3
         - id: pad02
           type: b1
         - id: dimx03
           type: b3
         - id: pad03
           type: b1
         - id: dimx10
           type: b3
         - id: pad10
           type: b1
         - id: dimx11
           type: b3
         - id: pad11
           type: b1
         - id: dimx12
           type: b3
         - id: pad12
           type: b1
         - id: dimx13
           type: b3
         - id: pad13
           type: b1
         - id: dimx20
           type: b3
         - id: pad20
           type: b1
         - id: dimx21
           type: b3
         - id: pad21
           type: b1
         - id: dimx22
           type: b3
         - id: pad22
           type: b1
         - id: dimx23
           type: b3
         - id: pad23
           type: b1
         - id: dimx30
           type: b3
         - id: pad30
           type: b1
         - id: dimx31
           type: b3
         - id: pad31
           type: b1
         - id: dimx32
           type: b3
         - id: pad32
           type: b1
         - id: dimx33
           type: b3
         - id: pad33
           type: b1
    sce_gs_dthe:
        seq:
         - id: dthe
           type: b1
         - id: pad01
           type: b63
    sce_gs_fba:
        seq:
         - id: fba
           type: b1
         - id: pad01
           type: b63
    sce_gs_finish:
        seq:
         - id: pad00
           type: u8
    sce_gs_fog:
        seq:
         - id: pad00
           type: b56
         - id: f
           type: b8
    sce_gs_fogcol:
        seq:
         - id: fcr
           type: b8
         - id: fcg
           type: b8
         - id: fcb
           type: b8
         - id: pad24
           type: b40
    sce_gs_frame:
        seq:
         - id: fbp
           type: b9
         - id: pad09
           type: b7
         - id: fbw
           type: b6
         - id: pad22
           type: b2
         - id: psm
           type: b6
         - id: pad30
           type: b2
         - id: fbmsk
           type: b32
    sce_gs_hwreg:
        seq:
         - id: wdata
           type: u8
    sce_gs_label:
        seq:
         - id: id
           type: u8
         - id: idmsk
           type: u8
    sce_gs_miptbp1:
        seq:
         - id: tbp1
           type: b14
         - id: tbw1
           type: b6
         - id: tbp2
           type: b14
         - id: tbw2
           type: b6
         - id: tbp3
           type: b14
         - id: tbw3
           type: b6
         - id: pad60
           type: b4
    sce_gs_miptbp2:
        seq:
         - id: tbp4
           type: b14
         - id: tbw4
           type: b6
         - id: tbp5
           type: b14
         - id: tbw5
           type: b6
         - id: tbp6
           type: b14
         - id: tbw6
           type: b6
         - id: pad60
           type: b4
    sce_gs_pabe:
        seq:
         - id: pabe
           type: b1
         - id: pad01
           type: b63
    sce_gs_prim:
        seq:
         - id: prim
           type: b3
         - id: iip
           type: b1
         - id: tme
           type: b1
         - id: fge
           type: b1
         - id: abe
           type: b1
         - id: aa1
           type: b1
         - id: fst
           type: b1
         - id: ctxt
           type: b1
         - id: fix
           type: b1
         - id: pad11
           type: b53
    sce_gs_prmode:
        seq:
         - id: pad00
           type: b3
         - id: iip
           type: b1
         - id: tme
           type: b1
         - id: fge
           type: b1
         - id: abe
           type: b1
         - id: aa1
           type: b1
         - id: fst
           type: b1
         - id: ctxt
           type: b1
         - id: fix
           type: b1
         - id: pad11
           type: b53
    sce_gs_prmodecont:
        seq:
         - id: ac
           type: b1
         - id: pad01
           type: b63
    sce_gs_rgbaq:
        seq:
         - id: r
           type: b8
         - id: g
           type: b8
         - id: b
           type: b8
         - id: a
           type: b8
         - id: q
           type: f4
    sce_gs_scanmsk:
        seq:
         - id: msk
           type: b2
         - id: pad02
           type: b62
    sce_gs_scissor:
        seq:
         - id: scax0
           type: b11
         - id: pad11
           type: b5
         - id: scax1
           type: b11
         - id: pad27
           type: b5
         - id: scay0
           type: b11
         - id: pad43
           type: b5
         - id: scay1
           type: b11
         - id: pad59
           type: b5
    sce_gs_signal:
        seq:
         - id: id
           type: u8
         - id: idmsk
           type: u8
    sce_gs_st:
        seq:
         - id: s
           type: f4
         - id: t
           type: f4
    sce_gs_test:
        seq:
         - id: ate
           type: b1
         - id: atst
           type: b3
         - id: aref
           type: b8
         - id: afail
           type: b2
         - id: date
           type: b1
         - id: datm
           type: b1
         - id: zte
           type: b1
         - id: ztst
           type: b2
         - id: pad19
           type: b45
    sce_gs_tex0:
        seq:
         - id: tbp0
           type: b14
         - id: tbw
           type: b6
         - id: psm
           type: b6
         - id: tw
           type: b4
         - id: th
           type: b4
         - id: tcc
           type: b1
         - id: tfx
           type: b2
         - id: cbp
           type: b14
         - id: cpsm
           type: b4
         - id: csm
           type: b1
         - id: csa
           type: b5
         - id: cld
           type: b3
    sce_gs_tex1:
        seq:
         - id: lcm
           type: b1
         - id: pad01
           type: b1
         - id: mxl
           type: b3
         - id: mmag
           type: b1
         - id: mmin
           type: b3
         - id: mtba
           type: b1
         - id: pad10
           type: b9
         - id: l
           type: b2
         - id: pad21
           type: b11
         - id: k
           type: b12
         - id: pad44
           type: b20
    sce_gs_tex2:
        seq:
         - id: pad00
           type: b20
         - id: psm
           type: b6
         - id: pad26
           type: b11
         - id: cbp
           type: b14
         - id: cpsm
           type: b4
         - id: csm
           type: b1
         - id: csa
           type: b5
         - id: cld
           type: b3
    sce_gs_texa:
        seq:
         - id: ta0
           type: b8
         - id: pad08
           type: b7
         - id: aem
           type: b1
         - id: pad16
           type: b16
         - id: ta1
           type: b8
         - id: pad40
           type: b24
    sce_gs_texclut:
        seq:
         - id: cbw
           type: b6
         - id: cou
           type: b6
         - id: cov
           type: b10
         - id: pad22
           type: b42
    sce_gs_texflush:
        seq:
         - id: pad00
           type: u8
    sce_gs_trxdir:
        seq:
         - id: xdr
           type: b2
         - id: pad02
           type: b62
    sce_gs_trxpos:
        seq:
         - id: ssax
           type: b11
         - id: pad11
           type: b5
         - id: ssay
           type: b11
         - id: pad27
           type: b5
         - id: dsax
           type: b11
         - id: pad43
           type: b5
         - id: dsay
           type: b11
         - id: dir
           type: b2
         - id: pad61
           type: b3
    sce_gs_trxreg:
        seq:
         - id: rrw
           type: b12
         - id: pad12
           type: b20
         - id: rrh
           type: b12
         - id: pad44
           type: b20
    sce_gs_uv:
        seq:
         - id: u
           type: b14
         - id: pad14
           type: b2
         - id: v
           type: b14
         - id: pad30
           type: b34
    sce_gs_xyoffset:
        seq:
         - id: ofx
           type: b16
         - id: pad16
           type: b16
         - id: ofy
           type: b16
         - id: pad48
           type: b16
    sce_gs_xyz:
        seq:
         - id: x
           type: b16
         - id: y
           type: b16
         - id: z
           type: b32
    sce_gs_xyzf:
        seq:
         - id: x
           type: b16
         - id: y
           type: b16
         - id: z
           type: b24
         - id: f
           type: b8
    sce_gs_zbuf:
        seq:
         - id: zbp
           type: b9
         - id: pad09
           type: b15
         - id: psm
           type: b4
         - id: pad28
           type: b4
         - id: zmsk
           type: b1
         - id: pad33
           type: b31
    sce_gs_disp_env:
        seq:
         - id: pmode
           type: u8
         - id: smode2
           type: u8
         - id: dispfb
           type: u8
         - id: display
           type: u8
         - id: bgcolor
           type: u8
    sce_gs_draw_env1:
        seq:
         - id: frame1
           type: u8
         - id: frame1addr
           type: u4
         - id: zbuf1
           type: u8
         - id: zbuf1addr
           type: s8
         - id: xyoffset1
           type: u8
         - id: xyoffset1addr
           type: s8
         - id: scissor1
           type: u8
         - id: scissor1addr
           type: s8
         - id: prmodecont
           type: u8
         - id: prmodecontaddr
           type: s8
         - id: colclamp
           type: u8
         - id: colclampaddr
           type: s8
         - id: dthe
           type: u8
         - id: dtheaddr
           type: s8
         - id: test1
           type: u8
         - id: test1addr
           type: s8
    sce_gs_draw_env2:
        seq:
         - id: frame2
           type: u8
         - id: frame2addr
           type: u4
         - id: zbuf2
           type: u8
         - id: zbuf2addr
           type: s8
         - id: xyoffset2
           type: u8
         - id: xyoffset2addr
           type: s8
         - id: scissor2
           type: u8
         - id: scissor2addr
           type: s8
         - id: prmodecont
           type: u8
         - id: prmodecontaddr
           type: s8
         - id: colclamp
           type: u8
         - id: colclampaddr
           type: s8
         - id: dthe
           type: u8
         - id: dtheaddr
           type: s8
         - id: test2
           type: u8
         - id: test2addr
           type: s8
    sce_gs_clear:
        seq:
         - id: testa
           type: u8
         - id: testaaddr
           type: s8
         - id: prim
           type: u8
         - id: primaddr
           type: s8
         - id: rgbaq
           type: u8
         - id: rgbaqaddr
           type: s8
         - id: xyz2a
           type: u8
         - id: xyz2aaddr
           type: s8
         - id: xyz2b
           type: u8
         - id: xyz2baddr
           type: s8
         - id: testb
           type: u8
         - id: testbaddr
           type: s8
    sce_gs_d_buff:
        seq:
         - id: disp
           type: u8
           repeat: expr
           repeat-expr: 2
         - id: giftag0
           type: u8
         - id: draw0
           type: u8
         - id: clear0
           type: u8
         - id: giftag1
           type: u8
         - id: draw1
           type: u8
         - id: clear1
           type: u8
    sce_gs_d_buff_dc:
        seq:
         - id: disp
           type: u8
           repeat: expr
           repeat-expr: 2
         - id: giftag0
           type: u8
         - id: draw01
           type: u8
         - id: draw02
           type: u8
         - id: clear0
           type: u8
         - id: giftag1
           type: u8
         - id: draw11
           type: u8
         - id: draw12
           type: u8
         - id: clear1
           type: u8
    sce_gs_tex_env:
        seq:
         - id: texflush
           type: u8
         - id: texflushaddr
           type: s8
         - id: tex11
           type: u8
         - id: tex11addr
           type: s8
         - id: tex01
           type: u8
         - id: tex01addr
           type: s8
         - id: clamp1
           type: u8
         - id: clamp1addr
           type: s8
    sce_gs_tex_env2:
        seq:
         - id: texflush
           type: u8
         - id: texflushaddr
           type: s8
         - id: tex12
           type: u8
         - id: tex12addr
           type: s8
         - id: tex02
           type: u8
         - id: tex02addr
           type: s8
         - id: clamp2
           type: u8
         - id: clamp2addr
           type: s8
    sce_gs_alpha_env:
        seq:
         - id: alpha1
           type: u8
         - id: alpha1addr
           type: s8
         - id: pabe
           type: u8
         - id: pabeaddr
           type: s8
         - id: texa
           type: u8
         - id: texaaddr
           type: s8
         - id: fba1
           type: u8
         - id: fba1addr
           type: s8
    sce_gs_alpha_env2:
        seq:
         - id: alpha2
           type: u8
         - id: alpha2addr
           type: s8
         - id: pabe
           type: u8
         - id: pabeaddr
           type: s8
         - id: texa
           type: u8
         - id: texaaddr
           type: s8
         - id: fba2
           type: u8
         - id: fba2addr
           type: s8
    sce_gs_load_image:
        seq:
         - id: giftag0
           type: u8
         - id: bitbltbuf
           type: u8
         - id: bitbltbufaddr
           type: s8
         - id: trxpos
           type: u8
         - id: trxposaddr
           type: s8
         - id: trxreg
           type: u8
         - id: trxregaddr
           type: s8
         - id: trxdir
           type: u8
         - id: trxdiraddr
           type: s8
         - id: giftag1
           type: u8
    sce_gs_store_image:
        seq:
         - id: vifcode
           type: u8
           repeat: expr
           repeat-expr: 4
         - id: giftag
           type: u8
         - id: bitbltbuf
           type: u8
         - id: bitbltbufaddr
           type: s8
         - id: trxpos
           type: u8
         - id: trxposaddr
           type: s8
         - id: trxreg
           type: u8
         - id: trxregaddr
           type: s8
         - id: finish
           type: u8
         - id: finishaddr
           type: s8
         - id: trxdir
           type: u8
         - id: trxdiraddr
           type: s8
    sce_gs_g_param:
        seq:
         - id: sce_gs_inter_mode
           type: s2
         - id: sce_gs_out_mode
           type: s2
         - id: sce_gs_f_f_mode
           type: s2
         - id: sce_gs_version
           type: s2
         - id: sce_gs_v_s_cfunc
           type: s4
         - id: sce_gs_v_s_cid
           type: s4
