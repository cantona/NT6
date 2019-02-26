inherit ROOM;

void create()
{
        set("short", "兵營");
        set("long", @LONG
這裏是兵營，密密麻麻到處都是官兵，有的在武將的指揮下列隊操練，
有的獨自在練功，有的坐着、躺着正在休息。南牆下坐着主帥，不動聲色
地尋視着四周。看到你進來，他們全都向你包圍了過來，形勢看來不太妙。
北邊有一個兵器庫。
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "north" : __DIR__"bingqiku",
                  "south" : __DIR__"bingyindamen",
        ]));
        set("objects", ([
                "/d/kaifeng/npc/guanbing" : 4,
                "/d/city/npc/wujiang" : 1,
        ]));
	set("coor/x", -7030);
	set("coor/y", 2200);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}