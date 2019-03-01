
#include <armor.h>
#include <ansi.h>

inherit MYHEART2;

void create()
{
        set_name(HIM "仙鼠靈尾" NOR, ({ "xianshu lingwei2", "xianshu2", "lingwei2" }) );
        set_weight(1);
        if( clonep())
                set_default_object(__FILE__);
        else {
                set("material", "paper");
                set("unit", "根");
                set("long", HIM "公元二零零八年春節，于蓬萊仙島麒麟崖下斬殺蓬萊仙鼠後獲得的靈尾，異常珍貴，限量珍藏。\n" NOR);
                set("value", 1000000);
                set("limit", ([
                        "exp"    :   1000000,
                ]));                
                set("armor_prop/qy", 3);
                set("armor_prop/fy", 3);
                set("armor_prop/damage", 200);
                set("armor_prop/str", 4);
                set("armor_prop/int", 4);
                set("armor_prop/dex", 4);
                set("armor_prop/con", 4);
                set("special/desc", HIR "佩帶後可增加任務和殺怪獎勵1%，且減少蓬萊島上移動忙亂時間。" NOR);
                set("armor_prop/xianshu-lingwei", 1);
        }
        setup();
}

int query_autoload()
{
        return 1;
}