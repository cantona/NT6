#include <ansi.h> 
inherit TASK; 
void create() 
{ 
        set_name( MAG "乾坤袋" NOR, ({ "qiankun dai" }) ); 
        set_weight(20); 
        if( clonep() ) 
                destruct(this_object()); 
        else { 
                set("unit", "個"); 
                set("material", "paper"); 
                set("long", "一個普普通通甚至有些破舊不堪的布袋，知道究竟有何用的人少之甚少。\n"); 
        } 
        set("owner", "說不得"); 
        setup(); 
} 
