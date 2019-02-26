#include <ansi.h>
inherit ITEM;

void create()
{
        set_name("佈陣箱", ({ "buzhen xiang", "buzhen", "xiang" }));
        set_weight(4000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + WHT "這是一個頗為陳舊的墨漆木箱，箱中"
                            "裝有各種各樣\n的道具，大非尋常。可以用來布"
                            "陣(" HIW "array" NOR + WHT ")惑敵。\n" NOR);
                set("unit", "個");
                set("value", 5000);
                set("no_sell", "嘿，這破箱子也能賣錢？\n");
                set("count", 5);
                set("material", "wood");
        }
        setup();
}

void init()
{
        add_action("do_array", "array");
        add_action("do_array", "buzhen");
}

int do_array(string arg)
{
        object me, env, *ob;
        string desc;
        int skill;
        mapping exit;

        me = this_player();

        if (me->is_busy()
            || query_temp("pending/exercising", me )
            || query_temp("exit_blocked", me) )
                return notify_fail("你現在正忙着呢。\n");

        env = environment(me);
        exit=query("exits", env);

        skill = (int)me->query_skill("qimen-wuxing", 1);

        if (skill < 1)
                return notify_fail("你把佈陣箱翻來覆去擺弄了半天，卻"
                                   "不知如何下手。\n");

        if (query("count") < 1)
                return notify_fail("佈陣箱中的物件已經用完了。\n");

        if (skill < 120)
                return notify_fail("你對奇門五行的研究不夠，尚且無法"
                                   "佈陣。\n");

        if (! env)
                return notify_fail("這裏無法佈陣。\n");

        if (wiz_level(me) < 3
            && (query("no_fight", env )
            || query("sleep_room", env )
            || query("skybook", env )
            || query("no_sleep_room", env)) )
                return notify_fail("這裏不是你囂張的地方。\n");

        if( wiz_level(me)<3 && !query("outdoors", env) )
                return notify_fail("室內空間過於狹小，難以佈陣。\n");

        if( query("th_buzhen", env) )
                return notify_fail("這裏已經布有奇門陣法。\n");

        if( query("max_jingli", me)<800 )
                return notify_fail("你的精力修為不足，難以佈陣。\n");

        if( query("jingli", me)<500 )
                return notify_fail("你目前的精力不足，難以佈陣。\n");

        if( query("jing", me)<300 )
                return notify_fail("你目前的精氣不足，難以佈陣。\n");

        addn("count", -1);
        me->receive_damage("jing", 200);
        addn("jingli", -300, me);
        me->start_busy(5);

        message_sort(HIG "\n$N" HIG "微微一笑，驀地擺出" NOR + WHT "佈陣箱"
                     HIG "，隨後身形急轉，飄舞不定，在四周迅速佈下奇門陣法"
                     "。霎時煙塵四起，砂石亂飛，聲勢煞為驚人。不一刻，又見"
                     "$N" HIG "收勢凝形負手而立，四下裏從寂靜中隱隱透出一股"
                     "肅殺之氣。\n\n" NOR, me);

        desc=query("long", env)+HIM"\n卻見此處景況非常詭異，紫色霧氣彌"
               "漫於空中，透出森森鬼氣。\n\n" NOR;

        set("org_desc",query("long",  env), env);
        set("org_exits",query("exits",  env), env);
        set("org_cost",query("cost",  env), env);
        set("long", desc, env);
        set("th_buzhen", 1, env);
        set("th_zhen_owner",query("id",  me), env);
        set("th_pozhen", skill, env);

        if (skill < 150)
        {
                env->set("exits",([
                        "east"  : file_name(env),
                        "south" : file_name(env), 
                        "west"  : file_name(env),
                        "north" : file_name(env),
                ]));
        } else
        if (skill < 180)
        {
                env->set("exits",([
                        "east"  : file_name(env),
                        "south" : file_name(env),
                        "west"  : file_name(env),
                        "north" : file_name(env),
                        "northwest" : file_name(env),
                        "northeast" : file_name(env),
                        "southeast" : file_name(env),
                        "southwest" : file_name(env),
                ]));
        } else
        {
                env->set("exits",([
                        "east"  : file_name(env),
                        "south" : file_name(env),
                        "west"  : file_name(env),
                        "north" : file_name(env),
                        "enter" : file_name(env),
                        "out"   : file_name(env),
                        "up"    : file_name(env),
                        "down"  : file_name(env),
                        "northwest" : file_name(env),
                        "northeast" : file_name(env),
                        "southeast" : file_name(env),
                        "southwest" : file_name(env),
                ]));
        }
        call_out("remove_effect", skill / 2, env);
        return 1;
}

void remove_effect(object env)
{
        if( !env || !query("th_buzhen", env) )
                return;

        set("long",query("org_desc",  env), env);
        set("exits",query("org_exits",  env), env);
        set("cost",query("org_cost",  env), env);
        delete("org_desc", env);
        delete("org_cost", env);
        delete("org_exits", env);
        delete("th_buzhen", env);
        delete("th_pozhen", env);
        delete("th_zhen_owner", env);

        tell_object(env, HIM "\n突然間紫霧朝周圍散去，四面景緻"
                         "猛然一變。\n\n" NOR);
}