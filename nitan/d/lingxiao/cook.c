inherit ROOM;

#include <ansi.h> 

void create()
{
        set("short","廚房");
        set("long",@LONG
這裡是凌霄城的廚房。一陣飯菜的香味充盈其間。一個凌霄
弟子滿頭大汗，正在做飯。他做飯方法倒也特別，人綁在一根倒
吊的繩子上，用一個奇大的鏟子來攪動一口極大的鍋。聽說是白
自在去少林寺考察回來後，要求每一個輪值做飯的弟子都要這樣
幹，利于練功雲雲……你可以用(serve)，來獲得飯菜。
LONG);
        set("exits",([
                "west" : __DIR__"zoulang2",
        ]));
        set("objects",([
                __DIR__"npc/dizi" : 1,
        ]));
        set("ricewater", 5);
        setup();
}

void init()
{
        add_action("do_serve","serve");
}

int do_serve()
{
        object me;
        object food;
        object water;
        me = this_player();

        if( query("family/family_name", me) != "凌霄城" )
                return notify_fail(CYN "凌霄弟子道：你又不是凌霄城的，走開。\n" NOR);

        if (present("rice", this_player())) 
                return notify_fail(CYN "凌霄弟子道：吃完了再拿，別浪費食物。\n" NOR);

        if (present("soup", this_object())) 
                return notify_fail(CYN "凌霄弟子道：吃完了再拿，別浪費食物。\n" NOR);

        if (query("ricewater") > 0)
        {
                message_vision(CYN "凌霄弟子將熱氣騰騰的飯菜遞到你手中，笑"
                               "道：你慢用。\n" NOR, me);
                food = new(__DIR__"obj/rice");
                water = new(__DIR__"obj/soup");
                food->move(me);
                water->move(me);
                addn("ricewater", -1);
        }
        else 
                message_vision(CYN "凌霄弟子對$N" CYN "歉聲道：嗨，吃的喝的都"
                               "沒了。\n" NOR,me);
        return 1; 
}
