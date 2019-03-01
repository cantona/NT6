// Room: /testmud/d/changan/gudi.c
// This is a room made by Wsl.

inherit ROOM;
int do_break(string arg);
int do_jump(string arg);
int do_enter(string arg);
void create()
{
        set("short", "谷底");
        set("long", @LONG
頭頂幾道陽光照在地上，腳下是一片很厚的草地，走在上面軟綿
綿的，很是恰意，四周看上去高不可攀，怪石嶙峋，你心中不由一驚，
要不是這片厚厚的草堆墊著，在好的輕功也會摔得變成一堆肉泥。
LONG );
        set("item_desc", ([
        "怪石" : "在嶙峋的怪石中，有塊巖石十分光滑，與其他巖石不同。\n", 
])); 

        setup();
}
void init()
{
    add_action("do_break", "break");
    add_action("do_jump", "jump");
    add_action("do_enter", "enter");
}
int do_break(string arg)
{
    int n;
    object me = this_player();
    if( !query_temp("killer", this_player()))return 0;
    if( !arg || arg!="巖石" )
    {
        write("你要震碎什麼！\n");
        return 1;
    }
    if (query("break"))
        return notify_fail("巖石已被打破了。\n");
    n=query("neili", me);
    if (n >= 40000)
    {
        message_vision("$N氣運丹田，雙掌直向前方打出一道勁力。\n", this_player());
        message_vision("只見被$N打碎的巖石四出飛濺，中間的一塊巨巖承受不了震動，\n", this_player());
        message_vision("掉落在草地上，發出巨大的響聲。你驚喜的發現在巖石上方出現了一個洞。\n", this_player());
        set("break",1);
        set("neili", n-5000, this_player());
        remove_call_out("close");
        call_out("close", 5, me);
    }
    else
    {
        message_vision("結果只聽一聲悶哼，$N被自己的內力震得眼前一黑....\n", this_player());
        set("neili", 0, this_player());
        this_player()->unconcious();
    }
    return 1;
}
int do_jump(string arg)
{
        object me;
        me = this_player();
        if(!query("break")) return 0;
        if( query_temp("climb", me) )
                return notify_fail("你已經站在巖石上了。\n");
        if( !arg || arg!="碎巖" )
        {
        write("你想爬到什麼地方去？\n");
        return 1;
        }
        if ((int)me->query_skill("dodge",1) > 800 ) {
                message_vision("$N一個縱身，跳上了巖石。\n", me);
                set_temp("climb", 1, me);
        }else{
                message_vision("$N施展輕功，向上跳去，但卻怎麼也跳不上去。\n", me);
        }
        return 1;
}
int do_enter(string arg)
{
        object me;
        me = this_player();
        if( !query_temp("climb", me))return 0;
        if( !arg || arg!="巖洞" )
        {
        write("你想去那啊？\n");
        return 1;
        }
        message_vision("$N躬了躬身體，鑽進了巖洞裡。\n", me);
        me->move("/d/qinhuang/mudong0.c");
        message_vision("“隆隆”，洞口已經封死了。\n", me);
        return 1;
}

void close(object me)
{
    if (me)
        delete_temp("climb", me);
    message("vision","上面幾塊巖石掉了下來，把洞口又封住了。\n", this_object());
    delete("break");
}
