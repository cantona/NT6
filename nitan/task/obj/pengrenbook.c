#include <ansi.h> 
inherit TASK; 
void create() 
{ 
        set_name( HIY "烹飪大全" NOR, ({ "pengren book" }) ); 
        set_weight(2); 
        if( clonep() ) 
                destruct(this_object()); 
        else { 
                set("unit", "本"); 
                set("material", "paper"); 
                set("long", "這是一本摸上去油膩膩的小本子，上面記載了肉，粥，菜共計八大類的各種佳餚做法。\n"); 
        } 
        set("owner", "廚娘"); 
        setup(); 
} 
