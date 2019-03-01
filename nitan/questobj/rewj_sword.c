// rewj_sword
#include <weapon.h>
#include <ansi.h>
inherit SWORD;

void create()
{
        set_name(HIY"一陣雲煙"NOR, ({ "cigar", "sword" }));
        set_weight(6000);
        set("taskobj", 1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("value", 2000);
                set("material", "steel");
                set("wield_msg", "$N抽了$n，慘然一笑，接著長嘆一聲，從褲兜裡取出個白玉磁瓶，倒出菩提子吧唧吧唧啃了起來。\n");
                set("unwield_msg", "$N一聲長嘆：人生如夢，夢如$n，煙如霧，霧如水蒸氣，水蒸氣如那個屁啊。\n");
        }
        init_sword(30);
        setup();
}
