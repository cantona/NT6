// /d/xingxiu/npc/anran.c
// Last Modified by winder on Apr. 25 2001

#include <ansi.h>
inherit NPC;
inherit F_GUARDER;

mapping *quest = ({
  (["name":                "xianrenya",
    "start" :              "/d/xingxiu/xianrenya",
    "place" :              "仙人崖",]),
  (["name":                "silk1",
    "start" :              "/d/xingxiu/silk1",
    "place" :              "嘉峪關以西的絲綢之路",]),
  (["name":                "shanjiao",
    "start" :              "/d/xingxiu/shanjiao",
    "place" :              "天山腳下",]),
  (["name":                "xinglongshan",
    "start" :              "/d/xingxiu/xinglongshan",
    "place" :              "興隆山",]),
  (["name":                "tugu",
    "start" :              "/d/xingxiu/tugu",
    "place" :              "吐谷渾伏俟城",]),
});
string ask_job();

void create()
{
        set_name("黯然子", ({ "anran zi", "anran", "zi" }) );
        set("gender", "男性" );
        set("nickname", "星宿派六弟子");
        set("age", 31);
        set("location", 1);
        set("unique", 1);
        set("long", "黯然子在星宿二代十弟子中排行第六，
但他對星宿派武功有些獨創，功力不淺。\n");
        set("env/wimpy", 40);
        set("str", 29);
        set("dex", 26);
        set("con", 24);
        set("int", 22);
        set("per", 18);
        set("shen", -7500);

        set_skill("force", 105);
        set_skill("huagong-dafa", 115);
        set_skill("dodge", 110);
        set_skill("zhaixinggong", 160);
        set_skill("strike", 110);
        set_skill("chousui-zhang", 160);
        set_skill("poison", 110);
        set_skill("parry", 110);
        set_skill("staff", 110);
        set_skill("tianshan-zhang", 160);
        set_skill("literate", 70);
        set_skill("claw", 110);
        set_skill("sanyin-wugongzhao", 160);
        map_skill("claw", "sanyin-wugongzhao");
        map_skill("force", "huagong-dafa");
        map_skill("dodge", "zhaixinggong");
        map_skill("strike", "chousui-zhang");
        map_skill("parry", "chousui-zhang");
        map_skill("staff", "tianshan-zhang");
        prepare_skill("claw", "sanyin-wugongzhao");
        prepare_skill("strike", "chousui-zhang");

        set("max_qi", 2000);
        set("max_jing", 2000);
        set("eff_jingli", 1800);
        set("score", -14000);
        set("combat_exp", 750000);
        set("chat_chance_combat", 5);
        set("chat_msg_combat", ({
                (: exert_function, "huagong" :),
                (: perform_action, "strike.biyan" :),
        }));
        create_family("星宿派", 2, "弟子");
        set("attitude", "peaceful");
        set("inquiry", ([
                "丁春秋" : "丁春秋是你叫的嗎？沒大沒小的。以後叫老仙！",
                "截殺" : (: ask_job :),
                "搶劫" : (: ask_job :),
                "rob"  : (: ask_job :),
                "job"  : (: ask_job :),
                "吹捧" : "小師妹最討老仙喜歡，你去問她吧。",
        ]));
          set("coagents", ({
                  ([ "startroom" : "/d/xingxiu/riyuedong",
                     "id"        : "ding chunqiu", ]),
          }));


        setup();
        carry_object("/clone/weapon/gangzhang")->wield();
        carry_object("/clone/cloth/dao-cloth")->wear();
        add_money("silver", 10);
}
void attempt_apprentice(object ob)
{
        command("consider");
        command("say 星宿門中各人都有專職，要拜師你去找我師兄弟吧！");
        return;
}
int accept_object(object me, object obj)
{
        object ob=this_object();
        if(!me || environment(me) != environment()) return 0;
        if(!objectp(obj)) return 0;
        if(!present(obj, me)) return notify_fail("你沒有這件東西。");
        if(userp(obj))
        {
                command("consider"+query("id", me));
                command("say 你拿個快死的人來騙我？");
                return 0;
        }
        if(!me->query_condition("xx_task2"))
        {
                command("shake"+query("id", me));
                command("say 這麼久才回來，我還不如找別人來幹！");
                return 0;
        }
        if( query("id", obj) == "prize" && query("owner", obj) == query("id", me) )
        {
                command("nod"+query("id", me));
                command("say 好樣的！這才象我們星宿派的作風！\n");
                message_vision(HIY"$N將$n"HIY"拆開，拿出了一大堆金銀財寶。\n"NOR,ob, obj);
                remove_call_out("del_temp");
                remove_call_out("destroying");
                call_out("destroying", 5, obj, ob, me);
                return 1;
        }
        if( query("money_id", obj) )
        {
                command("pat"+query("id", me));
                command("say 錢我有的是，你以後還是留給自己吧。");
                return 0;
        }
        if( query("owner", obj) != query("id", me) )
        {
                command("hehe"+query("id", me));
                command("say 不錯啊，但這活可不是你乾的。");
                return 1;
        }
        else return 0;
}
void destroying(object obj, object ob, object me)
{
        object n_money;
        int exp,pot;
        if(obj) destruct(obj);
        if(!ob) return;
        if(!me || environment(me) != environment())
        {
                command("say 咦，人呢？");
                return;
        }
        command("pat"+query("id", me));
        message_vision(HIY "$N對$n説道：你這次做得極為出色，這是你該得的部分，拿去吧！\n"NOR,ob, me);
        n_money = new("/clone/money/gold");
        n_money->move(me);
        n_money->add_amount(1);
        set_temp("job2_exp", 150+(query_temp("biaoshi", me)*(random(50)+50)), me);
        exp=query_temp("job2_exp", me);
        pot=query_temp("biaoshi", me)*20;
        addn("combat_exp", exp, me);
        addn("potential", pot, me);
        set_temp("prize_reason", "搶劫", me);
        set_temp("can_give_prize", 1, me);
        set_temp("prize_exp", exp, me);
        set_temp("prize_pot", pot, me);
        tell_room(environment(me),me->name()+"數着錢袋裏的金子，臉上的肌肉不住地顫動，眼睛散發着一種奇怪的光芒。\n" NOR, ({ me }));
        tell_object(me,"嘿嘿，發了！得到"+chinese_number(query_temp("job2_exp", me))+"點經驗。\n");
        log_file("mission/ms_shangdui",sprintf("%20s做搶劫任務，殺了%2i個鏢師，得到：%4i點EXP和%4i點潛能。\n",
        me->name(1)+"("+getuid(me)+")",query_temp("biaoshi", me),query_temp("job2_exp", me),query_temp("biaoshi", me)*20));
        delete_temp("job2_exp", me);
        delete_temp("biaoshi", me);
        me->clear_condition("xx_task2",1);
        delete_temp("job_asked", ob);
        return;
}
string ask_job()
{
        object me, ob;
        mapping aquest;
        int exp, j;
        aquest = quest[random(sizeof(quest))];
        me = this_player();
        ob = this_object();
        exp=query("combat_exp", me);

        if(ob->is_busy() || ob->is_fighting())
                return "沒看見我正忙着嗎？一邊等着去！";
        if( !query("family", me) )
                return "看得出你對老仙態度恭敬，何不加入我星宿派呢？";
        if( query("family/family_name", me) != "星宿派" && 
                !query_temp("ding_flatter", me) )
                return "你對老仙的態度看上去不太恭敬啊！";
        if(me->query_condition("wait_xx_task"))
                return "上次把我師兄給的任務搞砸了，這次你就等等吧。";
        if(me->query_condition("xx_task2"))
                return "我現在還沒有得到任何消息，你等會兒再來吧。";
//        if(me->query_condition("job_busy"))
  //              return "你現在還有任務在身，等會兒再來吧。";
        if( query_temp("job_asked", ob) == query("id", me) )
                return "不是叫你先去那裏等我嗎？怎麼還賴在這裏？";
        if( query_temp("job_asked", ob) )
                return "嘿嘿，你來晚了，等下一次吧。";
        if(exp<200000)
                return "哈哈哈，你再加把力練功吧。";
        if(exp>=750000)
                return "你的功力已經超過我了，還用跟我出去做事？";
        if( query("shen", me)>-10000 )
                return "哼！看來你的心腸還不夠黑啊，這種事你不問也罷。";
        if(exp>=600000) j=6;
        else if(exp>=500000) j=5;
        else if(exp>=400000) j=5;
        else if(exp>=300000) j=4;
        else j=3;

        set_temp("xx_job2", 1, me);
        delete_temp("biaoshi", me);
        message_vision(CYN "\n$N陰陰一笑，説道：這兩天會有一隊駱駝商隊經過，你夠膽就和我一起去看看吧。\n"NOR, ob, me);
        set_temp("job_asked",query("id",  me), ob);
        set_temp("dest", aquest["name"], ob);
        set_temp("start_place", aquest["start"], ob);
        set_temp("place", aquest["place"], ob);
        set_temp("j", j, me);
        me->apply_condition("xx_task2", 10 + j);
        me->start_busy(1);
        call_out("going", 30, ob);
        return "我還有些事要辦，你先去"+query_temp("place", ob)+"等我。\n";
}
void going(object me)
{
        message_vision("$N急急忙忙地走了出去。\n", me);
        me->move(query_temp("start_place", me));
        message_vision("$N急急忙忙地走了過來。\n", me);
}
void init()
{
        object ob, where, me;
        ::init();
        ob=this_object();
        where = environment(ob);
        if( query_temp("dest", ob) )
        {
                if(interactive(me = this_player()) &&
                        query_temp("xx_job2", me) && 
                        query_temp("job_asked", ob) == query("id", me) && 
                        file_name(where) == query_temp("start_place", ob) )
                {
                        remove_call_out("waiting");
                        call_out("do_back", 120, ob);
                        call_out("waiting", 1, ob, me);
                }
                else
                {
                        remove_call_out("do_back");
                        call_out("do_back", 90, ob);
                }
        }
}
void waiting(object ob, object me)
{
        if(!ob || !living(me)) return;
        command("nod"+query("id", me));
        command("say 好，我們就在這裏等着他們來吧。");
        set_temp("wait_target", 1, ob);
        set_temp("wait_target", 1, me);
        remove_call_out("wait_target");
        call_out("wait_target", 30, ob, me);
        return;
}
void do_back(object me)
{
        delete_temp("wait_target", me);
        delete_temp("start_place", me);
        delete_temp("place", me);
        delete_temp("dest", me);
        message_vision("$N轉過山丘，幾個起落就不見了。\n", me);
        me->move("/d/xingxiu/riyuedong1");
        message_vision("$N急急忙忙地走了過來。\n", me);
        remove_call_out("del_temp");
        call_out("del_temp", 300, me);
}
void del_temp(object me) {delete_temp("job_asked", me);}

int wait_target(object ob, object me)
{
        object obj;
        if(!objectp(present(me, environment(ob))))
        {
                message_vision("$N説道：耶？那傢伙怎麼不見了？\n", ob);
                remove_call_out("do_back");
                do_back(ob);
                return 1;
        }
        if(!objectp(ob = present("anran zi", environment(me))))
        {
                tell_object(me,"你發現黯然子不見了，只好灰溜溜地轉身離開。\n");
                tell_room(environment(me),me->name()+"突然一臉茫然的表情，看來是想要離開了。\n", ({ me }));
                delete_temp("xx_job2", me);
                me->clear_condition("xx_task2");
                delete_temp("wait_target", me);
                return 1;
        }
        obj = new("/d/xingxiu/npc/shangdui");
        obj->move(environment(me));
        set("arg",query_temp("dest",  ob), obj);
        message_vision(HIY"\n只聽一陣駱駝風鈴聲傳來，一隻駱駝商隊出現在眼前！\n\n"NOR, ob);
        tell_object(me,"獵物終於出現了！\n");
        message_vision(HIY"$N對着$n大聲命令道：你快搶(qiang)商隊，我來對付其他人！\n"NOR, ob, me);
        message_vision("説完$N就衝上前去，和幾個護鏢鏢師打鬥追逐開了。\n", ob);
        remove_call_out("do_back");
        do_back(ob);
        delete_temp("wait_target", me);
        set_temp("rob_start", 1, me);
}
