// wuxiuwen.c

#include <ansi.h>

inherit NPC;
string ask_me_1(string name);
string ask_me_2(string name);
void create()
{
        set_name("武修文", ({"wu xiuwen", "wu", "xiuwen"}));
        set("title", HIY"郭靖二弟子"NOR);
        set("gender", "男性");
        set("age", 21);
        set("long", "他是郭靖的二弟子，精明強幹，專門負責後勤。\n");
         set("attitude", "peaceful");
        
        set("per", 23);
        set("str", 20);
        set("int", 20);
        set("con", 30);
        set("dex", 25);

        set("inquiry", ([
                "黃蓉" : "那是我師母。\n",
                "郭靖" : "那是我師父。\n",
        ]));

        set("qi", 1000);
        set("max_qi", 1000);
        set("jing", 500);
        set("max_jing", 500);
        set("neili", 1000);
        set("max_neili", 1000);
        
        set("combat_exp", 80000);
        set("score", 20000);

        set("huju_count", 20);
        set("beixin_count", 2);
         
        set_skill("force", 50);
        set_skill("quanzhen-xinfa", 50);
        set_skill("unarmed", 50);
        set_skill("changquan", 50);
        set_skill("dodge", 50);
        set_skill("jinyan-gong", 50);
        set_skill("parry", 50);

        set("inquiry", ([
                "鐵護腕" : (: ask_me_1, "huwan" :),
                "鐵護腰" : (: ask_me_1, "huyao" :),
                "皮手套" : (: ask_me_1, "shoutao" :),
                "皮圍脖" : (: ask_me_1, "weibo" :),
                "鐵指套" : (: ask_me_1, "zhitao" :),
                "鐵背心" : (: ask_me_2, "beixin" :)
        ]));
        
        map_skill("force", "quanzhen-xinfa");
        map_skill("unarmed", "changquana");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "changquana");
        
        setup();
        
        carry_object("/clone/misc/cloth")->wear();
}
string ask_me_1(string name)
{
        mapping fam; 
        object ob;
        
        if (  present(name, this_player()) )
                return RANK_D->query_respect(this_player()) + 
                "你現在身上不是有這樣防具嗎，怎麼又來要了？ 真是貪得無饜！";

        if (query("huju_count") < 1)
                return "抱歉，你來得不是時候，防具已經發完了。";

        ob = new("/d/shaolin/obj/" + name);
        ob->move(this_player());

        addn("huju_count", -1);

        message_vision("武修文給$N一件"+query("name", ob)+"。\n",this_player());

        return "拿去吧。不過要記住，防具只可防身練武，不可憑此妨害他人。";
}

string ask_me_2(string name)
{
        mapping fam; 
        object ob;
        
        if (query("beixin_count") < 1)
                return "抱歉，你來得不是時候，武器已經發完了。";

        ob = new("/d/shaolin/obj/" + name);
        ob->move(this_player());

        addn("beixin_count", -1);

        message_vision("武修文給$N一件"+query("name", ob)+"。\n",this_player());

        return "拿去吧。不過要記住，鐵背心乃是防身寶物，不可憑此妨害他人。";
}
