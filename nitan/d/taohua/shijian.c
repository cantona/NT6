// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <room.h>
#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "試劍亭");
        set("long", @LONG
這座小亭孤零零立於水中，整座亭均以紅松搭成，四面池水縈迴，清
幽古樸兼而有之。亭內掛着一副對聯(duilian)，均以狂草寫成，字裏行
間大有俯仰自得，不可一世之意。
LONG );

        set("item_desc", ([
        "duilian" : " \n
※※※※※※※※※※※※※※※
※※    桃          碧    ※※
※※                      ※※
※※    花          海    ※※
※※                      ※※
※※    影          潮    ※※
※※                      ※※
※※    落          生    ※※
※※                      ※※
※※    飛          按    ※※
※※                      ※※
※※    神          玉    ※※
※※                      ※※
※※    劍          簫    ※※
※※※※※※※※※※※※※※※
\n", 
        ]));

        set("cost", 2);
        set("outdoors", "taohua");

        setup();
}

void init()
{
        add_action("do_jump", "fly");
        add_action("do_lian", "lian");
}

int do_jump(string arg)
{
        object me = this_player();

             if ( !arg || arg != "back" ) 
             return notify_fail( "什麼？\n");

        message_vision("$N縱身跳回聽魚石。\n\n", me);
        me->move(__DIR__"tingyu");
        message("vision", me->name() + "縱身由試劍亭裏跳了過來。\n",environment(me), ({me}) );

        return 1;
}

int do_lian(string arg)
{
        object me;
        string skillarg, skillname, skillzhao, multiple;
        int times, shijian, skill, skill_basic, qi;

        me = this_player();
        seteuid(getuid());

        if( query_temp("cursed", me) )
                return notify_fail("什麼？\n");

        if (me->is_busy())
                return notify_fail("你現在正忙着呢。\n");

        if( me->is_fighting() )
                return notify_fail("你已經在戰鬥中了，學一點實戰經驗吧。\n");

        if( arg=="parry" )
                return notify_fail("你不能通過練習招架來提高這項技能。\n");

        if( !arg ) 
                return notify_fail("你要幹什麼？\n");

        if(sscanf(arg, "%s %d", skillarg, times)!=2 )
                skillarg = arg;
        
        if( skillarg != "sword" ) return notify_fail("什麼？\n");
        
        if( skillarg=="parry" )
                return notify_fail("你不能通過練習招架來提高這項技能。\n");

        if(!times || times == 0) {
                times = 1;
                multiple="";
        }
        else        multiple="反覆";
        shijian = times;
        
        if(!stringp(skillname = me->query_skill_mapped(skillarg)) )
                return notify_fail("你只能練習用 enable 指定的特殊技能。\n");

        skill_basic = me->query_skill(skillarg, 1);
        skill = me->query_skill(skillname, 1);

        if( skill < 1 )
                return notify_fail("你好像還沒有學過這項技能吧？最好先去請教別人。\n");
        if( skill_basic < 1 )
                return notify_fail("你對這方面的技能還是一竅不通，最好從先從基本學起。\n");
        if( skill_basic/2 <= skill/3 )
                return notify_fail("你的基本功火候未到，必須先打好基礎才能繼續提高。\n");

        notify_fail("你現在不能練習這項技能。\n");
        if( !SKILL_D(skillname)->valid_learn(me) ) return 0;

        notify_fail("你試着練習" + to_chinese(skillname) + "，但是並沒有任何進步。\n");

        for(times; times > 0; times--) {
                if( SKILL_D(skillname)->practice_skill(me) )
                        me->improve_skill(skillname, skill_basic/3+1, skill_basic > skill? 0: 1);
                else return 0;
        }

        if(skillzhao = SKILL_D(skillname)->query_skill_name(me->query_skill(skillname, 1))) {
                message_vision( HIY"$N" + multiple + "練習著" + to_chinese(skillname) + "中的" 
                                + skillzhao + "這一招，看來有些進步。\n"NOR, me);
                if( me->query_skill("bibo-shengong", 1) > 80 )
                        addn("shijian", shijian, me);
        } 
        else {
                message_vision( HIY"$N" + multiple + "練習著" + to_chinese(skillname) + "，看來有些進步。\n"NOR, me);
                if( me->query_skill("bibo-shengong", 1) > 80 )
                        addn("shijian", shijian, me);
        }

        return 1;
}
