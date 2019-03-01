// feed.c 養豬大法

#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object *obs;
        object ob;
        int lvl;

        if (me->ban_say(0))
                return 0;

        if (! arg)
                return notify_fail("你要送哪個玩家進豬圈？\n");

        lvl = me->query_skill("feed-power", 1);

        if (arg == "all" || arg == "ALL")
        {
                if (lvl < 500)
                        return notify_fail("你的養豬水平尚未到達宗師境界，無法施展無上養豬大法。\n");

                if (me->query_skill("idle-force", 1) < 500)
                        return notify_fail("你的發呆神功尚未到達宗師境界，無法施展無上養豬大法。\n");

                if( query("potential", me)<query("learned_points", me)+50 )
                        return notify_fail("你的潛能不夠，難以施展無上養豬大法。\n");

                if( query("jing", me)<50 )
                        return notify_fail("你的精神太差，不能施展這一曠古神功。\n");

                if (! environment(me)->is_chat_room() ||
                    environment(me) == find_object("/d/city/zhujuan"))
                        return notify_fail("這裡難以讓你施展奇術。\n");

                obs = filter_array(all_inventory(environment(me)),
                                   (: interactive($1) &&
                                      $1 != $(me) &&
                                      wiz_level($1) <= wiz_level($(me)) &&
                                      query_idle($1) >= 120 :));
                if (sizeof(obs) < 1)
                        return notify_fail("這裡並沒有合適的對象讓你施展神功。\n");

                addn("learned_points", 50, me);
                me->receive_damage("jing", 50);

                message_sort(HIM "$N" HIM "口中念念有詞道：“天靈靈，地靈靈，凈壇使者快快顯靈！”"
                               "只聽晴空一聲霹靂，數道閃電直落而下，登時煙霧繚繞....\n" NOR, me);
                tell_object(obs, HIG "你只覺得頭一暈...\n" NOR);
                obs->move("/d/city/zhujuan");
                message_sort("待煙霧緩緩散去，你發現" + implode(obs->name(), "、") + "竟然不見了！\n", me);
                message("vision", "只聽連續幾聲“撲通”，" + chinese_number(sizeof(obs)) +
                                  "個人掉進了豬圈，繼續高聲打著呼嚕。\n",
                                  environment(obs[0]), obs);
                return 1;
        }

        if (! objectp(ob = find_player(arg)) || ! me->visible(ob))
                return notify_fail("你要送哪個玩家進豬圈？\n");

        if (me == ob)
                return notify_fail("你大腦有水？\n");

        if (wiz_level(me) < wiz_level(ob))
                return notify_fail("你的養豬水平還沒有那麼高。\n");

        if (! lvl)
                return notify_fail("你得先學好了養豬大法再說。\n");

        if (lvl < 50)
                return notify_fail("你的養豬水平太差，無法施展絕技。\n");

        if (lvl < 300 && environment(ob) != environment(me))
                return notify_fail("你的養豬水平有限，無法施展奇術于千裡之外！\n");

        if (environment(ob) == find_object("/d/city/zhujuan"))
                return notify_fail("此人正在豬圈中享福呢。\n");

        if (! environment(ob)->is_chat_room() && wiz_level(me) < 1)
                return notify_fail("此人所在的地點難以讓你施展奇術。\n");

        if (! interactive(ob))
                return notify_fail("此人不在線上，不能養之。\n");

        if (query_idle(ob) < 120)
                return notify_fail("這人現在精神著呢，不好養吧。\n");

        if( query("jing", me)<50 )
                return notify_fail("你的精神太差，不能施展這一曠古神功。\n");

        if( query("learned_points", me)+10>query("potential", me) )
                return notify_fail("你的潛能不夠，無法施展這一曠古神功。\n");

        me->receive_damage("jing", 50);
        addn("learned_points", 10, me);

        message_vision(HIM "$N" HIM "口中念念有詞：天蓬元帥急急聽令，現送上肥豬一頭！\n", me);
        if( !wizardp(ob) && (random(lvl*lvl)+lvl*lvl<query("combat_exp", ob) || 
            query("combat_exp", ob) >= 50000) )
        {
                write("沒有任何效果，看來你這次養豬不成！\n");
                return 1;
        }

        switch(random(4))
        {
        case 0:
                message_vision(HIM "天空現出五彩祥雲，天蓬元帥緩緩落下，一把拎起"
                               HIM "$N" HIM "，冷笑兩聲，架雲去了。\n" NOR,
                               ob);
                break;
        case 1:
                message_vision(HIM "天蓬元帥出現在一股煙霧中，一把抓住$N"
                               HIM "，喝道：走，咱們家有事商量，快和我去！\n" NOR,
                               ob);
                break;
        case 2:
                message_vision(HIM "天蓬元帥急急忙忙的跑來，大聲喊道：" +
                               ob->name() + HIM "！嫦娥姐姐來了！$N"
                               HIM "一聽，慌忙跟在老豬屁股後面顛顛的跑了。\n" NOR,
                               ob);
                break;
        default:
                message_vision(HIM "撲通一下，只見天蓬元帥從天上摔了下來。$N" +
                               HIM "忍不住嘻嘻一笑，元帥大怒：“好家伙，躲在這裡？”\n"
                               "一團煙霧過後，只聽慘叫連連，$N" HIM "聲音漸漸遠去。\n" NOR,
                               ob);
                break;
        }

        ob->move("/d/city/zhujuan");
        message("vision", "只聽“撲通”一聲，" + ob->name() +
                          "掉進了豬圈，繼續高聲打著呼嚕。\n",
                environment(ob), ob);
        write(HIC "你的養豬大法成功了，" + ob->name(1) +
              HIC "現在進豬圈享福去了\n" NOR);

        CHANNEL_D->do_channel(this_object(), "rumor", "聽說" +
                              me->name(1) + HIM "施展養豬大法，" +
                              ob->name(1) + HIM "進豬圈繼續發呆，長睡不醒。");
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : feed <玩家> | all

如果玩家正在發呆，你有擅長養豬神功，那麼可以使用這條指令
將該玩家送進豬圈實習。每使用一次養豬大法都會耗費十點潛能
和一些精。 如果使用 all 參數，則可以將在場所有發呆人士送
入豬圈，當然，耗費的潛能會更多。
 
HELP );
        return 1;
}