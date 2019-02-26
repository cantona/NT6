inherit ROOM;

void create()
{
        set("short", "馬莊宴廳");
        set("long", @LONG
這裏是馬莊的正廳，佈置的頗為優雅，絲毫沒有正廳上的
嚴肅氣氛。一張紅木大桌邊上有個書櫃，櫃裏擺了各式各樣的
書。幾個丐幫的乞丐圍聚在這裏。
LONG);
        set("region", "yangzhou");
        set("exits", ([
                "east"  : __DIR__"ma_zhengting",
        ]));
        set("objects", ([
                "/d/gaibang/npc/2dai" : 1,
                "/d/gaibang/npc/3dai" : 1,
                "/d/gaibang/npc/4dai" : 1,
        ]));
        set("no_clean_up", 0);
	set("coor/x", 20);
	set("coor/y", -40);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}