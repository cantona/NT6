// Feb. 6, 1999 by Winder
inherit ROOM;
void create()
{
        set("short", "山洞");
        set("long", @LONG
你壯起膽子，走進了山洞中，這裡暗無天日，突然間，有
只蝙蝠在你面前飛過，你被驚出了一身冷汗。越往裡走就越來
越黑，你好象迷失方向了。
LONG
        );
        set("exits", ([
                "east" : __FILE__,
                "west" : __FILE__,
                "south" : __FILE__,
                "north" : __DIR__"shandong5",
        ]));
        set("coor/x", 1590);
        set("coor/y", -1970);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}