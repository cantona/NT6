// Room: /d/village/shouse.c

inherit ROOM;

void create()
{
        set("short", "小土房");
        set("long", @LONG
這是一間用土坯搭成的房屋，屋裡只有幾件殘破的家俱。在靠門
口的牆角有一只空空的籠子，大概曾經用來養過雞、鴨之類的家禽。
LONG );
        set("exits", ([ /* sizeof() == 1 */
            "west" : __DIR__"sroad2",
        ]));
        set("objects", ([
            __DIR__"npc/oldwoman": 1
        ]) );

        setup();
        replace_program(ROOM);
}
 