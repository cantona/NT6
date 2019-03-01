// Room: /d/mobei/buluo1.c
// Last Modified by winder on May. 25 2001

inherit ROOM;

void create()
{
        set("short", "鐵木真部落");
        set("long", @LONG
鐵木真部落是當今大漠最強盛的一族，隱有一統蒙古之勢。練綿的
帳蓬望不到邊，來往的人們手中多拿著武器，向北去就是轅門。東西兩
邊都是部落中人居住的蒙古包。
LONG
        );
        set("objects", ([ /* sizeof() == 1 */
                __DIR__"npc/menggukid" : 2,
        ]));
        set("exits", ([ /* sizeof() == 4 */
                "east"  : __DIR__"menggubao1",
                "west"  : __DIR__"menggubao",
                "north" : __DIR__"yuanmen",
                "south" : __DIR__"buluo",
        ]));
        set("outdoors", "mobei");
        set("coor/x", -210);
        set("coor/y", 5220);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}