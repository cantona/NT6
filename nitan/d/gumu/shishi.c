// shishi.c 石室
// Java Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "石室");
        set("long", @LONG
這是一間石室，室中點著燈火。石室奇小，兩人站著，轉身就很不
容易，室頂又矮，伸長手臂，幾可碰到。在石室角落裏有一隻不大的布
袋(budai) ，繩索綁着袋口，蠕蠕而動，不知道是什麼東西。
LONG );
        set("exits", ([
                "north" : __DIR__"mudao16",
        ]));
        set("item_desc", ([
                "budai": "一隻舊布袋，裏面還蠕蠕而動着。\n"
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3200);
        set("coor/y", -60);
        set("coor/z", 90);
        setup();
}

void init()
{
        add_action("do_open", "dakai");
        add_action("do_open", "open");
        add_action("do_zhua", "zhua");
        add_action("do_zhua", "catch");
}

int do_open(string arg)
{
        object obj, me=this_player();
        if( !arg || arg != "budai" )
        {
                return notify_fail("你要打開什麼？\n");
        }
        if( query("opened", this_object()) )
                return notify_fail("布袋已被打開了。裏面啥也沒有了。\n");
        message_vision("$N俯身在石室角落裏提起一隻布袋，解開縛在袋口的繩索，倒轉袋子一抖，飛出來三隻麻雀。\n",me) ;
        set("opened", 1, this_object());
        obj=new(__DIR__"npc/maque");
        obj->move(this_object());
        obj=new(__DIR__"npc/maque");
        obj->move(this_object());
        obj=new(__DIR__"npc/maque");
        obj->move(this_object());
        return 1;
}

int do_zhua(string arg)
{
        object me=this_player();
        int c_exp, c_skill;

        c_exp=query("combat_exp", me);
        c_skill=(int)me->query_skill("yunv-shenfa", 1);
        if( !arg || arg != "ma que" ) return notify_fail("你要抓什麼？\n");
        if( !objectp(present("ma que", environment(me))))
                return notify_fail("這裏沒有麻雀吧？\n");
        if( query("qi", me)<30 )
                return notify_fail("你覺得太累了，不如歇會吧？\n");
        if( me->query_skill("yunv-xinfa", 1) < 10)
        {
                message_vision("$N的玉女心法不夠嫻熟，抓麻雀也沒用。\n", me) ;
                return 1;
        }
        me->receive_damage("qi", random(30));
        if( random((int)c_skill/10) + 1 < 2)
        {
                message_vision("$N撲過去就抓。可是麻雀靈便異常，東飛西撲，$N氣喘吁吁，累得滿頭大汗，別説捉到，連羽毛也碰不到一根。\n", me);
                return 1;
        }
        message_vision("$N輕輕縱起，伸手處，正好逮住一隻麻雀。\n", me);
        if ((random(10)>3) && c_skill*c_skill*c_skill/10<c_exp && c_skill<101)
        {
                me->improve_skill("yunv-shenfa",random(query("dex", me)));
                tell_object(me,"你的玉女身法進步了！\n");
        }
        return 1;
}