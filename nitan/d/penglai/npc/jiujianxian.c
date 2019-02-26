// 
// Create By Rcwiz 09/2003

#include <ansi.h>

inherit NPC;

string ask_jiu();

void create()
{
        set_name(HIW "酒劍仙" NOR, ({ "jiujian xian", "jiujian", "xian" }));

        set("long", HIW "這人好生面熟，難道蜀山派的酒劍仙，他怎會在這裏？。\n" NOR);

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
        set_skill("sword", 2500);
        set_skill("yinyang-shiertian", 550);
        set_skill("force", 550);
        set_skill("martial-cognize", 550);
        set_skill("literate", 550);
        set_skill("medical", 2500);

        map_skill("force", "yinyang-shiertian");
        map_skill("dodge", "yinyang-shiertian");
        map_skill("parry", "yinyang-shiertian");
        map_skill("unarmed", "yinyang-shiertian");
        
        set("inquiry", ([
                "蓬萊仙島"               :   "這不是你該來的地方，我看你還是快走吧。\n",
                "蜀山派"                 :   "你也聽説過嗎，看不出來啊，呵呵。\n",
                "青梅酒"                 :   (: ask_jiu :),
        ]));
        
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
        }) );
        setup();

        carry_object("/kungfu/class/sky/npc/obj/xianpao")->wear();
}

string ask_jiu()
{
        object me = this_player();
        object ob_xy, ob_xnj, ob_hbk, ob_qmj;
        int i;

        // 需要材料
        /*
         青梅     2
         蓬萊蟠桃 1
         菊花     1
       */
        command("nod");
        command("say 既然是為了青梅酒而來，我酒劍仙當然義不容辭。");
        command("say 不過釀製青梅酒需要一些特殊的材料：");
        message_vision(HIM  + "\n"
                       "青梅     2 顆 \n"
                       "蓬萊蟠桃 1 個\n"
                       "菊花     1 朵\n\n" NOR, this_object());
        command("say 如果你這些材料都備齊了的話就來找我吧！");
        command("say 忘記提醒你了，如果你是第一次找本劍仙釀製青梅酒，嘿嘿 ……");
        
        if (! me->query_temp("want_make_qingmeijiu"))
        {
                me->set_temp("want_make_qingmeijiu", 1);
                return "怎麼樣？如果你考慮好了，再來找我！\n";
        }
                
                        
        // 需要青梅
        if (! objectp(ob_xy = present("penglai qingmei", me)))
                return "你好像還沒備齊青梅吧？\n";                        
        if (base_name(ob_xy) != "/d/penglai/obj/qingmei")
                return "你好像還沒備齊青梅吧？\n";
        
        if ("/adm/daemons/stored"->get_ob_amount(me, ob_xy) >= 2)
        {
                for (i = 1; i <= 2; i++)
                {
                        //destruct(ob_xy);
                        ob_xy = present("penglai qingmei", me);
                }
        }
        else
        {
                return "怎麼樣，2顆青梅備齊了嗎？\n";
        }
        
        
        // 需要蓬萊蟠桃
        if (! objectp(ob_xnj = present("penglai pantao", me)))
                return "你好像還沒備齊蓬萊蟠桃吧？\n";                        
        if (base_name(ob_xnj) != "/d/penglai/obj/pantao")
                return "你好像還沒備齊蓬萊蟠桃吧？\n";

        if ("/adm/daemons/stored"->get_ob_amount(me, ob_xnj) >= 1)
        {
                for (i = 1; i <= 1; i++)
                {
                        //destruct(ob_xy);
                        ob_xnj = present("penglai pantao", me);
                }
        }
        else
        {
                return "怎麼樣，1個蓬萊蟠桃備齊了嗎？\n";
        }        

        // 需要菊花
        if (! objectp(ob_hbk = present("penglai juhua", me)))
                return "你好像還沒備齊菊花吧？\n";                        
        if (base_name(ob_hbk) != "/d/penglai/obj/juhua")
                return "你好像還沒備齊菊花吧？\n";

        if ("/adm/daemons/stored"->get_ob_amount(me, ob_hbk) >= 1)
        {
                for (i = 1; i <= 1; i++)
                {
                        //destruct(ob_xy);
                        ob_hbk = present("penglai juhua", me);
                }
        }
        else
        {
                return "怎麼樣，1朵菊花備齊了嗎？\n";
        }

        // 消耗材料      
        ob_xy =  present("penglai qingmei", me);
        destruct(ob_xy);
        ob_xy =  present("penglai qingmei", me);
        destruct(ob_xy);
        ob_xnj = present("penglai pantao", me);
        destruct(ob_xnj);
        ob_hbk = present("penglai juhua", me);        
        destruct(ob_hbk);
        
       
        
        command("say 既然你材料都備齊了，這青梅酒就由本劍仙釀製吧。");
        
        message_sort(HIR "\n$N" HIR "從腰間取出一個葫蘆，將各種材料放進葫蘆中，然後閉上眼睛，口中"
                     "默唸着什麼，似乎正在施展法術 …… 頃刻，一股酒香從葫蘆中飄出。看來這青梅酒已成。\n\n" NOR, this_object(), me);

        command("say 好了好了，很久沒有聞到這青梅酒的香味了。");
        
        if (! me->query("penglai/qingmeijiu_quest/ok"))
        {
                command("say 本劍仙忘記告訴你了，凡是第一次找我釀製青梅酒後，這酒都由本劍仙代為品嚐了 ……");
                message_vision(HIC "説罷，$N" HIC "脖子一仰，將葫蘆裏的青梅酒喝了個精光。\n" NOR, this_object());
                command("haha");
                command("say 好酒，好酒啊。");
                me->set("penglai/qingmeijiu_quest/ok", 1);
                me->delete_temp("want_make_qingmeijiu");
                me->save();
                return "不過你不用擔心，下次釀製好後我便將酒送你了，哈哈 ~~~";
        }
        else
        {
                ob_qmj = new("/d/penglai/obj/qingmeijiu");
                ob_qmj->move(me, 1);
                message_vision("$N" NOR "拿出一瓶青梅酒給$n。\n" NOR, this_object(), me);
                log_file("penglai_quest", me->query("id") + " 製作青梅酒成功！\n");
        }
        
        tell_object(me, HIG "恭喜你，獲得了青梅酒，趕緊交給守路仙人吧！\n" NOR);        
        
        me->delete_temp("want_make_qingmeijiu");
        
        me->save();
        
        return "小心，別灑了，這酒可是凡間品嚐不到的！\n";
}

void unconcious()
{
        die();
}
