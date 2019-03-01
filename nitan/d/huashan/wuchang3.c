// wuchang3.c

inherit ROOM;

void create()
{
        set("short", "東練武場");
        set("long", @LONG
這裡是華山派的練武場，場上立這幾個木人，地處偏僻，有些荒
涼。
LONG );
        set("exits", ([ /* sizeof() == 2 */
            "west"     : __DIR__"wuchang1",
        ]));
        set("outdoors", "huashan");

        set("for_family", "華山派");

        setup();
        replace_program(ROOM);
}
