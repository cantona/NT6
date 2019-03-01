// /d/yixing/npc/cl_bei.c 貝海石
// Last Modified by winder on Jul. 12 2002

inherit NPC;

#include <ansi.h>
#include <localtime.h>

string ask_job();
string ask_cure();
string ask_salary();

void create()
{
        set_name("貝海石", ({ "bei haishi", "bei" }));
        set("nickname", "著手成春");
        set("party/party_name", HIC"長樂幫"NOR);
        set("party/rank", "總管");
        set("long", 
                "他是一個身穿黃衫的老人，看上去臉色蒼白，說話有氣無力，\n"
                "還不停的咳嗽著，便似身患重病一般。\n");
        set("gender", "男性");
        set("age", 50);
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 25);
        set("int", 30);
        set("con", 28);
        set("dex", 28);

        set("max_qi", 900);
        set("max_jing", 500);
        set("neili", 700);
        set("max_neili", 700);
        set("jiali", 40);
        set("combat_exp", 200000);
        set("score", 8000);

        set_skill("force", 100);
        set_skill("dodge", 100);
        set_skill("parry", 100);
        set_skill("cuff",  120);
/*
        set_skill("ding-force",  100);
        set_skill("wuxingbu",   100);
        set_skill("wuxing-quan", 120);

        map_skill("force", "ding-force");
        map_skill("dodge", "wuxingbu");
        map_skill("cuff",  "wuxing-quan");
        map_skill("parry", "wuxing-quan");

        prepare_skill("cuff", "wuxing-quan");
*/
        set("inquiry", ([
                "長樂幫" : "長樂幫的具體事務由我總管。",
                "入幫" : "你去問幫主吧。",
                "幫務" : (: ask_job :),
                "job"   : (: ask_job :),
                "武功" : "幫主老人家的武功比我強多了，你還是向幫主學吧。",
                "香主" : "各位香主的任命由幫主老人家說了算。",
                "司徒橫" : "我對我們幫主老人家的景仰之情，有如滔滔江水連綿不絕。",
                "幫主" : "我家幫主司徒大爺乃威鎮江南的“東霸天”也。",
                "療傷" : (: ask_cure :),
                "cure" : (: ask_cure :),
                "紅包" : (: ask_salary :),
                "salary" : (: ask_salary :),
        ]));

        setup();

        carry_object("/clone/misc/cloth")->wear();
}

string ask_cure()
{
        object ling, me = this_player();
        string myfam;

        myfam = (string)query("party/party_name");
        if( query("party/party_name", me) != myfam )
                return RANK_D->query_rude(me) + "莫非是想打聽我幫的秘密吧。";  

        if( time()<query("bangs/curetime", me)+60 )
                return RANK_D->query_rude(me) + "不是剛問過我嗎？";

        if( !(ling = present("bang ling", me)) )
                return RANK_D->query_rude(me) + "竟連自己的幫令都管不住！";

        if( query("owner", ling) != query("id", me) )
                return RANK_D->query_rude(me) + "竟連自己的幫令都管不住！";

        if( query("score", ling)<10 )
                return RANK_D->query_rude(me) + "不為幫中出力，光知道撈好處。";

        if( query("eff_qi", me)*10>query("max_qi", me)*8 )
                return "傷不重的話，挨兩天就自癒了。";

        command("nod");
        addn("score", -2, ling);
        set("bangs/curetime", time(), me);
        message_vision("$N將一一包金創藥遞給$n。\n", this_object(), me);
        message_vision("$N小心翼翼地把一包金創藥敷在傷口上，只覺傷勢大為好轉，氣色看起來好多了。\n", me);
        me->receive_curing("qi", 50);
        return "服一包金創藥就沒事了。";
}

string ask_salary()
{
        object wage, ling, me = this_player();
        string myfam;
        int amount;

        myfam = (string)query("party/party_name");
        if( query("party/party_name", me) != myfam )
                return RANK_D->query_rude(me) + "莫非是想打聽我幫的秘密吧。";

//        if( me->query_temp("bangs/pos") )
        if( query("bangs/pos", me) )
                return RANK_D->query_respect(me) + "已是一堂之主了，幫主那兒定有重賞。";

        if( !(ling = present("bang ling", me)) )
                return RANK_D->query_rude(me) + "竟連自己的幫令都管不住！";

        if( query("owner", ling) != query("id", me) )
                return RANK_D->query_rude(me) + "竟連自己的幫令都管不住！";

        if( time()<query("bangs/salarytime", me)+1800 )
                return RANK_D->query_rude(me) + "不是剛問過我嗎？";

        if( (amount=query("score", ling))<30 )
                return RANK_D->query_rude(me) + "最近表現很差呀，你這些日子在幹嗎？";

        command("nod");
        set("bangs/salarytime", time(), me);

        wage = new("/clone/money/silver");
        wage->set_amount(amount);
        delete("score", ling);
        wage->move(me);
        message_vision("$N轉身拿出一個紅包遞給$n。\n", this_object(), me);
        return "你最近表現不錯，這份紅包你拿去花吧。";
}

#include "guanjia.h";
