#include <armor.h>
#include <ansi.h>
inherit NECK;

void create()
{
   set_name(HIG"藤甲護頸"NOR, ({ "hujing"}) );
   set_weight(300);
   if( clonep() )
     set_default_object(__FILE__);
   else {
     set("material", "鐵");
     set("unit", "個");
     set("value",200);
     set("armor_prop/armor",38);
     //set("armor_prop/dodge",1);
   }
   setup();
}