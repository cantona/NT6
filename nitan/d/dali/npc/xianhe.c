// xianhe.c

inherit NPC;
#include <ansi.h>;
void create()
{
        set_name(HIR"丹"NOR"頂鶴", ({ "danding he", "he"}));
        set("race", "飛禽");
        set("age", 3);
        set("long", "一隻全身潔白的丹頂鶴，看來是修了翅膀，沒法高飛了。\n");
        set("attitude", "peaceful");

        set("limbs", ({ "頭部", "身體", "翅膀", "爪子", "尾巴" }) );
        set("verbs", ({ "bite", "claw" }) );

        set("combat_exp", 300);
        set_temp("apply/attack", 5);
        set_temp("apply/defense", 7);
        set_temp("apply/armor", 7);

        setup();
}
