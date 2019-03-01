inherit ROOM;

void create ()
{
        set ("short", "貨棧");
        set("long", @LONG
這是一家生意興隆貨棧。貨棧門口車來車往，幾個活計在忙忙碌
碌地工作著，地上放著一些剛剛運來的貨物。屋裡面整齊的排列著幾
排貨架，貨架上堆著各式各樣的雜貨，有一個掌櫃模樣的人坐在櫃台
後面笑容可鞠地招呼著客人。貨棧的牆上貼著一張破舊的告示(gaosh
i)。
LONG );
        set("item_desc", (["gaoshi" : "現在正緊缺人手，急需雇傭一批短工來幹活。
work        開始工作。
", ]));
        set("exits", 
        ([ //sizeof() == 1
                "west" : "/d/changan/yongtai-dadao1",
        ]));
        set("objects", 
        ([ //sizeof() == 1
                "/d/changan/npc/liang" : 1,
        ]));
        set("no_fight", 0);
        set("coor/x", -10750);
	set("coor/y", 1950);
	set("coor/z", 0);
	setup();
}

void init()
{
        add_action("do_work", "work");
}

int do_work(string arg)
{
        object ob;
        object me;
        me = this_player();
        if( !query_temp("working_in_huozhan", me) )
        {
                if( query("qi", me)<25 || 
                    query("jing", me)<25 )
                        return notify_fail("你可是累壞了，幹不動了。\n");

                message_vision("$N從車上卸下一袋袋的大米，又"
                               "壘在牆邊，累的腰酸腿疼！\n",me);
                me->receive_damage("qi", 20);
                me->receive_damage("jing", 20);
                ob = new("/clone/money/coin");
                ob->set_amount(10);
                ob->move(me);
                message_vision("樑老板笑眯眯地對$N說：辛苦啦，這是你的工錢。\n",me);
                set_temp("working_in_huozhan", 1, me);
                remove_call_out ("reset_work");
                call_out ("reset_work", 2 + random(3), me);
        } else
        {
                message_vision("樑老板趕緊把$N扶起來：先歇一會兒。\n",me);
        }
        return 1;
}

void reset_work(object me)
{
        delete_temp("working_in_huozhan", me);
}