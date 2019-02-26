// This program is a part of NT MudLIB 
 
#include <ansi.h>
#include <armor.h>
inherit NECK;
 
void create()
{
        set_name(HBGRN "刑天項鍊" NOR, ({ "xingtian neck", "neck" }) );
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("long", HIY "這便是刑天戴過的項鍊，通體血光滔天。\n" NOR);
                set("value", 3000); 
                set("no_sell", "這樣東西不能賣。\n");
                set("rigidity",8000);   
                set("material", "tian jing");
                set("no_pawn", 1);
                set("armor_prop/armor", 10);
        }
        
        set("mod_mark", "A2030");
        set("mod_level", "M2030");
        set("mod_name", HBRED "刑天套裝" NOR);
        set("quality_level", 3);

        setup();
}

