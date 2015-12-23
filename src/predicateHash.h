#ifndef __PREDICATE_HASH__
#define __PREDICATE_HASH__ 

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <errno.h>
#include <string.h>
#include "journal.h"
#include "bitSet.h"
#include "constants.h"

typedef struct Column Column_t;

typedef struct predicateSubBucket {
	uint64_t range_start;
	uint64_t range_end;
	Column_t *condition;
	BitSet_t* bit_set;
	uint64_t open_requests;
} predicateSubBucket;

typedef struct predicateBucket {
	uint8_t deletion_started;
	uint32_t local_depth;
	uint32_t current_subBuckets;
	uint64_t pointers_num;
	predicateSubBucket **key_buckets;
} predicateBucket;

typedef struct predicateHash {
	uint64_t size;
	uint32_t global_depth;
	predicateBucket **index;
} predicateHash;


/* HASH INIT METHOD */
predicateHash* predicateCreateHash(void); 
/********************/

/*HASH FUNCTION USED FOR TO GO TO THE RIGHT INDEX*/
uint64_t predicateHashFunction(uint64_t, predicateSubBucket*);
/*************************************************/

/*INSERT TO HASH FUNCTION AND OTHER HELPER FUNCTIONS*/
void predicateFixHashPointers(predicateBucket **, predicateBucket *, uint32_t, uint64_t); 
void predicateFixSplitPointers(predicateHash*, predicateBucket*, predicateBucket*, uint64_t );
void predicateDuplicateIndex(predicateHash*);
void predicateCopyBucketPtrs(predicateBucket*, predicateBucket*);
void predicateCopySubbucketTransactions(predicateSubBucket*, predicateSubBucket*);
int predicateInsertHashRecord(predicateHash*, predicateSubBucket*);
predicateBucket* predicateCreateNewBucket(uint32_t);
predicateSubBucket* predicateCreateNewSubBucket(predicateSubBucket *);
void predicateCleanBucket(predicateBucket *);
Boolean_t predicateRecordsEqual(predicateSubBucket*, predicateSubBucket*);
BitSet_t* predicateGetBitSet(predicateHash *, predicateSubBucket *);
void predicatePrintHash(predicateHash *);
void predicatePrintBucket(predicateBucket *);
predicateSubBucket* createPredicateSubBucket(uint64_t, uint64_t, uint32_t, Op_t, uint64_t);
/*****************************************************/

/*DELETE HASH FUNCTION*/
int predicateDestroyHash(predicateHash *);
// void predicateDestroySubBucket(predicateSubBucket *);
// void predicateDestroyBucket(predicateBucket *);
void predicateFixDeletePointers(predicateHash*, predicateBucket*, predicateBucket* , uint64_t);
/**********************/



#endif