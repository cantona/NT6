inherit ROOM;

void create()
{
        set("short", "王府正廳");
        set("long", @LONG
這裡是平西王府的正廳，正中兩把太師椅，牆上掛著一幅
字畫，布置的簡單清潔。這裡空盪盪的沒有一個人，看來平西
王平時極少來這裡，只有幾個下人不時來打掃一下。
LONG);
        set("exits", ([
                "south"    :__DIR__"wangfu1",
        ]));

	set("coor/x", -16840);
	set("coor/y", -7170);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);         
}