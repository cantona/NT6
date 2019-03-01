// Room: /d/shaolin/zhonglou2.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "鐘樓二層");
        set("long", @LONG
每個樓層上都舖設了結實的木樓板，八角形的牆身上則開了四扇
大窗。從窗孔看，牆體也是極為厚實。從這裡往外眺望，可以看到圍
繞塔周的小園以及北邊的竹林，隨風飄來陣陣竹葉的清香。
LONG );
        set("exits", ([
                "up" : __DIR__"zhonglou3",
                "down" : __DIR__"zhonglou1",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
