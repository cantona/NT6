inherit ROOM;
 
void create()
{
        set("short", "天香堂偏廳");
        set("long", @LONG
偏廳佈置的頗為優雅，絲毫沒有正廳上的嚴肅氣氛。一張紅木大
桌邊上有個書櫃，櫃裏擺了各式各樣的書。牆上掛着幾幅字畫。
LONG );
        set("exits", ([
                    "east"   : __DIR__"tian1",
        ]));
        setup();
        replace_program(ROOM);
}