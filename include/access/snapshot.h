/*
事务snapshot相关代码
*/
#ifndef _SNAPSHOT_H_
#define _SHAPSHOT_H_

typedef struct SnapshotData {
	int xmin;
	int xmax;
} SnapshotData;

typedef SnapshotData* Snapshot;


#endif