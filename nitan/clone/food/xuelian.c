// 神話世界﹒西遊記﹒版本４．５０
/* <SecCrypt CPL V3R05> */
 
// xuelian.c 雪蓮
#include <ansi.h>
inherit ITEM;

void init();
void eat();

void create()
{
   set_name(HIW "雪蓮" NOR,({"xue lian", "xuelian", "lian"}));
   set_weight(20);
   if (clonep())
     set_default_object(__FILE__);
   else {
     set("long", "一朵雪蓮花，只生長于絕峰極寒之處。\n");
     set("unit", "朵");
     set("value", 300);
       }
   
   setup();
}

void init()
{
   add_action("do_chi", "eat");
}


int do_chi(string arg)
{   
        if( !this_object()->id(arg) ) return 0;
        if( this_player()->is_busy() )
                return notify_fail("你上一個動作還沒有完成。\n");

   if(!arg) return notify_fail("你要吃什麼？\n");

   if( query("max_atman", this_player())>0 )
   {
         message_vision(RED "$N吃下一朵雪蓮花，忽覺一陣反胃，又盡數吐了出來。\n" NOR, this_player());
   } 
   else 
   { 
      if( query("gender", this_player()) == "男性" )
     message_vision(GRN "$N吃下一朵雪蓮花，看起來精神多了。\n" NOR, this_player());
      else
     message_vision(GRN " $N吃下一朵雪蓮花，臉顯酡紅，倍增嬌艷。\n" NOR, this_player());
   }   
   destruct(this_object());
   return 1;
}