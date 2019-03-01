//xueshi.c

inherit NPC;

void create()
{
        set_name("李博淵", ({"li boyuan", "li", "boyuan"}));
        set("gender", "男性");
        set("age", 45);
        set("title", "大學士");
        set("str", 25);
        set("int", 30);
        set("long", "李博淵是國子監大學士。\n");
        set("combat_exp", 40000);
        set("attitude", "friendly");
        set("class", "scholar");
        set_skill("unarmed", 50);
        set_skill("dodge",50);
        set_skill("literate", 400);
        set_skill("parry", 50);

        set("neili", 500); 
        set("max_neili", 500);
        set("inquiry", ([
                "讀書識字": "對了，你是來對地方了！\n",
                "學習" : "學習是要交學費的\n",
        ]) );

        setup();
        carry_object("/d/changan/npc/obj/choupao")->wear();
}

int recognize_apprentice(object ob)
{
        if( query_temp("mark/李", ob)<1 )
                return 0;
        addn_temp("mark/李", -1, ob);
        return 1;
}

int accept_object(object who, object ob)
{
        object me = this_player();
        if( !query_temp("mark/李", who) )
        set_temp("mark/李", 0, who);
        if( query("money_id", ob) && ob->value() >= 10000 )
        {
                message_vision("李博淵同意指點$N一些讀書寫字的問題。\n", who);
                addn_temp("mark/李", ob->value()/50, who);
        
                return 1; 
        }
}