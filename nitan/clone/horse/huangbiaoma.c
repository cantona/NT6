#include <ansi.h>

inherit NPC;

void create()
{
        set_name(HIY "黃驃馬" NOR, ({ "huangbiaoma"}));
        set("race", "野獸");
        set("gender", "雄性");
        set("age", random(3));
        set("long", "這是一匹黃驃駿馬，全身金黃，沒有一絲雜毛。\n");
        set("ridable", 1);
        set("int", 30);
        set("qi", 300);
        set("max_qi", 300);
        set("jing", 100);
        set("max_jing", 100);
        set("shen_type", 0);
        set("combat_exp",50000);
        set("attitude", "peaceful");

        set("limbs", ({ "頭部", "腹部", "尾巴","後腿","前腿" }) );
        set("verbs", ({ "bite", "hoof" }) );
        set_temp("apply/attack", 50);
        set_temp("apply/armor", 15);
        set_temp("apply/damage", 25);

        setup();
}
