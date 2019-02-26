// /d/beihai/xiaolu1.c
// Last Modified by winder on May. 22 2002

inherit ROOM;

void create()
{
        set("short", "小路");
        set("long", @LONG
這是一條沿着湖的小路，路西邊是一片松樹林，東面可以看見瓊島
上的白塔。松樹林裏不時可以看見一隻只松鼠跳來跳去。
LONG
        );
        set("exits", ([
                "south" : __DIR__"ximen",
                "north" : __DIR__"xiaolu2",
        ]));
        set("outdoors", "beihai");
        set("no_clean_up", 0);

        set("coor/x", -200);
        set("coor/y", 4060);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}