// Room: /d/guiyun/lianwuchang.c
// Last Modified by winder on Jul. 9 2001

inherit ROOM;

int do_jump(string arg);
int do_squat();
string look_zhuang();

void create()
{
        set("short","練武場");
        set("long",@LONG
這是供歸雲莊內弟子們練功的場子。場邊擺了兩排兵器架，上面插
着各種兵器，最多的還是各式各樣的劍。在場子的一個角落裏並排豎着
兩根半高的木樁(zhuang)，相距約一米，看起來是練功用的。西邊是男
弟子休息室，而東邊則是女弟子休息室。南邊是吃飯和喝茶的地方。
LONG
);
        set("exits",([
                "west" : __DIR__"xiuxishi-m",
                "east" : __DIR__"xiuxishi-f",
                "north" : __DIR__"zoulang6",
                "south" : __DIR__"fanting",
        ]) );
        set("objects",([
                "/clone/weapon/changjian" : 1,
                __DIR__"obj/mujian" : 1,
                __DIR__"npc/dizi-m" : 1,
                __DIR__"npc/dizi-f" : 1,
        ]));

        set("item_desc",([
                "zhuang" : (: look_zhuang :),
        ]) );
        set("no_clean_up",0);
        set("outdoors", "guiyun");
        set("coor/x", 250);
        set("coor/y", -860);
        set("coor/z", 0);
        setup();
}

void init()
{
        add_action("do_jump", "jump");
        add_action("do_jump", "tiao");
        add_action("do_squat", "squat");
        add_action("do_squat", "dun");
}

int do_jump(string arg)
{
        object me = this_player();
        int level, qicost, exp;

        if (me->is_busy())
                return notify_fail("你上一個動作還沒有完成！\n");
        level = me->query_skill("dodge", 1);
        exp=query("combat_exp", me);
        if (arg == "zhuang")
        {
                if( query_temp("thd_zhuang", me) )
                {
                        write("你已經在樁上了，別是站久了頭昏吧？\n");
                        return 1;
                }
                qicost = level / 3 + random(level / 3);
                if( query("qi", me) <= qicost )
                {
                        write("你太累了，先歇歇吧！\n");
                        return 1;
                }
                if (level < 20)
                {
                        write("你聳身作勢，向樁上躍去，可惜的是腳尖還差一些才能夠到。\n");
                        return 1;
                }
                me->receive_damage("qi", qicost);
                if (level < 60)
                {
                        message_vision("$N吸了口氣，縱上了木樁，這似乎是鍛鍊輕功的好方法。\n", me);
                        if (level * level * level / 10 < exp)
                                me->improve_skill("dodge", me->query_int() / 2);
                }
                else
                        message_vision("$N腳下微一運勁，輕輕地一縱就上了木樁，這兩根木樁對$P而言也太矮了。\n", me);
                set_temp("thd_zhuang", 1, me);
                me->start_busy(random(2)+1);
                return 1;
        }
        if (arg == "down")
        {
                if( !query_temp("thd_zhuang", me) )
                {
                        message_vision("$N想挖個坑跳進去，四處比劃了一番，卻發現周圍的人都用異樣的眼光看着自己。\n", me);
                        return 1;
                }
                qicost = level / 4 + random(level / 4);
                if( query("qi", me) <= qicost )
                {
                        write("你太累了，先歇歇吧！\n");
                        return 1;
                }
                me->receive_damage("qi", qicost);
                if (level < 60)
                {
                        message_vision("$N笨手笨腳地從樁上跌了下來，發現這很象是普通輕功的一式“平沙落雁”。\n", me);
                        if (level * level * level / 10 < exp)
                                me->improve_skill("dodge", me->query_int() / 5);
                }
                else
                        message_vision("$N輕輕一縱落到了地上，覺得這兩根木樁對$P而言也太矮了。\n", me);
                me->start_busy(random(2)+1);
                delete_temp("thd_zhuang", me);
                return 1;
        }
        return notify_fail("你要往哪裏跳？\n");
}
        
int do_squat()
{
        object me = this_player();
        int level, qicost, exp;

        if (me->is_busy())
                return notify_fail("你上一個動作還沒有完成！\n");
        level = me->query_skill("leg", 1);
        exp=query("combat_exp", me);
        qicost = level / 3 + random(level / 3);
        if( !query_temp("thd_zhuang", me) )
        {
                message_vision("$N剛往地上一蹲，就有個莊丁飛跑過來，大聲喝道：“不準隨地大小便！”\n", me);
                return 1;
        }
        if( query("qi", me) <= qicost )
        {
                write("你太累了，先站會兒喘喘氣吧！\n");
                return 1;
        }
        if (level < 30)
        {
                write("你試着蹲下來，卻覺得兩腿發軟，隨時有跌下去的危險，連忙又站直了身子。\n");
                return 1;
        }
        if (level < 100)
        {
                write("你雙腿成馬步，挺胸收腹，以站樁姿勢蹲了下來。\n");
                write("蹲了許久，你的雙腿都快木了，只好站起來活動一下。\n");
                if (level * level * level / 10 < exp)
                        me->improve_skill("leg", me->query_int());
                me->receive_damage("qi", qicost);
                me->start_busy(random(2)+1);
                if (!random(8))
                        tell_room(this_object(), me->name() + "雙腿成馬步，挺胸收腹，以站樁姿勢蹲了一會。\n", ({me}));
        }
        else
                write("你用力往下一蹲，只聽木樁“吱嘎”作響，看來你的腿勁過大了。\n");
        return 1;
}

string look_zhuang()
{
        if( query_temp("thd_zhuang", this_player()) )
                return "你往腳下的木樁看去，覺得有點暈眩，剛才在地上看時好像沒有這麼高！\n";
        else
                return "木樁離地大概一米左右，普通人難以跳上去。\n";
}

int valid_leave(object me, string dir)
{
        if( query_temp("thd_zhuang", me) )
                return notify_fail("先從木樁上跳下來(down)再説吧！\n");

        if( dir == "west" && query("gender", me) != "男性" )
                return notify_fail("你打開門正要往裏走，忽然發現裏面都是光膀子的男弟子，你趕忙捂着臉退了出來。\n");

        if( dir == "east" && query("gender", me) != "女性" )
                return notify_fail("你打開門正要往裏走，卻聽到裏面傳來一陣女弟子的尖叫聲，你嚇得趕忙退了出來。\n");
        return ::valid_leave(me, dir);
}