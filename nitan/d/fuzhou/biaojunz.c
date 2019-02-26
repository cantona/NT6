// Room: /d/fuzhou/biaojunz.c
// Date: may.12 1998 Java

inherit ROOM;

void create()
{
        set("short", "內宅");
        set("long", @LONG
福威鏢局內宅裝點的十分華貴。花梨木桌上放着一尊精緻的振鬃長
嘶的玉馬，右首太師椅上好大一張豹皮把整張椅子遮得嚴嚴實實。
LONG );
        set("exits", ([
                "east"  : __DIR__"biaojuzt",
        ]));
        set("objects", ([
                __DIR__"npc/wang" : 1,
        ]));
	set("coor/x", -111);
	set("coor/y", -6161);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}