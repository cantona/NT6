//lianthrow.c                唐門練武場

inherit ROOM;

void init();
int do_lian(string);

void create ()
{
        set ("short", "練武場");
        set ("long", @LONG
這是一個寬敞的練武場。你的身邊擺著幾個木架，每一個上面又
分成十數個小格，每一格中都放著不同的暗器。你的對面，也就是廣
場的那邊有幾個木人模型，頭、臉、耳、鼻都清晰可見，你可以用它
來練習(zhi)唐家稱霸江湖的暗器手法。
LONG);
        set("exits", ([
                "south" : __DIR__"nzlange3",
        ]));
        set("outdoors", "tangmen");
        setup();
}

void init()
{
        add_action("do_lian", "zhi");
}

int do_lian(string arg)
{
        object me;
        int jingli_cost;

        me = this_player();

        if ( !arg || ( arg != "biao" ) )
                return notify_fail("你想幹什麼？\n");

        jingli_cost = (-1) * (5 + random(15));

        if( query("jingli", me) <= (-jingli_cost) )
                return notify_fail("你太疲勞了，沒有精力練功了。\n");

        if ( (int)me->query_skill("throwing", 1) < 51 )  
        {
                write("你從木架上拿起一枚暗器，擺好架勢向木人擲去，“咄”的一聲打歪了！\n但是你對暗器手法又有了一點認識。\n");
                addn("jingli", jingli_cost, me);
                me->improve_skill("throwing",(15+random(query("int", me)/2)));
        }
        else
                if ( (int)me->query_skill("throwing", 1) < 101 )  
                {
                        write("你從木架上捻起一枚暗器，甩手向木人擲去，“咄”的一聲打中了！\n你對暗器手法有了一些認識。\n");
                        addn("jingli", jingli_cost, me);
                        me->improve_skill("throwing",(20+random(query("int", me)/2)));
                }
                else
                        write("你隨手捻起一枚暗器向木人擲去，“咄”的一聲正中眉心！\n你在這裡已經學不到什麼了！\n");
        return 1;
}