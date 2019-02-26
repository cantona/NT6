// european.c 西洋人

#include <ansi.h>

inherit CHALLENGER;

void create()
{
        set_name("西洋人", ({ "european" }));
        set("long", "一個西洋人。\n");
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
        set_skill("xiyang-neigong", 1);
        set_skill("dodge", 1);
        set_skill("xiyang-boji", 1);
        set_skill("parry", 1);
        set_skill("xiyang-jian", 1);
        set_skill("sword", 1);

        map_skill("sword", "xiyang-jian");
        map_skill("force", "xiyang-neigong");
        map_skill("dodge", "xiyang-boji");
        map_skill("parry", "xiyang-jian");

        set("rank_info/rude", "紅毛鬼");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
                (: perform_action, "sword.ci" :),
                (: perform_action, "sword.lian" :),
        }));

        setup();

        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/clone/weapon/xiyang-sword")->wield();
}

string challenge()
{
        set("opinion/msg", ({
                (random(2) ? "此人來自據説是比俄羅斯的莫斯科還要遙遠的西方。"
                           : "這是西洋武士，和我們中土人大不一樣。"),
                (random(2) ? "是啊，遙遠的地方，武技也是頗為奇特。"
                           : "嗯，西洋劍術適宜刺擊，不過並不善於劈砍。"),
                (random(2) ? "從如此遙遠的地方趕來，也真是夠難為他的了！"
                           : "西洋劍術固然注重實戰效果，不過仍然算不得是上乘劍術。"),
        }));

        command(random(2) ? "haha" : "killair");
        switch (random(2))
        {
        case 0:
                return "我來自" + query("nation") + "，聽説你們中原"
                        "武術高明，特地前來切磋切磋！";

        default:
                return "我是" + query("nation") + "的" + name() + "，你們中"
                       "原有沒有人願意和我比試一下武藝？";
        }
}

void unconcious()
{
        command("chat 啊！怎麼……怎麼這麼厲害？");
        die();
}

void competition_with(object ob)
{
        command("say 好吧！我們就分個高低看看！\n");
        ::competition_with(ob);
}

void lost()
{
        string *ob_list = ({
                "/clone/fam/etc/prize1",
                "/clone/fam/etc/prize3",
                "/clone/fam/etc/prize4",
                "/clone/fam/etc/prize5",
        });
        object ob;

        ob = new(ob_list[random(sizeof(ob_list))]);
        message_vision(HIY"$N"HIY"身子一退，掉下一"+query("unit", ob)+
                       ob->name() + HIY "。\n\n" NOR, this_object());

        ob->move(environment());
        ::lost();
}
