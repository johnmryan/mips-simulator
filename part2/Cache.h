/*
 * DirectMappedCache.h
 *
 *  Created on: Oct 20, 2015
 *      Author: jbb
 */

#ifndef NDSIM_COMPLETE_CACHE_H_
#define NDSIM_COMPLETE_CACHE_H_

class Cache {
	unsigned logBlockSize;  // log2 number of bytes in a block (not words)
	unsigned logDepth;      // log2 number of blocks in a single set
	unsigned accesses;      // running count of number of cache access
	unsigned hits;          // running count of number of cache hits
	unsigned *tagArray;     // tag array
	bool     *validArray;   // valid array
	public:
	Cache(unsigned logBlockSize_, unsigned logDepth_);
	bool checkHit(unsigned addr); // check if address is hit or miss (true if hit)
	void printStats();
	unsigned getAccesses()  { return accesses; }
	unsigned getHits()      { return hits; }
	virtual ~Cache();
};

#endif /* NDSIM_COMPLETE_CACHE_H_ */
