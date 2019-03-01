// /d/yixing/npc/cl_bangzhong3.c  幫眾
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>;
inherit NPC;

string ask_food();

void create()
{
        set_name("幫眾", ({ "changle bangzhong", "bangzhong" }));
        set("party/party_name", HIC"長樂幫"NOR);
        set("party/rank", "豹捷堂");
        set("long","這是一個慣于為非作歹的長樂幫眾。\n他眼珠亂轉，似乎正在想什麼壞主意。\n");
        set("gender", "男性");
        set("age", 25);
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 23);
        set("int", 20);
        set("con", 20);
        set("dex", 23);

        set("max_qi", 300);
        set("max_jing", 200);
        set("max_neili", 100);
        set("neili", 100);
        set("combat_exp", 20000);
        set("score", 1000);

        set_skill("force", 50);
        set_skill("dodge", 40);
        set_skill("cuff", 50);
        set_skill("parry", 50);

        set("inquiry", ([
                "長樂幫" : "這裡就是長樂幫總舵所在地。",
                "司徒橫" : "我對我們幫主老人家的景仰之情，有如滔滔江水連綿不絕。",
                "豹捷堂" : "自從展香主蒙冤後，豹捷堂就每況癒下。",
                "展香主" : "他被關在石室。",
                "展飛" : "他被關在石室。",
                "香主" : "各位香主的任命由幫主老人家說了算。",
                "貝海石" : "貝大夫在弊幫勞苦功高，頗得幫主信任。",
                "幫主" : "我家幫主司徒大爺乃威鎮江南的“東霸天”也。",
                "食物" : (: ask_food :),
                "菜" : (: ask_food :),
                "food" : (: ask_food :),
                "酒" : "你幫務在身，還是喝點水解解渴吧。",
                "drink" : "你幫務在身，還是喝點水解解渴吧。",
                "水" : "你隨便拿一個能裝水的來裝。",
                "water" : "你隨便拿一個能裝水的來裝。",
        ]));

        setup();

         carry_object("/clone/weapon/changjian")->wield();
}

string ask_food()
{
        object ob, ling, me = this_player();
        string myfam;

        if( is_fighting() )
                return RANK_D->query_rude(me) + "瞎了眼沒見我正忙著？！";

        myfam = (string)query("party/party_name");
        if( query("party/party_name", me) != myfam )
                return RANK_D->query_rude(me) + "莫非是想打聽我幫的秘密吧。";

        if( uptime() < (int)query("foodtime") + 30 )
                return "現在沒有酒菜。";

        if( stringp(query("party/rank", me) == "香主") )
        {
                command("bow"+query("id", me));
                set("foodtime", uptime());
                ob = new("/d/hangzhou/obj/fish");
                ob->move(me);
                message_vision("$N將一"+query("unit", ob)+ob->name()+"奉給$n。\n",this_object(),me);
                return "香主您老人家辛苦了。";
        }
        if( !(ling = present("bang ling", me)) )
                return RANK_D->query_rude(me) + "竟連自己的幫令都管不住！";
        if( query("owner", ling) != query("id", me) )
                return RANK_D->query_rude(me) + "竟連自己的幫令都管不住！";
        command("nod");
        set("foodtime", uptime());
        switch(query("score", ling)/50 )
        {
                case 0: ob = new("/d/city/obj/peanut"); break;
                case 1: ob = new("/d/city/obj/tofu"); break;
                case 2: ob = new("/d/city/obj/baozi"); break;
                case 3: ob = new("/d/city/obj/jitui"); break;
                case 4: ob = new("/d/hangzhou/obj/shrimp"); break;
                case 5: ob = new("/d/city/obj/gourou"); break;
                case 7: ob = new("/d/city/obj/ham"); break;
                default: ob = new("/d/city/obj/kaoya"); break;
        }

        ob->move(me);
        message_vision("$N將一"+query("unit", ob)+ob->name()+"奉給$n。\n",this_object(),me);
        return RANK_D->query_respect(me) + "辛苦了。";
}
