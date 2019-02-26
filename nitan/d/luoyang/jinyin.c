inherit ROOM;

void create()
{
        set("short", "金銀鋪");
        set("long", @LONG
這裏原本是洛陽城裏最大金銀鋪，洛陽城的居民遇到需要兑換存取的
時候都是直奔這裏。這裏的生意原本是最最興隆的，可是卻在一個月以前，
因為這裏的老闆不怎麼的得罪了官府，被查封了起來。
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "north" : __DIR__"eroad4",
        ]));
        set("objects", ([
                "/d/kaifeng/npc/guanbing" : 2,
        ]));
	set("coor/x", -6950);
	set("coor/y", 2140);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}