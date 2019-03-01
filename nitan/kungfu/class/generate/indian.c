// indian.c 印度高手

#include <ansi.h>

inherit CHALLENGER;

void create()
{
        set_name("天竺人", ({ "indian" }));
        set("long", "一個天竺人，長得非常瘦小。\n");
        set("gender", "男性");
        set("age", 20);
        set("str", 20);
        set("int", 20);
        set("con", 20);
        set("dex", 20);

        // the follow 5 setting has no use
        set("max_qi", 100);
        set("max_jing", 100);
        set("neili", 100);
        set("max_neili", 100);
        set("jiali", 100);
        set("shen", -1000);

        set("combat_exp", 3000000);
        set("scale", 100);

        set_skill("force", 1);
        set_skill("yujiashu", 1);
        set_skill("dodge", 1);
        set_skill("yujiashu", 1);
        set_skill("parry", 1);
        set_skill("finger", 1);
        set_skill("nianhua-zhi", 1);
        set_skill("strike", 1);
        set_skill("sanhua-zhang", 1);

        map_skill("finger", "nianhua-zhi");
        map_skill("strike", "sanhua-zhang");
        map_skill("force", "yujiashu");
        map_skill("dodge", "yujiashu");
        map_skill("parry", "nianhua-zhi");

        prepare_skill("strike", "sanhua-zhang");
        prepare_skill("finger", "nianhua-zhi");

        set("class", "bonze");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
                (: perform_action, "finger.fuxue" :),
                (: perform_action, "strike.sanhua" :),
        }));

        set_temp("apply/strike", 50);
        set_temp("apply/finger", 50);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/parry", 50);
        set_temp("apply/dodge", 50);
        set_temp("apply/force", 50);

        set("chat_lost", "中原武學真是名不虛傳。");
        set("chat_win", "嗯…看來這個人武功還沒有學到家，還是改日再來吧。");

        setup();

        carry_object("/clone/cloth/seng-cloth")->wear();
}

string challenge()
{
        set("opinion/msg", ({
                (random(2) ? "此人來頭不小，當年達摩祖師便是來自天竺。"
                           : "這是天竺高手，和少林派乃是同源。"),
                (random(2) ? "去天竺路途遙遠，十分兇險，來到中原大是不易。"
                           : "天竺瑜珈術奧妙無窮，少林絕學易筋經便是由此化來。"),
                (random(2) ? "當初達摩祖師來到中原，帶來了十二項絕技，實在是非同小可。"
                           : "少林絕技博大精深，天竺武學實在不可小視啊！"),
        }));

        command(random(2) ? "bow" : "buddhi " + query("id"));
        switch (random(2))
        {
        case 0:
                return "我乃" + query("nation") + "人士，不遠萬裡"
                        "來到中原，特地向諸位高手請教武學。";

        default:
                return "我是" + query("nation") + "的" + name() + "，還"
                       "望中原諸位武林高手賜教。";
        }
}

void unconcious()
{
}

void competition_with(object ob)
{
        command("say 好吧！我們就比劃比劃，勿傷和氣。\n");
        ::competition_with(ob);
}

void lost()
{
        string *ob_list = ({
                "/clone/fam/pill/puti4",
                "/clone/fam/pill/sheli4",
                "/clone/fam/gift/str2",
                "/clone/fam/gift/int2",
                "/clone/fam/gift/con2",
                "/clone/fam/gift/dex2",
        });

        object ob;
        string un;

        ob = new(ob_list[random(sizeof(ob_list))]);

        if( query("base_unit", ob) )
               un=query("base_unit", ob);
        else
               un=query("unit", ob);

        message_vision(CYN "$N" CYN "雙手合十，嘆道：中原武學真是博大"
                       "精深，這" + un + ob->name() + CYN "就算是我求"
                       "學的贈禮吧。\n" NOR, this_object());

        ob->move(this_object(), 1);
        command("give"+query("id", ob)+"to"+
                query("id", query_competitor()));
        ::lost();
}
