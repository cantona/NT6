// Room: /d/taiwan/zhuqian.c
// Last Modifyed by Ahda on Jan. 4 2002

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "竹塹");
        set("long", @LONG
竹塹，在台灣島西北部，是介于北部與中部的過渡地帶，全境多山
嶺與台地，沿海和河流沿岸始有狹小平原。東、南、北為丘陵環拱，西
臨台灣海峽，因多季風，有“風城”之稱。最早來此開墾的漢人是客家
人，由于土地貧瘠且多丘陵山地，居民們大半以種茶、植樹、栽果為生，
此地的繭絲、茗茶、西瓜都是聞名全台的特產。
LONG );
        set("exits", ([
                "northeast" : __DIR__"danshui",
                "southwest" : __DIR__"maolishe",
        ]));
        set("objects", ([
                __DIR__"npc/kejiaren": 1,
        ]));
        set("outdoors", "taiwan");
        set("coor/x", 2530);
        set("coor/y", -6980);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
