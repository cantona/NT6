
#include <armor.h>
#include <self.h>

inherit ARMOR;

void create(class data)
{
        set_name("甲", ({ "armor", }));

        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("long", "這是一件普通的護甲。\n");
                set("unit", "件");
                set("value", 200);
                set("material", "cloth");
                set("armor_prop/armor", query("point")*2);
        }

        set_weight(500);
        setup();
}

// 武器裝備的傷害值
int apply_damage()
{
        int d;
        int p;

        attack_lvl = weapon_level();
        p = query("point");
        d = attack_lvl * p / MAX_LEVEL + query("bless") * 10; // 乾坤聖水聖化一次增加十點攻擊
        return d + p;
}

// 防禦裝備的有效值
int apply_armor()
{
        int d;
        int p;

        defense_lvl = armor_level();
        p = query("point");
        // if( d > p * 3 / 2) d = p * 3 / 2 + query("bless") * 10;// 乾坤聖水聖化一次增加10點防禦
        d = p * 3 / 2 + query("bless") * 2;// 乾坤聖水聖化一次增加2點防禦
        return d + p;
}

#include <ansi.h>
#include <armor.h>

inherit ARMOR;

void create()
{
        set_name("金絲甲", ({ "aarmor" }));
        set_weight(9000);
        set("item_make", 1);
        set("unit", "張");
        set("long", "這是由神鐵煉製而成的一張護甲。
護甲緣上刻着一行小字：胡大一(adami)
");
        set("value", 2100000);
        set("point", 152);
        set("material", "magic stone");
        set("material_file", "ddd");
        set("wear_msg", "$N裝備金絲甲。\n");
        set("remove_msg", "$N脱下了金絲甲。\n");
        set("armor_prop/armor", apply_armor());

        setup();
}

string long() { return query("long") + item_long(); }


#include <ansi.h>
#include <weapon.h>

inherit SWORD;
inherit F_ITEMMAKE;

void create()
{
        set_name("白虹劍", ({ "asword" }));
        set_weight(9000);
        set("item_make", 1);
        set("unit", "柄");
        set("long", "這是由神鐵煉製而成的一柄劍。
劍柄上刻着一行小字：胡大一(adami)
");
        set("value", 2100000);
        set("point", 190);
        set("material", "magic stone");
        set("wield_msg", "$N「唰」的一聲抽出一柄寒光閃閃的$n握在手中。\n");
        set("unwield_msg", "$N將手中的$n插回劍鞘。\n");

        init_sword(apply_damage());

        setup();
}

string long() { return query("long") + item_long(); }
