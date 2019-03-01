// Room: /d/wuyi/dawangfeng.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "大王峰");
        set("long", @LONG
大王峰又稱紗帽峰，山形如宦者紗帽，獨具王儀而得名。此山為入
武夷第一峰。四周懸崖壁立，上豐下斂，氣勢雄渾。遠遠望去，宛若擎
天巨柱，與玉女遙遙相望。石壁上刻有“居高思危”四字赫然在目，令
人觸景生情，浮想聯翩，直指人心。
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "northdown" : __DIR__"path3",
                "southdown" : __DIR__"path1",
        ]));
        set("objects", ([
                "/d/taishan/npc/jian-ke" : 1,
        ]));
        set("coor/x", 1390);
        set("coor/y", -4990);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}
