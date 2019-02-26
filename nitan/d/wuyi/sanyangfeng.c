// Room: /d/wuyi/sanyangfeng.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "三仰峯");
        set("long", @LONG
位於七曲溪北的三仰峯，三片巨石昂首向東，直插雲霄。遠看如三
面厚重的旌旗，迎風招展。峯上古樹環匝、綠葉成蔭，碧霄洞上勒有明
代萬曆林培所書“武夷最高處”五個大字。
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "west"       : __DIR__"path9",
                "south"      : __DIR__"path8",
                "northeast"  : __DIR__"path10",
        ]));
        set("objects", ([
                "/d/taishan/npc/shu-sheng" : 1,
        ]));
        set("coor/x", 1370);
        set("coor/y", -4950);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
