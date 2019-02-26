// Room: /d/songshan/woshi.c
// Last Modified by winder on Jul. 17 2001

inherit ROOM;

void create()
{
        set("short", "卧室");
        set("long", @LONG
你走進了一間卧室。一種非常清亮的感覺撲面而來。琴劍書畫，掛
在牆上。窗明几淨，一切都井井有條。
    右首一張牀，牀上一條黃緞被，看起來很是舒適。
LONG );
        set("exits", ([
                "west" : __DIR__"houting",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -10);
        set("coor/y", 930);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}