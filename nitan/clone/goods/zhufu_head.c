// This program is a part of NT MudLIB 
// Written by Lonely@nitan.org
// head.c 頭盔
 
#include <ansi.h>
#include <armor.h>
 
inherit HEAD;
 
void create()
{
        set_name(HIY "神" HIW "之" HIM "祝福" NOR YEL "頭盔" NOR, ({ "zhufu head", "helmet", "toukui" }) );
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "steel");
                set("unit", "頂");
                set("long", HIM "這是一頂鐵制的頭盔，用以保護頭部。\n" NOR);
                set("value", 1500); 
                set("armor_prop/armor", 20);
        }
        
        set("auto_load", 1); 
        set("mod_mark", "A2011");  
        set("mod_level", "M2010");  
        set("mod_name", HIY"神"HIW"之"HIM"祝福"NOR YEL"套裝"NOR); 

        set("enchase", ([ 
                "flute" : 1,
                "used" : 1,
                "apply_prop" : ([ /* sizeof() == 2 */
                        "armor1" : 30,
                        "int" : 1,
                ]),
        ]));

        set("insert", ([ /* sizeof() == 1 */
                "1" : ([ /* sizeof() == 3 */
                        "id" : "magic stone",
                        "name" : HIM"玄石"NOR,
                        "apply_prop" : ([ /* sizeof() == 2 */
                                "armor1" : 30,
                                "int" : 1,
                        ]),
                ]),
        ]));
        
        set("require", ([
                "max_level" : 40,
                "max_age"   : 30,
        ]));
        set("quality_level", 2); 
        setup();
}

