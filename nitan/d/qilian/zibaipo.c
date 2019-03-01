// Room: /d/qilian/zibaipo.c
// Winder 2000/09/05 

inherit ROOM;

void create()
{
        set("short", "紫柏坡");
        set("long", @LONG
紫柏坡在祈連山脈中是座小山峰，但風景絕佳。漫山小溪潺潺，有
山魚悠遊其中。周山盛開一種紫色山花，四季不謝，相傳是由紫德真人
所種，但以訛傳訛，得名紫柏，其實山上一顆柏樹也沒有。
LONG );
        set("outdoors", "qilian");
        set("exits", ([
                "east"      : __DIR__"tieshishan",
                "westup"    : __DIR__"qitianfeng",
                "northeast" : __DIR__"ailaoshan",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -14000);
        set("coor/y", 3000);
        set("coor/z", 100);
        setup();
        replace_program(ROOM);
}