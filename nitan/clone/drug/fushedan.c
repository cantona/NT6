// Code of ShenZhou
//  poison: fushedan.c
// Jay 3/18/96

// more work needed to use this object to make poison

inherit ITEM;
int cure_ob(string);

void create()
{
        set_name("腹蛇膽", ({"shedan", "dan"}));
        set("unit", "粒");
        set("long", "這是一隻綠瑩瑩的腹蛇膽，是製備毒藥的最佳原料。\n");
        set("value", 500);
        set("medicine", 1);
                set("no_sell", 1);
        setup();
}

/*
int do_eat(string arg)
{
        if (!id(arg))
                return notify_fail("你要吃什麼？\n");
        return notify_fail("你找死啊。\n");
}
*/


int cure_ob(object me)
{

   message_vision("$N吃下一粒" + name() + "。\n", me);
   if ((int)me->query_condition("snake_poison") > 0) {
      me->apply_condition("snake_poison", 0);
   write("突然，你覺得腹內猶如翻江倒海....");
      addn("qi", -500, me);
   }

   destruct(this_object());
   return 1;
}