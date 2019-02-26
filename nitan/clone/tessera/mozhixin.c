#include <ansi.h>

inherit TESSERA;

void create()
{
        set_name(HIY "聖魔之心·魔" NOR, ({"mozhi xin", "mozhi", "xin"}));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "霎那間天地變色，萬物隱匿，乃魔界至高無上的寶物，支配着魔界萬物。\n" NOR);
                set("unit", "塊");
                set("value", 13000);
                set("can_be_enchased", 1);
                set("enchase/SN", 1 + random(9));
                set("enchase/type", "all");
                set("enchase/cur_firm", 100); 
                set("enchase/weapon_prop", ([
                        "add_magic" : 50,     
                        "add_skill" : 30,     
                ]));
                set("enchase/armor_prop", ([
                        "add_magic" : 50,     
                        "add_skill" : 30,     
                ]));
                set("magic/type", "magic");
                set("magic/power", 90 + random(11));
        }
        setup();
}

int query_autoload()
{
        return 1;
}
