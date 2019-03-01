// mudao06.c 墓道
// Java Oct.10 1998

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIG"墓道"NOR);
        set("long", @LONG
這裡是古墓中的墓道，四周密不透風，借著牆上昏暗的燈光，你能
勉強分辨出方向。牆是用整塊的青石砌合起來的，接合得甚是完美，難
以從中找出一絲縫隙。燈光照在青石壁上，閃爍著碧幽幽的光點。
    東邊石壁上似乎有一扇暗門(door)。
LONG        );
        set("exits", ([
                "west" : __DIR__"zhongting",
//                "east" : __DIR__"houting",
        ]));
        set("item_desc", ([
                "door" : "一扇厚重的石門，光溜溜的全沒有把手。你認真看了看，發現門邊的石壁上似乎有什麼按鈕(niu)可以開門。\n",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3190);
        set("coor/y", 10);
        set("coor/z", 90);
        setup();
}

void init()
{
        add_action("do_an", "press");
        add_action("do_an", "an");
}

int do_an(string arg)
{
        object room, me = this_player();

        if( !arg || arg != "niu" )
        {
                message_vision("你在石壁上亂按一氣，除了一手灰，啥也沒摸著。\n", me);
                return 1;
        }
        if( query("exits/east"))
        {
                return notify_fail("石門已經是開著的，你還按個啥？\n");
        }
        if( me->query_skill("yunv-xinfa", 1) > 10)
        {
                message_vision("$N站在石門前，也不知在哪裡按了一下，石門吱吱響著，緩緩打開了。\n", me);
                if( !(room = find_object(__DIR__"houting")) )
                        room = load_object(__DIR__"houting");
                set("exits/east", __DIR__"houting");
                set("exits/west", __DIR__"mudao06", room);
                tell_room(room,"只聽得石門在吱吱聲中被緩緩打開。\n");
                remove_call_out("close");
                call_out("close", 5, me);
        }
        else
                message_vision("$N試著在石壁上按來按去，可是石門紋絲不動，只得罷了。\n", me);
        return 1;
}

void close(object me)
{
        object room;

        tell_room(this_object(), "石門緩緩地關上，恢復了原狀。\n");
        delete("exits/east");
        if( !(room = find_object(__DIR__"houting")) )
                room = load_object(__DIR__"houting");
        delete("exits/west", room);
        tell_room(room,"西牆的暗門緩緩地關上了。\n");
}