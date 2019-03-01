#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIY"羅盤"NOR, ({ "luo pan", "luo", "pan", "compass" }));
        set("weight", 1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "只");
                set("long", "一只精工制造的羅盤，可以定位(dingwei)，是航海者的必備物品。\n" NOR);
                set("value", 5000);
        }
        setup();
}

void init()
{ 
  add_action("do_dingwei","dingwei");
}
        
int do_dingwei()
{
    int stepe,stepw,steps,stepn;
    object me, where;
    string msg;
    me = this_player();
    where = environment(me);
    if( query("outdoors", where) != "大海" )
        return notify_fail("你又沒出海，用羅盤幹嘛？\n");
    if( query("exits/out", where) || query("boat_of", where) )
           return notify_fail("船還沒開呢。\n");     
    message_vision("$N將$n托在掌心，仔細地察看著現在的方位。\n",me,this_object());
    msg = "\n羅盤顯示你現在的位于黃道帶";
    stepe=query_temp("stepe", where);
    stepw=query_temp("stepw", where);
    steps=query_temp("steps", where);
    stepn=query_temp("stepn", where);
    if(stepe) msg += "以東"+chinese_number(stepe)+"個距離";
    if(stepw) msg += "以西"+chinese_number(stepw)+"個距離";
    if(steps) msg += "、以南"+chinese_number(steps)+"個距離";
    if(stepn) msg += "、以北"+chinese_number(stepn)+"個距離";
    if(!stepe && !stepw && !steps && !stepn) msg += "正中";
    msg += "的地方。\n"; 
    write(msg);
    return 1;
}