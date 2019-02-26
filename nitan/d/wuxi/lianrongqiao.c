// Room: /d/wuxi/lianrongqiao.c
// Winder 2000/02/22 

inherit ROOM;

void create()
{
        set("short", "蓮蓉橋");
        set("long", @LONG
蓮蓉橋俗稱北門大橋，因為是一條官道，橋面修得很寬很平坦，上
面足可讓六匹馬並行而過。這裏由於官兵盤問較緊，不準小商小販來此
營生，經過的人也不太多。橋面顯得十分乾淨，也很冷清，向南去是城
裏，向北是長江邊。
LONG );
        set("outdoors", "wuxi");
        set("exits", ([
                "north" : __DIR__"road5",
                "south" : __DIR__"northgate",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1040);
	set("coor/y", -680);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}