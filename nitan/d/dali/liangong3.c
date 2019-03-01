// liangong3.c

inherit ROOM;

void create()
{
        set("short", "練武場");
        set("long", @LONG
這裡擺著一些銅人，他們比木人更加結實，也就不容易壞，因此
也是高手修煉上乘絕藝的地方。向南一直走穿過練功場就是王府內院。
LONG );
        set("exits", ([
                "south" : "/d/dali/liangong2",
        ]));
        set("objects", ([
                "/clone/npc/tong-ren": 3,
        ]));
	set("coor/x", -19111);
	set("coor/y", -6801);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}