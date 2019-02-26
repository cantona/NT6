// Room: /d/hengshan/xuankong1.c
// Date: Oct. 2 1997 by That

inherit ROOM;

void create()
{
        set("short", "懸空寺北樓");
        set("long", @LONG
這裏是懸空寺的北門樓，也是北碑亭。登樓俯視，如臨深淵，谷底
仰望，如壁間丹鳳。向南有懸空棧橋通往南樓。
LONG
        );
        set("exits", ([
                "south"    : __DIR__"zhanqiao",
                "up"       : __DIR__"sanjiaodian",
                "westdown" : __DIR__"cuiping2",
        ]));
        set("objects", ([
                __DIR__"npc/yafu" : 1,
        ]));
//        set("no_clean_up", 0);
        set("coor/x", 0);
        set("coor/y", 3180);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}
