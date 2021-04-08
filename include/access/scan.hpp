#ifndef _scan_hpp_
#define _scan_hpp_

#include "access/relation.hpp"
#include "access/scankey.hpp"
#include "storage/block.hpp"
#include "storage/buf.hpp"

// 堆表扫描描述
struct HeapScanDescData {
	Relation rs_rd;  // 表描述符
	int rs_nkeys;    // scan key个数
	ScanKey rs_key;  // scan key的指针

	/* initscan初始化设定值 */
	BlockNumber rs_nblocks;	   // rel总共block数量
	BlockNumber rs_startblock; // rel开始block number
	BlockNumber rs_numblocks;  // rel最大扫描数量

	/* scan 当前状态 */
	bool rs_inited;            // scan是否初始化
	HeapTupleData rs_curtuple; // 当前tuple
	BlockNumber rs_curblock;   // 当前block
	Buffer		rs_curbuf;	   // 当前buf
};



// 索引表扫描描述

// 系统表扫描描述

#endif