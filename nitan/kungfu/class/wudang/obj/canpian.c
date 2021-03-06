//Cracked by Kafei
// canpian
// used to improve tjsg and hunyuan-yiqi over 200
// -chu@xkx

#include <ansi.h>
#include <weapon.h>

inherit ITEM;
inherit F_UNIQUE;

int do_dun(string arg);
int do_jie(string arg);

void create()
{
    set_name(YEL "九陽神功殘篇" NOR, ({"canpian", "book"}));
    set_weight(100);
    if (clonep())
        set_default_object(__FILE__);
    else {
        set("unit", "部");
        set("long", "這是武當派祖師張三丰真人筆錄的部分九陽神功。\n");
        set("material", "paper");
        set("value", 1);
                set("skill", ([
                        "name": "jiuyang-shengong",        // name of the skill
                        "exp_required": 10000000,      // minimum combat experience required
                        "jing_cost":    300,     // jing cost every time study this
                        "difficulty":   100,     // the base int to learn this skill
                        "max_skill":    100      // the maximum level you can learn
                ]) );
    }
}

int init()
{
    add_action("do_canwu", "canwu");
    return 1;
}

int do_canwu(string arg)
{
    object player = this_player();
    object target, obj=this_object(), env=environment(player);
    string my_skill, your_skill;
    int my_lvl, your_lvl;

    if (!arg) return notify_fail("你要跟誰一起參悟?\n");
    target = present(arg, env);
    if (!objectp(target))  return notify_fail("你要跟誰一起參悟?\n");
    if (!userp(target))    return notify_fail("你只能跟玩家一起參悟。\n");
    if (player->is_busy()) return notify_fail("你正忙着呢。\n");
    
    my_lvl = player->query_skill("taiji-shengong", 1);
    your_lvl = player->query_skill("hunyuan-yiqi", 1);
    if (my_lvl < 200 && your_lvl < 200) 
        return notify_fail("你的太極神功或者混元一氣功不夠高，無法參悟。\n");
    if (my_lvl >= 200) {
        my_skill = "taiji-shengong";
        your_skill = "hunyuan-yiqi";
        your_lvl = target->query_skill("hunyuan-yiqi", 1);
    }else {
        my_lvl = your_lvl;
        your_lvl = target->query_skill("taiji-shengong", 1);
        my_skill = "hunyuan-yiqi";
        your_skill = "taiji-shengong";
    }
    if (your_lvl < my_lvl-10)
        return notify_fail(target->name(1)+"的本門內功遠遜於你，已不能幫你參悟了。\n");
    if( query("jing", player)<1000 )
        return notify_fail("你精神不濟，連話都説不清楚了。\n");
    if( query("jing", target)<1000 )
        return notify_fail("你想向"+target->name(1)+"請教有關"+
                to_chinese(your_skill)+"的問題，可人家沒精打采的不理你。\n");
    message_vision("$N拿出九陽神功殘篇，跟$n相互參悟，雙方似有所悟。\n",
        player, target);

    if (wizardp(player)) {
        tell_object(player, sprintf("my_skill = %s/%d, yourskill=%s/%d\n",
            my_skill, my_lvl, your_skill, your_lvl));
        tell_object(player, "valid_learn() returns "+
            SKILL_D(my_skill)->valid_learn(player)+"\n");
    } 

    if (wizardp(target)) {
        tell_object(target, sprintf("my_skill = %s/%d, yourskill=%s/%d\n",
            my_skill, my_lvl, your_skill, your_lvl));
        tell_object(target, "valid_learn() returns "+
                SKILL_D(your_skill)->valid_learn(target)+"\n");
    } 

    addn("jing", -1000, player);
    addn("jing", -500, target);

    if (SKILL_D(my_skill)->valid_learn(player))    {
        player->improve_skill(my_skill, 200);
        if (SKILL_D(your_skill)->valid_learn(target))  target->improve_skill(your_skill, 80);
        return 1;
    }
    return 0;
}