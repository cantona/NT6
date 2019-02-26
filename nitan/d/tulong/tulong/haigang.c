#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "東海之濱");
        set("long", @LONG
這裏就是大海之濱，浪花拍打着礁石，發出陣陣響聲，海
面上一羣羣海鷗歐歐地叫着，不時有魚兒躍出海面，濺起層層
浪花。邊上有艘大船(boat)，船上坐着幾個漁夫打扮的人，乘
船可渡過大海到達海的另一端。西面一直走就是燕京了，東面
是一望無際的大海。極目眺望不禁讓人心胸開擴神舒意暢，的
確是一個好居處。
LONG);
        set("exits", ([
                "west"  : "/d/beijing/road10",
                "north" : __DIR__"haian",
        ]));

        set("item_desc", ([
                "boat" : "這是一艘大帆船，造得很結實，看來可以出遠海的。\n",
        ]));

        set("objects", ([
                "/d/shenlong/npc/chuanfu" :1,
        ]));

        set("outdoors", "beijing");
        setup();
}

void init()
{
        object me, dao, room, bai, ding;

        me = this_player();
        room = load_object("/d/tulong/tulong/huichang");
        ding = present("ding", room);

        if (objectp(ding)) 
                dao = present("tulong dao", ding);

        if (objectp(dao))
        {
                room = load_object("/d/tulong/tulong/daobian");
                bai = present("bai guishou", room);

                tell_object(me, HIC "\n只見岸邊上泊滿了海船，所有的海船全部標記着天"
                               "鷹教的標誌。\n" NOR);

                if (objectp(bai)
                    && !query_temp("go", bai )
                    && !query_temp("to_wang", me )
                    && query("combat_exp", me)>1000000
                    && query("weiwang", me)>100000 )
                {
                              tell_object(me, CYN "\n白龜壽對你説道：此次我天鷹教得到了屠"
                                        "龍寶刀，這位武林同\n道可願意參加揚刀立威大"
                                        "會，選出此刀該為何人所有？\n" NOR);
                        tell_object(me, HIR "\n你願意參加(" HIY "accept" HIR ")王盤"
                                        "山島揚刀立威大會嗎？\n" NOR);
                        set_temp("to_wang", 1, me);
                        add_action("do_accept", "accept");
                }
        }
}

int do_accept()
{
        object me, room, bai;

        me = this_player();
        room = load_object("/d/tulong/tulong/daobian");
        bai = present("bai guishou", room);

        if( !query_temp("to_wang", me) )
                return notify_fail("什麼？\n");

        if( query_temp("go", bai) )
                return notify_fail("真是可惜，已經有人比你早一步參加了。\n");

        tell_object(me, HIR "你決定去參加揚刀立威大會。\n\n" NOR);

               set_temp("go", 1, bai);
        me->start_busy(15);

        remove_call_out("moveto");
        call_out("moveto", 10, me);
        return 1;
}

int moveto(object me)
{
        message_vision(HIC "\n$N" HIC "坐上了天鷹教的大船，聽到舵子"
                       "手喊道：“開船了！”大船\n慢慢的向大海駛進"
                       "。\n\n" NOR, me);
        me->move("/d/tulong/tulong/boat");

        remove_call_out("arrive1");
        call_out("arrive1", 10, me);
        return 1;
}

int arrive1(object me)
{
        message_vision(HIB "\n天鷹教的大船在大海上慢慢的漂着……$N"
                       HIB "不禁感到睡意朦朧。\n" NOR, me);

        remove_call_out("arrive2");
        call_out("arrive2", 10, me);
        return 1;
}

int arrive2(object me)
{
        message_vision(HIY "\n$N" HIY "突然聽到一聲驚喝：“到了，下"
                       "船吧！”$N" HIY "頓時提起精神跟\n着天鷹教教"
                       "眾下了船。\n\n" NOR, me);
        me->move("/d/tulong/tulong/boat2");
        tell_object(me, HIC "\n你跟隨天鷹教到達了王盤山島邊。\n\n" NOR);
        return 1;
}