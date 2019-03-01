
#include <armor.h>
#include <ansi.h>

inherit HEAD;
 
void create()
{
        set_name(HIY "黃頭巾" NOR, ({ "huang toujin", "huang", "toujin" }) );
        set_weight(300);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "cloth");
                set("unit", "頂");
                set("long", HIY "這是一頂黃頭巾，相傳漢朝黃巾義軍所佩帶。\n" NOR);
                set("value", 100000);
                set("armor_prop/armor", 100);
                set("armor_prop/str", 10);
        }
        setup();
}

int query_autoload()
{
        return 1;
}