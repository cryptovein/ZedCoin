// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2011-2012 Litecoin Developers
// Copyright (c) 2013 ZedCoin Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

	// no checkpoint now, can be added in later releases
    static MapCheckpoints mapCheckpoints =
            boost::assign::map_list_of
			(     0, uint256("0x7f020bb968e46bc26171772042d20010e05b8b3999dae6d45ee514770622ed7d"))
            (   500, uint256("0x5b0c4ca8517bd6779e304fb5edd09438601cc2a3b408a2d7b34c516f2c6fdfaa"))
            (  1000, uint256("0x460e31d0c32916ce4a11f8968230f0ba8caca70b8363e93f8e2aed47f66c961f"))
            (  2500, uint256("0x5c5f13be7442950e347c6c6d8fe8cb4f8fd68bd950456fc60a9a8880670a89a3"))
			(  5000, uint256("0xf86aabe14f25d2f219c2f51de88b96bf7266c7e77551df288d488a8bfeec224a"))
			( 17955, uint256("0x78078605e5c48509cc3d91f34607c02c49dcdbe02f5085dae2c0c0c9679732a8"))
			;


    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints

        MapCheckpoints::const_iterator i = mapCheckpoints.find(nHeight);
        if (i == mapCheckpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0;
	
        return mapCheckpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL;
	
        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, mapCheckpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
		
        return NULL;
    }
}
