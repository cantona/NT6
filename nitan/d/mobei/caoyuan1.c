// Room: /d/mobei/caoyuan1.c
// Last Modified by winder on May. 25 2001

inherit ROOM;

void create()
{
        set("short", "蒙古草原");
        set("long", @LONG
遠處煙塵起處，一隊隊蒙古鐵騎列隊來往操練。西邊夕陽如血，混
圓的殘陽下是連綿的營帳和牛羊，那就是鐵木真的部落。東面的樹林邊
幾個小孩正在玩耍，樹林後面是座荒山。 
LONG);
        set("outdoors","mobei");
        set("objects", ([ /* sizeof() == 1 */
                __DIR__"npc/tujiu" : 2,
        ]));
        set("exits", ([ /* sizeof() == 2 */
                "east"  : __DIR__"shulin",
                "south" : __DIR__"shulin5",
        ]));
        set("coor/x", -230);
        set("coor/y", 5230);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}