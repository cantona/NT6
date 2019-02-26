// english.c 英國人

#include <ansi.h>

inherit CHALLENGER;

void create()
{
        set_name("英國人", ({ "english" }));
        set("long", "一個英國人。\n");
        set("gender", "男性");
        set("age", 20);
        set("str", 40);
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
        set_skill("qishi-ji", 1);
        set_skill("club", 1);

        map_skill("club", "qishi-ji");
        map_skill("force", "xiyang-neigong");
        map_skill("dodge", "xiyang-boji");
        map_skill("parry", "qishi-ji");

        set("rank_info/rude", "紅毛鬼");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
                (: perform_action, "club.chong" :),
                (: perform_action, "club.juan" :),
        }));

        setup();

        carry_object("/clone/cloth/yinjia")->wear();
        carry_object("/clone/weapon/qishiji")->wield();
}

string challenge()
{
        set("opinion/msg", ({
                (random(2) ? "此人佩帶着聖騎士勛章，想必是由英吉利女皇親自頒發。"
                           : "此人身着重鎧，手持長戟，想必應是英吉利的皇家騎士。"),
                (random(2) ? "不錯，英吉利皇家騎士團向來以勇猛著稱，善於衝鋒陷陣。"
                           : "傳説他們那裏有個叫「龍槍」的勇士，其槍術已稱得上是出神入化。"),
                (random(2) ? "從如此遙遠的地方遠度而來，也真是夠難為他的了！"
                           : "嗯，長矛雖利於衝刺，但是變化略少，近身作戰更見其弊。"),
        }));

        command(random(2) ? "haha" : "killair");
        switch (random(2))
        {
        case 0:
                return "我來自" + query("nation") + "，聽説你們中原"
                       "武術高明，特地前來切磋切磋！";

        default:
                return "我是" + query("nation") + "皇家騎士團的" + name() + "，中"
                       "原有誰願意和我一較高低？";
        }
}

void unconcious()
{
        command("chat 啊！怎麼……怎麼這麼厲害？");
        die();
}

void competition_with(object ob)
{
        command("say 太好了，我們就分個高低看看！\n");
        ::competition_with(ob);
}

void lost()
{
        string *ob_list = ({
                "/clone/fam/etc/prize1",
                "/clone/fam/etc/prize2",
                "/clone/fam/etc/prize3",
                "/clone/fam/etc/prize4",
        });
        object ob;

        ob = new(ob_list[random(sizeof(ob_list))]);
        message_vision(HIY"$N"HIY"身子一退，掉下一"+query("unit", ob)+
                       ob->name() + HIY "。\n\n" NOR, this_object());

        ob->move(environment());
        ::lost();
}