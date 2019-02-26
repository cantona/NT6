// Room: /d/suzhou/sdhyuan.c
// Last Modified by winder on May. 15 2001
inherit ROOM;

void create()
{
        set("short", "花園");
        set("long",@long
這裏原是吳宮的御花園遺址，園內有夫差與西施採蓮取樂，稱為“
山頂盪舟”的玩花池。池的東面挖了吳王井，專供西施照容曉粧之用。
西面有一口樑代高僧修浚的智積井，寺內和尚引水常取與此。
long);
        set("outdoors", "suzhou");
        set("exits",([
                "west"     : __DIR__"zhijijing",
                "east"     : __DIR__"wuwangjing",
                "eastdown" : __DIR__"lingyanta",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}