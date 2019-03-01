// 神話世界﹒西遊記﹒版本４．５０
/* <SecCrypt CPL V3R05> */
 
#include <weapon.h>

inherit HAMMER;
inherit F_LIQUID;

void create()
{
  set_name("大茶壺", ({"teapot"}));
  set_weight(2000);
  if( clonep() )
    set_default_object(__FILE__);
  else {
    set("long", "一個大茶壺。\n");
    set("unit", "個");
    set("value", 50);
    set("max_liquid", 7);
    set("wield_msg", "$N抓起一個$n，握在手中當武器。\n");
    set("material", "bone");
  }
  
  set("liquid", ([
       "type": "water",
       "name": "西湖龍井茶",
       "remaining": 8,
       ]) );
  init_hammer(1);
  setup();

}
