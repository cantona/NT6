// This program is a part of NITAN MudLIB
// feng.c 風清揚

inherit NPC;
inherit F_MASTER;

#include <ansi.h>

string ask_skill();
string ask_skill1();
string ask_skill2();
string ask_skill3();
mapping po_type = ([ "破劍式" : ({ "sword" }),
                     "破刀式" : ({ "blade" }),
                     "破槍式" : ({ "staff" }),
                     "破鞭式" : ({ "hammer", "club", "dagger" }),
                     "破索式" : ({ "whip" }),
                     "破掌式" : ({ "unarmed", "finger", "claw",
                                   "strike", "hand", "cuff" }),
                     "破箭式" : ({ "throwing" }),
                     "破氣式" : ({ "force" }), ]);

int check_skill(string skill);
mixed teach_lonely_sword();

void create()
{
        set_name("風清揚", ({ "feng qingyang", "feng", "qingyang" }));
        set("title", "華山劍宗長老");
        set("nickname", HIW "劍氣沖霄" NOR);
        set("long", @LONG
這便是當年名震江湖的華山名宿風清揚。他身
著青袍，神氣抑鬱臉如金紙。身材瘦長，眉宇
間一直籠罩著一股淡淡的憂傷神色，顯然對當
年的劍氣之爭一直難以忘懷。
LONG);
        set("gender", "男性");
        set("age", 68);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 40);
        set("int", 40);
        set("con", 40);
        set("dex", 40);
        set("max_qi", 6000);
        set("max_jing", 5000);
        set("neili", 6500);
        set("max_neili", 6500);
        set("jiali", 200);
        set("level", 60);
        set("combat_exp", 4000000);

        set_skill("force", 700);
        set_skill("zixia-shengong", 700);
        set_skill("huashan-neigong", 700);
        set_skill("dodge", 700);
        set_skill("feiyan-huixiang", 700);
        set_skill("huashan-shenfa", 700);
        set_skill("parry", 700);
        set_skill("sword", 700);
        set_skill("huashan-sword", 700);
        set_skill("lonely-sword", 700);
        set_skill("blade", 700);
        set_skill("fanliangyi-dao", 700);
        set_skill("strike", 700);
        set_skill("hunyuan-zhang", 700);
        set_skill("cuff", 700);
        set_skill("poyu-quan", 700);
        set_skill("huashan-quan", 700);
        set_skill("huashan-zhang", 700);
        set_skill("literate", 700);
        set_skill("martial-cognize", 700);

        map_skill("cuff", "poyu-quan");
        map_skill("force", "zixia-shengong");
        map_skill("dodge", "feiyan-huixiang");
        map_skill("parry", "lonely-sword");
        map_skill("blade", "fanliangyi-dao");
        map_skill("sword", "lonely-sword");
        map_skill("strike", "hunyuan-zhang");

        prepare_skill("cuff", "poyu-quan");
        prepare_skill("strike", "hunyuan-zhang");

        //create_family("華山劍宗", 0, "高人");
        create_family("華山派", 0, "高人");

        set("inquiry", ([
                "破眾"    : (: ask_skill :),
                "笑滄海"  : (: ask_skill1 :),
                "劍魂"    : (: ask_skill2 :),
                "劍心通明": (: ask_skill3 :),
        ]));

        set("chat_chance_combat", 200);
        set("chat_msg_combat", ({
                (: perform_action, "sword.po" :),
                (: perform_action, "sword.yi" :),
                (: perform_action, "sword.poqi" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set("can_perform/lonely-sword", ({ "sword", "blade", "staff",
                                           "hammer", "club", "dagger",
                                           "whip", "unarmed", "finger",
                                           "claw", "strike", "hand",
                                           "cuff", "force", "throwing" }));

        set("no_teach", ([
                "lonely-sword" : (: teach_lonely_sword :),
        ]));
        set_temp("apply/damage", 200);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob",5);
        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
}

void init()
{
        object ob, me = this_object();

        ::init();

        if (! objectp(me)) return;
        if (file_name(environment(me)) == "/d/huashan/xiaofang")
        {
                if (interactive(ob = this_player()) && ! ob->is_fighting()
                 && sizeof(query_temp("win", ob)) != 6
                &&  ! wizardp(ob))
                {
                        remove_call_out("auto_kill");
                        call_out("auto_kill", 1, ob );
                }else if( !query("see_feng", ob) )
                {
                        remove_call_out("improve_sword");
                        call_out("improve_sword", 1, ob );
                }
        }
}

int auto_kill(object ob)
{
        object me = this_object();

        command("say 好家伙竟敢謀害桃谷六仙，納命來吧！");
        me->kill_ob(ob);
        ob->fight(me);
        return 1;
}

int improve_sword(object ob)
{
        int my_sword, add_level;

        if (! objectp(ob)) return 1;
        my_sword = ob->query_skill("sword", 1);
        command("say " + RANK_D->query_respect(ob) + "既然一場來到，你我可謂有緣，待我指點你一些劍法吧。");
        message_vision("風清揚開始為$N解說基本劍法的精義。\n", ob);

        if (my_sword < 100)
        {
                add_level = my_sword + 20;
                tell_object( ob, "你的基本劍法增加了二十級！\n");
        } else
        if (my_sword < 120)
        {
                add_level = my_sword + 10;
                tell_object( ob, "你的基本劍法增加了十級！\n");
        } else
        if (my_sword < 150)
        {
                add_level = my_sword + 5;
                tell_object( ob, "你的基本劍法增加了五級！\n");
        }
        else {
                message_vision("風清揚對著$N驚訝地「啊！」了一聲。\n", ob);
                command("say " + RANK_D->query_respect(ob) + "的劍法已然登堂入室，老朽不勝佩服！\n");
                tell_object(ob, "你的基本劍法已躊爐火純青之境，風清揚已沒什麼可指點于你的了！\n");
                set("see_feng", 1, ob);
                return 1;
        }

        ob->set_skill("sword", add_level);
        set("see_feng", 1, ob);
        addn("combat_exp", 15000, ob);
        return 1;
}

mixed teach_lonely_sword()
{
        object me;

        me = this_player();

        if( query("family/family_name", me) != "華山派"
             && query("family/family_name", me) != "華山劍宗" )
        {
                command("say 走開！非華山的弟子我一概不教。");
                return -1;
        }

        if (me->query_skill("lonely-sword", 1) > 120)
        {
                if( query_temp("feng_has_told", me) )
                {
                        command("say 你自己好好練吧！");
                        return -1;
                }

                command("pat"+query("id", me));
                command("say 這套劍法要靠自己勤練，以後你自己多加鑽研吧！");
                set_temp("feng_has_told", 1, me);
                return -1;
        }

        if( query_temp("learnd_lonely_sword", me) )
                return 0;

        set_temp("learnd_lonely_sword", 1, me);
        command("say 很好，很好。這門劍法重在劍意，不在招式。");
        command("say 倘若學習，切不可拘泥于形式。");
        return 0;
}

void attempt_apprentice(object ob)
{
        if( query("family/family_name", ob) != "華山派"
             && query("family/family_name", ob) != "華山劍宗" )
        {
                command("say 走開！非華山的弟子我一概不見。");
                return;
        }

        command("say 我不收徒，你另請高明吧。");
}

int check_skill(string skill)
{
        if (skill != "sword" && skill != "lonely-sword")
        {
                command("say 我只懂劍法，你想學就學，不想學就算了。");
                return -1;
        }
        return 1;
}

int recognize_apprentice(object ob, string skill)
{
        if( query("can_learn/feng/lonely-sword", ob) )
                return check_skill(skill);

        if( query("can_learn/feng/sword", ob )
           && skill != "lonely-sword")
        {
                if (skill == "sword")
                        return 1;

                command("say 教你點基本劍法是看得起你，少跟我羅嗦！");
                return -1;
        }

        if( query_temp("have_asked_feng", ob) )
        {
                command("say 還不快滾！");
                return -1;
        }

        if( query("family/family_name", ob) != "華山派"
             && query("family/family_name", ob) != "華山劍宗" )
        {
                command("say 走開！非華山的弟子我一概不教。");
                return -1;
        }

        if( query("character", ob) == "陰險姦詐"
            || query("character", ob) == "心狠手辣" )
        {
                command("heng");
                command("say 不想死的就給我滾！");
                set_temp("have_asked_feng", 1, ob);
                return -1;
        }

        if( query("character", ob) == "光明磊落" )
        {
                command("hmm");
                command("say 你天性不壞，可是卻不適合練習這套劍法。");
                set_temp("have_asked_feng", 1, ob);
                return -1;
        }

        /*
        if( query("shen", ob)<-10000
            || query("shen", ob)>10000
            || query("weiwang", ob)>10000 )
        {
                command("say 我風某從不和成名人士打交道，你走吧。");
                set_temp("have_asked_feng", 1, ob);
                return -1;
        }
        */

        if( query("int", ob)<26 )
        {
                command("sneer");
                command("say 你這個呆頭鵝，忒笨了點，走吧。");
                set_temp("have_asked_feng", 1, ob);
                return -1;
        }

        if( query("int", ob)<28 )
        {
                command("look "+query("id", ob));
                command("say 你倒是不算笨，有點小聰明，不過…還是差得遠啊。");
                set_temp("have_asked_feng", 1, ob);
                return -1;
        }

        if (ob->query_skill("sword", 1) < 100)
        {
                command("say 你人雖不錯，可是你的對劍法的理解也未免太差了。");
                return -1;
        }

        if( query("int", ob)<34 )
        {
                if (skill == "sword")
                {
                        command("say 好吧，我就教你一點關于劍法的知識。");
                        set("can_learn/feng/sword", 1, ob);
                        return 1;
                }

                if (skill != "lonely-sword")
                {
                        command("say 我只會劍法，要學其它的本事找別的師傅去吧！");
                        return -1;
                }

                command("sigh");
                command("say 你這人算是聰明，可離獨孤九劍還是差之甚遠。");
                return -1;
        }

        if (check_skill(skill) == -1)
                return -1;

        message_sort(HIW "\n$N" HIW "點了點頭，對$n" HIW "說道：“甚"
                     "好，甚好。雖然我不收徒，不過看你天資實在不錯，"
                     "就傳你一點劍法吧。這套獨孤九劍共分為九勢，我先"
                     "傳你總訣式，其他破劍式、破刀式、破槍式、破鞭式"
                     "、破索式、破掌式、破箭式、破氣式我隨後一一分解"
                     "與你聽。”\n" NOR, this_object(), ob);

        tell_object(ob, HIC "\n風清揚同意傳授你「獨孤九劍」。\n" NOR);
        set("can_learn/feng/lonely-sword", 1, ob);
        ob->improve_skill("martial-cognize", 1500000);
        return 1;
}

int accept_ask(object me, string topic)
{
        string *learned, *try_to;
        mixed pot;

        pot=query("potential", me);
        pot = atoi(pot);

        if (! topic || undefinedp(try_to = po_type[topic]))
                return 0;

        if (! (int)me->query_skill("lonely-sword", 1))
        {
                command("say 你會獨孤九劍麼？就向我問這個？");
                return 1;
        }

        learned=query("can_perform/dugu-jiujian", me);
        if (! arrayp(learned))
                learned = ({ });
        if (member_array(try_to[0], learned) != -1)
        {
                command("say 你不是已經學會" + topic + "了麼？");
                return 1;
        }

        command("say 好吧，" + topic + "的要訣你要聽仔細了。");
        if( query("potential", me)-query("learned_points", me)<10 )
        {
                set("learned_points",query("potential",  me), me);
                tell_object(me, HIG "你聽了風清揚的教導，頗覺迷茫，看"
                                "來是潛能不夠了。\n" NOR);
                return 1;
        }

        addn("learned_points", 10, me);
        if (random(2))
        {
                write(HIY "你聽了風清揚的教導，頗有心得。\n" NOR);
                return 1;
        }

        learned -= try_to;
        learned += try_to;
        set("can_perform/dugu-jiujian", learned, me);
        tell_object(me, HIC "你學會了獨孤九劍之「" + topic + "」。\n");
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("lonely-sword"))
                me->improve_skill("lonely-sword", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        return 1;
}

string ask_skill()
{
        object me = this_player();

        if (! (int)me->query_skill("lonely-sword", 1))
        {
                return "你會獨孤九劍麼？就向我問這個？";
        }

        if( query("can_perform/lonely-sword/pozhong", me) )
                return "你不是已經學會了嗎？";

        if( query("potential", me)-query("learned_points", me)<10 )
        {
                set("learned_points",query("potential",  me), me);
                return "獨孤九劍要旨在于「悟」，不可拘泥不化，講究料敵機先，出奇制勝。\n"+
                HIG "你聽了風清揚的教導，頗覺迷茫，看"
                        "來是潛能不夠了。" NOR;
        }
        addn("leaned_points", 10, me);
        if (random(5) > 2)
        {
                return "獨孤九劍要旨在于「悟」，不可拘泥不化，講究料敵機先，出奇制勝。\n"HIY "你聽了風清揚的教導，頗有心得。" NOR;
        }
        return MASTER_D->teach_pfm(this_player(),this_object(),([
                                        "perform"       : "can_perform/lonely-sword/po",            //pfm的代碼
                                        "name"          : "破眾",               //pfm的名稱
                                        "sk1"           : "lonely-sword",       //主要的武功的id
                                        "lv1"           : 80,                   //主要的武功的等級
                                        "sk2"           : "sword",              //需要武功sk2的id
                                        "lv2"           : 50,                   //需要武功sk2 的等級
                                        "neili"         : 50,                   //需要基本內功
                                        "free"          : 1,
                                        "gongxian"      : 300,
                                        ]));
}
string ask_skill1()
{
        object me = this_player();

        if (! (int)me->query_skill("lonely-sword", 1))
        {
                return "你會獨孤九劍麼？就向我問這個？";
        }

        if( query("can_perform/lonely-sword/xiao", me) )
                return "你不是已經學會了嗎？";

        if( query("potential", me)-query("learned_points", me)<10 )
        {
                set("learned_points",query("potential",  me), me);
                return "獨孤九劍要旨在于「悟」，不可拘泥不化，講究料敵機先，出奇制勝。\n"+
                HIG "你聽了風清揚的教導，頗覺迷茫，看"
                        "來是潛能不夠了。" NOR;
        }
        addn("leaned_points", 10, me);
        if (random(5) > 2)
        {
                return "獨孤九劍要旨在于「悟」，不可拘泥不化，講究料敵機先，出奇制勝。\n"HIY "你聽了風清揚的教導，頗有心得。" NOR;
        }
        return MASTER_D->teach_pfm(this_player(),this_object(),([
                                        "perform"       : "can_perform/lonely-sword/xiao",            //pfm的代碼
                                        "name"          : "笑滄海",             //pfm的名稱
                                        "sk1"           : "lonely-sword",       //主要的武功的id
                                        "lv1"           : 180,                   //主要的武功的等級
                                        "sk2"           : "sword",              //需要武功sk2的id
                                        "lv2"           : 180,                   //需要武功sk2 的等級
                                        "free"          : 1,
                                        "neili"         : 200,                   //需要基本內功
                                        ]));
}

string ask_skill2()
{
        object me = this_player();

        if (! (int)me->query_skill("lonely-sword", 1))
        {
                return "你會獨孤九劍麼？就向我問這個？";
        }

        if( query("can_perform/lonely-sword/hun", me) )
                return "你不是已經學會了嗎？";

        if( query("potential", me)-query("learned_points", me)<10 )
        {
                set("learned_points",query("potential",  me), me);
                return "獨孤九劍要旨在于「悟」，不可拘泥不化，講究料敵機先，出奇制勝。\n"+
                HIG "你聽了風清揚的教導，頗覺迷茫，看"
                        "來是潛能不夠了。" NOR;
        }
        addn("leaned_points", 10, me);
        if (random(5) > 2)
        {
                return "獨孤九劍要旨在于「悟」，不可拘泥不化，講究料敵機先，出奇制勝。\n"HIY "你聽了風清揚的教導，頗有心得。" NOR;
        }
        return MASTER_D->teach_pfm(this_player(),this_object(),([
                                        "perform"       : "can_perform/lonely-sword/hun",            //pfm的代碼
                                        "name"          : "劍魂",             //pfm的名稱
                                        "sk1"           : "lonely-sword",       //主要的武功的id
                                        "lv1"           : 1000,                   //主要的武功的等級
                                        "sk2"           : "sword",              //需要武功sk2的id
                                        "lv2"           : 1000,                   //需要武功sk2 的等級
                                        "neili"         : 2000,                   //需要基本內功
                                        "reborn"        : 1,           
                                        "free"          : 1,
                                        "gongxian"      : 3000,
                                        ]));
}

string ask_skill3()
{
        object me = this_player();

        if (! (int)me->query_skill("lonely-sword", 1))
        {
                return "你會獨孤九劍麼？就向我問這個？";
        }

        if( query("can_perform/lonely-sword/jian", me) )
                return "你不是已經學會了嗎？";

        if( query("potential", me)-query("learned_points", me)<10 )
        {
                set("learned_points",query("potential",  me), me);
                return "獨孤九劍要旨在于「悟」，不可拘泥不化，講究料敵機先，出奇制勝。\n"+
                HIG "你聽了風清揚的教導，頗覺迷茫，看"
                        "來是潛能不夠了。" NOR;
        }
        addn("leaned_points", 10, me);
        if (random(5) > 2)
        {
                return "獨孤九劍要旨在于「悟」，不可拘泥不化，講究料敵機先，出奇制勝。\n"HIY "你聽了風清揚的教導，頗有心得。" NOR;
        }
        return MASTER_D->teach_pfm(this_player(),this_object(),([
                                        "perform"       : "can_perform/lonely-sword/jian",            //pfm的代碼
                                        "name"          : "劍心通明",             //pfm的名稱
                                        "sk1"           : "lonely-sword",       //主要的武功的id
                                        "lv1"           : 1000,                   //主要的武功的等級
                                        "sk2"           : "sword",              //需要武功sk2的id
                                        "lv2"           : 1000,                   //需要武功sk2 的等級
                                        "neili"         : 2000,                   //需要基本內功
                                        "reborn"        : 1,           
                                        "free"          : 1,
                                        "gongxian"      : 3000,
                                        ]));
}
