// /d/yixing/npc/cl_situ.c 司徒橫
// Last Modified by winder on Jul. 12 2002

#include <changle.h>

#define OFFICE (BANGS+"clxiaoting")

inherit NPC;

#include <ansi.h>
#include <localtime.h>

#include D_BEAUTY


int ask_join();
string ask_job();
string ask_skills();
string ask_position();
string ask_life();

string *positions = ({
        "龍靈堂",
        "獅敏堂",
        "熊威堂",
});

void create()
{
        set_name("司徒橫", ({ "situ heng", "situ" }));
        set("nickname", HIY"八爪金龍"NOR);
        set("party/party_name", HIC"長樂幫"NOR);
        set("party/rank", "幫主");
        set("long","他是一個身材高大，但有些乾瘦的中年人，雙臂很長，飛抓功夫在武林中也堪稱一絕。\n");
        set("gender", "男性");
        set("age", 45);
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 50);
        set("int", 28);
        set("con", 24);
        set("dex", 25);

        set("max_qi", 1000);
        set("max_jing", 800);
        set("max_neili", 1000);
        set("neili", 1000);
        set("jiali", 60);
        set("combat_exp", 300000);
        set("score", 10000);

        set_skill("force", 120);
        set_skill("dodge", 120);
        set_skill("parry", 120);
        set_skill("claw",  120);
        set_skill("strike", 80);
        set_skill("staff", 80);

        set_skill("poison", 80);
/*
        set_skill("huagong-dafa", 120);
        set_skill("zhaixinggong", 120);
        set_skill("sanyin-zhua",  120);
        set_skill("chousui-zhang", 80);
        set_skill("tianshan-zhang", 80);

        map_skill("force", "huagong-dafa");
        map_skill("dodge", "zhaixinggong");
        map_skill("parry", "sanyin-zhua");
        map_skill("claw",  "sanyin-zhua");
        map_skill("strike", "chousui-zhang");
        map_skill("staff", "tianshan-zhang");

        prepare_skill("claw",  "sanyin-zhua");
*/
        set("inquiry", ([
                "入幫" : (: ask_join :),
                "join" : (: ask_join :),
                "幫務" : (: ask_job :),
                "job" : (: ask_job :),
                "武功" : (: ask_skills :),
                "skills" : (: ask_skills :),
                "長樂幫" : "長樂幫威震江湖，指日可待！哈！哈！哈！",
                "貝先生" : "貝先生勞苦功高，所以我任命他為總管。",
                "貝大夫" : "貝先生勞苦功高，所以我任命他為總管。",
                "貝海石" : "貝先生勞苦功高，所以我任命他為總管。",
                "香主" : (: ask_position :),
                "position" : (: ask_position :),
                "生活" : (: ask_life :),
                "life" : (: ask_life :),
        ]));

        setup();

        carry_object("/clone/misc/cloth")->wear();
//        carry_object("/clone/weapon/feizhua")->wield();
}

string ask_job()
{
        object ob = this_player();

        if( query("party/party_name", ob) != HIC"長樂幫"NOR )
                return RANK_D->query_rude(ob) + "莫非是想打聽我幫的祕密吧。";

        return "有關具體幫務方面的事你去問貝先生。";
}

string ask_position()
{
        object *obj, ling, wage, me = this_player();
        string *poss, pos, myfam;
        int i, score, bonus, period, record;

        if( is_fighting() )
                return RANK_D->query_rude(me) + "瞎了眼沒見我正忙着？！";

        myfam = (string)query("party/party_name");
        if( query("party/party_name", me) != query("party/party_name") )
                return RANK_D->query_rude(me) + "莫非是想打聽我幫的祕密吧。";

        if( !(ling = present("bang ling", me)) )
                return RANK_D->query_rude(me) + "竟連自己的幫令都管不住！";

        if( query("owner", ling) != query("id", me) )
                return RANK_D->query_rude(me) + "竟連自己的幫令都管不住！";

        if( stringp(pos=query_temp("bangs/pos", me))){
                period=uptime()-query_temp("bangs/pos_time", me);
                if( period < 1800 )
                        return "你在這麼短的時間內不可能有多大作為，以後再讓幫主巡視" + pos + "吧。";

                score=query("score", ling);
                bonus=score-query_temp("bangs/pos_score", me);
                set_temp("bangs/pos_score", score, me);
                set_temp("bangs/pos_time", uptime(), me);

                if( bonus < period / 10 )
                        return pos + "最近表現很差呀，你這些日子在幹嗎？";

                command("nod");
//              bonus *= (score / 1000 + 1);
//              This line is the old code, if player stays on line and cumulates the
//              score, it can be very big, for example, online 15 hours can get about 20k score
//              20000 / 1000 + 1 = 21, if he only ask xiang zhu one
//              bonus = (20000 - 500) * 21 = 409500, and later bonus /= 3, add_exp = bonus +random(bonus)
//              So a player can get 200k exp like this.

//              So instead of multiply, add the bonus, so it won't increase by factors. 
                                bonus += (score / 50 +1);
                wage = new("/clone/money/silver");
                record = bonus + random(bonus);
                wage->set_amount(record);
                wage->move(me);
                message_vision("$N轉身拿出一個紅包遞給$n。\n", this_object(), me);
                log_file("test/BangPos",sprintf("%s於%s時因管轄%s%s獲利%s兩銀子\n",query("name", me),ctime(time()),myfam,pos,chinese_number(record)));

                bonus /= 3;
                addn("combat_exp", bonus+random(bonus), me);
                return pos + "在你的管轄下，最近表現不錯。";
        }

        if( query("combat_exp", me)<10000 )
                return RANK_D->query_rude(me) + "當香主未免太嫩了吧。";

        if( (score=query("score", ling))<500 )
                return "就憑你這點功勞也窺視香主之位？";

        obj = users();
        poss = positions;
        for(i = 0; i < sizeof(obj); i++) {
                if( query("party/party_name", obj[i]) == myfam){
                if( stringp(pos=query_temp("bangs/pos", obj[i])) )
                        poss -= ({pos});
                }
        }

        if( !sizeof(poss) )
                return "現在所有的香主之位都有人佔着。";

        pos = poss[random(sizeof(poss))];
        set_temp("bangs/pos", pos, me);
        set_temp("bangs/pos_time", uptime(), me);
        set_temp("bangs/pos_score", score, me);
        
        me->set_temp("apply/short",
   ({ HIR + myfam + pos + "香主"NOR + query("name",me)+"("+capitalize(query("id",me))+")" }));
        log_file("test/BangPos",sprintf("%s於%s時當上%s%s香主\n",query("name", me),ctime(time()),myfam,pos));
        command("congra");
        return "我把" + pos + "託付給你，你可要不負眾望。";
}

string ask_life()
{
        object me = this_player();
        string myfam, *beautys, beauty;

        if( is_fighting() )
                return RANK_D->query_rude(me) + "瞎了眼沒見我正忙着？！";

        myfam = (string)query("party/party_name");
        if( query("party/party_name", me) != myfam )
                return RANK_D->query_rude(me) + "莫非是想打聽我幫的祕密吧。";

        if( uptime() < (int)query("joytime") + 20 + random(20) ) {
                command("lazy");
                return "老夫最近對此沒有興趣。";
        }

        beautys = keys(info_beauty);
        beauty = beautys[random(sizeof(beautys))];

        command("hehe " + query("id"));
        set_temp("bangs/beauty", beauty, me);
        set("joytime", uptime());
        return "最近" + beauty + "這娘們怎麼樣啦？老夫這幾天都沒睡穩覺。";
}

int accept_object(object who, object ob)
{
        object ling, room;
        string myfam, beauty;
        int bonus, record;

        myfam = query("party/party_name");
        if( query("party/party_name", who) != myfam )
                return notify_fail(name() + "大怒道：大膽！想謀害本幫主？！\n");

        if( !(room = environment()) )
                return notify_fail(name() + "大怒道：等我回總舵再説吧！\n");

        if( base_name(room) != OFFICE )
                return notify_fail(name() + "大怒道：等我回總舵再説吧！\n");

        if( !stringp(beauty=query_temp("bangs/beauty", who)) )
                return notify_fail(name() + "大怒道：滾！老夫的私事不用你操心！\n");

        if( !ob->is_character() )
                return notify_fail(name() + "大怒道：這種爛東西你自己用吧！\n");

        if( query("gender", ob) != "女性" )
                return notify_fail(name() + "大怒道：老夫對人妖沒興趣！\n");

        if( query("name", ob) != beauty )
                return notify_fail(name() + "大怒道：連老夫的話都記不住！");

        if( userp(ob) )
                return notify_fail(name() + "大怒道：滾！隨便找個人回來竟想矇騙老夫！");

        if( query("eff_qi", ob)*10<query("max_qi", ob)*9
         || query("eff_jing", ob)*10<query("max_jing", ob)*9 )
                return notify_fail(name() + "大怒道：傷成這個樣子，老夫還有什麼興趣！");

        command("haha");
        delete_temp("bangs/beauty", who);
        ob->move(this_object());
        call_out("destroy_beauty", 1, ob);
        bonus=info_beauty[beauty]*100000/(100000+query("combat_exp", who));
        record = bonus + random(bonus);
        addn("combat_exp", record, who);
        addn("shen", -record, who);
        log_file("test/BangWomen",sprintf("%-10s於%-20s時上貢%-10s得%-5s經驗點\n",query("name", who),ctime(time()),beauty,chinese_number(record)));

        if( ling = present("bang ling", who) ) {
                if( query("owner", ling) == query("id", who) )
                        addn("score", bonus+random(bonus), ling);
        }

        message_vision("$N説道：好！好！好！" + myfam + "上上下下幾千人中數你最討幫主的歡心！",this_object());
        return 1;
}       

void destroy_beauty(object ob)
{
        if( ob )  destruct(ob);
}

#include BANGZHU
