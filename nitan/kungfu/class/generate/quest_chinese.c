// chan_cler 中國挑戰者

inherit NPC;

private void from_wudang();
private void from_shaolin();
private void from_huashan();
private void from_ouyang();
private void from_gaibang();
void random_move();
void destruct_me();
int is_stay_in_room() { return 1; }

function *init_family = ({ (: from_wudang :), (: from_shaolin :), (: from_huashan :),
                           (: from_ouyang :), (: from_gaibang :) });

void create()
{
        set_name("中國人", ({ "chinese" }));
        set("long", "一個人。\n");
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

        set("combat_exp", 3000000);

        set_skill("force", 1);
        set_skill("dodge", 1);
        set_skill("parry", 1);

        set("chat_chance", 30);
        set("chat_msg", ({ (: random_move :) }));
        set("scale", 100);
        set_temp("born_time", time());
        add_money("silver",50);
        keep_heart_beat();
        setup();

        evaluate(init_family[random(sizeof(init_family))]);
}

private void from_wudang()
{
        set("scale", 200);
        set("from", ({
                "據説此人出自武當，是武當派的高手，然而修武不修德，可惜啊可惜。",
                "聽聞此人本是武當山下一農夫，耳瀆目染，居然練就成非凡武功。",
                "據説此人乃武當棄徒，當年犯了殺戒逃至東洋，不想今日返回中原！",
        }));

        set_skill("taiji-shengong", 1);
        set_skill("parry",1);
        set_skill("tiyunzong", 1);
        set_skill("sword", 1);
        set_skill("taiji-jian", 1);
        set_skill("hand", 1);
        set_skill("paiyun-shou", 1);
        set_skill("unarmed", 1);
        set_skill("taiji-quan", 1);

        map_skill("force", "taiji-shengong");
        map_skill("parry","taiji-jian");
        map_skill("dodge", "tiyunzong");
        map_skill("sword", "taiji-jian");
        map_skill("hand", "paiyun-shou");
        map_skill("unarmed", "taiji-quan");

        prepare_skill("hand", "paiyun-shou");
        prepare_skill("unarmed", "taiji-quan");

        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: perform_action, "sword.lian" :),
                (: perform_action, "unarmed.zhen" :),
                (: exert_function, "recover" :),
        }) );

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/wudang/obj/greyrobe")->wear();
}

private void from_shaolin()
{
        set("scale", 150);
        set("from", ({
                "據説此人出自少林，是少林的俗家高手，可卻沒有半點慈悲之心，唉！",
                "聽聞此人偷師於少林，練就了一身超凡脱俗的本領。",
                "據説此人乃少林的火工頭陀，偷學武藝後被發現，竟然打死"
                + "達摩院長老出逃西域，想不到今日返回中原！",
                "據説此人當年犯了少林的戒律，被迫離寺，想不到隱居多年"
                + "以後居然重出江湖。"
        }));

        set_skill("hunyuan-yiqi", 1);
        set_skill("parry",1);
        set_skill("shaolin-shenfa", 1);
        set_skill("sword", 1);
        set_skill("damo-jian", 1);
        set_skill("finger", 1);
        set_skill("nianhua-zhi", 1);
        set_skill("strike", 1);
        set_skill("sanhua-zhang", 1);

        map_skill("force", "hunyuan-yiqi");
        map_skill("parry","damo-jian");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("sword", "damo-jian");
        map_skill("finger", "nianhua-zhi");
        map_skill("strike", "sanhua-zhang");

        prepare_skill("finger", "nianhua-zhi");
        prepare_skill("strike", "sanhua-zhang");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "sword.sanjue" :),
                (: perform_action, "strike.san" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
                (: exert_function, "recover" :),
        }) );

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

private void from_huashan()
{
        set("scale", 130);
        set("from", ({
                "據説此人出自華山，無惡不作，後來行跡忽然不見，想不到今日又出頭。",
                "聽聞此人本是華山長老，因劍氣之爭遠投異地，不知何故返回中原！",
                "據説此人本是別派卧底到華山去的，偷學本領以後沒回本派"
                + "反而覓地苦修，今日終於得出江湖。",
        }));

        set_skill("zixia-shengong", 1);
        set_skill("parry",1);
        set_skill("feiyan-huixiang", 1);
        set_skill("sword", 1);
        set_skill("huashan-sword", 1);
        set_skill("cuff", 1);
        set_skill("poyu-quan", 1);
        set_skill("strike", 1);
        set_skill("hunyuan-zhang", 1);

        map_skill("force", "zixia-shengong");
        map_skill("dodge", "feiyan-huixiang");
        map_skill("parry","huashan-sword");
        map_skill("sword", "huashan-sword");
        map_skill("cuff", "poyu-quan");
        map_skill("strike", "hunyuan-zhang");

        prepare_skill("cuff", "poyu-quan");
        prepare_skill("strike", "hunyuan-zhang");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "sword.jianzhang" :),
                (: perform_action, "cuff.leidong" :),
                (: perform_action, "cuff.poshi" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
                (: exert_function, "recover" :),
        }) );

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

private void from_ouyang()
{
        set("scale", 130);
        set("from", ({
                "據説此人原是當今武林宗師歐陽鋒的兄長，不知何故失蹤，今"
                + "日居然又出現了。",
                "聽聞此人偷學了西域白駝山莊歐陽世家的武功，後來被歐陽"
                + "鋒發現打成重傷，此人帶傷而走，竟然活到今日，不可思議！",
        }));

        set_skill("hamagong", 1);
        set_skill("parry",1);
        set_skill("chanchu-bufa", 1);
        set_skill("staff", 1);
        set_skill("lingshe-zhangfa", 1);
        set_skill("cuff", 1);
        set_skill("lingshe-quan", 1);
        set_skill("finger", 1);
        set_skill("shedu-qiqiao", 1);

        map_skill("force", "hamagong");
        map_skill("parry", "lingshe-zhangfa");
        map_skill("dodge", "chanchu-bufa");
        map_skill("staff", "lingshe-zhangfa");
        map_skill("cuff", "lingshe-quan");
        map_skill("finger", "shedu-qiqiao");

        prepare_skill("cuff", "lingshe-quan");
        prepare_skill("finger", "shedu-qiqiao");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "staff.lingshe" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
                (: exert_function, "recover" :),
        }) );

        carry_object("/clone/weapon/gangzhang")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

private void from_gaibang()
{
        set("scale", 130);
        set("from", ({
                "據説此人原是丐幫長老，武功高絕，後因欺辱良家女子而被"
                + "逐出幫外，今日重現江湖比如又起血雨腥風。"
        }));

        set_skill("huntian-qigong", 1);
        set_skill("parry",1);
        set_skill("feiyan-zoubi", 1);
        set_skill("staff", 1);
        set_skill("dagou-bang", 1);
        set_skill("strike", 1);
        set_skill("dragon-strike", 1);

        map_skill("force", "huntian-qigong");
        map_skill("parry", "dagou-bang");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("staff", "dagou-bang");
        map_skill("strike", "dragon-strike");

        prepare_skill("strike", "dragon-strike");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
                (: exert_function, "recover" :),
        }) );

       carry_object("/clone/weapon/gangzhang")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

int accept_fight(object ob)
{
        command("say 很好！那我就不客氣了。");
        kill_ob(ob);
        return 1;
}

int accept_hit(object ob)
{
        command("say 哼！什麼人？");
        kill_ob(ob);
        return 1;
}

void random_move()
{
        if (time() - query_temp("born_time") > 600)
        {
                destruct_me();
                return;
        }
        GROUP_QUEST_D->random_move(this_object());
}

void destruct_me()
{
        message_vision("$N急急忙忙的走了。\n", this_object());
        destruct(this_object());
}
