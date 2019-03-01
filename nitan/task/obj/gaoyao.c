#include <ansi.h> 
inherit TASK; 
void create() 
{ 
        set_name( HIC "膏藥" NOR, ({ "gaoyao" }) ); 
        set_weight(2); 
        if( clonep() ) 
                destruct(this_object()); 
        else { 
                set("unit", "張"); 
                set("material", "paper"); 
                set("long", "這是一張特制的膏藥，彌漫著淡淡的草藥氣味。\n"); 
        } 
        set("owner", "徐天川"); 
        setup(); 
} 
