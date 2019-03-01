// This program is a part of NT MudLIB
// lu.c 陸乘風

#include <ansi.h>
#include "taohua.h"

inherit NPC;
inherit F_MASTER;

mixed ask_skill1();
mixed ask_skill2();
mixed ask_skill3();

string ask_me();
int    ask_xfsy();

void create()
{
        set_name( "陸乘風" ,({ "lu chengfeng", "lu", "chengfeng" }));
        set("gender", "男性");
        set("nickname", HIC "歸雲莊主" NOR);
        set("age", 52);
        set("long", "陸乘風是黃藥師的第四個徒弟。他的鬢角已微見白發，但\n"
                    "身材魁梧，雙眼有神。\n");
        set("attitude", "friendly");
        set("class", "scholar");
        set("str", 24);
        set("int", 30);
        set("con", 25);
        set("dex", 21);

        set("max_qi", 4500);
        set("max_jing", 2500);
        set("neili", 5000);
        set("max_neili", 5000);
        set("jiali", 120);
        set("combat_exp", 1000000);
        set("bagua_count", 5);
        set("yulu_count", 5);

        set_skill("force", 200);
        set_skill("bibo-shengong", 200);
        set_skill("unarmed", 200);
        set_skill("xuanfeng-tui", 200);
        set_skill("strike", 200);
        set_skill("luoying-shenzhang", 200);
        set_skill("finger", 180);
        set_skill("tanzhi-shentong", 180);
        set_skill("dodge", 180);
        set_skill("luoying-shenfa", 180);
        set_skill("parry", 180);
        set_skill("sword", 200);
        set_skill("luoying-shenjian", 200);
        set_skill("whip", 180);
        set_skill("canglang-bian", 180);
        set_skill("literate", 180);
        set_skill("qimen-wuxing", 160);
        set_skill("calligraphy", 160);
        set_skill("martial-cognize", 160);

        map_skill("force", "luoying-xinfa");
        map_skill("unarmed", "xuanfeng-tui");
        map_skill("strike", "luoying-shenzhang");
        map_skill("finger", "tanzhi-shentong");
        map_skill("dodge", "luoying-shenfa");
        map_skill("parry", "luoying-shenjian");
        map_skill("whip", "canglang-bian");
        map_skill("sword", "luoying-shenjian");

        prepare_skill("unarmed", "xuanfeng-tui");
        prepare_skill("strike", "luoying-shenzhang");

        create_family("桃花島", 2, "弟子");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.sui" :),
                (: perform_action, "strike.wuxing" :),
                (: perform_action, "unarmed.kuang" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }));

        set("inquiry", ([
                "東邪"   : "家師人稱東邪！呵呵。",
                "西毒"   : "歐陽鋒是與家師並世齊名的高手，人稱老毒物。",
                "南帝"   : "聽家師說段王爺現在出家當了和尚，法名一燈。",
                "北丐"   : "北丐洪七公是丐幫幫主，現在揚州城外。",
                "黃蓉"   : "她是師父的愛女。",
                "梅超風" :"這賊婆娘害得我好苦。她不要臉偷漢，那也罷了，幹嗎要偷師父的《九陰真經》？",
                "陳玄風" :"他和梅超風都是師門叛徒，有何好說？這兩人害得我好苦！我半身不遂，就是拜受這兩人之賜。",
                "曲靈風" :"靈風師兄專于武技，不過育有一女，不知如今下落如何？",
                "馮默風" :"你可持桃花本門信物前往尋找默風，馮師弟天性淡泊，但外和內剛，恐怕需用非常手段才能逼他表露身份．．．",
                "黃藥師" : "當年師父一怒之下，將我們師兄弟四人一齊震斷腳筋，逐出桃花島。",
                "桃花島" : (: ask_me :),
                "巨浪滔天" : (: ask_skill1 :),
                "狂風絕技" : (: ask_skill2 :),
                "風雷四神劍" : (: ask_skill3 :),
                "旋風掃葉腿" : (: ask_xfsy :),
        ]));
        set("master_ob", 4);
        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/changjian");
}

void init()
{
        ::init();
        add_action("do_recite", "recite");
}

void attempt_apprentice(object ob)
{
        string master;
        if (! permit_recruit(ob))
                return;
        /*
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
        */
        if( query_temp("pending/recite", ob) )
        {
                command("say 你粗鄙不文，見識淺薄，本莊主怎會收你？");
                return;
        } else
        {
                command("say 一位異人曾在本莊花廳留詩半闕，如果你能補全，也不枉來歸雲莊一遭");
                message_vision("陸莊主凝視著$N，說道：快把你的下闕大聲朗誦(recite)出來吧。\n",
                               this_player());
                set_temp("pending/recite", 1, ob);
        }
}

int do_recite(string arg)
{
        string name, new_name, ttt;

        if( !query_temp("pending/recite", this_player()) )
                return 0;

        if (! arg)
                return notify_fail("你說什麼？\n");

        set_temp("pending/recite", 0, this_player());

        message_vision("$N大聲說道：" + arg + "\n", this_player());

        if (arg == "無人爭曉渡殘月下寒沙")
        {
                command("smile");
                if( query("gender", this_player()) == "男性" )
                        ttt = "門生";
                else
                if( query("gender", this_player()) == "女性" )
                        ttt = "青衣";
                else
                {
                        command("sigh");
                        command("say " + "卿本佳人，奈何自宮，本莊與東廠概無關聯，你去吧！");
                        return 0;
                }
                command("say " + "好！好！" + RANK_D->query_respect(this_player()) +
                        "果然博聞強記。敝人就收你做個" + ttt +"吧。");

                command("recruit "+query("id", this_player()));
                set("title", "歸雲莊"+ttt, this_player());
        } else
        {
                command("say 你這白丁，待在這裡，沒的臟了我的屋子！");
        }
        return 1;
}

string ask_me()
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player())) || 
                fam["family_name"] !="桃花島")
                return RANK_D->query_respect(this_player()) +
                       "與敝莊素無來往，不知此話從何談起？";

        if (query("bagua_count") < 1)
                return "今天我太累了，有什麼事明天再說吧。";

        if( present("tie bagua",this_player()) || query_temp("get_bagua", this_player()) )
                return "現在你可以上桃花島試一試，看有沒有福份見到我師傅。";

        if (this_player()->query_skill("qimen-wuxing", 1) < 60 ||
        this_player()->query_skill("bibo-shengong", 1) < 60)
                return "桃花島上機關重重，你功夫不夠，還是不去為妙。";

        addn("bagua_count", -1);
        ob = new("/d/taohua/obj/bagua");
        ob->move(this_player());
        set_temp("get_bagua", 1, this_player());

        message_vision("陸乘風遞給$N一塊鐵八卦。\n", this_player());
        return "上島之後千萬小心，萬事靠自己，我也幫不上什麼忙了。";
}
/*
mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/pikong-zhang/dai", me) )
                return "這一招我不是已經教過你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你不是我們桃花島的人，問這個幹嘛？";

        if (me->query_skill("pikong-zhang", 1) < 1)
                return "你連劈空掌都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<80 )
                return "師父吩咐過，不傳功給無功勞的弟子。";

        if (me->query_skill("force") < 120)
                return "你的內功修為不夠，還是多鍛煉鍛煉吧。";

        if (me->query_skill("pikong-zhang", 1) < 80)
                return "你的劈空掌還不夠熟練，練高了再來找我。";

        message_sort(HIY "\n$n" HIY "對著$N" HIY "點了點頭，說道：“我給你演示"
                     "一遍，可看仔細了！”話音剛落，頓時只見$n" HIY "雙掌交疊雲"
                     "貫而出，激盪出無數圈勁氣，一環環向$N" HIY "斫去，招數當真"
                     "精奇無比。\n\n" NOR, me, this_object());

        command("smile");
        command("say 招式便是如此，你自己下去體會吧。");
        tell_object(me, HIC "你學會了「披星戴月」。\n" NOR);
        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("pikong-zhang"))
                me->improve_skill("pikong-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/pikong-zhang/dai", 1, me);
        addn("family/gongji", -80, me);

        return 1;
}
*/

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/canglang-bian/lang", me) )
                return "這一招我不是已經教過你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你不是我們桃花島的人，問這個幹嘛？";

        if (me->query_skill("canglang-bian", 1) < 1)
                return "你連滄浪鞭法都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<200 )
                return "師父吩咐過，不傳功給無功勞的弟子。";

        if (me->query_skill("force") < 120)
                return "你的內功修為不夠，還是多鍛煉鍛煉吧。";

        if (me->query_skill("canglang-bian", 1) < 80)
                return "你的滄浪鞭法還不夠熟練，練高了再來找我。";

        message_sort(HIY "\n$n" HIY "對著$N" HIY "點了點頭，說道：“我給你演示"
                     "一遍，可看仔細了！”話音剛落，頓時只見$n" HIY "手中長鞭"
                     "如巨浪連綿無窮無盡攻向虛空，真精奇無比。\n\n" NOR, me,
                     this_object());

        command("smile");
        command("say 招式便是如此，你自己下去體會吧。");
        tell_object(me, HIC "你學會了「巨浪滔天」。\n" NOR);
        if (me->can_improve_skill("whip"))
                me->improve_skill("whip", 1500000);
        if (me->can_improve_skill("canglang-bian"))
                me->improve_skill("canglang-bian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/canglang-bian/lang", 1, me);
        addn("family/gongji", -80, me);

        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/xuanfeng-tui/kuang", me) )
                return "這一招我不是已經教過你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你不是我們桃花島的人，問這個幹嘛？";

        if (me->query_skill("xuanfeng-tui", 1) < 1)
                return "你連旋風掃葉腿都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<300 )
                return "師父吩咐過，不傳功給無功勞的弟子。";

        if (me->query_skill("force") < 150)
                return "你的內功修為不夠，還是多鍛煉鍛煉吧。";

        if (me->query_skill("xuanfeng-tui", 1) < 100)
                return "你的旋風掃葉腿還不夠熟練，練高了再來。";

        message_sort(HIY "\n$n" HIY "點了點頭，喝道：“看好了！”便在$n" HIY
                     "話音落下的一瞬間，早已拔地而起，陡然使出旋風掃葉腿狂風"
                     "絕技，身法變得飄忽不定，足帶風塵，掌攜萬鈞。招式連貫氣"
                     "勢恢弘，勁風只襲得$N" HIY "面龐隱隱生疼。\n\n" NOR, me,
                     this_object());

        command("haha");
        command("say 下去後可要勤加練習，莫辜負了恩師的一番栽培。");
        tell_object(me, HIC "你學會了「狂風絕技」。\n" NOR);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1500000);
        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("xuanfeng-tui"))
                me->improve_skill("xuanfeng-tui", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/xuanfeng-tui/kuang", 1, me);
        addn("family/gongji", -300, me);

        return 1;
}

mixed ask_skill3()
{
        object me;

        me = this_player();

        if( query("can_perform/luoying-shenjian/fenglei", me) )
                return "這一招我不是已經教過你了嗎？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你不是我們桃花島的人，問這個幹嘛？";

        if (me->query_skill("luoying-shenjian", 1) < 1)
                return "你連落英神劍都沒學，還談什麼絕招可言？";

        if( query("family/gongji", me)<300 )
                return "師父吩咐過，不傳功給無功勞的弟子。";

        if (me->query_skill("force") < 150)
                return "你的內功修為不夠，還是多鍛煉鍛煉吧。";

        if (me->query_skill("luoying-shenjian", 1) < 100)
                return "你的落英神劍還不夠熟練，練高了再來。";

        message_sort(HIY "\n$n" HIY "點了點頭，喝道：“看好了！”便在$n" HIY
                     "話音落下的一瞬間，早已拔地而起，陡然使出「風雷四神劍」"
                     "絕技，高聲長吟：“桃花影裡飛神劍”，如風如雷般的發出數劍! "
                     "氣勢恢弘，勁風只襲得$N" HIY "面龐隱隱生疼。\n\n" NOR, me,
                     this_object());

        command("haha");
        command("say 下去後可要勤加練習，莫辜負了恩師的一番栽培。");
        tell_object(me, HIC "你學會了「風雷四神劍」。\n" NOR);
        if (me->can_improve_skill("force")) 
                me->improve_skill("force", 1500000); 
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("luoying-shenjian"))
                me->improve_skill("luoying-shenjian", 1500000);
        if (me->can_improve_skill("bibo-shengong")) 
                me->improve_skill("bibo-shengong", 1500000); 
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/luoying-shenjian/fenglei", 1, me);
        addn("family/gongji", -300, me);

        return 1;
}
int accept_kill(object me)
{
        if( query("family/family_name", me) == "桃花島" )
        {
                command("say 你我本是同門，如何要加害于我！\n");
                set("th_killer", 1, me);
                kill_ob(me);
                return 1;
        }
      return 1;
}

int accept_object(object me, object obj)
{
        call_out("accept_obj", 2, me, obj);
        return 1;
}

int accept_obj(object me, object obj)
{
        if (! me || ! obj) return 0;
        if( query("name", obj) == "旋風掃葉腿" )
        {
                command("ah");
                message_vision(CYN "$N雙手顫抖的展開薄紙，仔仔細細的讀了起來。\n", this_object());
                message_vision(CYN "$N一邊讀，一邊熱淚盈眶！\n", this_object());
                command("cry");
                command("say 多謝"+ RANK_D->query_respect(me) +"了。\n");
                set("xfsy_xinfa_reading", 1);
                set("xfsy_xinfa_accept", 1);
                if( query("family/family_name", me) == "桃花島" )
                        set("help_chengfeng", 1, me);
        }
        call_out("finish_reading", 100 + random(50), obj);
        return 1;
}

void finish_reading(object obj)
{
        delete("xfsy_xinfa_reading");
        destruct(obj);
}

int ask_xfsy()
{
        object me, obj;

        me = this_player();
        if (query("xfsy_xinfa_reading"))
        {
                command("say 對不住，我還沒讀完恩師所傳心法．");
                return 1;
        }

        if( query("family/family_name", me) == "桃花島"
        &&  query("xfsy_xinfa_accept"))
        {
                obj = new("/d/taohua/obj/xfsy_xinfa2");
                obj->move(me);
                command("say 這套心法我做了一些注解，"+RANK_D->query_respect(me) +
                        "可拿回去自行參悟。");

                message_vision("$N遞給$n一張薄紙。\n",this_object(),me);
                delete("xfsy_xinfa_accept");
        } else
                command("say 旋風掃葉腿心法已不在我這裡。");

        return 1;
}
