// Room: /d/taishan/xiayi.c
// Last Modified by Winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "俠義廳");
        set("long", @LONG
這裡是封禪台左邊的俠義廳，武林盟賞善使者平時不下山時，
通常都是在這裡辦理武林公案。上首正中放著把太師椅，賞善使者
就坐在上面開堂審理。左右各侍立著幾位紅衣武士，看上去威風凜
凜，自有一股莊嚴氣象。
LONG );
        set("exits", ([
                "west" : __DIR__"fengchan",
        ]));
        set("objects",([
                __DIR__"npc/wei-shi2" : 3,
        ]));
        set("coor/x", 40);
	set("coor/y", 310);
	set("coor/z", 220);
	setup();
        SHANGSHAN->come_here();
}

void reset()
{
        ::reset();
        SHANGSHAN->come_here();
}