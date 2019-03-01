inherit ROOM;

void create()
{
        set("short", "飯館");
        set("long", @LONG
這是一家湘西的小飯館，布置頗為簡易，顧客多是匆匆的行人，
買點包子、雞腿、米酒就趕路去了。
LONG );
        set("exits", ([
                "west" : __DIR__"beidajie2",
               ]));
        set("objects", ([
                __DIR__"npc/xiaoer" : 1,
        ]));

        set("coor/x", -450);
        set("coor/y", -180);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
