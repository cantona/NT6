
#include <armor.h>
#include <ansi.h>

inherit MEDAL;

void create()
{
        set_name(HIG "斬妖勛章" NOR, ({ "zhanyao xunzhang", "zhanyao", "xunzhang" }));
        set("long", HIG "斬殺千年九頭蛇精後獲得的勛章，非常珍貴，乃勇者的象徵。\n" NOR);
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "枚");
                set("value", 200000);
                set("material", "bronze");
                set("armor_prop/damage", 200);
                set("armor_prop/zhanyao", 1);
                set("special/desc", HIR "佩帶後可增加神龍島殺怪經驗及潛能獎勵10%。" NOR);
                set("armor_prop/con", 6);
                set("armor_prop/dex", 6);
                set("armor_prop/str", 6);
                set("armor_prop/int", 6);

        }
        setup();
}        

int query_autoload()
{
        return 1;
}