// hai.c 海公公
// Jay 4/6/96

inherit NPC;

string ask_for_zigong();
int ask_for_gongzi();

void create()
{
        set_name("海公公", ({"hai gonggong", "hai", "gonggong"}));
        set("title", "東廠千户");
        set("long",
"他是東廠大太監海大富，喬裝改扮成商人模樣出京尋歡作樂，長得既像
老頭又像老太太。\n"
        );

        set("gender", "無性");
        set("rank_info/respect", "公公");

        set("attitude", "heroism");
        set("class", "eunach");

        set("inquiry",([
                "自宮"    : (: ask_for_zigong :),
                "zigong"  : (: ask_for_zigong :),
                "工資"    : (: ask_for_gongzi :),
                "薪水"    : (: ask_for_gongzi :),
                "salary"  : (: ask_for_gongzi :),
                "payment" : (: ask_for_gongzi :),
                "gongzi"  : (: ask_for_gongzi :),
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
        set("combat_exp", 15000);
        set("score", 100);
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
        map_skill("parry", "bixie-jian");

        setup();
        set("chat_chance", 15);
        set("chat_msg", ({
                (: random_move :)
        }) );

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver", 50);
}

void init()
{
        add_action("do_decide", "decide");
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

        if( query("mud_age", me)<600 )
                return "這位小兄弟才出孃胎，就要自宮，好可憐見的。\n";

        set_temp("pending/zigong", 1, me);
        return "自宮？這位公子相貌堂堂，何必... 我真希望能有你的那個。自宮之後，
不可後悔，你若決心已定(decide)，告訴我。\n";
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
        set("gender", "無性", this_player());
        set("class", "eunach", this_player());
        set("combat_exp",query("combat_exp",  this_player())+1000, this_player());
        this_player()->unconcious();
        return 1;
}

int ask_for_gongzi()
{
        object me,payment;
        int paytimes;

        me = this_player();
        if( query("gender", me) != "無性")return 0;
        if ( me->query_skill("bixie-jian",1) < 60)
        {
                tell_object(me,"海公公道：下等使役太監哪有工資？進東廠再説！\n");
                       return 1;
        }
        paytimes=(query("mud_age", me)/7200);
        if( query("paytimes", me)<paytimes )
        {
            payment=new("/clone/money/gold");
            payment->move(me);
            addn("paytimes", 1, me);
            tell_object(me,"海公公道：這是你本月的份額，收好吧。\n");
        }
        else tell_object(me,"海公公道：欺負我老糊塗？你本月工資已經領取過了！\n");
        return 1;
}
