// Room: /d/jiaxing/diaoyu.c
// Last Modified by winder on Nov. 17 2000

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "釣魚亭");
        set("long", @LONG
湖邊一座石砌的精緻小亭。極目遠眺，碧水連天，波光瀲灩。近處
游魚唼喋，漾起一圈圈漣漪。
LONG
        );
        set("outdoors", "jiaxing");
        set("no_fight",1);
        set("no_steal",1);
        set("no_sleep",1);
        set("no_beg",1);
        set("fish",200);
        set_temp("char_count",2);

        set("exits", ([
                "south" :  __DIR__"nanhu",
        ]));
	set("coor/x", 1200);
	set("coor/y", -1760);
	set("coor/z", 0);
	setup();
}

void init()

{
        add_action("do_diao","diao");
        add_action("do_ban","dazuo");
        add_action("do_ban","tuna");
        add_action("do_ban","du");
        add_action("do_ban","study");
        add_action("do_ban","exercise");
        add_action("do_shuohua","say");
        add_action("do_shuohua","whisper");
        add_action("do_shuohua","reply");
        add_action("do_shuohua","tell");

}
int do_shuohua()
{
        write ("別説話！別把魚嚇走了！\n");
        return 1;
}
int do_ban()
{
        write ("別妨礙人家釣魚！\n");
        return 1;
}
int do_diao(string arg)
{
        object me = this_player();
        int bonus,exp,pot;
        object mon;

//        if((int)(me->query("combat_exp")) > 15000)
//              return notify_fail("你的經驗太高了，這裏不適合你。\n");
        if (query_temp("char_count") < 1)
              return notify_fail("這裏太擁擠了。沒處下鈎。回頭再來吧。\n");
        if (query("fish") < 1)
              return notify_fail("這裏的魚釣得差不多了，半天看不到魚影。回頭再來吧。\n");
        if (!arg)
              return notify_fail("你要釣什麼？\n");
        if (arg != "fish" && arg != "魚")
              return notify_fail("你可不是姜太公，沒指望釣到別的。\n");
        if( query_temp("fishing", me) )
              return notify_fail("你已經在釣魚了。\n");
        if( (query("qi", me))<16 )
              return notify_fail("你已經太累了，還是休息一下吧。\n");
        message_vision("
$N將魚餌掛在鈎上，輕輕一蕩魚竿，將魚餌扔進水裏。\n\n",me);
        set_temp("fishing", 1, me);
        addn_temp("char_count", -1);
        addn("fish", -1);
        addn("qi", -10, me);

        call_out("del_fishing", 6, me, mon, bonus, exp, pot);
        return 1;
}

void del_fishing(object me, object mon, int bonus, int exp, int pot)
{
        delete_temp("fishing", me);
        addn_temp("char_count", 1);
        if (random (10) < 2)
        {
                message_vision(HIY"
只見浮漂微微一動，$N趕緊用力提竿，提上來一看，白白的魚鈎上什麼也
沒有。唉，太心急了，沒等魚兒吃鈎就早早提竿了。\n"NOR,me);
                me->start_busy(3);
                return ;
        }
        else
        {
                exp = 2 + random(6);
                pot = 1 + random(3);
                message_vision(HIW"
浮漂在動了，$N屏息靜氣，死死盯住浮漂，不敢有絲毫大意，只見浮漂猛
地往下一沉，$N抓住時機一提竿，$N釣起了一條" + chinese_number(exp) + "斤重的魚。\n\n"NOR 
"$N身旁突然鑽出一個魚販，一把將$N手中的魚奪走，順手扔給$N一錠銀子。\n",me);
//        bonus = (int) me->query("combat_exp");
//        bonus += exp;
//        me->set("combat_exp", bonus);
//        bonus = (int) me->query("potential");
//        bonus += exp;
//        me->set("potential", bonus);
                mon = new("/clone/money/silver");
                mon->set_amount(exp);
                mon->move(me);
                me->start_busy(3);

                return;
        }
}