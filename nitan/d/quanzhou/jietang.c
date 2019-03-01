// Room: /d/quanzhou/jietang.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "甘露戒壇");
        set("long", @LONG
從大殿後門出來，便是重檐八角攢尖式的戒壇，是佛教徒受戒剃度
之處。壇分五級，最高層中奉木雕的盧舍那坐佛，所祀佛像還有釋加牟
尼佛、阿彌陀佛、千手千眼觀音佛等。壇座環列「護三皈」和「護五戒
」諸神神主牌位六十四座，氣氛莊嚴。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                "south"   : __DIR__"yuetai",
                "northup" : __DIR__"cangjingge",
        ]));
	set("coor/x", -920);
	set("coor/y", -7620);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}