#include <ansi.h>
inherit NPC;

string ask_me();

void create()
{
        set_name("譚友紀", ( { "tan youji", "tan" }) );
        set("title", "揚州府師爺");
        set("gender", "男性" );
        set("age", 57);

        set("combat_exp", 30000);
        set_skill("unarmed", 50);
        set_skill("dodge", 60);
        set_temp("apply/attack",  20);
        set_temp("apply/defense", 20);
        set_temp("apply/damage",  20);
        set("shen_type", 0);

        set("inquiry", ([
                "叫化雞" : (: ask_me :),
                "揚州府":"只要加入官府(join guanfu)，就可以為朝廷出力。\n",
                "官府":"只要加入官府(join guanfu)，就可以為朝廷出力。\n",
                "當官":"只要加入官府(join guanfu)，就可以為朝廷出力。\n",
                "捕快":"只要加入官府(join guanfu)，就可以為朝廷出力。\n",
                "任務":"只要加入官府(join guanfu)，就可以為朝廷出力。\n",
                "task":"只要加入官府(join guanfu)，就可以為朝廷出力。\n",
                "quest":"只要加入官府(join guanfu)，就可以為朝廷出力。\n"
        ]));
        set("chat_chance", 3);
        set("chat_msg", ({
                "譚師爺道：現在想當官的人越來越多了！\n",
        }) );
        setup();
        carry_object("/clone/misc/cloth")->wear();
}
void init()
{
        object ob;
        mapping myfam;
        ob = this_player();
        ::init();
        add_action("do_join", "join");
}

int do_join(string arg)
{
        object ob = this_player();
        if(!arg || arg!="guanfu") return notify_fail("譚友紀道：你要加入什麼組織？\n");
        if( query("officerlvl", ob)>0 )
        {
                message_vision(HIC"譚友紀説道：你已經是揚州府捕快了。\n"NOR,ob);
                return 1;
        }
        if( query("combat_exp", ob)<20000 )
        {
                message_vision(HIC "譚友紀對$N搖頭道：你的實戰經驗太低。\n" NOR,ob);
                return 1;
        }
        if( query("class", ob) != "bonze" && 
                query("class", ob) != "lama" && 
                query("class", ob) != "quanzhen" && 
                query("class", ob) != "eunach" )
                set("class", "officer", ob);
        set("officerlvl", 1, ob);
        message_vision(HIY "譚友紀對$N道：從現在起你就是個實習捕快！\n" NOR,ob);
        addn("weiwang", 10, ob);
        message_vision(HIC "$N的江湖威望提高了！\n" NOR,ob);
        tell_object(ob,"你現在的江湖威望是"+chinese_number((query("weiwang", ob)))+"。\n"NOR);
        return 1;
}
string ask_me()
{
        if( query_temp("marks/雞", this_player()) )
        {
                say("好小子，你怎麼知道我喜歡吃叫化雞？\n");
                command("lick");
                say("既然你我成了食友，我就告訴你吧。付耳過來！\n");
                command("whisper"+query("id", this_player())+"你去北京找全聚德的老闆，只要告訴他是我叫你去的，他就會...");
                delete_temp("marks/雞", this_player());
                set_temp("marks/雞2", 1, this_player());
                return "今天嗯....啊....那個天氣很好....\n";
        }
        else if( query_temp("marks/雞2", this_player()) )
                return "我是個浙江人，也沒有你那麼羅嗦！\n";
        else
                return "泥縮絲米偶釘布懂\n";
}