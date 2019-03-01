#include <ansi.h>
#include "taohua.h"

inherit NPC;
inherit F_MASTER;

mixed ask_me();
mixed ask_skill1();

void create()
{
        set_name( "馮默風" ,({ "feng mofeng", "feng", "mofeng" }));
        set("gender", "男性");
        set("age", 39);
        set("long", "馮默風是黃藥師最小的一個徒弟，他的根基不錯，但性子\n"
                    "較為愚魯。他的基本功紮實，一副忠厚老實的樣子。\n");
        set("attitude", "friendly");
        set("class", "scholar");
        set("str", 30);
        set("int", 24);
        set("con", 27);
        set("dex", 23);
        set("shen_type",1);
        set("max_qi", 4200);
        set("max_jing", 2100);
        set("neili", 4500);
        set("max_neili", 4500);
        set("jiali", 100);
        set("combat_exp", 800000);

        set_skill("force", 180);
        set_skill("luoying-xinfa", 180);
        set_skill("unarmed", 160);
        set_skill("xuanfeng-tui", 160);
        set_skill("strike", 160);
        set_skill("pikong-zhang", 160);
        set_skill("finger", 140);
        set_skill("canglang-zhi", 140);
        set_skill("dodge", 160);
        set_skill("parry", 160);
        set_skill("sword", 160);
        set_skill("luoying-shenjian", 160);
        set_skill("literate", 140);
        set_skill("martial-cognize", 140);

        map_skill("force", "luoying-xinfa");
        map_skill("unarmed", "xuanfeng-tui");
        map_skill("strike", "pikong-zhang");
        map_skill("finger", "canglang-zhi");
        map_skill("dodge", "xuanfeng-tui");
        map_skill("parry", "luoying-shenjian");
        map_skill("sword", "luoying-shenjian");

        prepare_skill("unarmed", "xuanfeng-tui");
        prepare_skill("strike", "pikong-zhang");

        create_family("桃花島", 2, "弟子");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.sui" :),
                (: perform_action, "finger.tao" :),
                (: perform_action, "strike.dai" :),
                (: perform_action, "unarmed.kuang" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }));

        set("chat_chance", 1);
        set("chat_msg", ({
                    CYN "馮默風說道：師父疼愛小師妹，他的軟□甲一直由小師妹穿著。\n" NOR,
                    CYN "馮默風自言自語地說道：家師所布置的這個桃花陣真是不簡單！\n" NOR,
        }));

        set("inquiry", ([
                   "拜師" : (: ask_me :),
                   "投師" : (: ask_me :),
                   "東邪" : "家師人稱東邪！呵呵。",
                   "西毒" : "歐陽鋒是與家師並世齊名的高手，人稱老毒物。",
                   "南帝" : "聽家師說段王爺現在出家當了和尚，法名一燈。",
                   "北丐" : "北丐洪七公是丐幫幫主，現在揚州城外。",
                   "黃蓉" : "她是師父的愛女。",
                   "黃藥師" : "你要拜訪家師？",
                   "桃花島" : "這兒就是桃花島，你若不是本派弟子，要過桃花陣。",
                   "桃花陣" : "往南就是了。",
                   "碧浪滔天" : (: ask_skill1 :),
        ]));
        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/changjian");
}

void attempt_apprentice(object ob)
{
        string master;
        if (! permit_recruit(ob))
                return;

        if( stringp(master=query_temp("taohua/master", ob)) )
        {
                if (master != name())
                {
                        command("say 家師不是讓你拜" + master + "的嗎？你怎麼來"
                                "找我來了？");
                        return;
                }

                command("say 好吧，既然家師有令，我就收下你了，不過要好好遵守桃"
                        "花島的規矩。");
                command("recruit "+query("id", ob));
                delete_temp("taohua/master", ob);
                return;
        }

        command("shake");
        command("say 我可不敢擅自收徒，你還是找家師黃島主吧！");
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/canglang-zhi/tao", me) )
                return "這一招我不是已經教過你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你不是我們桃花島的人，問這個幹嘛？";

        if (me->query_skill("canglang-zhi", 1) < 1)
                return "你連滄浪指法都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<50 )
                return "師父吩咐過，不傳功給無功勞的弟子。";

        if (me->query_skill("force") < 120)
                return "你的內功修為不夠，還是多鍛煉鍛煉吧。";

        if (me->query_skill("canglang-zhi", 1) < 80)
                return "你的滄浪指法還不夠熟練，練高了再來找我。";

        message_sort(HIY "\n$n" HIY "點了點頭，道：“既然家師吩咐過，今日我就"
                     "傳你這招，可要看好了。”說完只見$n" HIY "陡然伸出一指，"
                     "紛翻不定，頓聽指氣嗤然作響，全全籠罩$N" HIY "四周。\n\n"
                     NOR, me, this_object());

        command("nod");
        command("say 看懂了嗎？");
        tell_object(me, HIC "你學會了「碧浪滔天」。\n" NOR);
        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 1500000);
        if (me->can_improve_skill("canglang-zhi"))
                me->improve_skill("canglang-zhi", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/canglang-zhi/tao", 1, me);
        addn("family/gongji", -50, me);

        return 1;
}

mixed ask_me()
{
        object me;
        me = this_player();

        if( query("family/family_name", me) )
        {
                if( query("family/family_name", me) != "桃花島" )
                {
                        command("say 閣下已有門派，家師是不會收留你的，請走吧！");
                        return 1;
                }

                if( query("family/master_name", me) )
                {
                        command("say 你不是已經入了我們桃花島嗎？");
                        return 1;
                }
        }

        if( query("detach/桃花島", me) )
        {
                command("say 當年你離開了桃花島，今天還敢回來見家師？");
                return 1;
        }

        if( query("betrayer/times", me) )
        {
                command("say 你這判師之人，家師是絕對不會收你為徒的！");
                return 1;
        }
        command("say 好吧，我帶你過桃花陣，你自己去找黃島主吧。");
        message_vision(HIW "\n$N" HIW "大步的向南走去，$n" HIW "緊隨其後。\n\n" NOR,
                       this_object(), me);
        this_object()->move("/d/taohua/damen");
        me->move("/d/taohua/damen");
        command("say 好了，我帶你到大門，你進去就可以見到家師。");
        message_vision("$N頭也不回的往北面離去。\n", this_object());
        this_object()->move(query("startroom"));
        message_vision("$N急匆匆的走了過來。\n", this_object());
        return 1;
}

void unconcious()
{
        die();
}
