// Room: /d/mobei/caoyuan.c
// Last Modified by winder on May. 25 2001

inherit ROOM;

void create()
{
        set("short", "蒙古草原");
        set("long", @LONG
這如海般的蒙古草原，浩淼無邊，天空中蒼鷹掠過，發出尖尖的哨
音。身邊的牛羊緩緩的移動。西邊是個小土丘，上面長滿了灌木叢。
LONG);
        set("objects", ([ /* sizeof() == 1 */
                __DIR__"npc/huazheng" : 1,
        ]));
        set("outdoors","mobei");
        set("exits", ([ /* sizeof() == 3 */
                "westup" : __DIR__"guanmu1",
                "south" : __DIR__"caoyuan2",
                "north" : __DIR__"caoyuan4",
        ]));
        set("coor/x", -230);
        set("coor/y", 5170);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}