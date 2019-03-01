// shantang.c
// Modified by Winder June.25 2000

inherit ROOM;

void create()
{
        set("short", "酒家");
        set("long", @LONG
這裡是樹林中的一間小小的酒家，地方雖然不大，但是也有不少逍
遙派的弟子光顧這裡。你終于找到香味的來源了，看著可口的飯菜，你
忍不住也想叫 (order)一份了。
LONG );
        set("exits",([
                "north" : __DIR__"xiaodao2",
        ]));
        set("objects",([
                CLASS_D("xiaoyao")+"/likuilei" : 1,
        ]));
        set("ricewater", 5);
        set("coor/x", 60);
        set("coor/y", -510);
        set("coor/z", 0);
        setup();
}
void init()
{
        add_action("do_order","order");
}

int do_order(string arg)
{
        object me;
        object food;
        object water;
        me=this_player();
        if (arg)  return notify_fail("小二哥跑出來道: 這樣東西這裡沒有啊。\n");
        if (query("ricewater")>0)
        {
                message_vision("小二哥連聲答應，從內廳一溜煙跑出來，端著一碗米飯和一碗水拿了給$N。\n",me);
                food=new(__DIR__"obj/rice");
                water=new(__DIR__"obj/bowl");
                food->move(me);
                water->move(me);
                addn("ricewater",-1);
        }
        else 
                message_vision("小二哥在內廳對$N歉聲應道: 嗨，吃的喝的都沒了。\n",me);
        return 1; 
}
int valid_leave(object me,string dir)
{
        me=this_player();
        if(dir=="north" && (present("bowl",this_player()) || present("rice",this_player()))) 
             return notify_fail("小二說道：真抱歉，我們這裡沒有打包服務。\n");
        return ::valid_leave(me,dir);
}