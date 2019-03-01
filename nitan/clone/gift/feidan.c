// feidan.c 核子飛彈

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "核子飛彈" NOR, ({ "nucleus bomb" }));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "這是高科技產品，是" RED "血滴子" NOR "的2000版本。\n");
                set("value", 50000000);
                set("no_sell", 1);
                set("unit", "枚");
        }
}

void init()
{
        add_action("do_launch", "launch");
        add_action("do_aim", "aim");
}

int do_launch(string arg)
{
        object me;
        object ob;
        string user;

        me = this_player();

        if (me->is_busy())
                return notify_fail("什麼事情都等你忙完了再說。\n");

        if (me->is_fighting())
                return notify_fail("打完架再考慮這些事情吧！\n");

        if (! arg || ! id(arg))
                return notify_fail("你要發射什麼？\n");

        if (! stringp(user = query_temp("aim")))
                return notify_fail("你先瞄準(aim)好再發射！\n");

        if (! objectp(ob = find_player(user)) ||
            ! me->visible(ob))
                return notify_fail("你要炸的玩家現在好像不在線上。\n");

        message_vision(HIM "$N掏出一個" + name() + HIM "，喃喃自"
                       "語道：“5... 4... 3... 2... 1...”說罷一按開關！\n"
                       "就聽“轟”的一聲，" + name() + HIM "騰空而去！\n" NOR, me);

        message_vision(HIC "突然天空傳來一陣嗡嗡的聲音...\n" +
                       "“轟”的一聲，$N" HIC "被炸得渾身都是小煙，"
                       "一句話都說不出來...\n" NOR, ob);

        if (wizardp(ob))
                message_vision(HIM "$N" HIM "連忙點燃一張符紙，口中"
                       "直念叨：“太上老君救命啊...”\n" NOR, ob);
        else
        {
                message_vision(HIG "$N" HIG "一臉無辜的表情，真冤枉啊！\n" NOR, ob);
                ob->ban_say_until(10 * 60, "你現在被炸得頭暈眼花，說不出話");
                CHANNEL_D->do_channel(this_object(), "rumor",
                                      "聽說" + ob->name(1) +
                                      "慘遭核子飛彈襲擊，現在精神失常。");
        }

        destruct(this_object());
        return 1;
}

int do_aim(string arg)
{
        object me;
        object ob;
        string my_id;

        if (arg && sscanf(arg, "%s with %s", arg, my_id) == 2 && ! id(my_id))
                return notify_fail("這裡沒有(" + my_id + ")這樣東西。\n");

        if ((arg == "none" || arg == "cancel") && query_temp("aim"))
        {
                delete_temp("aim");
                write("立即取消飛彈瞄準！\n");
                return 1;
        }

        me = this_player();

        if (! arg || ! objectp(ob = find_player(arg)) ||
            ! me->visible(ob))
                return notify_fail("你要瞄準哪個玩家？\n");

        if (me->is_busy())
                return notify_fail("什麼事情都等你忙完了再說。\n");

        if (me->is_fighting())
                return notify_fail("打完架再考慮這些事情吧！\n");

        if (me->ban_say())
                return notify_fail("你現在說不出話來...導彈也沒法發射。\n");

        tell_object(me, HIY "你掏出一個" + name() + HIY "，東瞄瞄，西瞄瞄。\n" NOR, me);
        message("vision", HIR "【觀察衛星】緊急報告，" + ob->name(1) +
                          HIR "已經被人用" + name() +
                          HIR "瞄準了。\n" NOR, ob);

        set_temp("aim",query("id", ob));
        me->start_busy(2);

        return 1;
}

string long()
{
        object ob;
        string msg;

        msg = query("long");
        if (query_temp("aim") &&
            objectp(ob = find_player(query_temp("aim"))))
        {
                msg += "現在這枚飛彈正瞄準著" + ob->name(1) +
                       "，待命發射(launch)。\n";
        } else
                msg += "現在這枚飛彈正處于準備狀態，"
                       "可以隨時瞄準(aim)。\n";
        return msg;
}