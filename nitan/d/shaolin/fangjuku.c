// Room: /d/shaolin/fangjuku.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "防具庫");
        set("long", @LONG
這是一間很大的房間，靠牆整齊地放著一個個大櫃子，不少櫃子
門敞開著，露出裡面的各種防具，品種之多，是你生平僅見。一位灰
衣僧人正埋頭整理一堆破損的護具。連你進來也沒有注意。
LONG );
        set("exits", ([
                "north" : __DIR__"yaopinku",
                "south" : __DIR__"wuqiku",
        ]));
        set("objects",([
                CLASS_D("shaolin") + "/dao-xiang" : 1,
        ]));
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
