// xiao.c
#include <weapon.h>
#include <ansi.h>

inherit DAGGER;

void create()
{
        set_name(HIG"綠玉洞簫"NOR, ({ "xu xiao", "xiao"}));
        set_weight(4000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("long", "這是一根用綠玉做成的洞簫。\n");
                set("value", 2000);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一聲從懷中掏出一根$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n揣回懷裡。\n");
        }
        init_dagger(50);
        setup();
}
