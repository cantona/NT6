inherit ROOM;

void create()
{
        set("short", "金銀舖");
        set("long", @LONG
這裡原本是洛陽城裡最大金銀舖，洛陽城的居民遇到需要兌換存取的
時候都是直奔這裡。這裡的生意原本是最最興隆的，可是卻在一個月以前，
因為這裡的老板不怎麼的得罪了官府，被查封了起來。
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