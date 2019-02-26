// 通天老仙 掌管轉世
// Create By Rcwiz 09/2003

#include <ansi.h>

inherit NPC;

#define SCBORN_D   "/adm/daemons/scbornd"
#define MEMBER_D   "/adm/daemons/memberd"

mixed start_scborn();
mixed start_kaoyan();

void create()
{
        set_name(HIW "通天老仙" NOR, ({ "tongtian laoxian", "tongtian", "laoxian" }));
        set("long", HIW "    此乃鎮守天外天的天界大神—通天老仙，據説他\n"
                        "掌管着天界轉世之路最後一道到大門。\n" NOR);

        set("gender", "男性");
        set("age", 199);
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
                "轉世"   :   (: start_scborn :),
                "考驗"   :   (: start_kaoyan :),
        ]));
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
        }) );
        setup();

        carry_object(__DIR__"obj/xianpao")->wear();
}

// 轉世後考驗過12天可以再獲得2點輪迴點
mixed start_kaoyan()
{
           object me;

           me = this_player();

           if (! me->query("scborn/ok"))
           {
                   write("你還沒轉世呢。\n");
                   return 0;
           }

       if (me->query("sky12/floor") != 13)
       {
              write("你還沒有通過十二重天界的考驗！不知道怎麼跑來的，快滾！\n");
                          me->move("/d/city/wumiao");
              return 0;
       }

           // 檢查是否已經獲得過
           if (me->query("scborn/get_lunhui_point_12t"))
           {
                          write("你已經獲取過輪迴點了。\n");
                          return 0;
           }

           if (me->query("scborn/total_lunhui_point") >= 17)
           {
                          write("數據錯誤。\n");
                          return 0;
           }

           // 獲得輪迴點
           me->add("scborn/total_lunhui_point", 2);
           me->add("scborn/cur_lunhui_point", 2);
           me->set("scborn/get_lunhui_point_12t", 1);

           me->save();

           write("恭喜你經過十二重天考驗，獲得 兩 點輪迴點。\n");
           return 1;
}


mixed start_scborn()
{
        object me = this_player();
        
        // 檢查轉世條件
        if (! SCBORN_D->check_data2(me))return 1;

        if (me->query("sky12/haotianta"))
        {
                tell_object(me, HIG "通天老仙對你説道：昊天塔找到了嗎？\n" NOR);
                return 1;
        }

        message_sort(HIM "\n$N" HIM "對$n" HIM "説道：人之生老病死、轉世輪迴皆有定數，"
                     "乃上天註定，如果非要逆天而行，則需打通重重難關，你現在打通了天界"
                     "十二重天，原本應該可以轉世重生，但由於你違逆天道，人道，如要順利"
                     "轉世重新做人還需將自身吸入昊天塔中，借用此神器吸星換月之力方可。\n" NOR,
                     this_object(), me);
                     
        tell_object(me, HIG "通天老仙悄悄告訴你：如果你找到昊天塔就把它交給我，我會幫助"
                        "你完成轉世！\n" NOR);
        
        me->set("sky12/haotianta", 1);

        return 1;
}

void init()
{
        add_action("do_yhjob", "yhjob");
}

// 選擇職業
int do_yhjob(string arg)
{
        object me;
        string msg;

        me = this_player();

    // 介紹
        if (! arg)
        {
                // 一轉介紹
                msg  = HIR "\n您目前可以選擇以下職業作為您轉世後的職業：\n" NOR;
                msg += HIC "俠客：令江湖中人景仰的職業，擁有正氣類攻擊特技。\n" NOR;
                msg += HIM "魔師: 令世人畏懼的職業，擁有邪異類攻擊特技。\n" NOR;
                msg += HIG "隱士: 被世人所遺忘，隱居世外，擁有多種輔助類特技。\n" NOR;
                msg += HIY "具體職業介紹請參見轉世職業幫助文件 help scborn_yhjob\n" NOR;
                msg += HIY "請輸入指令" HIR " yhjob 職業 " HIY "來選擇您轉世後的職業，選擇前請認真閲讀轉世職業幫助文件。\n\n" NOR;

                write(msg);
                return 1;        
        }

        if (arg != "俠客" && arg != "魔師" && arg != "隱士")
                return notify_fail("請選擇正確的職業：俠客、魔師、隱士。\n");
        
        if (me->query("scborn"))
                return notify_fail("對不起，您不能選擇該種職業。\n");

        if (me->query("yhjob/job") && me->query("yhjob/job") != "武士")
                return notify_fail("對不起，您不能選擇該種職業。\n");

        write(HIG "您選擇了 " + arg + " 的職業。\n");

        me->set("yhjob/job" , arg);
        me->save();

        return 1;
}

int accept_object(object me, object ob)
{        
        string obj;
        string msg;
        string *spes;
        mapping special;
        string job;

                if (me->query("scborn/ok"))
                {
                        write("你已經轉過世了。\n");
                        return 0;
                }
                
        // 檢查轉世條件
        if (! SCBORN_D->check_data2(me))return 0;
        
        obj = filter_color(ob->name());

        if (obj != "昊天塔" || 
            ob->is_item_make() ||
            ! ob->is_magic_item())return 0;

                if (! me->query("yhjob"))
                {
                        write("您還沒有選擇你轉世後的職業呢，請輸入指令 yhjob 開始選擇您的職業！\n");
                        return 0;
                }

                job = me->query("yhjob/job");

                if (job != "俠客" && job != "魔師" && job != "隱士")
                {
                        write("您選擇的職業不正確，請重新選擇。\n");
                        return 0;
                }

        // 開始轉世
        if (! SCBORN_D->start_scborn(me))
        {
                write("轉世時數據出錯！\n");
                return 0;
        }
        destruct(ob);

        message_sort(HIC "\n$N" HIC "念起咒語，祭起手中的昊天塔，剎時間，七道光芒從"
                         "昊天塔中奔騰而出，將$n" HIC "捲了進去 ……\n" NOR,
                         this_object(), me);
                         

        me->move("/kungfu/class/sky/haotian");
        tell_object(me, HIG "你穿梭時空，進入了來世！\n\n" NOR);

        me->move("/d/city/wumiao");
                
        special = me->query("special_skill");
        spes = keys(special);
        
        if (MEMBER_D->is_valib_member(me->query("id")) &&
            sizeof(spes) == 2)
        {
                msg = SCBORN_D->get_special_name(spes[0]) + "、";
                msg += SCBORN_D->get_special_name(spes[1]);
        }
        else 
                msg = SCBORN_D->get_special_name(spes[0]);


                // 設置職業技能
                if (job == "俠客")
                {
                        me->set("special_skill/haoran",1);
                        me->set("special_skill/xiagu",1);
                        me->set("special_skill/shewo",1);
                }
                else if (job == "魔師")
                {
                        me->set("special_skill/moxin",1);
                        me->set("special_skill/youran",1);
                        me->set("special_skill/haoling",1);
                }
                else // 隱士
                {
                        me->set("special_skill/haina",1);
                        me->set("special_skill/xianyun",1);
                        me->set("special_skill/tianxia",1);
                }
        // UPDATE_D->born_player(me);

        call_out("notify_all", 1, me, msg, spes);

        return 1;
}

int notify_all(object me, string msg, mixed spes)
{
                CHANNEL_D->do_channel(this_object(), "rumor", 
                               HIY "聽説" + me->name() + HIY + 
                               "打通十二重天，穿梭時空，進入了來世！\n" NOR);
         
         tell_object(me, HIW "\n你獲得轉世技能：" + msg + "\n" NOR);

                 // 獲得輪迴點
                 tell_object(me, HIG"轉世成功，獲得 五 點輪迴點，以後請使用 power 指令查看。\n");
                 me->add("scborn/total_lunhui_point", 5);
                 me->add("scborn/cur_lunhui_point", 5);

         // 重新設置轉世技能，update_d->born_player()要刪除所有技能
         if (MEMBER_D->is_valib_member(me->query("id")) &&
             sizeof(spes) == 2)
         {
                me->set("special_skill/" + spes[0], 1);
                me->set("special_skill/" + spes[1], 1);
         }
         else
                me->set("special_skill/" + spes[0], 1);
                
         me->save();
         
         // 通知數據備份消息
         call_out("notify_me", 1, me);
         
         return 1;
}

int notify_me(object me)
{
        tell_object(me, HIR "\n你轉世前的數據已備份，七日內如發現數據異常，請及時通知本站admin！\n\n" NOR);
        return 1;
}
void unconcious()
{
        die();
}
