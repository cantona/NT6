#include <ansi.h>
inherit NPC;

#define HEILONG    "/clone/lonely/heilongbian"
#define LING       "/clone/lonely/item/tongjiling"

void create()
{
        object ob;
        set_name("史鬆", ({ "shi song", "shi", "song" }));
        set("gender", "男性");
        set("long", "這是一個精壯漢子，軍官模樣，腰間圍一條長鞭。\n");
        set("nickname", WHT "黑龍鞭" NOR);
        set("title", "巡捕首領");
        set("age", 35);
        set("str", 25);
        set("dex", 20);
        set("max_qi", 500);
        set("max_jing", 300);
        set("neili", 800);
        set("max_neili", 800);
        set("jiali", 50);
        set("combat_exp", 300000);
        set("shen_type", -1);
        set("attitude", "peaceful");

        set_skill("force", 120);
        set_skill("bagua-xinfa", 120);
        set_skill("whip", 120);
        set_skill("yunlong-bian", 120);
        set_skill("cuff", 100);
        set_skill("bagua-quan", 100);
        set_skill("dodge", 100);
        set_skill("feiyan-zoubi", 100);
        set_skill("parry", 100);
        set_skill("literate", 80);
        set_skill("martial-cognize", 80);

        map_skill("force", "bagua-xinfa");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("cuff", "bagua-quan");
        map_skill("whip", "yunlong-bian");
        map_skill("parry", "yunlong-bian");

        prepare_skill("cuff", "bagua-quan");

        set_temp("apply/attack", 30);
        set_temp("apply/defense", 30);
        set_temp("apply/armor", 100);
        set_temp("apply/damage", 50);
        set_temp("apply/unarmed_damage", 50);

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "cuff.gua" :),
                (: perform_action, "whip.chan" :),
                (: exert_function, "recover" :),
        }));

        set("inquiry", ([
                "茅十八" : "誰幫我幹掉這惡賊，我一定保他前程似錦。",
                "纏字訣" : "我總得留兩手吧？",
        ]));

        set("chat_chance", 1);
        set("chat_msg", ({
                CYN "史鬆説道：在下黑龍鞭史鬆，奉鰲少保將令，擒拿天地會反賊。\n" NOR,
                CYN "史鬆説道：鰲少保天生神勇，曾在北京街上一拳打死一頭瘋牛。\n" NOR,
        }));

        setup();

        if (clonep())
        {
                ob = find_object(HEILONG);
                if (! ob) ob = load_object(HEILONG);
                if (! environment(ob))
                {
                        ob->move(this_object());
                        ob->wield();
                } else
                {
                        ob = new("/clone/weapon/changbian");
                        ob->move(this_object());
                        ob->wield();
                }
        }

        carry_object("/d/beijing/npc/obj/guanfu3")->wear();
        add_money("silver", 20);
}

void init()
{
        object me, ob;
        ::init();

        ob = this_player();
        me = this_object();

        if( query("id", ob) == "mao shiba" )
        {
                command("say 茅十八你這個反賊，今天終於逮到你了！");
                me->set_leader(ob);
                remove_call_out("kill_ob");
                call_out("kill_ob", 1, ob); 
        }

        if (interactive(ob)
	 && !query("no_fight", environment(ob) )
            && (query("combat_exp", ob)>150000 )
            && (query("family/family_name", ob) == "天地會") )
        {
                command("say 你這個天地會反賊，納命來吧！");
                me->set_leader(ob);
                remove_call_out("kill_ob");
                call_out("kill_ob", 1, ob); 
        }
}

int accept_object(object me, object ob)
{
        int exp, pot, sc;

        exp = 500 + random(300);
        pot = 100 + random(50);
        sc = random(10);

        if (base_name(ob) != LING)
        {
                command("say 你給我這種東西幹什麼？");
                return 0;
        }

        if( query("combat_exp", me)>10000 )
        {
                if( !query("skybook/luding/shi", me) )
                {
                        addn("combat_exp", exp, me);
                        addn("potential", pot, me);
                        addn("score", sc, me);
                        tell_object(me, HIW "\n\n你成功的幫助史鬆弄到了通緝令！\n" NOR +
                                        HIC "通過這次的歷練，你獲得了" + chinese_number(exp) +
                                        "點經驗、" + chinese_number(pot) + "點潛能以及" +
                                        chinese_number(sc) + "點江湖閲歷。\n\n" NOR);
                        set("skybook/luding/shi", 1, me);
                        set("can_learn/yunlong-bian/shi", 1, me);
                }
                command("haha");
                command("say 你把那姓茅的大盜幹掉了？這可真是謝謝你了。");
                command("say 我這有一套雲龍鞭法，如果你願意，我倒是可以傳你兩手。\n");
        } else
        {
                command("nod"+query("id", me));
                command("say 不錯，不錯。可惜你江湖經驗太淺，要不還可教你點東西。");
        }
        destruct(ob);
        return 1;
}

int recognize_apprentice(object me, string skill)
{
        if( !query("can_learn/yunlong-bian/shi", me) )
        {
                command("say 奶奶的，你找死麼？");
                return -1;
        }

        if (skill != "yunlong-bian")
        {
                command("say 我拿手的就只有這套鞭法，你不學就算了。");
                return -1;
        }
        return 1;
}

int accept_fight(object me)
{
        command("say 沒興趣。");
        return 0;
}

int accept_hit(object me)
{
        command("say 他奶奶的，連我你都敢惹？");
        kill_ob(me);
        return 1;
}
