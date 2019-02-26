// wuchang2.c

inherit ROOM;

void create()
{
        set("short", "北練武場");
        set("long", @LONG
這裏是華山派的練武場，場上立這幾個木人，南面是另一個練武
場，到處是華山的弟子人來人往，熱鬧非凡。
LONG );
        set("exits", ([ /* sizeof() == 2 */
            "south"     : __DIR__"wuchang1",
        ]));
        set("outdoors", "huashan" );
        set("for_family", "華山派");

        setup();
        replace_program(ROOM);
}
