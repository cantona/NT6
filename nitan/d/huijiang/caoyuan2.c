// Room: /d/huijiang/caoyuan2.c
// Last Modified by winder on Sep. 12 2001

inherit ROOM;

void create()
{
        set("short", "草原");
        set("long", @LONG
腳下是軟軟的青草，還留著早晨的露珠，便如同一塊綠色的大毯子
般。成群的牛羊就是這塊毯子上繡著的點點花朵。牧羊的姑娘輕輕揮動
手中的皮鞭，唱著草原上的牧歌。
LONG );
        set("outdoors", "huijiang");
        set("objects", ([ /* sizeof() == 1 */
                __DIR__"npc/sheep" : 2,
        ]));
        set("exits", ([ /* sizeof() == 1 */
                "east" : __DIR__"caoyuan",
        ]));
        set("coor/x", -50060);
        set("coor/y", 9080);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}