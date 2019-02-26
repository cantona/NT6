// wuchang1.c

inherit ROOM;

void create()
{
        set("short", "南練武場");
        set("long", @LONG
這裏是華山派的練武場，場上立這幾個木人，西南通向廣場，北
面是另一個練武場，東邊也是一個練武場，可是不知怎麼的，似乎很
少有人過去。附近到處是華山的弟子人來人往，熱鬧非凡。
LONG );
        set("exits", ([ /* sizeof() == 2 */
            "southwest" : __DIR__"square",
            "north"     : __DIR__"wuchang2",
            "east"      : __DIR__"wuchang3",
        ]));
        set("outdoors", "huashan" );
        set("for_family", "華山派");

        setup();
        replace_program(ROOM);
}
