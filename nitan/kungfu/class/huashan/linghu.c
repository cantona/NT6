// This program is a part of NITAN MudLIB
// linghu.c 令狐沖

#include <ansi.h>
#include "qizong.h"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

mixed ask_me();
string ask_ylj1();
string ask_ylj2();
string ask_ylj3();
mixed learn_chongling();

void create()
{
        set_name("令狐沖", ({ "linghu chong", "linghu", "chong" }));
        set("nickname", "大師兄");
        set("long", "他身材較瘦，長的濃眉闊眼，氣宇暄昂，在同門中排行老大，\n"
                    "是華山派年輕一代中的頂尖好手。\n");
        set("gender", "男性");
        set("age", 28);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 30);
        set("int", 40);
        set("con", 30);
        set("dex", 30);

        set("qi", 4800);
        set("max_qi", 4800);
        set("jing", 2400);
        set("max_jing", 2400);
        set("neili", 5700);
        set("max_neili", 5700);
        set("jiali", 60);
        set("level", 30);
        set("combat_exp", 2200000);
        set("score", 150000);

        set_skill("blade", 200);
        set_skill("cuff", 200);
        set_skill("feiyan-huixiang", 200);
        set_skill("strike", 200);
        set_skill("hunyuan-zhang", 200);
        set_skill("cuff",200);
        set_skill("poyu-quan", 200);
        set_skill("force", 200);
        set_skill("yijinjing", 200);
        set_skill("huashan-neigong", 200);
        set_skill("zixia-shengong", 200);
        set_skill("dodge", 200);
        set_skill("parry", 220);
        set_skill("sword", 240);
        set_skill("huashan-sword", 240);
        set_skill("chongling-jian", 240);
        set_skill("lonely-sword", 240);
        set_skill("huashan-quan", 240);
        set_skill("huashan-zhang", 240);
        set_skill("literate", 240);
        set_skill("tanqin-jifa", 400);
        set_skill("xiaoao-jianghu", 400);
        set_skill("qingxin-pushan", 400);
        set_skill("martial-cognize", 230);

        map_skill("force", "yijinjing");
        map_skill("cuff", "poyu-quan");
        map_skill("strike", "huashan-zhangfa");
        map_skill("dodge", "feiyan-huixiang");
        map_skill("parry", "lonely-sword");
        map_skill("sword", "lonely-sword");
        map_skill("tanqin-jifa", "xiaoao-jianghu");

        prepare_skill("strike", "hunyuan-zhang");
        prepare_skill("cuff", "poyu-quan");

        set("chat_chance_combat", 40);
        set("chat_msg_combat", ({
                (: perform_action, "sword.poqi" :),
                (: perform_action, "sword.po" :),
                (: perform_action, "sword.yi" :),
                (: exert_function, "recover" :),
        }) );

        create_family("華山派", 14, "弟子");

        set("inquiry", ([
                "風清揚" : "唉，已經很久沒有見到他老人家了。你問這幹嘛？",
                "任盈盈" : "你真有她的消息嗎，說罷，以見他神情激動，好象眼睛紅紅的！\n",
                "清心普善咒" : "這可是盈盈交給我的...",
                "笑傲江湖"   : "這是曲洋長老和劉正風師叔留下來的...唉！",
                "琴譜"       : (: ask_me :),
                "沖靈劍法"   : (: learn_chongling :),
                "寶劍"       : (: ask_ylj3 :),
                // "墨紋玄鐵"   : (: ask_ylj2 :),
                // "遇見尼姑，逢賭必輸" : (: ask_ylj1 :),
        ]));

        set("no_teach", ([
                "yijinjing"    : "此乃少林秘傳，蒙方正大師傳授，我不能擅自教你。",
                "lonely-sword" : "風老先生傳我九劍的時候我立下誓言不得私"
                                 "自傳授，你還是學習其他武功吧！",
        ]));

        set("music_book", 1);
        set("master_ob",3);
        setup();
        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/heimuya/npc/obj/card2");
}

int recognize_apprentice(object me, string skill)
{
        if (skill != "tanqin-jifa" &&
            skill != "xiaoao-jianghu" &&
            skill != "qingxin-pushan")
        {
                command("say 對不起...我不能傳授你這些，你要是想學點操琴技術還差不多。");
                return -1;
        }

        if( query_temp("can_learn/linghu/"+skill, me) )
                return 1;

        set_temp("can_learn/linghu/"+skill, 1, me);
        command("say 好吧，你既然對" + to_chinese(skill) +
                "有興趣，我就教你一點。");

        return 1;
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("family/family_name", ob) == "華山劍宗" )
        {
                command("say 你是劍宗的啊？我可不好收你，我師傅不同意的！");
                return;
        }

        if( query("shen", ob)<0 )
        {
                command("say 我華山派乃是堂堂名門正派，對弟子要求極嚴。");
                command("say 在德行方面，" + RANK_D->query_respect(ob) +
                        "是否還做得不夠？");
                return;
        }

        if ((int)ob->query_int() < 25)
        {
                command("say 依我看" + RANK_D->query_respect(ob) + "的資質似乎不適合學我華山派武功？");
                return;
        }

        command("say 好吧，我就收下你了。");
        command("recruit "+query("id", ob));
        if( query("class", ob) != "swordsman" )
                set("class", "swordsman", ob);

        return;
}

mixed ask_me()
{
        object me;
        object ob;

        me = this_player();
        if (query("music_book") < 1)
                return "我的琴譜已經借出去了。\n";

        ob = new("/clone/book/qin");
        ob->move(me, 1);
        message_vision("$n把琴譜給了$N，道：你拿去好好學習吧。\n",
                       me, this_object());
        set("music_book", 0);
        return 1;
}

void reset()
{
        set("music_book", 1);
}

/*
void unconcious()
{
        die();
}
*/

mixed learn_chongling()
{
        object me = this_player();
        int lv = me->query_skill("huashan-sword", 1);

        if (me->query_skill("chongling-jian"))
               return "你不是已經會了嗎？\n";

        if( query("family/family_name", me) != "華山派" )
               return "你說什麼，我不明白！\n";

        if (lv < 100)
               return "你沖靈劍法修為不夠，我還不能傳你這招！\n";
        message_vision(HIW "$N" HIW "說道：“這套劍法是我和小師妹練劍的時候突發奇想"
                       "創出來的，乃是從華山劍法中演化出來！你可看好了！”說完將「沖"
                       "靈劍法」沖頭到尾地給$n" HIW "演示了一遍！\n" NOR,
                       this_object(), me);

        command("haha");
        tell_object(me, HIG "你學會了「沖靈劍法」！\n" NOR);

        if( !query("have_ask_chongling", me)){
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("huashan-sword"))
                me->improve_skill("huashan-sword", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("have_ask_chongling", 1, me);
        }

        command("say 領會了多少就看你華山劍法的修為了，剩下的就靠你自己下去練習！");

        me->set_skill("chongling-jian", lv / 10);

        return 1;
}

int accept_object(object who, object ob)
{
        object obn;
        int r;

        if (r = ::accept_object(who, ob))
                return r;

        if (! who || environment(who) != environment())
                return 0;

        if (! objectp(ob))
                return 0;

        if (! present(ob, who))
                return notify_fail("你沒有這件東西。\n");

        if( query("name", ob) != "信" &&
            query("id", ob) != "qingxin" )
                return notify_fail("令狐沖不需要這件東西。\n");

        say("令狐沖雙手捧著任盈盈的信，淚如雨下，這塊白虎堂令牌你拿去還給盈盈，告訴她我就去找她!");
        obn = new("/d/heimuya/npc/obj/card2");
        obn->set_amount(1);
        obn->move(who);
        destruct(ob);
        return 1;
}

string ask_ylj1()
{
        object me;

        me = this_player();
        command("haha"+query("id", me));
        set_temp("ylj/step1", 1, me);

        return sort_string("兄台也知道這件事？這是當初兄弟我為救恆山派的儀琳師妹，向採"
                           "花大盜田伯光開的玩笑，事後恆山的定靜師伯不但沒怪我，還送我"
                           "了一塊世間已絕跡的墨紋玄鐵，要我用它鑄成一把絕世寶劍，行俠"
                           "處惡，笑傲江湖.....\n", 64, 3);
}

string ask_ylj2()
{
        object me;

        me = this_player();
        if( !query_temp("ylj/step1", me) )
                return "這可是個天大的秘密。\n";

        set_temp("ylj/step2", 1, me);
        delete_temp("ylj/step1", me);

        return "說來這墨紋玄鐵也是一個寶物，我一直找不到鑄劍名師，不想浪費了這塊玄鐵...。\n";
}

string ask_ylj3()
{
        object me, obj;

        me = this_player();
        if( !query_temp("ylj/step2", me) )
                return "這可是個天大的秘密。\n";

        delete_temp("ylj/step2", me);
        command("look"+query("id", me));

        if( query("shen", me)>100000 )
        {
                obj = new(__DIR__"obj/xuantie");
                obj->move(me);
                // me->set_temp("ylj/step3", 1);
                return "看兄台一身正氣，這塊玄鐵就送與兄台，望兄台能找到鑄\n"
                       "劍名師，鑄成寶劍，行俠江湖，也不枉費定靜師伯的一翻苦心.....\n";
        }
        return "這可是個天大的秘密。\n";
}
