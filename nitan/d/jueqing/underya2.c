#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "寒潭盡頭");
        set("long", @LONG
這裏只覺陽光耀眼，花香撲鼻，竟是別有天地，遊目四顧，
只見繁花青草，便如同一個極大的花園，然花影不動，幽谷無
人。十餘丈外有一間茅屋(house)， 側耳傾聽，四下裏靜悄悄
的，絕無人聲鳥語，惟有蜜蜂的嗡嗡微響。身後寒潭透着陣陣
寒氣。
LONG);
        set("item_desc", ([
                "house" : NOR + YEL "但見茅屋破舊不堪，似乎很久沒人來過了。\n" NOR,
        ]));

        set("exits", ([
                "enter" : __DIR__"house",
        ]));
                 
        set("no_clean_up", 0);

        setup();
}

void init()
{       
        add_action("do_jump", ({ "tiao", "jump" }));
}

int do_jump(string arg)
{
        object me = this_player();
        object ob;


        if (! arg || arg != "tan")
                return notify_fail("你要往哪兒跳？\n");

        if (me->is_busy())
                return notify_fail("你現在正忙着呢！\n");

        if (me->is_fighting())
                return notify_fail("你還是先把你面前這個傢伙解決了再説。\n");

        write(HIC "你縱身入潭，順勢而下忙，向光亮處游去，過不多時，便到了\n"
                  "寒潭另一側，你迫不及待，縱身躍出水面。\n\n" NOR);

        if (! ob = find_object(__DIR__"underya"))
               ob = load_object(__DIR__"underya");

        me->move(ob);
       
        return 1;

}