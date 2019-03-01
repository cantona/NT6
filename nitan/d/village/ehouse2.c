// Room: /d/village/ehouse2.c

inherit ROOM;

void create()
{
        set("short", "民宅");
        set("long", @LONG
這是一間很結實的房子，雖然也是間土坯房，但看的出建造的比
村裡其他的土坯房要好很多。牆上掛著、地下擺著一些農具。
LONG );
        set("exits", ([ /* sizeof() == 1 */
            "south" :__DIR__"eroad2",
        ]));
        set("objects", ([
                __DIR__"npc/dibao": 1
        ]) );

        setup();
        replace_program(ROOM);
}
 