inherit ROOM;

string show_bei();
string show_aoxian();

// 72小時只能挑戰一次
#define TIME_LIMIT 2

#include <ansi.h>

void create()
{
        set("short", HIR "火燄洞" NOR);
        set("long",@LONG
一進入此處幽深之氣息突然被一陣無比熾熱的氣息掩蓋，只見四
周巖壁使勁地泛著紅光，似乎是經歷幾千幾萬年的熾烤。洞內深邃無
比，前方黑乎乎的一片，只有借助著巖石泛出的火光才能看清楚四周
景致。不遠處，有一塊碑石（bei）， 遠看上上面刻著一些文字。據
說，這裡隱藏著一只已經修煉成人形的遠古火燄巨獸。
LONG);


        set("exits", ([
                "out"  : __DIR__"dong3.16",
        ]));

        set("item_desc", ([
                "bei"  : (: show_bei :),
                "aoxian":(: show_aoxian :),
        ]));

        set("no_rideto",1);
        set("no_flyto", 1);
        set("no_clean_up", 1);
        setup();

}

string show_bei()
{
        object ob;

        ob = find_living("huo qilin");
        if (objectp(ob) && environment(ob) == this_object())
        {
                return HIG "這是一塊隱藏著機關的碑石，碑石中央凹陷的部分被斬妖勛章填滿，正閃閃發光！\n" NOR;
        }
        return NOR + WHT "上面刻著一些奇特的符號，從未見過，不過在碑石中央有一塊地方已經凹"
                         "陷(aoxian)下去，似乎是一個機關\n" NOR;
}

string show_aoxian()
{
        object ob;

        ob = find_living("huo qilin");
        if (objectp(ob) && environment(ob) == this_object())
        {
                return HIG "碑石中央凹陷的部分被斬妖勛章填滿，正閃閃發光！\n" NOR;
        }

        if( query("no_putin", this_object()) )
                return HIG "碑石中央凹陷的部分被斬妖勛章填滿，正閃閃發光！\n" NOR;

        return HIY "你仔細觀察這凹陷下去的一塊，似乎可以放(putin)入一塊物品來打開其中的機關。\n" NOR;
}

// 檢查今天是否已經參加過麒麟戰
void init()
{
        object me = this_player();

        add_action("do_putin", "putin");

        // TIME_LIMIT小時只能參加一次，測試期間例外，為2小時
        if (time() - query("boss/qilin", me) <  TIME_LIMIT * 3600 && userp(me) && ! wizardp(me))
        {
                tell_object(me, HIG "\n對不起，你參加火麒麟對抗戰間隔時不足" +
                                sprintf("%d", TIME_LIMIT) + "小時。\n");
                tell_object(me, HIC "你距離上次參加火麒麟對抗戰間隔： " + HIY +
                  sprintf("%d",(time()-query("boss/qilin", me))/3600)+HIC"小時。\n\n"NOR);
                me->move(__DIR__"dong3.16");
                return;
        }

        // 設置參加時間
        tell_object(me, HIG "\n你進入火燄洞準備參加對抗火麒麟戰鬥，請不要離開，否則" +
                        sprintf("%d", TIME_LIMIT) + "小時內無法再次進入。\n" NOR);
        tell_object(me, HIR "你已經設置為免死狀態，在火燄洞死亡後可自動在武廟復活，不損失任何物品和技能。\n\n" NOR);
        set("boss/qilin", time(), me);

        // 不需要設置，房間自動免死

        me->save();

        return;
}

// 放入斬妖勛章
int do_putin(string arg)
{
        object ob, env;
        object ob_qilin;

        object me = this_player();

        if (! arg)return notify_fail("你打算放入什麼物品到石碑中凹陷部分？\n");

        ob_qilin = find_living("huo qilin");
        if (objectp(ob_qilin))
        {
                if (environment(ob_qilin) == this_object() )
                        return notify_fail(HIG "石碑中的斬妖勛章正閃閃發光，透射出神秘而詭異的氣息！\n" NOR);
        }
        // 正在清場則不能扔
        env = environment(me);
        if( query("doing", env) )
        {
                return notify_fail("目前正在清場，請稍後再試！\n");
        }

        if( query("no_putin", env) )
                return notify_fail("你目前暫時無法完成此操作，請稍後再試。\n");

        if (objectp(ob = present(arg, me)))
        {

                // 判斷是否為斬妖勛章
                if (base_name(ob) != "/clone/armor/zhanyao-xunzhang")
                        return notify_fail("你準備拿出" + ob->name() + NOR "放入石碑，卻發現怎麼也放不上去。\n");

                /*
                // 測試期間用麒麟鑰匙打開，揚州客店有銷售，1COIN一把
                if (base_name(ob) != "/d/shenlong/obj/qilin_key")
                        return notify_fail("你準備拿出" + ob->name() + NOR "放入石碑，卻發現怎麼也放不上去。\n");
                */
                message_vision(HIR "\n喀嚓~一聲，$N將" + ob->name() + HIR "放入石碑中的凹陷部分，瞬間" + ob->name() +
                             HIR "與石碑合為一體，並散發出詭異的光芒 ……\n" NOR, me);

                destruct(ob);

                set("no_putin", 1, env);
                remove_call_out("clear_no_putin");
                call_out("clear_no_putin", 10, env);

                // 進行延遲出現
                remove_call_out("qilin_coming");
                call_out("qilin_coming", 5, me);

                return 1;
        }

        return notify_fail("你身上沒有這樣物品。\n");
}

void qilin_coming(object me)
{
        object ob_qilin, ob;

        ob = find_living("huo qilin");

        if (objectp(ob) && environment(ob))
        {
                if (base_name(environment(ob)) == __FILE__)
                        return ;
        }

        // 正在清場則返回
        ob = environment(me);
        if( query("doing", ob))return ;

        message_vision(HIY "\n猛然間，石碑劇烈的顫動，整個山洞也開始晃動，伴隨著一陣巨響，一團火燄從山"
                       "洞深處竄出 ……\n" NOR, me);

        ob_qilin = new(__DIR__"npc/qilin");

        set("life_time", time(), ob_qilin);
        ob_qilin->move(__FILE__);

        delete("no_putin", ob);

        return;
}

void clear_no_putin(object env)
{
        delete("no_putin", env);
        return;
}

void start_move()
{
        object *ob;
        int i;
        object ob_out;

        ob = all_inventory(this_object());

        // 清出清場標志
        delete("doing");

        if (! sizeof(ob))return;

        if (! objectp(ob_out = find_object(__DIR__"dong3.16")))
                ob_out = load_object(__DIR__"dong3.16");

        for (i = 0; i < sizeof(ob); i++)
        {
                if (! ob[i]->is_character())
                {
                        destruct(ob[i]);
                        continue;
                }

                if( query("id", ob[i]) == "huoqilin" )
                        continue;

                ob[i]->move(ob_out);
        }

        return;
}

// 來自BOSS的呼叫，當麒麟死亡後延遲將所有房間內的ID
// 移動到火燄洞外，如delay_time = 0 則不延遲
void move_all_player_out(int delay_time)
{
        if (! delay_time)
        {
                start_move();
        }
        else
        {
                remove_call_out("start_move");
                call_out("start_move", delay_time);
        }

        return;

}
