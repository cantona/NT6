// Room: /d/huashan/sgyhole.c

inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "山洞");
        set("long", @LONG
這是一個毫不起眼的山洞，但是裏面的石壁上卻畫滿了五嶽劍派
所有已經失傳的精妙絕招。花崗巖石壁(wall)上很多小人，全是用利
器刻制，想見當初運力之人內力十分深厚。
LONG );
        set("exits", ([ /* sizeof() == 4 */
            "southup"   : __DIR__"sgyhole",
            "northdown" : __DIR__"sgyhole3"
        ]));
        set("item_desc", ([ 
            "wall" : @TEXT

       o    | o      o    \ o      o      o     <o     <o>
    --^|\    ^|^  --v|^    v|v    |/v   \|X|    \|      |
       /\     >\    /<      >\    /<      >\    /<      >\

       o>     o      o      o      o      o      o      o
       \ __   x     </     <|>    </>    <\>    <)>     |\__
      /<      >\    /<      >\    /<      >\     >>     L
TEXT
        ]));

        setup();
}
void init()
{
        add_action("do_mianbi", "mianbi");
        add_action("do_think", "think");
}

int do_think(string msg)
{
    object me = this_player();

    string where, witch;
    
    if (! msg)return notify_fail("什麼？\n");

    if (sscanf(msg, "%s from %s", witch, where) != 2)
          return notify_fail("幹什麼？\n");

    if (witch != "萬劍焚雲")
          return notify_fail("你想參悟什麼？\n");

    if (where != "wall")
          return notify_fail("這裏沒什麼給你參悟的啊！\n");

    if (me->is_busy())
          return notify_fail("你現在正忙着呢。\n");

    if (me->is_fighting())
          return notify_fail("你在戰鬥哦？！小心，來了！！！\n");
   
    if( query("can_perform/zhurong-jian/wan", me) )
          return notify_fail("你不是已經會了嗎？\n");

    if ((int)me->query_skill("zhurong-jian", 1) < 140)
          return notify_fail("你祝融劍法不夠嫻熟，無法貫通石壁上的絕學！\n");

    if ((int)me->query_skill("force") < 220)
          return notify_fail("你內功修為不夠，無法貫通石壁上的絕學！\n");

    if( query("max_neili", me)<1200 )
          return notify_fail("你的內力修為不足，無法貫通石壁上的絕學！\n");

    if( query("jing", me)<100 )
          return notify_fail("你的精力無法集中，無法領悟石壁上的絕學！\n");

    me->start_busy(4 + random(4));

    if (random(10) != 1)   
          return notify_fail("你仔細參悟石壁上的絕學，若有所悟，但是始終無法融會貫通！\n");

    me->receive_damage("jing", 95);

    me->start_busy(2 + random(4));

    write(HIM "猛然間，你一聲長嘯，胸中豁然貫通，再無疑慮。\n" NOR);
    write(HIC "你終於通曉了絕學「萬劍焚雲」。\n" NOR);

    set("can_perform/zhurong-jian/wan", 1, me);

    if (me->can_improve_skill("sword"))
            me->improve_skill("sword", 1500000);
    if (me->can_improve_skill("zhurong-jian"))
            me->improve_skill("zhurong-jian", 1500000);
    if (me->can_improve_skill("martial-cognize"))
            me->improve_skill("martial-cognize", 1500000);

    return 1;    
}

int do_mianbi()
{
        object ob;
        int c_skill;

        ob = this_player();

        c_skill = (int)ob->query_skill("zhurong-jian", 1);
        if (ob->query_skill("sword", 1) <= c_skill)
        {
                write("你對劍法的瞭解顯然太低，無法領悟石壁內容。\n", ob);
                return 1; 
        }

        if (! ob->can_improve_skill("zhurong-jian"))
        {
                write("$N的實戰經驗不足，無法領悟石壁內容。\n");
                return 1; 
        }

        if( query("jing", ob)<40 )
        {
                write("你精力不能集中，現在無法領悟石壁內容。\n");
                return 1; 
        }

        if (c_skill >= 10)
        {
                write("你覺得石壁內容太膚淺了。\n");
                return 1;
        }

        message_vision("$N面對着石壁趺坐靜思，良久，對「祝融劍法」"
                        "似有所悟。\n", ob);
        ob->improve_skill("zhurong-jian",1+random(query("int", ob)));
        ob->receive_damage("jing", 35);
        ob->start_busy(2);
        return 1;
}