// dugu.c 獨孤求敗

#include <ansi.h>

inherit NPC;
inherit F_MASTER;
inherit F_NOCLONE;

#define ULTRA_OPINION   "宗師"
#define OPINION_TYPE    HIY "兵器功夫" NOR
#define MY_OPINION      "weapon"

#define QUESTGOODS_D(x) ("/quest/questdg/quest/questgoods" + x)
#define QUESTDG_D(x)    ("/quest/questdg/quest/questdg" + x)
#define DGMSG_D         ("/quest/questdg/dugu-msg")
#define ANTI_ROBOT      "/kungfu/class/ultra/robot"

mixed ask_opinion();
int give_quest();
int give_up();
void npc_dest(object npc);
void destory(object ob);
string time_period(int timep);
mixed ask_maze();

string  *my_opinions = ({ "sword", "blade", "staff", "hammer",
                          "club", "whip",  "dagger", });

string *dg_msg = ({
        "獨孤求敗笑呵呵的說：“",
        "獨孤求敗慢慢踱著方步道：“",
        "獨孤求敗低頭想了想，說道：“",
        "獨孤求敗滿臉期待的說道：“",
        "獨孤求敗微笑著道：“",
});

string* qin_msg1 = ({
        "動物是人們的朋友，就算name嚴重影響了生態環境，關起來也就可以了，",
        "我聽說name過多的繁殖，影響了當地的生態，不過還是不應該隨便殺動物，",
        "難道name也會給人類帶來麻煩？真是稀奇，我倒是想看看它，",
        "我這裡的花園養著很多的動物，就是沒有name，",
        "在空閒的時候，看看動物的生活能夠放鬆情緒，name其實挺可愛的，",
        "南海神尼是一個很喜歡動物的人，尤其是name，用來送給她做禮物最好不過，",
        "江湖上打打殺殺的，少不了讓name也遭受無辜連累，我有心保護它，",
});

string* qin_msg2 = ({
        "你去把它帶到這裡來吧。”",
        "去找到它，把它帶來。”",
        "你能把它帶我這裡來麼？”",
        "你就辛苦一趟去幫我把它找來吧。”",
        "把它弄來給我。”",
});

// 該頭文件必須在這裡嵌入
#include <ultra.h>

void check_weapon();

void create()
{
        set_name("獨孤求敗", ({ "dugu qiubai", "dugu" }) );
        set("title", HIC "大宗師" NOR);
        set("gender", "男性");
        set("age", 48);
        set("long",
"這是一個普普通通的老者，一襲粗布衣裳，\n"
"頦下一縷白須，神情詳和。目光轉動之間，\n"
"隱隱流露出一絲王者之氣。\n");
        set("attitude", "peaceful");
        set("no_get", 1);
        set("str", 38);
        set("int", 39);
        set("con", 32);
        set("dex", 33);

        set("max_qi", 20000);
        set("max_jing", 20000);
        set("neili", 30000);
        set("max_neili", 30000);
        set("jiali", 100);

        set("combat_exp", 50000000);

        set("inquiry", ([
                "獨孤九劍" : "我把天下武功的變化歸結在九劍之中，算不得是劍法，若拘\n"
                             "泥于形勢就無法理解其中奧妙。\n"
                             "獨孤九劍真正的精妙之處不在于其劍招，而是其" HIY "劍意" NOR + CYN "。",
                "劍意"     : "劍招乃其形，而劍意乃其神，吾花費畢生經歷于華山一山洞\n"
                             HIY"空室" NOR + CYN"中參悟出獨孤九劍之劍意，並將其筆錄在「" HIY "獨孤九劍殘"
                             "本" NOR + CYN"」" NOR + CYN "內。\n" NOR,
                "空室"     : "穿過我身後的山洞就會發現一個峭壁，我將殘本藏于其間的\n"
                             "山洞內，並請高手匠人設計出六把不同鎖將其鎖住，每把瑣"
                             "連接著一個開鎖\n的機關，機關藏于六個不同的石室內，須得"
                             "將所有" HIY "鎖" NOR + CYN "打開方能進入空室。\n" NOR,
                "鎖"       : "年深日久，開鎖的方法我已不記得了。我只記得如果石門\n"
                             "上的六把火炬都點燃了，石門上的鎖也就開了。\n",
                "無招勝有招" : "那就是獨孤九劍的最高境界！\n",
                "獨孤九劍殘本" : "如果你能拿來給話我到是可以把獨孤九劍中的精妙之處傳\n授于你。\n",
                "評價"     : (: ask_opinion :),
                "opinion"  : (: ask_opinion :),
                "武學修養" : "武學修養(martial-cognize)乃武術大義，可謂是以一通通百通！",
                "任務"     : "獨孤求敗嘆了口氣，道：“如今江湖上危機四伏，我正道人士還有很多事情要去做啊！”\n",
                "maze"     : (: ask_maze :),
                "迷宮"     : (: ask_maze :),
        ]));

        set_skill("unarmed", 500);
        set_skill("sword", 500);
        set_skill("blade", 500);
        set_skill("staff", 500);
        set_skill("hammer", 500);
        set_skill("club", 500);
        set_skill("whip", 500);
        set_skill("dagger", 500);
        set_skill("throwing", 500);
        set_skill("parry", 500);
        set_skill("dodge", 500);
        set_skill("force", 500);
        set_skill("never-defeated", 500);
        set_skill("martial-cognize", 500);

        map_skill("sword", "never-defeated");
        map_skill("blade", "never-defeated");
        map_skill("staff", "never-defeated");
        map_skill("hammer", "never-defeated");
        map_skill("club", "never-defeated");
        map_skill("whip", "never-defeated");
        map_skill("dagger", "never-defeated");
        map_skill("parry", "never-defeated");
        map_skill("dodge", "never-defeated");
        map_skill("force", "never-defeated");

        set("opinion/ultra",  1);
        set("opinion/master", 1);

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: check_weapon :),
        }) );

        set("rank_info/self", "在下");

        setup();
        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/clone/weapon/zhujian")->wield();

        set("startroom", "/d/huashan/shandong");
        check_clone();
}

void init()
{
        object me;

        if (! interactive(me = this_player()))
                return;

        delete_temp("want_opinion", me);
        if (ultrap(me))
        {
                message_vision(CYN "$N" CYN "微微一笑，對$n"
                               CYN "點了點頭。\n" NOR,
                               this_object(), me);
        }

        add_action("give_quest", "quest");
        add_action("give_up", "giveup");
}

mixed ask_maze()
{
        object me;
        object ob;
        mapping quest;
        mapping maze;

        me = this_player();
        ob = this_object();
        quest=query("quest_dg", me);

        if (!quest)
                return "你並沒有接我的任務，找我問迷宮的事情幹什麼？";

        if ( undefinedp(quest["maze"]) )
                return "你接的任務跟迷宮無關啊，湊什麼熱鬧呢？";

        /* 取消老的迷宮
        maze = MAZE_D->query_maze(quest["maze"]);
        if ( !mapp(maze) || undefinedp(maze["entry"]) )
        */
        if( !(find_object("/f/ultra/"+query("id", me)+"/maze/exit")) )
                return "你的任務看來是無法完成啦，那個迷宮據說已經消失了。";

        message_vision("$N對$n點頭道：“既然你已經準備好要去那裡，那就祝你一切順利！”\n", ob, me);
        FUBEN_D->enter_fuben(me, "ultra");

        return 1;
}

void check_weapon()
{
        if (objectp(query_temp("weapon")))
                return;

/*
        message_vision(CYN "$N" CYN "長嘆一口氣道：我$N"
                       CYN "多年來兵器還從未離過手，罷！罷"
                       "了！我去也！\n" NOR, this_object());
        destruct(this_object());
*/
}

mixed ask_opinion()
{
        object me;
        object ob;

        me = this_player();

        if( query("combat_exp", me)<200000 )
                return "呵呵，你這點武功還談什麼評價？";

        if( query("opinion/"MY_OPINION, me) == ULTRA_OPINION )
                return "哈哈，你兵器方面的修為已經稱得上是宗師了！咱們要不要過過招？";

        if (is_fighting(me))
                return "哈哈，廢什麼話，打贏了我，你自己給自己評價吧！";

        if (me->is_fighting())
                return "你等會兒吧！待我趕走他們。";

        if (objectp(ob = query_temp("opinion")))
        {
                if (ob == me)
                {
                        command("say 你著什麼急？不要煩我。");
                        return 1;
                }

                message_vision(CYN "$N" CYN "正在沉思，沒有回答$n"
                               CYN "，只是擺了擺手。\n" NOR,
                               this_object(), me);
                return 1;
        }

        switch(query_temp("want_opinion/dugu", me) )
        {
        case 0:
                command("look"+query("id", me));
                command("say 好吧，你用兵器攻我一招，我看看你的水平如何。");
                break;
        case 1:
                command("say 不是說讓你來一招我看看嗎？");
                break;
        case 2:
                message_vision(CYN "$N" CYN "皺眉對$n" CYN
                               "道：“我看你這人是夠羅嗦的。”\n" NOR,
                               this_object(), me);
                break;
        case 3:
                command("say 給我閉上你的嘴！");
                return 1;
        }

        addn_temp("want_opinion/dugu", 1, me);
        return 1;
}

int calc_level(object me, string skill)
{
        int lvl;
        string sp;
        mapping action;

        lvl = me->query_skill(skill, 1) / 2;
        sp = me->query_skill_mapped(skill);
        if (! sp) return lvl;

        lvl += me->query_skill(sp, 1);
        action=SKILL_D(sp)->query_action(me,query_temp("weapon", me));
        if (mapp(action))
                lvl += (action["force"] + action["parry"] + action["dodge"] - 250) / 10;
        return lvl;
}

void do_congration(object me)
{
        command("chat 這位" + RANK_D->query_respect(me) +
                "可要善自珍重，須知強中更有強中手。");
}

int accept_hit(object me)
{
        if( query_temp("want_hit/dugu", me) >= 2 )
        {
                command("heng");
                command("say 事不過三，你要找死那就去死吧！");
                kill_ob(me);
                return 1;
        }

        command("shake");
        command("say 這位" + RANK_D->query_respect(me) + "，"
                "練武之人切忌貿然挑舋。");
        addn_temp("want_hit/dugu", 1, me);
        return 0;
}

int accept_fight(object me)
{
        object weapon;

        if( query("opinion/"MY_OPINION, me) == ULTRA_OPINION )
        {
                message_vision(CYN "$N" CYN "大喜，對$n" CYN
                               "道：“很好，近年我還沒有和宗"
                               "師高手過過招，來吧！”\n" NOR,
                               this_object(), me);
                return 1;
        }

        if( !query_temp("want_opinion/dugu", me) )
        {
                command("say 平白無故動什麼手？");
                return 0;
        }

        if( !objectp(weapon=query_temp("weapon", me)) )
        {
                command("say 沒兵器你動什麼手？");
                return 0;
        }

        if( query("qi", me)*100/query("max_qi", me)<80 ||
            query("jing", me)*100/query("max_jing", me)<80 )
        {
                command("say 你現在狀態不佳，等休息好了再說吧！");
                return 0;
        }

        command("nod");
        COMBAT_D->do_attack(me, this_object(), weapon);
        COMBAT_D->do_attack(this_object(), me, query_temp("weapon"));

        if( query("qi", me) <= 0 )
        {
                message_vision(CYN "\n$N" CYN "搖搖頭對$n" CYN
                               "道：“你現在的武功還差得遠，連"
                               "我一招都接不住！”\n" NOR,
                               this_object(), me);
                return notify_fail("看來要好好的修煉功夫了。\n");
        }

        call_out("check_opinion", 2, me);
        set_temp("opinion", me);
        delete_temp("want_opinion", me);
        message_vision(CYN "\n$N" CYN "點點頭道：“好了，你先等"
                       "會兒，待我想想。”\n" NOR,
                       this_object(), me);
        return notify_fail("看來不能心急，還得等一會兒。\n");
}

int accept_kill(object me)
{
        if( query("combat_exp", me)<500000000 )
        {
                message_vision(CYN "$N" CYN "大怒道：“無名小輩搗"
                               "什麼亂？給我滾！”說罷一掌把$n" CYN
                               "劈倒在地。\n" NOR, this_object(), me);
                me->unconcious();
                return -1;
        }
        command("sigh");
        command("say 很好！近年還真沒有遇到什麼敢和我較量的高手！");
        return 1;
}

int recognize_apprentice(object me, string skill)
{
        if( query("character", me) != "狡黠多變" &&
            query("character", me) != "國士無雙" )
        {
                command("say 我看你的性格不夠機智靈活，不適宜"
                        "向我學習武功，還是算了吧！");
                return -1;
        }

        if (skill == "martial-cognize")
                return 1;

        if (! ultrap(me))
        {
                command("say 想學我的不敗神功？你還不夠資格，"
                        "等你成了大宗師再說吧！");
                return -1;
        }

        if (me->query_skill(skill, 1) >= 180)
        {
                command("say 夠了！我就教你到這裡吧，武功還是"
                        "要靠自己多研究才是！");
                return -1;
        }

        if (skill != "never-defeated")
                return 1;

        if( query_temp("can_learn/dugu/never-defeated", me) )
                return 1;


        set_temp("can_learn/dugu/never-defeated", 1, me);
        command("nod");
        command("say 我可以教你我多年領悟出來的不敗神功，可是"
                "你能不能學，還要看你的機緣了！");
        return 1;

        return -1;
}

void unconcious()
{
        /*
        message("vision", "\n"HIR + name() + "臉色一變，吐了一口鮮"
                "血，身形一閃，消逝不見。\n\n" NOR, environment());
        command("chat 罷！罷！罷！在下去也！");
        destruct(this_object());
        */
        full_self();
        return;
}

void die()
{
        /*
        message("vision", "\n"HIR + name() + "大叫一聲，狂吐了一口鮮"
                "血，身形一閃，就此不見。\n\n" NOR, environment());
        command("chat 在下去也！");
        destruct(this_object());
        */
        full_self();
        return;
}

int give_quest()
{
        mapping questtemp, questgoods, questdg;
        mapping skills, robot_quest;
        string msg, dest, error, dgmsg, place;
        object ob, npc, thing;
        int time, bonus, level, i, lev, lev1;
        int exp;
        int all_lvl, lvl;
        object maze_target;
        object maze_object;

        ob = this_player();
        exp=query("combat_exp", ob);

        if( (query("character", ob) != "光明磊落") &&
            (query("character", ob) != "國士無雙") &&
            (query("character", ob) != "狡黠多變") )
        {
                write("獨孤求敗看了你一眼，道：“你本性殺氣太重，跟我等相處日久必然格格不入，你還是另找他人去吧！”\n");
                return 1;
        }
        /*
        if( query("shen", ob)<0 )
        {
                write("獨孤求敗對你冷冷道：“道不同，不相為謀，你還是請便罷！”\n");
                return 1;
        }
        */
        if (exp < 500000)
        {
                write("獨孤求敗看了看你，輕撫白須，道：“江湖險惡，你還是先練好基本功吧。”\n");
                return 1;
        }

        if( mapp(query("quest_dg", ob)) )
        {
                write("獨孤求敗拍了拍你的肩膀，呵呵笑道：“不要急，先將手頭的做完再說。”\n");
                return 1;
        }

        if( mapp(query("quest_hs", ob)) )
        {
                write("獨孤求敗拍了拍你的肩膀，呵呵笑道：“黃裳那老家伙給你任務了？先去把它完成吧！”\n");
                return 1;
        }


        if( !wizardp(ob) && (time()-query("questdg_giveup_time", ob))<30 )
        {
                write("不要急，慢一點嘛。\n");
                return 1;
        }

        /*if( query("questdg_times", ob)<3
         || (query("questdg_times", ob)>5 && random(20) == 5) )
        */
        if( wizardp(ob) )
        {
                X_QuestD->query_quest(ob, this_object());
                return 1;
        }

        if (random(4) + 1)
        {
                // 以下給任務
                if(exp <= 600000)        level = 0;
                else if(exp <= 900000)   level = 1;
                else if(exp <= 1200000)  level = 2;
                else if(exp <= 1800000)  level = 3;
                else if(exp <= 2500000)  level = 4-random(3);
                else if(exp <= 3200000)  level = 5-random(3);
                else if(exp <= 4000000)  level =6-random(3);
                else
                {
                        if(random(15)==0||(exp>10000000&&random(10)==0))
                                level = 8;
                        else level = 7 - random(3);
                }
                if (level != 8)
                {
                        if (exp > 4000000)
                        {
                                all_lvl = 0;
                                lvl = random(28) + 1;
                                for (i = 1;i < 8;i ++)
                                {
                                        all_lvl += i;
                                        if (lvl > all_lvl - i && lvl <= all_lvl)
                                        {
                                                lvl = i;
                                                break;
                                        }
                                }
                        } else lvl = level;
                        while(1)
                        {
                                questtemp = QUESTDG_D(lvl)->query_questdg(ob);
                                if (questtemp["type"] == "殺" || questtemp["type"] == "擒")
                                {
                                    if (! get_object(questtemp["object"])->is_master())
                                        break;
                                } else
                                        break;
                        }
                }
                if (level == 8)
                {
                        npc = new(CLASS_D("generate") + "/player_npc.c");
                        FUBEN_D->clear_fuben("ultra",query("id", ob));
                        maze_object=get_object("/f/ultra/"+query("id", ob)+"/maze");
                        maze_object->set_maze_boss(npc);
                        //maze_target = MAZE_D->create_maze(npc);
                        maze_target=get_object("/f/ultra/"+query("id", ob)+"/maze/exit");
                        npc->move(maze_target);
                        /*
                        NPC_D->place_npc(npc,query("combat_exp", ob)<500000?({"大理一帶","終南山","關外","西域"}):
                                              query("combat_exp", ob)<800000?({"大理一帶","終南山","西域"}):({"大理一帶","西域"}));
                        */
                        npc->set_from_me(ob, 1);
                        addn_temp("apply/attack", npc->query_skill("force")/3, npc);
                        addn_temp("apply/dodge", npc->query_skill("force")/3, npc);
                        addn_temp("apply/parry", npc->query_skill("force")/3, npc);
                        addn_temp("apply/damage", 200+random(100), npc);
                        addn_temp("apply/unarmed_damage", 200+random(100), npc);
                        addn_temp("apply/armor", 200+random(300), npc);
                        set_temp("quester",query("id",  ob), npc);
                        set("auto_perform", 1, npc);
                        /*
                        NPC_D->random_move(npc);
                        NPC_D->random_move(npc);
                        NPC_D->random_move(npc);

                        place=query("place", npc);
                        */
                        set("shen", -20000, npc);
                        /*
                        msg = "獨孤求敗面色凝重道：“" + npc->name(1) +
                              "居然又重現江湖，你速去除了這一害，\n此人可能會在" + place +
                              "附近，慢了就找不到了。”\n",
                        */
                        msg = "獨孤求敗面色凝重道：“"+npc->name(1)+
                              "居然又重現江湖，你速去除了這一害，\n此人喜歡躲在迷宮(maze)中，慢了就找不到了。”\n",

                        questtemp = ([
                                //"maze" : maze_target->query("maze/mazename"),
                                "maze" : maze_object,
                                "name" : npc->name(1),
                                "id":query("id", npc),
                                "bonus": (200+random(51)),
                                "type" : "殺",
                                "level" : level,
                                //"chinese_w" : place,
                                //"where" : npc->query("startroom"),
                                "where": maze_target,
                                "dgmsg" : msg,
                                "object" : base_name(npc),
                        ]);
                        tell_object(ob, questtemp["dgmsg"] + "\n");
                        set("quest_dg", questtemp, ob);

                        return 1;
                }
                else
                {
                        switch(questtemp["type"])
                        {
                        case "殺":
                                if( query("race", get_object(questtemp["object"])) != "人類" )
                                {
                                        questtemp["type"] = "擒";
                                        msg = dg_msg[random(sizeof(dg_msg))] + replace_string(qin_msg1[random(sizeof(qin_msg1))],"name",questtemp["name"]) + qin_msg2[random(sizeof(qin_msg2))];
                                        break;
                                }
                                if(undefinedp(msg = questtemp["msg1"])||msg==""||random(2))
                                {
                                        if(questtemp["race"])
                                                msg=DGMSG_D->query_dgmsg("宰",questtemp["name"]);
                                        else
                                                msg=DGMSG_D->query_dgmsg("殺",questtemp["name"]);
                                }
                                break;
                        case "尋":
                                if(undefinedp(msg = questtemp["msg"])||msg==""||random(2))
                                        msg=DGMSG_D->query_dgmsg("尋",questtemp["name"]);
                                break;
                        case "擒":
                                if( query("race", get_object(questtemp["object"])) != "人類" )
                                {
                                        msg = dg_msg[random(sizeof(dg_msg))] + replace_string(qin_msg1[random(sizeof(qin_msg1))],"name",questtemp["name"]) + qin_msg2[random(sizeof(qin_msg2))];
                                        break;
                                }
                                if(undefinedp(msg = questtemp["msg2"])||msg==""||random(2))
                                {
                                        if(questtemp["race"])
                                                msg=DGMSG_D->query_dgmsg("捉",questtemp["name"]);
                                        else
                                                msg=DGMSG_D->query_dgmsg("擒",questtemp["name"]);
                                }
                                break;
                        case "送":
                                npc = new(CLASS_D("generate") + "/dg_receiver.c");
                                FUBEN_D->clear_fuben("ultra",query("id", ob));
                                maze_object=get_object("/f/ultra/"+query("id", ob)+"/maze");
                                maze_object->set_maze_boss(npc);
                                maze_target=get_object("/f/ultra/"+query("id", ob)+"/maze/exit");
                                //maze_target = MAZE_D->create_maze(npc);
                                npc->move(maze_target);
                                /*
                                NPC_D->place_npc(npc,query("combat_exp", ob)<500000?({"大理一帶","終南山","關外","西域"}):
                                                      query("combat_exp", ob)<800000?({"大理一帶","終南山","西域"}):({"大理一帶","西域"}));
                                */
                                NPC_D->set_from_me(npc, ob, 100);
                                set_temp("quester",query("id",  ob), npc);
                                /*
                                NPC_D->random_move(npc);
                                NPC_D->random_move(npc);
                                NPC_D->random_move(npc);
                                */
                                //place = npc->query("place");
                                thing = new(questtemp["object"]);
                                if (! objectp(thing))
                                        log_file("static/Non_things", sprintf("無法找到物品 %s\n", questtemp["object"]));
                                set("send_to",query("id",  npc), thing);
                                set("send_from", query("id"), thing);
                                set("send_from_name", query("name"), thing);
                                msg = dg_msg[random(5)]+"麻煩你幫我將"+thing->name(1)+"送至"+npc->name(1)+"處，"
                                                "他現在正在迷宮中，誤了時間他可能就離開了。";
                                /*
                                msg = dg_msg[random(5)]+"麻煩你幫我將"+thing->name(1)+"送至"+npc->name(1)+"處，"
                                                "他現在正在"+place+"，誤了時間他可能就離開了。";
                                */
                                if (!thing->move(ob))
                                {
                                        thing->move(environment(this_object()));
                                        message_vision("獨孤求敗將$N輕輕放在地上。\n",thing);
                                } else message_vision("獨孤求敗將$N交給$n。\n",thing,ob);
                                break;
                        }
                        questdg=([
                                "name":questtemp["name"],
                                "type":questtemp["type"],
                                "bonus":questtemp["bonus"],
                                "object":questtemp["object"],
                                "dgmsg":msg,
                        ]);
                }
        }
/*
        if (questdg["type"] == "殺" && (random(6) == 2 || wizardp(ob)))
        {
                robot_quest = ANTI_ROBOT->get_question();
                msg = "獨孤求敗鄭重說道：“我剛將我們組織的口令更改了一下，你去通知一下" + questdg["name"] + NOR"，新口令是：\n";
                msg += robot_quest["question"];
                msg += "你只需要將口令用"HIR"普通的數字形式"NOR"傳送過去就行了，傳送的指令是：whisper。\n";
                questdg["type"]   = "傳";
                questdg["dgmsg"]  = msg;
                questdg["answer"] = robot_quest["answer"];
        }
*/

        tell_object(ob, questdg["dgmsg"]+"\n");
        questdg["level"]=level;
        if (questdg["type"] == "送")
        {
                questdg["obj"] = thing;
                questdg["send_to"]=query("send_to", thing);
                if (maze_object)
                        questdg["maze"] = maze_object;
        }
        set("quest_dg", questdg, ob);
        return 1;
}


int accept_object(object who, object ob)
{
        int exp, pot,level,bonus,time,times;
        int i,quest_count,mar,score,weiwang,all_quest_dg;
        int total_count;
        mapping questdg;
        string dest,msg;
        object gold,obj;
        mixed special = 0;
        mixed money = 0;
        mapping my;

        if (base_name(ob) == "/clone/lonely/book/dugubook")
        {
                if (who->query_skill("lonely-sword", 1) < 340)
                {
                        command("shake");
                        command("say 可惜，可惜！你獨孤九劍還不夠熟練，還無法領悟獨孤九劍的精妙之處！");
                        destruct(ob);
                        return 1;
                }

                if( query("lonely-sword/nothing", who) )
                {
                        command("nod");
                        command("say 你已經領悟了獨孤九劍之精髓，下去好好練習吧！");
                        destruct(ob);
                        return 1;
                }

                // 開始傳授獨孤九劍之無招
                command("nod");
                command("say 不錯，不錯！既然如此，我就將獨孤九劍之精髓傳授于你。");
                command("say 獨孤九劍最精妙之處已經不是招式，而是一種" HIY "境界" NOR + CYN "！");
                command("say 獨孤九劍講究後發制人，不拘泥于任何招式，隨心而發，隨心而收，達到一\n"
                        "種" HIY "無招勝有招" NOR + CYN "的境界！");
                command("say 明白了？");

                set("lonely-sword/nothing", 1, who);

                if (who->can_improve_skill("sword"))
                        who->improve_skill("sword", 1500000);
                if (who->can_improve_skill("sword"))
                        who->improve_skill("sword", 1500000);
                if (who->can_improve_skill("sword"))
                        who->improve_skill("sword", 1500000);
                if (who->can_improve_skill("lonely-sword"))
                        who->improve_skill("lonely-sword", 1500000);
                if (who->can_improve_skill("lonely-sword"))
                        who->improve_skill("lonely-sword", 1500000);
                if (who->can_improve_skill("lonely-sword"))
                        who->improve_skill("lonely-sword", 1500000);
                who->improve_skill("martial-cognize", 1500000);
                who->improve_skill("martial-cognize", 1500000);
                who->improve_skill("martial-cognize", 1500000);

                tell_object(who, HIG "你學會了獨孤九劍之「無招」。\n" NOR);

                destruct(ob);
                return 1;
        }

        if( !(questdg=query("quest_dg", who)) )
        {
                tell_object(who,"獨孤求敗看了看你，似乎不知道你是什麼意思。\n");
                return notify_fail("獨孤求敗淡淡一笑，道：“我可不缺什麼東西。”\n");
        }

        if( query("money_id", ob) )
        {
                if (ob->value() < 1000000)
                {
                        tell_object(who,"獨孤求敗對你語重心長的說：你拿這麼點錢來幹什麼呢？我又不是缺錢花。\n");
                        return notify_fail("獨孤求敗搖搖頭：如果給個100兩黃金，或許我就消除了你的任務。\n");
                }
                delete("quest_dg", who);
                tell_object(who,"獨孤求敗盯著" + ob->name(1) + "注視良久，嘆氣道：那你這個任務不做就算了吧。\n");
                destruct(ob);
                return 1;
        }

        if(questdg["type"] != "尋" && questdg["type"] != "擒" && questdg["type"] != "送")
        {
                tell_object(who,"獨孤求敗看了看你，似乎不知道你是什麼意思。\n");
                return notify_fail("獨孤求敗淡淡一笑，道：“我可不缺什麼東西。”\n");
        }

        if( ob->name(1) != questdg["name"] || userp(ob))
        {
                tell_object(who,"獨孤求敗嘆了口氣，道：這並不是我想要的。\n");
                return notify_fail("獨孤求敗看著你，道：“你是不是再去找找看啊？”\n");
        }

        if(questdg["type"]=="送")
        {
                if( !ob->is_receipt() || query("reply_to", ob) != query("id", this_object()) )
                {
                        write("獨孤求敗接過來一看，驚訝的說：“我不是叫你幫我送東西了麼，你是不是記錯了？”\n");
                        return 0;
                }
                if( query("reply_by", ob) != questdg["send_to"] )
                {
                        write("獨孤求敗接過來一看，生氣的說：“這張回執是誰給你的？別想來糊弄我！”\n");
                        return 0;
                }
                if( query("receive_from", ob) != query("id", who) )
                {
                        write("獨孤求敗接過來一看，生氣的說：“這張回執是你自己得到的麼？別想來糊弄我！”\n");
                        return 0;
                }
        }

        if( userp(ob) || query("user", ob) ||
            ob->is_item_make() ||
            ob->query_save_file())
        {
                write("獨孤求敗大怒道：“好你個小子，竟然想蒙騙本宗師！來人！把他給我抓起來！”\n");
                who->get_into_prison(this_object(), 0, 30);
                log_file("static/QUEST_DIJIAO",sprintf("%s(%s)(獨孤任務)制造%s(%s)(%s)作弊\n",query("name", who),
                query("id", who),ob->name(),query("id", ob),ctime(time())));
                return 1;
        }

        // message_vision("$N將$n交給獨孤求敗。\n",who,ob); 與give信息重復
        tell_object(who,"獨孤求敗點頭微笑，其意頗為嘉許，道：“不錯！不錯！”\n");
        delete("quest_dg", who);
        if( ob->is_character() && query("startroom", ob) )
        {
                my = ob->query_entire_dbase();
                my["jing"]   = my["eff_jing"]   = my["max_jing"];
                my["jingli"] = my["eff_jingli"] = my["max_jingli"];
                my["qi"]     = my["eff_qi"]     = my["max_qi"];
                my["neili"]  = my["max_neili"];
                if(! living(ob))
                        ob->revive();
                ob->clear_condition();
                ob->remove_all_killer();
                if (! ob->return_home(query("startroom", ob)) )
                        ob->move(query("startroom", ob));
        } else destruct(ob);

        level = questdg["level"]+1;
        if( (i=query("questdg_times", who))<8 )
                i = 15-i;
        else i = 1;

        exp = level*105 + questdg["bonus"]*3;
        exp+=query("questdg_times", who);
        exp += random(exp/2);
        exp /= i;

        if (questdg["type"] == "擒")
        exp += exp/5;
        pot = exp/(2+random(2));
        score = random(exp/20);
        weiwang = random(exp/15);

        if( query("questdg_times", who)+1>200 )
               mar=exp/5+random(query("questdg_times", who));
        else mar = 20 + random(20);

        if (mar > 1000) mar = 1000;

        if(wizardp(who)||!random(10))
        {
                i=(exp/60+1);
                if(i>30) i=30;
                gold=new("/clone/money/gold");
                gold->set_amount(i);
                tell_object(who,"接著說道：“整日行走江湖，手頭有點緊吧？！喏，拿點黃金做盤纏吧！”\n"
                        HIW"\n你被獎勵了 "+i+" 兩黃金。\n");
                if(!gold->move(who))
                {
                        message_vision("但是$N身上東西太重，黃金一下子掉到了地上。\n",who);
                        gold->move(environment());
                }
                GIFT_D->bonus(who, ([ "exp" : exp*3/2, "pot" : pot, "mar" : mar,
                                      "weiwang" : weiwang, "score" : score, "percent" : 100 ]), 1);
        }
        else
                GIFT_D->bonus(who, ([ "exp" : exp*3/2, "pot" : pot, "mar" : mar, "percent" : 100,
                                      "weiwang" : weiwang, "score" : score ]), 1);

        // who->add("questdg_times",1);
        addn("total_hatred", -5, who);
        if( query("total_hatred", who)<0)set("total_hatred", 0, who);


        quest_count=query("questdg_times", who)+1;
        total_count = quest_count % 500;
        if (total_count == 50)
        {
                msg = "$N呵呵笑了兩聲道：“你還可以，連著"+chinese_number(quest_count)+
                      "次任務都完成的漂漂亮亮，繼續努力！”\n";
                special = 1;
        } else
        if (total_count == 100)
        {
                msg = "$N笑的合不攏嘴，看了你一眼道：“有志氣！"+chinese_number(quest_count)+
                      "次任務幹得幹凈利索！”\n";
                special = "/clone/gift/puti-zi";
        } else
        if (total_count == 150)
        {
                msg = "$N嘆道：“真是長江後浪推前浪，想不到你接連"+chinese_number(quest_count)+
                      "次任務都無一疏漏，不易，不易！”\n";
                money = 1;
        } else
        if (total_count == 200)
        {
                msg = "$N嘆道：“真是長江後浪推前浪，想不到你接連"+chinese_number(quest_count)+
                      "次任務都無一疏漏，不易，不易！”\n";
                money = 1;
        } else
        if (total_count == 250)
        {
                msg = "$N嘆道：“真是長江後浪推前浪，想不到你接連"+chinese_number(quest_count)+
                      "次任務都無一疏漏，不易，不易！”\n";
                money = 1;
        } else

        if (total_count == 300)
        {
                msg = "$N嘆道：“真是長江後浪推前浪，想不到你接連"+chinese_number(quest_count)+
                      "次任務都無一疏漏，不易，不易！”\n";
                special = "/clone/gift/tianxiang";
        } else
        if (total_count == 350)
        {
                msg = "$N嚇了一跳：“看來你真的很適合學武，竟接連"+chinese_number(quest_count)+
                      "次任務都無一疏漏，不易，不易！”\n";
                special = "/clone/gift/tianxiang";
        } else
        if (total_count == 400)
        {
                msg = "$N嘆道：“真是一個武學天才啊，想不到你接連"+chinese_number(quest_count)+
                      "次任務都無一疏漏，不易，不易！”\n";
                special = "/clone/gift/jiuzhuan";
        } else
        if (total_count == 450)
        {
                msg = "$N大聲叫起來：“天才！真是天才，真有人連續"+chinese_number(quest_count)+
                      "次任務都無一疏漏，不易，不易！”\n";
                special = "/clone/gift/jiuzhuan";
        } else
        if (total_count == 0)
        {
                msg = "$N深深嘆了口氣，道：“沒想到你連著"+chinese_number(quest_count)+
                      "次任務無一失手，看來以後就是你們這些人挑大樑啦！”\n";
                special = "/clone/gift/jiuzhuan";
#ifdef DB_SAVE
                if( MEMBER_D->is_valid_member(query("id", who)) )
                {

                        if( query("special_skill/sophistry", who) )
                        {
                        if (quest_count >= 5000)
                                        quest_count = 0;
                        } else {
                        if (quest_count >= 2000)
                                        quest_count = 0;
                        }
                } else {
#endif
                        if (quest_count >= 1000)
                                quest_count = 0;
#ifdef DB_SAVE
                }
#endif
        } else
        if ((total_count % 10) == 0)
        {
                msg = "$N呵呵笑著：“你表現很不錯啊，居然連著" +
                      chinese_number(quest_count) +
                      "次都沒有失手，別忙著練，慢慢來。”\n";
        }

        set("questdg_times", quest_count, who);

        if (special)
        {
                // message_vision(msg, this_object(), who);
                GIFT_D->special_bonus(this_object(), who, special);
        }
        if (money)
        {
                // message_vision(msg, this_object(), who);
                QUEST_D->money_bonus(this_object(), who, money);
        }

        // 記錄完成任務的次數（不要求連續），如果滿1000次則獎勵瑪瑙殘片
        all_quest_dg=query("all_quest_dg", who);
        if (!all_quest_dg) all_quest_dg = 0;
        all_quest_dg += 1;
        if (all_quest_dg == 1000)
        {
                obj = new("/clone/tessera/gem.c");
                tell_object(who,this_object()->name() + "又對你點了點頭：你已經從我這裡接了一千個任務，我這裡正好\n" +
                        "有個"+query("name", obj)+"，就獎給你了！\n");
                if (!obj->move(who))
                        obj->move(environment());
                set("all_quest_dg", 0, who);
                FAMILY_D->add_family_fame(who, 20 + random(5));
                LEAGUE_D->add_league_fame(who, 20 + random(5));
                BUNCH_D->add_bunch_fame(who, 20 + random(5));
        }else set("all_quest_dg", all_quest_dg, who);
        return -1;
}

int give_up()
{
        object ob,obj,room;
        mapping questdg;

        ob = this_player();

        if( mapp(questdg=query("quest_dg", ob)) )
        {
                write("你滿臉羞慚，請求獨孤求敗取消自己的任務。\n");
                /*
                if (questdg["type"] == "傳")
                {
                        message_vision("$N驚訝地對$n笑笑：『傳口令，這個是很簡單的任務啊！不要著急，回頭再好好想想，努力把它完成！\n",this_object(),ob);
                        return 1;
                }
                */
                write("獨孤求敗和顏悅色地拍拍你的腦袋，道：“沒關系，要繼續努力啊！”\n");
                if(questdg["type"] == "送")
                {
                        if( query("questdg_times", ob)>0 )
                                addn("questdg_times", -1, ob);
                }
                else if(questdg["type"] == "殺"&&questdg["level"] == 8)    //by llm
                {
                        set("questdg_times", 0, ob);
                }
                else
                        set("questdg_times", 0, ob);

                if ( stringp(questdg["maze"]) )
                {
                        //MAZE_D->remove_maze(questdg["maze"]);
                        FUBEN_D->clear_fuben("ultra",query("id", ob));
                }

        }
                /*
                if(questdg["type"] == "送")
                {
                        if(objectp(obj = questdg["obj"]))
                        {
                                if(obj->is_character())
                                        message_vision("$N一躍而起，跑得無影無蹤了。\n",obj);
                                obj->move(environment(ob));
                                destruct(obj);
                                if( query("questdg_times", ob)>0 )
                                        addn("questdg_times", -1, ob);
                        }
                }
                else
                if(questdg["type"] == "殺"&&questdg["level"] == 8)    //by llm
                {
                        if(!(room = find_object(questdg["where"])) )
                                room = load_object(questdg["where"]);

                        if(objectp(obj = present(questdg["id"],room))
                                &&obj->is_character()
                                &&!userp(obj))
                        {
                                message_vision("$N哼了一聲，轉身走開了。\n",obj);
                                obj->move("/d/wizard/wizard_room");
                                destruct(obj);
                        }
                        set("questdg_times", 0, ob);
                }
                else
                        set("questdg_times", 0, ob);
        }
        */
        else
                write("獨孤求敗和顏悅色地看著你，道：“沒關系，你現在根本就沒有任務啊！”\n");
        delete("quest_dg", ob);
        set("questdg_giveup_time", time(), ob);
        return 1;
}

string time_period(int timep)
{
        int t, d, h, m, s;
        string time;
        t = timep;
        s = t % 60;             t /= 60;
        m = t % 60;             t /= 60;
        h = t % 24;             t /= 24;
        d = t;

        if(d) time = chinese_number(d) + "天";
        else time = "";

        if(h) time += chinese_number(h) + "小時";
        if(m) time += chinese_number(m) + "分";
        time += chinese_number(s) + "秒";
        return time;
}

void destory(object ob)
{
        if(!ob)
                return;
        if(ob->is_character())
                message_vision("$N一躍而起，跑得無影無蹤了。\n",ob);
        ob->move("/d/wizard/wizard_room");
        destruct(ob);
        return ;
}

void npc_dest(object npc)
{
        if(!npc) return;
        if( npc->is_fighting() && query_temp("wait_times", npc)<4 )
        {
                addn_temp("wait_times", 1, npc);//4次機會
                call_out("npc_dest",60,npc);     //再等一分鐘
                return;
        }
        if(npc->is_character())
                message_vision("$N重重地哼了一聲：“看來都是膽小鬼”，轉身一晃，已不見了身影。\n",npc);
        npc->move("/d/wizard/wizard_room");
        destruct(npc);
        return ;
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "天地絕滅" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/never-defeated/juemie",
                           "name"    : "天地絕滅",
                           "sk1"     : "never-defeated",
                           "lv1"     : 120,
                           "sword"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "天打雷劈" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/never-defeated/lei",
                           "name"    : "天打雷劈",
                           "sk1"     : "never-defeated",
                           "lv1"     : 120,
                           "sword"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "破字訣" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/never-defeated/po",
                           "name"    : "破字訣",
                           "sk1"     : "never-defeated",
                           "lv1"     : 120,
                           "force"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "天花亂墜" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/never-defeated/tianhua",
                           "name"    : "天花亂墜",
                           "sk1"     : "never-defeated",
                           "lv1"     : 120,
                           "sword"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "晴空萬裡" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/never-defeated/wanli",
                           "name"    : "晴空萬裡",
                           "sk1"     : "never-defeated",
                           "lv1"     : 120,
                           "sword"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "御策訣" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/never-defeated/yuce",
                           "name"    : "御策訣",
                           "sk1"     : "never-defeated",
                           "lv1"     : 120,
                           "throwing"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        default:
                return 0;
        }
}
