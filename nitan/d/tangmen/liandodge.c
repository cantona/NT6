//liandodge.c                唐門練武場

inherit ROOM;

void init();
int do_lian(string);

void create ()
{
        set ("short", "練武場");
        set ("long", @LONG
這是一個寬敞的練武場。你的面前的場子上立滿了一根根木樁，
幾個唐門弟子正在上面施展輕功身法，飛快的四處遊走，但不時也
有幾個摔了下來，弄的鼻青臉腫。你要不怕就也上去練練 (yue)基
本的輕功身法吧。
LONG);

        set("exits", ([
                "north" : __DIR__"nzlange3",
        ]));
        set("outdoors", "tangmen");
        setup();
}

void init()
{
        add_action("do_lian", "yue");
}

int do_lian(string arg)
{
        object me;
        int jingli_cost;

        me = this_player();

        if ( !arg || ( arg != "zhuang" ) )
                return notify_fail("你想幹什麼？\n");

        jingli_cost = (-1) * (5 + random(15));

        if( query("jingli", me) <= (-jingli_cost) )
                return notify_fail("你太疲勞了，沒有精力練功了。\n");

        if ( (int)me->query_skill("dodge", 1) < 51 )  
        {
                write("你氣運丹田，輕輕一縱身跳上一根較矮的木樁，但是腳下一晃摔了下來！\n不過你對輕功身法有了一點了解。\n");
                addn("jingli", jingli_cost, me);
                me->improve_skill("dodge",(15+random(query("int", me)/2)));
        }
        else
                if ( (int)me->query_skill("dodge", 1) < 101 )  
                {
                        write("你氣隨心升，一晃身躍上一根木樁，只是感到內息略有阻滯！\n你對輕功身法有了一些認識。\n");
                        addn("jingli", jingli_cost, me);
                        me->improve_skill("dodge",(20+random(query("int", me)/2)));
                }
                else
                        write("你隨意的在木樁上飛奔跳躍，感到已經沒有困難。\n你在這裡已經學不到什麼了！\n");
        return 1;
}