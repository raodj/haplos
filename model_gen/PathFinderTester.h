#ifndef PATH_FINDER_TESTER_H
#define PATH_FINDER_TESTER_H

//---------------------------------------------------------------------------
//
// Copyright (c) PC2Lab Development Team
// All rights reserved.
//
// This file is part of free(dom) software -- you can redistribute it
// and/or modify it under the terms of the GNU General Public
// License (GPL)as published by the Free Software Foundation, either
// version 3 (GPL v3), or (at your option) a later version.
//
// The software is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the IMPLIED WARRANTY of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
// Miami University and PC2Lab makes no representations or warranties
// about the suitability of the software, either express or implied,
// including but not limited to the implied warranties of
// merchantability, fitness for a particular purpose, or
// non-infringement.  Miami University and PC2Lab is not be liable for
// any damages suffered by licensee as a result of using, result of
// using, modifying or distributing this software or its derivatives.
//
// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the
// U.S., and the terms of this license.
//
// Authors: Dhananjai M. Rao       raodm@miamiOH.edu
//
//---------------------------------------------------------------------------

#include "ArgParser.h"

class PathFinderTester {
public:
    /** The top-level method that coordinates the various tasks.
        
        This method essentially calls various internal helper methods
        in the following order:

        <ol>

        <li>First it calls loadModel method which loads the generated
        model with nodes, ways, and bulidings data into memory.</li>
        
        </ol>
    */
    int run(int argc, char *argv[]);

protected:
    /** This is a simple inner class that is used to conveniently
        encapsulate various command-line arguments that is used by the
        model generator.  This encapsulation streamlines managing
        several different command-line arguments in a streamlined
        manner
    */
    class CmdLineArgs {
    public:
        /** The path to the text file from where model data is to be
            loaded. This text file must have been generated by
            ModelGenerator in order to correctly operate with this
            class.  Use the \c --model command-line argument to set
            its value.
        */
        std::string modelFilePath;

        /** The starting ID of the building from where the path is to
            be computed.
        */
        long startBldID = -1;

        /** The ending ID of the building to which the path is to be
            computed.
        */
        long endBldID = -1;

        /** Optional output xfig file to which the route is to be
            drawn.
        */
        std::string xfigFilePath;

        /** The scale for the output XFIG figure so that various
            shapes and information are readable.
        */
        int figScale = 16384000;

        /** The minimum distance around the source and destination
            paths only within which the nodes are to be checked.
            Nodes outside this range are not checked as an
            optimization to improve performance.
        */
        double minDist = 0.25;

        /** Additional distance to search in depending on the distance
            between the source and destination.
        */
        double distScale = 0.1;

        /** Flag to indicate path should be optimized for time instead
            of distance
        */
        bool useTime = false;

        /** Command-line arguments to indicate if a given number of
            randomly chosen pairs of buildings are to be used to
            test path finding algorithm.
        */
        int rndTestCount = -1;

        /** An initial base/offset for random number seed.  This is
            used to skip over tests */
        int rndSeed = 0;

        /** Flag to indicate that entry ways for all buildings is to
            be checked.  This check ensures that entry coordinate
            yield a valid near-by index on the way they are mapped
            to.
        */
        bool checkEntries = false;

        /** Print ways that are disconnected from all other ways. The
            OSM data contains ways that are not connected to any other
            ways.  This causes buildings/ways to be disconnected from
            the rest.  If this flag is set, then disconnected ways are
            detected and printed.
        */
        bool printNoWays = false;

        /** Use standard I/O streams to read pairs of building IDs and
            print the route between the pairs of building IDs.
        */
        bool useStdIO = false;
    } cmdLineArgs;

    /** A simple class that encapsulates the OSM data */
    OSMData osmData;
    
private: 
    /** Internal helper method to parse command-line arguments and
        poulate the internal cmdLineArgs object with pertinent
        information.

        This method internally uses the ArgParser to parse out the
        command-line argument specified by the user.

        \param[in] args The number of command-line arguments -- i.e.,
        the size of the argv array.

        \param[in] argv The actual command-line arguments.

        \return This method returns zero if the command-line arguments
        were successfully processed.  On errors it returns a non-zero
        error code.
    */
    int processArgs(int argc, char *argv[]);   

    /** Run a given number of random tests.

        \param[in] testCount The number of tests to be run.
    */
    void runRndTests(int testCount) const;

    /** Convenience method to generate and print the path between two
        given buildings.
    */
    void runRndTest(const long startBldID, const long endBldID) const;

    /** Convenience method to return building IDs as a vector from the
        hash map of buildings

        \return A vector with the building IDs obtained from
        osmData.buildingMap.
    */
    std::vector<long> getBuildingIDs() const;

    /** Check entrys for each building correctly maps to a node on the
        corresponding way.
    */
    void checkEntries() const;

    /** Print ways that are disconnected from all other ways. The OSM
        data contains ways that are not connected to any other ways.
        This causes buildings/ways to be disconnected from the rest.
        This method detects and prints such ways in the following
        manner -- For each way in the model, check to see if // there
        is it has least one node that was 2 way-IDs associated with
        it. If not, it is a disconnected way.

        \note This method cannot detect several interconnected paths
        but as a whole they are actually disconnected.
    */
    void printDisconnectedWays();

    /** Method to read pairs of building IDs from standard input.

        This method is called from the run() method in this class if
        the user specified the --stdio flag.  This method reads pairs
        of building IDs from stdin, computes path, and print it to
        stdout.
    */
    void processStdIO();
};

#endif