// japanese.c 日本鬼子

inherit CHALLENGER;

string *ob_list = ({
                "/clone/fam/gift/str2",
                "/clone/fam/gift/int2",
                "/clone/fam/gift/con2",
                "/clone/fam/gift/dex2",
                "/clone/fam/item/zijin",
                "/clone/fam/item/wujin",
});

void create()
{
        object ob;

        set_name("日本鬼子", ({ "japanese" }));
        set("long", "日本鬼子。\n");
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
        set_skill("fushang-neigong", 1);
        set_skill("dodge", 1);
        set_skill("renshu", 1);
        set_skill("parry", 1);
        set_skill("dongyang-dao", 1);
        set_skill("blade", 1);

        map_skill("blade", "dongyang-dao");
        map_skill("force", "fushang-neigong");
        map_skill("dodge", "renshu");
        map_skill("parry", "dongyang-dao");

        set("rank_info/rude", "鬼子");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
                (: perform_action, "blade.luan" :),
                (: perform_action, "blade.zhan" :),
        }));

        setup();

        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/clone/weapon/jpn-dao")->wield();

        ob = new(ob_list[random(sizeof(ob_list))]);
        ob->move(this_object());
}

string challenge()
{
        set("opinion/msg", ({
                (random(2) ? "此人來自東洋扶桑，據說那裡的東洋刀法極其怪異。"
                           : "東洋扶桑遠在東海之外，那裡的武士擅長使用窄刃長刀。"),
                (random(2) ? "是啊，東洋忍術也是詭秘得很。"
                           : "沒錯，不過東洋刀造型奇特，配合忍術還是頗有威力。"),
                (random(2) ? "哼！此人氣燄如此囂張，實為習武者大忌！"
                           : "此人可謂鼠目寸光，須知武道無窮，一絲也馬虎不得！"),
        }));

        command(random(2) ? "haha" : "heng");
        switch (random(3))
        {
        case 0:
                return "我！大和武士" + name() + "，來向你們中原"
                        "武人挑戰！誰敢出來迎戰？";

        case 1:
                return "我就是東洋扶桑國的" + name() + "，你們中"
                        "原有沒有人是我的對手？";

        default:
                return "我" + name() + "代表大和武士來向你們挑戰"
                        "，有種的就給我滾出來！";
        }
}

void unconcious()
{
        command("chat 八格呀路！");
        die();
}

void competition_with(object ob)
{
        command("say 八格呀路，你死去吧！\n");
        ::competition_with(ob);
        kill_ob(ob);
}