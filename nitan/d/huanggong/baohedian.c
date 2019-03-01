// Room: /d/huanggong/baohedian.c

inherit ROOM;

void create()
{
        set("short", "保和殿");
        set("long", @LONG
碉欄玉砌, 金玉堂皇, 這才是皇族氣范. 飛檐敞椽, 支撐天地的大
柱正是八部天龍. 這裡是紫禁三殿的--保和殿.
    保和的意思是保持事物的協調. 這座建築的重檐歇山頂式, 是皇帝
舉行殿試的場所以及歲末除夕賜宴外藩王公的地方.
LONG
        );
        set("no_clean_up", 0);
        set("exits", ([
                "northwest" : __DIR__"longzongmen",
                "northeast" : __DIR__"jingyunmen",
                "north"     : __DIR__"qianqingmen",
                "south"     : __DIR__"zhonghedian",
                "east"      : __DIR__"yongxiang4",
                "west"      : __DIR__"yongxiang1",
        ]));
	set("coor/x", -2810);
	set("coor/y", 7721);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}