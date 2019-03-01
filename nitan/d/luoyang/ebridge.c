#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "城東橋");
        set("long", @LONG
此橋高跨洛陽護城河之上，氣勢非凡。站在橋上向兩側望去，一條人
工開掘的護城河將洛陽城圍在當中，橋身以漢白玉造就，既美觀又很堅固。
橋上車水馬龍，川流不息。橋下的護城河水清澈見底，時有遊魚躍起。
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "west" : __DIR__"dongdoor",
                //"eastdown" : __DIR__"guandaoe1",
                "eastdown" : __DIR__"road2",
        ]));

	set("coor/x", -6920);
	set("coor/y", 2150);
	set("coor/z", 0);
	setup();
        //replace_program(ROOM);
}

void init()
{
        object me;
        object ob;

        if( interactive(me = this_player()) && !me->is_fighting() )
        {
                if( query_temp("juxianzhuang_step", me) == 11 )
                {
                        ob = new("/maze/juxianzhuang/npc/qiaofeng");
                        ob->move(environment(me));
                        message_vision(HIW "$N走了過來，後面跟著一輛馬車。\n", ob);
                }
        }
}