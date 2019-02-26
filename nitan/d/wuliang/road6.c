// Room: /wuliang/road6.c
// Date: Oct.18 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "後山小路");
        set("long", @LONG
走出十餘里，已經到無量山峯的後山，只聽得水聲淙淙，前面有
條山溪。尋聲來到溪旁，溪水清澈異常，遠近地下撒滿枯枝，腳步走
動，格格做響。
LONG );
        set("outdoors", "wuliang");
        set("exits", ([
                "south"   : __DIR__"road5",
                "northup" : "/d/xiaoyao/pubu",
        ]));
        set("objects", ([
                __DIR__"npc/gan" : 1,
                __DIR__"npc/ge"  : 1,
        ]));
        set("coor/x", -71020);
        set("coor/y", -79880);
        set("coor/z", 100);
        setup();
        replace_program(ROOM);
}