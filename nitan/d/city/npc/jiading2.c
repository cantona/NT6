// jiading.c 家丁

inherit NPC;
string ask_kid();

void create()
{
        set_name("家丁", ({ "jia ding", "jia" }));
        set("gender", "男性");
        set("age", 35);

        set("combat_exp", 4000);
        set_skill("dodge", 20);
        set_skill("unarmed", 20);
        set_temp("apply/attack",  10);
        set_temp("apply/defense", 10);
        set("shen_type", -1);

        set("chat_chance", 30);
        set("chat_msg", ({
                "家丁道：去去，一邊去。。。\n",
        "嗯。家丁皺了皺眉頭，一副不愛理人的樣子。\n",
        "家丁道：你能不能別來煩我？\n"
    }) );
    
        set( "inquiry", ([
                "楊府" : "哈哈，你不正在楊府門口嗎？\n",
                "小玲瓏山館" : "就是楊府。\n",
                "揚州" : "揚州繁華甲天下！\n",
                "楊磊石" : (: ask_kid :)
        ]) );
        setup();
        add_money("silver",3);
        carry_object("/clone/misc/cloth")->wear();
}

string ask_kid()
{
    if( query_temp("kid_ask", this_player()) )
    {
    }
    else
        return "那是我家少爺。\n";
}