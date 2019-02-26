//Room: shoushi-dain.c

inherit ROOM;

void create()
{
        set("short", "首飾店");
        set("long", @LONG
一間首飾店。首飾店內放着一個長條桌子，桌子上擺有幾隻檀香
木盒，盒子是全開着的，裏面各種金銀首飾樣樣俱全，看得人眼花繚
亂，首飾店的老闆正在查點貨物。
LONG );
        set("exits", ([ /* sizeof() == 1 */
                "south" : "/d/changan/qixiang5",
        ]));
        set("objects", ([
                "/d/changan/npc/chen-laoban" : 1,
        ]) );

        set("coor/x", -10700);
	set("coor/y", 1980);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}