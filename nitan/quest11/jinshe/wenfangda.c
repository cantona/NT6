// /d/city/npc/wenfangda
// by daidai 加入金蛇quest相關
inherit NPC;
#include <ansi.h>
string ask_quest(); 
void create()
{
        set_name("温方達", ({ "wen fangda", "wen", "fangda" }));
        set("title", "温家五老");
        set("long", 
        "他就是温家五老的老大温方達。\n"
        "一個精瘦的老者，一雙眼睛露出狡猾的目光。\n");
        set("gender", "男性");
        set("age", 66);
        set("attitude", "friendly");
        set("shen", -10000);
        set("str", 35);
        set("int", 30);
        set("con", 25);
        set("dex", 27);

        set("max_qi", 2000);
        set("eff_jingli", 1800);
        set("max_jing", 1800);
        set("neili", 3000);
        set("max_neili", 3000);
        set("jiali", 70);
        set("combat_exp", 1000000);
         

        set_skill("force", 150);
        set_skill("yijin-jing", 150);
        set_skill("dodge", 150);

        set_skill("shaolin-shenfa", 150);
        set_skill("cuff", 150);
        set_skill("wenjia-daofa", 160);
        set_skill("parry", 150);
        set_skill("blade", 150);
        set_skill("wenjia-quan", 150);
        set_skill("literate", 110);

        map_skill("force", "yijin-jing");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("cuff", "wenjia-quan");
        map_skill("parry", "wenjia-daofa");
        map_skill("blade", "wenjia-daofa");
        prepare_skill("cuff", "wenjia-quan");

        set("inquiry", ([
                "金蛇郎君" : (: ask_quest:),
                "夏雪宜" : (: ask_quest:),
        ]));

        setup(); 
        carry_object(ARMOR_D("cloth"))->wear();
        carry_object("/clone/weapon/blade1")->wield();
}

string ask_quest()
{
        object me, ob, room;
        me = this_player();
        ob = this_object();

        if( query("quest/金蛇劍法/pass", me) )
        { 
           // 解了quest還來問 找抽！！ by daidai
           call_out("outwuguan",1,me);
           return "你是怎麼知道這個奸賊的？";
        }
        if( !query_temp("quest/金蛇劍法/start", me) )
        {
           command("heng");
           return "那是我温家堡的仇人！";
        }
        message_vision(HIG"$N臉上露出異樣的神色。\n"NOR, ob);
        command("look"+query("id", me));
        command("sigh");
        command("say 這麼説你就是金蛇奸賊的傳人了，來報仇了？");
         message_vision(HIC"$N一擺手：“跟我來吧。”帶着$n向練武場走去。\n"NOR, ob, me);
        
        set_temp("quest/金蛇劍法/start_kill", 1, me);
        delete_temp("quest/金蛇劍法/start", me);
//         me->move("/d/xiangyang/wen/quest/lianwu");
// 為了避免有多個玩家同時解quest by daidai
         room=new("/d/xiangyang/wen/quest/lianwu");
        me->move(room);
        return "哼......";
}
void outwuguan(object me)
{
        object ob=this_object();
        object *inv;
        if(!me) return;
        command("ah");
        command("say 你是金蛇郎君那個奸賊的傳人！來人啊！給我殺了這廝！");
        message_vision(HIR"只見一羣家丁揮舞兵器向$N衝殺而來，$N落荒而逃。\n"NOR, me);
        inv = filter_array(deep_inventory(me), (: userp :));
        if( sizeof(inv))
                inv->move(environment(ob));
        me->move("/d/xiangyang/ncx3");
}
