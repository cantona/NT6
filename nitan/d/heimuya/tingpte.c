inherit ROOM;
 
void create()
{
        set("short", "天香堂廂房");
        set("long", @LONG
偏廳布置的頗為優雅，絲毫沒有正廳上的嚴肅氣氛。一張紅木大
桌邊上有個書櫃，櫃裡擺了各式各樣的書。牆上掛著幾幅字畫。堂的
一邊擺著幾張大床，讓人看了就想睡覺。
LONG );
        set("sleep_room", 1);
        set("no_fight", 1);
        set("no_clean_up", 0);
        set("exits", ([
                    "west"   : __DIR__"tian1",
        ]));
        set("objects", ([
                __DIR__"npc/dizi6" : 1,
        ]));       
        setup();
        replace_program(ROOM);
}