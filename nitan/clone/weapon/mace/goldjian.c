// goldjian.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
#include <ansi.h>
inherit MACE;

void create()
{
        set_name(HIY"金裝□"NOR,({"gold mace", "mace", "goldmace", "jinjian"}));
        set_weight(10000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("value", 20000);
                set("material", "gold");
                set("wield_msg", "$N抽出了$n，喃喃道：□兒，□兒，再請你一回！\n");
                set("unwield_msg", "$N收起了$n，長吁了一口氣道：寶□果然又顯雄風！\n");
        }
        
        init_mace(95);
        setup();
}
