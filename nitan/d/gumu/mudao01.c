// mudao01.c 墓道
// Java Oct.10 1998

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIG"墓道"NOR);
        set("long", @LONG
這裏是古墓中的墓道，四周密不透風，藉着牆上昏暗的燈光，你能
勉強分辨出方向。牆是用整塊的青石砌合起來的，接合得甚是完美，難
以從中找出一絲縫隙。燈光照在青石壁上，閃爍着碧幽幽的光點。
LONG        );
        set("exits", ([
                "north" : __DIR__"mumen",
                "south" : __DIR__"qianting",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3220);
        set("coor/y", 20);
        set("coor/z", 90);
        setup();
}

/*
void init()
{
        add_action("do_move", "move");
        add_action("do_move", "luo");
        add_action("do_move", "tui");
}

int do_move(string arg)
{
        object room, me = this_player();

        if( !arg || arg != "shi" )
        {
                return notify_fail("你要移動什麼？\n");
        }
        if( !query("exits/north"))
        {
                return notify_fail("降龍石已經落下，你還能移動什麼？\n");
        }
        if((int)me->query_str()>33)
        {
                message_vision("$N站在降龍石前，雙掌發力推動降龍石，只聽得降龍石吱吱連聲，緩緩向下落去，封住了墓門。\n", me);
                delete("exits/north");
                if( !(room = find_object(__DIR__"mumen")) )
                        room = load_object(__DIR__"mumen");
                delete("exits/south", room);
                tell_room(room,"只聽得降龍石吱吱連聲，緩緩向下落去，封住了墓門。\n");
        }
        else
                message_vision("$N試着推了推巨石，巨石紋絲不動，只得罷了。\n", this_player());
        return 1;
}

*/