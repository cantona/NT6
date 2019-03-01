//黃樑枕 (進入夢境所用的道具)
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(YEL "黃樑枕" NOR, ({ "huangliang zhen", "zhen" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "據說帶著這個枕頭睡覺(dream)可以進入夢境。\n" NOR);
                set("unit", "個");
                set("value", 10);
                set("weight", 10);                
             }
        setup();
}

void init()
{
     add_action("have_dream", "dream");
}

int have_dream()
{
   object ob, me = this_player();

   if( !query("sleep_room", environment(me)) )
   {
      write("這裡不能睡覺，你怎麼做夢呀！\n");
      return 1;
   }

   foreach (ob in deep_inventory(me)) 
   { 
      if (ob->is_character()) 
      {   
         write("你身上帶著個大活物怎麼做夢呀?\n"); 
         return 1;
      }
   }
   message_vision("\n$N倒頭往床上一躺，呼呼大睡起來。\n\n", me);
   message_vision("睡著睡著，$N的身體忽然變得輕飄飄地飛走了。\n\n", me);
   set_temp("dream_place", environment(me), me);
   me->move("/d/reborn/dream");
   message_vision(HIG"一瞬間$N竟飄到了夢境裡。\n\n"NOR, me);
   destruct(this_object());
   return 1;
}
