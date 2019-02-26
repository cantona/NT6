#include <weapon.h>
#include <ansi.h>
#include <armor.h> 
inherit HANDS; 

void create()
{
        set_name(HIY "琥珀神環" NOR, ({ "hupo shenhuan" , "hupo" , "shenhuan", "huan" }) );
        set_weight(500);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "枚");
                set("long", HIY "散發着古樸光澤的指環，這便是燕子鄔主人慕容"
                            "博的信物琥珀神環。\n" NOR);
                set("value", 800000);
                set("no_sell", "…嗯…這東西珍是夠珍貴，可是年代久遠，我難以估價。");
                set("material", "steel");
                set("armor_prop/armor", 30);
                set("armor_prop/finger", 50);
                set("armor_prop/strike", 50);
                set("armor_prop/unarmed_damage", 100);
                set("wear_msg", HIY "$N" HIY "微微一笑，輕輕戴上一枚琥珀神環，頓"
                                "時指尖光華四射。\n" NOR);
                set("remove_msg", HIY "$N" HIY "將琥珀神環從指尖取了下來。\n" NOR);
                set("stable", 100);
        }
        setup();
}