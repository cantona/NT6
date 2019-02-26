// xiaowu1.c 小屋
// Java Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "小屋");
        set("long", @LONG
你走進了一間小屋，房間很小，除了一張小牀放不下別的東西了。
牀上好像有幾件疊得整整齊齊的粗布衫，洗的乾乾淨淨。
LONG        );
        set("exits", ([
                "south" : __DIR__"mudao10",
                "north" : __DIR__"mudao04",
        ]));
        set("objects", ([
                __DIR__"obj/fengjiang" : 3,
                __DIR__"obj/fengmi" : 1,
        ]));
        set("coor/x", -3220);
        set("coor/y", -10);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}
