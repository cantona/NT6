// Room: /d/shaolin/shijie10.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "石階");
        set("long", @LONG
松樹與松樹似乎都擠在一塊生長，陽光到這裏變得格外黯淡只在
地上留下斑駁的碎影。靜聽不遠處格的一聲，象是松枝斷落的聲音。
LONG );
        set("exits", ([
                "southdown" : __DIR__"shijie9",
                "northup" : __DIR__"shijie11",
        ]));
        set("outdoors", "shaolin");
        setup();
        replace_program(ROOM);
}
