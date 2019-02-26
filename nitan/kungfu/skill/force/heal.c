// heal.c
// Updated by Lonely

// 參考於俠客行
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **\
 * heal.c 內功治療內傷功能                                              *
 *                                                                      *
 * 內功應該擁有幾種共有的功能，像已有的打坐、吐吶、運氣、運精、運精力， *
 * 以及開放中的比拼內力。其中運轉內息治療內傷也應該是所有內功都應該有的 *
 * 功能。                                                               *
 * 泥潭現有的傷害系統，在內傷和外傷完全沒有區別。內傷外傷是兩碼子事，當 *
 * 內功高，內傷自然容易好。外傷卻未必，又不是神功一運，立即鎮傷生肌，那 *
 * 變成生化人了。所以外傷在大部份情況下只能藉助於外界藥物的輔助來治療。 *
 * 基本上普通內傷都可以通過運轉內息來治療，所差者不過於不同內功在於治療 *
 * 方面效果的好壞，而且如果傷勢越重，效果越小，不像以前俠客行一次多少內 *
 * 力、就固定恢復多少。通過內傷的康復，慢慢會加快治癒速度。而外傷的康愈 *
 * 速度，多半則取決於其傷勢的程度，所用藥物的藥性，以及本身的肌肉構造， *
 * 也就是泥潭裏面的con。                                       *
 * 至於如何體現出內外傷的不同，而將這泥潭的傷害系統做得更合理性，這些是 *
 * 以後所要改變的，這裏所要説明的只是以下功能只是以內傷作為前提考慮，所 *
 * 以或許對於泥潭現有的傷害系統會有少許的不合理性。                     *
 *                                                                      *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/


#include <ansi.h>

mapping eff_heal = ([
        "yinyang-shiertian"     : 21,   // 轉世技能，最強的內功。
        "jiuyin-shengong"       : 10,   // 大宗師內功超強。
        "bluesea-force"         : 10,   // 大宗師內功超強。
        "never-defeated"        : 10,   // 大宗師內功超強。
        "kuihua-mogong"         : 10,   // 大宗師內功超強。
        "jiuyang-shengong"      : 9,    // 九陽神功在療傷方面的效果無可置疑。
        "taixuan-gong"          : 9,    // 參考九陽神功。
        "yijinjing"             : 9,
        "hunyuan-yiqi"          : 8,    // 鑑於易筋經以及九陽神功在療傷方面的效果。
        "zixia-shengong"        : 8,    // 紫霞神功及混元功在自療方面沒有什麼提及，但是有鑑
                                        // 於其療人的效果，以及嶽不羣曾經想讓令狐沖自習紫霞
                                        // 神功來治療內傷，可見於自療方面的效果，或許可以與
                                        // 易筋經相媲美。就算是有所不及，考慮到當今紫霞神功
                                        // 沒有什麼特別的 exert，也應當讓紫霞神功在治療方面
                                        // 的效果相對於其他內功更好。
        "taiji-shengong"        : 8,
        "xiantian-gong"         : 8,    // 書中有相當篇幅提到武當九陽功與全真玄門內功的療傷。
        "kurong-changong"       : 7,    // 大理內功在療人方面的效果很好，可是在自療方面卻沒
                                        // 有什麼特別之處。
        "linji-zhuang"          : 7,    // 峨嵋內功在療傷方面沒有什麼特別描述，不過因其是九
                                        // 陽一系。
        "bibo-shengong"         : 6,
        "yunu-xinfa"            : 6,
        "xiaowuxiang"           : 5,
        "sanku-shengong"        : 5,    // 三苦神功，為唐門內功，療傷一般,在療毒方面超強。
        "huntian-qigong"        : 4,    // 混天功、蛤蟆功、龍象般若功走的都是剛猛一路的內功，
        "hamagong"              : 4,    // 因此在療傷方面會相對弱些。
        "longxiang-gong"        : 4,
        "beiming-shengong"      : 3,    // 北冥神功吸人內力，體內真氣相沖會影響療傷時的效果。
        "huagong-dafa"          : 2,    // 化功大法以毒練功，在療傷方面效果應該最為不好。
        "dulong-dafa"           : 2,
        "hongming-xuangong"     : 1,
        "ding-force"            : 1,    // 以上三種內功書中未有提及，被列為不可考。
]);


int exert(object me, object target)
{
        string force;
        mapping msg;

        if (me->is_fighting())
                return notify_fail("戰鬥中運功療傷？找死嗎？\n");

        if (me->is_busy())
                return notify_fail("等你忙完了手頭的事情再説！\n");

        force = me->query_skill_mapped("force");
        if (! stringp(force))
                return notify_fail("先激發你的特殊內功。\n");

        if( query("eff_qi", me) >= query("max_qi", me) )
                return notify_fail("你現在氣血充盈，不需要療傷。\n");

        if ((int)me->query_skill(force, 1) < 20)
                return notify_fail("你的" + to_chinese(force) + "修為還不夠。\n");

        if( query("neili", me)<50 )
                return notify_fail("你的真氣不夠。\n");

        if( query("eff_qi", me)<query("max_qi", me)/5 )
                return notify_fail("你已經受傷過重，只怕一運真氣便有生命危險！\n");
        
        msg = SKILL_D(force)->heal_msg(me);
                
        if (! msg || undefinedp(msg["start_self"]))
                write(HIW "你全身放鬆，坐下來開始運功療傷。\n" NOR);
        else 
                write(msg["start_self"]);               

        set_temp("pending/healing", 1, me);
        
        if (! msg || undefinedp(msg["apply_short"]))
                me->set_short_desc("正坐在地下運功療傷。");                
        else    
                me->set_short_desc(msg["apply_short"]);

        if (! msg || undefinedp(msg["start_other"]))
                tell_room(environment(me), HIW + me->name() + "盤膝坐下，開始運功療傷。\n" NOR, me);
        else
                tell_room(environment(me), msg["start_other"], me); 
                                
        me->start_busy((:call_other, __FILE__, "healing" :),
                       (:call_other, __FILE__, "halt_healing" :));

        return 1;
}

// 療傷中
int healing(object me)
{
        string force;
        int recover_points, lvl, con, eff;
        mapping msg;

        force = me->query_skill_mapped("force");
        if (! stringp(force))
        {
                // 沒有特殊內功了？
                tell_object(me, "你一時難以定奪如何運用內力，只好先暫停療傷。\n");
                set_temp("pending/healing", 0, me);
                me->set_short_desc(0);
                message_vision("$N歎了口氣，搖搖晃晃的站了起來。\n", me);
                return 0;
        }
        
        msg = SKILL_D(force)->heal_msg(me);

        if( query("eff_qi", me)<query("max_qi", me) )
        {
                // 需要繼續療傷
                if( query("neili", me)<50 )
                {
                        if (! msg || undefinedp(msg["unfinish_self"]))
                                tell_object(me, "你覺得真氣不濟，難以在經脈中繼續運轉療傷，只得暫緩療傷，站起身來。\n");
                        else    
                                tell_object(me, msg["unfinish_self"]);
                                
                        set_temp("pending/healing", 0, me);
                        me->set_short_desc(0);
                        
                        if (! msg || undefinedp(msg["unfinish_other"]))
                                tell_room(environment(me), me->name() + "歎了口氣，搖搖晃晃的站了起來。\n", me);
                        else    
                                tell_room(environment(me), msg["unfinish_other"], me);
                                
                        return 0;
                }
                
                //lvl = (int)me->query_skill("force") / 10;
                lvl = (int)me->query_skill("force");
                con = (int)me->query_con();
                eff = eff_heal[force];
                if (! eff ) eff = 3;

                recover_points = con + lvl * eff;
                if( query("breakup", me) )
                        recover_points *= 3;
                   if (recover_points < 1) recover_points = 1;
                me->receive_curing("qi", recover_points);                                
                addn("neili", -50, me);
                
                if (! msg || undefinedp(msg["heal_msg"]))
                {
                        switch (random(10))
                        {
                        case 0:
                                tell_object(me, "你運用" + to_chinese(force) + "沿着"
                                                "諸大穴慢慢運轉，療解傷痛。\n");
                                break;
                        case 1:
                                tell_object(me, "你將內力納入丹田，再上行衝頂，透泥宮"
                                                "，頓覺精神爽快。\n");
                                break;
                        case 2:
                                tell_object(me, "你將內力運入四肢百賅，復又回收丹田，"
                                                 "傷勢痊癒不少。\n");
                                break;
                        }
                        return 1;
                } else
                {
                        tell_object(me, msg["heal_msg"]);
                        return 1;
                }
        }

        // 恢復完畢
        set_temp("pending/exercise", 0, me);
        me->set_short_desc(0);
        if (! msg || undefinedp(msg["finish_self"]))
                tell_object(me, HIY "你運功完畢，吐出一口瘀血，自覺經脈順暢，內傷盡去，神元氣足地站了起來。\n" NOR);
        else    
                tell_room(me, msg["finish_self"]); 
                
        if (! msg || undefinedp(msg["finish_other"]))
                tell_room(environment(me), HIY + me->name() + "運功完畢，吐出一口瘀血，站起身來，臉色看起來好多了。\n" NOR, me);
        else
                tell_room(environment(me), msg["finish_other"], me);      
                
        return 0;
}

// 停止療傷
int halt_healing(object me)
{
        string force;
        mapping msg;
        
        if (stringp(force = me->query_skill_mapped("force"))) 
                msg = SKILL_D(force)->heal_msg(me);
        
        if (! msg || undefinedp(msg["halt_self"]))
                tell_object(me, "你將真氣收回丹田，微微喘息，站了起來。\n");
        else    
                tell_object(me, msg["halt_self"]);
                
        if (! msg || undefinedp(msg["halt_other"]))
                tell_room(environment(me), me->name() + "猛的吸一口氣，突然站了起來。\n", me);
        else    
                tell_room(environment(me), msg["halt_other"], me);
                
        set_temp("pending/healing", 0, me);
        me->set_short_desc(0);
        if( query("neili", me)>100 )
                addn("neili", -100, me);
        else
                set("neili", 0, me);
        return 1;
}
