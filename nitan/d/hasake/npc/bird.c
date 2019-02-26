// 天鈴鳥
inherit NPC;
void create()
{
        set_name("天鈴鳥", ({ "tianlin niao", "bird" }) );
        set("race", "飛禽");
        set("age", 1);
        set("long", "一隻美麗的天鈴鳥，鳥兒的歌聲像是天上的銀鈴。
這鳥兒只在晚上唱歌，白天睡覺。有人説，這是天上的星星掉下來之後變的。\n");
        set("attitude", "friendly");
        set("max_qi", 100);
        set("max_jing", 100);
        set("eff_jingli", 100);        
        set("limbs", ({ "嘴", "翅膀", "爪子" }) );
        set("verbs", ({ "bite", "claw" }) );
        set("combat_exp", 100);
        set("chat_chance", 30);
        set("chat_msg", ({ (: random_move :),}) );
        set_temp("apply/attack", 5);
        set_temp("apply/defense", 5);
        set_temp("apply/damage", 5);
        set("senlin", 1);
        setup();
}
