#include <ansi.h>
inherit ROOM;

void create()
{
        set("short","懸崖邊");
        set("long", @LONG
這裡是紫蓋仙洞外的懸崖絕壁(xuanya)，站在此處向下望去，雲
深鎖霧，寒風吹來，你不由地打了個寒戰。
LONG );
        set("item_desc", ([
               "xuanya"  : HIG "\n只見從絕壁上垂下一些樹籐(teng)， 似乎可以順著"
                           "爬(climb)\n上去。而下面卻是萬丈深淵，深不見底。\n" NOR,

               "teng"    : YEL"\n這些樹籐看起來很結實。\n" NOR,
        ]));

        set("exits",([
               "south":__DIR__"zigaihole",
        ]));            
        
        setup();

}

void init()
{
        add_action("do_tiao", ({"tiao", "jump"}));
        add_action("do_climb", "climb");
}

int do_tiao(string arg)
{
        object me, room1, room2;
        string msg;

        me=this_player();
        
        if (! room1 = find_object(__DIR__"xuanya"))
                      room1 = load_object(__DIR__"xuanya");

         if (! arg || (arg != "ya" && arg != "xuanya" && 
                      arg != "懸崖"))
                return 0;
        
        if (me->is_fighting() || me->is_busy())
        {
                write("你現在正忙著呢。\n");
                return 1;
        }        

        if (! room2 = find_object(__DIR__"xuanyadi"))
                      room2 = load_object(__DIR__"xuanyadi");

        msg = HIC"\n你鼓起勇氣往懸崖下一跳，耳邊的風“呼呼”作響，你感"
              "覺越\n落越快，一顆心都要掉了出來，猛然間你看見下面有一棵大樹，"
              HIC"\n你伸手抓住樹枝，但是樹枝卻“啪”的一聲斷了，你重重地摔\n"
              HIC"在地上，頓時昏了過去。\n\n" NOR;

        write(msg);
        me->move(room2);
        me->unconcious();
       
        me->receive_wound("qi",(query("max_qi", me)/2));

        if (random(99)<62)
                CHANNEL_D->do_channel(this_object(), "rumor", 
                              me->name() + "不幸墜下衡山懸崖，生死不明！");
        
        return 1;
}

int do_climb(string arg)
{
        object me, room;
        string msg;

        me = this_player();

        if (! room = find_object(__DIR__"zigai"))
                room=load_object(__DIR__"zigai");
        
        if (! arg || arg != "teng")
                return notify_fail("\n你要往哪兒爬。\n\n");

        if (me->is_fighting() || me->is_busy())
                return notify_fail("\n你正忙著呢。\n\n");

        msg = HIG "\n$N拉著樹籐往峭壁上爬去。\n\n" NOR;

        message_vision(msg, me);
        write(HIW "\n你終于爬了上來。\n\n" NOR);
        message("vision", HIG "\n" + me->name() + HIG "從峭壁下面爬了上來。\n\n" NOR,
                          room, me);

        me->move(room);

        return 1;
        
}
