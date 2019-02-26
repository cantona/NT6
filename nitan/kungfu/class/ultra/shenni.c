// shenni 南海神尼

#include <ansi.h>

inherit NPC;
inherit F_MASTER;
inherit F_NOCLONE;


#define ULTRA_OPINION   "宗師"
#define OPINION_TYPE    HIY "內家功夫" NOR
#define MY_OPINION      "force"

#define QUEST_SN_D(x)   ("/quest/questsn/quest/questsn" + x)
#define QUEST_WUGOOD_D  ("/quest/questsj/quest_sj")
#define SNMSG_D         ("/quest/questsn/quest/shenni-msg")
#define ANTI_ROBOT      "/kungfu/class/ultra/robot"

mixed ask_opinion();
int give_quest();
int give_up();
void destory(object ob);
string time_period(int timep);
mixed ask_maze();

string* sn_msg = ({
        "南海神尼微笑着説：“",
        "南海神尼閉着眼睛冥思片刻道：“",
        "南海神尼低頭想了想，説道：“",
        "南海神尼拍了拍手，説道：“",
        "南海神尼微微笑了笑道：“",
});

string* qin_msg1 = ({
        "動物是人們的朋友，就算name嚴重影響了生態環境，關起來也就可以了，",
        "我聽説name過多的繁殖，影響了當地的生態，不過還是不應該隨便殺動物，",
        "難道name也會給人類帶來麻煩？真是稀奇，我到是想看看它，",
        "我這裏的花園養着很多的動物，就是沒有name，",
        "在空閒的時候，看看動物的生活能夠放鬆情緒，name其實挺可愛的，",
        "獨孤求敗是一個很喜歡動物的人，尤其是name，用來送給他做禮物最好不過，",
        "江湖上打打殺殺的，少不了讓name也遭受無辜連累，我有心保護它，",
});

string* qin_msg2 = ({
        "你去把它帶到這裏來吧。”",
        "去找到它，把它帶來。”",
        "你能把它帶我這裏來麼？”",
        "你就辛苦一趟去幫我把它找來吧。”",
        "把它弄來給我。”",
});

string  *my_opinions = ({ "force" });

// 該頭文件必須在這裏嵌入
#include <ultra.h>

void create()
{
        set_name("南海神尼", ({ "nanhai shenni", "shenni", "nanhai" }) );
        set("title", HIG "大宗師" NOR);
        set("gender", "女性");
        set("age", 91);
        set("long", "這是一位青衫老尼，看不出有什麼不同。\n");
        set("attitude", "peaceful");
        set("class", "bonze");
        set("no_get", 1);
        set("str", 30);
        set("int", 37);
        set("con", 39);
        set("dex", 33);

        set("max_qi", 9999);
        set("max_jing", 9999);
        set("neili", 9999);
        set("max_neili", 9999);
        set("jiali", 70);

        set("combat_exp", 50000000);

        set("inquiry", ([
                "彈指神通" : "那是我碧海神功關於指法方面的變化，當年我到東海，曾經傳授給一人。",
                "評價"     : (: ask_opinion :),
                "opinion"  : (: ask_opinion :),
                "武學修養" : "好好提高自己的武學修養(martial-cognize)，到時候什麼武功都如小兒科！",
                "任務" : "本性兇狠但是立身正派的人，可以在我這裏領任務(quest)。\n",
                "迷宮"      : (: ask_maze :),
                "maze"      : (: ask_maze :),
        ]));

        set_skill("strike", 500);
        set_skill("finger", 500);
        set_skill("parry", 500);
        set_skill("dodge", 500);
        set_skill("force", 500);
        set_skill("staff", 500);
        set_skill("bluesea-force", 500);
        set_skill("martial-cognize", 500);
        set_skill("literate", 220);

        map_skill("parry", "bluesea-force");
        map_skill("force", "bluesea-force");
        map_skill("dodge", "bluesea-force");
        map_skill("finger", "bluesea-force");
        map_skill("strike", "bluesea-force");
        map_skill("staff", "bluesea-force");

        prepare_skill("finger", "bluesea-force");
        prepare_skill("strike", "bluesea-force");

        set("opinion/ultra",  1);
        set("opinion/master", 1);

        set("rank_info/self", "本座");

        setup();
        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/clone/weapon/zhubang")->wield();

        set("startroom", "/d/xiakedao/zhuwu2");
        check_clone();
}

void init()
{
        object me;

        if (! interactive(me = this_player()))
                return;

        delete_temp("want_opinion", me);
        if (ultrap(me))
                message_vision("$N眉角微微一動。\n", this_object(), me);
        add_action("give_quest", "quest");
        add_action("give_up","giveup");
}

mixed ask_maze()
{
        object me;
        object ob;
        mapping quest;
        mapping maze;

        me = this_player();
        ob = this_object();
        quest=query("quest_sn", me);

        if (!quest)
                return "你並沒有接我的任務，找我問迷宮的事情幹什麼？";

        if ( undefinedp(quest["maze"]) )
                return "你接的任務跟迷宮無關啊，湊什麼熱鬧呢？";
        /*
        maze = MAZE_D->query_maze(quest["maze"]);
        if ( !mapp(maze) || undefinedp(maze["entry"]) )
        */
        if( !(find_object("/f/ultra/"+query("id", me)+"/maze/exit")) )
                return "你的任務看來是無法完成啦，那個迷宮據説已經消失了。";

        message_vision("$N對$n點頭道：“既然你已經準備好要去那裏，那就祝你一切順利！”\n", ob, me);
        //me->move(maze["entry"]);
        FUBEN_D->enter_fuben(me, "ultra");

        return 1;
}

mixed ask_opinion()
{
        object me;
        object ob;

        me = this_player();

        if( query("combat_exp", me)<200000 )
                return "哼！你這點武功也出來丟人現眼？";

        if( query("opinion/"MY_OPINION, me) == ULTRA_OPINION )
                return "不必了，你內功方面的修為已經稱得上是宗師了！要是和貧尼過上幾招也不錯。";

        if (is_fighting(me))
                return "哈哈，廢什麼話，打贏了我，你自己給自己評價吧！";

        if (me->is_fighting())
                return "你等會兒吧！待我趕走他們。";

        if (objectp(ob = query_temp("opinion")))
        {
                if (ob == me)
                {
                        command("say 你着什麼急？不要煩我。");
                        return 1;
                }

                message_vision("$N頗為惱怒的對$n道：“沒看我正忙着嗎？”\n",
                               this_object(), me);
                return 1;
        }

        switch(query_temp("want_opinion/shenni", me) )
        {
        case 0:
                command("say 好吧，咱們過一招，比拚一下內力。");
                break;
        case 1:
                command("say 你準備好沒有？好了就來吧。");
                break;
        case 2:
                message_vision(CYN "$N" CYN "皺眉對$n" CYN
                               "道：“我看你這人是夠羅嗦的。”\n" NOR,
                               this_object(), me);
                break;
        case 3:
                command("say 快給我閉上你的鳥嘴！");
                return 1;
        }

        addn_temp("want_opinion/shenni", 1, me);
        return 1;
}

int calc_level(object me, string skill)
{
        int lvl;
        string sp;

        lvl = me->query_skill(skill, 1) / 2;
        sp = me->query_skill_mapped(skill);
        if (! sp) return lvl;

        lvl += me->query_skill(sp, 1);
        if( query("max_neili", me)>4000)lvl+=20;
        return lvl;
}

void do_congration(object me)
{
        command("chat 不錯，不錯，真是不錯。");
}

int accept_hit(object me)
{
        command("heng");
        command("say 好你個" + RANK_D->query_rude(me) + "，你找死找到這來了！");
        kill_ob(me);
        return 1;
}

int accept_fight(object me)
{
        object weapon;

        if( query("opinion/"MY_OPINION, me) == ULTRA_OPINION )
        {
                message_vision("$N對$n道：“很好，你也算是宗師高手了，"
                               "來吧！咱們比劃一下！”\n",
                               this_object(), me);
                return 1;
        }

        if( !query_temp("want_opinion/shenni", me) )
        {
                command("say 你幹什麼要和我動手？");
                return 0;
        }

        command("look "+query("id", me));

        COMBAT_D->do_attack(this_object(), me, 0);

        if( query("qi", me) <= 0 )
        {
                message_vision("\n$N搖搖頭對$n道：“你現在的武功"
                               "還差得遠，連我一招都接不住！”\n",
                               this_object(), me);
                return notify_fail("看來要好好的修煉功夫了。\n");
        }

        message_combatd("$N右掌伸出，正和$n手掌相對，兩人同時運起內力，"
                       "不一會兒只見二人頭上生起騰騰霧氣。\n忽然$N手掌"
                       "一撤、收回功力，沒有一點阻滯，不禁讓$n大為愕然。\n",
                       this_object(), me);
        if( query("neili", me)<3000 )
        {
                message_vision("$N搖搖頭對$n道：“適才你內力不足，我難"
                               "以衡量，待你將內力修煉好了再來吧！”\n",
                               this_object(), me);
                return notify_fail("看來還是回去鍛鍊一下內力吧！\n");
        }
        set("neili", 0, me);


        call_out("check_opinion", 2, me);
        set_temp("opinion", me);
        delete_temp("want_opinion", me);
        message_vision("\n$N一擺手道：“好了，待我想想。”\n",
                       this_object(), me);
        return notify_fail("看來不能心急，還得等一會兒。\n");
}

int accept_kill(object me)
{
        if( query("combat_exp", me)<500000000 )
        {
                message_vision("$N大怒道：“無名小輩搗什麼"
                               "亂？給我滾！”説罷一掌把$n劈倒在地。\n",
                               this_object(), me);
                me->unconcious();
                return -1;
        }
        command("sigh");
        command("say 很好！近年還真沒有遇到什麼敢和我較量的高手！");
        return 1;
}

int recognize_apprentice(object me, string skill)
{
        if( query("character", me) != "心狠手辣" && query("character", me) != "國士無雙" )
        {
                command("say 你這人生性不夠毒辣，下不了狠心，"
                        "我沒有興趣教你！");
                return -1;
        }

        if (skill == "martial-cognize")
                return 1;

        if (! ultrap(me))
        {
                command("say 想學我的碧海神功？你還不夠資格，"
                        "等你成了大宗師再説吧！");
                return -1;
        }

        if (me->query_skill(skill, 1) >= 180)
        {
                command("say 夠了！我就教你到這裏吧，武功還是"
                        "要靠自己多研究才是！");
                return -1;
        }

        if (skill != "bluesea-force")
                return 1;

        if( query_temp("can_learn/shenni/bluesea-force", me) )
                return 1;


        set_temp("can_learn/dugu/bluesea-force", 1, me);
        command("nod");
        command("say 不錯，我教你我的絕學碧海神功，能不能學，"
                "就看你的造化了！");
        return 1;

        return -1;
}

void unconcious()
{
        /*
        message("vision", "\n"HIR + name() + "臉色一變，吐了一口鮮"
                "血，身形一閃，消逝不見。\n\n" NOR, environment());
        command("chat 罷！罷！罷！貧尼去也！");
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
        command("chat 貧尼去也！");
        destruct(this_object());
        */
        full_self();
        return;
}

int give_quest()
{
    mapping quest,qgood,skills,robot_quest;
    object me,target,thing,npc,the_ob;
    int i, giveup,tag,want,lev,lev1,time;
    int exp;
    int lvl,all_lvl;
    string msg,*sname,place,the_race;
    object maze_target;
    object maze_object;

    me = this_player();
    exp=query("combat_exp", me);

    if( (query("character", me) != "陰險奸詐") && 
            (query("character", me) != "國士無雙") && 
            (query("character", me) != "心狠手辣") )
    {
        write("南海神尼搖頭道：你天性忠實厚道，恐怕接我任務會太過於心慈手軟，還是另找別人要任務吧。\n");
        return 1;
    }
    /*
    if( !(query("shen", me)>0) )
    {
        write("南海神尼看着你只是搖頭：“行走江湖，立身要正！雖然我講究以殺止殺，但是你邪氣太重，還是算了吧！”\n");
        return 1;
    }
    */
    if(exp < 500000)
    {
        write("南海神尼微笑着拍了拍你的腦袋：以你現在的經驗，接我任務實在太過危險，好好去歷練歷練，回頭再來找我。\n");
        return 1;
    }


    if( quest=query("quest_sn", me) )
    {
        write("南海神尼呵呵笑着説：心急可是喝不了熱粥啊，不要着急，慢慢來。\n");
        return 1;
    }

    if( mapp(query("quest_kh", me)) )
    {
        write("南海神尼微微一怔説：葵花太監不是給了你任務了麼？要不你還是先完成手頭的任務吧。\n");
        return 1;
    }


    giveup=query_temp("sn_giveup", me);
    if( (time()-query("questsn_giveup_time", me))<20+giveup*2 && !wizardp(me) )
    {
        write("南海神尼笑着對你説道：“怎麼完不成任務這麼不順利？不要着急，先好好想想原因在哪裏。\n");
        return 1;
    }

/*
    if( query("questsn_times", me)<3
         || (query("questsn_times", me)>5 && random(20) == 5) )
    {
        X_QuestD->query_quest(me, this_object());
        return 1;
    }
*/

    quest = ([]);
    // 以下給任務
    if(exp <= 600000)        tag = 0;
    else if(exp <= 900000)   tag = 1;
    else if(exp <= 1200000)  tag = 2;
    else if(exp <= 1800000)  tag = 3;
    else if(exp <= 2500000)  tag = 4-random(3);
    else if(exp <= 3200000)  tag = 5-random(3);
    else if(exp <= 4000000)  tag = 6-random(3);
    else
    {
        if(random(15)==0||(exp>10000000&&random(10)==0))
            tag=8;
        else tag=7-random(3);
    }

    i=query("questsn_times", me);
    if((i > 20 && random(20)==18) || wizardp(me))
    {
        qgood = QUEST_WUGOOD_D->query_good();
        msg = qgood["msg"+random(4)];
        want = random(qgood["max_num"] - qgood["min_num"] + 1) + qgood["min_num"];
        msg = YEL"南海神尼呵呵大笑，高興的説道：“你的辦事能力真不賴！\n"+msg
            +"\n你想法弄一批"+qgood["name"]+"來，大約要 "+want+" "+qgood["unit"]+"，有多少可以先交多少。去罷！”\n"NOR;
        write(msg);
        quest = ([
                   "id"         : qgood["id"],
                   "name"       : qgood["name"],
                   "msg"        : msg,
                   "want"       : want,
                   "type"       : "收",
                   "check_file" : qgood["check_file"],
                   "level"      : tag,
                   "bonus"      : 0,
                   "all_bonus"  : 0,
                ]),
        set("quest_sn", quest, me);
        return 1;
    }

    if(tag==8)
    {
        npc = new(CLASS_D("generate") + "/player_npc.c");
        FUBEN_D->clear_fuben("ultra",query("id", me));
        maze_object=get_object("/f/ultra/"+query("id", me)+"/maze");
        maze_object->set_maze_boss(npc);
        //maze_target = MAZE_D->create_maze(npc);
        maze_target=get_object("/f/ultra/"+query("id", me)+"/maze/exit");
        npc->move(maze_target);
        npc->set_from_me(me,1);
        addn_temp("apply/attack", npc->query_skill("force")/3, npc);
        addn_temp("apply/dodge", npc->query_skill("force")/3, npc);
        addn_temp("apply/parry", npc->query_skill("force")/3, npc);
        addn_temp("apply/damage", 200+random(100), npc);
        addn_temp("apply/unarmed_damage", 200+random(100), npc);
        addn_temp("apply/armor", 200+random(300), npc);
        set_temp("quester",query("id",  me), npc);
        set("auto_perform", 5, npc);

        set("shen", -query("combat_exp", npc)/2000, npc);
        msg="南海神尼正容對你説：“"+npc->name(1)+
            "這個惡棍多次危害武林，聽説他最近躲在一個迷宮中，你去除掉他吧！”\n";

        quest = ([
            "maze" : maze_object,
            "name" : npc->name(1),
            "id":query("id", npc),
            "bonus": (200+random(51)),
            "type" : "殺",
            "level": 8,
            "where": maze_target,
            "msg":   msg,
            "object": base_name(npc),
        ]);
        tell_object(me, quest["msg"]+"\n");
        set("quest_sn", quest, me);

        return 1;
    }
    else
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
            } else lvl = tag;
            while(1)
            {
                quest = QUEST_SN_D(lvl)->query_quest();
                if (quest["type"] == "殺" || quest["type"] == "擒")
                {
                    if (! get_object(quest["object"])->is_master())
                    break;
                } else
                    break;
            }

/*
    if(undefinedp(quest["msg"]) || quest["msg"] == "")
*/
    switch(quest["type"])
    {
        case "擒":
                msg = sn_msg[random(sizeof(sn_msg))] + replace_string(qin_msg1[random(sizeof(qin_msg1))],"name",quest["name"]) + qin_msg2[random(sizeof(qin_msg2))];
                break;
        case "殺":
                if( query("race", get_object(quest["object"])) != "人類" )
                {
                        quest["type"] = "擒";
                        msg = sn_msg[random(sizeof(sn_msg))] + replace_string(qin_msg1[random(sizeof(qin_msg1))],"name",quest["name"]) + qin_msg2[random(sizeof(qin_msg2))];
                        break;
                } else msg=SNMSG_D->query_snmsg("殺",quest["name"]);
                break;
        case "尋":
                msg=SNMSG_D->query_snmsg("尋",quest["name"]);
                break;
        case "送":
                npc = new(CLASS_D("generate") + "/sn_receiver.c");
                FUBEN_D->clear_fuben("ultra",query("id", me));
                maze_object=get_object("/f/ultra/"+query("id", me)+"/maze");
                maze_object->set_maze_boss(npc);
                maze_target=get_object("/f/ultra/"+query("id", me)+"/maze/exit");
                //maze_target = MAZE_D->create_maze(npc);
                npc->move(maze_target);
                NPC_D->set_from_me(npc, me, 100);
                set_temp("quester",query("id",  me), npc);
                thing = new(quest["object"]);
                set("send_to",query("id",  npc), thing);
                set("send_from", query("id"), thing);
                set("send_from_name", query("name"), thing);
                msg = sn_msg[random(5)]+"你看能否幫我將"+thing->name(1)+"送至"+npc->name(1)+"處，"
                                        "他現在正在一個迷宮中，趕緊去，不然誤了時間他可能就不在了。";
                if (!thing->move(me))
                {
                    thing->move(environment());
                    message_vision("南海神尼將$N輕輕放在地上。\n",thing);
                } else message_vision("南海神尼將$N交給$n。\n",thing,me);
                quest["thing"] = thing;
                quest["send_to"]=query("send_to", thing);
                quest["maze"] = maze_object;
                break;
        }
    }
    quest["msg"] = msg;
    quest["level"] = tag;

/*
    if (quest["type"] == "殺" && (random(6) == 3 || wizardp(me)))
    {
        robot_quest = ANTI_ROBOT->get_question();
        msg = "南海神尼微笑着説道：“我剛將武林同盟的口令更改了一下，你去通知一下" + quest["name"] + NOR"，新口令是：\n";
        msg += robot_quest["question"];
        msg += "你只需要將口令用"HIR"普通的數字形式"NOR"傳送過去就行了，傳送的指令是：whisper。\n";
        quest["type"]   = "傳";
        quest["msg"]  = msg;
        quest["answer"] = robot_quest["answer"];
    }
*/

    set("quest_sn", quest, me);
    if(stringp(quest["msg"])&&quest["msg"]!="")
                write(YEL""+quest["msg"]+"\n"NOR);
    else
    {
                write(YEL""+msg+"\n"NOR);
                set("quest_sn/msg", msg, me);
    }
    return 1;
}

int accept_object(object me, object ob)
{
    int rank,exp,pot,score,times, i,tag,all_quest_sn, bonus;
    mapping quest;
    object gold,who,obj;
    string msg;
    int mar,weiwang,shen,quest_count;
    int total_count;
    mixed special = 0;
    mixed money = 0;

    who = this_object();

    if( (query("character", me) != "陰險奸詐") && (query("character", me) != "心狠手辣") && query("character", me) != "國士無雙" && !(query("shen", me)>0) )
    {
        write("南海神尼驚訝的道：“你是誰？給我這個東西幹什麼？”\n");
        return 0;
    }
    else if( !(quest=query("quest_sn", me)) )
    {
        write("南海神尼呵呵笑道：“我知道你想孝敬我，但是可以靠實際行動嘛，東西你還是自己留着吧。”\n");
        return 0;
    }

    if( query("money_id", ob) )
    {
           if (ob->value() < 1000000)
           {
                   tell_object(me,"南海神尼呵呵一笑：我不缺錢花啊，這點錢，你自己留着買東西吃吧。\n");
                   return notify_fail("南海神尼輕輕説道：如果給我100兩黃金，我就取消了你的任務。\n");
           }
           delete("quest_sn", me);
           tell_object(me,"南海神尼隨手發下" + ob->name(1) + "，輕輕對你説：那你這個任務不做就算了吧。\n");
           destruct(ob);
           return 1;
    }

    if(quest["type"]!="尋"&&quest["type"]!="收"&&quest["type"]!="送"&&quest["type"]!="擒")
    {
        write("南海神尼微笑道：“我沒有叫你去找東西呀，東西你收回。”\n");
        return 0;
    }

    if (userp(ob) ||
        ob->is_item_make() ||
        ob->query_save_file())
    {
        write("南海神尼大怒道：“好你個小子，竟然想矇騙本副盟主！來人！把他給我抓起來！”\n");
        me->get_into_prison(this_object(), 0, 30);
        log_file("static/QUEST_DIJIAO",sprintf("%s(%s)(神尼任務)製造%s(%s)(%s)作弊\n",query("name", me),
             query("id", me),ob->name(),query("id", ob),ctime(time())));
        return 1;
    }

    if ( quest["type"] == "送" )
    {
        if( !ob->is_receipt() || query("reply_to", ob) != query("id", who) )
        {
            write("南海神尼接過來一看，皺眉道：“給我這玩藝幹什麼？”\n");
            return 0;
        }
        if( query("reply_by", ob) != quest["send_to"] )
        {
            write("南海神尼接過來一看，皺眉道：“這張回執是誰給你的？別想來糊弄我！”\n");
            return 0;
        }
        if( query("receive_from", ob) != query("id", me) )
        {
            write("南海神尼接過來一看，皺眉道：“這張回執是你自己得到的麼？別想來糊弄我！”\n");
            return 0;
        }
    } else if ( quest["type"] == "收" )
    {
        switch( quest["id"] )
        {
            case "HEAD_OBJ":
            case "ARMOR_OBJ":
            case "CLOTH_OBJ":
                if ( !(bonus = quest["check_file"]->check_value(base_name(ob))) )
                {
                    write("南海神尼接過來一看，皺眉道：“給我這玩藝幹什麼？”\n");
                    return 0;
                }

                if( !mapp(query("armor_prop", ob)) || 
                     !stringp(query("armor_type", ob)) )
                {
                    write("南海神尼接過來一看，皺眉道：“給我這玩藝幹什麼？”\n");
                    return 0;
                }
                quest["bonus"] = bonus;
                break;
            case "SWORD_OBJ":
            case "BLADE_OBJ":
            case "HAMMER_OBJ":
            case "STAFF_OBJ":
                if ( !(bonus = quest["check_file"]->check_value(base_name(ob))) )
                {
                    write("南海神尼接過來一看，皺眉道：“給我這玩藝幹什麼？”\n");
                    return 0;
                }

                if( !mapp(query("weapon_prop", ob)) )
                {
                    write("南海神尼接過來一看，皺眉道：“給我這玩藝幹什麼？”\n");
                    return 0;
                }
                quest["bonus"] = bonus;
                break;
            default :
                if ( !(bonus = quest["check_file"]->check_value(base_name(ob))) )
                {
                    write("南海神尼接過來一看，皺眉道：“給我這玩藝幹什麼？”\n");
                    return 0;
                }
                quest["bonus"] = bonus;
                break;
        }
    } else if ( ob->name(1) != quest["name"] )
    {
        write("南海神尼説道：“這不是我想要的。”\n");
        return 0;
    }

//    message_vision("$N將$n交給南海神尼。\n",me,ob);與give信息重複haiyan
    times=query("questsn_times", me);//連續次數
    tag=query("quest_sn/level", me)+1;//任務等級
    if( (i=query("questsn_times", me))<15)i=15-i;
    else i = 1;

    exp = tag*80 + quest["bonus"]*3;
        exp += times;
    exp += random(exp/2);
    exp = exp/i;

    if (tag > 4 && i > 5)
        exp /= 2;

    if (quest["type"]=="收")
    {
        exp = quest["bonus"]*(tag + 1);
        exp += random(exp/2);
    }

    pot = exp/(2+random(2));

    score = random(exp/20);
    weiwang = random(exp/15);

    if (times + 1 > 200)
         mar = exp/5 + random(times);
    else mar = 20 + random(20);

    if (mar > 1000) mar = 1000;

    if(quest["type"]=="收")
    {
        if((int)quest["want"]>(quest["ok"]+1))
        {
            addn("quest_sn/ok", 1, me);
            write("南海神尼接過來高興的説：“我要的就是這個，第 "+quest["ok"]+" 了，太好了，還有 "+(quest["want"]-quest["ok"])+" 個，繼續努力！”\n");
            score /= 3;
            exp /= 2;
            pot /= 2;
            mar /= 2;
            weiwang /= 2;
            QUEST_D->bonus(me, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                  "weiwang" : weiwang, "score" : score]), 1);
            addn("quest_sn/all_bonus", exp, me);
            destruct(ob);
            return 1;
        }
        exp += quest["all_bonus"]/2;
        pot = exp/(2+random(2));
        weiwang = random(exp/15);
        mar = mar*2;
        mar += mar/4 * quest["want"];
        score = score;
    }
    write("南海神尼接過來開心的笑着説：“不錯呀！你這次任務完成得很好！”\n");
    destruct(ob);
    if(!random(10))
    {
        i=(exp/60+1);
        if(i>30) i=30;
        gold=new("/clone/money/gold");
        gold->set_amount(i);
        tell_object(me,"然後取出一錠黃金給你：“行走江湖，身上總要帶點錢，我這裏有些金子，給你去用吧！”\n"
                       HIW"\n你被獎勵了 "+i+" 兩黃金。\n");
        if(!gold->move(me))
        {
            message_vision("但是$N身上東西太重，黃金一下子從手中滑到了地上。\n",me);
            gold->move(environment());
        }
        GIFT_D->bonus(me, ([ "exp" : exp*3/2, "pot" : pot, "mar" : mar,
                             "weiwang" : weiwang, "score" : score, "percent" : 100 ]), 1);
    }
    else GIFT_D->bonus(me, ([ "exp" : exp*3/2, "pot" : pot, "mar" : mar, "percent" : 100,
                              "weiwang" : weiwang, "score" : score ]), 1);

    /*
    if ( times < 1 )
        set("questsn_times", 1, me);
    else
        addn("questsn_times", 1, me);
    */
   set_temp("sn_giveup", 0, me);

   addn("total_hatred", -5, me);
   if( query("total_hatred", me)<0)set("total_hatred", 0, me);

   quest_count=query("questsn_times", me)+1;
   total_count = quest_count % 500;
   if (total_count == 50)
   {
       msg = "$N呵呵笑了兩聲道：“你還可以，連着"+chinese_number(quest_count)+
       "次任務都完成的漂漂亮亮，繼續努力！”\n";
        special = 1;
           } else
       if (total_count == 100)
   {
       msg = "$N笑的合不攏嘴，看了你一眼道：“有志氣！"+chinese_number(quest_count)+
       "次任務幹得乾淨利索！”\n";
       special = "/clone/gift/puti-zi";
   } else
    if (total_count == 150)
    {
        msg = "$N歎道：“真是長江後浪推前浪，想不到你接連"+chinese_number(quest_count)+
               "次任務都無一疏漏，不易，不易！”\n";
        money = 1;
    } else
    if (total_count == 200)
    {
        msg = "$N歎道：“真是長江後浪推前浪，想不到你接連"+chinese_number(quest_count)+
               "次任務都無一疏漏，不易，不易！”\n";
        money = 1;
    } else
    if (total_count == 250)
    {
        msg = "$N歎道：“真是長江後浪推前浪，想不到你接連"+chinese_number(quest_count)+
               "次任務都無一疏漏，不易，不易！”\n";
        money = 1;
    } else

    if (total_count == 300)
    {
        msg = "$N歎道：“真是長江後浪推前浪，想不到你接連"+chinese_number(quest_count)+
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
        msg = "$N歎道：“真是一個武學天才啊，想不到你接連"+chinese_number(quest_count)+
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
       msg = "$N深深歎了口氣，道：“沒想到你連着"+chinese_number(quest_count)+
       "次任務無一失手，看來以後就是你們這些人挑大樑啦！”\n";
       special = "/clone/gift/jiuzhuan";
#ifdef DB_SAVE
       if( MEMBER_D->is_valid_member(query("id", me)) )
        {
                if( query("special_skill/sophistry", me) )
                {
                       if (quest_count >= 5000)
                               quest_count = 0;
                } else {
                       if (quest_count >= 2000)
                               quest_count = 0;
                }
        }
       else
        {
#endif
       if (quest_count >= 1000)
           quest_count = 0;
#ifdef DB_SAVE
        }
#endif
   } else
       if ((total_count % 10) == 0)
   {
       msg = "$N微微點頭：“乾的不錯，居然連着"+chinese_number(quest_count)+
       "次都沒有失手，接着來，別放鬆！”\n";
   }

   set("questsn_times", quest_count, me);

   if (special) {
       // message_vision(msg, who, me);
       GIFT_D->special_bonus(who, me, special);
   }
    if (money) {
        // message_vision(msg, who, me);
        QUEST_D->money_bonus(who, me, money);
    }

    delete("quest_sn", me);

   //記錄完成任務的次數（不要求連續），如果滿1000次則獎勵翡翠殘片
   all_quest_sn=query("all_quest_sn", me);
   if (!all_quest_sn) all_quest_sn = 0;
   all_quest_sn += 1;
   if (all_quest_sn == 1000)
   {
       obj = new("/clone/tessera/gem.c");
       tell_object(me,this_object()->name() + "又對你點了點頭：你已經從我這裏接了一千個任務，我這裏正好\n" +
                   "有個"+query("name", obj)+"，就獎給你了！\n");
       if (!obj->move(me))
               obj->move(environment());
       set("all_quest_sn", 0, me);
                FAMILY_D->add_family_fame(who, 20 + random(5));
                LEAGUE_D->add_league_fame(who, 20 + random(5));
                BUNCH_D->add_bunch_fame(who, 20 + random(5));
   }else set("all_quest_sn", all_quest_sn, me);

   return 1;
}

int give_up()
{
    object me,ob,obj;
    int giveup,rank;
    mapping quest;

    me = this_player();
    /*
    if( query("quest_sn", me) )
    {
    if( (query("character", me) != "陰險奸詐") && (query("character", me) != "心狠手辣") && !(query("shen", me)>0) )
        return 1;
    }
    */
    if( (quest=query("quest_sn", me)) )
    {
        message_vision("$N委屈的到南海神尼面前哭訴：“我這次任務沒有完成，辜負了您老人家的期望......”\n",me);
        /*
        if (quest["type"] == "傳")
        {
                message_vision("$N皺着眉頭對$n説：『不就是傳一個口令麼？有那麼難？回去仔細想想，這個任務一定要完成！\n",this_object(),me);
                return 1;
        }
        */
        if (quest["type"] == "送")
        {
                if (objectp(ob = quest["thing"]))
                {
                        ob->move("/d/register/prison");
                        destruct(ob);
                }
        }
        if ( stringp(quest["maze"]) )
        {
            //MAZE_D->remove_maze(quest["maze"]);
            FUBEN_D->clear_fuben("ultra",query("id", me));
        }

        message_vision("南海神尼對$N微笑着説:“沒關係，下次好好努力就行啦。”\n", me);

        if (quest["type"] == "收")
        {
                delete("quest_sn", me);
                return 1;
        }
        set("questsn_times", 0, me);

        giveup=query_temp("sn_giveup", me);
        if ( giveup < 1 )
            set_temp("sn_giveup", 1, me);
        else if ( giveup < 5 )
            set_temp("sn_giveup", giveup+1, me);
        else set_temp("sn_giveup", 5, me);

        set("questsn_giveup_time", time(), me);

        delete("quest_sn", me);
    }
    else
        write("南海神尼微笑着告訴你：“你目前沒有任何任務。”\n");
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
    if(!ob) return;
    if(ob->is_character())
        message_vision("$N突然一溜煙地跑得沒影了。\n",ob);
    ob->move("/d/wizard/prison");
    destruct(ob);
    return ;
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "碧海清波" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/bluesea-force/bo",
                           "name"    : "碧海清波",
                           "sk1"     : "bluesea-force",
                           "lv1"     : 120,
                           "force"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "苦海無邊" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/bluesea-force/hai",
                           "name"    : "苦海無邊",
                           "sk1"     : "bluesea-force",
                           "lv1"     : 120,
                           "finger"  : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "絕仙決" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/bluesea-force/jue",
                           "name"    : "絕仙決",
                           "sk1"     : "bluesea-force",
                           "lv1"     : 120,
                           "force"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "戮仙決" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/bluesea-force/lu",
                           "name"    : "戮仙決",
                           "sk1"     : "bluesea-force",
                           "lv1"     : 120,
                           "force"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "五陰焚滅" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/bluesea-force/mie",
                           "name"    : "五陰焚滅",
                           "sk1"     : "bluesea-force",
                           "lv1"     : 120,
                           "strike"  : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "南海無影杖" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/bluesea-force/nan",
                           "name"    : "南海無影杖",
                           "sk1"     : "bluesea-force",
                           "lv1"     : 120,
                           "staff"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "玄黃連環掌" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/bluesea-force/xuan",
                           "name"    : "玄黃連環掌",
                           "sk1"     : "bluesea-force",
                           "lv1"     : 120,
                           "strike"  : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "斬仙決" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/bluesea-force/zhan",
                           "name"    : "斬仙決",
                           "sk1"     : "bluesea-force",
                           "lv1"     : 120,
                           "force"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "誅仙決" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/bluesea-force/zhu",
                           "name"    : "誅仙決",
                           "sk1"     : "bluesea-force",
                           "lv1"     : 120,
                           "force"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        default:
                return 0;
        }
}
