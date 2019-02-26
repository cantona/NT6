// chaoyang.c

inherit ROOM;
#include <ansi.h>

#define SWORD "/clone/lonely/jinshejian"
#define THE_BOOK "/clone/lonely/book/jinshe1"

// Modify by Rcwiz for Heros.cd

object ob;
string msg;
string look_sword();

void create()
{
        set("short", HIY "金蛇洞" NOR);

        set("book_count", 1);
        set("sword_count", 1);
        msg = "只見對面石壁上斜倚着一副骷髏骨，身上衣服已爛了七八成，那骷髏\n"
              "骨宛然尚可見到是個人形。你見到這副情形，一顆心嘣嘣亂跳，見石室中\n"
              "別無其他可怖事物，於走近仔細照看。石壁上有幾百幅用利器刻成的簡陋\n"
              "人形，每個人形均不相同，舉手踢足，似在練武。你挨次看去，密密層層\n"
              "的都是圖形，心下不解，不知刻在這裏有甚麼用意。圖形盡處，石壁上出\n"
              "現了幾行字，也是以利器所刻，湊過去一看，見刻的是十六個字：“重寶\n"
              "祕術，付與有緣，入我門來，遇禍莫怨。”";

        if (! ob = find_object(SWORD))
                 ob = load_object(SWORD);

        if (! environment(ob))
        {
                 destruct(ob);

                 msg += "這十六字之旁，有個劍柄凸出\n在石壁之上，似是一把劍（sword）插入了石"
                        "壁，直至劍柄。\n";
        }
        else if (query("sword_count") > 0)
        {
                msg += "這十六字之旁，有個劍柄凸出\n在石壁之上，似是一把劍（sword）插入了石"
                       "壁，直至劍柄。\n";
        }

        else msg += "\n";

        set("long", @LONG
只見對面石壁上斜倚着一副骷髏骨，身上衣服已爛了七八成，那
骷髏骨宛然尚可見到是個人形。你見到這副情形，一顆心嘣嘣亂跳，
見石室中別無其他可怖事物，於走近仔細照看。石壁上有幾百幅用利
器刻成的簡陋人形，每個人形均不相同，舉手踢足，似在練武。你挨
次看去，密密層層的都是圖形，心下不解，不知刻在這裏有甚麼用意。
圖形盡處，石壁上出現了幾行字，也是以利器所刻，湊過去一看，見
刻的是十六個字：『重寶祕術，付與有緣，入我門來，遇禍莫怨。』
這十六字之旁，有個劍柄凸出在石壁之上，似是一把劍（sword）插入
了石壁，直至劍柄。
LONG );

        set("item_desc", ([
              "ya"    : NOR + WHT "懸崖下峭壁高聳，一條青藤（teng）直垂而下。\n" NOR,
              "teng"  : HIG "一根青藤，在半空中搖晃着，可以用他爬（climb）上懸崖。\n" NOR,
              "sword" : (: look_sword :),
        ]));        

        set("objects", ([
            __DIR__"obj/jinshe-zhui" : 1,
        ]));

        setup();
}

void init()
{
        add_action("do_climb", "climb");
        add_action("do_ba", "ba");
        add_action("do_wa", "wa");
}

int do_wa()
{
        object me = this_player();
        object ob;

        if (! ob = find_object(THE_BOOK))
                ob = load_object(THE_BOOK);

        if (me->is_busy() || me->is_fighting())
                return notify_fail("等你忙完了再説吧！\n");

        message_vision(HIC "$N" HIC "使勁地在地上挖，不一會兒挖出一個洞來。\n", me);

        if (environment(ob))
        {                
                if (query("book_count") > 0)
                ob = new(THE_BOOK);
                else
                return 1;
        }

        tell_object(me, HIG "你猛然發現下面有幾本書，你將它拿了起來。\n");

        ob->move(me, 1);
        ob = new("/clone/book/jinshe2");
        ob->move(me, 1);
        ob = new("/clone/book/jinshe3");
        ob->move(me, 1);
        addn("book_count", -1);
        me->start_busy(2);

        return 1;
}

string look_sword()
{
        /*
        object ob;
  
        if (! ob = find_object(SWORD))
                ob = load_object(SWORD);

        if (! environment(ob))
        {
              destruct(ob);
              return HIG "一柄形狀奇特的劍。\n" NOR;
        }
        else if (query("sword_count") > 0)
        */
        if (query("sword_count") > 0)
                return HIG "一柄形狀奇特的劍。\n" NOR;

        return "你要看什麼？\n";
}

int do_ba(string arg)
{
        object me = this_player();
        object ob;
        string show;

        show = "只見對面石壁上斜倚着一副骷髏骨，身上衣服已爛了七八成，那骷髏\n"
              "骨宛然尚可見到是個人形。他見到這副情形，一顆心嘣嘣亂跳，見石室中\n"
              "別無其他可怖事物，於走近仔細照看。石壁上有幾百幅用利器刻成的簡陋\n"
              "人形，每個人形均不相同，舉手踢足，似在練武。他挨次看去，密密層層\n"
              "的都是圖形，心下不解，不知刻在這裏有甚麼用意。圖形盡處，石壁上出\n"
              "現了幾行字，也是以利器所刻，湊過去一看，見刻的是十六個字：“重寶\n"
              "祕術，付與有緣，入我門來，遇禍莫怨。”\n";

        if (! arg || arg != "sword")
               return notify_fail("你要拔什麼？\n");

        if (me->is_busy() || me->is_fighting())
               return notify_fail("等你忙完了再説吧！\n");

        if (me->query_str() < 40)
               return notify_fail("你臂力不足，無法將劍拔起。\n");    

        /*
        if (! ob = find_object(SWORD))
                ob = load_object(SWORD);
        */

        me->start_busy(2);

        /*
        if (environment(ob))
        {
        */
                if (query("sword_count") < 1)
                return notify_fail("你要拔什麼？\n");
                ob = new(SWORD);
                addn("sword_count", -1);
        /*
        }
        */

        message_vision(HIG "$N" HIG "用力將劍從地上拔出。\n", me);
        ob->move(me);

        set("long", show);
        return 1;          
}

int do_climb(string arg)
{
        object me = this_player();

        if (me->is_busy() || me->is_fighting())
               return notify_fail("等你忙完了再説吧！\n");

        message_vision(HIG "$N" HIG "拉着青藤爬上懸崖……\n", me);
                
        me->move("/d/huashan/chaoyang");

        me->start_busy(2);

        return 1;          
}

void reset()
{
        set("book_count", 1);
        set("sword_count", 1);
        ::reset();
}
