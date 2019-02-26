#include <ansi.h>
inherit NPC;

void create()
{
        set_name("覺遠", ({ "jue yuan", "jue", "yuan" }));
        set("long", "一位衣着樸素、鬚髮花白的老僧。只見他正挑着一\n"
                    "對大鐵桶，比之尋常水桶大了兩倍有餘，那僧人頸\n"
                    "中、手上、腳上，更繞滿了粗大的鐵鏈，行走時鐵\n"
                    "鏈拖地，不停發出聲響。這對大鐵桶本身只怕便有\n"
                    "二百來斤，桶中裝滿了水，重量更是驚人。\n" );
        set("gender", "男性");
        set("attitude", "friendly");
        set("class", "bonze");

        set("age", 60);
        set("shen_type", 1);
        set("str", 32);
        set("int", 34);
        set("con", 31);
        set("dex", 30);
        set("max_qi", 8000);
        set("max_jing", 6000);
        set("neili", 9000);
        set("max_neili", 9000);
        set("jiali", 300);
        set("combat_exp", 5000000);

        set_skill("force", 380);
        set_skill("jiuyang-shengong", 400);
        set_skill("shaolin-jiuyang", 180);
        set_skill("wudang-jiuyang", 180);
        set_skill("emei-jiuyang", 180);
        set_skill("dodge", 220);
        set_skill("shaolin-shenfa", 220);
        set_skill("unarmed", 380);
        set_skill("parry", 260);
        set_skill("martial-cognize", 300);
        set_skill("buddhism", 200);
        set_skill("literate", 100);

        map_skill("force", "jiuyang-shengong");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("unarmed", "jiuyang-shengong");
        map_skill("parry", "jiuyang-shengong");

        prepare_skill("unarmed", "jiuyang-shengong");

        set_temp("apply/attack", 150);
        set_temp("apply/defense", 150);
        set_temp("apply/dodge", 150);
        set_temp("apply/damage", 200);
        set_temp("apply/unarmed_damage", 200);

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "unarmed.hun" :),
                (: perform_action, "unarmed.jiu" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
        }));

        create_family("少林派", 0, "打雜僧人"); 

        setup();

        carry_object("/d/shaolin/obj/xu-cloth")->wear();
}

void attempt_apprentice(object ob)
{
        message_vision(CYN "$N" CYN "搖了搖頭，對$n" CYN "説道：“貧僧乃帶"
                       "罪之身，豈能收徒。”\n" NOR, this_object(), ob);
}

void init()
{
        object me;

        me = this_player();

        if (! interactive(me))
                return;

        if (living(this_object()) && present("lengjia jing", me))
        {
                command("yi");
                command("say 這位施主，本派遺失的《楞伽經》怎會在你身上！");
                command("say 請這位施主行個方便，將經書還給貧僧。");
                return;
        }
}

int accept_object(object who, object ob)
{
        if( query("id", ob) == "lengjiajing" )
        {
                destruct(ob);
                if( query("can_learn/jiuyang-shengong/kunlun", who) )
                {
                        if( query("can_learn/jiuyang-shengong/shaolin", who) )
                        {
                                command("say 多謝，多謝。");
                                return 1;
                        } else
                        {
                                message_vision(CYN "$N" CYN "滿臉歡喜的對$n" CYN "道"
                                               "：施主宅心仁厚，日後必有大成，貧僧多"
                                               "謝了。\n" NOR, this_object(), who);
                                command("sigh");
                                command("say 無數好事之人貪圖於此，乃是為了這本經書裏"
                                        "所記載的一門武功。");
                                command("say 施主為人忠厚正直，倘若不嫌棄，貧僧倒是可"
                                        "以將這門武功的一部分傳授於你。");

                                set("can_learn/jiuyang-shengong/shaolin", 1, who);
                                tell_object(who, HIC "覺遠同意傳授你「少林九陽功」。\n" NOR);

                                if (who->can_improve_skill("martial-cognize"))
                                        who->improve_skill("martial-cognize", 1500000);
                                return 1;
                        }
                }
                message_vision(CYN "$N" CYN "滿臉歡喜的對$n" CYN "道：施主宅心仁厚，"
                               "日後必有大成，貧僧多謝了。\n" NOR, this_object(), who);
                return 1;
        }
        return 0;
}

int recognize_apprentice(object who, string skill)
{
        if( !query("can_learn/jiuyang-shengong/shaolin", who) )
        {
                command("say 施主言重了，貧僧本事低微，何談“指點”二字。");
                return -1;
        }

        if (skill != "shaolin-jiuyang")
        {
                command("say 正所謂“知足而樂，能忍則安”，其它武功請恕貧僧不能教授。");
                return -1;
        }
        return 1;
}
