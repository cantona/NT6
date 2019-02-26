// Room: /d/playertown/xuemeiting.c 雪梅亭
// Build 1999.12.10 bmw

inherit ROOM;

void create()
{
        set("short", "雪梅亭");
        set("long",
"這是一個非常別緻的小亭子，暗紅色的亭柱被幾條漢白玉長凳相連，\n"
"畔在碧綠的湖水邊，亭子的周圍種着幾棵梅樹，當這裏下雪的時候，紅梅\n"
"正是綻放時，配上這頂紅亭，格外秀氣，所以這裏時常有戀人再次相會，\n"
"被當地的百姓戲稱為“鴛鴦亭”。\n"
);
        set("outdoors", "playertown");
        set("exits", ([
                "west"  : __DIR__"road5",
        ]));
        setup();
        replace_program(ROOM);
}