inherit ITEM;
inherit F_FOOD;
int do_eat(string arg);
void create()
{
        set_name("烤肉", ({ "fried meat", "meat" }) );
        set_weight(350);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一串香噴噴的烤肉\n");
                set("unit", "串");
                set("value", 3);
                set("food_remaining", 12);
                set("food_supply", 12);
                set("material", "bone");
                set("decayed",0);
        }
        setup();
}
void eat_decayed(object me)
{
   int waittime;
   waittime=5-me->query_con()/10;
   if (waittime<1) waittime=1;
   me->start_busy(waittime);
   message_vision("$N忽然覺得肚子裏咕嘟咕嘟直響，找了塊乾淨地方就蹲了下來...\n嗚，好臭！\n", me);
   return;
}
int do_eat(string arg)
{
   int foo;
/*
   foo=::do_eat(arg);
   if (!foo) return foo;
*/
   if (query("decayed")<1)
       message_vision("$N覺得" + name() + "非常好吃，真想再來一串。\n", this_player());
   else
   {
     message_vision("$N覺得" + name() + "味道怪怪的。\n", this_player());
     call_out("eat_decayed",this_player()->query_con()/5+1,this_player());
   }
  return 1;
}
