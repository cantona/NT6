// 神話世界﹒西遊記﹒版本４．５０
/* <SecCrypt CPL V3R05> */
 
// jingping.c 凈瓶 

inherit ITEM;
inherit F_LIQUID;

void create()
{
   set_name("凈瓶", ({"jingping", "bottle"}));
   set_weight(1000);
   if (clonep())
     set_default_object(__FILE__);
   else {
     set("long", "南海觀音盛水的凈瓶。\n");
     set("unit", "個");
     set("value", 5000);
     set("max_liquid", 500);
   }

   // because a container can contain different liquid
   // we set it to contain wine at the beginning
   set("liquid", ([
     "type": "water",
     "name": "凈水",
     "remaining": 400,
     "drunk_apply": 20,
   ]));
}