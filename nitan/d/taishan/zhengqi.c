// Room: /d/taishan/zhengqi.c
// Last Modified by Winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "正氣廳");
        set("long", @LONG
這裡是封禪台右邊的正氣廳，武林盟罰惡使者平時不下山時，
通常都是在這裡處置武林公案。上首正中放著把虎皮椅，罰惡使者
就坐在上面開堂審理。左右各侍立著幾位紅衣武士，看上去殺氣騰
騰，令人凜然而生懼意。
LONG );
        set("exits", ([
                "east" : __DIR__"fengchan",
        ]));
        set("objects",([
                __DIR__"npc/wei-shi2" : 3,
        ]));
        set("coor/x", 20);
	set("coor/y", 310);
	set("coor/z", 220);
	setup();
        FAE->come_here();
}
void reset()
{
        ::reset();
        FAE->come_here();
}