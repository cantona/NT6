// This is a room made by wsl.
inherit ROOM;
void create()
{
    set("short", "大殿");
        set("long", @LONG
沿着"水銀"河，走到了大殿的盡頭，這裏更是金碧輝煌，迎面是
一個龍頭寶座，用純金鑄造而成，寶座上囊嵌無數的寶石，上方有個
碩大的龍頭，也是由金玉所成，巍是壯觀。東面有扇巨大的石門，但
卻是關着的。
LONG );
        set("exits", ([
                "south" :__DIR__"dadian2",
]));
    set("qiao",1);
    setup();
}
void init()
{
        add_action("do_look","look");
        add_action("do_climb","climb");
        add_action("do_qiao","qiao");
        add_action("do_jump","jump");
}
int do_look(string arg)
{
        object me=this_player();
        if (!arg)       return 0;
        if( !query_temp("killer", me))return 0;
        if( !query_temp("climb", me))return 0;
        switch (arg){
                case "龍頭":    if (query("qiao"))
                                write("細看這個龍頭，兩眼炯炯有神，似乎有些異處。\n");
                                else
                                write("細看這個龍頭，才發現龍頭少了兩個龍珠子。\n");
                        return 1;
                case "石門":    write("石門上有兩個門環，卻看不到一絲縫隙，門環上有\n兩個洞，不知道是做什麼用的。\n");
                        set_temp("look", 1, me);
                return 1;
        }
        return 0;
}
int do_climb(string arg)
{
        object me=this_player();
        object weapon;
        if(!arg)        return 0;
        if( !query_temp("look", me))return 0;
        if(arg != "龍角")       return notify_fail("你要往那爬呀？\n");
        if( query_temp("chan", me))return notify_fail("你已經在龍頭上了。\n");
        if( !objectp(weapon=query_temp("weapon", me)))return notify_fail("這裏光溜溜的，你怎麼爬呀。\n");
        if( query("skill_type", weapon) != "whip")return notify_fail("你還是找條繩子什麼的，也許會爬得上去哦。\n");
        message_vision("$N使出"+query("name", weapon)+"，往上一拋，纏在龍角上。\n然後$N施展輕功，爬到了龍頭上。\n",me);
        set_temp("chan", 1, me);
                return 1;
}
int do_qiao(string arg)
{
        object me=this_player();
        object weapon,ob;
        if(!arg)        return 0;
        if( !query_temp("chan", me))return notify_fail("你夠不着。\n");
        if(!query("qiao")) return notify_fail("你還要橇什麼？\n");
        if(arg != "龍眼")       return notify_fail("你想撬什麼嘛？\n");
        if( !objectp(weapon=query_temp("weapon", me)))return notify_fail("用手啊，也許找些什麼工具來會好點哦。\n");
        if( query("skill_type", weapon) != "dagger")return notify_fail("你舉起手中"+query("name", weapon)+"揮舞了幾下，才發現這樣東西不好使也。\n");
        message_vision("$N掏出一把"+query("name", weapon)+",使勁地撬了起來。\n$N連吃奶的力氣都用上了，終於撬起了兩個碩大的龍眼。\n",me);
        ob=new(__DIR__"obj/longzhu.c");
        if (!ob->move(me))
                ob->move(this_object());
        ob=new(__DIR__"obj/longzhu.c");
        if (!ob->move(me))
                ob->move(this_object());
        set("qiao",0);
        return 1;
}
int do_jump(string arg)
{
        object me=this_player();
        if(!arg)        return 0;
        if( !query_temp("chan", me))return 0;
        message_vision("$N一個縱身，跳了下了來。\n",me);
        delete_temp("chan", me);
        return 1;
}
void open_door(object ob,int i)
{
    object room;
    if (!ob || environment(ob)!=this_object())  return;
    if (i<10)
    {
    tell_room(this_object(),"石門激烈地震動了一下，“咯...咯...咯...”\n");
    call_out("open_door",10,ob,i+1);
    return;
    }
    tell_room(this_object(),"門上的石環轉動了一圈，只見石門猛地向兩邊分開。");
    if (!room=find_object(__DIR__"shidao2"))
        room=load_object(__DIR__"shidao2");
    message_vision("$N站立不穩，被一股強大的吸力拉了進去。\n",ob);
    ob->move(room);
    ob->unconcious();
}
