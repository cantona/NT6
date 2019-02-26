// Room: /d/wuyi/1qu.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "一曲");
        set("long", @LONG
“曲曲山迴轉，峯峯水抱流”。這裏就是天下馳名的武夷山九曲溪
了。溪岸北邊是道教聖地武夷宮。南岸是大小觀音巖。溪水到這裏流速
平緩，東去匯如崇陽溪。朱熹《九曲棹歌》曰：“武夷山上有仙靈，山
下寒流曲曲清。欲識箇中奇絕處，棹歌閒聽兩三聲。一曲溪邊上釣船，
幔亭峯影蘸晴川。虹橋一斷無消息，萬壑千巖鎖翠煙。……”
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "west"      : __DIR__"2qu",
                "north"     : __DIR__"wuyigong",
                "northwest" : __DIR__"path1",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1400);
        set("coor/y", -5010);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
