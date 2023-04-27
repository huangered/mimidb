/*
 *��ɨ����������
 */
#ifndef _relscan_h_
#define _relscan_h_

#include "access/genam.h"
#include "access/indextuple.h"


// �ѱ�ɨ������
typedef struct HeapScanDescData {
    /* scan parameter */
    Relation rs_rd; // ��������
    int rs_nkeys;   // scan key ����
    ScanKey rs_key; // scan key ��ָ��

    /* initscan��ʼ���趨ֵ */
    BlockNumber rs_nblocks;    // rel �ܹ� block ����
    BlockNumber rs_startblock; // rel ��ʼ block number
    BlockNumber rs_numblocks;  // rel ���ɨ������

    /* scan ��ǰ״̬ */
    bool rs_inited;            // scan�Ƿ��ʼ��
    HeapTupleData rs_curtuple; // ��ǰtuple
    BlockNumber rs_curblock;   // ��ǰblock
    Buffer rs_curbuf;          // ��ǰbuf
} HeapScanDescData;

typedef struct IndexScanDescData {
    /* scan ���� */
    Relation heap_rel;  /*heap��������*/
    Relation index_rel; /*index��������*/
    int nkeys;
    ScanKey keyData;
    ScanKey orderByData;

    // index-only ɨ��
    IndexTuple xs_itup;
    TupleDesc xs_itupdesc;
    HeapTuple xs_hitup;
    TupleDesc xs_hitupdesc;

    int key;
    int value;
    BlockNumber block;
    OffsetNumber offset;
} IndexScanDescData;

#endif