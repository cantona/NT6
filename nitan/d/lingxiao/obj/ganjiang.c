//LUCAS 2000-6-18
// ganjiang.c 
#include <weapon.h>
#include <ansi.h>
inherit SWORD;

void create()
{
        set_name( HIC "幹將" NOR , ({ "ganjiang", "jian" }));
        set_weight(8000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "這就是赫赫有名的幹將,劍鋒上隱隱透出一股清氣,仔細凝望,只覺一股肅殺之氣森熱煌饃□□n");
                set("value", 20000);
                set("material", "steel");
                set("weapon_prop/per", 8);
                set("wield_msg", "$N「唰」的一聲抽出一柄$n握在手中,頓時風沙飛揚,黑雲罩日,漫天神鬼驚懼。\n");
                set("unwield_msg", "$N將手中的$n插回劍鞘,一下子風平浪靜,晴空萬裡。\n");
        }
        init_sword(100);
        setup();
}
