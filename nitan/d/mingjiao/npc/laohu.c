// /d/mingjiao/npc/laohu.c 老虎
inherit NPC;
void create()
{
        set_name("老虎", ({ "lao hu", "hu" }) );
        set("race", "野獸");
        set("age", 5);
        set("long", "一隻兇猛的大老虎。\n");
        set("attitude", "aggressive");
        set("limbs", ({ "頭部", "身體", "前爪", "後爪", "尾巴" }) );
        set("verbs", ({ "bite", "claw" }) );
        set("combat_exp", 200000);
        set("str", 80);
        set("con", 80);
        set("no_get",1);
              set("chat_chance", 6);
              set("chat_msg", ({
              (: this_object(), "random_move" :),
              }) );
        set_temp("apply/damage", 30);
        set_temp("apply/armor", 50);
        setup();
}


