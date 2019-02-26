// Room: /city/daxiao.c

inherit ROOM;

int sos(int,int);
void fresh(object ob);
void create()
{
        set("short", "賭場");
        set("long", @LONG
這裏是賭(gamble)「大小」的房間，牆上掛着一塊牌子(paizi)。
LONG );
        set("item_desc", ([
                "paizi" :
"本賭場新開放賭「大小」正處於測試階段。\n"
"「大小」賭法：\n"
"共用三粒色子撒在一隻碗裏，色子點數總和：\n"
"       四 至 十 為「小」，\n"
"       十一 至 十七 為「大」，\n"
"       三粒色子點數相同，則大小通吃。\n"
"\n開大賠大，開小賠小，一賠一。\n"
"\n本賭場接受各種貨幣為賭注。\n"
"\n賭注為五十到五百。\n",
        ]));
        set("exits", ([
                "east" : "/d/city/duchang",
                "north" : "/d/city/bocai",
        ]));
//	set("no_clean_up", 0);
        set("no_fight", "1");
	set("coor/x", -20);
	set("coor/y", -10);
	set("coor/z", 0);
	setup();
}

void init()
{
        add_action("do_gamble", "gamble");
}

int do_gamble(string arg)
{
        int a,b,c;
        int wager, skill, lpoint, tpoint;
        string wtype1, wtype2, wtype0, status;
        object mtype, me;
        mapping lrn;

        int min, max;
        min = 500;
        max = 500000;

        me = this_player();

        if( query_temp("casino/mark", me) )
                return notify_fail("你這麼着急啊? 還是再多休息一會兒吧 -:)\n");

        if (!arg || sscanf(arg, "%s %s %s %d", wtype0, wtype1, wtype2, wager) !=4)
                return notify_fail("gamble big|small money|skill <type> <amount>\n"
                                   "eg. gamble big money silver 3\n");

        if (wtype1 == "money")
        {
                mtype = present(wtype2 + "_money", me);
                if( !mtype)          return notify_fail("你身上沒有這種貨幣。\n");
                if( wager < 1 )        return notify_fail("你要壓多少啊?\n");
                if( (int)mtype->query_amount() < wager)
                        return notify_fail("你身上沒有那麼多"+query("name", mtype)+"。\n");
                if( wager*(query("base_value", mtype))<min || 
                    wager*(query("base_value", mtype))>max )
                        return notify_fail("你的賭注不在限額之內!\n"
                        "這裏的限額是" + chinese_number(min) + "至" + chinese_number(max) + "。\n");
        }
        else    return notify_fail("本賭場不接受這種賭注。\n");

        if ( (wtype0 != "big") && (wtype0 != "small") )
                return notify_fail("你要賭大還是賭小?\n");

        set_temp("gamb_t", (query_temp("gamb_t", me)+1), me);
        if( query_temp("gamb_t", me)>50 )
        {
                call_out("fresh", 300, me);
                set_temp("casino/mark", 1, me);
                return notify_fail(
"這位" + RANK_D->query_respect(me) + "，你已經賭了很久了，還是先休息一會兒吧。\n");
        }

        a = random(6) + 1;
        b = random(6) + 1;
        c = random(6) + 1;

        message_vision("開：" + a + "   " + b + "   " + c + "   ，", me);

        if ((a == b) && (b == c) )
//              message_vision("開：" + a + " " + b + " " + c " ,大小通殺。\n", me);
                message_vision("大小通殺。\n", me);
        else if ( (a+b+c) > 10 )
//              message_vision("開：" + a + " " + b + " " + c " ,吃小賠大。\n", me);
                message_vision("吃小賠大。\n",me);
        else if ( (a+b+c) < 11 )
//              message_vision("開：" + a + " " + b + " " + c " ,吃大賠小。\n", me);
                message_vision("吃大賠小。\n",me);

        if ( ( (a == b) && (b == c) ) ||
             ( (a+b+c) > 10 && (wtype0 == "small") ) ||
             ( (a+b+c) < 11 && (wtype0 == "big") ) )
                status = "lose";

        if (wtype1 == "money")
        {
                if ( status == "lose") {
        message_vision(query("name", me)+"輸了"+chinese_number(wager)+
query("base_unit", mtype)+query("name", mtype)+"。\n",me);
                        mtype->set_amount((int)mtype->query_amount() - wager);
                        mtype->move(me);
                }
                else {
        message_vision(query("name", me)+"贏了"+chinese_number(wager)+
query("base_unit", mtype)+query("name", mtype)+"。\n",me);
                        mtype->set_amount((int)mtype->query_amount() + wager);
                        mtype->move(me);
                }
        }
        else if (wtype1 == "skill")
        {
                if ( status == "lose") {
        message_vision(query("name", me)+"輸了"+chinese_number(wager)+
"點" + to_chinese(wtype2) + "的功力。\n", me);
                        wager -= lpoint;
                        while (wager > 0)
                        {
                           wager -= skill*skill;
                           skill -= 1;
                        }
                        wager *= -1;
                        if (wager > lpoint) wager -= lpoint;
                        else wager += (lpoint*-1);
                }
                else {
        message_vision(query("name", me)+"贏了"+chinese_number(wager)+
"點" + to_chinese(wtype2) + "的功力。\n", me);
                        wager += lpoint;
                        while (wager >= (skill+1)*(skill+1))
                        {
                          skill += 1;
                          wager -= skill*skill;
                        }
                        wager -= lpoint;
                }
                me->set_skill(wtype2, skill);
                me->improve_skill(wtype2, wager);
        }
        return 1;
}

void fresh(object ob)
{
	if (! objectp(ob)) return;
        delete_temp("gamb_t", ob);
        delete_temp("casino/mark", ob);
}

int sos(int lower, int upper)
{
        int x,y;
        x = 0;

        while (lower <= upper)
        {
                y = lower*lower;
                x += y;
                lower++;
        }
        return x;
}