#include <ansi.h> 
inherit TASK; 
void create() 
{ 
        set_name( WHT "醫仙心得" NOR, ({ "yixian xinde" }) ); 
        set_weight(2); 
        if( clonep() ) 
                destruct(this_object()); 
        else { 
                set("unit", "本"); 
                set("material", "paper"); 
                set("long", "這是一本醫書，其中收錄了各家醫術之所長，被視為醫之珍寶。\n"); 
        } 
        set("owner", "胡青牛"); 
        setup(); 
} 
