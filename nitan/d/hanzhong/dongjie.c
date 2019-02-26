// dongjie.c 東街
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "東街");
        set("long", @LONG
這裏是漢中鎮的東街，往東走就是漢中東門了。漢中鎮是個小
城鎮，不算繁華，街上的行人也很稀少。北面是一家客棧，客棧門
口掛着半副‘雞鳴早看天’的對聯，上聯已經被撕掉了。南面是一
座大宅院，硃紅大門上佈滿銅釘。從這裏往西走，就是漢中鎮的中
心了。
LONG
        );
        set("outdoors", "hanzhong");
        set("exits", ([
                "east" : __DIR__"dongmen",
                "west" : __DIR__"zhongxin",
                "north" : __DIR__"kedian1",
                "south" : __DIR__"fu-damen",
        ]));
        set("objects", ([
                __DIR__"npc/seller" : 1,
                "/clone/npc/walker"  : 1,
        ]));
        set("coor/x", -12240);
	set("coor/y", 810);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}