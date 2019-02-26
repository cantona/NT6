// This program is a part of NT MudLIB

#include <ansi.h>

#define ZHOUTIAN_D      "/adm/daemons/zhoutiand"

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object tongren_ob;

        if( me->is_busy() || me->is_fighting() )
                return notify_fail(BUSY_MESSAGE);

        if( !arg || arg == "" )
                return notify_fail("指令格式 : chongxue <穴位銅人ID>\n");

        if( (int)me->query_skill("force", 1) < 200 )
                return notify_fail("你的內功修為不足，無法將細小經脈穴位打通。\n");

        if( (int)me->query_skill("jingluo-xue", 1) < 100 )
                return notify_fail("你對經絡學掌握不夠，無法將細小經脈穴位打通。\n");

        if( query("qi", me)*100/query("max_qi", me)<90 )
                return notify_fail("你現在的氣太少了，無法靜心衝穴。\n");

        if( query("jing", me)*100/query("max_jing", me)<90 )
                return notify_fail("你現在的精太少了，無法靜心衝穴。\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("你覺得內力頗有不足，無法將細小經脈穴位打通。\n");

        if( query("neili", me)*100/query("max_neili", me)<90 )
                return notify_fail("你現在的內力太少了，無法運功衝穴。\n");

        if( arg == "all" )
        {
                if( !query("jingmai/finish", me) )
                        return notify_fail("你並沒有全身大小週天經脈穴道貫通過。\n");

                set("breakup", 1, me);
                message_vision( HIC "突然$N" HIC "大喝一聲，一股無形氣浪" 
                                HIC "陡然散佈開來，四周空氣登時變得燥熱。\n" NOR, me); 
                tell_object(me, HIG "你頓時覺得渾身一陣輕鬆，一股清涼之意油然" 
                                HIG "而起，心靈一片空明，內力沒有絲毫阻滯，全身經脈已然暢通，舒泰之極。\n" NOR); 
                return 1;
        }

        if( query("jingmai/finish", me) )
                return notify_fail("你已經打通全身大小週天經脈，無需再次衝穴。\n");

        if( !objectp(tongren_ob = present(arg, me)) )
                return notify_fail("你身上沒有這個銅人！\n");

        if( !tongren_ob->is_tongren() )
                return notify_fail("你無法使用它來衝穴。\n");

        if( query("jingmai/"+query("jingmai_name", tongren_ob)+"/"+arg, me) )
                return notify_fail("你已經打通了這個穴位。\n");

        message_vision(HIW "$N" HIW "按照銅人所記載的衝穴方式，藉助銅人之物，暗運內功，開始衝穴。\n" NOR, me);
        message_vision(HIW "只見$N" HIW "頭上白霧騰騰、渾身如同籠罩在雲中。\n" NOR, me);

        tell_object(me, HIG "你覺得內力在丹田源源而生，快速翻滾，體內真元運轉越來越快，\n"
                        HIG"渾身燥熱難當，一股真氣流衝向"+query("xuewei_name", tongren_ob)+"而去。\n"NOR);


        ZHOUTIAN_D->do_chongxue(me, tongren_ob);

        me->start_busy(1);

        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : chongxue <穴位銅人ID>
           chongxue all    如果上世曾經大小週天經脈穴道貫通過，使用該指令衝穴

該指令可以細小經脈打通，連接成完整經脈。

HELP
);
        return 1;
}


