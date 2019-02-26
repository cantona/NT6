// Room: /d/huanggong/shenwumen.c

inherit ROOM;

void create()
{
        set("short", "神武門");
        set("long", @LONG
原稱玄武門. 這裏是皇城的北門, 呈凹字形的建築, 與午門合稱兩
闕, 是防禦和保衞皇城的宮門. 門樓重檐廡殿頂, 內設鐘鼓, 黃昏時鳴
鍾百零八響, 而後起更擊鼓報時, 直到次日拂曉鳴鐘. 每年遴選秀女, 
應選女子皆從此門入宮. 明末李自成攻進北京城時, 崇禎帝由此門逃上
煤山, 自縊身亡. 
LONG         );
        set("outdoors", "huanggong");
        set("no_fight", "1");
        set("exits", ([ /* sizeof() == 2 */
                "east"  : __DIR__"dao5",
                "west"  : __DIR__"dao6",
                "north" : __DIR__"jingshan",
                "south" : __DIR__"qinandian",
        ]));
        set("objects", ([
                __DIR__"npc/yulin" : 2,
                __DIR__"npc/chaerzhu" : 1,
        ]));

	set("coor/x", -2820);
	set("coor/y", 7751);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        if (dir!="north")
                return notify_fail("察爾珠上前擋住你，朗聲説道：這位"+RANK_D->query_respect(me)+"，入宮走前門。\n");
        return ::valid_leave(me, dir);
}