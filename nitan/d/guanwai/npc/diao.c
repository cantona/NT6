//  /guanwai/npc/diao.c

inherit NPC;
#include <ansi.h>;

void create()
{
        set_name(HIY"金雕"NOR, ({ "diao"}));
        set("race", "飛禽");
        set("age", 3);
        set("long", "一隻大金雕，正立在樹枝上仰視長天。\n");
        set("attitude", "peaceful");

        set("limbs", ({ "頭部", "身體", "翅膀", "爪子", "尾巴" }) );
        set("verbs", ({ "bite", "claw" }) );

        set("combat_exp", 30000);
        set_temp("apply/attack", 100);
        set_temp("apply/defense", 150);
        set_temp("apply/armor", 50);

        setup();
}
