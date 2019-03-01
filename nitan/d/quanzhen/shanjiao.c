// shanjiao.c 終南山腳
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "終南山腳");
        set("long", @LONG
這裡是終南山的山腳，終南山號稱西北的第一山，以山勢奇峻，
環境清幽著稱。這裡的山勢還很平緩，一道石階蜿蜒通往山上。面前
是一座高山，如同擎天一柱般插向天空，所以古人的詩句中有‘終南
一柱’的說法。
LONG
        );
        set("outdoors", "zhongnan");
        set("exits", ([
                "north"    : __DIR__"shanlu4",
                "westdown" : __DIR__"shanlu3",
        ]));
        set("objects",([
                __DIR__"npc/youke" : 1,
                __DIR__"npc/xiangke" : 2,
                __DIR__"npc/seller" : 1,
                "/clone/npc/walker" : 1,
        ]));

        set("coor/x", -3130);
        set("coor/y", -10);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}