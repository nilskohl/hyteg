#! /usr/bin/env python3
# -*- coding: utf-8 -*-

from mesa_pd import Module
import mesa_pd.collision_detection as collision_detection
import mesa_pd.data as data
import mesa_pd.kernel as kernel
import mesa_pd.mpi as mpi
import mesa_pd.vtk as vtk

import argparse
import numpy as np
import os

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Generate all necessary files for the waLBerla mesa_pd module.')
    parser.add_argument('path', help='Where should the files be created?')
    args = parser.parse_args()

    mpd = Module(args.path, 'mesa_pd_convection')
    ps = mpd.add(data.ParticleStorage())
    ps.add_property("velocity", "walberla::mesa_pd::Vec3", defValue="real_t(0)", syncMode="ALWAYS")

    ps.add_include("blockforest/BlockForest.h")
    ps.add_property("currentBlock", "blockforest::BlockID", defValue="", syncMode="NEVER")

    mpd.add(mpi.Notifications(ps))
    mpd.add(mpi.SyncGhostOwners(ps))
    mpd.add(mpi.SyncNextNeighbors(ps))

    ps.print()

    mpd.generate(False)
