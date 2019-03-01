// Modified by haiyan

#include <ansi.h> 
inherit ITEM; 

void create() 
{ 
     set_name( HIY"符紙"NOR, ({ "fu zhi" })); 
     set_weight(20); 
     if( clonep() ) 
         set_default_object(__FILE__); 
     else
     { 
         set("unit", "張"); 
         set("no_put", 1);
         set("no_sell", 1);
         set("long", "這是一張道士們用來驅魔捉鬼的符紙，上面畫著一些奇怪的紅色符號。\n"); 
     } 
     setup(); 
} 
