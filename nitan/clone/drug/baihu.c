// Code of ShenZhou
// baihu.c 白虎奪命丸
// xQin 04/01

#include <ansi.h>

inherit ITEM;
int cure_ob(string);
void create()
{
   set_name(HIW"白虎奪命丸"NOR, ({"baihu wan", "duoming wan", "wan"}));
   if (clonep())
      set_default_object(__FILE__);
   else {
      set("no_sell",1);
      set("no_get",1);
      set("no_drop",1);
      set("unit", "顆");
      set("value", 100000);
   }
   setup();
}


int cure_ob(object me)
{
   
        if (me->query_condition("bonze_drug") > 0)
        {
        addn("max_neili", -1, me);
        message_vision(HIR"$N吃下一顆" + name() + HIR"，只覺五臟六腑都在翻騰，原來服食藥物過多，適得其反。\n"NOR, me);
        destruct(this_object());
        return 1;
        }
        set("eff_jing",query("max_jing",  me), me);
        set("jing",query("max_jing",  me), me);
        set("jingli",query("max_jingli",  me), me);
        set("eff_qi",query("max_qi",  me), me);
        set("qi",query("max_qi",  me), me);
        set("neili",query("max_neili",  me), me);

   
       message_vision(HIW"$N吃下一顆" + name() + HIW"，只覺一股真氣從丹田上升，瞬間便已周行全身經脈迴歸丹田。\n"NOR, me);
       me->apply_condition("bonze_drug", 60);
       destruct(this_object());
       return 1;
}