inherit ITEM;

void create()
{
        set_name("風箏", ({ "kite" }) );
        set_weight(150);
        set_max_encumbrance(1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("prep", "on");
                set("long", "一個蝴蝶風箏，放風箏的線上幫著一個小小的竹哨。 \n");
                set("value", 2000);
        }
}

void init()
{
        add_action("do_play", "play");
}

int do_play(string arg)
{
   object me, ob;    

   me = this_player();
   ob = this_object();
   if( me->is_fighting() )
      return notify_fail("在戰鬥中放風箏，想找死嗎！\n");
   if( me->is_busy() )
      return notify_fail("你上一個動作還沒有完成，不能放風箏。\n");
   if (!arg || (arg != "kite" && arg != "風箏")) return 0;
   tell_object(me, "你掏出一個" + ob->name() + "。\n");
   environment(me)->kite_notify(ob, 0);

   return 1;
}

int is_container() { return 1; }
