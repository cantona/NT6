#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", "七曲九回廊");
        set("long",
"這裡是七、八十道長廊，相互接連，連綿不絕，直是無窮無盡。每個\n"
"長廊轉彎處都有一盞宛如鬼火般搖晃不定的黃燈。廊邊的潭水在燈光照射\n"
"下發出墨綠的異光。\n"
);
        set("no_magic", "1");

        setup();
}
int valid_leave(object me, string dir)
{
     if( random(query("kar", me))<15 )
message_vision(GRN"“叮”的一聲輕響...一蓬牛毛細針向$N射來。\n"NOR,me);
     if(random(me->query_skill("dodge") / 100) > 10 ) {
     message_vision(RED"只聽$N一聲慘嚎，細針深深地釘在了$N的身上！\n"NOR,me);
     me->receive_wound("qi",random(me->query_skill("dodge") / 10));
     }
     else
     message_vision(GRN"$N輕鬆的躲了開去。\n"NOR,me);
     return ::valid_leave(me, dir);
}

