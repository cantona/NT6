// Room: /d/songshan/tianzhongge.c
// Last Modified by Winder on Jul. 15 2001

inherit ROOM;

void create()
{
        set("short", "天中閣");
        set("long", @LONG
天中閣是中岳廟的大門，原稱黃中閣。廟內有古柏三百余株，金石
碑碣百余座。廟前石翁仲，雕制古樸。南面是嵩山的出口太室闕。
LONG );
        set("outdoors","songshan");
        set("exits", ([
                "north" : __DIR__"chongsheng",
                "south" : __DIR__"taishique",
        ]));
        set("objects", ([
                "/clone/npc/walker"  : 1,
        ]));
        set("no_clean_up", 0);
        set("coor/x", 0);
        set("coor/y", 710);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
