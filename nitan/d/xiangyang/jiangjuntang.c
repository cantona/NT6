// Room: /d/xiangyang/jiangjuntang.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "將軍府大堂");
        set("long", @LONG
這裡是將軍府的大堂，公案後端坐著一個威猛的將軍，但一臉疲
憊，看來征戰剛歸的模樣。大堂兩邊擺著兵器架，架上鋒刃仍留血跡，
映著架後的戰旗，分外耀眼。兩班將佐，雖征塵未洗，但鬥志昂揚，
甚是雄壯。
LONG );
        set("exits", ([
                "south" : __DIR__"jiangjunyuan",
        ]));
        set("objects", ([
                __DIR__"npc/wang" : 1,
                __DIR__"npc/zuo" : 1,
                __DIR__"npc/pian" : 1,
                __DIR__"npc/ya" : 1,
                __DIR__"npc/pi" : 1,
        ]));
        set("coor/x", -7810);
	set("coor/y", -740);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}