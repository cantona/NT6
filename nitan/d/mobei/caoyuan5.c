// Room: /d/mobei/caoyuan5.c
// Last Modified by winder on May. 25 2001

inherit ROOM;

void create()
{
        set("short", "蒙古草原");
        set("long", @LONG
烏雲從西面的天空快速地移動過來，烏雲中有閃點在不住閃動，烏
雲下就是廣袤的蒙古草原，遠處的閃電照亮了一片連綿的營帳，那就是
鐵木真的部落。
LONG
        );
        set("no_clean_up", 0);
        set("outdoors","mobei");
        set("exits", ([ /* sizeof() == 2 */
                "northeast" : __DIR__"caoyuan6",
                "south"     : __DIR__"caoyuan4",
        ]));
        set("coor/x", -230);
        set("coor/y", 5190);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}