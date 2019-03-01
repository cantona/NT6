// 通天老仙 掌管轉世
// Create By Rcwiz 09/2003

#include <ansi.h>

inherit NPC;

#define MEMBER_D   "/adm/daemons/memberd"
#define FUBEN_D    "/adm/daemons/fuben_daemonsd"

mixed start_thborn();

void create()
{
        set_name(HIY "炎黃天神" NOR, ({ "yanhuang tianshen", "yanhuang", "tianshen" }));
        set("long", HIY "    炎黃天神威風凜凜，在此恭候您多時了，想要\n"
                        "通過二次轉生，必須接受天神的考驗。\n" NOR);

        set("gender", "男性");
        set("age", 9999);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 100);
        set("int", 100);
        set("con", 100);
        set("dex", 100);

        set("max_qi", 200000);
        set("max_jing", 50000);
        set("max_neili", 30000);
        set("neili", 30000);
        set("jiali", 200);
        set("combat_exp", 90000000);

        set_skill("dodge", 550);
        set_skill("parry",550);
        set_skill("unarmed", 550);
        set_skill("yinyang-shiertian", 550);
        set_skill("force", 550);
        set_skill("martial-cognize", 550);
        set_skill("literate", 550);

        map_skill("force", "yinyang-shiertian");
        map_skill("dodge", "yinyang-shiertian");
        map_skill("parry", "yinyang-shiertian");
        map_skill("unarmed", "yinyang-shiertian");
        
        set("inquiry", ([
                "二轉"   :   (: start_thborn :),
        ]));
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
        }) );
        setup();

        carry_object(__DIR__"obj/xianpao")->wear();
}

mixed start_thborn()
{
        object me = this_player();
        
        string item1, item2;
        object ob1, ob2;
        
        string *keys_item1, *keys_item2;        
        object ob_taixu, ob_boss;
        
        mapping  ob_list1 = ([
                "將軍令"            : "/clone/misc/boss_item/jiangjun-ling",
                "富士山風景畫"      : "/clone/misc/boss_item/fengjing-hua",
                "暗殺名單"          : "/clone/misc/boss_item/ansha-mingdan",
                "交子"              : "/clone/misc/boss_item/jiaozi",
                "《櫻花讚》"        : "/clone/misc/boss_item/yinghua-zan",
                "安守閣地圖"        : "/clone/misc/boss_item/anshouge-tu",
                "天師鬼符"          : "/clone/misc/boss_item/tianshi-guifu",            
        ]);        
                
        mapping  ob_list2 = ([
                "將軍令"            : "/clone/misc/boss_item/jiangjun-ling",
                "富士山風景畫"      : "/clone/misc/boss_item/fengjing-hua",
                "暗殺名單"          : "/clone/misc/boss_item/ansha-mingdan",
                "交子"              : "/clone/misc/boss_item/jiaozi",
                "《櫻花讚》"        : "/clone/misc/boss_item/yinghua-zan",
        ]);                
        
        // 檢查轉世條件
        if (! me->query("scborn/ok"))
                return "你還沒有通過轉世，不能進行二轉！\n";
        
        if (me->query("thborn/ok"))
        {
                if (me->query("thborn/repeat"))// 重新2轉
                {
                        tell_object(me, HIG "\n你可以進入重新二轉！\n" NOR);
                        me->move("/kungfu/class/sky/sky2zhuan");
                        return 1;
                }
                return "你不是已經二轉了嗎，還來幹什麼！\n";
        }

        if (me->query("combat_exp") < 380000000)
                return "你的實戰經驗不足3.8億，不能進行二轉！\n";
                
        if (me->query_skill("force", 1) < 1500)
                return "你基本內功不足1500級別，不能進行二轉！\n";

        if (me->query_skill("dodge", 1) < 1500)
                return "你基本輕功不足1500級別，不能進行二轉！\n";
                
        if (me->query_skill("parry", 1) < 1500)
                return "你基本招架不足1500級別，不能進行二轉！\n";

        if (! MEMBER_D->is_valib_member(me->query("id")))
                return "你不是有效會員，不能進行二轉！\n";
                          
        // 已經接了任務                          
        if (sizeof(me->query("scborn/thborn_item1_id")))
        {
                if (! objectp(ob1 = present(me->query("scborn/thborn_item1_id"), me)) && ! me->query("scborn/item_ok"))
                {
                        return me->query("scborn/thborn_item1_name") + NOR "你找到了嗎！\n";
                }
                if (! objectp(ob2 = present(me->query("scborn/thborn_item2_id"), me)) && ! me->query("scborn/item_ok"))
                {
                        return me->query("scborn/thborn_item2_name") + NOR "你找到了嗎！\n";
                }
                /*
                // 測試期間不開放挑戰BOSS
                if (me->query("id") != "rcwiz" && me->query("id") != "axiao" && me->query("id") != "mrhy")
                {
                        message_sort(HIM "\n$N" HIM "對$n" HIM "說道：不錯！不錯！看來你已經通過了第一"
                                         "輪考驗，現在我將送你進入無盡太虛之中挑戰二轉守護神，打敗守護"
                                         "神便可開啟二轉之門！\n", this_object(), me);
                        tell_object(me, HIG "無盡太虛之門還未開啟，請保留好你的任務物品，開放日程請留意系統通告！\n" NOR);                                 
                        return 1;
                }
                */
                // 兩樣都找到了
                if (! me->query("scborn/item_ok"))
                {
                        destruct(ob1);
                        destruct(ob2);
                }
                
                me->set("scborn/item_ok", 1);
                
                message_sort(HIM "\n$N" HIM "對$n" HIM "說道：不錯！不錯！看來你已經通過了第一"
                                 "輪考驗，現在我將送你進入無盡太虛之中挑戰二轉守護神，打敗守護"
                                 "神便可開啟二轉之門！\n\n", this_object(), me);

                CHANNEL_D->do_channel(this_object(), "rumor", HIY +  me->name() + "(" + me->query("id") + ")" HIM "被炎黃天神"
                                                              "送入無盡太虛，挑戰二轉守護神！" NOR);        
                                                                              
                ob_taixu = new("/kungfu/class/sky/wujin-taixu");
                ob_boss = new("/kungfu/class/sky/npc/shouhushen");
                ob_boss->move(ob_taixu);
                ob_boss->set("myroom", ob_taixu);
                
                FUBEN_D->move_lonely_fb_room(me, ob_taixu, "系統提示：進入無盡太虛，離開請進入 out 出口！", "", "");        
                
                me->save();                                              
                return 1;                                                              
        }
        else
        {
                keys_item1 = keys(ob_list1);
                keys_item2 = keys(ob_list2);
                
                if (me->query_skill("force", 1) < 1800)
                {                        
                        item1 = keys_item2[random(sizeof(ob_list2))];
                        ob1 = new(ob_list2[item1]);                        
                        //ob_list2 -= ([ item1 ]);
                        keys_item2 -= ({ item1 });
                        item2 = keys_item2[random(sizeof(keys_item2))];                        
                        me->set("scborn/thborn_item1_name", item1);

                        me->set("scborn/thborn_item1_id", ob1->query("id"));
                        me->set("scborn/thborn_item2_name", item2);
                        ob2 = new(ob_list2[item2]);
                        me->set("scborn/thborn_item2_id", ob2->query("id"));
                        destruct(ob1);
                        destruct(ob2);        
                }
                else
                {
                        item1 = keys_item1[random(sizeof(ob_list1))];
                        ob1 = new(ob_list1[item1]);                        
                        //ob_list1 -= ([ item1 ]);
                        keys_item1 -= ({ item1 });
                        item2 = keys_item1[random(sizeof(keys_item1))];
                        
                        me->set("scborn/thborn_item1_name", item1);
                        me->set("scborn/thborn_item1_id", ob1->query("id"));
                        me->set("scborn/thborn_item2_name", item2);
                        ob2 = new(ob_list1[item2]);
                        me->set("scborn/thborn_item2_id", ob2->query("id"));
                        destruct(ob1);
                        destruct(ob2);
                }

                message_sort(HIM "\n$N" HIM "對$n" HIM "說道：天道有序，即使閣下通過第一次轉生"
                                 "獲取了超越常人的能力，但是，第二次轉生需要自身達到意識上的超"
                                 "脫激發體內蘊藏的巨大能量，從而真正的擺脫天道的束縛，脫胎換骨。"
                                 "看來你已經獲得了二次轉生的基本條件，現在，你只需要接受最後的"
                                 "考驗，本大神便可協助你完成二次轉生。\n"
                                 HIM "$N" HIM "頓了頓繼續道：如果你能找到" + item1 + HIM "和" +
                                 item2 + HIM "交給本大神，我便可以協助你進入無盡太虛，挑戰二轉"
                                 "守護神！\n", this_object(), me);
                     
                tell_object(me, HIG "提示：如果你找到" + item1 + HIG "和" + item2 + HIG "請再次來與天神對話！\n" NOR);
        }
        
        me->save();

        return 1;
}

void unconcious()
{
        die();
}
