// Room: /d/huanggong/jiaotaidian.c

inherit ROOM;

void create()
{
        set("short", "交泰殿");
        set("long", @LONG
這個亭子形方殿，是皇後過生日慶祝的小禮堂。交泰殿名源于 <周
易> ：“天地交，泰”。殿中放置了象征國家至高權力的二十五顆寶璽。
東側是一尊銅壺滴漏，西側是一架大自鳴鐘。每年春季，皇後在此舉行
喂蠶儀禮。
LONG
        );
        set("exits", ([ /* sizeof() == 4 */
                 "north" : __DIR__"kunninggong",
                 "south" : __DIR__"qianqinggong",
        ]));
        set("objects", ([ /* sizeof() == 4 */
                __DIR__"obj/yuma" : 1,
        ]));

	set("coor/x", -2810);
	set("coor/y", 7761);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}