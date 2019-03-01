// Room: /d/huashan/songlin1.c

inherit ROOM;

void create()
{
        set("short", "鬆樹林");
        set("long", @LONG
這是一片鬆樹林。幾丈高的鬆樹密密麻麻，遮得不見天日。地上
落滿鬆針，有不知名的野兔偷偷逃過。四周一片寂靜。
LONG );
        set("exits", ([
                "south" : __DIR__"changlang",
                "north" : __DIR__"songlin" + (random(4) + 1),
                "east"  : __DIR__"songlin2",
                "west"  : __DIR__"songlin" + (random(4) + 1),
        ]));

        set("outdoors", "huashan");
        setup();
        replace_program(ROOM);
}
