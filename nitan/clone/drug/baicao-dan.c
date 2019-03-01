// Code of ShenZhou
#include <ansi.h>

inherit ITEM;
void create()
{
   set_name("百草丹", ({"baicao dan", "dan"}));
   if (clonep())
      set_default_object(__FILE__);
   else
   {
      set("unit", "顆");
      set("value", 4000);
      set("no_sell", 1);
      set("long", "這是一顆丐幫的百草丹，功能療傷保精。\n");
      set("medicine", 1);
      set("only_do_effect", 1); 
   }
   setup();
}

int do_effect(object me)  
{
   message_vision("$N吃下一顆" + name() + "。\n", me);
   
   if( query("eff_qi", me)<query("max_qi", me)/6
    || query("eff_jing", me)<query("max_jing", me)/6){
        write("你傷勢過重，服食丹藥僅能略盡人事！\n");
   }
   else if( query("eff_qi", me) == query("max_qi", me )
    && query("eff_jing", me) == query("max_jing", me)){
        me->receive_wound("qi", 50);
        me->receive_wound("jing", 50);
        write( HIR "你沒傷胡亂服食丹藥，反有大害！\n\n" NOR );
   }
   else {
        if( query("eff_qi", me)<query("max_qi", me)){
                me->receive_curing("qi", 50);
        }
        
        if( query("eff_jing", me)<query("max_jing", me)){
                me->receive_curing("jing", 50);
        }
        
        message_vision(YEL "$N只覺傷勢大為好轉，可見此丹靈效。\n\n" NOR, me);
   }
                
   destruct(this_object());
   return 1;
}
