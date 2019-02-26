// fangyi.c 方怡
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>;
inherit NPC;

int do_work();
string *fjob = ({"毒蛇", "蟒蛇", "腹蛇", "金環蛇", "水蛇", "銀環蛇", "竹葉青"});

void create()
{
        set_name("方怡", ({ "fang yi","fang" }));
        set("long", "一張瓜子臉，容貌甚美。\n");
        set("gender", "女性");
        set("age", 18);
        set("attitude", "peaceful");
        set("shen_type", 0);
        set("str", 23);
        set("int", 25);
        set("con", 25);
        set("dex", 26);
        set("max_qi", 600);
        set("max_jing", 600);
        set("neili", 600);
        set("max_neili", 600);
        set("jiali", 30);
        set("combat_exp", 50000);

        set_skill("force", 30);
        set_skill("dulong-dafa", 20);
        set_skill("dodge", 40);
        set_skill("yixingbu", 60);
        set_skill("strike", 30);
        set_skill("leg", 30);
        set_skill("parry", 40);
        set_skill("sword", 50);
        set_skill("jueming-leg", 40);
        set_skill("meiren-sanzhao", 40);
        set_skill("literate", 40);

        map_skill("force", "dulong-dafa");
        map_skill("dodge", "yixingbu");
        map_skill("leg", "jueming-leg");
        map_skill("sword", "meiren-sanzhao");
        map_skill("parry", "jueming-leg");
        prepare_skill("leg", "jueming-leg");

        set("party/party_name", HIY"神龍教"NOR);
        set("party/rank", HIR"赤龍門"NOR"教眾");
        set("party/level", 1);
        create_family("神龍教", 3, "弟子");

        set("inquiry", ([
                "教主" : (: do_work :),
                "神龍教" : (: do_work :),
                "jiao" : (: do_work :),
        ]));
        setup();
        carry_object(VEGETABLE_DIR"xionghuang");
        carry_object(WEAPON_DIR"changjian")->wield();
        carry_object(CLOTH_DIR"female-cloth")->wear();

}
void init()
{
        add_action("do_comfort", "comfort");
}

int do_work()
{
        object me = this_player();
        string fword, fwant;

        if( !query("sg/spy", me) && !wizardp(me) )
        {
                say("方怡哼了一聲説：假仁假義的東西，還不給我滾！\n");
                return 1;
        }
        if( query_temp("marks/方a", me) )
        {
                say("方怡不耐煩地説道：有完沒完了？\n");
                return 1;
        }
        if( time()<query("marks/方c", me)+180 )
        {
                command("slap"+query("id", me));
                say("方怡大怒道：蠢豬，這麼快就忘了！\n");
                return 1;
        }

        set_temp("marks/方a", 1, me);
        set("marks/方c", time(), me);

        fwant = fjob[random(sizeof(fjob))];
        fword = sprintf("方怡歎了口氣，説道：奉教主之命，捉%s來配藥。\n",fwant);
        say(fword);
        set_temp("marks/毒蛇", fwant, me);
        return 1;
}

int do_comfort(string arg)
{
        object me = this_player();

        if(!arg || !(arg == "fang yi" || arg == "fang")) return notify_fail("");
        message_vision("$N笑嘻嘻地安慰着方怡。\n", me);
        if( !query_temp("marks/方a", me) )
        {
                say("方怡冷笑道：別假惺惺了。\n");
                return 1;
        }
        delete_temp("marks/方a", me);
        message_vision("$N道：方姑娘，請放心！我這就給你去抓。\n", me);
        command("thank"+query("id", me));
        set_temp("marks/方b", 1, me);

        return 1;
}

int accept_object(object who, object ob)
{
        int expgain, faccept;

        if( !query_temp("marks/方b", who))return 0;
        if( query("name", ob) != query_temp("marks/毒蛇", who) )
        {
                command("angry"+query("id", who));
                command("disapp"+query("id", who));
                return 0;
        }

        delete_temp("marks/方b", who);
        delete_temp("marks/毒蛇", who);

        call_out("destroy_it", 1, ob);

        command("jump"+query("id", who));
        command("secret"+query("id", who));

        message_vision("方怡在$N耳邊悄悄的説了幾句話。\n", who);
        if( who->query_skill("medicine", 1) < 30 )
                who->improve_skill("medicine",random(2*query("int", who)));

        if( (expgain=query("combat_exp", who))>50000)return 1;

        addn("sg/exp", 1, who);
        expgain = (50000 - expgain) / 200;
        addn("combat_exp", expgain+random(expgain), who);

        return 1;
}

void destroy_it(object ob)
{
        if(ob) destruct (ob);
}
