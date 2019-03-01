// Room: /d/taishan/wudafu.c
// Last Modified by winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "五大夫鬆");
        set("long", @LONG
《史記》載，秦始皇封泰山時中途遇雨，避于此間大樹下，因封樹
為“五大夫”。後訛為五株。明代萬歷年間，古鬆被雷雨所毀。清雍正
年間欽差丁皂保奉敕重修泰山時，補植五株鬆。古鬆拳曲古拙，蒼勁蔥
鬱，自古被譽為“秦鬆挺秀”，列為泰安八景之一。
　　五大夫鬆西攔住山坡上有望人鬆，長枝下垂，似躬身招手邀客，又
名迎客鬆。
LONG );
        set("exits", ([
                "northwest" : __DIR__"chaoyang",
                "eastdown"  : __DIR__"sandengya",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "taishan");
        set("coor/x", 40);
	set("coor/y", 210);
	set("coor/z", 120);
	setup();
        replace_program(ROOM);
}