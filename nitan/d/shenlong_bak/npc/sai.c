// 賽神龍

#include <ansi.h>

inherit NPC;

string ask_renjiandao();
string ask_shedong();
string ask_zhen();
string give_lhd();

void create()
{
        set_name("賽神龍", ({ "sai shenlong", "sai", "shenlong" }) );
        set("gender", "男性");
        set("age", 999999);
        set("long", "此人仙風道骨，眉目菱角分明，氣宇軒昂。\n");
        set("attitude", "peaceful");
        set("str", 100);
        set("int", 100);
        set("con", 100);
        set("dex", 100);

        set("max_qi", 10000000);
        set("max_jing", 10000000);
        set("max_jingli", 10000000);        
        set("neili", 600000);
        set("max_neili", 600000);
        set("jiali", 100);

        set("combat_exp", 1000000000);

        set("inquiry", ([
                "蛇精" : "那九頭蛇精就躲在蛇精洞內，只有用童男童女可將其引出。\n",
                "童男童女" : "如要找到蛇精可在蛇精洞用一對童男童女將其引出，但是，此法有違人道，\n" +
                             "當年我也是請張天師施法制作出童男童女符才將其引出的。\n",
                "人間道"   : (: ask_renjiandao :),   
                "蛇精洞"   : (: ask_shedong :),     
                "蛇精鱗片" : "當你打中蛇精時，會有一定機率掉出蛇精鱗片。\n",
                "真·六道輪迴" : (: ask_zhen :),
                 //"輪迴點"   : (: give_lhd :),
        ]));

        set_skill("unarmed", 2000);
        set_skill("sword", 2000);
        set_skill("blade", 2000);
        set_skill("staff", 2000);
        set_skill("hammer", 2000);
        set_skill("club", 2000);
        set_skill("whip", 2000);
        set_skill("dagger", 2000);
        set_skill("throwing", 2000);
        set_skill("parry", 2000);
        set_skill("dodge", 2000);
        set_skill("force", 2000);
        set_skill("lingbo-weibu", 2000);
        set_skill("lunhui-sword", 2000);  
        set_skill("never-defeated", 2000);  
        set_skill("martial-cognize", 2000);

        map_skill("sword", "lunhui-sword");
        map_skill("blade", "never-defeated");
        map_skill("staff", "never-defeated");
        map_skill("hammer", "never-defeated");
        map_skill("club", "never-defeated");
        map_skill("whip", "never-defeated");
        map_skill("dagger", "never-defeated");
        map_skill("parry", "lunhui-sword");
        map_skill("dodge", "lingbo-weibu");
        map_skill("force", "lunhui-sword");

        prepare_skill("unarmed", "never-defeated"); 
        
         set("chat_chance_combat", 120); 
        set("chat_msg_combat", ({ 
              (: perform_action, "sword.xiuluo" :),
              (: perform_action, "sword.lan" :),
              (: perform_action, "sword.zhen" :),              
              (: exert_function, "powerup" :), 
              (: exert_function, "shield" :), 
              (: exert_function, "sword" :),                             
        }));
        
        setup();
        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/clone/weapon/zhujian")->wield();

}

string ask_shedong()
{
        string msg;
        
        command("say 這蛇精洞內滿布毒蛇，地形錯綜複雜，一不小心就會迷路。");
        command("say 如果要進蛇洞還是先熟悉下蛇精洞的地圖吧：");
        
        write(@LONG
                              蛇王洞
                                |
                              毒蛇窟
                                |
                              毒蛇窟
                                |
                              毒蛇窟
                                |
                              毒蛇窟               
                                |
              毒蛇窟—毒蛇窟—神龍洞—out—蛇洞外
                                |
                              毒蛇窟
                                |
                              毒蛇洞
                                |
                              千蛇洞                             
                                |
                              千蛇洞
                                |
                              千蛇洞
                                |
                              千蛇洞—九頭蛇洞—九頭蛇洞
                                                   |
                                                蛇精洞外
                                                   |
                                                 蛇精洞
LONG);                                                 
        return "怎麼樣，記熟了嗎？\n";
        
}

string give_lhd()
{
        object me;
        object ob_hlp;
        int i;
        
        me = this_player();
        
      if( query("reborn/times", me) < 3 ) 
                return "走開，走開，沒看我正忙嗎？\n";
        
        if( query("scborn/get_lhd_sai", me) )
                return "輪迴點你不是已經領取了嗎？\n";
        
        if( query("scborn/total_lunhui_point", me) >= 18 )
                return "你的輪迴點已經達到18點了，無法再領取。\n";
        
        if( query("scborn/total_lunhui_point", me)+3>18 )
                return "你如果領取輪迴點就會超過18點了，無法再領取，如有BUG請速與本站管理員聯繫。\n";
                                
        // 已經完成任務
        if( query("scborn/lunhuidian/finish", me) )
                return "不錯，不錯，能從蛇精身上拿到鱗片的人少之有少，閣下算是其中一個。\n";

        // 分配任務
        if( !query("scborn/lunhuidian/give_quest", me) )
        {
                command("look"+query("id", me));
                command("say 這輪迴點異常珍貴，只贈勇者，如果閣下能證明給我看，輪迴點自當奉上。");
                command("say 前方不遠處有一個蛇精洞，幾百年前我將這妖孽鎮壓在此，使之無法在人間興風作浪。");
                command("ke");
                command("say 如果閣下能從它身上取得50片蛇精鱗片，那就證明閣下必為勇者。");
                command("say 不過，蛇精乃千年妖孽，道行高深，你可要想清楚了！");
                
                tell_object(me, this_object()->name() + HIG "讓你從蛇精身上取得鱗片，證明你是勇者。\n" NOR);
                set("scborn/lunhuidian/give_quest", 1, me);
                me->save();
                return "怎麼樣，有膽量去嗎？";
        }
        
        // 完成任務        
        if (! objectp(ob_hlp = present("shejing linpian", me)))
                return "怎麼樣，50片蛇精鱗片取到了嗎？\n";
                
        if (base_name(ob_hlp) != "/d/shenlong/npc/obj/linpian")
                return "怎麼樣，50片蛇精鱗片取到了嗎？\n";
        
        if ("/adm/daemons/stored"->get_ob_amount(me, ob_hlp) >= 50)
        {
                for (i = 1; i <= 50; i++)
                {
                        destruct(ob_hlp);
                        ob_hlp = present("shejing linpian", me);
                }
        }
        else
        {
                return "怎麼樣，50片蛇精鱗片取到了嗎？\n";
        }
        
        command("hehe");
        command("nod"+query("id", me));
        command("say 不錯，既然是勇者，這輪迴點就奉送給你了。");        
                             
        tell_object(me, HIG "恭喜你獲得了 3 點輪迴點。\n");

        set("scborn/lunhuidian/finish", 1, me);
        addn("scborn/cur_lunhui_point", 3, me);
        addn("scborn/total_lunhui_point", 3, me);
        set("scborn/get_lhd_sai", 1, me);

        me->save();
        
        return "佩服，佩服！";        
}

string ask_renjiandao()
{
        object me;
        object ob_hlp;
        int i;
        
        me = this_player();
        
        if( query("int", me)<32 || 
            query("con", me)<32 || 
            query("str", me)<32 || 
            query("dex", me)<32 )
            return "你的先天屬性還不足以修煉人間道，我看你還是先回去吧。\n";

        if( query("reborn/times", me) < 3 )
                return "此處不是爾等駐留之地，還是速速離去吧。\n";
                
        if( me->query_skill("yinyang-shiertian",1) && query("reborn/times", me) < 4 )
                return "哼，凡夫俗子，竟然如此貪心！\n";

        if (me->query_skill("lunhui-sword",1))
                return "哼，凡夫俗子，竟然如此貪心！\n";
                
        if (me->query_skill("renjian-dao", 1))
                return "怎麼樣，這招你練熟了嗎？\n";
                
        command("nod");
        command("say 千百年來，我在此鎮守蛇精，洞外毒蛇密佈，非等閒之輩能夠進入。");
        command("look "+query("id", me));
        command("say 閣下武藝超羣，既然到此，你我也算一場緣分，這「人間道」就傳你吧！");

        message_sort(HIC "\n$N" HIC "走上前去，在$n" HIC "耳邊悄悄説了幾句，然後又拿出一本書，指指點點，"
                     "$n" HIC "不住地點頭，忽而眉頭深鎖，忽而低頭沉思 ……\n良久，$n" HIC "大笑一聲，似乎"
                     "對剛才的疑慮有所頓悟。\n", this_object(), me);

        command("nod "+query("id", me));

        tell_object(me, HIG "恭喜你領悟了「人間道」劍法，目前等級為10級。\n" NOR);
        me->set_skill("renjian-dao", 10);
        
        return "好自為知吧！";
        
                
}
int accept_kill(object me)
{
        command("heng");
        command("say 很好！");
        return 1;
}

void unconcious()
{
       die();
}

void die()
{
        command("chat 不可能，不可能 ……");
        destruct(this_object());
}

int accept_object(object me, object ob)
{

        if (base_name(ob) != "/clone/lonely/book/dugubook")
        {
                command("say 你給我這種東西幹什麼？");
                return 0;
        }


        destruct(ob);
        return 1;
}

// 真·六道輪迴
string ask_zhen()
{
        object *obs; 
        object ob;
        object me;
        object ob_hlp;
        int i;
        
        me = this_player();
        
        if( query("reborn/times", me) < 3)
                return "走開，走開，沒看我正忙嗎？\n";
        
        if( me->query_skill("yinyang-shiertian",1) && query("reborn/times", me) < 4 )
                return "閣下武功已經獨步天下，何必如此貪心?\n";

        if( query("max_neili", me)<10000 )
                return "你的內力修為不夠，這招我還不能傳你。\n";

        if ((int)me->query_skill("buddhism", 1) < 200)
                return "你對禪宗心法參悟不夠，這招我還不能傳你。\n";

        if ((int)me->query_skill("lunhui-sword", 1) < 900)
                return "你六道輪迴劍火候不夠，這招我還不能傳你。\n";

        // 已經完成任務
        if( query("lunhui-sword_quest/zhen/finish", me) )
                return "不錯，不錯，能從蛇精身上拿到鱗片的人少之有少，閣下算是其中一個。\n";
        
        /*
        // 檢查輪迴點        
        if( query("scborn/cur_lunhui_point", me)<6 && !query("thborn/ok", me) )
                return "可惜啊，你輪迴點不足，無法領悟到此招。\n";
        */
        
        // 分配任務
        if( !query("lunhui-sword_quest/zhen/give_quest", me) )
        {
                command("look "+query("id", me));
                command("say 學此招者，必為勇者，如果閣下能證明給我看，此招便傾囊相受。");
                command("say 前方不遠處有一個蛇精洞，幾百年前我將這妖孽鎮壓在此，使之無法在人間興風作浪。");
                command("ke");
                command("say 如果閣下能從它身上取得10片蛇精鱗片，那就證明閣下必為勇者。");
                command("say 不過，蛇精乃千年妖孽，道行高深，你可要想清楚了！");
                
                tell_object(me, this_object()->name() + HIG "讓你從蛇精身上取得鱗片，證明你是勇者。\n" NOR);
                set("lunhui-sword_quest/zhen/give_quest", 1, me);
                me->save();
                return "怎麼樣，有膽量去嗎？";
        }
        
        // 完成任務        
        if (! objectp(ob_hlp = present("shejing linpian", me)))
                return "怎麼樣，10片蛇精鱗片取到了嗎？\n";
                
        if (base_name(ob_hlp) != "/d/shenlong/npc/obj/linpian")
                return "怎麼樣，10片蛇精鱗片取到了嗎？\n";
        
        obs = all_inventory(me); 
        obs = filter_array(obs, (: base_name($1) == "/d/shenlong/npc/obj/linpian" :)); 
        if( sizeof(obs) < 10 ) 
                return "怎麼樣，10片蛇精鱗片取到了嗎？\n";

        for (i = 0; i < 10; i++) 
        { 
                ob = obs[i]; 
                obs[i] = 0; 
                destruct(ob); 
        }
        
        command("hehe");
        command("nod "+query("id", me));
        command("say 不錯，既然是勇者，這「真·六道輪迴」就傳你了，你可聽好了 ……");
        
        message_sort(HIC "\n$N" HIC "走上前去，在$n" HIC "耳邊悄悄説了幾句，然後又拿出一本書，指指點點，"
                     "$n" HIC "不住地點頭，忽而眉頭深鎖，忽而低頭沉思 ……\n良久，$n" HIC "大笑一聲，似乎"
                     "對剛才的疑慮有所頓悟。\n", this_object(), me);
                             
        tell_object(me, HIG "恭喜你學會了「真·六道輪迴」。\n");
        set("can_perform/lunhui-sword/zhen", 1, me);
        set("lunhui-sword_quest/zhen/finish", 1, me);
        
        /*
        // 扣除輪迴點
        if( !query("thborn/ok", me) )
                addn("scborn/cur_lunhui_point", -6, me);

        // 設置扣除輪迴點的出處
        if( !query("thborn/ok", me) )
                set("scborn/perform_zhen_saishenlong", 1, me);
        */
        me->save();
        
        return "佩服，佩服！";
        
                
}
