// /d/yixing/npc/banjiu.c
// Last Modified by winder on Jul. 12 2002

inherit NPC;

void create()
{
        set_name("斑鳩", ({ "ban jiu"}));
        set("race", "野獸");
        set("age", 3);
        set("long", "一隻小斑鳩，在田地間跳上跳下。\n");
        set("attitude", "peaceful");

        set("limbs", ({ "頭部", "身體", "翅膀", "爪子", "尾巴" }) );
        set("verbs", ({ "bite", "claw" }) );

        set("combat_exp", 300);
        set_temp("apply/attack", 3);
        set_temp("apply/defense", 5);
        set_temp("apply/armor", 1);

        setup();
}
