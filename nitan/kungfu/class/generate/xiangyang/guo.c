// guojing.c 郭靖

#include <ansi.h>

inherit NPC;
int ask_rong();
string sign_up();
void random_move();

void create()
{
        set_name("郭靖", ({"guo jing", "guo", "jing"}));
        set("nickname", HIY"北俠"NOR);
        set("gender", "男性");
        set("age", 41);
        set("long", 
                "他就是人稱北俠的郭靖，既是蒙古成吉思汗的金刀駙馬，又是\n"
                "江南七怪、全真派馬鈺道長、「北丐」洪七公和「老頑童」周\n"
                "伯通等人的徒弟，身兼數門武功。\n"
                "他身着一件灰色長袍，體態魁梧，敦厚的面目中透出一股威嚴\n"
                "令人不由得產生一股欽佩之情。\n");
         set("attitude", "peaceful");

        set("chat_chance", 80);
        set("chat_msg", ({          
                (: random_move :),
        }));
                
        set("str", 40);
        set("int", 20);
        set("con", 38);
        set("dex", 25);

            set("no_get", 1);
            set("no_nuoyi", 1);
            
        set("inquiry", ([
                "周伯通" : "你見到我周大哥了？他現在可好？\n",
                "老頑童" : "周大哥一貫這樣，沒點正經！\n",
                "洪七公" : "師父除了吃，就是喜歡玩。到處玩，還是為了找吃的。\n",
                "黃藥師" : "那是我泰山大人。他雲遊四海，神龍見首不見尾的。\n",
                "一燈大師" : "在下對大師好生感激。\n",
                "歐陽鋒" : "這個老毒物，害死我六位師父，一待襄陽事了，決不與他干休。\n",
                "黃蓉"   : "蓉兒是我的愛妻，你問她做甚？\n",
                "蓉兒"   : "蓉兒就是蓉兒了。你問這麼多幹嘛？\n",
                "郭芙"   : "這個女兒，又笨又不聽話。\n",
                "郭襄"   : "襄兒生於亂世，這輩子又多艱厄。但願她能快樂一世。\n",
                "郭破虜" : "那是我的小兒子。\n",
                "楊過"   : "過兒確實有出息。\n",
                "馬鈺"   : "馬道長於我有半師之誼。\n",
                "丘處機" : "邱道長義薄雲天，是真豪傑。\n",
                "柯鎮惡" : "那是我大師父。\n",
                "朱聰"   : "那是我二師父。\n",
                "韓寶駒" : "那是我三師父。\n",
                "南希仁" : "那是我四師父。\n",
                "張阿生" : "那是我五師父。\n",
                "全金髮" : "那是我六師父。\n",
                "韓小瑩" : "那是我七師父。\n",
                "丐幫"   : "丐幫英雄幾百年了，守衞襄陽多虧了他們。\n",
                "拜師"   : "現在蒙古人圍攻襄陽，我哪有心情收徒啊！\n",
                "報名"   : (: sign_up :),
                "殺蒙古韃子" : (: sign_up :),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({ 
                        (: perform_action, "strike.fei" :),
                        (: perform_action, "strike.hui" :),
                        (: perform_action, "strike.qu" :),
                        (: perform_action, "strike.zhen" :),
                        (: exert_function, "shield" :),
                        (: exert_function, "powerup" :),
                        (: exert_function, "recover" :),                        
        }));
        
        set("qi", 600000);
        set("max_qi", 600000);
        set("jing", 600000);
        set("max_jing", 600000);
        set("neili", 120000);
        set("max_neili", 120000);
        set("jiali", 200);
        
        set("combat_exp", 40000000);
        set("score", 200000);
         
        set_skill("force", 1200);                // 基本內功
        set_skill("huntian-qigong", 1200);        // 混天氣功
        set_skill("strike", 1200);                // 基本拳腳
        set_skill("xianglong-zhang", 1200);        // 降龍十八掌
        set_skill("dodge", 1200);                // 基本躲閃
        set_skill("jinyan-gong", 1200);                // 金雁功
        set_skill("parry", 1200);                // 基本招架
        set_skill("feixu-jin", 500);
        
        map_skill("force", "huntian-qigong");
        map_skill("strike", "xianglong-zhang");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "dragon-strike");
        
        prepare_skill("strike", "xianglong-zhang");
        
        setup();
        
        carry_object("/clone/misc/cloth")->wear();
        
        if (clonep()) keep_heart_beat();
}

string sign_up()
{
        object me;
        int win_times;
        
        me = this_player();

        if (is_fighting())
                return HIR "對不住了，現在在先正忙於對付蒙古韃子。\n" NOR;
                
        if (! XYWAR_D->sign_up_status())
                return HIR "對不住，現在不能報名！\n" NOR;
        
        if (! me->query_temp("want_sign_up_xiangyang_war"))
        {
                me->set_temp("want_sign_up_xiangyang_war", 1);
                return HIG "你是否決定報名參加襄陽保衞戰，如果確定請再輸入一次。\n" NOR;
        }

        if (XYWAR_D->if_sign_up(me->query("id")))
        {
                return HIC "不錯，閣下保家衞國之心可佳！郭某在此謝過了！\n" NOR;
        }

        command("nod");
        command("say 好好好，我大宋有如此愛國之士，定會將蒙古韃子驅出中原！");
        command("haha");

        XYWAR_D->sign_up(me->query("id"));
        XYWAR_D->xywar_message(me->name() + "(" + me->query("id") + ")" HIG "已報名加入襄陽保衞戰，目前共有 " + 
                                     CHINESE_D->chinese_number(XYWAR_D->n_sign_up()) + " 名江湖義士參加抗擊蒙古軍！\n" NOR);

        tell_object(me, HIG "你已經成功報名參加本次的襄陽保衞戰！\n" NOR);
        tell_object(me, HIR "注意，襄陽保衞戰結束請請勿離線，否則將自動取消報名資格！\n" NOR);

        tell_object(me, HIC "\n死亡保護90%已經設置完成，死亡後有90%機率不造成任何損失。\n" NOR);
        
        XYWAR_D->set_no_die(me);

        // 刪除以前的隨機字串標誌        
        win_times = me->query("xywar/win");
        me->delete("xywar");
        me->set("xywar/win", win_times);
        me->save();

        return "誓死保衞襄陽！\n";

}


void die()
{

        XYWAR_D->guojing_message(HIR "襄陽軍士們，郭某去也，誓死保衞我襄陽！！！" NOR);
        XYWAR_D->xywar_message("郭靖奮力抵抗蒙古韃子，不幸戰死襄陽，終其一生，為抵抗蒙古韃子做出了難以磨滅的貢獻！");
        XYWAR_D->guojing_die();
        destruct(this_object());
}

void uncoucious()
{
        die();
}

void init()
{
        object me = this_player();
        object env;
        env = environment(this_object());
        
        if (base_name(env) == "/d/xiangyang/guangchang")
                call_out("do_hello", 3, me);
        
        //主動殺蒙古兵
        if (me->query("mgbing"))kill_ob(me);

}

void do_hello(object me)
{
        if (! objectp(me))return;
                
        if (environment(me) != environment(this_object()))return; 
        
        if (! XYWAR_D->sign_up_status())return;
        
        tell_object(me, HIG "\n郭靖對你説道：這位" + RANK_D->query_respect(me) + 
        "，想參加襄陽保衞戰，為抗擊蒙古韃自出一份力嗎？\n"
        "如果願意參加襄陽保衞戰請向我打聽 " HIR "報名" HIG " 的相關信息吧！\n" NOR); 
}

void heart_beat()
{
        if (XYWAR_D->dest_status() == 1)
        {
                destruct(this_object());
                return;
        }
        
        return ::heart_beat();
}

void random_move()
{
        string route;
        object env;
        string max_route;
        mapping doors;
                
        if (query_temp("dest_now"))
        {
                                
                destruct(this_object());
                return;
        }

        if (XYWAR_D->dest_status() == 1)
        {
                set_temp("dest_now", 1);
        }

        // 行進路徑方向
        // 需要先設置
        route = query("route");

        env = environment(this_object());

        if (! objectp(env))return;

        // 如果到達中央廣場則重新選擇
        if (base_name(env) == "/d/xiangyang/guangchang" && XYWAR_D->if_guojing_moved())
        {
                max_route = XYWAR_D->max_min_n_soldier("max");
                doors = XYWAR_D->get_doors();
                this_object()->move(doors[max_route]);

                // 設置移動方向
                set("route", XYWAR_D->re_poision(max_route));
                return;
        }

        // 按照路由列表移動
        if (stringp(route) && XYWAR_D->now_status() == 2)command("go " + route);
}

int recognize_apprentice(object ob, string skill)
{
        if (ob->query("xywar/win") < 6)
        {
                tell_object(ob, HIG "郭靖對你説道：閣下俠義之心不足，郭某可不能貿然傳你此招。\n" NOR);
                return -1;
        }

        if (ob->query_skill("jiuyin-shengong", 1) < 1)
        {
                tell_object(ob, HIG "郭靖對你説道：你連九陰神功都不會，怎能領悟飛絮勁的奧妙？\n" NOR);
                return -1;
        }
        
        if (ob->query_skill("feixu-jin", 1) < 400)
        {
                tell_object(ob, HIG "郭靖對你説道：以你目前對飛絮勁的修為，還不足以進一步修煉？\n" NOR);
                return -1;
        }

        return 1;
}
