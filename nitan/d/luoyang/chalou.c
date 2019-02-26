inherit ROOM;

void create()
{
        set("short", "壺記茶樓");
        set("long", @LONG
你一走進來，就聞到一股茶香沁入心脾，精神為之一爽。幾張八仙桌
一字排開，坐滿了客人，或高聲談笑，或交頭接耳。你要想打聽江湖掌故
和謠言，這裏是個好所在。後面是休息室，到樓上可以聽人説書。
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"sroad2",
                  "up" : __DIR__"chalou2",
                  "west" : __DIR__"rest",
        ]));
        set("objects", ([
                "/d/beijing/npc/teahuoji" : 1,
        ]));
	set("coor/x", -7000);
	set("coor/y", 2160);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}