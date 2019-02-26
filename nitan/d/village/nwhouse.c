// Room: /d/village/nwhouse.c

inherit ROOM;

void create()
{
        set("short", "民房");
        set("long", @LONG
這是一個小房間，屋子裏飄着一股大葱加香粉的味道。靠牆擺着
張大牀，牀頭有個小梳粧枱。
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
 