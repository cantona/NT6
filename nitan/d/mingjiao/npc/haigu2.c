#include <ansi.h>

inherit ITEM;

void create()
{
       set_name("骸骨", ({"haigu"}) );
       set_weight(10000);
       set_max_encumbrance(6000000);
       if( clonep() )
               set_default_object(__FILE__);
       else{
       set("unit", "具");
       set("long", "這是一具女子的骸骨。在其胸部插著一把短劍。\n");
       set("value", 0);
       set("material","wood");
       set("no_get",1);
       set("init",0);
       }
       setup();
}

void init()
{
       object ob;
       object me=this_object();
       if( query("init") == 0 ) {
               ob=new("/clone/weapon/duanjian");
               ob->move(me);
               addn("init",1);
       }
}