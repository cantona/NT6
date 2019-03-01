#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("張翠山", ({ "zhang cuishan", "zhang" }));  
        set("long",
        "一個二十一二歲的少年，面目俊秀，雖然略覺清\n"
        "□，但神朗氣爽，身形的瘦弱竟掩不住一股剽悍\n"
        "之意。\n");
        set("attitude", "heroism");
        set("title", "武當五俠");
        set("nickname", WHT"銀鉤鐵劃"NOR);
        set("per", 30);
        set("age", 21);
        set("shen_type", 1);
        set("combat_exp", 1400000);
        set("score", 60000);

        set_skill("unarmed", 200+random(50));
        set_skill("parry", 200+random(50));
        set_skill("dodge", 200+random(50));

        create_family("武當派", 2, "弟子");
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/beijing/npc/obj/cloth1")->wear();
}
int accept_fight(object who)
{
        command("say 我是不會和你打架的！");
        return 0;
}
int accept_hit(object who)
{
        command("say 我是不會和你打架的！");
        return 0;
}
int accept_kill(object who)
{
        command("say 怎麼，要行兇麼？在這裡恐怕由不得你！");
        return 1;
}
int accept_ansuan(object who)
{
        return notify_fail("你剛想暗算，可是只見會場裡黑壓壓的擠滿了人，根本看不清楚。\n");
}
void receive_damage(string type, int n)
{
        return;
}
void receive_wound(string type, int n)
{
        return;
}
int begin(object me)
{
        if( query_temp("biwu", me) )
        return notify_fail("正在和別人比試呢！急什麼急！\n");

        set_temp("biwu", 1, me);
        command("say 閣下武功高強，就請持此屠龍刀去，卻請饒了島上一幹人的性命。");
        message_vision(CYN "$N說道：敢問閣下是誰，憑什麼對我發號施令，我們先來比試比試。\n" NOR, me);
        message_vision(CYN "$N說道：兵刃、拳腳、內功、暗器、輕功、水功，隨便哪一樁，由你自己挑，我都奉陪。\n" NOR, me);
        remove_call_out("biwu");
        call_out("biwu",3,me);
        set_temp("bizhang", 1, me);
        return 1;
}
void biwu(object me)
{
        command("say 我不是跟你比兵刃，只是比寫幾個字。");
        message_vision(HIR "\n張翠山說著緩步走到左首山峰前一堵大石壁前，吸一口氣，猛地裡雙腳一撐，提身而起。\n"NOR,this_object());
        remove_call_out("biwu2");
        call_out("biwu2",8,me);
}
void biwu2(object me)
{
        message_vision(HIR "\n張翠山身形縱起丈余，跟著使出“梯雲縱”絕技，右腳在山壁一撐，一借力，又縱起兩丈。\n"NOR,this_object());
        message_vision(HIR "\n手中判官筆看準石面，嗤嗤嗤幾聲，已寫了一個“"NOR+HIY"武"NOR+HIR"”字。\n"NOR,this_object());
        message_vision(HIR "\n張翠山一個字寫完，身子便要落下，突然左手揮出，銀鉤在握，倏地一翻，鉤住了石壁的縫隙。\n"NOR,this_object());
        message_vision(HIR "\n利用縫隙支住身子的重量，右手跟著又寫了個“"NOR+HIY"林"NOR+HIR"”字。\n"NOR,this_object());
        remove_call_out("biwu3");
        call_out("biwu3",8,me);
}
void biwu3(object me)
{
        message_vision(HIR "\n張翠山兩個字寫罷，跟著又寫“"NOR+HIY"至"NOR+HIR"”字，“"NOR+HIY"尊"NOR+HIR"”字。越寫越快，但見石屑紛紛而下。\n" NOR, this_object());
        message_vision(HIR "\n字跡或如靈蛇盤騰，或如猛獸屹立，須臾間二十四字一齊寫畢。\n\n" NOR, this_object());
        message_vision(HIR "這一番石壁刻書，當真如李白詩雲：\n\n"NOR,this_object());
        message_vision(HIW "            飄風驟雨驚颯颯，落花飛雪何茫茫。\n\n" NOR, this_object());
        message_vision(HIW "            起來向壁不停手，一行數字大如鬥。\n\n" NOR, this_object());
        message_vision(HIW "            恍恍如聞鬼神驚，時時只見龍蛇走。\n\n" NOR, this_object());
        message_vision(HIW "            左盤右蹙如驚雷，狀同楚漢相攻戰。\n\n" NOR, this_object());
        message_vision(HIR "\n張翠山寫到“鋒”字的最後一筆，銀鉤在石壁上一撐，翻身落地，輕輕巧巧的落在殷素素身旁。\n" NOR, this_object());
        message_vision(HIR "\n$N凝視著石壁上那三行大字，良久良久，沒有作聲。\n" NOR, me);
        remove_call_out("shu");
        call_out("shu",4,me);
}
void shu(object me)
{
        message_vision(HIR "\n$N終于嘆了一口氣，說道：“我寫不出，是我輸了。”\n"NOR, me);
        message_vision(CYN "$N說道：“請問閣下有何吩咐？”\n"NOR, me);
        delete_temp("bizhang", me);
        set_temp("shu", 1, me);
        remove_call_out("end");
        call_out("end",5,me);
}
void end(object me)
{
        object ding,dao;
        object obj = present("yin susu");
        command("say 既是我勝了，就請饒了一幹人的性命。");
        command("say 走吧");
        delete_temp("biwu", me);
        ding = present("ding", environment());
        if (! objectp(ding)) return;
        dao = present("tulong blade", ding);
        if (! objectp(dao)) return;
        if (objectp(dao))
        {
                command("rumor "+me->name(1)+"在王盤山擊敗了各路英豪，奪得了屠龍寶刀。");
                if( !query("guan/王盤揚刀威名揚", me) )
                {
                        addn("combat_exp", 20000, me);
                        addn("potential", 500, me);
                        addn("weiwang", 10000, me);
                        addn("score", 5000, me);
                }
                set("guan/王盤揚刀威名揚", 1, me);
                dao->move(me, 1);
        }
        tell_object(me,HIW"\n你得到了屠龍寶刀！\n\n");
        message_vision(HIC"\n$N和$n等三人上船，揚帆而去。\n"NOR,me,this_object());
        if (objectp(obj)) obj->move("/d/tulong/tulong/boat");
        this_object()->move("/d/tulong/tulong/boat");
        me->move("/d/tulong/tulong/boat");
        remove_call_out("storm");
        call_out("storm",random(30),me);
}
void storm(object me)
{
        message_vision(HIB "\n突然之間，$N身子一側，滾了幾個轉身，只聽得疾風呼嘯，\n" NOR,this_object());
        message_vision(HIB "波浪轟擊之聲，似乎千百個巨浪同時襲到。\n" NOR,this_object());
        remove_call_out("storm2");
        call_out("storm2",4,me);
}
void storm2(object me)
{
        message_vision(HIB "\n腳底下艙板鬥然間向左側去，船中的海水又向外倒瀉，\n" NOR,this_object());
        message_vision(HIB "但聽得狂風呼嘯，身周盡是海水。\n" NOR,this_object());
        remove_call_out("storm3");
        call_out("storm3",4,me);
}
void storm3(object me)
{
        message_vision(HIB "\n天上烏雲慢慢散開，露出星夜之光。\n" NOR,this_object());
        message_vision(HIB"\n船慢慢地向東向北飄流。\n"NOR,this_object());
        remove_call_out("storm4");
        call_out("storm4",4,me);
}
void storm4(object me)
{
        message_vision(HIB "\n船慢慢地向東向北飄流。\n" NOR,this_object());
        remove_call_out("storm5");
        call_out("storm5",4,me);
}
void storm5(object me)
{
        message_vision(HIB "\n船慢慢地向東向北飄流。\n" NOR,this_object());
        remove_call_out("storm6");
        call_out("storm6",4,me);
}
void storm6(object me)
{
        message_vision(HIB "\n船慢慢地向東向北飄流。\n" NOR,this_object());
        remove_call_out("arrive");
        call_out("arrive",4,me);
}
void arrive(object me)
{
        object obj = present("yin susu");
        message_vision(HIY "只見正北方一條大船向這方駛來，看來回到中原了。\n" NOR,this_object());
        message_vision(CYN "張翠山抱拳說道：咱們就此別過，後會有期。\n" NOR,me,this_object());
        if (objectp(obj)) obj->move("/d/tulong/tulong/boat3");
        this_object()->move("/d/tulong/tulong/boat3");
        me->move("/d/tulong/tulong/boat3");
}
void init()
{
       add_action("do_get", "get");
}
int do_get(string arg)
{
       object obj,env,ding;
       string what,where;
       if(!arg)
       return 0;
       if(sscanf(arg,"%s from %s",what, where) !=2)
       return 0;
       if(objectp(present("mai jing", environment())) || objectp(present("guo sanquan",environment())))
       return 0;
       if(where == "ding")
       {
              message_vision(CYN "$N說道：在下武當張翠山，這廂有理了！\n" NOR,
                                 this_object());
              delete_temp("bizhang", this_player());
              begin(this_player());
              return 1;
       }
       return 0;
}
