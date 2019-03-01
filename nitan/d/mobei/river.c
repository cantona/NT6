// Room: /d/mobei/river.c
// Last Modified by winder on May. 25 2001

inherit ROOM;

void create()
{
        set ("short", "水塘");
        set ("long", @LONG
一個渾濁的小水塘，邊上的水草都長到了岸邊，水中依稀有魚在遊
動。幾頭牛羊在塘邊旁若無人地喝水，似乎把誰都不看在眼裡，西面天
空中一片烏雲正向這邊移動，看來要下雨了。
LONG);
        set("no_clean_up", 0);
        set("outdoors","mobei");
        set("exits", ([ /* sizeof() == 2 */
                "west"      : __DIR__"caoyuan3",
                "northeast" : __DIR__"byriver",
        ]));
        set("coor/x", -210);
        set("coor/y", 5150);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}