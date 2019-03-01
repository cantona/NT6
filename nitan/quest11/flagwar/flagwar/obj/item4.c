#include <ansi.h>

inherit ITEM; 

void create()
{
	      set_name(HIG"搶旗戰 - "HIW"太古赤火箭"NOR, ({"fwar remote antiquity fire arrow","arrow"}) );
        set_weight(300);
        set("unit", "個");
        set("long", "搶旗戰專用特殊物品，使用(shoot arrow on <目標>)後有機會令目標致死。\n");
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
  if(!arg || sscanf(arg, "arrow on %s", id) != 1) return notify_fail("指令格式：shoot arrow on <目標>。\n");
  if(!target = present(id, environment(me))) return notify_fail("這裡沒有這個人。\n");
  if(target == me) return notify_fail("你只能射別人。\n");
  if(!target->query_temp("flag_war")) return notify_fail("你只能對搶旗戰的人使用。\n");
  message_vision("$N拿著$n對準"+target->name()+"，突然臉色一變鬆手射出。\n$n挾著燥熱的火光追循"+target->name()+"而去。\n", me, ob);
  me->want_kill(ob);
  damage = 1000+random(2000);
  target->receive_damage("qi", damage, me);
  COMBAT_D->report_status(target);
  me->fight_ob(target); 
  target->kill_ob(me);
  me->start_busy(5);
  if(random(3) >= 1) {
  message_vision(HIY"突然間$n光華大盛，陡然散發出死亡氣息撲向$N。\n", target, ob);
    	if(target->query_temp("flag_war/guard")) {
    		target->add_temp("flag_war/guard", -1);
    		message_vision(HIY"$N身上的特殊防護效果發揮效用抵擋住死亡氣息。\n"NOR, target);
    	} else target->unconcious();
  }
  destruct(ob);
  return 1;
}