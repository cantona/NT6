// Room: /d/taishan/huima.c
// Last Modified by winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "回馬嶺");
        set("long", @LONG
回馬嶺古名石關，又名天關、瑞仙巖。此地山勢陡峭，峰回路轉，
馬至此不能登，故名。據說當年唐玄宗上泰山封禪，來到這裡，因陡峭
難攀，累死了白馬，要改乘小轎上山。石坊後盤路岌岌陡絕，東南上而
西北折，形似馬蹄，故稱馬蹄盤。崖壁題“勒馬回看岱嶺雲”。
LONG );
        set("exits", ([
                "northup"  : __DIR__"ertian",
                "eastdown" : __DIR__"hutiange",
        ]));
        set("objects",([
                __DIR__"npc/tiao-fu" : 1,
                __DIR__"npc/jian-ke" : 1,
        ]));
//        set("no_clean_up", 0);
        set("outdoors", "taishan");
        set("coor/x", 60);
	set("coor/y", 180);
	set("coor/z", 90);
	setup();
        replace_program(ROOM);
}