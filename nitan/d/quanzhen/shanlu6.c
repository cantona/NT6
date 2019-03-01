// /d/quanzhen/shanlu6.c
// Java Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "山間小徑");
        set("long", @LONG
這是一條位於終南山腳，鮮為人知的小徑。四周古木叁天，樹林
蒼翠，遍地山花，枝頭啼鳥唱和不絕。往西和東南可通往山林深處。
LONG
        );
        set("outdoors", "zhongnan");
        set("exits", ([
                "southeast" : __DIR__"shanlu5",
                "west"      : __DIR__"shanlu7",
        ]));

        set("coor/x", -3150);
        set("coor/y", 10);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}