inherit ROOM;

void create()
{
        set("short", "洛陽中心廣場");
        set("long", @LONG
你腳下站的就是赫赫有名的古都洛陽，雖然國家正處于連年戰亂災荒，
民不聊生，但是絲毫不能掩飾這裡的繁華，一條條寬敞明凈的大道，熙熙
攘攘的人群，熱鬧的集市，充分展示了這座最古老的城市的生機。街上滿
是來這裡觀光遊覽的遊客，想必吸引他們的是大名鼎鼎的洛陽唐三彩和中
國第一古剎白馬寺吧！當然建在這裡的洛陽行宮也是許多別處的官員常來
膜拜的地方，而金刀王家的大名更是引來了無數的武林人士的拜訪。廣場
上好像剛剛下過雨，空氣很清新，地上濕漉漉的，整個廣場給人的感覺就
是古老而賦有生機，就像是這座古城的一個縮影。
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"eroad1",
                  "north" : __DIR__"nroad1",
                  "south" : __DIR__"sroad1",
                  "west" : __DIR__"wroad1",
        ]));
        set("objects", ([
                "/d/taishan/npc/jian-ke" : 1,
                "/d/beijing/npc/maiyi2" : 1,
                "/d/beijing/npc/girl4" : 1,
                "/d/beijing/npc/old1" : 1,
                "/clone/npc/walker" : 1,
        ]));
	set("coor/x", -6990);
	set("coor/y", 2180);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}