#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "後山山洞");
        set("long", @LONG
這裡是全真教開山祖師王重陽真人靜修的山洞。洞雖不大但卻布
置得很是雅致，便似大戶人家的客廳一樣。洞壁上懸掛著副畫(hua)，
桌椅茶幾都很精致。
LONG );
        set("exits", ([
                "out" : __DIR__"xiaolu12",
        ]));
        set("item_desc", ([
                "hua": YEL "\n畫中是一個中年道士的背影，看不出什麼相"
                       "貌，畫中道人一手\n指著天，畫角題著「" HIR "活"
                       "死人像" NOR + YEL "」幾個字。\n" NOR,
        ]) );

        set("objects", ([
                CLASS_D("quanzhen") + "/wang" : 1,
        ]));
        set("coor/x", -2670);
        set("coor/y", 130);
        set("coor/z", 150);
        setup();
}

void init()
{
        add_action("do_ketou", "ketou");
}


int do_ketou(string arg)
{
        object paper, me = this_player();
        int level1, level2, level3;

        if (me->is_busy()) return notify_fail("你正在忙著呢。\n");

        message_vision("$N恭恭敬敬地在神案前的團蒲上跪了下來，對著神位磕了三個響頭。\n", me);
        // me->receive_damage("qi", random(30));
        me->start_busy(1);

        if( query("qi", me) <= 50 )
                write("你只覺得腦子有些昏昏沉沉的。\n");
        if( query("qi", me) <= 30 )
                write("你覺得天旋地轉，似乎馬上便要暈去。\n");

        if( !(query("family/family_name", me) == "全真教") )
                return 1;

        level1 = me->query_skill("xiantian-gong", 1);
        level2 = me->query_skill("taoism", 1);
        level3 = me->query_skill("quanzhen-jian", 1);

        if( level1>300 && level2>300 && level3>300 && random(50) == 1 && !query_temp("quanzhen/shentong_paper", me) )
        {
                paper=new(__DIR__"obj/shentong_paper");
                if ( !paper ) return 1;

                addn("paper_count", -1);
                set_temp("quanzhen/shentong_paper", 1, me);

                message_vision(HIG"$N在團蒲上重重地一磕，團蒲的邊上忽然裂了開來，露出一小段絲絹。\n"NOR,me);
                write("你仔細的將絲絹抽出一看，上面密密麻麻的記載了練功心法，似乎與先天\n");
                write("功一脈相承，但卻更加深奧。\n");
                message_vision("$N連忙將密笈收好。\n",me);
                paper->move(me, 1);
        }

        return 1;
}