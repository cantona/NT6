// Room: /d/gumu/woshi1.c
// Last Modifyed by Winder on Jan. 14 2002

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short",HIC"小臥室"NOR);
        set("long", @LONG
這裡是楊過當年的臥室，房中空空洞洞。一塊長條青石作床，床上
舖了張草席，一幅白布當作薄被，此外除了一根人高的繩索橫過室中，
別無他物。
LONG        );
        set("exits", ([
                "west" : __DIR__"mudao20",
        ]));
        set("objects", ([
                __DIR__"obj/bed" : 1,
        ]));
        set("sleep_room", 1);
        set("no_fight", 1);

        set("coor/x", -3160);
        set("coor/y", -10);
        set("coor/z", 90);
        setup();
}

void init()
{
        add_action("do_zuo", "zuo");
        add_action("do_zuo", "sleep");
        add_action("do_liao", "liao");
}

int do_zuo(string arg)
{
        object me = this_player();
        int exp, lvl;

        exp=query("combat_exp", me);
        if (me->is_busy() || me->is_fighting())
                return notify_fail("你正忙著哪！\n");
        if (arg == "bed" || arg == "chuang")
        {
                if( me->query_skill("yunv-xinfa", 1) < 1)
                {
                        message_vision("$N現在的內功承受不住寒玉床的寒冰之氣。\n", me);
                        me->start_busy(1);
                        return 1;
                }
                if( query("neili", me)<300 )
                {
                        message_vision("$N現在的功力承受不住寒玉床的寒冰之氣。\n", me);
                        me->start_busy(1);
                        return 1;
                }
                lvl = (int)me->query_skill("force", 1);
                if(lvl > 100 && lvl < 200)
                {
                        message_vision("$N躺上了寒玉床，開始潛運內功，使內息遍行大小周天。\n", me);
                        if (random(10) > 6)
                        {
                                message_vision("$N調息完畢，只覺得精神健旺，內息充沛欲奔騰而出。\n", me);
                                if ((lvl*lvl*lvl/10) < exp)
                                {
                                        me->improve_skill("force", random(lvl));
                                }
                                me->receive_damage("qi", random(lvl/3));
                        }
                        else
                                message_vision("$N調息完畢，站起身來，提了提內力，好象沒什麼長進。\n", me);
                }
                else
                        message_vision("$N躺上寒玉床，只覺得冰冷刺骨，‘啊’的一聲狼狽不堪地跳了起來。\n", me);
                me->start_busy(1);
                return 1;
        }
        else return notify_fail("你要坐在哪裡？\n");
}

int do_liao(string arg)
{
        object me = this_player();

        if (me->is_fighting() || me->is_busy())
                return notify_fail("你正忙著呢。\n");
        if( query("eff_qi", me) >= query("max_qi", me) )
                return notify_fail("你現在身上沒有受到任何傷害！\n");
        if ( (int)me->query_condition("bed_poison") > 0 )
        {
                me->receive_wound("qi", 10);
                message_vision(HIR "$N突然只覺一陣奇寒侵入身體，想是兩次療傷時隔太短，身子尚未復原之故。\n"NOR, me);
                me->unconcious();
                return 1;
        }
        if (arg == "bed" || arg == "chuang")
        {
                message_vision(HIY"$N爬上寒玉床，要借千年寒玉療傷。\n"NOR, me);
                if (me->query_skill("yunv-xinfa", 1) < 40)
                        return notify_fail("寒玉床療傷需以純熟的玉女心經內功相輔，否則無法外療。\n");
                set("eff_qi",query("max_qi",  me), me);
                me->apply_condition("bed_poison", 25);
                return 1;
        }
        return notify_fail("你要在哪裡療傷？\n");
}