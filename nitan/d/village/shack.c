// Room: /d/village/ehouse1.c

inherit ROOM;

void create()
{
        set("short", "民宅");
        set("long", @LONG
這是一間十分簡陋，四壁漏風的小房子，屋子裡連一張象樣的床
都沒有，只有一面門板上面舖著些幹草。這屋子的主人一定是貧困潦
倒，窮的叮當響。
LONG );
        set("exits", ([ /* sizeof() == 1 */
            "south" :__DIR__"wexit",
        ]));

        set("objects", ([
            __DIR__"npc/poorman": 1
        ]));

        setup();
        replace_program(ROOM);
}
 