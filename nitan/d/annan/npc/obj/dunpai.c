#include <armor.h>
#include <ansi.h>
inherit SHIELD;

void create()
{
   set_name(HIG"籐牌"NOR, ({ "tengpai"}) );
   set_weight(300);
   if( clonep() )
     set_default_object(__FILE__);
   else {
     set("material", "鐵");
     set("unit", "個");
     set("value",1500);
     set("armor_prop/armor",35);
     set("armor_prop/dodge",11);
   }
   setup();
}