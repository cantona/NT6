#include <weapon.h>
#include <ansi.h>
#include <armor.h> 
inherit HANDS; 

void create()
{
        set_name(HIM "逍遙神仙環" NOR, ({ "shenxian huan" , "xiaoyao" , "shenxian", "huan" }) );
        set_weight(500);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "枚");
                set("long", HIM "散發着古樸光澤的玉斑指，這便是逍遙掌門人信物逍遙神仙環。\n" NOR);
                set("value", 800000);
                set("no_sell", "…嗯…這東西珍是夠珍貴，可是年代久遠，我難以估價。");
                set("material", "steel");
                set("armor_prop/armor", 30);
                set("armor_prop/hand", 50);
                set("armor_prop/strike", 50);
                set("armor_prop/unarmed_damage", 100);
                set("wear_msg", HIM "$N" HIM "微微一笑，輕輕戴上一枚玉斑指，頓時指尖光華四射。\n" NOR);
                set("remove_msg", HIM "$N" HIM "將逍遙神仙環從指尖取了下來。\n" NOR);
                set("stable", 100);
        }
        setup();
}
