// xiong.c
inherit NPC;
void create()
{
        set_name("大白熊", ({ "xiong" }) );
        set("race", "野獸");
        set("age", 6);
        set("con", 100);
        set("str", 100);
        set("long", "一只毛長身巨，狀如大牯牛的大白熊。\n");
        set("attitude", "aggressive");
        set("limbs", ({ "頭部", "身體", "前爪", "後爪", "尾巴" }) );
        set("verbs", ({ "bite", "claw" }) );
        set("combat_exp", 250000);
              set("chat_chance", 6);
              set("chat_msg", ({
              (: random_move :),
              }) );
        set_temp("apply/damage", 30);
        set_temp("apply/armor", 70);
        setup();
}
