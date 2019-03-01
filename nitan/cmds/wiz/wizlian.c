// wizlian.c 巫師專用
// Written by Doing Lu 1998/11/1

#include <globals.h>
#include <ansi.h>

inherit F_CLEAN_UP;

void        restore_condition(object me);
void        restore_origin(object me);

mapping attrib =([
        "qi"                 : "",
        "氣"                : "qi",
        "eff_qi"        : "",
        "有效氣"        : "eff_qi",
        "max_qi"        : "",
        "最大氣"        : "max_qi",
        "jing"                : "",
        "精"                : "jing",
        "eff_jing"        : "",
        "有效精"        : "eff_jing",
        "max_jing"        : "",
        "最大精"        : "max_jing",
        "food"                : "",
        "食物"                : "food",
        "water"                : "",
        "飲水"                : "water",
        "neili"                : "",
        "內力"                : "neili",
        "max_neili"        : "",
        "最大內力"        : "max_neili",
        "jingli"        : "",
        "精力"                : "jingli",
        "max_jingli"        : "",
        "最大精力"        : "max_jingli",
        "per"           : "",
        "容貌"          :  "per",
        "kar"           : "",
        "福緣"          :  "kar",
        "shen"                : "",
        "神"                : "shen",
        "age"           : "",
        "年齡"          : "age",
        "mud_age"        : "",
        "年齡"                : "mud_age",
        "str"                : "",
        "膂力"                : "str",
        "臂力"                : "str",
        "int"                : "",
        "悟性"                : "int",
        "智力"                : "int",
        "con"                : "",
        "根骨"                : "con",
        "dex"                : "",
        "身法"                : "dex",
        "MKS"                : "",        
        "PKS"                : "",
        "potential"        : "",
        "潛力"                : "potential",
        "潛能"                : "potential",
        "combat_exp"        : "",
        "exp"                : "combat_exp",
        "經驗"                : "combat_exp",
        "learned_points": "",
        "學習點數"        : "learnd_points",
        "score"         : "",
        "江湖閱歷"      : "score",
        "weiwang"       : "",
        "江湖威望"      : "weiwang",
        "meili"         : "",
        "魅力"          : "meili",
        "門派功績"      : "family/gongji",
        "gongji"        : "family/gongji",
        "magic_points"  : "",
        "靈惠"          : "magic_points",
        "experience"    : "",
        "實戰體會"      : "experience",
        "balance"       : "",
        "金錢"          : "balance",
        "total_hatred"  : "",
        "戾氣"          : "total_hatred",
]);

int main(object me, string arg)
{
        object ob;
        mapping learned;
        string pack, argn, argm;        // 屬性/武功  參數1  參數2:暫時不用
        int argnum;                        // 參數的個數 (包括屬性)

        int i;
        string attrs;
        
        if (! SECURITY_D->valid_grant(me, "(apprentice)")) 
                    return 0; 

        // 恢復狀態，精、氣、內力
        if (! arg)
        {
                message_vision(HIW "$N喃喃的念了一會咒語，一股煙霧籠罩了$N。\n\n" NOR, me);
                restore_condition(me);
                return 1;
        }

        // 恢復成原始數據，放棄武功
        if (arg == "org")
        {
                message_vision(HIW "$N喃喃的念了一會咒語，一股煙霧籠罩了$N。\n\n" NOR, me);
                restore_origin(me);
                return 1;
        }

        argnum = sscanf(arg, "%s %d %d", pack, argn, argm);

        if (argnum < 2)
        {
                // 沒有指定屬性
                message_vision(HIW "$N喃喃的念了一會咒語，什麼也沒發生。\n\n" NOR, me);
                return 1;
        }

        if (! undefinedp(attrs = attrib[pack]))
        {
                // 修改屬性
                if (attrs == "") attrs = pack;
                message_vision(HIW "$N喃喃的念叨：天靈靈，地靈靈，各路神仙快顯靈！\n\n" NOR, me);
                set(attrs, argn, me);
                message_vision(HIY "天上轟隆隆的響了一會，$N呵呵的笑了兩聲說道：真是靈驗。\n\n" NOR, me);
                return 1;
        } else
        {
                // 修改武功
                message_vision(HIW "$N點燃一張符咒，喝道：太上老君急急如律敕令！\n\n" NOR, me);
                
                if( !find_object(SKILL_D(pack))
                        && file_size(SKILL_D(pack)+".c") < 0 )
                {
                        message_vision(HIR "天上轟隆隆的響了一會，太上老君怒喝道：你搞什麼鬼！\n\n" NOR, me);
                        return 1;
                }

                if (argn >= 0)
                {
                        me->set_skill(pack, argn);
                        message_vision(HIY "一道金光從天上射下來，隱入$N的體內。\n\n" NOR, me);
                } else
                {
                        message_vision(HIR "天上轟隆隆的響了一會，太上老君怒喝道：不要亂來！\n\n" NOR, me);
                }
                return 1;
        }
}

void restore_condition(object me)
{
        message_vision(HIY "$N變得神採奕奕！\n\n" NOR, me);
        // 恢復氣
        set("qi",query("max_qi",  me), me);
        set("eff_qi",query("max_qi",  me), me);

        // 恢復精
        set("jing",query("max_jing",  me), me);
        set("eff_jing",query("max_jing",  me), me);

        // 恢復內力
        set("neili",query("max_neili",  me), me);

        // 恢復精力
        set("jingli",query("max_jingli",  me), me);

        // 恢復食物
        set("food", me->max_food_capacity(), me);

        // 恢復飲水
        set("water", me->max_water_capacity(), me);

        // 解毒
        set("noposion", 1, me);
}

void restore_origin(object me)
{
        int i;
        mapping pmap;
        string* sk;

        message_vision(HIY "咦，$N變得天真無邪，一臉無辜狀！\n\n" NOR, me);
        
        // 恢復神， PK, MPK
        set("shen", 0, me);
        set("PKS", 0, me);
        set("MKS", 0, me);

        // disbale並且放棄各種武功

        pmap = me->query_skill_prepare();                // 準備的技能
        if (!pmap) pmap = ([]);

        if( mapp(pmap) && sizeof(pmap) > 0 )
        {
                sk = keys(pmap);
                for (i=0; i<sizeof(sk); i++)
                {
                        me->prepare_skill(sk[i]);        // 清除準備的技能
                }
        }
        
        sk = keys(me->query_skills());                        // 所學武功的名稱集合
        for(i = 0; i<sizeof(sk); i++)
        {
                me->map_skill(sk[i]);                        // 取消激發某項武功
                map_delete(me->query_skills(), sk[i]);        // 放棄所學的武功
        }

        delete("family", me);

        me->reset_action();                                // 完成
}

int help(object me)
{
write(@HELP
指令格式 : wizlian <武功/屬性> 值

此命令提升巫師的武功，或是修改各項屬性，包括氣，精，神...

wizlian          : 恢復所有屬性包括氣，精，精力，內力，食物，飲水。
wizlian org      : 初始化個人數據，放棄所有武功，神降到0。
wizlian [屬性] n : 修改某項屬性為n。
wizlian [武功] n : 修改某項武功為n級，點數為m，如果小于零就不修改。

HELP
    );
    return 1;
}
