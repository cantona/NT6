// /d/beihai/xiaolu2.c
// Last Modified by winder on May. 22 2002

inherit ROOM;

void create()
{
        set("short", "小路");
        set("long", @LONG
這是一條沿着湖的小路，路西邊是一片松樹林，上的白塔。松樹林
裏不時可以看見一隻只松鼠跳來跳去。東面隱隱可以看見一個亭子的一
角。
LONG
        );
        set("exits", ([
                "east"      : __DIR__"wulong",
                "south"     : __DIR__"xiaolu1",
                "northeast" : __DIR__"dukou1",
        ]));
        set("outdoors", "beihai");
        set("no_clean_up", 0);

        set("coor/x", -200);
        set("coor/y", 4070);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}