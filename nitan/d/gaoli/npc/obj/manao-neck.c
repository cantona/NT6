
#include <armor.h>
#include <ansi.h>

inherit NECK;

void create()
{
   set_name(HIY"瑪瑙項鏈"NOR, ({ "necklace"}) );
   set_weight(1000);
   if( clonep() )
     set_default_object(__FILE__);
   else {
     set("long","這是一串名貴的瑪瑙項鏈。\n");
     set("material", "瑪瑙");
     set("unit", "串");
     set("value", 1000);
     set("armor_prop/armor",10);
     set("armor_prop/dodge",2);
     set("armor_prop/per",5);
   }
   setup();
}
