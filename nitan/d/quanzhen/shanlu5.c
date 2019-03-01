// /d/quanzhen/shanlu5.c
// Java Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "山間小徑");
        set("long", @LONG
這是一條位於終南山腳，鮮為人知的小徑。四周古木三天，樹林
蒼翠，遍地山花，枝頭啼鳥唱和不絕。往東可看到一條道路。往西北
可通往山林深處。
LONG
        );
        set("outdoors", "zhongnan");
        set("exits", ([
                "east"      : __DIR__"shanlu4",
                "northwest" : __DIR__"shanlu6",
        ]));

        set("no_clean_up", 0);
        set("coor/x", -3140);
        set("coor/y", 0);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}