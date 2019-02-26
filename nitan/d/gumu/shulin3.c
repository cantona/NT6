// shulin3.c 樹林
// Java Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "小樹林");
        set("long", @LONG
這裏是樹林的邊緣，參天古樹已經很稀少了。東面有一座高山，隱
約看見山間雲霧繚繞中，似乎有什麼廊檐的建築。山勢緩和，但山上鬱
鬱葱葱地栽滿了樹木。
LONG        );
        set("outdoors", "gumu");
        set("exits", ([
                "south"     : __DIR__"caodi",
                "northeast" : __DIR__"shulin2",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3220);
        set("coor/y", 50);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}