// Room: /d/village/shop.c

inherit ROOM;

void create()
{
        set("short", "雜貨店");
        set("long", @LONG
這是一間小小的雜貨店，經營些油、鹽、醬、醋及日用百貨，村
子裏的人多數是很窮，除了生活必需品，這裏很少販賣其它物品。
LONG );

        set("exits", ([ /* sizeof() == 1 */
            "south" : __DIR__"eroad3",
        ]));

        set("objects", ([
            __DIR__"npc/xiejian": 1
        ]));

        setup();
        replace_program(ROOM);
}
 