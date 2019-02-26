// chuancai-jiyi.c

inherit SKILL;

string type() { return "knowledge"; }

int valid_enable(string usage) { return usage == "cooking"; }

int valid_learn(object me)
{
    return 1;
}

mapping query_menu(object me)
{
        return ([ "香酥花生"   : ({ "xiangshu huasheng" }),
                  "麻辣手撕雞" : ({ "mala ji" }),
                  "手撕雞"     : ({ "shousi ji" }),
                  "三黃雞"     : ({ "sanhuang ji" }),
                  "乾煸尤魚"   : ({ "ganbian youyu" }),
                  "魚香肉絲"   : ({ "yuxiang rousi" }),
                  "宮寶雞丁"   : ({ "gongbao jiding" }),
                  "紅油肚片"   : ({ "hongyou dupian" }),
                  "麻婆豆腐"   : ({ "mapo doufu" }),
                  "夫妻肺片"   : ({ "fuqi feipian" }),
                  "毛血旺"     : ({ "maoxue wang" }),
                  "粉蒸肉"     : ({ "fenzheng rou" }) ]);
}

int practice_skill(object me)
{
        object cailiao;

        if (! objectp(cailiao = present("cai liao", me)) ||
            cailiao->query_amount() < 1)
                return notify_fail("你身上沒有菜料了。\n");

        if( query("qi", me)<50 )
                return notify_fail("你的體力不夠了，無法鍛鍊手藝。\n");

        if( query("jing", me)<50 )
                return notify_fail("你的精神不濟，無法鍛鍊手藝。\n");

        me->receive_damage("qi", 40);
        me->receive_jing("jing", 40);
        cailiao->add_amount(-1);

        return 1;
}
