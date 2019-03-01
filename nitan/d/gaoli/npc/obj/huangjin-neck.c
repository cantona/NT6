
#include <armor.h>
#include <ansi.h>

inherit NECK;

void create()
{
   set_name(HIY"黃金項鏈"NOR, ({ "necklace"}) );
   set_weight(1000);
   if( clonep() )
     set_default_object(__FILE__);
   else {
     set("long","這是一串名貴的黃金項鏈。\n");
     set("material", "黃金");
     set("unit", "串");
     set("value", 1000);
     set("armor_prop/armor",10);
     set("armor_prop/dodge",2);
     set("armor_prop/per",5);
   }
   setup();
}
