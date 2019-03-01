// shulin1.c 樹林
// Java Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "小樹林");
        set("long", @LONG
這是一片小樹林，周圍的樹木都很高。間雜着一些叫不出名字的鮮
花，五彩繽紛。你隱隱地有些擔心起來：不會迷路了吧，轉頭間卻看見
東南邊似乎有一條小路，隱藏在樹叢之中。
LONG        );
        set("outdoors", "gumu");
        set("exits", ([
                "northdown" : __DIR__"shulin0",
                "southwest" : __DIR__"shulin2",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3200);
        set("coor/y", 70);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}