// yahuan.c
inherit NPC;

void create()
{
        set_name("丫環", ({ "yahuan","ya","huan" }) );
        set("gender", "女性" );
        set("age", 18);
        set("long", "這是一個容貌清秀的丫環，正在打鬧的開心。\n");
        set("shen_type", -1);
        set("combat_exp", 1000);
        set("str", 20);
        set("dex", 18);
        set("con", 19);
        set("int", 20);
        set("attitude", "friendly");
        set("max_qi", 100);
        set("max_jing", 100);
        set("neili", 100);
        set("max_neili", 100);
        set("score", 800);

        set_skill("force", 20);
        set_skill("dodge", 20);
        set_skill("unarmed", 20);
        set_skill("parry", 20);
        set_temp("apply/attack", 8);
        set_temp("apply/defense", 12);
        set_temp("apply/damage", 11);
        set_temp("apply/armor", 7);
        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        object ob;

        ::init();

        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}
void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
             say("丫環笑著說道：這位" + RANK_D->query_respect(ob)
             + "，過來和我們一起玩吧。\n");
        return;
}
