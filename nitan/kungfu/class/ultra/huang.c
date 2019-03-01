// huang 黃裳

#include <ansi.h>

inherit NPC;
inherit F_MASTER;
inherit F_NOCLONE;

#define ULTRA_OPINION   "宗師"
#define OPINION_TYPE    HIY "拳腳功夫" NOR
#define MY_OPINION      "unarmed"

#define QUEST_HS_D(x)   ("/quest/quesths/quest/quesths" + x)
#define QUEST_WUGOOD_D  ("/quest/questsj/quest_sj")
#define HSMSG_D         ("/quest/quesths/quest/huangshang-msg")
#define ANTI_ROBOT      "/kungfu/class/ultra/robot"

mixed ask_opinion();
mixed ask_skill();
int give_quest();
int give_up();
void destory(object ob);
string time_period(int timep);
mixed ask_maze();

string  *my_opinions = ({ "unarmed", "finger",
                          "strike", "cuff", "hand", "claw" });

string* hs_msg = ({
        "黃裳頭也不抬地說：“",
        "黃裳翻出一疊檔案道：“",
        "黃裳低頭想了想，說道：“",
        "黃裳拿著一份公文，說道：“",
        "黃裳微微笑了笑道：“",
});

// 該頭文件必須在這裡嵌入
#include <ultra.h>

void create()
{
        set_name("黃裳", ({ "huang shang", "huang" }) );
        set("title", HIY "大宗師" NOR);
        set("gender", "男性");
        set("age", 92);
        set("long", "此人氣度閒雅，看不出武功高低。\n");
        set("attitude", "peaceful");
        set("no_get", 1);
        set("str", 32);
        set("int", 39);
        set("con", 37);
        set("dex", 32);

        set("max_qi", 20000);
        set("max_jing", 20000);
        set("neili", 30000);
        set("max_neili", 30000);
        set("jiali", 100);

        set("combat_exp", 50000000);

        set("inquiry", ([
                "九陰真經" : "想不到當年我隨手寫的一本武學心得竟成為危害江湖的不祥之物。",
                "評價"     : (: ask_opinion :),
                "opinion"  : (: ask_opinion :),
                "武學修養" : "武學修養(martial-cognize)不到家，還談什麼武功呢？",
                "攝心大法" : (: ask_skill :),
                "任務"     : "天性好，又是負神的話，可以在我這裡領任務(quest)。\n",
                "迷宮"      : (: ask_maze :),
                "maze"      : (: ask_maze :),
        ]));

        set_skill("unarmed", 500);
        set_skill("finger", 500);
        set_skill("claw", 500);
        set_skill("strike", 500);
        set_skill("hand", 500);
        set_skill("cuff", 500);
        set_skill("parry", 500);
        set_skill("dodge", 500);
        set_skill("force", 500);
        set_skill("jiuyin-shengong", 500);
        set_skill("martial-cognize", 500);
        set_skill("literate", 200);

        map_skill("parry", "jiuyin-shengong");
        map_skill("force", "jiuyin-shengong");
        map_skill("dodge", "jiuyin-shengong");
        map_skill("unarmed", "jiuyin-shengong");
        map_skill("finger", "jiuyin-shengong");
        map_skill("strike", "jiuyin-shengong");
        map_skill("hand", "jiuyin-shengong");
        map_skill("cuff", "jiuyin-shengong");
        map_skill("claw", "jiuyin-shengong");

        prepare_skill("claw", "jiuyin-shengong");
        prepare_skill("cuff", "jiuyin-shengong");

        set("opinion/ultra",  1);
        set("opinion/master", 1);

        set("rank_info/self", "某家");

        setup();
        carry_object("/clone/cloth/cloth")->wear();

        set("startroom", "/d/dali/lushui");
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
        if( !is_fighting() &&random(5)==0)
        {
                remove_call_out("greeting");
                call_out("greeting", 1, me);
        }
        add_action("give_quest", "quest");
        add_action("give_up","giveup");
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        if( query("quest_hs", ob) && query("shen", ob)<0 )
                write("黃裳說道："+query("name", ob)+",你的任務完成得怎麼樣了？\n");
}

mixed ask_maze()
{
        object me;
        object ob;
        mapping quest;
        mapping maze;

        me = this_player();
        ob = this_object();
        quest=query("quest_hs", me);

        if (!quest)
                return "你並沒有接我的任務，瞎嚷嚷什麼？";

        if ( undefinedp(quest["maze"]) )
                return "你接的任務跟迷宮無關，好好把你手頭的事情做了！";

        /* 取消老的迷宮
        maze = MAZE_D->query_maze(quest["maze"]);
        if ( !mapp(maze) || undefinedp(maze["entry"]) )
        */
        if( !(find_object("/f/ultra/"+query("id", me)+"/maze/exit")) )
                return "真是沒用！那個迷宮據說都已經消失了！";

        message_vision("$N對$n點頭道：“既然你已經準備好要去那裡，那切記一定要成功！”\n", ob, me);
        FUBEN_D->enter_fuben(me, "ultra");

        return 1;
}

mixed ask_opinion()
{
        object me;
        object ob;

        me = this_player();

        if( query("combat_exp", me)<200000 )
                return "呵呵，你這點武功還談什麼評價？";

        if( query("opinion/"MY_OPINION, me) == ULTRA_OPINION )
                return "哈哈，你拳腳方面的修為已經稱得上是宗師了！咱們要不要過過招？";

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

        switch(query_temp("want_opinion/huang", me) )
        {
        case 0:
                command("look"+query("id", me));
                command("say 好吧，你空手攻我一招，我看看你的水平如何。");
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

        addn_temp("want_opinion/huang", 1, me);
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
        action = SKILL_D(sp)->query_action(me, 0);
        if (mapp(action))
                lvl += (action["force"] + action["attack"] +
                        action["parry"] + action["dodge"] - 150) / 15;
        return lvl;
}

void do_congration(object me)
{
        command("chat 恭喜這位" + RANK_D->query_respect(me) + "，不過武"
                "道永無止境，還望繼續努力啊！");
}

int accept_hit(object me)
{
        if( query_temp("want_hit/huang", me) >= 2 )
        {
                command("heng");
                command("say 事不過三，你要找死那就去死吧！");
                kill_ob(me);
                return 1;
        }

        command("shake");
        command("say 這位" + RANK_D->query_respect(me) + "，"
                "練武之人切忌貿然挑舋。");
        addn_temp("want_hit/huang", 1, me);
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

        if( !query_temp("want_opinion/huang", me) )
        {
                command("say 平白無故動什麼手？");
                return 0;
        }

        if( objectp(weapon=query_temp("weapon", me)) )
        {
                command("say 把你手中的" + weapon->name() + NOR +
                        CYN "給我放下！" NOR);
                return 0;
        }

        if( query("qi", me)*100/query("max_qi", me)<80 || 
            query("jing", me)*100/query("max_jing", me)<80 )
        {
                command("say 你現在狀態不佳，等休息好了再說吧！");
                return 0;
        }

        command("nod");
        COMBAT_D->do_attack(me, this_object(), 0);
        COMBAT_D->do_attack(this_object(), me, 0);

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
        if( query("character", me) != "光明磊落" && 
            query("character", me) != "國士無雙" )
        {
                command("say 大丈夫處世，不論善惡行事一定要光"
                        "明磊落，你生性不是這種人。");
                return -1;
        }

        if (skill == "martial-cognize")
                return 1;

        if (! ultrap(me))
        {
                command("say 想學我的九陰神功？你還不夠資格，"
                        "等你成了大宗師再說吧！");
                return -1;
        }

        if (me->query_skill(skill, 1) >= 180)
        {
                command("say 夠了！我就教你到這裡吧，武功還是"
                        "要靠自己多研究才是！");
                return -1;
        }

        if (skill != "jiuyin-shengong")
                return 1;

        if( query_temp("can_learn/huang/jiuyin-shengong", me) )
                return 1;


        set_temp("can_learn/huang/jiuyin-shengong", 1, me);
        command("nod");
        command("say 很好，我就傳你九陰神功吧，可不要忘記做人"
                "的根本！");
        return 1;

        return -1;
}

void unconcious()
{
        /*
        message("vision", "\n"HIR + name() + "臉色一變，吐了一口鮮"
                "血，身形一閃，消逝不見。\n\n" NOR, environment());
        command("chat 罷！罷！罷！老夫去也！");
        destruct(this_object());
        */
        full_self();
        return;
}

mixed ask_skill()
{
        object me;

        me = this_player();

        if( query("can_perform/jiuyin-shengong/xin", me) )
        {
             command("say 你不是已經會了嗎？");
             return 1;
        }

        if( !query("can_learn/jiuyin-shengong/xin", me) )
        {
               message_sort(HIM "\n黃裳嘆道：“當年我隨手寫了一本武學心得，名曰「九陰真經」，本欲"
                            "留與後人研究武學之用，不料竟成為危害江湖的不祥之物。如果閣下能將其上、"
                            "下兩冊收集齊交還與我，我便傳你絕招「攝心大法」。\n", me);
               command("tan");

               return "閣下意下如何？";
        }


        if (me->query_skill("jiuyin-shengong", 1) < 240)
        {
               command("say 你九陰神功火候還不夠，我還不能傳你這招！");
               return 1;
        }
        if (me->query_skill("martial-cognize", 1) < 240)
        {
               command("say 你武學修養不足，還是下去多磨練一下吧！");
               return 1;
        }
        if( !query("can_perform/jiuyin-shengong/shou", me )
            || !query("can_perform/jiuyin-shengong/zhi", me )
            || !query("can_perform/jiuyin-shengong/zhua", me )
            || !query("can_perform/jiuyin-shengong/zhang", me) )
        {
               command("shake");
               command("say 等你將九陰神功其他絕招領悟後再來找我吧！");
               return 1;
        }

        command("nod");
        command("say 很好，很好！");
        command("say 既然這樣我就傳你攝心大法！");
        message_sort(HIC "\n黃裳將$N" HIC "呼自身旁，對著$N" HIC "耳邊小聲嘀咕了幾句。"
                       "黃裳不時地做出各種奇怪的表情，$N" HIC "邊聽邊看，良久，$N" HIC
                       "一聲長嘯，胸中疑慮頓然消失，再無困擾 ……\n", me);
        command("haha");

        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("jiuyin-shengong"))
                me->improve_skill("jiuyin-shengong", 1500000);
        if (me->can_improve_skill("martial-cognize"))
                me->improve_skill("martial-cognize", 1500000);

        tell_object(me, HIG "你學會了「攝心大法」！\n" NOR);
        set("can_perform/jiuyin-shengong/xin", 1, me);
        return 1;
}
void die()
{
        /*
        message("vision", "\n"HIR + name() + "大叫一聲，狂吐了一口鮮"
                "血，身形一閃，就此不見。\n\n" NOR, environment());
        command("chat 老夫去也！");
        destruct(this_object());
        */
        full_self();
        return;
}
/*
int accept_object(object me, object ob)
{
        if (base_name(ob) != "/clone/lonely/book/zhenjing1"
          && base_name(ob) != "/clone/lonely/book/zhenjing2")
        {
               command("say 你給我這種東西幹什麼？");
               return 0;
        }

        if (base_name(ob) == "/clone/lonely/book/zhenjing1")
        {
               command("nod");
               command("say 很好，很好！");
               if( query("give_zhenjing2", me) )
               {
                     command("haha");
                     command("say 既然這樣我就傳你絕招，你可以隨時來問我！");
                     tell_object(me, HIG "黃裳決定傳你「攝心大法」。\n" NOR);
                     set("can_learn/jiuyin-shengong/xin", 1, me);
                     delete("give_zhenjing1", me);
                     delete("give_zhenjing2", me);
                     destruct(ob);
                     return 1;
               }
               set("give_zhenjing1", 1, me);
               command("say 還有一本「九陰真經下冊」，你盡快找到交還與我！");
               destruct(ob);
               return 1;
        }

        if (base_name(ob) == "/clone/lonely/book/zhenjing2")
        {
               command("nod");
               command("say 很好，很好！");
               if( query("give_zhenjing1", me) )
               {
                     command("haha");
                     command("say 既然這樣我就傳你絕招，你可以隨時來問我！");
                     tell_object(me, HIG "黃裳決定傳你「攝心大法」。\n" NOR);
                     set("can_learn/jiuyin-shengong/xin", 1, me);
                     delete("give_zhenjing1", me);
                     delete("give_zhenjing2", me);
                     destruct(ob);
                     return 1;
               }
               set("give_zhenjing2", 1, me);
               command("say 還有一本「九陰真經上冊」，你盡快找到交還與我！");
               destruct(ob);
               return 1;
        }

}
*/

int give_quest()
{
    mapping quest,qgood,skills,robot_quest;
    object me,target,thing,npc;
    int i, giveup,tag,want,lev,lev1;
    int exp;
    int all_lvl,lvl;
    string msg,*sname,place;
    object maze_target;
    object maze_object;

    me = this_player();
    exp=query("combat_exp", me);

    if( (query("character", me) != "光明磊落") && 
            (query("character", me) != "國士無雙") && 
           (query("character", me) != "狡黠多變") )
    {
        write("黃裳問你：你這種性格的人，來這裡幹什麼？\n");
        return 1;
    }
    /*
    if( !(query("shen", me)<0) )
    {
        write("黃裳看著你只是搖頭：“行走江湖，不是光想著做大俠，我講求的是以殺止殺，你殺性不夠，還是算了吧！”\n");
        return 1;
    }
    */
    if (exp < 500000)
    {
        write("黃裳對你說道：以你現在的經驗，還需要多多磨練啊。\n");
        return 1;
    }

    if( quest=query("quest_hs", me) )
    {
        write("黃裳對你說：先把你手上的任務完成再說。\n");
        return 1;
    }
    if( mapp(query("quest_dg", me)) )
    {
        write("黃裳對你說：獨孤求敗的任務你還沒完成，莫非想找老夫討打？\n");
        return 1;
    }

    giveup=query_temp("hs_giveup", me);
    if( (time()-query("quesths_giveup_time", me))<20+giveup*2 )
    {
        write("黃裳對你哼了一聲道：“老完不成任務，我對你的表現很不滿意，先反省一會兒。\n");
        return 1;
    }

/*
        if( query("quesths_times", me)<3
         || (query("quesths_times", me)>5 && random(20) == 5) )
        {
                X_QuestD->query_quest(me, this_object());
                return 1;
        }
*/
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

    i=query("quesths_times", me);
    if((i > 20 && random(20)==18) || wizardp(me))
    {
        qgood = QUEST_WUGOOD_D->query_good();
        msg = qgood["msg"+random(4)];
        want = random(qgood["max_num"] - qgood["min_num"] + 1) + qgood["min_num"];
        msg = YEL"黃裳微微笑著，讚許地說道：“辦事能力不錯！\n"+
              msg+"\n"+
              "你想法弄一批"+qgood["name"]+"來，大約要 "+want+" "+qgood["unit"]+"，有多少可以先交多少。去罷！”\n"NOR;
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
        set("quest_hs", quest, me);
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
            /*
            NPC_D->place_npc(npc,query("combat_exp", me)<500000?({"大理一帶","終南山","關外","西域"}):
                                  query("combat_exp", me)<800000?({"大理一帶","終南山","西域"}):({"大理一帶","西域"}));
            */
            npc->set_from_me(me,1);
            addn_temp("apply/attack", npc->query_skill("force")/3, npc);
            addn_temp("apply/dodge", npc->query_skill("force")/3, npc);
            addn_temp("apply/parry", npc->query_skill("force")/3, npc);
            addn_temp("apply/damage", 200+random(100), npc);
            addn_temp("apply/unarmed_damage", 200+random(100), npc);
            addn_temp("apply/armor", 200+random(300), npc);
            set_temp("quester",query("id",  me), npc);
            set("auto_perform", 1, npc);
            /*
            NPC_D->random_move(npc);
            NPC_D->random_move(npc);
            NPC_D->random_move(npc);
            */
            place=query("place", npc);

            set("shen",query("combat_exp",  npc)/2000, npc);
            msg="黃裳憂心忡忡的說：“"+npc->name(1)+
                "這個假仁假義的無恥之徒多次危害武林，聽說他最近躲在迷宮中，你去除掉他吧！”\n";

            quest = ([
                //"maze" : maze_target->query("maze/mazename"),
                "maze" : maze_object,
                "name" : npc->name(1),
                "id":query("id", npc),
                "bonus": (200+random(51)),
                "type" :"殺",
                "level":8,
                //"chinese_w":place,
                //"where":npc->query("startroom"),
                "where": maze_target,
                "msg":msg,
                "object":base_name(npc),
            ]);
            tell_object(me,quest["msg"]+"\n");
            set("quest_hs", quest, me);

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
                quest = QUEST_HS_D(lvl)->query_quesths();
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
        case "殺":
                msg=HSMSG_D->query_hsmsg("殺",quest["name"]);
                break;
        case "尋":
                msg=HSMSG_D->query_hsmsg("尋",quest["name"]);
                break;
        case "征":
                npc = new(CLASS_D("generate") + "/hs_target.c");
                FUBEN_D->clear_fuben("ultra",query("id", me));
                maze_object=get_object("/f/ultra/"+query("id", me)+"/maze");
                maze_object->set_maze_boss(npc);
                maze_target=get_object("/f/ultra/"+query("id", me)+"/maze/exit");
                //maze_target = MAZE_D->create_maze(npc);
                npc->move(maze_target);
                /*
                NPC_D->place_npc(npc,query("combat_exp", me)<500000?({"大理一帶","終南山","關外","西域"}):
                                      query("combat_exp", me)<800000?({"大理一帶","終南山","西域"}):({"大理一帶","西域"}));
                */
                NPC_D->set_from_me(npc, me, 100);
                set_temp("quester",query("id",  me), npc);
                /*
                NPC_D->random_move(npc);
                NPC_D->random_move(npc);
                NPC_D->random_move(npc);
                */
                place=query("place", npc);
                msg = hs_msg[random(5)]+npc->name(1)+"去年從武林同盟這裡借走不少錢，地方分舵催討多次不得，"
                        "聽說他現在正在迷宮中，你去試試！\n如果也收不到錢，就收了他的"+quest["name"]+"。拿武林令要出示(chushi)一下。";
                thing = new("/quest/quesths/wulin-ling");
                thing->move(me);
                message_vision("黃裳將武林令交給$N。\n",me);
                quest["target"]=query("id", npc);
                break;
        case "送":
                npc = new(CLASS_D("generate") + "/hs_receiver.c");
                FUBEN_D->clear_fuben("ultra",query("id", me));
                maze_object=get_object("/f/ultra/"+query("id", me)+"/maze");
                maze_object->set_maze_boss(npc);
                maze_target=get_object("/f/ultra/"+query("id", me)+"/maze/exit");
                //maze_target = MAZE_D->create_maze(npc);
                npc->move(maze_target);
                /*
                NPC_D->place_npc(npc,query("combat_exp", me)<500000?({"大理一帶","終南山","關外","西域"}):
                                      query("combat_exp", me)<800000?({"大理一帶","終南山","西域"}):({"大理一帶","西域"}));
                */
                NPC_D->set_from_me(npc, me, 100);
                set_temp("quester",query("id",  me), npc);
                /*
                NPC_D->random_move(npc);
                NPC_D->random_move(npc);
                NPC_D->random_move(npc);
                */
                place=query("place", npc);
                thing = new(quest["object"]);
                set("send_to",query("id",  npc), thing);
                set("send_from", query("id"), thing);
                set("send_from_name", query("name"), thing);
                msg = hs_msg[random(5)]+"你幫我將"+thing->name(1)+"送至"+npc->name(1)+"處，"
                                        "他現在正在迷宮中，誤了時間他可能就離開了。";
                if (!thing->move(me))
                {
                    thing->move(environment());
                    message_vision("黃裳將$N扔在地上。\n",thing);
                } else message_vision("黃裳將$N交給$n。\n",thing,me);
                quest["thing"] = thing;
                quest["send_to"]=query("send_to", thing);
                break;
    }
    }
    quest["msg"] = msg;
    quest["level"] = tag;
/*
    if (quest["type"] == "殺" && random(6) == 3)
    {
        robot_quest = ([]);
        robot_quest = ANTI_ROBOT->get_question();
        msg = "";
        msg += "黃裳鄭重說道：“我剛將武林同盟的口令更改了一下，你去通知一下" + quest["name"] + NOR"，新口令是：\n";
        set_temp("test", robot_quest, me);
        msg += robot_quest["question"];
        msg += "你只需要將口令用"HIR"普通的數字形式"NOR"傳送過去就行了，傳送的指令是：whisper。\n";
        quest["type"]   = "傳";
        quest["msg"]  = msg;
        quest["answer"] = robot_quest["answer"];
    }
*/

    if (maze_object)
        quest["maze"] = maze_object;

    set("quest_hs", quest, me);
    write(msg + "\n");
    return 1;
}

int accept_object(object me, object ob)
{
    int rank,exp,pot,score,times,i,tag,all_quest_hs,bonus;
    mapping quest;
    object gold,who,obj;
    string msg;
    int mar,weiwang,shen,quest_count;
    int total_count;
    mixed special = 0;
    mixed money = 0;

    who = this_object();

    if( (query("character", me) != "光明磊落") && (query("character", me) != "狡黠多變") && query("character", me) != "國士無雙" && !(query("shen", me)<0) )
    {
        write("黃裳奇道：“你是何人？”\n");
        return 0;
    }
    else if( !(quest=query("quest_hs", me)) )
    {
        write("黃裳說道：“無功不受祿，東西你收回。”\n");
        return 0;
    }

    if( query("money_id", ob) )
    {
                if (ob->value() < 1000000)
           {
                   tell_object(me,"黃裳滿臉不悅的對你說：這麼一點點錢，能用來幹什麼？你自己留著買雞腿用吧！\n");
                   return notify_fail("黃裳抬頭望天，緩緩說道：如果給個100兩黃金，或許我就消除了你的任務。\n");
           }
           delete("quest_hs", me);
           tell_object(me,"黃裳接過你的" + ob->name(1) + "，微微笑了笑，點頭道：那你這個任務不做就算了吧。\n");
           destruct(ob);
           return 1;
    }

    if (quest["type"]!="尋"&&quest["type"]!="征"&&quest["type"]!="收"&&quest["type"]!="送")
    {
        write("黃裳說道：“我沒有叫你去找東西，東西你收回。”\n");
        return 0;
    }

    if (userp(ob) ||
        ob->is_item_make() ||
        ob->query_save_file())
    {
        write("黃裳大怒道：“好你個小子，竟然想蒙騙本盟主！來人！把他給我抓起來！”\n");
        me->get_into_prison(this_object(), 0, 30);
        log_file("static/QUEST_DIJIAO",sprintf("%s(%s)(黃裳任務)制造%s(%s)(%s)作弊\n",query("name", me),
             query("id", me),ob->name(),query("id", ob),ctime(time())));
        return 1;
    }

    if ( quest["type"] == "征" )
    {
        if( query_temp("zheng", ob) != query("id", me) )
        {
            write("黃裳接過來，一看怒道：“這哪是你揀來的，還想蒙騙本盟主！走，你的江湖威望降低了！”\n");
            addn("weiwang", -weiwang*(random(5)+4)/4, me);
            if( query("weiwang", me)<0)set("weiwang", 0, me);
            return 0;
        }
    } else if ( quest["type"] == "送" )
    {
        if( !ob->is_receipt() || query("reply_to", ob) != query("id", who) )
        {
            write("黃裳接過來一看，皺眉道：“給我這玩藝幹什麼？”\n");
            return 0;
        }
        if( query("reply_by", ob) != quest["send_to"] )
        {
            write("黃裳接過來一看，勃然大怒道：“這張回執是誰給你的？別想來糊弄我！”\n");
            return 0;
        }
        if( query("receive_from", ob) != query("id", me) )
        {
            write("黃裳接過來一看，勃然大怒道：“這張回執是你自己得到的麼？別想來糊弄我！”\n");
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
                    write("黃裳接過來一看，皺眉道：“給我這玩藝幹什麼？”\n");
                    return 0;
                }

                if( !mapp(query("armor_prop", ob)) || 
                     !stringp(query("armor_type", ob)) )
                {
                    write("黃裳接過來一看，皺眉道：“給我這玩藝幹什麼？”\n");
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
                    write("黃裳接過來一看，皺眉道：“給我這玩藝幹什麼？”\n");
                    return 0;
                }

                if( !mapp(query("weapon_prop", ob)) )
                {
                    write("黃裳接過來一看，皺眉道：“給我這玩藝幹什麼？”\n");
                    return 0;
                }
                quest["bonus"] = bonus;
                break;
            default :
                if ( !(bonus = quest["check_file"]->check_value(base_name(ob))) )
                {
                    write("黃裳接過來一看，皺眉道：“給我這玩藝幹什麼？”\n");
                    return 0;
                }
                quest["bonus"] = bonus;
                break;
        }
    } else if ( ob->name(1) != quest["name"] )
    {
        write("黃裳說道：“這不是我想要的。”\n");
        return 0;
    }

//    message_vision("$N將$n交給黃裳。\n",me,ob);與give信息重復haiyan
    times=query("quesths_times", me);//連續次數
    tag=query("quest_hs/level", me)+1;//任務等級
    if( (i=query("quesths_times", me))<15)i=15-i;
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
            addn("quest_hs/ok", 1, me);
            write("黃裳接過來點點頭說：“第 "+quest["ok"]+" 了，很好，還有 "+(quest["want"]-quest["ok"])+" 個，繼續努力！”\n");
            exp /= 2;
            pot /= 2;
            mar /= 2;
            weiwang /= 2;
            score /= 3;
            GIFT_D->bonus(me, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                  "weiwang" : weiwang, "score" : score]), 1);
            addn("quest_hs/all_bonus", exp, me);
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
    write("黃裳接過來說道：“很好！你這次任務完成得不錯！”\n");
    destruct(ob);

    if (quest["type"]=="征" && objectp(obj = present("wulin ling", me)))
        destruct(obj);

    if(!random(10))
    {
        i=(exp/60+1);
        if(i>30) i=30;
        gold=new("/clone/money/gold");
        gold->set_amount(i);
        tell_object(me,"然後取出一錠黃金給你：“這次獎你些金子，下次繼續努力！”\n"
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
        set("quesths_times", 1, me);
    else
        addn("quesths_times", 1, me);
    */
        set_temp("hs_giveup", 0, me);

   addn("total_hatred", -5, me);
   if( query("total_hatred", me)<0)set("total_hatred", 0, me);

   quest_count=query("quesths_times", me)+1;
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
       if( MEMBER_D->is_valid_member(query("id", me)) )
        {
       if( query("special_skill/sophistry", me) )
        {
              if (quest_count >= 5000)
                       quest_count = 0;
        }
        else
        {
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
       msg = "$N微微點頭：“幹的不錯，居然連著" +
       chinese_number(quest_count) +
       "次都沒有失手，接著來，別放鬆！”\n";
   }

   set("quesths_times", quest_count, me);

   if (special) {
       // message_vision(msg, who, me);
       GIFT_D->special_bonus(who, me, special);
   }
    if (money) {
        // message_vision(msg, who, me);
        QUEST_D->money_bonus(who, me, money);
    }

    delete("quest_hs", me);

   //記錄完成任務的次數（不要求連續），如果滿1000次則獎勵水晶殘片
   all_quest_hs=query("all_quest_hs", me);
   if (!all_quest_hs) all_quest_hs = 0;
   all_quest_hs += 1;
   if (all_quest_hs == 1000)
   {
       obj = new("/clone/tessera/gem.c");
       tell_object(me,this_object()->name() + "又對你點了點頭：你已經從我這裡接了一千個任務，我這裡正好\n" +
                   "有個"+query("name", obj)+"，就獎給你了！\n");
       if (!obj->move(me))
               obj->move(environment());
       set("all_quest_hs", 0, me);
                FAMILY_D->add_family_fame(who, 20 + random(5));
                LEAGUE_D->add_league_fame(who, 20 + random(5));
                BUNCH_D ->add_bunch_fame(who, 20 + random(5));
   }else set("all_quest_hs", all_quest_hs, me);
   return 1;
}

int give_up()
{
    object me,ob,obj;
    int giveup,rank;
    mapping quest;

    me = this_player();
    /*
    if( query("quest_hs", me) )
    {
    if( (query("character", me) != "光明磊落") && (query("character", me) != "狡黠多變") && !(query("shen", me)<0) )
        return 1;
    }
    */
    if( (quest=query("quest_hs", me)) )
    {
        message_vision("$N戰戰兢兢地走到黃裳面前請罪：“小的該死，辜負了盟主的期望......”\n",me);
        /*
        if (quest["type"] == "傳")
        {
                message_vision("$N皺著眉頭對$n說：『不就是傳一個口令麼？有那麼難？回去仔細想想，這個任務一定要完成！\n",this_object(),me);
                return 1;
        }
        */
        if ( stringp(quest["maze"]) )
        {
                //MAZE_D->remove_maze(quest["maze"]);
                FUBEN_D->clear_fuben("ultra",query("id", me));
        }

        if (quest["type"] == "征")
        {
               if (ob = present("wulin ling",me))
               {
                        ob->move("/d/register/prison");
                        destruct(ob);
               }
        }
        if (quest["type"] == "送")
        {
                if (objectp(ob = quest["thing"]))
                {
                        ob->move("/d/register/prison");
                        destruct(ob);
                }
        }
        message_vision("黃裳對$N嘆了一聲道: 怎麼不動動腦筋？這麼簡單的事情都做不了。\n", me);

        if (quest["type"] == "收")
        {
                delete("quest_hs", me);
                return 1;
        }
        rank=query("quest_hs/level", me);
        addn("weiwang", -(rank*6+random(rank+4)), me);
        if( query("weiwang", me)<0 )
               set("weiwang", 0, me);
        write("黃裳告訴你：“你的江湖威望降低了！”\n");

        set("quesths_times", 0, me);

        giveup=query_temp("hs_giveup", me);
        if ( giveup < 1 )
            set_temp("hs_giveup", 1, me);
        else if ( giveup < 5 )
            set_temp("hs_giveup", giveup+1, me);
        else set_temp("hs_giveup", 5, me);

        set("quesths_giveup_time", time(), me);

        delete("quest_hs", me);
    }
    else
        write("黃裳告訴你：你目前沒有任何任務。\n");
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
    ob->move("/d/wizard/wizard_room");
    destruct(ob);
    return ;
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "九陰神拳" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/jiuyin-shengong/quan",
                           "name"    : "九陰神拳",
                           "sk1"     : "jiuyin-shengong",
                           "lv1"     : 120,
                           "cuff"    : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "九陰神手" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/jiuyin-shengong/shou",
                           "name"    : "九陰神手",
                           "sk1"     : "jiuyin-shengong",
                           "lv1"     : 120,
                           "hand"    : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "攝心大法" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/jiuyin-shengong/xin",
                           "name"    : "攝心大法",
                           "sk1"     : "jiuyin-shengong",
                           "lv1"     : 120,
                           "force"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "九陰神掌" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/jiuyin-shengong/zhang",
                           "name"    : "九陰神掌",
                           "sk1"     : "jiuyin-shengong",
                           "lv1"     : 120,
                           "strike"  : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "九陰神指" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/jiuyin-shengong/zhi",
                           "name"    : "九陰神指",
                           "sk1"     : "jiuyin-shengong",
                           "lv1"     : 120,
                           "finger"  : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "九陰神爪" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/jiuyin-shengong/zhua",
                           "name"    : "九陰神爪",
                           "sk1"     : "jiuyin-shengong",
                           "lv1"     : 120,
                           "claw"    : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        default:
                return 0;
        }
}
