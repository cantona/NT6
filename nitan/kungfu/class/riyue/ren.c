//ren.c

#include <ansi.h>
#include "riyue.h"

inherit NPC;
inherit F_MASTER;
// inherit F_QUESTER;

string ask_linghuchong();

void create()
{
        set_name("任盈盈", ({ "ren yingying","ren","ying"}) );
        set("gender", "女性" );
        set("age", 20);
        set("shen_type", 1);
        set("combat_exp", 500000);

        set("per", 30);
        set("str", 16);
        set("dex", 27);
        set("con", 17);
        set("int", 18);

        set("attitude", "friendly");
        set("chat_chance", 3);
        set("chat_msg",({
        "任盈盈説道：不知令狐沖他，怎樣了，是否又和那小賤人在一起......\n",
        "任盈盈説道：也不知藍鳳凰見沒見到他，可真急死我了.......\n",
        }) );

        create_family("日月神教",2,"弟子 聖姑");

        set_skill("force", 120);
        set_skill("riyue-xinfa", 120);
        set_skill("dodge", 120);
        set_skill("piaomiao-shenfa", 120);
        set_skill("hand", 120);
        set_skill("huanmo-longtianwu", 120);
        set_skill("cuff", 120);
        set_skill("xuwu-piaomiao", 120);
        set_skill("parry", 120);
        set_skill("literate", 120);
        set_skill("sword", 120);
        set_skill("riyue-jian", 120);

        map_skill("force", "riyue-xinfa");
        map_skill("dodge", "piaomiao-shenfa");
        map_skill("hand", "huanmo-longtianwu");
        map_skill("cuff", "xuwu-piaomiao");
        map_skill("sword", "riyue-jian");
        map_skill("parry", "riyue-jian");

        prepare_skill("hand", "huanmo-longtianwu");
        prepare_skill("cuff", "xuwu-piaomiao");

        set("inquiry",([
            "令狐沖" : (: ask_linghuchong:),
        ]) );
        set("letter",1);

        set("master_ob",2);
        setup();
        carry_object("/clone/cloth/female5-cloth")->wear();
        carry_object("/d/heimuya/npc/obj/jin")->wear();
        carry_object("/d/heimuya/npc/obj/changjian")->wield();
        carry_object("/d/heimuya/npc/obj/letter");
}

void attempt_apprentice(object ob)
{
    if(! permit_recruit(ob))  return;

    if( query("shen", ob)>0 )
    {
         command("say 我倒是想收你，可是教主會不答應的！");
         return;
    }

    command("recruit "+query("id", ob));
    set("title", HIM"日月神教教眾"NOR, ob);
}

string ask_linghuchong()
{
    object me = this_player();
    object ob;

    message_vision("任盈盈説道：去年上華山一去就再無音信，他不會忘記我吧......\n", me );
    if(! query("letter"))
        return "這位" + RANK_D->query_respect(me) + "，我已經派" +
               "藍鳳凰去尋找了，也不知道怎麼樣了。";
    message_vision("任盈盈又説道：這位"+ RANK_D->query_respect(me)+"，我這裏有"
                   "信，你要是找到令狐沖，就把信交給他，他會明白的。\n" , me);
    ob=new("/d/heimuya/npc/obj/letter");
    ob->move(me);
    set("letter", 0);
    set_temp("ren_qingxin", 1, me);
    return "這封信煩你交給令狐沖。\n";
}

void reset()
{
     set("letter", 1);
}
