// perform.c

#include <ansi.h>

inherit F_CLEAN_UP;

protected int do_perform(object me, string arg);

int main(object me, string arg)
{
        string and;
        int result;
        int busy;
        int lvl;
        string msg;
        string *fams;

        seteuid(getuid());

        if (me->is_busy())
                return notify_fail("( 你上一個動作還沒有完成，不能施用外功。)\n");

        if (! arg) return notify_fail("你要用外功做什麼？\n");

        if (query_temp("forget", me)) 
                return notify_fail(HIR "你發現自己遺忘了絕招如何使用。\n" NOR);

        if (me->query_condition("no_perform"))
                return notify_fail(HIR "你只覺全身力道竟似渙散了一般，全然無法控制。\n" NOR);

        if (query_temp("freeze", me) && time()-query_temp("last_perform_time", me) < 1)
                return notify_fail(HIR "你處于冰凍不良的狀態下，動作緩慢，無法如此快速連續使用絕招。\n" NOR);

        if (sscanf(arg, "%s and %s", arg, and) == 2 ||
            sscanf(arg, "%s twice", arg) == 1 && (and = arg))
        {
                lvl = me->query_skill("zuoyou-hubo", 1);
                if (! lvl)
                        return notify_fail("你要幹什麼？以為自己有三頭六臂啊！\n");

                if( me->query_skill("count",1) && !query("special_skill/capture", me) )
                        return notify_fail("你雜學太多，心頭煩亂，難以分心二用。\n");

                if (lvl <= 100)
                        return notify_fail("你的左右互搏修為太淺，難以分心二用。\n");

                if( query("int", me)>24 && query("int", me)<40 )
                        return notify_fail("你試圖分心二用，但是手就是不聽使喚。\n");

                if( (!arrayp(fams = query("reborn/fams", me)) || 
                    (member_array("全真教", fams) == -1 &&
                    member_array("古墓派", fams) == -1)) && 
                    (! me->query_family() ||
                    ( me->query_family() != "全真教" &&
                      me->query_family() != "古墓派" )))
                        return notify_fail("你試圖分心二用，但是手就是不聽使喚。\n");

                if (! me->is_fighting())
                        return notify_fail("只有戰鬥中才能施展左右互搏。\n");

                if (lvl < 360 && random(lvl) < 100)
                {
                        me->start_busy(1);
                        write("你試圖分心二用，但是手就是不聽使喚。\n");
                        return 1;
                }
        }

        if (and) set_temp("use_hubo", 1, me);

        result = do_perform(me, arg);
        if (! and)
                return result;

        if (! result)
                write(query_notify_fail());
        else
        {
                switch (random(4))
                {
                case 0:
                        msg = HIY "$N" HIY "大喝一聲，雙手分"
                              "使兩招，一起攻出。\n" NOR;
                        break;

                case 1:
                        msg = HIY "$N" HIY "雙手齊出，分使不"
                              "同招式，令人眼花繚亂。\n" NOR;
                        break;

                case 2:
                        msg = HIY "$N" HIY "左右手分使兩招，"
                              "毫不停滯，宛如兩人同時攻出。\n" NOR;
                        break;

                case 3:
                        msg = HIY "$N" HIY "左手一招，右手一"
                              "招，兩招來路各異，令人難以低檔！\n" NOR;
                        break;
                }

                message_combatd(msg, me);
        }

        busy = me->query_busy();
        me->interrupt_busy(0);

        result = do_perform(me, and);
        if (! result)
                write(query_notify_fail());

        if (intp(busy) && intp(me->query_busy()) &&
            busy > me->query_busy())
        {
                me->interrupt_busy(0);
                me->start_busy();
        }
        delete_temp("use_hubo", me);
        return 1;
}

protected int do_perform(object me, string arg)
{
        object weapon;
        string martial, skill;
        int result;

        if (sscanf(arg, "%s.%s", martial, arg) != 2)
        {
                if( weapon=query_temp("weapon", me) )
                        martial=query("skill_type", weapon);
                else
                        martial = "unarmed";
        }

        me->clean_up_enemy();
        if (stringp(skill = me->query_skill_mapped(martial)))
        {
                notify_fail("你所使用的外功中沒有這種功能。\n");
                if (SKILL_D(skill)->perform_action(me, arg))
                {
                        set_temp("last_perform_time", time(), me);
                        if (random(120) < (int)me->query_skill(skill))
                                me->improve_skill(skill, 1, 1);
                        return 1;
                } else
                if (SKILL_D(martial)->perform_action(me, arg))
                {
                        set_temp("last_perform_time", time(), me);
                        if (random(120) < (int)me->query_skill(martial, 1))
                                me->improve_skill(martial, 1, 1);
                        return 1;
                }
                return 0;
        }

        return notify_fail("你現在的" + to_chinese(martial)[4..7] +
                           "(" + martial + ")中並沒有這種外功。\n");
}

int help (object me)
{
        write(@HELP
指令格式：perform | yong [<武功種類>.]<招式名稱> [<施用對象>]
          perform | yong 招式1 [<對象1>] and 招式2 [<對象2>]
          perform | yong 招式1 [<對象1>] twice

如果你所學的外功(拳腳、劍法、刀法....)有一些特殊的攻擊方式或
招式，可以用這個指令來使用，你必須先用 enable 指令指定你使用
的武功，不指定武功種類時，空手的外功是指你的拳腳功夫，使用武
器時則是兵刃的武功。

若是你的外功中有種類不同，但是招式名稱相同的，或者不屬於拳腳
跟武器技能的武功(如輕功)，可以用 <武功>.<招式>  的方式指定，
如：

perform sword.chan

換句話說，只要是 enable 中的武功有特殊招式的，都可以用這個指
令使用。

如果你精通左右互搏，可以同時使用兩個招式攻擊同一對手或則分別
攻擊兩人。左右互搏修煉的越是精深，則成功率越高。

使用 twice 參數表示左右手使用同樣的招式。
HELP );
        return 1;
}
