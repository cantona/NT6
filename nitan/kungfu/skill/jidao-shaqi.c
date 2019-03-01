// jidao-shaqi.c 極道煞氣
// By Alf

inherit FORCE;

int valid_enable(string usage)
{
    return usage == "force";
}

int valid_learn(object me)
{
    int lvl = (int)me->query_skill("jidao-shaqi", 1);

    if ((int)me->query_skill("force", 1) < 30)
        return notify_fail("你的基本內功火候還不夠，還不能學習極道煞氣。\n");

    if (
    me->query_skill("bahuang-gong",1)    // 靈鷲：八荒六合功
    || me->query_skill("beiming-shengong",1)    // 逍遙：北冥神功
    || me->query_skill("bibo-shengong",1)    // 桃花：碧波神功
    || me->query_skill("chunyang-gong",1)    // 大理：純陽功
    || me->query_skill("hamagong",1)    // 白駝：蛤蟆功
    || me->query_skill("huagong-dafa",1)    // 星宿：化功大法
    || me->query_skill("huntian-qigong",1)    // 丐幫：混天氣功
    || me->query_skill("hunyuan-yiqi",1)    // 少林：混元一氣功
    || me->query_skill("jiuyang-shengong",1)    // 少林：九陽神功
    || me->query_skill("linji-zhuang",1)    // 峨嵋：臨濟十二莊
    || me->query_skill("longhu-baqi",1)    // 武官：龍虎霸氣
    || me->query_skill("nilian-shengong",1)    // 白駝：逆練神功
    || me->query_skill("shenlong-zhanqi",1)    // 神龍：神龍戰氣
    || me->query_skill("taiji-shengong",1)    // 武當：太極神功
    || me->query_skill("wolong-xingfa",1)    // 巡捕：臥龍心法
    || me->query_skill("wuwang-shenzhou",1)    // 凌霄城：無妄神咒
    || me->query_skill("xiantian-gong",1)    // 全真：先天功
    || me->query_skill("xiawuxiang",1)    // 雪山：小無相功
    || me->query_skill("xuanmen-neigong",1)    // 全真：玄門內功
    || me->query_skill("yunlong-shengong",1) // 雲龍：雲龍神功
    || me->query_skill("zixia-shengong",1) )    // 華山：紫霞神功
        return notify_fail("你不先散了別派內功，怎能學極道煞氣？！\n");
    return 1;
}


int practice_skill(object me)
{
    return notify_fail("極道煞氣只能通過學習(xue)，或是從運用(yun)中增加熟練度。\n");
}

string exert_function_file(string func)
{
    return "/kungfu/perform/jidao-shaqi/" + func;
}

