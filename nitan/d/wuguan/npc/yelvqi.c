#include <ansi.h>

inherit NPC;
string *names = ({"打掃馬房", "鋸木頭", "劈柴", "澆菜地", "鋤草" });
string ask_job();

void create()
{
        set_name("耶律齊", ({ "yelv qi", "yelv", "qi" }));
        set("title", "全真教第二代弟子");
        set("nickname", HIY "丐幫幫主" NOR);
        set("long", "耶律齊是郭靖和黃蓉的大女婿，郭芙的丈夫。\n");
        set("gender", "男性");
        set("age", 35);
        set("str", 35);
        set("dex", 30);
        set("int", 30);
        set("con", 30);
        set("per", 28);
        set("shen_type", 1);
        set("max_qi", 4000);
        set("max_jing", 3000);
        set("max_neili", 5000);
        set("neili", 5000);
        set("jiali", 200);
        set("combat_exp", 2500000);
        set("score", 5000);

        set_skill("force", 220);
        set_skill("quanzhen-xinfa", 200);
        set_skill("xiantian-gong", 220);
        set_skill("staff", 200);
        set_skill("dagou-bang", 200);
        set_skill("unarmed", 220);
        set_skill("kongming-quan", 220);
        set_skill("strike", 200);
        set_skill("haotian-zhang", 200);
        set_skill("sword", 200);
        set_skill("quanzhen-jian", 200);
        set_skill("dodge", 200);
        set_skill("jinyan-gong", 200);
        set_skill("parry", 200);
        set_skill("jinguan-yusuo", 200);
        set_skill("literate", 180);
        set_skill("martial-cognize", 220);

        map_skill("force", "xiantian-gong");
        map_skill("unarmed", "kongming-quan");
        map_skill("sword", "quanzhen-jian");
        map_skill("staff", "dagou-bang");
        map_skill("parry", "jinguan-yusuo");
        map_skill("dodge", "jinyan-gong");
        map_skill("strike", "haotian-zhang");

        prepare_skill("unarmed", "kongming-quan");

        create_family("郭府", 2, "女婿");

        set("inquiry", ([
             "job"  : (: ask_job :),
             "工作" : (: ask_job :),
             "工具" : "你去物品房找老李要吧。",
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "unarmed.ruo" :),
                (: perform_action, "unarmed.kong" :),
                (: exert_function, "hup" :),
                (: exert_function, "shield" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }) );

        setup();
        carry_object("clone/misc/cloth")->wear();
}

void init()
{
        object ob;

        ::init();

        if (interactive(ob = this_player())
           && query("mark/guofu_ok", ob )
           && !query_temp("job_name", ob )
           && query("combat_exp", ob)<50000 )
	{
       		command("nod"+query("id", ob));
        	command("say 現在郭府內正缺人手，你可以找我領工作(" HIY
               		"ask yelv qi about 工作" NOR + CYN ")來做。" NOR);
	}
        add_action("do_task", "fuming");
}

string ask_job()
{
        object me, ob;
        string target;

        ob = this_player();
        me = this_object();

        target = names[random(sizeof(names))];

        if( query_temp("job_name", ob) )
		return "你不是已經領了工作嗎？還不快去做。";

        if( query("combat_exp", ob) >= 100000 )
             	return "你功夫已經足夠闖蕩江湖，這裏沒有什麼適合你的工作了。";

        if( query("mark/guofu_out", ob) )
             	return "你不是已經外出闖蕩了嗎，怎麼又回來了？";

        set_temp("job_name", target, ob);
        //ob->apply_condition("wuguan_job", random(3) + 4);
        return "…嗯…你先到物品房領工具，然後去後院「" HIY + target + NOR
               + CYN "」吧。\n" NOR;
}

int do_task(string arg)
{
        object ob, me, obj;
        int exp, pot;

        ob = this_player();
        me = this_object();
        exp = 25 + random(10);
        pot = 6 + random(6);

/*
        if (! arg || arg != "ok")
		return 0;
*/

        if( !query_temp("job_name", ob) )
		return notify_fail(CYN "耶律齊皺眉道：我沒給你工作，怎"
                                   "麼跑來覆命了？\n" NOR);

        if( !(query_temp("mark/劈完了", ob )
            || query_temp("mark/澆完了", ob )
            || query_temp("mark/鋤完了", ob )
            || query_temp("mark/鋸完了", ob )
            || query_temp("mark/掃完了", ob )
            || query_temp("mark/挑完了", ob)) )
                return notify_fail(CYN "耶律齊皺眉道：我讓你乾的事都幹"
                                   "完了嗎？\n" NOR);

        if (interactive(ob)
        && (int)ob->query_condition("wuguan_job"))
	{
              command("hmm"+query("id", ob));
              return notify_fail(CYN "耶律齊皺眉道：怎麼這麼快，是不是"
                                 "沒做完啊，吩咐你回來了嗎？\n" NOR);
        }

        if( !query_temp("mark/還了", ob) )
		return notify_fail(CYN "耶律齊道：…嗯…你還是先把工具"
                                   "還了""再説吧（將工具還給武修文 give 工具ID to wu xiuwen )。\n" NOR);

        command("smile"+query("id", ob));
        command("say 幹得不錯，這是給你的獎賞。");

        obj = new("/clone/money/silver");
        obj->set_amount(1 + random(2));
        obj->move(me, 1);
        command("give "+query("id", ob)+"silver");

        if( query("potential", ob)>ob->query_potential_limit() )
		pot = 1;

        addn("combat_exp", exp, ob);
        ob->improve_potential(pot);

        tell_object(ob, HIC "你獲得了" + chinese_number(exp) + "點"
                        "經驗和" + chinese_number(pot) + "點潛能。"
                        "\n" NOR);
        delete_temp("job_name", ob);
        delete_temp("mark", ob);
        addn("mark/guofu_job", 1, ob);
        return 1;
}

void unconcious()
{
        die();
}
