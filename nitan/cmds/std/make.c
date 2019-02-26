// make.c

#include <ansi.h>
#include <medical.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object qm;
        object hob;
        string med;
        mapping make;
        mapping req;
        mapping herb;
        string *ks;
        object *hlist;
        string msg;
        int only_list;
        int i;

        if (! arg)
        {
                make=query("can_make", me);
                if (! mapp(make))
                        return notify_fail("你現在不會制任何藥物。\n");

                ks = keys(make);
                msg = "你現在已經會制";
                if (sizeof(ks) >= 2)
                        msg += implode(ks[0..sizeof(ks) - 2], "、") +
                                "和" + ks[sizeof(ks) - 1] + "了。\n";
                else
                        msg += ks[0] + "了。\n";
                msg = sort_string(msg, 64);
                write(msg);
                return 1;
        }

        // only for list?
        only_list = sscanf(arg, "%s ?", arg);

        if( !stringp(med=query("can_make/"+arg, me)) )
                return notify_fail("你還不會配這種藥啊！\n");

        // The player can only make the medicine under the /clone/medicine,
        // nothing, but for save memory.
        med = MEDICINE(med);
        if (file_size(med + ".c") < 0)
                return notify_fail("這種藥方好像已經失傳了？你還是問問巫師吧。\n");

        if (! mapp(req = query("mixture", get_object(med))))
                return notify_fail(med->name() + "好像無法配製...\n");

        if (! mapp(herb = req["herb"]))
                return notify_fail(med->name() + "需要什麼原料呢...\n");

        if (only_list)
        {
                // show herb
                write("煉製" + arg + "需要以下這些藥材：\n");
                ks = keys(herb);
                for (i = 0; i < sizeof(ks); i++)
                {
                        write(chinese_number(herb[ks[i]]) + query("base_unit", get_object(HERB(ks[i]))) +
                              HERB(ks[i])->name() + "\n");
                }
                return 1;
        }

        if (me->is_fighting())
                return notify_fail("打架的時候你還有閒工夫配藥？\n");

        if (me->is_busy())
                return notify_fail("還是先把手頭的事情忙完吧。\n");

        if( query("no_fight", environment(me)) && 0 )
                return notify_fail("你在這裏製藥只怕要打擾到別人。\n");

        qm=query_temp("handing", me);
        if (! qm)
                return notify_fail("你的先把能夠磨藥的研缽拿(hand)在手上才行。\n");

        if (! qm->can_make_medicine())
                return notify_fail(qm->name() + "好像無法發揮研缽的作用吧。\n");

        if (sizeof(all_inventory(qm)) > 0)
                return notify_fail("你還是先把" + qm->name() + "裏面的東西拿出來再説。\n");

        if( query("jing", me)<query("max_jing", me)*7/10 )
                return notify_fail("你現在精神難以集中，無法配藥。\n");

        ks = keys(req) - ({ "herb", "neili", "jing", "jingli", "min_level", "time" });

        // check skills
        for (i = 0; i < sizeof(ks); i++)
                if (me->query_skillo(ks[i], 1) < req[ks[i]])
                        return notify_fail("你的" + to_chinese(ks[i]) +
                                           "水平不夠，還無法調劑" +
                                           med->name() + "。\n");

        // check herb
        ks = keys(herb);
        hlist = allocate(sizeof(ks));
        for (i = 0; i < sizeof(ks); i++)
        {
                hob = present("herb_" + ks[i], me);
                if (! hob || hob->query_amount() < herb[ks[i]])
                {
                        if (file_size(HERB(ks[i]) + ".c") < 0)
                        {
                                write("沒有(" + ks[i] + ")這種藥材啊！"
                                      "怎麼回事？\n");
                                return 1;
                        }
                        return notify_fail("你點了點藥材，發現" +
                                           HERB(ks[i])->name() +
                                           "的分量還不夠。\n");
                }
                hlist[i] = hob;
        }

        // decrease herb
        msg = "你選出";
        for (i = 0; i < sizeof(ks); i++)
        {
                if (i) msg += "、";
                msg += chinese_number(herb[ks[i]]) +
                       query("base_unit", hlist[i])+
                       hlist[i]->name();
                hlist[i]->add_amount(-herb[ks[i]]);
        }
        msg += "，然後小心翼翼的把它們放到" + qm->name() + "裏面，開始製藥。\n";
        msg = sort_string(msg, 64);
        write(msg);
        message("vision", me->name() + "東摸摸，西弄弄，不知道在幹啥。\n",
                environment(me), ({ me }));
        me->start_busy(bind((:call_other, __FILE__, "making" :), me),
                       bind((:call_other, __FILE__, "halt_make" :), me));
        me->set_short_desc("正在專心致志的煉製藥物。");
        set_temp("pending/making", 0, me);
        set_temp("making/medicine", med, me);
        set_temp("making/time", req["time"], me);
        set_temp("making/require", req, me);
        set_temp("making/container", qm, me);
        return 1;
}

int stop_making(object me)
{
        delete_temp("making", me);
        delete_temp("pending/making", me);
        me->set_short_desc(0);
        return 0;
}

int making(object me)
{
        int step;
        mapping req;
        string msg_me, msg_out;
        string med;
        object ob;
        object qm;

        step=query_temp("pending/making", me);
        req=query_temp("making/require", me);
        med=query_temp("making/medicine", me);
        qm=query_temp("making/container", me);
        if( qm != query_temp("handing", me) )
        {
                write("嗯？研缽呢...？我的研缽！\n");
                return stop_making(me);
        }

        switch (step)
        {
        default:
                step = 0;
                msg_me = "你拿起棒杵，慢慢的搗着" + qm->name() + "裏面的藥材。\n";
                msg_out = "$N拿起棒杵叮咣叮咣的搗得很起勁。\n";
                break;
        case 1:
                msg_me = "撲哧撲哧，藥材眼見變成了一塊塊小碎塊。\n";
                msg_out = "$N沒完沒了的搗鼓。\n";
                break;
        case 2:
                msg_me = "你輕輕的研磨着藥材，讓它越來越細。\n";
                msg_out = "$N緊張的磨着東西。\n";
                break;
        case 3:
                msg_me = "你接着把那些殘留的大塊兒一點的藥材搗碎。\n";
                msg_out = "$N突然又叮咣叮咣的搗個不停。\n";
                break;
        case 4:
                msg_me = "你細細的將所有的藥材磨成了粉末。\n";
                msg_out = "$N拿着棒杵磨來磨去。\n";
                break;
        case 5:
                msg_me = "你輕輕的合上" + qm->name() +
                         "，默默的運用內力，烘培裏面的藥材。\n";
                msg_out = "$N合上" + qm->name() + "，雙手抱着，不知道在幹什麼。\n";
                break;
        case 6:
                if( query("jing", me)<req["jing"] )
                {
                        write("你覺得精神不濟，看來難以繼續調劑「" +
                              med->name() + "」。\n");
                        return stop_making(me);
                }
                        
        
                if( query("neili", me)<req["neili"] )
                {
                        write("你覺得內力不濟，看來難以繼續調劑「" +
                              med->name() + "」。\n");
                        return stop_making(me);
                }
        
                if( query("jingli", me)<req["jingli"] )
                {
                        write("你覺得精力不濟，看來難以繼續調劑「" +
                              med->name() + "」。\n");
                        return stop_making(me);
                }
        
                me->receive_damage("jing", req["jing"]);
                addn("neili", -req["neili"], me);
                addn("jingli", -req["jingli"], me);

                if( me->add_temp("making/time",-1)>0 )
                {
                        // when time > 0, next busy stage will
                        // still at 6, becuase the step will be
                        // increase by 1 later, so I decrase it
                        // first
                        step--;
                }

                msg_me = random(2) ? "你覺得" + qm->name() + "慢慢的熱了起來，感"
                                     "覺到裏面的藥材似乎已經融化了。\n"
                                   : "你不斷的將內力傳入" + qm->name() + "，發熱"
                                     "使裏面的藥材融化合一。\n";
                msg_out = random(2) ? "$N像老和尚一樣閉目冥神坐在那裏。\n"
                                    : "$N手裏握着" + qm->name() + "沒完沒了的轉來轉去。\n";

                break;
        case 7:
                msg_me = "你運用內力，隔着" + qm->name() + "使裏面的藥材徹底的融合。\n";
                msg_out = "$N眉毛動了動，接着又像老和尚一樣閉目冥神坐在那裏。\n";
                break;
        case 8:
                msg_me = "你長吁了一口氣，慢慢的把手拿開，打開了" + qm->name() + "。\n";
                msg_out = "$N長吁了一口氣，慢慢的把手拿開，打開了" + qm->name() + "。\n";
                break;
        case 9:
                if ((random(me->query_skill("medical", 1) +
                     query("item_prop/medical", qm)) >= req["min_level"]) ||
                    (me->query_skillo("liandan-shu", 1) + query("item_prop/liandan-shu", qm)) >= req["liandan-shu"]+100 )
                {
                        ob = new(med);
                        ob->move(qm, 1);
                        msg_me = HIM "你把「" + ob->name() + HIM "」成功的制好了！\n" NOR;
                        msg_out = HIM "$N" HIM "嘴角露出一絲微笑。\n" NOR;
                        me->improve_skill("liandan-shu", me->query_int()*100+100); 
                }else if( !query("special_skill/lucky", me) || random(2) == 0 )
                {
                        msg_me = HIG "真令人沮喪！居然失敗了，真是可惜了。\n" NOR;
                        msg_out = HIG "$N" HIG "一臉沮喪，不"
                                  "知道發生了什麼倒黴事。\n" NOR;
                }else
                {
                        ob = new(med);
                        ob->move(qm, 1);
                        msg_me = HIM "你感覺似乎有什麼地方沒有做對，然而你的運氣實在太好了！\n你把「" + ob->name() + HIM "」成功的制好了！\n" NOR;
                        msg_out = HIM "$N" HIM "嘴角露出一絲微笑。\n" NOR;
                        me->improve_skill("liandan-shu", me->query_int()*10+10); 
                }
                break;
        }

        msg_out = replace_string(msg_out, "$N", me->name());
        message("vision", msg_me, me);
        message("vision", msg_out, environment(me), ({ me }));
        step++;
        if (step >= 10)
                // end of making
                return stop_making(me);

        set_temp("pending/making", step, me);
        return 1;
}

int halt_make(object me)
{
        message_vision("$N把手中的研缽一翻個，東西"
                       "全都倒了出來。\n", me);
        stop_making(me);
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : make [<藥品>] [?]

這個指令可以讓你煉製某樣藥品，如果沒有指明藥品則會列出當前
你會煉製的藥品。如果在指明的藥品後面添加一個"?" 則會列出煉
制這種藥品需要的材料。

HELP );
    return 1;
}
