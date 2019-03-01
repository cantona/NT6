// kuihua 葵花太監

#include <ansi.h>

inherit NPC;
inherit F_MASTER;
inherit F_NOCLONE;

#define ULTRA_OPINION   "宗師"
#define OPINION_TYPE    HIY "輕身功夫" NOR
#define MY_OPINION      "dodge"

#define QUESTKILL_D     "/quest/questkh/quest/questkill"
#define QUESTKH_D(x)    ("/quest/questkh/quest/questkh" + x)
#define KHMSG_D         ("/quest/questkh/kuihua-msg")
#define ANTI_ROBOT      "/kungfu/class/ultra/robot"

mixed ask_opinion();
int give_quest();
int give_up();
void destory(object ob);
void npc_dest(object npc);
string time_period(int timep);
mixed ask_maze();
string  *my_opinions = ({ "dodge" });

// 該頭文件必須在這裡嵌入
#include <ultra.h>

void create()
{
        set_name("葵花太監", ({ "kuihua taijian", "kuihua", "taijian" }) );
        set("title", HIR "大宗師" NOR);
        set("gender", "男性");
        set("age", 99);
        set("long", "此人臉型瘦削，滿是陰騖，不知是喜是怒。\n");
        set("attitude", "peaceful");
        set("no_get", 1);
        set("str", 31);
        set("int", 39);
        set("con", 34);
        set("dex", 36);

        set("max_qi", 20000);
        set("max_jing", 20000);
        set("neili", 30000);
        set("max_neili", 30000);
        set("jiali", 100);

        set("combat_exp", 50000000);

        set("inquiry", ([
                "葵花寶典" : "那是我寫的一本關于輕功方面的心得，怎麼，你有興趣？",
                "評價"     : (: ask_opinion :),
                "opinion"  : (: ask_opinion :),
                "武學修養" : "學習深奧武功，沒有深厚的武學修養(martial-cognize)，提也休提！",
                "任務"     : "葵花太監低了頭，撫摩著手中的玉如意，全神貫注，理都不理。”\n",
                "maze"     : (: ask_maze :),
                "迷宮"     : (: ask_maze :),
        ]));

        set_skill("unarmed", 500);
        set_skill("finger", 500);
        set_skill("parry", 500);
        set_skill("dodge", 500);
        set_skill("force", 500);
        set_skill("sword", 500);
        set_skill("kuihua-mogong", 500);
        set_skill("martial-cognize", 500);
        set_skill("literate", 220);

        map_skill("parry", "kuihua-mogong");
        map_skill("force", "kuihua-mogong");
        map_skill("dodge", "kuihua-mogong");
        map_skill("finger", "kuihua-mogong");
        map_skill("sword", "kuihua-mogong");

        prepare_skill("finger", "kuihua-mogong");

        set("opinion/ultra",  1);
        set("opinion/master", 1);

        set("rank_info/self", "本宮");

        setup();
        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/clone/misc/spin")->wield();

        set("startroom", "/d/beijing/shanlu3");
        check_clone();
}

void init()
{
        object me;

        if (! interactive(me = this_player()))
                return;

        delete_temp("want_opinion", me);
        if (ultrap(me))
                message_vision(CYN "$N" CYN "掃了$n" CYN
                               "一眼，冷笑一聲。\n" NOR,
                               this_object(), me);
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
        quest=query("quest_kh", me);

        if (!quest)
                return "你是不是吃飽了沒事幹，莫非想去鬼門關逛逛？";

        if ( undefinedp(quest["maze"]) )
                return "你接的任務跟迷宮無關，不該知道的事情不要多問！";

        /*
        maze = MAZE_D->query_maze(quest["maze"]);
        if ( !mapp(maze) || undefinedp(maze["entry"]) )
        */
        if( !(find_object("/f/ultra/"+query("id", me)+"/maze/exit")) )
                return "真是該死，那個迷宮據說已經消失，你還有臉來見我？";

        message_vision("$N對$n點頭道：“既然你已經準備好要去那裡，那就千萬別失手！”\n", ob, me);
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
                return "嘿，你這點武功只好抓抓老鼠。";

        if( query("opinion/"MY_OPINION, me) == ULTRA_OPINION )
                return "嗯，你輕功方面的修為已經稱得上是宗師了！要是有興趣咱們過兩招？";

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

                message_vision(CYN "$N" CYN "頗為惱怒的對$n"
                               CYN "道：“沒看我正忙著嗎？”\n" NOR,
                               this_object(), me);
                return 1;
        }

        switch(query_temp("want_opinion/kuihua", me) )
        {
        case 0:
                command("say 好吧，你準備好了就接我一招，我看看你的水平如何。");
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

        addn_temp("want_opinion/kuihua", 1, me);
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
        lvl += 20;
        return lvl;
}

void do_congration(object me)
{
        command("chat*heihei"+query("id", me));
}

int accept_hit(object me)
{
        command("heng");
        command("say 你活得不耐煩了！");
        kill_ob(me);
        return 1;
}

int accept_fight(object me)
{
        object weapon;

        if( query("opinion/"MY_OPINION, me) == ULTRA_OPINION )
        {
                message_vision(CYN "$N" CYN "對$n" CYN "道：“很"
                               "好，你也算是頂尖高手了，來吧！咱"
                               "們比劃一下！”\n" NOR,
                               this_object(), me);
                return 1;
        }

        if( !query_temp("want_opinion/kuihua", me) )
        {
                command("say 你幹什麼要和我動手？");
                return 0;
        }

        command("look"+query("id", me));
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
        if( query("character", me) != "陰險姦詐" && 
            query("character", me) != "國士無雙" )
        {
                command("say 你這人沒有領會立世的精妙之理，還"
                        "是回去吧！");
                return -1;
        }

        if (skill == "martial-cognize")
                return 1;

        if (! ultrap(me))
        {
                command("say 想學我的葵花神功？你還不夠資格，"
                        "等你成了大宗師再說吧！");
                return -1;
        }

        if (me->query_skill(skill, 1) >= 180)
        {
                command("say 夠了！我就教你到這裡吧，武功還是"
                        "要靠自己多研究才是！");
                return -1;
        }

        if (skill != "kuihua-mogong")
                return 1;

        if( query_temp("can_learn/kuihua/kuihua-mogong", me) )
                return 1;


        set_temp("can_learn/kuihua/kuihua-mogong", 1, me);
        command("nod");
        command("say 不錯，我就傳你葵花神功吧，不要讀什麼葵花"
                "寶典，那是我拿去害人的！");
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

int give_quest()
{
    mapping questtemp,questkh,questkill,skills,robot_quest;
    object ob,npc;
    int time,level,i,lev,lev1;
    int exp;
    int lvl,all_lvl;
    string msg,*sname,place;
    object maze_target;
    object maze_object;

    ob = this_player();
    exp=query("combat_exp", ob);

    if( (query("character", ob) != "陰險姦詐") && 
            (query("character", ob) != "國士無雙") && 
            (query("character", ob) != "心狠手辣") )
    {
        message_vision("葵花太監抬頭看了$N一眼，尖著嗓子道：“你這號假仁假義的貨色，再不馬上給我滾開，我讓你血濺五步！”\n", ob);
        return 1;
    }
    /*
    if( query("shen", ob) >= 0 )
    {
        write("葵花太監頭也不抬，輕輕嘆了口氣，道：“好好一個人，偏要棄暗投明，竟還敢到這裡來，真是不想活啦？”\n");
        return 1;
    }
    */
        if (exp < 500000)
    {
        write("葵花太監頭也不抬，輕輕道：“你先去練練功夫吧，想為我做事，你還不夠呢。”\n");
        return 1;
    }
    if( mapp(query("quest_kh", ob)) )
    {
       write("葵花太監把玩著手中古玩，微微點頭來，道：“你手頭的任務可是完成了？”\n");
        return 1;
    }
    if( mapp(query("quest_sn", ob)) )
    {
        write("葵花太監把玩著手中古玩，冷笑搖頭，道：“南海神尼那個老不死的總和我作對，你敢帶著她的任務來找我？”\n");
        return 1;
    }


    if( (time()-query("questkh_giveup_time", ob))<(20+random(10)) )
    {
        write("不要急，慢一點嘛。\n");
        return 1;
    }

/*
        if( query("questkh_times", ob)<3
         || (query("questkh_times", ob)>5 && random(20) == 5) )
        {
                X_QuestD->query_quest(ob, this_object());
                return 1;
        }
*/

    // 以下給任務
    if(exp <= 600000)        level = 0;
    else if(exp <= 900000)   level = 1;
    else if(exp <= 1200000)  level = 2;
    else if(exp <= 1800000)  level = 3;
    else if(exp <= 2500000)  level = 4-random(3);
    else if(exp <= 3200000)  level = 5-random(3);
    else if(exp <= 4000000)  level = 6-random(3);
    else
    {
        if(random(15)==0||(exp>10000000&&random(10)==0)||wizardp(ob))
            level=8;
        else level=7-random(3);
    }

    i=query("questkh_times", ob);

    if(i > 20 && random(20) == 15)
    {
        questkill = QUESTKILL_D->query_questkill();
        msg = questkill["msg"];
        write("葵花太監用眼角瞟了你一眼，微露訝色，道：“你倒是好象挺能幹的嘛，嗯？”\n");
        write(msg+"\n");
        time = questkill["time"]/2+random(questkill["time"]/2);
        write("葵花太監回頭看了看你，又道：“我給你"+time_period(time)+"時間，你快去罷。”\n");
        time += time();
      //不要直接修改questkill
        questkh = ([
            "name" :  questkill["name"],
            "khmsg":  msg,
            "dir"  :  questkill["dir"],
            "dir1" :  questkill["dir1"],
            "type" :  questkill["type"],
            "time" :  time,
            "level":  level,
            "desc" :  "滅",
            ]),
        set("quest_kh", questkh, ob);
        return 1;
    }
    else
    {
        if(level==8)
        {
            npc = new(CLASS_D("generate") + "/player_npc.c");
            FUBEN_D->clear_fuben("ultra",query("id", ob));
            maze_object=get_object("/f/ultra/"+query("id", ob)+"/maze");
            maze_object->set_maze_boss(npc);
            //maze_target = MAZE_D->create_maze(npc);
            maze_target=get_object("/f/ultra/"+query("id", ob)+"/maze/exit");
            npc->move(maze_target);
            npc->set_from_me(ob,1);
            addn_temp("apply/attack", npc->query_skill("force")/3, npc);
            addn_temp("apply/dodge", npc->query_skill("force")/3, npc);
            addn_temp("apply/parry", npc->query_skill("force")/3, npc);
            addn_temp("apply/damage", 200+random(100), npc);
            addn_temp("apply/unarmed_damage", 200+random(100), npc);
            addn_temp("apply/armor", 200+random(300), npc);
            set_temp("quester",query("id",  ob), npc);
            set("auto_perform", 5, npc);

            set("shen",query("combat_exp",  npc)/2000, npc);
            msg="葵花太監恨恨地說：“"+npc->name(1)+
                "這個所謂的大俠屢次和我作對，聽說他最近躲在迷宮中，你去宰了他，提頭來見！”\n";

            questkh = ([
                "maze" : maze_object,
                "name" : npc->name(1),
                "id":query("id", npc),
                "bonus": (200+random(51)),
                "type" : "殺",
                "level": 8,
                "where": maze_target,
                "khmsg": msg,
                        "object":base_name(npc),
            ]);
            tell_object(ob,questkh["khmsg"]+"\n");
            set("quest_kh", questkh, ob);

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
            } else lvl = level;
            while(1)
            {
                questtemp = QUESTKH_D(lvl)->query_questkh(ob);
                if (questtemp["type"] == "殺" || questtemp["type"] == "擒")
                {
                    if (! get_object(questtemp["object"])->is_master())
                        break;
                } else
                    break;
            }

                if(undefinedp(msg = questtemp["msg"]) || msg == "" || random(2))
                {
                                if(questtemp["race"])
                                        msg=KHMSG_D->query_khmsg("宰",questtemp["name"]);
                                else
                                        msg=KHMSG_D->query_khmsg(questtemp["type"],questtemp["name"]);
                        }
                questkh=([
                        "id":questtemp["id"],
                        "name":questtemp["name"],
                        "bonus":questtemp["bonus"],
                        "type":questtemp["type"],
                        "khmsg":msg,
                        "level":level,
                        "object":questtemp["object"],
                        ]);

/*
    if (questkh["type"] == "殺" && (random(6) == 3 || wizardp(ob)))
    {
        robot_quest = ANTI_ROBOT->get_question();
        msg = "葵花太監陰笑著說道：“我剛將出入宮門的口令更改了一下，你去通知一下" + questkh["name"] + NOR"，新口令是：\n";
        msg += robot_quest["question"];
        msg += "你只需要將口令用"HIR"普通的數字形式"NOR"傳送過去就行了，傳送的指令是：whisper。\n";
        questkh["type"]   = "傳";
        questkh["khmsg"]  = msg;
        questkh["answer"] = robot_quest["answer"];
    }
*/

                write(questkh["khmsg"]+"\n");
                set("quest_kh", questkh, ob);
            }
    }
    return 1;
}

int accept_object(object who, object ob)
{
   int exp, pot,level,bonus,i,all_quest_kh;
   mapping questkh;
   object me,gold,obj;
   int shen,mar,weiwang,score,quest_count;
   int total_count;
   string msg;
   mixed special = 0;
   mixed money = 0;

   me = this_object();
   if( !(questkh=query("quest_kh", who)) )
   {
      return notify_fail("葵花太監滿臉不耐煩的沖你說：“走開，不要來煩我。”\n");
   }

   if( query("money_id", ob) )
   {
           if (ob->value() < 1000000)
           {
                   tell_object(who,"葵花太監勃然大怒道：你拿這麼點錢來哄我啊？再不給我滾遠點，我扒了你的皮！\n");
                   return notify_fail("葵花太監輕蔑的說：如果能給個100兩黃金，或許我就消除了你的任務。\n");
           }
           delete("quest_kh", who);
           tell_object(who,"葵花太監拋了拋手中的" + ob->name(1) + "，冷冷道：那你這個任務不做就算了吧。\n");
           destruct(ob);
           return 1;
   }

   switch(questkh["type"])
   {
      case "尋"  :
         if(ob->name(1) != questkh["name"] || userp(ob))
         {
            tell_object(who,"葵花太監大怒，斥道：“這是什麼東西？你想來糊弄我麼！”\n");
            return notify_fail("葵花太監吁了口氣，向你甩甩手，道：“你去吧，不要煩我。”\n");
         }
         break ;
      case "殺"  :
         if(!ob->is_head() && !ob->is_corpse())
         {
            tell_object(who,"葵花太監斜著眼睛描了一下，斥道：“這是個什麼東西？你想來糊弄我麼！”\n");
            return notify_fail("葵花太監白了你一眼，甩甩手，道：“你還站在這裡幹什麼？還不快去！”\n");
         }
         else if( !stringp(query("victim_name", ob)) || query("victim_name", ob) != questkh["name"] )
            {
                tell_object(who,"葵花太監捂著鼻子揮手說道：“什麼臭烘烘的？快給我拿走！”\n");
                return notify_fail("葵花太監白了你一眼，甩甩手，道：“我給你的任務你是否不想做了？”\n");
            }
            else if( query("killed_by", ob) != query("id", who) )
            {
                tell_object(who,"葵花太監哼了一聲道：“你是從哪裡撿來的？你自己做不了麼？”\n");
                return notify_fail("葵花太監白了你一眼，甩甩手，道：“你還站在這裡幹什麼？還不快出去！”\n");
             }
         break ;
      default    :
         return 0;
   }

        if( userp(ob) || query("user", ob) || 
            ob->is_item_make() ||
            ob->query_save_file())
    {
        write("葵花太監大怒道：“好你個小雜種，竟然想蒙騙本宮！來人！把他給我抓起來！”\n");
        who->get_into_prison(this_object(), 0, 30);
        log_file("static/QUEST_DIJIAO",sprintf("%s(%s)(葵花任務)制造%s(%s)(%s)作弊\n",query("name", who),
             query("id", who),ob->name(),query("id", ob),ctime(time())));
        return 1;
    }

//   message_vision("$N將$n交給葵花太監。\n",who,ob);與give信息重復haiyan
   tell_object(who,"葵花太監冷笑了一聲，抬頭看了看你，點頭道：“嗯，你可以去了。”\n");
    destruct(ob);
   if( (i=query("questkh_times", who))<15)i=15-i;
   else i = 1;
   level = questkh["level"]+1;
   exp = level*80 + questkh["bonus"]*3;
        exp+=query("questkh_times", who);
   exp += random(exp/2);
   exp = exp/i;

   if (level > 4 && i > 5)
        exp /= 2;

    /*
   if (level == 9)
       pot = exp*(2 + random(2));
   else
    */
       pot = exp/(2+random(2));
   score = random(exp/20);
   weiwang = random(exp/15);

   if( query("questkh_times", who)+1>200 )
         mar=exp/5+random(query("questkh_times", who));
   else mar = 20 + random(20);

   if (mar > 1000) mar = 1000;

   if(!random(18))
   {
      i=(exp/60+1);
      if(i>30) i=30;
      gold=new("/clone/money/gold");
      gold->set_amount(i);
      tell_object(who,"突然一錠黃金飛入你的手中，背後葵花太監冷冷說道：“這些金子拿去，日後辦事賣力點！”\n"
          HIW"\n你被獎勵了 "+i+" 兩黃金。\n"NOR);
       if(!gold->move(who))
       {
          message_vision("但是$N身上東西太重，黃金一下子從手中滑到了地上。\n",who);
          gold->move(environment());
      }
      GIFT_D->bonus(who, ([ "exp" : exp*3/2, "pot" : pot, "mar" : mar,
                            "weiwang" : weiwang, "score" : score, "percent" : 100 ]), 1);
   }
   else GIFT_D->bonus(who, ([ "exp" : exp*3/2, "pot" : pot, "mar" : mar, "percent" : 100,
                              "weiwang" : weiwang, "score" : score ]), 1);

   // who->add("questkh_times",1);
   quest_count=query("questkh_times", who)+1;
   total_count = quest_count % 500;
   if (total_count == 50)
   {
       msg = "$N嘿嘿冷笑兩聲道：“你小子還可以，連著"+chinese_number(quest_count)+
       "次任務都完成的幹凈利索，還算有點前途。”\n";
        special = 1;
           } else
       if (total_count == 100)
   {
       msg = "$N抬頭使勁看了你一眼道：“真是不錯，"+chinese_number(quest_count)+
       "次任務幹得還算妥當。”\n";
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
       msg = "$N深深嘆了口氣，道：“想不到你連著"+chinese_number(quest_count)+
       "次任務無一失手，看來以後的江湖就是你的天下啦！”\n";
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
       msg = "$N微微點頭：“幹的不錯，居然連著" +chinese_number(quest_count)+
       "次都沒有失手，繼續給我好好表現！”\n";
   }

   set("questkh_times", quest_count, who);

   if (special) {
       // message_vision(msg, me, who);
       GIFT_D->special_bonus(me, who, special);
   }
    if (money) {
        // message_vision(msg, me, who);
        QUEST_D->money_bonus(me, who, money);
    }
   delete("quest_kh", who);
   addn("total_hatred", -5, who);
   if( query("total_hatred", who)<0)set("total_hatred", 0, who);

   //記錄完成任務的次數（不要求連續），如果滿1000次則獎勵鑽石殘片
   all_quest_kh=query("all_quest_kh", who);
   if (!all_quest_kh) all_quest_kh = 0;
   all_quest_kh += 1;
   if (all_quest_kh == 1000)
   {
       obj = new("/clone/tessera/gem.c");
       tell_object(who,this_object()->name() + "又對你點了點頭：你已經從我這裡接了一千個任務，我這裡正好\n" +
                   "有個"+query("name", obj)+"，就獎給你了！\n");
       if (!obj->move(who))
               obj->move(environment());
       set("all_quest_kh", 0, who);
                FAMILY_D->add_family_fame(who, 20 + random(5));
                LEAGUE_D->add_league_fame(who, 20 + random(5));
                BUNCH_D->add_bunch_fame(who, 20 + random(5));
   }else set("all_quest_kh", all_quest_kh, who);

   return 1;
}

int give_up()
{
   object ob,obj,room;
   mapping questkh;

   ob = this_player();

   if(query("kill_all"))   return 0;

   message_vision("$N心驚膽戰，雙腿亂顫，請求葵花太監取消自己的任務。\n",ob);
   if( mapp(questkh=query("quest_kh", ob)) )
   {
      /*
      if (questkh["type"] == "傳")
      {
         message_vision("$N勃然大怒，指著$n鼻子罵道：『不就是傳一個口令麼？這麼點小事都完成不了？還不快滾！\n",this_object(),ob);
         return 1;
      }
      */
      if(questkh["desc"] == "滅")
      {
         message_vision("葵花太監看了$N一眼，“嗯”了一聲，不置可否。\n", ob);
      }
      else if(questkh["type"] == "殺"&&questkh["level"] == 8)    //by llm
      {
          message_vision("葵花太監頭也不抬，哼了一聲道：“沒用的東西！蠢材！”\n", ob);
          set("questkh_times", 0, ob);
      }
      else
      {
         message_vision("葵花太監頭也不抬，哼了一聲道：“沒用的東西！蠢材！”\n", ob);
         set("questkh_times", 0, ob);
      }

      if ( stringp(questkh["maze"]) )
      {
         //MAZE_D->remove_maze(questkh["maze"]);
         FUBEN_D->clear_fuben("ultra",query("id", ob));
      }

   }
   else
   {
      message_vision("葵花太監專心把玩手中的古董，好象根本沒看見$N\n", ob);
   }
   delete("quest_kh", ob);
   set("questkh_giveup_time", time(), ob);
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
        message_vision("$N哈哈一笑：“葵花太監的手下盡是一些窩囊廢！”轉身一晃，已不見了身影。\n",npc);
    npc->move("/d/register/prison");
    destruct(npc);
    return ;
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "無邊無際" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/kuihua-mogong/bian",
                           "name"    : "無邊無際",
                           "sk1"     : "kuihua-mogong",
                           "lv1"     : 120,
                           "sword"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "分身化影" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/kuihua-mogong/fenshen",
                           "name"    : "分身化影",
                           "sk1"     : "kuihua-mogong",
                           "lv1"     : 120,
                           "force"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "鬼魅身法" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/kuihua-mogong/gui",
                           "name"    : "鬼魅身法",
                           "sk1"     : "kuihua-mogong",
                           "lv1"     : 120,
                           "dodge"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "毀天滅地" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/kuihua-mogong/hui",
                           "name"    : "毀天滅地",
                           "sk1"     : "kuihua-mogong",
                           "lv1"     : 120,
                           "sword"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "無窮無盡" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/kuihua-mogong/qiong",
                           "name"    : "無窮無盡",
                           "sk1"     : "kuihua-mogong",
                           "lv1"     : 120,
                           "sword"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "無聲無息" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/kuihua-mogong/sheng",
                           "name"    : "無聲無息",
                           "sk1"     : "kuihua-mogong",
                           "lv1"     : 120,
                           "dodge"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "無法無天" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/kuihua-mogong/tian",
                           "name"    : "無法無天",
                           "sk1"     : "kuihua-mogong",
                           "lv1"     : 120,
                           "sword"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "無雙無對" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/kuihua-mogong/wswd",
                           "name"    : "無雙無對",
                           "sk1"     : "kuihua-mogong",
                           "lv1"     : 120,
                           "sword"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "群魔亂舞" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/kuihua-mogong/wu",
                           "name"    : "群魔亂舞",
                           "sk1"     : "kuihua-mogong",
                           "lv1"     : 120,
                           "sword"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "幽靈一擊" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/kuihua-mogong/you",
                           "name"    : "幽靈一擊",
                           "sk1"     : "kuihua-mogong",
                           "lv1"     : 120,
                           "force"   : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        case "幽冥神指" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/kuihua-mogong/zhi",
                           "name"    : "幽冥神指",
                           "sk1"     : "kuihua-mogong",
                           "lv1"     : 120,
                           "finger"  : 120,
                           "free"    : 1,
                           "shen"    : 38000, ]));
                break;
        default:
                return 0;
        }
}
