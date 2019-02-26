// Room: /d/village/smithy1.c

inherit ROOM;

void create()
{
        set("short", "鐵匠鋪");
        set("long", @LONG
這是一間甚是簡陋的鐵匠鋪，入門正中是個大鐵砧，滿地煤渣碎
鐵，牆上掛着幾張犁頭，屋子的角落裏堆着幾把破鋤頭、鐮刀，靠牆
放着幾把新出爐的鐵錘。東面有一個小門，門上掛著個破布簾。
LONG );
        set("exits", ([ /* sizeof() == 2 */
            "east" : __DIR__"smithy2",
            "north" : __DIR__"eroad3",
        ]));
        set("objects", ([
             __DIR__"npc/smith": 1
        ]) );

        setup();
        replace_program(ROOM);
}
 