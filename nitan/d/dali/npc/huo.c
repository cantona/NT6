// huo.c

inherit NPC;

string ask_for_zigong();
int ask_for_gongzi();

void create()
{
        set_name("霍先生", ({"huo xiansheng", "huo", "xiansheng"}));
        set("long",
"他一身邋遢，形容委瑣，整天迷迷糊糊的睡不醒模樣。可是他的賬務十幾年來無可挑剔。
原來他就是伏牛派的崔百泉，為避仇禍隱居於此。\n"
        );

        set("gender", "男性");
        set("attitude", "heroism");

        set("inquiry",([
                "工資"    : (: ask_for_gongzi :),
                "薪水"    : (: ask_for_gongzi :),
                "salary"  : (: ask_for_gongzi :),
                "payment" : (: ask_for_gongzi :),
                "gongzi"  : (: ask_for_gongzi :),
        ]));

        set("age", 51);
        set("shen_type", 0);
        set("str", 25);
        set("int", 20);
        set("con", 20);
        set("dex", 25);
        set("max_qi", 500);
        set("max_jing", 100);
        set("neili", 500);
        set("max_neili", 500);
        set("jiali", 100);
        set("combat_exp", 100000);
        set("score", 100);
        set("apply/attack",  30);
        set("apply/defense", 30);

        set_skill("force", 50);
        set_skill("unarmed", 50);
        set_skill("sword", 50);
        set_skill("dodge", 50);
        set_skill("parry", 50);

        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver", 50);
}

int ask_for_gongzi()
{
        object me,payment;
        int paytimes;
        string oldtitle;

        me = this_player();
        oldtitle=query("title", me);
        if (strsrch(oldtitle, "大理鎮南王府武將") >= 0) 
        {
            paytimes=(query("mud_age", me)/7200);
            if( query("dlpaytimes", me)<paytimes )
            {
                payment=new("/clone/money/gold");
                payment->move(me);
                addn("dlpaytimes", 1, me);
                tell_object(me,"霍先生道：這是你本月的份額，收好吧。\n");
            }
            else tell_object(me,"霍先生道：欺負我老糊塗？你本月工資已經領取過了！\n");
        }
        else
        tell_object(me,"霍先生道：欺負我老糊塗？等你升到武將再來領工資！\n");
        return 1;
}
