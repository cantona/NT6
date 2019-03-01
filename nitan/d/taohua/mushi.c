inherit ROOM;

void create()
{
  
        set("short", "墓室");
        set("long", @LONG
這是一間寬敞的墓室。墓室頂上有一顆特別大的明珠閃閃
發光。中央放著一副玉棺，周圍則堆放了無數的奇珍異玩。有
張供桌擺在玉前,桌上放著盤子(panzi).墓室對面掛這幅青年少
婦的畫像。畫像上的少婦巧笑嫣然，和慘白的玉棺及碧油油的
珠光形成了一幅奇詭的畫面。
LONG);
        set("exits", ([
                "up" : __DIR__"mudao",
        ]));

        if (random(1000) > 998)
                set("objects", ([
                        "/clone/money/gold" : 10,
                        "/clone/fam/item/haoyue" : 1,
                        "/clone/fam/etc/lv5b" : 1,
                ]));
        else
        if (random(100) > 98)
                set("objects", ([
                        "/clone/money/gold" : 5,
                        "/clone/fam/etc/lv5a" : 1,
                ]));
        else
        if (random(100) > 97)
                set("objects", ([
                        "/clone/money/gold" : 5,
                        "/clone/fam/etc/lv5d" : 1,
                ]));
        else
        if (random(10) > 8)
                set("objects", ([
                        "/clone/money/gold" : 1,
                ]));

        set("item_desc", ([
                "panzi" : @TEXT
    你仔細看了一下盤子，這是一個玉盤，裡面放著數顆晶瑩的
    明珠。這些明珠似乎可以拿出來(pick zhu)。
TEXT
        ]) );

        setup();
}

void init()
{
        object me = this_player();
        add_action("do_pick","pick");
        set_temp("taohua/墓室", 0, me);
}
void reset()
{
        ::reset();
        set("pick_available" , 6);
}
int do_pick(string arg)
{
        object *obs;
        object me,obj,killer;
        int count;

        me = this_player();
        if( !arg || arg!="zhu" )
                return notify_fail("你要拿什麼? \n");
                
        if (me->is_busy()) return notify_fail("你正在忙著呢！\n");

        if ( query("pick_available") )
        {
                message_vision("$N從盤子裡拿出來一顆明珠。\n",this_player() );
                obj = new ("/d/taohua/obj/mingzhu");
                obj->move(me);
                addn("pick_available", -1);
                me->start_busy(3);
                if( query_temp("taohua/墓室", me))return 1;
                killer = new ("/d/taohua/npc/shoumu") ;
                obs = all_inventory(this_object());        
                count = 0;
                foreach(object ob in obs) {
                        if(ob && ob->id("shou mu"))
                                count++;
                }
                if (count < 6)
                {
                        message_vision("\n突然墓室中打開了一道暗門，從裡面走出一個守墓家奴。\n"
                                       "對$N喝道：賊子敢爾！連夫人的東西你也敢動！\n", me);
   
                        killer->move(environment(me));
                        killer->kill_ob(me);
                        set_temp("taohua/墓室", 1, me);
                }
       }
       return 1;
}

