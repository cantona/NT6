// Room: /qingcheng/zushidian.c
// Date: Frb.20 1998 by Java

inherit ROOM;
void create()
{
        set("short", "祖師殿");
        set("long", @LONG
祖師殿又名真武宮。祖師殿背靠軒轅峯，面向白雲溪，十分清
幽。附近軒皇台，相傳為黃帝受道處。
LONG );
        set("exits", ([
                "eastup"    : __DIR__"chaoyangdong",
                "southdown" : __DIR__"gulongqiao",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -8100);
        set("coor/y", -890);
        set("coor/z", 50);
        setup();
        replace_program(ROOM);
}