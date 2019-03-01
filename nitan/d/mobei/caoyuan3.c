// Room: /d/mobei/caoyuan3.c
// Last Modified by winder on May. 25 2001

inherit ROOM;

void create()
{
        set("short", "蒙古草原");
        set("long", @LONG
漠北的這片荒原，土地貧瘠，只能以畜牧為生，生活在這片土地上
的蒙古各個部落之間為爭奪牛羊，奴隸，土地，財帛而互相廝殺，鐵木
真就是當今最強盛的一個部落。
LONG);
        set("objects", ([ /* sizeof() == 1 */
                __DIR__"npc/heijiu" : 2,
        ]));
        set("exits", ([ /* sizeof() == 3 */
                "northwest" : __DIR__"caoyuan2",
                "east"      : __DIR__"river",
                "south"     : __DIR__"mobei",
        ]));
        set("outdoors","mobei");
        set("coor/x", -220);
        set("coor/y", 5150);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}