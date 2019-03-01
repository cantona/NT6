// hai.c 海公公
#include <ansi.h>
inherit NPC;
string ask_for_zigong();
string ask_for_jingong();
int do_pretend ( string arg );

void create()
{
        set_name("海公公", ({"hai gonggong", "hai", "gonggong"}));
        set("title", "東廠千户");
        set("long",
                "他是東廠大太監海大富，喬裝改扮成商人模樣出京尋歡作樂，長得既像老頭又像老太太。\n"
        );

        set("gender", "無性");
        set("rank_info/respect", "公公");

        set("attitude", "heroism");
        set("class", "eunach");

        set("inquiry",([
                "自宮"  : (: ask_for_zigong :),
                "進宮"  : (: ask_for_jingong :),
                "皇宮"  : (: ask_for_jingong :),
        ]));

        set("age", 60);
        set("shen_type", -1);
        set("str", 25);
        set("int", 20);
        set("con", 20);
        set("dex", 25);
        set("max_qi", 500);
        set("max_jing", 100);
        set("neili", 500);
        set("max_neili", 500);
        set("jiali", 100);
        set("combat_exp", 75000);
        set("score", 5000);
        set("apply/attack",  30);
        set("apply/defense", 30);

        set_skill("force", 50);
        set_skill("unarmed", 50);
        set_skill("sword", 50);
        set_skill("dodge", 50);
        set_skill("parry", 50);
        set_skill("bixie-jian", 50);

        map_skill("dodge", "bixie-jian");
        map_skill("sword", "bixie-jian");

        setup();
        set("chat_chance", 15);

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/d/city/obj/jiudai");
        carry_object("/d/beijing/obj/yaofen");
        add_money("silver", 50);
}

void init()
{
        add_action("do_decide", "decide");
        add_action("do_pretend", "pretend");
}


string ask_for_zigong()
{
        object me;

        me = this_player();

        if( query("gender", me) == "無性" )
                return "你我同是閹人，何必開如此無聊的玩笑？\n";

        if( query("gender", me) == "女性" )
                return "我雖已廢，但一樣可以給你這個小美人帶來快樂，要不要試試？\n";
        if ((int)me->query_str() > 28 )
                return "這位好漢過於粗壯，自宮有礙觀瞻，不妥，不妥。\n";

        set_temp("pending/zigong", 1, me);
        return "自宮？這位公子相貌堂堂，何必... 我真希望能有你的那個。自宮之後，不可後悔，你若決心已定(decide)，告訴我。\n";
}

string ask_for_jingong()
{
        object me;

        me = this_player();

        if( query("gender", me) == "無性" )
        return("海公公笑吟吟地説道：您既已是公公了，自然可以進宮。\n");          

        if( query("gender", me) == "男性" )
        {
        set_temp("pending/zigong", 1, me);
        return("海公公笑吟吟地説道：並不是一定要自宮才可以進皇宮的；\n"+"不過，你若決心已定(decide)，我就成全了你。\n");
        }

        if( query("gender", me) == "女性" )
        return("海公公搖頭道：不行的，你長得太醜了。\n");                
}


int do_decide()
{
        if( !query_temp("pending/zigong", this_player()) )
                return 0;

        message_vision(
                "$N一咬牙，褪下中衣。（女玩家閉眼！）\n\n"
                "$n伸出長劍插到$N兩腿之間，飛速一剜，……\n\n"
                "$N頓時慘叫一聲昏了過去……\n\n",
                this_player(), this_object() );
        command("chat 嗨……");
        command("hehe");
        delete_temp("pending/zigong", this_player());
        delete_temp("pending/jingong", this_player());
        set("gender", "無性", this_player());
        set("class", "eunach", this_player());
        set("combat_exp",query("combat_exp",  this_player())+1000, this_player());
        this_player()->unconcious();
        
        return 1;
}

int accept_object(object me, object ob)
{
        if( !me || environment(me) != environment() ) return 0;
        if ( !objectp(ob) ) return 0; 
        if ( !present(ob, me) ) return notify_fail("你沒有這件東西。");
        if( query("name", ob) == "藥粉" )
        {
         write(HIC "海公公打開藥包，伸出小指，用指甲挑了一點粉末，\n"
         +"就着酒泯了，仍是不住咳嗽。\n" NOR);
               if(objectp(present("xiao", environment(me))))
                {
                command("say 奇怪，你怎麼也有這種藥。");   
                }
               else
                {
                 command("smile"+query("id", ob));
                 if( query_temp("haspretend", me) )
                 { 
                 command("say 多謝啦，小桂子，我現在好多了 !");
                 delete_temp("haspretend", me);
                 set("huanggong\\canenter", 1, me);
                 }              
                 else command("say 奇怪，你怎麼也有這種藥。");   
                }
        }
        else 
        {
                 command("shake ");
                 command("say 這種東西鬼才要 ! 老子宰了你 !");
                 remove_call_out("kill_ob");
                 call_out("kill_ob", 1, this_player());
        }   
             return 1;
}


int do_pretend ( string arg )
{
   object ob ;
   ob = this_player () ;
   if( !arg && arg!="guizi"&&arg!="xiao"&&arg!="xiao guizi")
     return notify_fail("\n你要裝成誰？\n");
   
if(objectp(present("xiao", environment(ob))))
{
write(HIR "\n海公公大叫一聲：你敢冒充小桂子，老子宰了你！\n" NOR);
remove_call_out("kill_ob");
call_out("kill_ob", 1, this_player());
return 1;
}
if( query("gender", ob) == "男性" )
{
set_temp("haspretend", 1, ob);
message_vision("\n$N裝成了小桂子，$n沒吭聲。\n",this_player(),this_object());
message_vision("\n海公公看了$N一眼，説“唉，是不是又該吃藥了？”\n",this_player());
return 1;
}
}


void die()
{
        say("海公公掙扎着歎道：唉，老皇爺的事兒我沒辦成啊！\n");                 
        message_vision("$N慘嚎一聲，死了！\n", this_object());
        ::die();
}
