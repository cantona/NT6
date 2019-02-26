// letter.c
// 師傅手諭

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name("師門信件", ({ "letter", "quest letter" }));
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "張");
                set("long", "這是一封師傅送來的親筆信。\n");
                set("value", 0);
        }
        setup();
}

void init()
{
        // 接受
        add_action("do_accept", "accept");

        // 拒絕
        add_action("do_refuse", "refuse");
}

// 查看時顯示任務提示
string long()
{
        string msg;
        mapping quest;
        object me;

        msg = query("long");
        if (! mapp(quest = query("quest")))
                return msg;

        me = this_player();
        if( query("id", me) != query("quester") )
                return msg;

        // call_out 不一定很準時，所以這裏要防止出現
        // “負一秒”這樣的情況
        if (time() > query("dest_time"))
                return msg;

        msg += "上面寫着：\n";

        // 為其他類型的任務提供擴展餘地
        switch (quest["type"])
        {
        case "kill" :
                // 尋找 master 太過麻煩，所以這裏就根據本人的善惡
                // 判斷消息
                msg += "\n“字諭弟子" + me->name() + "：";
                if (me->is_good())
                {
                        msg += ("得聞惡賊" HIR + quest["name"] + "(" + quest["id"] + ")" + NOR
                                "打家劫舍，無惡不作。近日他在" HIR +
                                quest["place"] + NOR "出沒，正是大好"
                                "機會將他除去，你若願意，便代我出手"
                                "無妨，但務必須在" HIR +
                                CHINESE_D->chinese_monthday(quest["limit"]) +
                                NOR "之前完成。否則回山覆命即可。" +
                                quest["master_name"] + "於" +
                                CHINESE_D->chinese_monthday(quest["time"]) +
                                "。”\n");
                } else
                if (me->is_bad())
                {
                        msg += ("得聞所謂大俠" HIR + quest["name"] + "(" + quest["id"] + ")" + NOR
                                "屢次和我派作對，近日他在" HIR +
                                quest["place"] + NOR "出沒，正是大好"
                                "機會將他除去，你若願意，便代我出手"
                                "無妨，但務必須在" HIR +
                                CHINESE_D->chinese_monthday(quest["limit"]) +
                                NOR "之前完成。否則回山覆命即可。" +
                                quest["master_name"] + "於" +
                                CHINESE_D->chinese_monthday(quest["time"]) +
                                "。”\n");
                } else {
                        msg += ("武林人士" HIR + quest["name"] + "(" + quest["id"] + ")" + NOR
                                "所為甚是討厭，得聞近日他在" HIR +
                                quest["place"] + NOR "出沒，正是大好"
                                "機會將他除去，你若願意，便代我出手"
                                "無妨，但務必須在" HIR +
                                CHINESE_D->chinese_monthday(quest["limit"]) +
                                NOR "之前完成。否則回山覆命即可。" +
                                quest["master_name"] + "於" +
                                CHINESE_D->chinese_monthday(quest["time"]) +
                                "。”\n");
                }
                break;
        }
        // 想立即拒絕的話就輸入 refuse，否則等 30 秒也沒關係
        msg += HIC "\n如果你願意接受此任務，請在" HIW +
               chinese_number(query("dest_time") - time()) +
               HIC "秒之內輸入" HIW "(accept quest)"
               HIC "以確認，否則即為拒絕"
               HIW "(refuse quest)" HIC "。\n" NOR;
        msg = sort_msg(msg);
        return msg;
}

private void eval_function(function fun) { evaluate(fun); }

// 自動取消
void start_auto_cancel(object who, int timeout)
{
        call_out("refuse_quest", timeout, who);
}

// 接受任務
// 發放上一個任務的獎勵，生成這一個任務的 npc
int do_accept(string arg)
{
        object head;
        object me;

        if (arg != "quest")
                return notify_fail("你要接受什麼？\n");

        if (query_temp("obsolete"))
                return 0;

        me = this_player();
        if( query("id", me) != query("quester") )
                return notify_fail("這信可不是寄給你的。\n");

        if( query("quest/id", me) != query("killed_id") )
                write("你看了看信，上面的東西看來是過時了。\n");
        else
        {
            if (QUEST_D->remote_bonus(me))
            {
                    QUEST_D->start_quest(me, query("quest"));
                    message_sort(query("msg/accept"), me);

                    // Drop head
                    if (objectp(head = present("head", me)) &&
                        query("owner_id", head) == query("killed_id") )
                    {
                        message_vision("$N看看手中的" + head->name() +
                                       "，心道此物已然無用，順手就往地上一扔。\n",
                                      me);
                        destruct(head);
                    } else
                    if (objectp(head = present("head", environment(me))) &&
                        query("owner_id", head) == query("killed_id") )
                    {
                        message_vision("$N看看地上的" + head->name() +
                                       "，心道此物已然無用，順手就往邊上一踢。\n",
                                      me);
                        destruct(head);
                    }
            } else
                    write("你看了看信，似乎沒啥重要的。\n");
        }

        set_temp("obsolete", 1);
        //call_out("dest_ob", 0, this_object());
        destruct(this_object());
        return 1;
}

// 析構函數
void dest_ob(object ob)
{
        destruct(ob);
}

// 拒絕
int do_refuse(string arg)
{
        object me;

        if (arg != "quest")
                return notify_fail("你要拒絕什麼？\n");

        if (query_temp("obsolete"))
                return 0;

        me = this_player();
        if( query("id", me) != query("quester") )
                return notify_fail("這信可不是寄給你的。\n");

        message_sort(query("msg/refuse"), me);

        set_temp("obsolete", 1);
        call_out("dest_ob", 0, this_object());
        return 1;
}

// CLASS_D("generate") + "/killed" 延時調用的析構函數
void refuse_quest(object me)
{
        message_sort(query("msg/refuse"), me);

        remove_call_out("eval_function");
        call_out("dest_ob", 0, this_object());
}