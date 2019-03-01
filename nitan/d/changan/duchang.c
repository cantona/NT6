//Room: duchang.c

#include <ansi.h>

inherit ROOM;

int room_status = 0;
int *big = allocate(2);
int *res = allocate(2);

int random2 (int i)
{
        return (random(i)+uptime()) % i;
}

mapping gutous = ([ 
        "tc" : "頭彩",
        "sd" : "雙對",
        "qx" : "七星",
        "sx" : "散星",
 ]); 

void create()
{
        set("short", "賭場");
        set("long", @LONG
大廳裡擺滿大大小小的賭桌，只要能說出名的賭具，這裡都有。
進來這裡你首先聽到的就是少女們吃吃的笑聲和男人們的吹牛聲，擲
骰子聲……在這裡，你幾乎就可以聽到世上所有不規矩的聲音。牆上
掛著一塊匾（ｓｉｇｎ）。
LONG );
        set("exits", ([ /* sizeof() == 1 */
                "south" : "/d/changan/qixiang3",
        ]));
        set("item_desc", ([
                "sign": @TEXT
賭骰子方法:
bet <kind> <amount> <money> 

只收現銀，概不賒欠。

kind:
    頭彩 <tc>（骰數由每次開盤前確定）      ：一贏三十六
    雙對 <sd>（兩骰號相同，且為偶數）      ：一贏十二
    七星 <qx>（兩骰之和為七）              ：一贏六
    散星 <sx>（兩骰之和為三，五，九，十一）：一贏三
TEXT
        ]));

        set("objects", ([
                "/d/changan/npc/zhuangjia" : 1,
        ]));

        set("no_fight", 1);
        set("coor/x", -10730);
	set("coor/y", 1970);
	set("coor/z", 0);
	setup();
}
void init()
{
        if (! interactive(this_player()))
                return;

        add_action("do_bet", "bet");

        if (room_status > 0)
                return;

        remove_call_out("gamble_prepare");
        remove_call_out("gamble_start");
        remove_call_out("gamble_perform");
        remove_call_out("gamble_finish");
        call_out ("gamble_prepare", 2);
        room_status = 1;
}

int do_bet(string arg)
{
        object me = this_player();
        string what;
        int amount;
        string money;
        object ob;
        object zj;

        if (! objectp(zj = present("zhuang jia", this_object())))
                return notify_fail("莊家都沒有，你要和誰賭？\n");

        if (! living(zj))
                return notify_fail("你還是等莊家醒了再說吧！\n");

        if (! arg || sscanf (arg,"%s %d %s", what, amount, money) != 3)
                return notify_fail("請使用： bet <押骰種類> <數目> <貨幣>\n");

        if (what != "tc" &&
            what != "sd" &&
            what != "qx" &&
            what != "sx")
                return notify_fail("你要押哪一種骰？\n");

        ob = present(money + "_money", me);
        if (! ob)
                return notify_fail("你身上沒有這種錢。\n");

        if (amount < 1)
                return notify_fail("請多押一些錢。\n");

        if (amount > ob->query_amount())
                return notify_fail("你身上的錢不夠押。\n");

        if (amount > 10)
                return notify_fail("莊家喊道：怎麼零零碎碎的那麼多？"
                                   "換成整票再來下注！\n");

        if( query("base_value", ob)*amount>100000 )
                return notify_fail("賭注最大十兩黃金。\n");

        if( query_temp("gamble_bet/amount", me)>0 )
                return notify_fail("你已經押過了。\n");

        if (room_status > 1)
                return notify_fail("現在正在賭呢，稍等片刻。\n");

        set_temp("gamble_bet/kind", what, me);
        set_temp("gamble_bet/amount", amount, me);
        set_temp("gamble_bet/money", money, me);
        message_vision(sprintf("$N拿出%s%s%s，押在%s上。\n",
                               chinese_number(amount),
                               query("base_unit", ob),
                               query("name", ob),
                               gutous[what]),
                               me);
        if (amount == ob->query_amount())
                destruct (ob);
        else
                ob->add_amount(-amount);

        if (! arrayp(query_temp("better")))
                set_temp("better", ({ me }));
        else
                set_temp("better", query_temp("better")+({ me }));

        return 1;
}

int valid_leave(object me, string dir)
{
        if (dir == "south")
        {
                if( query_temp("gamble_bet/amount", me)>0 )
                message_vision ("$N扔下押骰的錢，不要了。\n",me);
                delete_temp("gamble_bet", me);
        }
        return ::valid_leave(me,dir);
}

void display_bet(object room, int i)
{
        string str;
        switch (i)
        {
        case 1:
                str = 
"┌───┐\n"+
"│　　　│\n"+
"│　●　│\n"+
"│　　　│\n"+
"└───┘\n";

                break;
        case 2:
                str = 
"┌───┐\n"+
"│　　　│\n"+
"│●　●│\n"+
"│　　　│\n"+
"└───┘\n";
                break;
        case 3:
                str =
"┌───┐\n"+
"│●　　│\n"+
"│　●　│\n"+
"│　　●│\n"+
"└───┘\n";
                break;
        case 4:
                str = 
"┌───┐\n"+
"│●　●│\n"+
"│　　　│\n"+
"│●　●│\n"+
"└───┘\n";
                break;
        case 5:
                str =
"┌───┐\n"+
"│●　●│\n"+
"│　●　│\n"+
"│●　●│\n"+
"└───┘\n";
                break;
        case 6:
                str = 
"┌───┐\n"+
"│●　●│\n"+
"│●　●│\n"+
"│●　●│\n"+
"└───┘\n";
                break;
        }
        tell_room(room,str);
}

int rdm()
{
        return random2(6) + 1;
}

void gamble_prepare()
{
        object room = this_object();
        tell_room (room,"莊家唱道：新開盤！預叫頭彩！\n");
        tell_room (room,"莊家將兩枚玉骰往銀盤中一撒。\n");
        big[0] = rdm();
        big[1] = rdm();
// keep two numbers different for a probability == 1/36
        while (big[0] == big[1])
        {
                reset_eval_cost();
                big[1] = rdm();
        }
        display_bet(room,big[0]);
        display_bet(room,big[1]);
        tell_room(room,"莊家叫道：頭彩骰號"+chinese_number(big[0])+
        chinese_number(big[1])+"！\n");
        tell_room(room, "接著莊家麻利地順手將玉骰從盤中收回：現在開盤押錢！\n");
        room_status = 1;
        call_out("gamble_start",24);
        delete_temp("better");
}
 
void gamble_start()
{
        object room = this_object();
        tell_room (room,"莊家喊聲：封盤停押！\n");
        tell_room (room,"又補道：本盤頭彩骰號是"+chinese_number(big[0])+
        chinese_number(big[1])+"。\n");
        tell_room (room,"然後將兩枚玉骰扔進兩個金盅，一手持一盅搖將起來。\n");
        room_status = 2;
        call_out("gamble_perform", 6, 0);
        call_out("gamble_perform", 12, 1);
        call_out("gamble_finish", 18);
}
void gamble_perform (int i)
{
        object room = this_object();
        tell_room(room, " 金盅倒扣在銀盤上，玉骰滾了出來。\n");
        res[i] = rdm();
        display_bet (room,res[i]);
}

void player_wins(object who, int total)
{
        object money = new("/clone/money/" +
                           query_temp("gamble_bet/money", who));
        int amount=query_temp("gamble_bet/amount", who);
        total = total * amount;
        money->set_amount(total);
        message_vision(sprintf("$N贏了%s%s%s！\n",
                       chinese_number(total),
                       query("base_unit", money),
                       query("name", money)),
                       who);
        money->move(who);
}

void player_loses(object who, int total)
{
        object money = new("/clone/money/" +
                           query_temp("gamble_bet/money", who));
        total=query_temp("gamble_bet/amount", who);
        message_vision(sprintf("莊家將$N押在銀盤中的%s%s%s收走。\n",
                               chinese_number(total),
                               query("base_unit", money),
                               query("name", money)),
                               who);
        destruct(money);
}

void gamble_finish()
{
        string win;
        int total, i;
        object room = this_object();
        object *list;

        if (res[0]==big[0] && res[1]==big[1])
        {
                total = 36;
                win = "tc";
        } else
        if (res[0]==res[1] && (res[0]/2*2 == res[0]))
        {
                total = 12;
                win = "sd";
        } else 
        {
                int r = res[0]+res[1];
                if (r==7)
                {
                        total = 6;
                        win = "qx";
                } else if (r==3 || r==5 || r==9 || r==11) 
                {
                        total = 3;
                        win = "sx";
                } else
                {
                        total = 0;
                        win = "none of them";
                }
        }
        if (total == 0)
                tell_room(room, "莊家叫道：" + chinese_number(res[0])+
                                chinese_number(res[1])+"……空盤！\n");
        else
                tell_room(room, "莊家叫道："+chinese_number(res[0])+
                                chinese_number(res[1])+"……" +
                                               gutous [win]+"！\n");
        list = query_temp("better");
        i = sizeof(list);
        while (i--)
        {
                if (! objectp(list[i]))
                        continue;

                if (environment(list[i]) == room)
                {
                        if( query_temp("gamble_bet/kind", list[i]) == win )
                                player_wins(list[i],total); else
                        if( query_temp("gamble_bet/kind", list[i]) )
                                player_loses(list[i],total);
                }

                delete_temp("gamble_bet", list[i]);
        }
        tell_room (room,"\n");
        call_out ("gamble_prepare",5);
}