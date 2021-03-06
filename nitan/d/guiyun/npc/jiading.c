// jiading.c 家丁

inherit NPC;

void create()
{
        set_name("家丁", ({ "jia ding", "jia", "ding" }));
        set("gender", "男性");
        set("age", 35);
        set("long", "歸雲莊家丁。\n");
        set("combat_exp", 40000);
        set_skill("dodge", 50);
        set_skill("unarmed", 50);
        set_temp("apply/attack",  50);
        set_temp("apply/defense", 50);
        set("shen_type", 1);
        setup();

        add_money("silver",3);
        carry_object("/clone/misc/cloth")->wear();
}

int accept_object(object who, object ob)
{
        if( query("id", ob) == "guiyun shuxin" )
        {
                command("bow"+query("id", this_player()));
                set_temp("marks/guiyun", 1, this_player());
                write("家丁説道：" + RANK_D->query_respect(ob) + "原來是少莊主的朋友，快快請進。\n");
                return 1;
        }
        return 0;
}
