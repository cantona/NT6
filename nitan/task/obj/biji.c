#include <ansi.h> 
inherit TASK; 
void create() 
{ 
        set_name( WHT "散文筆記" NOR, ({ "biji" }) ); 
        set_weight(2); 
        if( clonep() ) 
                destruct(this_object()); 
        else { 
                set("unit", "本"); 
                set("material", "paper"); 
                set("long", "一本散文筆記，你隨手翻看，只覺得詞藻華麗，令人仿佛身臨其境。\n"); 
        } 
        set("owner", "朱熹"); 
        setup(); 
} 
