// Room: /d/huashan/songlin3.c

inherit ROOM;

void create()
{
        set("short", "松樹林");
        set("long", @LONG
這是一片松樹林。幾丈高的松樹密密麻麻，遮得不見天日。地上
落滿松針，有不知名的野兔偷偷逃過。四周一片寂靜。
LONG );
        set("exits", ([
                "south" : __DIR__"songlin" + (random(4) + 1),
                "north" : __DIR__"songlin" + (random(4) + 1),
                "east"  : __DIR__"songlin3",
                "west"  : __DIR__"songlin" + (random(4) + 1),
        ]));

        set("outdoors", "huashan");
        setup();
        replace_program(ROOM);
}
