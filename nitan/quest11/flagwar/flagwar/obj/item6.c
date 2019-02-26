#include <ansi.h>

inherit ITEM; 

void create()
{
	      set_name(HIG"搶旗戰 - "HIW"定身符"NOR, ({"fwar ding seal","seal"}) );
        set_weight(300);
        set("unit", "個");
        set("long", "搶旗戰專用特殊物品，使用(shoot seal on <目標>)後令目標無法行動。\n");
        set("value", 1);
        set("no_store",1);
        set("no_sell", 1);
        set("flag_war_item", 1);
 //       set("no_get", 1);
        set("no_drop", 1);
        setup();
}

void init() 
{
   add_action("do_shoot","shoot");
}
int do_shoot(string arg) {
	object me, ob, target;
	string id;
	int damage;
	me = this_player();
	if(!me) return 0;
	ob = this_object();
  if(environment() != me) return notify_fail(name()+"不在你身上。\n");
  if(me->is_busy()) return notify_fail("你上一個動作還沒有完成。\n");

  if(!sscanf(base_name(environment(me)), "/d/flagwar/%*s")) return notify_fail(name()+"只能在搶旗戰場使用。\n");
  if(!sizeof(me->query_temp("flag_war"))) return notify_fail(name()+"只能在搶旗戰的時候使用。\n");
  if(!arg || sscanf(arg, "seal on %s", id) != 1) return notify_fail("指令格式：shoot seal on <目標>。\n");
  if(!target = present(id, environment(me))) return notify_fail("這裏沒有這個人。\n");
  if(target == me) return notify_fail("你只能射別人。\n");
  if(!target->query_temp("flag_war")) return notify_fail("你只能對搶旗戰的人使用。\n");
  message_vision("$N拿着$n對準"+target->name()+"，嘴中唸出喃喃之聲。\n$n化作一道白光直撲"+target->name()+"而去。\n", me, ob);
  me->want_kill(ob);
  damage = 1000+random(2000);
  target->receive_damage("qi", damage, me);
  COMBAT_D->report_status(target);
  me->fight_ob(target); 
  target->kill_ob(me);
  me->start_busy(1);
  message_vision(HIY"突然間$n光華大盛，$N被嚇的動都不敢動。\n", target, ob);
    	if(target->query_temp("flag_war/guard")) {
    		target->add_temp("flag_war/guard", -1);
    		message_vision(HIY"$N身上的特殊防護效果發揮效用抵擋住這次攻擊。\n"NOR, target);
    	} else target->start_busy(10);
  destruct(ob);
  return 1;
}