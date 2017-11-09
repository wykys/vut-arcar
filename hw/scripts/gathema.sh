#!/bin/sh
# wykys 9.11.2017
# script for data preparation for gathema

BOARD=arcar
echo "Rename file from kicad for Gathema."
cd ../gerber
rm -f *.top *.bot *.smt *.smb *.plt *.plb *in2 *.in3 *.pth *.mill_pth *.mill *.score *.dim *-job.gbrjob
[ -e $BOARD-F.Cu.gbr ] && mv $BOARD-F.Cu.gbr $BOARD.top
[ -e $BOARD-B.Cu.gbr ] && mv $BOARD-B.Cu.gbr $BOARD.bot
[ -e $BOARD-F.Mask.gbr ] && mv $BOARD-F.Mask.gbr $BOARD.smt
[ -e $BOARD-B.Mask.gbr ] && mv  $BOARD-B.Mask.gbr $BOARD.smb
[ -e $BOARD-F.SilkS.gbr ] && mv  $BOARD-F.SilkS.gbr $BOARD.plt
[ -e $BOARD-B.SilkS.gbr ] && mv  $BOARD-B.SilkS.gbr $BOARD.plb
[ -e $BOARD-PTH.drl ] && mv $BOARD-PTH.drl $BOARD.pth
[ -e $BOARD-NPTH.drl ] && mv $BOARD-NPTH.drl $BOARD.mill
[ -e $BOARD-Edge.Cuts.gbr ] && mv $BOARD-Edge.Cuts.gbr $BOARD.dim
