// Room: dong8.c

#include <ansi.h>
inherit ROOM;

string* dirs = ({"east", "south", "west", "north"});

void create()
{
	set("short", HIR "麒麟窟" NOR);
        set("long", HIR "\n\n" 
"這是麒麟窟。進來頓覺一股熱浪撲面而來，沖得你差點暈了\n"
"過去。四周一片通紅，地面上冒著絲絲白氣，腳底劇烈的炙痛\n"
"使你幾乎立腳不住。熱風帶著隆隆巨響沖擊著耳鼓，令你覺得\n"
"置身洪爐之中，全身的水分都在被一滴滴地烤幹。你感到生命\n" 
"正離你而去﹒！\n\n" NOR 
     ); 
        set("exits", ([
                "east"      : __DIR__"dong9",
                "south"     : __DIR__"dong2",
                "west"      : __DIR__"dong4",
                "north"     : __DIR__"dong6",
	]));
	setup();
}

void init()
{
        object me = this_player();

        me->set_temp("die_reason", "闖入麒麟窟，被烈炎燒死了");
        me->receive_damage("qi", 500);
        me->receive_wound("qi",  500);
        message_vision(HIR "四周烈火熊熊，烈炎襲向$N將$N遍體灼傷！\n" NOR, me);
}
