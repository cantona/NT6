inherit ROOM;

void create()
{
        set("short", "西廳");
        set("long", @LONG
偏廳佈置的頗為優雅，絲毫沒有正廳上的嚴肅氣氛。一張紅
木大桌邊上有個書櫃，櫃裏擺了各式各樣的書。牆上掛着幾幅字
畫。看來客人少時，這裏又可以當書房用。
LONG);
        set("exits", ([
                "east"  : __DIR__"shang_dating",
        ]));
	set("coor/x", -6760);
	set("coor/y", 1880);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}