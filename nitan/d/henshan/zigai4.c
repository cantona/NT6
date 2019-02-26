#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "水蓮洞內");
        set("long", @LONG
往前行段路後，道路也漸漸寬闊了起來。隱隱約約似乎有水滴之
聲傳來，你不禁想朝聲音傳來的方向走去 (zou)看看。
LONG );
        set("exits",([
               "east" : __DIR__"zigai1",
        ]));
        
        set("objects",([
               "/clone/beast/yanjingshe" : 1,
        ]));
        
        setup();

}


void init()
{
        object me = this_player();
        add_action("do_zou", "zou");
        add_action("do_use", "use");

        if (present("fire", me))
                       set_temp("marks/點", 1, me);

        else delete_temp("marks/點", me);
}        

int do_zou()
{
        object me = this_player();
        
        if( !query_temp("marks/點", me) )
                return notify_fail(HIW"\n這裏一片漆黑，如果沒有火光寸步難行。\n\n"NOR);
        
        if (me->is_fighting() || me->is_busy())
                return notify_fail("\n你現在正忙着呢。\n\n");
        
        me->move(__DIR__"outzigai");
        
        return 1;
}


int do_use(string arg)
{
        object me = this_player();

        if (! arg || arg != "fire") return 0;
        
        if (! present("fire", me)) return 0;

        write(HIC "\n你將火折點然了。\n\n" NOR);

        set_temp("marks/點", 1, me);

        return 1;

}