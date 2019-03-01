// mace.c

#include <ansi.h>
#include <weapon.h>

#define ADMIN   "???"
#define PARTY   "金錢幫"

inherit STAFF;

void create()
{
        set_name(HIG + PARTY + "權杖" NOR, ({ "mace" }) );
        set_weight(30);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "一根晶瑩剔透的權杖，好像是丐幫的玉竹杖哦！\n"
                                "你仔細一看，不是，原來是冒牌貨，是" + PARTY + "的權杖。\n"
                                "幫主通過它發號司令，邀請(author)他人入幫或是開除(expell)不聽話的人。\n" NOR);
                set("value", 1);
                set("no_sell", "這是什麼垃圾？\n");
                set("unit", "根");
                set("wield_msg", HIG "$N" HIG "亮出一個晶瑩剔透的小棍棍，神氣"
                                 "活現的喝道：“還不拜見...本...幫主？”\n" NOR);
                set("unwield_msg", HIG "$N" HIG "鬼鬼祟祟的把權杖收好。\n" NOR);
        }

        set("admin", ADMIN);
        init_staff(1);
        setup();
}

void init()
{
        if (this_player() == environment())
        {
                add_action("do_author", "author");
                add_action("do_expell", "expell");
        }

        add_action("do_owner", "owner");
}

int do_owner(string arg)
{
        object me;
        object ob;

        me = this_player();
        if (wiz_level(me) < wiz_level("(wizard)"))
                return notify_fail("必須是 (wizard) 以上的巫師才能授權。\n");

        if (! arg || ! objectp(ob = present(arg, environment(me))))
                return notify_fail("你要把這" + name() + "贈給誰？\n");

        if (ob == me)
                return notify_fail("你腦潮啊？\n");

        if (! playerp(ob))
                return notify_fail("你只能把權杖贈給玩家。\n");

        if (ob->query("party/party_name") &&
            ob->query("party/party_name") != PARTY)
                return notify_fail(ob->name(1) + "已經入了其它幫派，不合適接受這" + name() + "。\n");

        message_vision("$N指了指" + name() + "，道：這" + name() +
                       "我就贈給幫主" + ob->name(1) + "了。\n", me);
        ob->set("party/party_name", PARTY);
        set("admin", ob->query("id"));
        message_vision("$N將" + name() + "交給了$n。\n", me, ob);
        move(ob, 1);
        return 1;
}

int do_author(string arg)
{
        object me;
        object ob;

        me = this_player();
        if (me->query("id") != query("admin") && me->query("couple/id") != query("admin"))
                return notify_fail("你不是" + PARTY + "幫主或幫主夫人，沒人聽你的。\n");

        if (me->query("party/party_name") != PARTY)
                return notify_fail("你自己都不是" + PARTY + "的人，怎麼收別人？\n");

        if (! arg || ! objectp(ob = present(arg, environment(me))))
                return notify_fail("你要邀請誰加入" + PARTY + "？\n");

        if (! playerp(ob))
                return notify_fail("你只能邀請玩家加入發呆幫。\n");

        if (ob == me)
                return notify_fail("你腦潮啊？\n");

        if (ob->query("combat_exp") >= 50000)
                return notify_fail("此人經驗太高，不宜進入" + PARTY + "。\n");

        if (ob->query("party/party_name"))
        {
                if (ob->query("party/party_name") == PARTY)
                        return notify_fail("人家已經是" + PARTY + "的人了。\n");

                return notify_fail("人家已經入了其他幫會了，不能加入你的" + PARTY + "了。\n");
        }

        if (me->query_temp("author") == ob)
                return notify_fail("你已經邀請人家了，可是別人還沒有答應。\n");

        if (! living(ob))
                return notify_fail("看樣子人家沒法聽見你說什麼了。\n");

        message_vision("$N高舉權杖，問道：“" + ob->name(1) + "，你可願意入我" +
                       PARTY + "？”\n", me);
        ob->set_temp("pending/answer/" + me->query("id") + "/right",
                     (: call_other, __FILE__, "do_right", ob, me :));
        ob->set_temp("pending/answer/" + me->query("id") + "/refuse",
                     (: call_other, __FILE__, "do_refuse", ob, me :));
        me->set_temp("pending/author", ob);
        tell_object(ob, YEL + me->name(1) + "想收你入" + PARTY + "，你同意不同意(right/refuse)？\n" NOR);
        return 1;
}

int do_expell(string arg)
{
        object me;
        object ob;

        me = this_player();
        if (me->query("id") != query("admin") && me->query("couple/id") != query("admin"))
                return notify_fail("你不是" + PARTY + "幫主或幫主夫人，沒人聽你的。\n");

        if (! arg || ! objectp(ob = present(arg, environment(me))))
                return notify_fail("你要邀請誰加入" + PARTY + "？\n");

        if (! playerp(ob))
                return notify_fail("你只能邀請玩家加入發呆幫。\n");

        if (ob == me)
                return notify_fail("你腦潮啊？\n");

        if (ob->query("party/party_name") != PARTY)
                return notify_fail("人家不是你" + PARTY + "的人，懶得理你。\n");

        message_vision("$N哼了一聲，喝道：“" + ob->name(1) +
                       "！你屢犯幫規，今日革你出幫，滾吧！”\n", me);
        ob->delete("party");

        CHANNEL_D->do_channel(this_object(), "rumor",
                              "聽說" + ob->name(1) + "被" + me->name(1) +
                              "開除出" + PARTY + "了。");
        return 1;
}

int do_right(object me, object ob)
{
        if (! ob || environment(ob) != environment(me))
                return notify_fail("可惜啊，人家已經不在這兒了。\n");

        if (! living(ob))
                return notify_fail("人家現在聽不到你說的話，還是算了吧。\n");

        if (ob->query_temp("pending/author") != me)
                return notify_fail("人家現在已經不打算收你了。\n");

        ob->delete_temp("pending/author");

        message_vision("$N拼命點頭，像小雞啄米一樣，忙道：“好！好！好！”\n", me);

        me->set("party/party_name", PARTY);
        CHANNEL_D->do_channel(this_object(), "rumor",
                              "聽說" + ob->name(1) + "收" + me->name(1) +
                              "入了" + PARTY + "。");
        return 1;
}

int do_refuse(object me, object ob)
{
        if (! ob || environment(ob) != environment(me))
                return notify_fail("可惜啊，人家已經不在這兒了。\n");

        if (! living(ob))
                return notify_fail("人家現在聽不到你說的話，還是算了吧。\n");

        if (ob->query_temp("pending/author") != me)
                return notify_fail("人家現在已經不打算收你了。\n");

        ob->delete_temp("pending/author");
        message_vision("$N一腳把$n踢開，喝道：“滾！一邊玩去！”\n",
                       me, ob);
        tell_object(ob, "看來人家對你的" + PARTY + "沒什麼興趣。\n");

        return 1;
}

int query_autoload() { return query("admin"); }

void autoload(string para) { set("admin", para); }
