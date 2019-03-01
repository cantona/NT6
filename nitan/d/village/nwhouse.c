// Room: /d/village/nwhouse.c

inherit ROOM;

void create()
{
        set("short", "民房");
        set("long", @LONG
這是一個小房間，屋子裡飄著一股大蔥加香粉的味道。靠牆擺著
張大床，床頭有個小梳妝台。
LONG );
        set("exits", ([ /* sizeof() == 1 */
            "northeast" : __DIR__"nwroad2",
        ]));
        set("objects", ([
                __DIR__"npc/cuihua": 1
        ]) );

        setup();
        replace_program(ROOM);
}
 