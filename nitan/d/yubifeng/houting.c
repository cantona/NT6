// /yubifeng/houting.c
// Last modified by winder 2003.9.2

inherit ROOM;

void create()
{
        set("short", "後廳");
        set("long", @long
這裏是莊內人用飯休息的地方，四角各生着一盆大炭火，一張八仙
桌居中，周圍打掃得甚是乾淨。管家正在和下人們吩咐着什麼。
long );
        set("exits", ([
                "west"  : __DIR__"zoulang5",
                "east"  : __DIR__"zoulang6",
                "north" : __DIR__"houyuan",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "yubifeng");
        set("coor/x", 6120);
        set("coor/y", 5200);
        set("coor/z", 100);
        setup();
        replace_program(ROOM);
}