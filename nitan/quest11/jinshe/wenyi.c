// /d/city/npc/wenyi

#include <ansi.h>
inherit NPC;

int ask_xia1();
string ask_gift();
#define this_quest_is_open "yes"
 
void create()
{
        object ob;
        object sb;
        set_name("温儀", ({ "wen yi", "wen" }));
        set("long", 
        "她就是金蛇郎君的妻子温儀。\n"
        "一位三十來歲的女子，容貌清秀，有着一種成熟的韻味。\n");
        set("gender", "女性");
        set("age", 36);
        set("attitude", "friendly");
        set("shen", 1000);
        set("str", 35);
        set("int", 30);
        set("con", 25);
        set("dex", 27);
        
         set("max_qi", 999999);
         set("max_jing", 999999);
         set("max_neili", 999999);
         set("neili", 999999);
        set("jiali", 10);
        set("combat_exp", 5000);
         

    set_skill("force", 10);
    set_skill("yijin-jing", 10);
    set_skill("dodge", 10);

    set_skill("shaolin-shenfa", 10);
    set_skill("cuff", 10);
    set_skill("wenjia-daofa", 10);
    set_skill("parry", 10);
    set_skill("blade", 10);
    set_skill("wenjia-quan", 10);
    set_skill("literate", 10);

          map_skill("force", "hunyuan-yiqi");
    map_skill("dodge", "shaolin-shnfa");
    map_skill("cuff", "wenjia-quan");
        map_skill("parry", "wenjia-daofa");
        map_skill("blade", "wenjia-daofa");
    prepare_skill("cuff", "wenjia-quan");
    
    set("inquiry", ([
                "温青青" : "青青是我女兒,她姓夏,叫夏青青.\n",
                "夏青青" : "青青是我女兒.\n",
                "温方山" : "温方山是我爹爹.\n",
                "金蛇郎君" : "名震天下的金蛇郎君就是我的夫君。\n",
                "温家五老" : "哼......\n",
                "夏雪宜" : (: ask_xia1 :),
                "寶物" : (: ask_gift :),
                "掌法祕籍" : (: ask_gift :),
                "金蛇掌法" : (: ask_gift :),
        ]));
 
        setup(); 
        
        if (clonep()) {
                ob = unew("/d/xiangyang/wen/quest/obj/jszf-book");
                if (!ob) ob = new("/clone/money/gold");
                ob->move(this_object());
                sb = unew("/d/xiangyang/wen/quest/obj/gift");
                if (!sb) sb = new("/clone/money/gold");
                sb->move(this_object()); 
                
          carry_object(ARMOR_D("flower_shoe"))->wear();
    carry_object(ARMOR_D("pink_cloth"))->wear();

        }
         
     
}

void init()
{
        add_action("do_comfort", "comfort");
}

void kill_ob(object ob)
{
        ob->remove_killer(this_object());
        remove_killer(ob);
        message_vision("温儀對$N淡淡一笑，又轉過身去，眉宇間沒有絲毫恐懼。”\n", ob);
        message_vision("$N心中忽然覺得：“自己怎麼這麼無恥，對一個手無寸鐵的人也要下此毒手？”\n", ob);
}

int ask_xia1()
{
        object me = this_player();
        string msg;
        msg = CYN"温儀聽到$N的詢問,身子一震,臉色大變。\n"NOR;
        message_vision(msg, me);
                
    if( query_temp("quest/金蛇掌法/start",1, me)){
        remove_call_out("do_happen1");
        call_out("do_happen1",3,me);
                return 1;
        }
        msg = CYN"温儀臉色變了幾變,漸漸平靜下來,對$N説:你問他作什麼?\n"NOR;
        message_vision(msg,me);
        set_temp("quest/jinshe2/fail", 1, me);
        return 1;
}

int do_happen1(object me)
{
        string msg;
        //if (base_name(environment(me)) != HERE)               return 1;
        msg = CYN"温儀歎了口氣,道:既然你是青青的朋友,我就告訴你吧。\n"NOR;
        msg+= CYN"温儀頓了頓道:那是一段陳年舊事,十八年前我遇到了青青的父親夏雪宜,也就是金蛇郎君。\n"NOR;
        msg+= CYN"温儀道:我們相親相愛,本以為,本以為真的可以化解父輩的仇恨,可是爹爹......。\n"NOR;
        msg+= CYN"温儀突然眼圈發紅,哽咽着説不出話來......\n"NOR;
        msg+= HIG"温儀哭得梨花帶雨,楚楚可憐,你忍不住想"HIC"安慰(comfort)"HIG"她一下.\n"NOR;
        message_vision(msg, me);
         set("quest/jinshe2/step1", 1, me);
        return 1;       
    }
int do_comfort(string arg)
{
       string msg;
       object me=this_player();
       if( !query("quest/jinshe2/step1", this_player()))return 0;
        
        if( !arg ) return notify_fail("你説什麼？\n");
        
        message_vision("$N輕聲安慰道：" + arg + "\n", this_player());
        if( strsrch(arg, "夏夫人") >=0 && (strsrch(arg, "你別難過") >=0
         || strsrch(arg, "是金蛇郎君") >=0 || strsrch(arg, "特意叫我來找你的") >=0 )) {
                command("ah");
                command("say 你説的都是真的?!!!\n");
                command("touch"+query("id", this_player()));
                set_temp("quest/jinshe2/step2", 1, this_player());
                delete_temp("quest/jinshe2/step1",1, this_player());
                return 0;
        } else {
                command("say 他這個負心人,丟下我們孃兒倆,一走就是十八年.");
                msg = HIC"安慰人總得有個稱呼,説法,消息和理由吧？\n"NOR;
                message_vision(msg, me);
        }
        
        }

int accept_object(object who, object ob)
{
    string msg;
    object me = this_player();
        if( !who || environment(who) != environment() ) {return 0;}
        if ( !objectp(ob) ) {return 0; }
        if ( !present(ob, who) ) return notify_fail("你沒有這件東西。\n");
        if( !query_temp("quest/jinshe2/step2", this_player()) && !query("quest/jinshe2/xin", this_player()))return 0;
        if (userp(ob)) {
               command("?"+query("id", who));
               command("say 你把人打暈想幹什麼？");
               this_object()->kill_ob(who);
               return notify_fail("糟糕，穿幫了！\n");
        }
        if( query("id", ob) == "xinjian" && query("name", ob) == "家信"){
                if( query("quest/jinshe2/xin", this_player())){
                        command("wuwu");
                        command("say 這...這是雪宜的字體。");
                        command("touch"+query("id", who));
                        command("say 雪宜從前留下了一批寶物,送你當作感謝吧!"); 
                        set("quest/jinshe2/gift", 1, this_player());
                        call_out("destroying", 1, ob);
                        return 1; 
            }
            command("hmm");
            command("say 你是從哪裏得到的這封信?當心我去找月影舉報你!");
            msg = HIG"温儀柳眉一皺:來人啊,把這個騙子轟出去!!!。\n"NOR;
            message_vision(msg, me);
            message_vision(HIR"\n一羣家丁應聲而出,將$N亂棒打暈,丟了出去。\n"NOR,me);
            me->unconcious();
            me->move("/d/city/chmiao");
            tell_room(environment(me),HIR"突然湧出一羣温府家丁,將" + me->name(1) +"亂棍打暈,丟了出去"NOR);
            return 1;
          }
        if( query("name", ob) != HIY"金蛇錐"NOR || query("id", ob) != "jinshezhui"){
               command("shake"+query("id", who));
               command("say 謝謝你啦。");
               return 0;
        }
        if( !query_temp("quest/金蛇劍法/金蛇錐", this_player()) )
        {
             command("hmm");
              command("say 你是從哪裏得到的?當心我去找月影和戴黛舉報你!");
             msg = HIG"温儀柳眉一皺:來人啊,把這個騙子轟出去!!!。\n"NOR;
             message_vision(msg, me);
             message_vision(HIR"\n一羣家丁應聲而出,將$N亂棒打暈,丟了出去。\n"NOR,me);
             me->unconcious();
             me->move("/d/city/chmiao");
             tell_room(environment(me),HIR"突然湧出一羣温府家丁,將" + me->name(1) +"亂棍打暈,丟了出去"NOR);
         call_out("destroying", 1, ob);
             return 1;
}
        command("ah"+query("id", who));
        command("say 這是雪宜的隨身之物,看來你是他託付的人,如果有他的"HIY"消息"CYN"的話,麻煩請您告訴我一聲.\n"NOR);
        command("thank"+query("id", who));
        msg = HIG"温儀向你打聽有關夏雪宜的"HIW"消息"HIG",去看看夏雪宜的"HIR"遺物"HIG"裏有什麼線索吧。\n"NOR;
        message_vision(msg, me);
        set("quest/jinshe2/xin", 1, who);
        delete_temp("quest/jinshe2/step2",1, who);
        call_out("destroying", 1, ob);
        return 1;
}
void destroying(object ob)
{
        if (!ob) return;
        if (userp(ob)) command("drop "+ob->parse_command_id_list()[0]);
        else destruct(ob);
}

string ask_gift()
{
        object ob, sb,me = this_player();
        mapping quest;
        int time;
  
  if( !query("quest/jinshe2/pass", me) && !query("quest/jinshe2/gift", me) )
        return "耶?你怎麼突然説這麼奇怪的事情?\n";
        
        if ( is_busy() || is_fighting())
                return "你沒看到我正忙着麼？\n";
  
        sb = present("box", this_object());
  ob = present("zhangfa miji", this_object());
        if ( !ob && !sb)
                return "耶？東西給我放到那裏去了？\n";

        time=time()-query("quest/jinshe2/zf_time", me);
        if( query("quest/jinshe2/zf_time", me) && time<86400 && !wizardp(me) && !query("env/debug", me) )
                return "你不是已經問過了?真是貪得無厭!!!\n";

        quest=query("quest/jinshe2", me);

        if ( quest["pass"] ) {
                if ( ob ) {
                        set("owner", me, ob);
                        ob->move(me);
                        set("quest/jinshe2/zf_time", time(), me);
                        return "好吧，這本「掌法圖解」你拿回去好好研究研究。\n";
                }
                else
                        return "你要的「掌法圖解」已經給別人拿走了\n";
        }
        if ( quest["gift"] ) {
                if ( sb ) {
                        set("owner", me, sb);
                        sb->move(me);
                        set("quest/jinshe2/zf_time", time(), me);
                        return "謝謝你,家夫留下的這個「包裹」就送給你吧.\n";
                }
                else
                        return "真不巧,我這裏現在沒有,你過陣子再來吧.\n";
        }

        if( query("registered", me)<3 )
                return "我現在很忙，沒興趣和你多羅嗦！\n";

}