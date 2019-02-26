#include <ansi.h>
inherit NPC;

#define HEILONG    "/clone/lonely/heilongbian"
#define LING       "/clone/lonely/item/tongjiling"

void create()
{
        object ob;
        set_name("茅十八", ({ "mao shiba", "mao", "shiba" }));
        set("long", @LONG
他虯髯如亂草，滿臉血污，好像曾受過很重的
傷，可以看得見他左腿上血跡未乾。但他雙目
炯炯，卻又有着説不出的威風。
LONG);
        set("title", "官府通緝要犯");
        set("gender", "男性");
        set("age", 30);
        set("str", 25);
        set("dex", 16);
        set("max_qi", 500);
        set("max_jing", 300);
        set("neili", 800);
        set("max_neili", 800);
        set("jiali", 50);
        set("combat_exp", 300000);
        set("shen_type", 1);
        set("attitude", "peaceful");

        set_skill("force", 100);
        set_skill("bagua-xinfa", 100);
        set_skill("blade", 120);
        set_skill("wuhu-duanmendao", 120);
        set_skill("cuff", 120);
        set_skill("hua-quan", 120);
        set_skill("dodge", 100);
        set_skill("feiyan-zoubi", 100);
        set_skill("parry", 100);
        set_skill("literate", 60);
        set_skill("martial-cognize", 80);

        map_skill("blade", "wuhu-duanmendao");
        map_skill("parry", "wuhu-duanmendao");
        map_skill("force", "bagua-xinfa");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("cuff", "hua-quan");

        prepare_skill("cuff", "hua-quan");

        set_temp("apply/attack", 30);
        set_temp("apply/defense", 30);
        set_temp("apply/armor", 100);
        set_temp("apply/damage", 50);
        set_temp("apply/unarmed_damage", 50);

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "cuff.juan" :),
                (: perform_action, "blade.duan" :),
                (: exert_function, "recover" :),
        }));

        set("inquiry", ([
                "史鬆"   : "誰殺了史鬆這奸賊，我可以幫他提高江湖威望。",
                "斷字訣" : "我總得留兩手吧？",
        ]));

        set("chat_chance", 2);
        set("chat_msg", ({
                CYN "茅十八説道: 他奶奶的，我就不信鰲拜有這等厲害，我正要上北京去鬥他一鬥。\n" NOR,
                CYN "茅十八歎道: 我這五虎斷門刀法對付鹽梟可是綽綽有餘，不知對付鰲拜行不行。\n" NOR,
                CYN "茅十八説道: 他奶奶的，要誰幫我殺了史鬆，兄弟我就謝謝了。\n" NOR,
                CYN "茅十八朗聲説道：江湖有言為人不識陳近南，就稱英雄也枉然。\n" NOR,
                (: random_move :)
        }) );
        setup();
        if (clonep())
        {
                ob = find_object(LING);
                if (! ob) ob = load_object(LING);
                if (! environment(ob))
                {
                        ob->move(this_object());
                        set_temp("handing", ob);
                }
        }
        carry_object("/d/city/obj/gangdao")->wield();
        carry_object("/clone/misc/cloth")->wear();
}

int accept_object(object me, object ob)
{
        int exp, pot, sc;

        exp = 500 + random(300);
        pot = 100 + random(50);
        sc = random(10);

        if (base_name(ob) != HEILONG)
        {
                command("say 你給我這種東西幹什麼？");
                return 0;
        }

        if( query("combat_exp", me)>10000 )
        {
        	if( !query("skybook/luding/mao", me) )
        	{
                addn("combat_exp", exp, 	me);
                addn("potential", pot, 	me);
                addn("score", sc, 	me);
                	tell_object(me, HIW "\n\n你成功的幫助茅十八弄到了黑龍鞭！\n" NOR +
                                        HIC "通過這次的歷練，你獲得了" + chinese_number(exp) +
                                        "點經驗、" + chinese_number(pot) + "點潛能以及" +
                                	chinese_number(sc) + "點江湖閲歷。\n\n" NOR);
                set("skybook/luding/mao", 1, 	me);
                set("can_learn/wuhu-duanmendao/mao", 1, 	me);
		}
                command("haha");
                command("say 多謝，多謝。那個狗腿子俺早就想除去了。");
                command("say 俺這有一套五虎斷門刀，你如果有意，倒是可以看看。\n");
        } else
	{
                command("pat"+query("id", me));
                command("say 要不是你的江湖經驗太淺，俺真想教你點東西。");
	}
        destruct(ob);
        return 1;
}

int recognize_apprentice(object me, string skill)
{
        if( !query("can_learn/wuhu-duanmendao/mao", me) )
        {
                command("say 幹嘛？沒拜師就想向俺學東西？");
                return -1;
        }

        if (skill != "wuhu-duanmendao")
        {
                command("say 俺就只有這一套刀法拿得出手。");
                return -1;
        }
        return 1;
}