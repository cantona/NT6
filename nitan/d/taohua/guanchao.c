// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
#include "localtime.h"

inherit ROOM;

string day_event()
{ 
        return NATURE_D->outdoor_room_event();
}

void create()
{
        set("short", "觀潮台");
      set("long", @LONG
這是一座頗有點破舊的高台，前面是一望無際的大海。遠遠望去大海
浩淼，萬裡無波，海天一線處一道白線滾滾而來，漸近漸快，稍後洪濤洶
湧，白浪連山，傾刻之間已至台下，驚濤駭浪狠狠打在台基上。你頓時感
覺立足不穩，搖搖欲墜，不禁臉上變色，為這天地之威所深深撼動。
LONG );

        set("exits", ([
                "southdown" : __DIR__"beach",
        ]));

        set("outdoors", "taohua");
        set("guanchao", 1);
        set("coor/x", 9040);
        set("coor/y", -2990);
        set("coor/z", 10);
        setup();
}

string long() 
{
        string msg;

        msg  = "這是一座頗有點破舊的高台，前面是一望無際的大海。";

        if (day_event() == "event_dawn" || day_event() == "event_evening")
        {
                msg += "遠遠望去大海浩淼，萬裡無波，海天一線處一道白線滾滾而來，漸近漸快，稍後";
                msg += "洪濤洶湧，白浪連山，傾刻之間已至台下，驚濤駭浪狠狠打在台基上。你頓時感覺";
                msg += "立足不穩，搖搖欲墜，不禁臉上變色，為這天地之威所深深撼動。";

        } else 
        {
                msg += "你登高而遠望，但見長天一碧，萬裡無波，當真是“海闊憑魚躍，天高";
                msg += "任鳥飛”。當此景象，你深吸一口氣，只覺胸腹之間清氣充盈，輕飄";
                msg += "飄的似乎就要乘風而去。";
        }

        return sort_string(msg, 64, 4); 
}