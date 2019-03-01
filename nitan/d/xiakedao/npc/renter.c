// renter.c 弟子

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

#define GUARD_CMD       "/cmds/std/guard"

mixed ask_rent();
mixed try_to_hire(object me, object ob);
void hire(object helper, object owner);
void create_all_helper();

mapping *info = ({
// level 1
([      "life"  : 500,
        "neili" : 800,
        "cost"  : 10,
]),
// level 2
([      "life"  : 800,
        "neili" : 1000,
        "cost"  : 20,
]),
// level 3
([      "life"  : 1000,
        "neili" : 1200,
        "cost"  : 25,
]),
// level 4
([      "life"  : 1200,
        "neili" : 1600,
        "cost"  : 30,
]),
// level 5
([      "life"  : 1500,
        "neili" : 2000,
        "cost"  : 35,
]),
// level 6
([      "life"  : 2000,
        "neili" : 2500,
        "cost"  : 40,
]),
// level 7
([      "life"  : 2500,
        "neili" : 3000,
        "cost"  : 50,
]),
// level 8
([      "life"  : 3000,
        "neili" : 3500,
        "cost"  : 60,
]),
// level 9
([      "life"  : 3500,
        "neili" : 4000,
        "cost"  : 80,
]),
// level 10
([      "life"  : 4000,
        "neili" : 5000,
        "cost"  : 100,
]),
// level 11
([      "life"  : 4500,
        "neili" : 6000,
        "cost"  : 150,
]),
// level 12
([      "life"  : 5000,
        "neili" : 7000,
        "cost"  : 200,
]),
// level 13
([      "life"  : 6000,
        "neili" : 8000,
        "cost"  : 300,
]),
// level 14
([      "life"  : 7000,
        "neili" : 9000,
        "cost"  : 500,
]),
// level 15
([      "life"  : 8000,
        "neili" : 9999,
        "cost"  : 700,
]),
});

void create()
{
        set_name("黃衣使者", ({ "xiake dizi", "dizi", "renter" }));
        set("long", "他身著黃衫，表情鬱鬱，似乎身有武功。\n");

        set("gender", "男性");
        set("age", 25);
        set("shen_type", 1);
        set("attitude", "peaceful");

        set("inquiry", ([
                "同門" : (: ask_rent :), 
                "師兄" : (: ask_rent :), 
                "rent" : (: ask_rent :), 
        ]));

        create_family("俠客島", 0, "弟子");
        setup();
        carry_object("/clone/misc/cloth")->wear();

        call_out("create_all_helper", 0);
}

mixed ask_rent()
{
        object me;
        object *obs;
        string msg;
        string fam;
        int i;

        me = this_player();
        if( arrayp(obs=query_temp("hire", me)) )
        {
                obs -= ({ 0 });
                fam = query("family/family_name");
                obs=filter_array(obs,(:query("family/family_name", $1) == $(fam):));
                if (sizeof(obs))
                        return "現在不是有" + obs[0]->name() + "和你在一起麼？你還想怎麼樣？";
        }

        obs = query_temp("helpers");
        if (! arrayp(obs) || (obs = obs - ({ 0 }),sizeof(obs) < 1))
                return "我的師兄弟都走啦，你還是等兩天再來吧。";

        msg = "$N笑了笑，道：“現在我身邊的師兄弟有這麼幾個，你看看吧。”\n";
        for (i = 0; i < sizeof(obs); i++)
                msg += sprintf("%2d. %-27s  等級：%d\n",
                               i + 1,
                               obs[i]->name(1)+"("+query("id", obs[i])+")",
                               query("npc_level", obs[i]));
        switch (random(5))
        {
        case 0:
                msg += "$N看了看$n，道：“你想找誰幫你的忙，不妨和我說說。”\n";
                break;
        case 1:
                msg += "$N對$n道：“我的師兄弟水平各有高下，你找一個派得上用場的吧！”\n";
                break;
        case 2:
                msg += "$N微微一笑，對$n道：“你覺得誰合適？”\n";
                break;
        }
        message_vision(msg, this_object(), me);
        return 1;
}

int accept_object(object me, object ob)
{
        object helper;
        object *obs;
        int cost;
        int n;

        if( !query("money_id", ob) )
                return 0;

        if( !objectp(helper=query_temp("pending/rent/helper", me)) )
        {
                command("say 你給我錢幹什麼？讚助我們俠客島麼？");
                return 0;
        }

        cost=query_temp("pending/rent/cost", me);
        n = ob->value() / 10000;
        if (n < cost)
        {
                command("say 我們這裡可不能打折，你還是免了吧！");
                if( n*2 >= cost && query("special_skill/treat", me) )
                        message_vision("$N跪在地上，抱著$n，哭喊道：“你就"
                                       "可憐可憐我這窮鬼吧！”\n$n看了，頗"
                                       "為無奈，搖搖頭，嘆口氣道：“好吧好"
                                       "吧，算了。”\n", me, this_object());
                else
                        return 0;
        }

        message_vision("$n接過$N遞過來的" + ob->name() +
                       "，記在帳上，有道：“等會兒！”\n",
                       me, this_object());
        destruct(ob);
        message_vision("$N高聲喊道：“" + helper->name() +
                       "！快來，快來啊，送錢的上門了！”\n", this_object());
        helper->move(environment());
        message_vision("$n走了過來，看了看$N。\n", me, helper);
        command("say 好啦，" + helper->name() + "，就是這位" +
                RANK_D->query_respect(me) + "，你一同去吧。");
        message_vision("$n點點頭，和$N寒暄兩句，跟在了$P的身後。\n",
                       me, helper);

        // 初始化雇傭的人
        // 設置雇傭開始的時間，主人，去掉目前的正在雇傭的狀
        // 態，跟隨主人，開始並維持心跳。
        set_temp("help_time", time(), helper);
        set_temp("owner", me, helper);
        set_temp("owner_name", me->name(1), helper);
        set_temp("owner_id",query("id",  me), helper);
        delete_temp("renter", helper);
        helper->set_leader(me);
        helper->keep_heart_beat();

        // 設置主人的信息
        obs=query_temp("hire", me);
        if (arrayp(obs))
        {
                obs -= ({ 0 });
                obs += ({ helper });
        } else
                obs = ({ helper });
        set_temp("hire", obs, me);

        GUARD_CMD->main(helper, me);
        delete_temp("pending/rent", me);

        obs = query_temp("helpers");

        if (! arrayp(obs)) obs = ({ }); else obs -= ({ 0 });

        obs -= ({ helper });

        set_temp("helpers", obs);

        CHANNEL_D->do_channel(this_object(), "rumor",
                me->name(1) + "在南海邀請到了一名俠客島弟子。");
        return -1;
}

mixed accept_ask(object me, string topic)
{
        object ob;
        object *obs;

        obs = query_temp("helpers");
        if (! arrayp(obs)) obs = ({ }); else obs -= ({ 0 });

        foreach (ob in obs)
                if (ob->id(topic) || ob->name(1) == topic)
                        return try_to_hire(me, ob);

        message_vision(CYN "$N" CYN "看了看$n" CYN "，疑問道"
                       "：“你想幹什麼？是要找我的" HIY "同門"
                       NOR CYN "師兄弟麼？”\n" NOR,
                       this_object(), me);
        return 1;
}

mixed try_to_hire(object me, object ob)
{
        object *obs;
        string fam;
        int cost;

        if( query("weiwang", me)<1000 )
                return "你這點名頭也能使喚人？算了吧！"; 

        if( query("score", me)<10000 )
                return "你江湖閱歷太淺，還是免了。"; 

        if( query("combat_exp", me)<50000 )
                return "你的武功太差，想支使誰呀？"; 

        if( query("combat/DPS", me)>30 )
                return "你這人，傷人太多，我們俠客島的弟子可不能助紂為虐。";

        if( query("combat/WPK", me)>30 )
                return "你這人呀！辣手無情，殺人無算，張兄李兄沒找你算帳就不錯了。";

        if( arrayp(obs=query_temp("hire", me)) )
        {
                obs -= ({ 0 });
                fam = query("family/family_name");
                obs=filter_array(obs,(:query("family/family_name", $1) == $(fam):));
                if (sizeof(obs))
                        return obs[0]->name() + "現在不是正和你在一起麼？還不夠啊？";
        }

        if( query("combat_exp", me)<query("combat_exp", ob)*2/3 )
                return "算了吧，" + ob->name() + "武功也強你太多，他可沒興趣幫你。";

        if( query("combat_exp", ob)*2<query("combat_exp", me) )
                return "哦？你武功這麼好，" + ob->name() + "恐怕幫不上你什麼忙吧。";

        cost = info[query("npc_level",ob) - 1]["cost"];
        message_vision("$N微微一笑，道：“好吧，不過你也得意"
                       "思意思啊，我們俠客島開銷也不小的。”\n"
                       "$N仔細考慮了一會兒，對$n道：“這樣吧，就" +
                       chinese_number(cost) + "兩黃金吧。 ”\n",
                       this_object(), me);
        set_temp("pending/rent/cost", cost, me);
        set_temp("pending/rent/helper", ob, me);
        return 1;
}

void create_all_helper()
{
        object *obs;
        int *lvls = ({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });
        int lvl;
        object ob;
        string startroom;

        if (! stringp(startroom = query("startroom")) ||
            environment() != find_object(startroom))
                return;

        obs = query_temp("helpers");
        if (! arrayp(obs)) obs = ({ }); else obs -= ({ 0 });
        for (int i=0; i<sizeof(obs); i++)
                lvls -= ({ query("npc_level", obs[i]) });
        while (sizeof(obs) < 15)
        {
                lvl = lvls[random(sizeof(lvls))];
                ob = new(CLASS_D("generate") + "/helper");
                // initialize the npc
                set("npc_level", lvl, ob);
                set_temp("renter", this_object(), ob);
                NPC_D->init_npc_skill(ob, lvl);
                ob->init_man(info[lvl - 1]);
                lvls -= ({ lvl });
                obs += ({ ob });
                ob->create_family("俠客島", 0, "弟子");
        }

        obs=sort_array(obs,(:query("npc_level", $1)-query("npc_level", $2):));
        set_temp("helpers", obs);
}

void remove()
{
        object *obs;
        object ob;

        obs = query_temp("helpers");
        if (! arrayp(obs)) return;
        obs -= ({ 0 });

        // 析構所有的師兄弟
        foreach (ob in obs) ob->destruct_by_owner();
}

void move_or_destruct()
{
        remove();
}

void reset()
{
        create_all_helper();
}
