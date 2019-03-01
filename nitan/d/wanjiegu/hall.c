// Room: /t/wanjiegu/hall.c

inherit ROOM;

void create()
{
        set("short", "內堂");
        set("long", @LONG
這裏放着一張大桌子，靠牆有兩張凳子，白白的牆壁一塵不染，
有一個人正在屋裏走來走去，顯的心情焦操。
LONG );
        set("exits", ([ /* sizeof() == 4 */
            "north" : __DIR__"backyard",
            "west" : __DIR__"left_room",
            "south" : __DIR__"xiaoting",
            "east" : __DIR__"right_room",
        ]));
        set("objects", ([
            __DIR__"npc/zhong" : 1,
        ]));
//        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}