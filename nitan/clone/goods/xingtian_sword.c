

// This program is a part of NT MudLIB 
 
#include <ansi.h>
#include <weapon.h>
inherit SWORD;
 
void create()
{
        set_name(HBGRN "刑天魔劍" NOR, ({ "xingtian sword", "sword" }));
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", HIY "這便是刑天曾經使用的魔劍，劍體血光沖天。\n" NOR);
                set("value", 3000); 
                set("no_sell", "這樣東西不能賣。\n");
                set("rigidity",8000);   
                set("material", "tian jing");
                set("no_pawn", 1);
        }     

        set("mod_mark", "A2033");
        set("mod_level", "M2030");
        set("mod_name", HBRED "刑天套裝" NOR);
        init_sword(50000);
        set("quality_level", 3);
        
        setup();
}

