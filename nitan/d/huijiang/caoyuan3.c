// Room: /d/huijiang/caoyuan3.c
// Last Modified by winder on Sep. 12 2001

inherit ROOM;

void create()
{
        set("short", "草原");
        set("long", @LONG
柔嫩的青草就踩在腳下，天上浮雲飄過，牧羊的姑娘輕哼著小曲，
揮動皮鞭驅趕著牛羊，遠處天山山脈高不可攀，一邊的湖水在靜靜的波
動。幾頭蒼鷹張著翅膀在空中緩緩滑過。
LONG
        );
        set("outdoors", "huijiang");
        set("objects", ([ /* sizeof() == 1 */
                __DIR__"npc/ox" : 1,
        ]));
        set("exits", ([ /* sizeof() == 1 */
                "west" : __DIR__"caoyuan",
        ]));
        set("coor/x", -50040);
        set("coor/y", 9080);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}