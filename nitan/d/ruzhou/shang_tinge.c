inherit ROOM;

void create()
{
        set("short", "東廳");
        set("long", @LONG
偏廳布置的頗為優雅，絲毫沒有正廳上的嚴肅氣氛。一張紅
木大桌邊上有個書櫃，櫃裡擺了各式各樣的書。牆上掛著幾幅字
畫。看來客人少時，這裡又可以當書房用。
LONG);
        set("exits", ([
                "west"  : __DIR__"shang_dating",
        ]));
	set("coor/x", -6740);
	set("coor/y", 1880);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}