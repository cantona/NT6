#include <ansi.h>
inherit ITEM; 

void create()
{
	      set_name(HIG"搶旗戰 - "HIW"五鬼印"NOR, ({"fwar five ghost seal","seal"}) );
        set_weight(300);
        set("unit", "個");
        set("long", "搶旗戰專用特殊物品，使用(apply)後可解除搬運旗子時的忙碌狀況。\n");
        set("value", 1);
        set("can_be_applied", 1);
        set("no_store",1);
        set("no_sell", 1);
        set("flag_war_item", 1);
 //       set("no_get", 1);
        set("no_drop", 1);
        setup();
}

int do_apply(object me) {
	object ob;
	if(!me) return 0;
	ob = this_object();
  if(environment() != me) return notify_fail(name()+"不在你身上。\n");
  if(!sizeof(me->query_temp("flag_war"))) return notify_fail(name()+"只能在搶旗戰的時候使用。\n");
  if(!sscanf(base_name(environment(me)), "/d/flagwar/%*s")) return notify_fail(name()+"只能在搶旗戰場使用。\n");
	if(!me->query_temp("flag_war/move_busy")) return notify_fail("你現在沒有因為搬運旗子而產生的忙碌狀況。\n");
  message_vision("$N拿起$n，口中喃喃唸着聽不懂的音節，手指着$n胡亂揮舞着。\n突然從$n冒出微微的光芒，$N看起來不知道那裏變的有些不同了。\n", me, ob);
	me->delete_temp("flag_war/move_busy");
  destruct(ob);
  return 1;
}