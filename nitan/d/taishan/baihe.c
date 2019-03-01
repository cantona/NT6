// Room: /d/taishan/baihe.c
// Last Modified by winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "白鶴泉");
        set("long", @LONG
相傳從前這裡有一個白鶴泉，它的水清涼甘甜，為泰山之最。這泉
水長年湧流不斷，噴出的水象仙鶴撲扇著翅膀洗澡一樣，因以為名。可
惜後來有一個自私自利的小官，獨霸了泉水，後來更因迷信風水之說，
把泉眼堵塞，白鶴泉從此便幹涸了。現在只剩下一座刻著「白鶴泉」三
字的石坊以為紀念。從這裡繼續北上，便是上山之路。
LONG );
        set("exits", ([
                "northup"   : __DIR__"hongmen",
                "southdown" : __DIR__"daizong",
        ]));
        set("resource/water",1);
        set("outdoors", "taishan");
        set("no_clean_up", 0);
        set("coor/x", 70);
	set("coor/y", 70);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}
int valid_leave(object me,string dir)
{
        if( !userp(me) && query("ts_xl", me) && dir == "southdown" )
                return 0;
        return ::valid_leave(me,dir);
}