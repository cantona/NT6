// Feb. 6, 1999 by Winder
inherit ROOM;
void create()
{
        set("short", "山洞");
        set("long", @LONG
你壯起膽子，走進了山洞中，這裏暗無天日，突然間，有
只蝙蝠在你面前飛過，你被驚出了一身冷汗。越往裏走就越來
越黑，你好像迷失方向了。
LONG
        );
        set("exits", ([
                "east" : __FILE__,
                "west" : __FILE__,
                "south" : __DIR__"shandong4",
                "north" : __FILE__,
        ]));
        set("coor/x", 1590);
        set("coor/y", -1960);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}