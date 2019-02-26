#include <armor.h>
#include <ansi.h>

inherit CLOTH;
inherit F_NOCLONE;

void create()
{
            set_name(NOR + YEL "飛駝金甲" NOR, ({ "feituo jinjia", "feituo", "jinjia", "armor", "jia", }) );
        set_weight(10000);
        set("unit", "副");
              set("long", YEL "這是一副用黃金打造而成的護甲，甲上雕刻着背生翅\n"
                    "膀的駱駝。傳説中只有高昌國王才可使用飛駝標記。\n" NOR);
        set("material", "cloth");
        set("value",1000000);
        set("no_sell", 1);
        set("armor_prop/dodge", -30);
        set("armor_prop/armor", 200);
        set("stable", 0);
        setup();
        check_clone();
}