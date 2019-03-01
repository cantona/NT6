
#include <weapon.h>
#include <ansi.h>
inherit STAFF;

void create()
{
        set_name(NOR + YEL "青銅杖" NOR, ({ "qingtong zhang","qingtong","zhang" }));
        set_weight(800);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("long", NOR + YEL "這是一根青銅鍛造的杖，入手沉甸甸的，似乎相當結實。\n" NOR);
                set("material", "qingtong");
                set("value", 100000);
        }
        init_staff(300);
        setup();
}

int query_autoload()
{
        return 1;
}
