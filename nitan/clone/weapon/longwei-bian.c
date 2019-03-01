#include <ansi.h>
#include <weapon.h>
inherit WHIP;

void create()
{
        set_name(HIY "龍尾長鞭", ({ "longwei bian", "bian","longwei" }));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("long", HIY "這是一根做工奇特的長鞭，據說是用龍尾所鑄，威力不菲。\n" NOR);
                set("wield_msg", "$N「唰」的一聲從腰後抽出一根$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n別回腰後。\n");
                set("value", 100000);
        }
        init_whip(300);
        setup();
}

int query_autoload()
{
        return 1;
}

